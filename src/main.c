#include "inc/main.h"
#include "inc/defines.h"
#include "inc/benchmark.h"

#include <math.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	BENCHMARK_START();

	// Register signal handler
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		eprintf("Error registering signal handler\n");
		return EXIT_FAILURE;
	}

	if (!init_model()) {
		eprintf("Error initializing model\n");
		return EXIT_FAILURE;
	}

	can_messages_init();
	// Start CAN threads
	kill_can_thread = false;
	pthread_mutex_init(&model_mutex, NULL);

	can_init(&can[CAN_SOCKET_PRIMARY], "can0");
	if (can_open_socket(&can[CAN_SOCKET_PRIMARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_PRIMARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_PRIMARY], NULL, (void *)can_thread, (void *)CAN_SOCKET_PRIMARY);
#if 0 == SIMULATOR
	can_init(&can[CAN_SOCKET_SECONDARY], "can1");
	if (can_open_socket(&can[CAN_SOCKET_SECONDARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_SECONDARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_SECONDARY], NULL, (void *)can_thread, (void *)CAN_SOCKET_SECONDARY);
#endif

	fprintf(stdout, "\n");
	running = true;
	while (running) {
		BENCHMARK_TICK();
		{
			BENCHMARK_TICK();
			pthread_mutex_lock(&model_mutex);

			// Velocity Estimation
			velocity_estimation(&can_data, &u_bar);

			// Slip Control
			slip_model_set_data(&can_data);
			SLIP_step(&slip_model);
			// Torque Vectoring
			torque_model_set_data(&can_data);
			TV_step(&torque_model);

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
	torque_model.dwork = &torque_rtDW;
	TV_initialize(&torque_model);

	slip_model.dwork = &slip_rtDW;
	SLIP_initialize(&slip_model);

	return true;
}

double torque_max(can_data_t *can_data) {
	(void)can_data;
	return 100.0;
}

void velocity_estimation(can_data_t *can_data, double *u_bar) {
	double delta = can_data->steering_angle / STEER_CONVERSION_FACTOR;
	double v_g = WHEEL_RADIUS * (can_data->omega_fl + can_data->omega_fr) / 2.0;
	*u_bar = v_g * cos(delta);
}

void slip_model_set_data(can_data_t *can_data) {
	// rtbrake_SlipV1 = can_data->brake;
	// rtSteeringangle_SlipV1 = can_data->steering_angle;
	// rtmap_tv_SlipV1 = can_data->map_tv;

	SLIP_map_sc = can_data->map_sc;
	SLIP_Driver_req = can_data->throttle;
	SLIP_yaw_rate = can_data->gyro_z;
	SLIP_omega_rl = can_data->omega_rl;
	SLIP_omega_rr = can_data->omega_rr;

	SLIP_Tm_rl = torque_max(can_data);
	SLIP_Tm_rr = torque_max(can_data);

	SLIP_u_bar = u_bar;

	SLIP_Inp_Ki = 2500.0;
	SLIP_Inp_Kp = 100.0;
	SLIP_Inp_LambdaRef = 0.05;
	SLIP_Inp_UppSatLim = 70.0;
	SLIP_Inp_minT = 20.0;
	SLIP_Inp_IntegralResetValue = 0;
}

void torque_model_set_data(can_data_t *can_data) {
	// rtbrake_Torque = can_data->brake;
	// rtmap_sc_Torque = can_data->map_sc;

	TV_map_tv = can_data->map_tv;
	TV_Driver_req = can_data->throttle;
	TV_Steeringangle = can_data->steering_angle;
	TV_yaw_rate = can_data->gyro_z;
	TV_u_bar = u_bar;

	TV_Inp_Ki = TV_PID_KI;
	TV_Inp_Kp = TV_PID_KP;
	TV_Inp_Kus = TV_KUF;

	TV_Tm_rl = SLIP_Out_Tm_rl;
	TV_Tm_rr = SLIP_Out_Tm_rr;

	TV_lambda_rr = SLIP_Out_Tmax_rl_slip;
	TV_lambda_rr_n = SLIP_Out_Tmax_rr_slip;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0, state_timestamp = 0;

	if (timestamp - 10 * 1e3 > out_timestamp) {
		out_timestamp = timestamp;

		real_T t_rl;
		real_T t_rr;
		real_T tmax_rl;
		real_T tmax_rr;

		if (true) { // only slip
			t_rl = SLIP_Out_Tm_rl;
			t_rr = SLIP_Out_Tm_rr;
			tmax_rl = SLIP_Out_Tmax_rl_slip;
			tmax_rr = SLIP_Out_Tmax_rr_slip;
		} else {
			t_rl = TV_Out_Tm_rl;
			t_rr = TV_Out_Tm_rr;
			tmax_rl = TV_Tm_rl;
			tmax_rr = TV_Tm_rr;
		}

#if 1 == SIMULATOR
		static simulator_control_output_converted_t out_src;
		out_src.estimated_velocity = u_bar;
		out_src.tmax_l = tm_rl;
		out_src.tmax_r = tm_rr;
		out_src.torque_l = t_rl;
		out_src.torque_r = t_rr;
		static simulator_control_output_t out_src_raw;
		simulator_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		simulator_control_output_pack(data, &out_src_raw, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_OUTPUT_FRAME_ID, data, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
#else
		static primary_control_output_converted_t out_src;
		out_src.estimated_velocity = u_bar;
		out_src.tmax_l = tmax_rl;
		out_src.tmax_r = tmax_rr;
		out_src.torque_l = t_rl;
		out_src.torque_r = t_rr;
		static primary_control_output_t out_src_raw;
		primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
#endif
	}

	if (timestamp - 10 * 1e3 > state_timestamp) {
		state_timestamp = timestamp;
		real_T map_sc = SLIP_map_sc;
		real_T map_tv = TV_map_tv;

#if 1 == SIMULATOR
		static simulator_control_state_converted_t state_src;
		state_src.map_pw = can_data.map_pw;
		state_src.map_sc = map_sc;
		state_src.map_tv = map_tv;
		static simulator_control_state_t state_src_raw;
		simulator_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
		simulator_control_state_pack(data, &state_src_raw, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_STATE_FRAME_ID, data, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
#else
		static secondary_control_state_converted_t state_src;
		state_src.map_pw = can_data.map_pw;
		state_src.map_sc = map_sc;
		state_src.map_tv = map_tv;
		static secondary_control_state_t state_src_raw;
		secondary_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
		secondary_control_state_pack(data, &state_src_raw, SECONDARY_CONTROL_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_CONTROL_STATE_FRAME_ID, data, SECONDARY_CONTROL_STATE_BYTE_SIZE);
#endif
	}
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
		kill_can_thread = true;
	}
}
