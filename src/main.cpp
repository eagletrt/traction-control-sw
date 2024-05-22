#include "inc/main.hpp"
#include "inc/can_messages.h"
extern "C" {
#include "inc/defines.h"
#include "inc/benchmark.h"
}
#include "external/soc/core/src/soc/soc.hpp"

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

	can_init(&can[CAN_SOCKET_PRIMARY], "vcan0");
	if (can_open_socket(&can[CAN_SOCKET_PRIMARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_PRIMARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_PRIMARY], NULL, can_thread, &can[CAN_SOCKET_PRIMARY]);
#if 0 == SIMULATOR
	can_init(&can[CAN_SOCKET_SECONDARY], "vcan1");
	if (can_open_socket(&can[CAN_SOCKET_SECONDARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_SECONDARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_SECONDARY], NULL, can_thread, &can[CAN_SOCKET_SECONDARY]);
#endif

	usleep(1000);

	printf("Starting...\n");

	running = true;
	uint64_t last_soc_step = get_timestamp_u();
	while (running) {
		BENCHMARK_TICK();
		uint64_t t_loop_start = get_timestamp_u();
		{
			BENCHMARK_TICK();
			pthread_mutex_lock(&model_mutex);
			velocity_estimation(&can_data, &u_bar);
			torque_model_set_data(&can_data);
			slip_model_set_data(&can_data);
			regen_model_set_data(&can_data);
			pthread_mutex_unlock(&model_mutex);

			// Slip Control
			SLIP_step(&slip_model);
			// Torque Vectoring
			TV_step(&torque_model);
			// Regen
			Regen_step(&regen_model);

			uint64_t soc_dt_us = get_timestamp_u() - last_soc_step;
			if (1e6 / SOC_UPDATE_FREQUENCY <= soc_dt_us) {
				auto t1 = get_timestamp_u();
				soc.setDT(soc_dt_us / 1e6);
				soc.setTemperature(can_data.hv_mean_temp);
				soc.predict(can_data.hv_total_current / 4.0);
				soc.update(can_data.hv_min_cell_voltage);
				last_soc_step = get_timestamp_u();
				printf("%" PRIu64 "\n", get_timestamp_u() - t1);
			}

			BENCHMARK_TOCK();
		}

		can_send_data();

		BENCHMARK_TOCK();
		uint64_t loop_duration = get_timestamp_u() - t_loop_start;

		usleep(1e6 / RUN_FREQUENCY - loop_duration);
	}

	BENCHMARK_END();
	return EXIT_SUCCESS;
}

void *can_thread(void *data) {
	can_socket_t socket;
	can_message_t message;
	struct can_frame frame;

	if (data == &can[CAN_SOCKET_PRIMARY]) {
		socket = CAN_SOCKET_PRIMARY;
		printf("Start CAN primary reader\n");
	} else {
		socket = CAN_SOCKET_SECONDARY;
		printf("Start CAN secondary reader\n");
	}

	message.socket = socket;
	message.can = (can_t *)data;
	while (!kill_can_thread) {
		if (can_receive(message.can, &frame) < 0) {
			eprintf("Error reading from socket %s\n", message.can->device);
			continue;
		}
		message.frame = frame;

		pthread_mutex_lock(&model_mutex);
		can_messages_parse(&message, &can_data);
		pthread_mutex_unlock(&model_mutex);
	}
	return NULL;
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

void regen_model_set_data(can_data_t *can_data) {
	Regen_Driver_req = can_data->throttle * can_data->map_pw;
	Regen_Inp_map_sc = can_data->map_sc;
	Regen_Inp_omega_inv_rl = can_data->omega_rl;
	Regen_Inp_omega_inv_rr = can_data->omega_rr;
	Regen_pressure_f = can_data->brake_f;
	Regen_pressure_r = can_data->brake_r;
	Regen_Tm_rl = torque_max(can_data);
	Regen_Tm_rr = torque_max(can_data);
}

void slip_model_set_data(can_data_t *can_data) {
	// rtbrake_SlipV1 = can_data->brake;
	// rtSteeringangle_SlipV1 = can_data->steering_angle;
	// rtmap_tv_SlipV1 = can_data->map_tv;

	SLIP_map_sc = can_data->map_sc;
	SLIP_Driver_req = can_data->throttle * can_data->map_pw;
	SLIP_yaw_rate = can_data->gyro_z;
	SLIP_omega_rl = can_data->omega_rl;
	SLIP_omega_rr = can_data->omega_rr;

	SLIP_Tm_rl = torque_max(can_data);
	SLIP_Tm_rr = torque_max(can_data);

	SLIP_u_bar = u_bar;

	SLIP_Inp_Ki = 40000.0;
	SLIP_Inp_Kp = 50.0;
	SLIP_Inp_LambdaRef = 0.2;
	SLIP_Inp_UppSatLim = 70.0;
	SLIP_Inp_IntegralOffset = 20.0;
}

void torque_model_set_data(can_data_t *can_data) {
	// rtbrake_Torque = can_data->brake;
	// rtmap_sc_Torque = can_data->map_sc;

	TV_map_tv = can_data->map_tv;
	TV_Driver_req = can_data->throttle * can_data->map_pw;
	TV_Steeringangle = can_data->steering_angle;
	TV_yaw_rate = can_data->gyro_z;
	TV_u_bar = u_bar;

	TV_Inp_Ki = TV_PID_KI;
	TV_Inp_Kp = TV_PID_KP;
	TV_Inp_Kus = TV_KUF;

	TV_Tm_rl = torque_max(can_data);
	TV_Tm_rr = torque_max(can_data);

	TV_lambda_rr = SLIP_Out_Tmax_rl_slip;
	TV_lambda_rr_n = SLIP_Out_Tmax_rr_slip;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0;
	static uint64_t state_timestamp = 0;
	static uint64_t debug_timestamp = 0;
	static uint64_t soc_state_timestamp = 0;
	static uint64_t soc_cov_timestamp = 0;

	real_T map_sc = SLIP_map_sc;
	real_T map_tv = TV_map_tv;

	real_T t_rl;
	real_T t_rr;
	real_T tmax_rl;
	real_T tmax_rr;

#if 1 // REGEN
	t_rl = Regen_Out_Tm_rl;
	t_rr = Regen_Out_Tm_rr;
	tmax_rl = Regen_Tm_rl;
	tmax_rr = Regen_Tm_rr;
#elif 0 // ONLY SLIP
	t_rl = SLIP_Out_Tm_rl;
	t_rr = SLIP_Out_Tm_rr;
	tmax_rl = SLIP_Out_Tmax_rl_slip;
	tmax_rr = SLIP_Out_Tmax_rr_slip;
#else
	t_rl = TV_Out_Tm_rl;
	t_rr = TV_Out_Tm_rr;
	tmax_rl = TV_Tm_rl;
	tmax_rr = TV_Tm_rr;
#endif

	if (timestamp - out_timestamp > 1e4) {
		out_timestamp = timestamp;

#if 1 == SIMULATOR
		static simulator_control_output_converted_t out_src;
		out_src.estimated_velocity = u_bar;
		out_src.torque_max_l = tmax_rl;
		out_src.torque_max_r = tmax_rr;
		out_src.torque_l = t_rl;
		out_src.torque_r = t_rr;
		static simulator_control_output_t out_src_raw;
		simulator_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		simulator_control_output_pack(data, &out_src_raw, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_OUTPUT_FRAME_ID, data, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
#else
		static primary_control_output_converted_t out_src;
		out_src.estimated_velocity = u_bar;
		out_src.torque_max_l = tmax_rl;
		out_src.torque_max_r = tmax_rr;
		out_src.torque_l = t_rl;
		out_src.torque_r = t_rr;
		static primary_control_output_t out_src_raw;
		primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
#endif
	}

	if (timestamp - state_timestamp > 1e4) {
		state_timestamp = timestamp;

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
		static primary_control_status_converted_t state_src;
		state_src.map_pw = can_data.map_pw;
		state_src.map_sc = map_sc;
		state_src.map_tv = map_tv;
		static primary_control_status_t state_src_raw;
		primary_control_status_conversion_to_raw_struct(&state_src_raw, &state_src);
		primary_control_status_pack(data, &state_src_raw, PRIMARY_CONTROL_STATUS_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_STATUS_FRAME_ID, data, PRIMARY_CONTROL_STATUS_BYTE_SIZE);
#endif
	}
	if (timestamp - debug_timestamp > 1e4) {
		debug_timestamp = timestamp;
		static primary_debug_signal_1_converted_t debug_src;
		debug_src.field_1 = Regen_Out_brake_balance;
		debug_src.field_2 = Regen_Out_Tm_rl;

		static primary_debug_signal_1_t debug_src_raw;
		primary_debug_signal_1_conversion_to_raw_struct(&debug_src_raw, &debug_src);
		primary_debug_signal_1_pack(data, &debug_src_raw, PRIMARY_DEBUG_SIGNAL_1_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_DEBUG_SIGNAL_1_FRAME_ID, data, PRIMARY_DEBUG_SIGNAL_1_BYTE_SIZE);
	}
	if (timestamp - soc_state_timestamp > 1e5) {
		soc_state_timestamp = timestamp;
		const auto &state = soc.getState();
		static secondary_hv_soc_estimation_state_converted_t hv_soc_estimation_state;
		hv_soc_estimation_state.soc = state(_SOC);
		hv_soc_estimation_state.rc1 = state(_RC1);
		hv_soc_estimation_state.rc2 = state(_RC2);

		secondary_hv_soc_estimation_state_t raw;
		secondary_hv_soc_estimation_state_conversion_to_raw_struct(&raw, &hv_soc_estimation_state);
		secondary_hv_soc_estimation_state_pack(data, &raw, SECONDARY_HV_SOC_ESTIMATION_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_HV_SOC_ESTIMATION_STATE_FRAME_ID, data,
						 SECONDARY_HV_SOC_ESTIMATION_STATE_BYTE_SIZE);
	}
	if (timestamp - soc_cov_timestamp > 1e5) {
		soc_cov_timestamp = timestamp;
		const auto &covariance = soc.getCovariance();
		static secondary_hv_soc_estimation_covariance_converted_t hv_soc_estimation_covariance;
		hv_soc_estimation_covariance.soc = covariance(_SOC, _SOC);
		hv_soc_estimation_covariance.rc1 = covariance(_RC1, _RC1);
		hv_soc_estimation_covariance.rc2 = covariance(_RC2, _RC2);

		secondary_hv_soc_estimation_covariance_t raw;
		secondary_hv_soc_estimation_covariance_conversion_to_raw_struct(&raw, &hv_soc_estimation_covariance);
		secondary_hv_soc_estimation_covariance_pack(data, &raw, SECONDARY_HV_SOC_ESTIMATION_COVARIANCE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_HV_SOC_ESTIMATION_COVARIANCE_FRAME_ID, data,
						 SECONDARY_HV_SOC_ESTIMATION_COVARIANCE_BYTE_SIZE);
	}
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
		kill_can_thread = true;
	}
}
