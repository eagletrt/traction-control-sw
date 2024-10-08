#include "inc/main.hpp"
#include "exported/Regen/Regen.h"
#include "exported/Slip_Control/SLIP.h"
#include "inc/data.h"
#include <pthread.h>
extern "C" {
#include "inc/defines.h"
#include "inc/can_messages.h"
#include "inc/benchmark.h"
#include "inc/utils.h"
}
#include "external/soc/core/src/soc/soc.hpp"

#include <math.h>
#include <unistd.h>
#include <signal.h>

double power_mech = 0.0;

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
	//
	// const char *user_home = get_user_home();
	// char hv_soc_state_path[255];
	// char lv_soc_state_path[255];
	// strcpy(hv_soc_state_path, user_home);
	// strcpy(lv_soc_state_path, user_home);
	// strcat(hv_soc_state_path, "/" HV_SOC_LAST_STATE_FILENAME);
	// strcat(lv_soc_state_path, "/" LV_SOC_LAST_STATE_FILENAME);
	// Eigen::VectorXd hvSOCIinitalState(state_enum::STATE_SIZE);
	// Eigen::VectorXd lvSOCIinitalState(state_enum::STATE_SIZE);
	// if (load_soc_state(hv_soc_state_path, hvSOCIinitalState)) {
	// 	hvSOC.setState(hvSOCIinitalState);
	// }
	// if (load_soc_state(lv_soc_state_path, lvSOCIinitalState)) {
	// 	lvSOC.setState(lvSOCIinitalState);
	// }

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
	uint64_t last_can_received_check_times = get_timestamp_u();
	while (running) {
		BENCHMARK_TICK();
		BENCHMARK_TICK();
		uint64_t t_loop_start = get_timestamp_u();

		if (get_timestamp_u() - last_can_received_check_times >= 1e6 / CHECK_CAN_MESSAGES_FREQUENCY) {
			last_can_received_check_times = get_timestamp_u();
			pthread_mutex_lock(&model_mutex);
			check_received_messages(&can_received);
			pthread_mutex_unlock(&model_mutex);
		}
		can_data_t this_step_can_data;

		{
			BENCHMARK_TICK();
			pthread_mutex_lock(&model_mutex);
			this_step_can_data = gl_can_data;
			pthread_mutex_unlock(&model_mutex);

			if (USE_TLM_VELOCITY_ESTIMATION == 0) {
				velocity_estimation(&this_step_can_data);
			}
			slip_model_set_data(&this_step_can_data);
			torque_model_set_data(&this_step_can_data);
			regen_model_set_data(&this_step_can_data);

			// Slip Control
			SLIP_step(&slip_model);
			// Torque Vectoring
			TV_step(&torque_model);
			// Regen
			Regen_step(&regen_model);

			uint64_t soc_dt_us = get_timestamp_u() - last_soc_step;
			if (1e6 / (SOC_UPDATE_FREQUENCY * 2) <= soc_dt_us) {
				static int compute_hv_soc = 0;
				if (compute_hv_soc && received_hv_soc_data) {
					// HV
					hvSOC.setDT(soc_dt_us / 1e6);
					hvSOC.setTemperature(this_step_can_data.hv_mean_temp);
					hvSOC.predict(this_step_can_data.hv_total_current / 4.0);
					hvSOC.update(this_step_can_data.hv_min_cell_voltage);
					// save_soc_state(hv_soc_state_path, hvSOC.getState());
				}
				if (!compute_hv_soc && received_lv_soc_data) {
					// LV
					lvSOC.setDT(soc_dt_us / 1e6);
					lvSOC.setTemperature(this_step_can_data.lv_mean_temp);
					lvSOC.predict(this_step_can_data.lv_total_current / 4.0);
					lvSOC.update(this_step_can_data.lv_min_cell_voltage);
					// save_soc_state(lv_soc_state_path, lvSOC.getState());
				}
				last_soc_step = get_timestamp_u();
				compute_hv_soc = (compute_hv_soc + 1) % 2;
			}

			BENCHMARK_TOCK();
		}

		can_send_data(this_step_can_data);

		uint64_t loop_duration = get_timestamp_u() - t_loop_start;

		BENCHMARK_TOCK();
		if (loop_duration < LOOP_DURATION) {
			usleep(LOOP_DURATION - loop_duration);
		}
		BENCHMARK_TOCK();
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
		can_messages_parse(&message, &gl_can_data, &can_received);
		pthread_mutex_unlock(&model_mutex);
	}
	return NULL;
}

bool init_model(void) {
	torque_model.dwork = &torque_rtDW;
	TV_initialize(&torque_model);

	slip_model.dwork = &slip_rtDW;
	SLIP_initialize(&slip_model);

	Regen_initialize(&regen_model);

	return true;
}
void check_received_messages(can_received_bitset_t *bitset) {
	received_controls_data = (*bitset & RECEIVED_CONTROLS_MASK) == RECEIVED_CONTROLS_MASK;
	received_hv_soc_data = (*bitset & RECEIVED_HV_SOC_MASK) == RECEIVED_HV_SOC_MASK;
	received_lv_soc_data = (*bitset & RECEIVED_LV_SOC_MASK) == RECEIVED_LV_SOC_MASK;
	*bitset = 0;
}

void limit_torque_by_power(can_data_t *can_data, double *torque_l, double *torque_r) {
	double p_mech = (*torque_l * can_data->omega_rl + *torque_r * can_data->omega_rr) * 4.5;
	power_mech = p_mech;
	double p_max = 40000;
	if (p_mech > p_max && p_mech > 0) {
		double reduction_ratio = std::min(std::max(p_max / p_mech, 0.0), 1.0);
		*torque_l *= reduction_ratio;
		*torque_r *= reduction_ratio;
	}
}

double torque_max(can_data_t *can_data) { return MAX_TORQUE * can_data->map_power; }

void velocity_estimation(can_data_t *can_data) {
	double delta = can_data->steering_angle / STEER_CONVERSION_FACTOR;
	double v_g = WHEEL_RADIUS * (can_data->omega_fl + can_data->omega_fr) / 2.0;
	can_data->u = v_g * cos(delta);
}

void regen_model_set_data(can_data_t *can_data) {
	Regen_Driver_req = can_data->throttle;
	Regen_Inp_map_sc = 0.5f; // can_data->map_sc;
	Regen_Inp_omega_inv_rl = can_data->omega_rl;
	Regen_Inp_omega_inv_rr = can_data->omega_rr;
	Regen_pressure_f = can_data->brake_f;
	Regen_pressure_r = can_data->brake_r;
	Regen_Tm_rl = torque_max(can_data);
	Regen_Tm_rr = torque_max(can_data);
}

void slip_model_set_data(can_data_t *can_data) {
	SLIP_throttle = can_data->throttle;
	SLIP_T_max = torque_max(can_data);
	static double w_rl = 0.0;
	static double w_rr = 0.0;
	w_rl = w_rl * 0.8 + can_data->omega_rl * 0.2;
	w_rr = w_rr * 0.8 + can_data->omega_rr * 0.2;
	SLIP_in_omega_rl = w_rl;
	SLIP_in_omega_rr = w_rr;
	SLIP_u = can_data->u;
	SLIP_yaw_rate = can_data->gyro_z;

	SLIP_in_Kp = 90.0;
	SLIP_in_Ki = 2000.0;
	SLIP_in_Kd = 15.0 * std::clamp((SLIP_u - 2.0) / 5.0, 0.0, 1.0);

	SLIP_in_lambda_reference = 0.11;
	SLIP_in_minimum_torque = 40.0;

	SLIP_in_iteration_step_seconds = 1.0 / RUN_FREQUENCY;
	SLIP_in_window_seconds = 0.10;
	SLIP_in_shallow_window_seconds = 0.2;
	in_differentiation_step_seconds = 0.35;
}

void torque_model_set_data(can_data_t *can_data) {
	TV_Driver_req = can_data->throttle;
	TV_Steeringangle = (can_data->steering_angle); // / STEER_CONVERSION_FACTOR;
	TV_yaw_rate = can_data->gyro_z;
	TV_u = can_data->u;

	TV_in_Ki = TV_PID_KI;
	TV_in_Kp = TV_PID_KP;
	TV_in_KUS = TV_KUS;

	TV_in_T_max_rl = torque_max(can_data);
	TV_in_T_max_rr = torque_max(can_data);

	if (can_data->sc_state) {
		TV_in_T_max_rl_slip = SLIP_out_T_max_rl_slip;
		TV_in_T_max_rr_slip = SLIP_out_T_max_rr_slip;
	} else {
		TV_in_T_max_rl_slip = torque_max(can_data);
		TV_in_T_max_rr_slip = torque_max(can_data);
	}
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

void can_send_data(can_data_t can_data) {
	static uint8_t data[8];
	uint64_t timestamp = get_timestamp_u();
	static uint64_t out_timestamp = 0;
	static uint64_t state_timestamp = 0;
	static uint64_t debug_state_timestamp = 0;
	// static uint64_t debug_timestamp = 0;
	static uint64_t hv_soc_state_timestamp = 0;
	static uint64_t hv_soc_cov_timestamp = 0;
	static uint64_t lv_soc_state_timestamp = 0;
	static uint64_t lv_soc_cov_timestamp = 0;

	real_T torque_rl;
	real_T torque_rr;
	real_T tmax_rl;
	real_T tmax_rr;
	if (can_data.reg_state && regen_enable(can_data.brake_f, can_data.throttle, hvSOC.getState()(_SOC))) {
		torque_rl = Regen_Out_Tm_rl;
		torque_rr = Regen_Out_Tm_rr;
		tmax_rl = Regen_Tm_rl;
		tmax_rr = Regen_Tm_rr;
	} else {
		if (can_data.tv_state) {
			torque_rl = TV_out_T_motor_rl;
			torque_rr = TV_out_T_motor_rr;
			tmax_rl = TV_in_T_max_rl_slip;
			tmax_rr = TV_in_T_max_rr_slip;
		} else if (can_data.sc_state) {
			torque_rl = SLIP_out_T_motor_rl;
			torque_rr = SLIP_out_T_motor_rr;
			tmax_rl = SLIP_out_T_max_rl_slip;
			tmax_rr = SLIP_out_T_max_rr_slip;
		} else {
			torque_rl = torque_max(&can_data) * can_data.throttle;
			torque_rr = torque_max(&can_data) * can_data.throttle;
			tmax_rl = torque_max(&can_data);
			tmax_rr = torque_max(&can_data);
		}
	}
	limit_torque_by_power(&can_data, &torque_rl, &torque_rr);

	if (received_controls_data && timestamp - out_timestamp > 1e4) {
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

	if (received_controls_data && timestamp - debug_state_timestamp > 1e4) {
		debug_state_timestamp = timestamp;
		static primary_debug_signal_1_converted_t ds1;
		ds1.device_id = primary_debug_signal_1_device_id_tlm;
		ds1.field_1 = power_mech;
		static primary_debug_signal_1_t ds1_raw;
		primary_debug_signal_1_conversion_to_raw_struct(&ds1_raw, &ds1);
		primary_debug_signal_1_pack(data, &ds1_raw, PRIMARY_DEBUG_SIGNAL_3_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_DEBUG_SIGNAL_1_FRAME_ID, data, PRIMARY_DEBUG_SIGNAL_1_BYTE_SIZE);
	}

	if (received_controls_data && timestamp - state_timestamp > 1e4) {
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
		state_src.map_power = can_data.map_power;
		state_src.sc_state = (primary_control_status_sc_state)can_data.sc_state;
		state_src.tv_state = (primary_control_status_tv_state)can_data.tv_state;
		state_src.reg_state = (primary_control_status_reg_state)can_data.reg_state;
		static primary_control_status_t state_src_raw;
		primary_control_status_conversion_to_raw_struct(&state_src_raw, &state_src);
		primary_control_status_pack(data, &state_src_raw, PRIMARY_CONTROL_STATUS_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_STATUS_FRAME_ID, data, PRIMARY_CONTROL_STATUS_BYTE_SIZE);
#endif
	}
	if (received_hv_soc_data && timestamp - hv_soc_state_timestamp > 1e5) {
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
	if (received_hv_soc_data && timestamp - hv_soc_cov_timestamp > 1e5) {
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
	if (received_lv_soc_data && timestamp - lv_soc_state_timestamp > 1e5) {
		lv_soc_state_timestamp = timestamp;
		const auto &state = lvSOC.getState();
		static secondary_lv_soc_estimation_state_converted_t lv_soc_estimation_state;

		constexpr float realMinSoc = 0.1;
		float soc = (state(_SOC) - realMinSoc) / (1.0 - realMinSoc);
		lv_soc_estimation_state.soc = soc;
		lv_soc_estimation_state.rc1 = state(_RC1);
		lv_soc_estimation_state.rc2 = state(_RC2);

		secondary_lv_soc_estimation_state_t raw;
		secondary_lv_soc_estimation_state_conversion_to_raw_struct(&raw, &lv_soc_estimation_state);
		secondary_lv_soc_estimation_state_pack(data, &raw, SECONDARY_LV_SOC_ESTIMATION_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_LV_SOC_ESTIMATION_STATE_FRAME_ID, data,
						 SECONDARY_LV_SOC_ESTIMATION_STATE_BYTE_SIZE);
	}
	if (received_lv_soc_data && timestamp - lv_soc_cov_timestamp > 1e5) {
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

bool load_soc_state(const char *path, Eigen::VectorXd &state) {
	FILE *ptr = fopen(path, "r");
	if (!ptr) {
		state(state_enum::_SOC) = 0;
		state(state_enum::_RC1) = 0;
		state(state_enum::_RC2) = 0;
		return false;
	}

	int ret = fscanf(ptr, "%lf %lf %lf", &state(state_enum::_SOC), &state(state_enum::_RC1), &state(state_enum::_RC2));

	fclose(ptr);
	if (ret > 0) {
		return true;
	}
	return false;
}
bool save_soc_state(const char *path, const Eigen::VectorXd &state) {
	FILE *ptr = fopen(path, "w");
	if (!ptr) {
		return false;
	}
	fprintf(ptr, "%f %f %f", state(state_enum::_SOC), state(state_enum::_RC1), state(state_enum::_RC2));
	fclose(ptr);
	return true;
}

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
		kill_can_thread = true;
	}
}
