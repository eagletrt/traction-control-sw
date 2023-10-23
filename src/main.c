#include "inc/main.h"
#include "inc/defines.h"

#include <math.h>
#include <unistd.h>

#define RUN_FREQUENCY 1000 // Hz

int main(void) {

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
	while (true) {
		pthread_mutex_lock(&model_mutex);

		ve_model_set_data(&ve_data);
		Velocity_Estimation_step(&ve_model);
		all_model_set_data(&all_data);
		All0_step(&all_model);
		slip_model_set_data(&slip_data);
		SlipV2_step(&slip_model);

		pthread_mutex_unlock(&model_mutex);

		fprintf(stdout, "\rve: %f", rtu_bar_Velocity_Estimation);

		can_send_data();

		usleep(1.0 / RUN_FREQUENCY * 1e6);
	}

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
		can_messages_parse(&message, &ve_data, &all_data, &slip_data);
		pthread_mutex_unlock(&model_mutex);
	}
}

bool init_model(void) {
	// Velocity Estimation
	ve_model.dwork = &ve_rtDW;
	Velocity_Estimation_initialize(&ve_model);

	all_model.dwork = &all_rtDW;
	All0_initialize(&all_model);

	slip_model.dwork = &slip_rtDW;
	SlipV2_initialize(&slip_model);

	return true;
}

void ve_model_set_data(ve_data_t *ve_d) {
	// Velocity Estimation Data
	rtaxG_Velocity_Estimation = ve_d->rtaxG_Velocity_Estimation * 9.81;

	rtTmax_rl_Velocity_Estimation = ve_d->rtTmax_rl_Velocity_Estimation;
	rtTmax_rr_Velocity_Estimation = ve_d->rtTmax_rr_Velocity_Estimation;

	rtmap_motor_Velocity_Estimation = ve_d->rtmap_motor_Velocity_Estimation;

	rtomega_fl_Velocity_Estimation = ve_d->rtomega_fl_Velocity_Estimation;
	rtomega_fr_Velocity_Estimation = ve_d->rtomega_fr_Velocity_Estimation;
	rtomega_rl_Velocity_Estimation = ve_d->rtomega_rl_Velocity_Estimation;
	rtomega_rr_Velocity_Estimation = ve_d->rtomega_rr_Velocity_Estimation;

	rtu_bar_Velocity_Estimation = ve_d->rtu_bar_Velocity_Estimation;
}

void all_model_set_data(all_data_t *all_d) {
	// All0 Data
	rtbrake_All0 = all_d->rtbrake_All0 / 100.0;
	rtDriver_req_All0 = all_d->rtDriver_req_All0 / 100.0;
	rtSteeringangle_All0 = all_d->rtSteeringangle_All0 * (M_PI / 180.0);

	rtmap_tv_All0 = all_d->rtmap_tv_All0;
	if(!equal_d(rtmap_tv_All0, 0.0)) {
		rtmap_sc_All0 = 0.0;
	} else {
		rtmap_sc_All0 = all_d->rtmap_sc_All0;
	}

	rtyaw_rate_All0 = all_d->rtyaw_rate_All0 * (M_PI / 180.0);

	rtTm_rl_All0 = rtTmax_rl_Velocity_Estimation;
	rtTm_rr_All0 = rtTmax_rr_Velocity_Estimation;

	rtu_bar_All0 = rtu_bar_Velocity_Estimation;
	rtomega_rl_All0 = rtomega_rl_Velocity_Estimation;
	rtomega_rr_All0 = rtomega_rr_Velocity_Estimation;
}

void slip_model_set_data(slip_data_t *slip_d) {
	// SlipV2 Data
	rtbrake_SlipV2 = slip_d->rtbrake_SlipV2 / 100.0;
	rtDriver_req_SlipV2 = slip_d->rtDriver_req_SlipV2 / 100.0;
	rtSteeringangle_SlipV2 = slip_d->rtSteeringangle_SlipV2 * (M_PI / 180.0);

	if(!equal_d(slip_d->rtmap_tv_SlipV2, 0.0)) {
		rtmap_sc_SlipV2 = 0.0;
	} else {
		rtmap_sc_SlipV2 = slip_d->rtmap_sc_SlipV2;
	}
	rtmap_tv_SlipV2 = 0.0;

	rtyaw_rate_SlipV2 = slip_d->rtyaw_rate_SlipV2 * (M_PI / 180.0);

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
		if(!equal_d(rtmap_tv_All0, 0.0)) {
			out_src.tmax_l = rtTm_rl_All0;
			out_src.tmax_r = rtTm_rr_All0;
			out_src.torque_l = rtTm_rl_a_All0;
			out_src.torque_r = rtTm_rr_m_All0;
		} else {
			out_src.tmax_l = rtTm_rl_SlipV2;
			out_src.tmax_r = rtTm_rr_SlipV2;
			out_src.torque_l = rtTm_rl_a_SlipV2;
			out_src.torque_r = rtTm_rr_m_SlipV2;
		}

		primary_control_output_conversion_to_raw_struct(&out_src_raw, &out_src);
		primary_control_output_pack(data, &out_src_raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_PRIMARY], PRIMARY_CONTROL_OUTPUT_FRAME_ID, data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);
	}

	if (timestamp - SECONDARY_INTERVAL_CONTROL_STATE * 1e3 > state_timestamp) {
		state_timestamp = timestamp;

		static secondary_control_state_t state_src_raw;
		static secondary_control_state_converted_t state_src;

		state_src.map_pw = rtmap_motor_Velocity_Estimation;
		state_src.map_sc = rtmap_sc_All0;
		state_src.map_tv = rtmap_tv_All0;

		secondary_control_state_conversion_to_raw_struct(&state_src_raw, &state_src);
		secondary_control_state_pack(data, &state_src_raw, SECONDARY_CONTROL_STATE_BYTE_SIZE);
		can_send(&can[CAN_SOCKET_SECONDARY], SECONDARY_CONTROL_STATE_FRAME_ID, data, SECONDARY_CONTROL_STATE_BYTE_SIZE);
	}
}