#include "inc/main.h"
#include "inc/defines.h"
#include "inc/benchmark.h"

#include <math.h>
#include <unistd.h>
#include <signal.h>

#define RUN_FREQUENCY 1000 // Hz

int main(void) {
	BENCHMARK_START();
	
	// Register signal handler
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		eprintf("Error registering signal handler\n");
		return EXIT_FAILURE;
	}

	can_messages_init();
	can_init(&can[CAN_SOCKET_PRIMARY], "can0");
	can_init(&can[CAN_SOCKET_SECONDARY], "can1");

	if (can_open_socket(&can[CAN_SOCKET_PRIMARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_PRIMARY].device);
		return EXIT_FAILURE;
	}
	if (can_open_socket(&can[CAN_SOCKET_SECONDARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_SECONDARY].device);
		return EXIT_FAILURE;
	}
	if (!init_model()) {
		eprintf("Error initializing model\n");
		return EXIT_FAILURE;
	}

	// Start CAN threads
	kill_can_thread = false;
	pthread_mutex_init(&model_mutex, NULL);

	pthread_create(&can_threads[CAN_SOCKET_PRIMARY], NULL, (void *)can_thread, (void *)CAN_SOCKET_PRIMARY);
	pthread_create(&can_threads[CAN_SOCKET_SECONDARY], NULL, (void *)can_thread, (void *)CAN_SOCKET_SECONDARY);

	fprintf(stdout, "\n");
	running = true;
	while (running) {
		BENCHMARK_TICK();
		{
			BENCHMARK_TICK();
			pthread_mutex_lock(&model_mutex);

			// Velocity Estimation
			ve_model_set_data(&can_data);
			Velocity_Estimation_step(&ve_model);
			// Torque Vectoring
			torque_model_set_data(&can_data);
			Torque_step(&torque_model);
			// Slip Control
			slip_model_set_data(&can_data);
			SlipV2_step(&slip_model);

			pthread_mutex_unlock(&model_mutex);
			BENCHMARK_TOCK();
		}

		can_send_data();

		BENCHMARK_TOCK();

		usleep(1.0 / RUN_FREQUENCY * 1e6);
	}

	BENCHMARK_END();
	return EXIT_SUCCESS;
}

void can_thread(can_socket_t socket) {
	can_message_t message;
	struct can_frame frame;

	message.socket = socket;
	message.can = &can[socket];
	while (!kill_can_thread) {
		if (can_receive(&can[socket], &frame) < 0) {
			eprintf("Error reading from socket %s\n", can[socket].device);
			continue;
		}
		message.frame = frame;

		pthread_mutex_lock(&model_mutex);
		can_messages_parse(&message, &can_data);
		pthread_mutex_unlock(&model_mutex);
	}
}

bool init_model(void) {
	// Velocity Estimation
	ve_model.dwork = &ve_rtDW;
	Velocity_Estimation_initialize(&ve_model);

	torque_model.dwork = &torque_rtDW;
	Torque_initialize(&torque_model);

	slip_model.dwork = &slip_rtDW;
	SlipV2_initialize(&slip_model);

	return true;
}

void ve_model_set_data(can_data_t *can_data) {
	// Velocity Estimation Data
	rtaxG_Velocity_Estimation = can_data->accel_x;

	rtmap_motor_Velocity_Estimation = can_data->map_pw;

	rtomega_fl_Velocity_Estimation = can_data->omega_fl;
	rtomega_fr_Velocity_Estimation = can_data->omega_fr;
	rtomega_rl_Velocity_Estimation = can_data->omega_rl;
	rtomega_rr_Velocity_Estimation = can_data->omega_rr;
}

void torque_model_set_data(can_data_t *can_data) {
	// All0 Data
	rtbrake_Torque = can_data->brake;
	rtDriver_req_Torque = can_data->throttle;
	rtSteeringangle_Torque = can_data->steering_angle;

	rtmap_tv_Torque = can_data->map_tv;
	rtmap_sc_Torque = can_data->map_sc;

	rtyaw_rate_Torque = can_data->gyro_z;

	rtTm_rl_Torque = rtTmax_rl_Velocity_Estimation;
	rtTm_rr_Torque = rtTmax_rr_Velocity_Estimation;

	rtu_bar_Torque = rtu_bar_Velocity_Estimation;
	rtomega_rl_Torque = rtomega_rl_Velocity_Estimation;
	rtomega_rr_Torque = rtomega_rr_Velocity_Estimation;
}

void slip_model_set_data(can_data_t *can_data) {
	// SlipV2 Data
	rtbrake_SlipV2 = can_data->brake;
	rtDriver_req_SlipV2 = can_data->throttle;
	rtSteeringangle_SlipV2 = can_data->steering_angle;

	rtmap_sc_SlipV2 = can_data->map_sc;
	rtmap_tv_SlipV2 = can_data->map_tv;

	rtyaw_rate_SlipV2 = can_data->gyro_z;

	rtTm_rl_SlipV2 = rtTmax_rl_Velocity_Estimation;
	rtTm_rr_SlipV2 = rtTmax_rr_Velocity_Estimation;

	rtu_bar_SlipV2 = rtu_bar_Velocity_Estimation;
	rtomega_rl_SlipV2 = rtomega_rl_Velocity_Estimation;
	rtomega_rr_SlipV2 = rtomega_rr_Velocity_Estimation;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0, state_timestamp = 0;

	if (timestamp - PRIMARY_INTERVAL_CONTROL_OUTPUT * 1e3 > out_timestamp) {
		out_timestamp = timestamp;

		static primary_control_output_t out_src_raw;
		static primary_control_output_converted_t out_src;

		out_src.estimated_velocity = rtu_bar_Velocity_Estimation;
#if 1==ENABLE_TORQUE_VECTORING
			out_src.tmax_l = rtTm_rl_Torque;
			out_src.tmax_r = rtTm_rr_Torque;
			out_src.torque_l = rtTm_rl_a_Torque;
			out_src.torque_r = rtTm_rr_m_Torque;
#else
			out_src.tmax_l = rtTm_rl_SlipV2;
			out_src.tmax_r = rtTm_rr_SlipV2;
			out_src.torque_l = rtTm_rl_a_SlipV2;
			out_src.torque_r = rtTm_rr_m_SlipV2;
#endif

		primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
	}

	if (timestamp - SECONDARY_INTERVAL_CONTROL_STATE * 1e3 > state_timestamp) {
		state_timestamp = timestamp;

		static secondary_control_state_t state_src_raw;
		static secondary_control_state_converted_t state_src;

		state_src.map_pw = rtmap_motor_Velocity_Estimation;
#if 1==ENABLE_TORQUE_VECTORING
		state_src.map_sc = rtmap_sc_Torque;
		state_src.map_tv = rtmap_tv_Torque;
#else
		state_src.map_sc = rtmap_sc_SlipV2;
		state_src.map_tv = rtmap_tv_SlipV2;
#endif

		secondary_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
		secondary_control_state_pack(data, &state_src_raw, SECONDARY_CONTROL_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_CONTROL_STATE_FRAME_ID, data, SECONDARY_CONTROL_STATE_BYTE_SIZE);
	}
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
	}
}