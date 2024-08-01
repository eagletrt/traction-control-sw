#include "inc/main.hpp"
extern "C" {
#include "inc/defines.h"
#include "inc/can_messages.h"
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

	can_init(&can[CAN_SOCKET_PRIMARY], "can0");
	if (can_open_socket(&can[CAN_SOCKET_PRIMARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_PRIMARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_PRIMARY], NULL, can_thread, &can[CAN_SOCKET_PRIMARY]);
	can_init(&can[CAN_SOCKET_SECONDARY], "can1");
	if (can_open_socket(&can[CAN_SOCKET_SECONDARY]) < 0) {
		eprintf("Error opening socket %s\n", can[CAN_SOCKET_SECONDARY].device);
		return EXIT_FAILURE;
	}
	pthread_create(&can_threads[CAN_SOCKET_SECONDARY], NULL, can_thread, &can[CAN_SOCKET_SECONDARY]);

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
			if (USE_TLM_VELOCITY_ESTIMATION == 0) {
				velocity_estimation(&can_data);
			}
			slip_model_set_data(&can_data);
			torque_model_set_data(&can_data);
			regen_model_set_data(&can_data);
			pthread_mutex_unlock(&model_mutex);

			// Slip Control
			SLIP_step(&slip_model);
			// Torque Vectoring
			TV_step(&torque_model);
#if REGEN_ENABLE == 1
			Regen_step(&regen_model);
#endif

			uint64_t soc_dt_us = get_timestamp_u() - last_soc_step;
			if (1e6 / SOC_UPDATE_FREQUENCY <= soc_dt_us) {
				// HV
				hvSOC.setDT(soc_dt_us / 1e6);
				hvSOC.setTemperature(can_data.hv_mean_temp);
				hvSOC.predict(can_data.hv_total_current / 4.0);
				hvSOC.update(can_data.hv_min_cell_voltage);
				// LV
				lvSOC.setDT(soc_dt_us / 1e6);
				lvSOC.setTemperature(can_data.lv_mean_temp);
				lvSOC.predict(can_data.lv_total_current / 4.0);
				lvSOC.update(can_data.lv_min_cell_voltage);

				last_soc_step = get_timestamp_u();
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

void velocity_estimation(can_data_t *can_data) {
	double delta = can_data->steering_angle / STEER_CONVERSION_FACTOR;
	double v_g = WHEEL_RADIUS * (can_data->omega_fl + can_data->omega_fr) / 2.0;
	can_data->u = v_g * cos(delta);
}

void regen_model_set_data(can_data_t *can_data) {
	Regen_Driver_req = can_data->throttle;
	Regen_Inp_map_sc = can_data->map_sc;
	Regen_Inp_omega_inv_rl = can_data->omega_rl;
	Regen_Inp_omega_inv_rr = can_data->omega_rr;
	Regen_pressure_f = can_data->brake_f;
	Regen_pressure_r = can_data->brake_r;
	Regen_Tm_rl = torque_max(can_data) * can_data->map_pw;
	Regen_Tm_rr = torque_max(can_data) * can_data->map_pw;
}

void slip_model_set_data(can_data_t *can_data) {
	SLIP_Driver_req = can_data->throttle;
	SLIP_Tmax_rl = torque_max(can_data) * can_data->map_pw;
	SLIP_Tmax_rr = torque_max(can_data) * can_data->map_pw;
	SLIP_map_sc = can_data->map_sc;
	SLIP_omega_rl = can_data->omega_rl;
	SLIP_omega_rr = can_data->omega_rr;
	velocity_estimation(can_data);
	SLIP_u = can_data->u;
	SLIP_yaw_rate = can_data->gyro_z;

	SLIP_Inp_Ki = 15000.0;
	SLIP_Inp_Kp = 0.0;
	SLIP_Inp_LambdaRef = 0.6;
	SLIP_Inp_UppSatLim = 70.0;
	SLIP_Inp_IntegralOffset = 35.0;
}

void torque_model_set_data(can_data_t *can_data) {
	// rtbrake_Torque = can_data->brake;
	// rtmap_sc_Torque = can_data->map_sc;

	TV_map_tv = can_data->map_tv;
	TV_Driver_req = can_data->throttle;
	TV_Steeringangle = can_data->steering_angle;
	TV_yaw_rate = can_data->gyro_z;
	TV_u_bar = can_data->u;

	TV_Inp_Ki = TV_PID_KI;
	TV_Inp_Kp = TV_PID_KP;
	TV_Inp_Kus = TV_KUF;

	TV_Tm_rl = torque_max(can_data);
	TV_Tm_rr = torque_max(can_data);

	TV_lambda_rr = SLIP_Out_Tmax_rl_slip;
	TV_lambda_rr_n = SLIP_Out_Tmax_rr_slip;
}

bool regen_enable(double brake_front, double throttle, double hvSOC) {
	static bool prev_brake_status = false;
	static bool prev_throttle_status = false;
	static bool prev_soc_status = false;
	if (brake_front > (REGEN_BRAKE_FRONT_ON_THRESHOLD + REGEN_BRAKE_HYSTERESIS)) {
		prev_brake_status = true;
	} else if (brake_front < (REGEN_BRAKE_FRONT_ON_THRESHOLD - REGEN_BRAKE_HYSTERESIS)) {
		prev_brake_status = false;
	}
	if (throttle < (REGEN_THROTTLE_ON_THRESHOLD - REGEN_THROTTLE_HYSTERESYS)) {
		prev_throttle_status = true;
	} else if (throttle > (REGEN_THROTTLE_ON_THRESHOLD + REGEN_THROTTLE_HYSTERESYS)) {
		prev_throttle_status = false;
	}
	if (hvSOC < (REGEN_SOC_ON_THRESOLD - REGEN_SOC_HYSTERESYS)) {
		prev_soc_status = true;
	} else if (hvSOC > (REGEN_SOC_ON_THRESOLD + REGEN_SOC_HYSTERESYS)) {
		prev_soc_status = false;
	}
	return prev_brake_status && prev_throttle_status && prev_soc_status;
}

void can_send_data() {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0;
	static uint64_t state_timestamp = 0;
	// static uint64_t debug_timestamp = 0;
	static uint64_t hv_soc_state_timestamp = 0;
	static uint64_t hv_soc_cov_timestamp = 0;
	static uint64_t lv_soc_state_timestamp = 0;
	static uint64_t lv_soc_cov_timestamp = 0;

	real_T map_sc = SLIP_map_sc;
	real_T map_tv = TV_map_tv;

	real_T torque_rl;
	real_T torque_rr;
	real_T tmax_rl;
	real_T tmax_rr;
	if (REGEN_ENABLE && regen_enable(can_data.brake_f, can_data.throttle, hvSOC.getState()(_SOC))) {
		torque_rl = Regen_Out_Tm_rl;
		torque_rr = Regen_Out_Tm_rr;
		tmax_rl = Regen_Tm_rl;
		tmax_rr = Regen_Tm_rr;
	} else {
		torque_rl = TV_Out_Tm_rl;
		torque_rr = TV_Out_Tm_rr;
		tmax_rl = TV_Tm_rl;
		tmax_rr = TV_Tm_rr;
	}

	if (timestamp - out_timestamp > 1e4) {
		out_timestamp = timestamp;

#if 1 == SIMULATOR
		static simulator_control_output_converted_t out_src;
		out_src.estimated_velocity = u_bar;
		out_src.torque_max_l = tmax_rl;
		out_src.torque_max_r = tmax_rr;
		out_src.torque_l = torque_rl;
		out_src.torque_r = torque_rr;
		static simulator_control_output_t out_src_raw;
		simulator_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		simulator_control_output_pack(data, &out_src_raw, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], SIMULATOR_CONTROL_OUTPUT_FRAME_ID, data, SIMULATOR_CONTROL_OUTPUT_BYTE_SIZE);
#else
		static primary_control_output_converted_t out_src;
		out_src.estimated_velocity = can_data.u;
		out_src.torque_max_l = tmax_rl;
		out_src.torque_max_r = tmax_rr;
		out_src.torque_l = torque_rl;
		out_src.torque_r = torque_rr;
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
	if (timestamp - hv_soc_state_timestamp > 1e5) {
		hv_soc_state_timestamp = timestamp;
		const auto &state = hvSOC.getState();
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
	if (timestamp - hv_soc_cov_timestamp > 1e5) {
		hv_soc_cov_timestamp = timestamp;
		const auto &covariance = hvSOC.getCovariance();
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
	if (timestamp - lv_soc_state_timestamp > 1e5) {
		lv_soc_state_timestamp = timestamp;
		const auto &state = lvSOC.getState();
		static secondary_lv_soc_estimation_state_converted_t lv_soc_estimation_state;
		lv_soc_estimation_state.soc = state(_SOC);
		lv_soc_estimation_state.rc1 = state(_RC1);
		lv_soc_estimation_state.rc2 = state(_RC2);

		secondary_lv_soc_estimation_state_t raw;
		secondary_lv_soc_estimation_state_conversion_to_raw_struct(&raw, &lv_soc_estimation_state);
		secondary_lv_soc_estimation_state_pack(data, &raw, SECONDARY_LV_SOC_ESTIMATION_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_LV_SOC_ESTIMATION_STATE_FRAME_ID, data,
						 SECONDARY_LV_SOC_ESTIMATION_STATE_BYTE_SIZE);
	}
	if (timestamp - lv_soc_cov_timestamp > 1e5) {
		lv_soc_cov_timestamp = timestamp;
		const auto &covariance = lvSOC.getCovariance();
		static secondary_lv_soc_estimation_covariance_converted_t lv_soc_estimation_covariance;
		lv_soc_estimation_covariance.soc = covariance(_SOC, _SOC);
		lv_soc_estimation_covariance.rc1 = covariance(_RC1, _RC1);
		lv_soc_estimation_covariance.rc2 = covariance(_RC2, _RC2);

		secondary_lv_soc_estimation_covariance_t raw;
		secondary_lv_soc_estimation_covariance_conversion_to_raw_struct(&raw, &lv_soc_estimation_covariance);
		secondary_lv_soc_estimation_covariance_pack(data, &raw, SECONDARY_LV_SOC_ESTIMATION_COVARIANCE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_LV_SOC_ESTIMATION_COVARIANCE_FRAME_ID, data,
						 SECONDARY_LV_SOC_ESTIMATION_COVARIANCE_BYTE_SIZE);
	}
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
		kill_can_thread = true;
	}
}
