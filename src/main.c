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

			switch (CONTROL_MODE) {
			case CONTROL_SLIP:
				// Slip Control
				slip_model_set_data(&can_data);
				SlipV1_step(&slip_model);
				break;
			case CONTROL_TORQUE:
				// Torque Vectoring
				torque_model_set_data(&can_data);
				Torque_step(&torque_model);
				break;
			case CONTROL_COMBINED:
				// All Control
				all_model_set_data(&can_data);
				AllControl_step(&all_model);
				break;
			default:
				break;
			}

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
	Torque_initialize(&torque_model);

	all_model.dwork = &all_rtDW;
	AllControl_initialize(&all_model);

	slip_model.dwork = &slip_rtDW;
	SlipV1_initialize(&slip_model);

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

void torque_model_set_data(can_data_t *can_data) {
	// All0 Data
	rtbrake_Torque = can_data->brake;
	rtDriver_req_Torque = can_data->throttle;
	rtSteeringangle_Torque = can_data->steering_angle;

	rtmap_sc_Torque = can_data->map_sc;
	rtmap_tv_Torque = can_data->map_tv;

	rtTel_Inp_Ki_Torque = TV_PID_KI;
	rtTel_Inp_Kp_Torque = TV_PID_KP;
	rtTel_Inp_Kus_Torque = TV_KUF;

	rtyaw_rate_Torque = can_data->gyro_z;

	rtTm_rl_Torque = torque_max(can_data);
	rtTm_rr_Torque = torque_max(can_data);

	rtu_bar_Torque = u_bar;
	rtomega_rl_Torque = can_data->omega_rl;
	rtomega_rr_Torque = can_data->omega_rr;
}

void slip_model_set_data(can_data_t *can_data) {
	// SlipV1 Data
	rtbrake_SlipV1 = can_data->brake;
	rtDriver_req_SlipV1 = can_data->throttle;
	rtSteeringangle_SlipV1 = can_data->steering_angle;

	rtmap_sc_SlipV1 = can_data->map_sc;
	rtmap_tv_SlipV1 = can_data->map_tv;

	rtTel_Inp_SC_Ki_SlipV1 = 2500.0;
	rtTel_Inp_SC_Kp_SlipV1 = 100.0;
	rtTel_Inp_SC_LambdaRef_SlipV1 = 0.05;
	rtTel_Inp_minT_SlipV1 = 20.0;
	// rtTel_Inp_T0_SlipV1
	// rtTel_Inp_Vramp_SlipV1

	rtyaw_rate_SlipV1 = can_data->gyro_z;

	rtTm_rl_SlipV1 = torque_max(can_data);
	rtTm_rr_SlipV1 = torque_max(can_data);

	rtu_bar_SlipV1 = u_bar;
	rtomega_rl_SlipV1 = can_data->omega_rl;
	rtomega_rr_SlipV1 = can_data->omega_rr;
}

void all_model_set_data(can_data_t *can_data) {
	// AllControl Data
	rtDriver_req_AllControl = can_data->throttle;
	rtbrake_AllControl = can_data->brake;
	rtSteeringangle_AllControl = can_data->steering_angle;

	rtTm_rl_AllControl = torque_max(can_data);
	rtTm_rr_AllControl = torque_max(can_data);
	rtmap_sc_AllControl = can_data->map_sc;
	rtmap_tv_AllControl = can_data->map_tv;

	rtTel_Inp_SC_PeakTorque_AllCont = SLIP_PEAK;
	rtTel_Inp_SC_SpeedCutoff_AllCon = SLIP_SPEED_CUTOFF;
	rtTel_Inp_SC_StartTorque_AllCon = SLIP_START_TORQUE;
	rtTel_Inp_TV_Ki_AllControl = TV_PID_KI;
	rtTel_Inp_TV_Kp_AllControl = TV_PID_KP;
	rtTel_Inp_TV_Kus_AllControl = TV_KUF;

	rtomega_rl_AllControl = can_data->omega_rl;
	rtomega_rr_AllControl = can_data->omega_rr;
	rtu_bar_AllControl = u_bar;
	rtyaw_rate_AllControl = can_data->gyro_z;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0, state_timestamp = 0;

	if (timestamp - PRIMARY_INTERVAL_CONTROL_OUTPUT * 1e3 > out_timestamp) {
		out_timestamp = timestamp;

		real_T t_rl = 0.0;
		real_T t_rr = 0.0;
		real_T tm_rl = 0.0;
		real_T tm_rr = 0.0;
		switch (CONTROL_MODE) {
		case CONTROL_SLIP:
			t_rl = rtTm_rl_a_SlipV1;
			t_rr = rtTm_rr_m_SlipV1;
			tm_rl = rtTm_rl_SlipV1;
			tm_rr = rtTm_rr_SlipV1;
			break;
		case CONTROL_TORQUE:
			t_rl = rtTm_rl_a_Torque;
			t_rr = rtTm_rr_m_Torque;
			tm_rl = rtTm_rl_Torque;
			tm_rr = rtTm_rr_Torque;
			break;
		case CONTROL_COMBINED:
			t_rl = rtTm_rl_a_AllControl;
			t_rr = rtTm_rr_m_AllControl;
			tm_rl = rtTm_rl_AllControl;
			tm_rr = rtTm_rr_AllControl;
			break;
		default:
			break;
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
		out_src.tmax_l = tm_rl;
		out_src.tmax_r = tm_rr;
		out_src.torque_l = t_rl;
		out_src.torque_r = t_rr;
		static primary_control_output_t out_src_raw;
		primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
#endif
	}

	if (timestamp - SECONDARY_INTERVAL_CONTROL_STATE * 1e3 > state_timestamp) {
		state_timestamp = timestamp;
		real_T map_sc = 0.0;
		real_T map_tv = 0.0;
		switch (CONTROL_MODE) {
		case CONTROL_SLIP:
			map_sc = rtmap_sc_SlipV1;
			map_tv = rtmap_tv_SlipV1;
			break;
		case CONTROL_TORQUE:
			map_sc = rtmap_sc_Torque;
			map_tv = rtmap_tv_Torque;
			break;
		case CONTROL_COMBINED:
			map_sc = rtmap_sc_AllControl;
			map_tv = rtmap_tv_AllControl;
			break;
		default:
			break;
		}

#if 1 == SIMULATOR
		static simulator_control_state_converted_t state_src;
		state_src.map_pw = u_bar;
		state_src.map_sc = map_sc;
		state_src.map_tv = map_tv;
		static simulator_control_state_t state_src_raw;
		simulator_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
		simulator_control_state_pack(data, &state_src_raw, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_STATE_FRAME_ID, data, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
#else
		static secondary_control_state_converted_t state_src;
		state_src.map_pw = u_bar;
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
