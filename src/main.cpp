#include "inc/main.hpp"
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

			uint64_t soc_dt_us = get_timestamp_u() - last_soc_step;
			if (1e6 / (SOC_UPDATE_FREQUENCY * 2) <= soc_dt_us) {
				static int compute_hv_soc = 0;
				if (compute_hv_soc && received_hv_soc_data) {
					// HV
					hvSOC.setDT(soc_dt_us / 1e6);
					hvSOC.setTemperature(this_step_can_data.hv_mean_temp);
					hvSOC.predict(this_step_can_data.hv_total_current / 4.0);
					hvSOC.update(this_step_can_data.hv_min_cell_voltage);
				}
				if (!compute_hv_soc && received_lv_soc_data) {
					// LV
					lvSOC.setDT(soc_dt_us / 1e6);
					lvSOC.setTemperature(this_step_can_data.lv_mean_temp);
					lvSOC.predict(this_step_can_data.lv_total_current / 4.0);
					lvSOC.update(this_step_can_data.lv_min_cell_voltage);
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
	can_socket_t socket = CAN_SOCKET_PRIMARY;
	can_message_t message;
	struct can_frame frame;

	printf("Start CAN primary reader\n");

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

void check_received_messages(can_received_bitset_t *bitset) {
	received_hv_soc_data = (*bitset & RECEIVED_HV_SOC_MASK) == RECEIVED_HV_SOC_MASK;
	received_lv_soc_data = (*bitset & RECEIVED_LV_SOC_MASK) == RECEIVED_LV_SOC_MASK;
	*bitset = 0;
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

// sig handler
void sig_handler(int signo) {
	if (signo == SIGINT) {
		running = false;
		kill_can_thread = true;
	}
}
