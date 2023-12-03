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

	all_model.dwork = &all_rtDW;
	AllControl_initialize(&all_model);

	// slip_model.dwork = &slip_rtDW;
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

	rtmap_tv_Torque = 1.0; // can_data->map_tv;
	rtmap_sc_Torque = 0.0; // can_data->map_sc;

	rtTel_Inp_Ki_Torque = TV_PID_KI;
	rtTel_Inp_Kp_Torque = TV_PID_KP;
	rtTel_Inp_Kus_Torque = TV_KUF;

	rtyaw_rate_Torque = can_data->gyro_z;

	rtTm_rl_Torque = 100.0f; // rtTmax_rl_Velocity_Estimation;
	rtTm_rr_Torque = 100.0f; // rtTmax_rr_Velocity_Estimation;

	rtu_bar_Torque = rtu_bar_Velocity_Estimation;
	rtomega_rl_Torque = rtomega_rl_Velocity_Estimation;
	rtomega_rr_Torque = rtomega_rr_Velocity_Estimation;
}

void slip_model_set_data(can_data_t *can_data) {
	// SlipV2 Data
	rtbrake_SlipV2 = can_data->brake;
	rtDriver_req_SlipV2 = can_data->throttle;
	rtSteeringangle_SlipV2 = can_data->steering_angle;

	rtmap_sc_SlipV2 = 1.0; // can_data->map_sc;
	rtmap_tv_SlipV2 = 1.0; // can_data->map_tv;

	// rtTel_Inp_SC_Ki_SlipV2 = SC_PID_KI;
	// rtTel_Inp_SC_Kp_SlipV2 = SC_PID_KP;
	// rtTel_Inp_SC_LambdaRef_SlipV2 = SC_LAMBDA_REF;
	// rtTel_Inp_SC_SpeedCutoff_SlipV2 = SC_SPEED_CUTOFF;

	rtTel_Inp_SC_PeakTorque_SlipV2 = SLIP_PEAK;
	rtTel_Inp_SC_SpeedCutoff_SlipV2 = SLIP_SPEED_CUTOFF;
	rtTel_Inp_SC_StartTorque_SlipV2 = SLIP_START_TORQUE;

	rtyaw_rate_SlipV2 = can_data->gyro_z;

	rtTm_rl_SlipV2 = 100.0f; // rtTmax_rl_Velocity_Estimation;
	rtTm_rr_SlipV2 = 100.0f; // rtTmax_rr_Velocity_Estimation;

	rtu_bar_SlipV2 = rtu_bar_Velocity_Estimation;
	rtomega_rl_SlipV2 = rtomega_rl_Velocity_Estimation;
	rtomega_rr_SlipV2 = rtomega_rr_Velocity_Estimation;
}

void all_model_set_data(can_data_t *can_data) {
	// AllControl Data
	rtDriver_req_AllControl = can_data->throttle;
	rtbrake_AllControl = can_data->brake;
	rtSteeringangle_AllControl = can_data->steering_angle;
	rtTm_rl_AllControl = 100.0f; // rtTmax_rl_Velocity_Estimation;
	rtTm_rr_AllControl = 100.0f; // rtTmax_rr_Velocity_Estimation;
	rtmap_sc_AllControl = 0.0;	 // can_data->map_sc;
	rtmap_tv_AllControl = 0.0;	 // can_data->map_tv;
	rtomega_rl_AllControl = rtomega_rl_Velocity_Estimation;
	rtomega_rr_AllControl = rtomega_rr_Velocity_Estimation;
	rtu_bar_AllControl = rtu_bar_Velocity_Estimation;
	rtyaw_rate_AllControl = can_data->gyro_z;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0, state_timestamp = 0, debug_timestamp = 0;

	if (timestamp - PRIMARY_INTERVAL_CONTROL_OUTPUT * 1e3 > out_timestamp) {
		out_timestamp = timestamp;

		real_T t_rl = 0.0;
		real_T t_rr = 0.0;
		real_T tm_rl = 0.0;
		real_T tm_rr = 0.0;
		if (ENABLE_TORQUE_VECTORING) {
			t_rl = rtTm_rl_a_Torque;
			t_rr = rtTm_rr_m_Torque;
			tm_rl = rtTm_rl_Torque;
			tm_rr = rtTm_rr_Torque;
		} else {
			t_rl = rtTm_rl_a_SlipV2;
			t_rr = rtTm_rr_m_SlipV2;
			tm_rl = rtTm_rl_SlipV2;
			tm_rr = rtTm_rr_SlipV2;
		}

		if (SIMULATOR) {
			static simulator_control_output_converted_t out_src;
			out_src.estimated_velocity = rtu_bar_Velocity_Estimation;
			out_src.tmax_l = tm_rl;
			out_src.tmax_r = tm_rr;
			out_src.torque_l = t_rl;
			out_src.torque_r = t_rr;
			static simulator_control_output_t out_src_raw;
			simulator_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
			simulator_control_output_pack(data, &out_src_raw, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_OUTPUT_FRAME_ID, data, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
		} else {
			static primary_control_output_converted_t out_src;
			out_src.estimated_velocity = rtu_bar_Velocity_Estimation;
			out_src.tmax_l = tm_rl;
			out_src.tmax_r = tm_rr;
			out_src.torque_l = t_rl;
			out_src.torque_r = t_rr;
			static primary_control_output_t out_src_raw;
			primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
			primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		}
	}

	if (timestamp - SECONDARY_INTERVAL_CONTROL_STATE * 1e3 > state_timestamp) {
		state_timestamp = timestamp;
		real_T map_sc = 0.0;
		real_T map_tv = 0.0;
		if (ENABLE_TORQUE_VECTORING) {
			map_sc = rtmap_sc_Torque;
			map_tv = rtmap_tv_Torque;
		} else {
			map_sc = rtmap_sc_SlipV2;
			map_tv = rtmap_tv_SlipV2;
		}

		if (SIMULATOR) {
			static simulator_control_state_converted_t state_src;
			state_src.map_pw = rtmap_motor_Velocity_Estimation;
			state_src.map_sc = map_sc;
			state_src.map_tv = map_tv;
			static simulator_control_state_t state_src_raw;
			simulator_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
			simulator_control_state_pack(data, &state_src_raw, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_STATE_FRAME_ID, data, SIMULATOR_CONTROL_STATE_BYTE_SIZE);
		} else {
			static secondary_control_state_converted_t state_src;
			state_src.map_pw = rtmap_motor_Velocity_Estimation;
			state_src.map_sc = map_sc;
			state_src.map_tv = map_tv;
			static secondary_control_state_t state_src_raw;
			secondary_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
			secondary_control_state_pack(data, &state_src_raw, SECONDARY_CONTROL_STATE_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_CONTROL_STATE_FRAME_ID, data, SECONDARY_CONTROL_STATE_BYTE_SIZE);
		}
	}
	if (timestamp - SECONDARY_INTERVAL_DEBUG_SIGNAL * 1e3 > debug_timestamp) {
		debug_timestamp = timestamp;

		if (SIMULATOR) {
			static simulator_debug_signal_converted_t debug_src;
			debug_src.field_1 = rtTel_Out_error_Torque / 100.0;
			debug_src.field_2 = rtERROR_SlipV2 / 100.0;
			static simulator_debug_signal_t debug_src_raw;
			simulator_debug_signal_conversion_to_raw_struct(&debug_src_raw, &debug_src);
			simulator_debug_signal_pack(data, &debug_src_raw, SIMULATOR_DEBUG_SIGNAL_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_DEBUG_SIGNAL_FRAME_ID, data, SIMULATOR_DEBUG_SIGNAL_BYTE_SIZE);
		} else {
			static secondary_debug_signal_converted_t debug_src;
			debug_src.field_1 = rtTel_Out_error_Torque;
			debug_src.field_2 = rtERROR_SlipV2;
			static secondary_debug_signal_t debug_src_raw;
			secondary_debug_signal_conversion_to_raw_struct(&debug_src_raw, &debug_src);
			secondary_debug_signal_pack(data, &debug_src_raw, SECONDARY_DEBUG_SIGNAL_BYTE_SIZE);
			can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_DEBUG_SIGNAL_FRAME_ID, data, SECONDARY_DEBUG_SIGNAL_BYTE_SIZE);
		}
	}
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
	}
}
