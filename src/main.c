#include "inc/main.h"
#include "inc/defines.h"

#include <unistd.h>

#define RUN_FREQUENCY 1000 // Hz

int main(void) {

	can_messages_init();
	can_init(&can[CAN_SOCKET_PRIMARY], "vcan0");
	can_init(&can[CAN_SOCKET_SECONDARY], "vcan1");

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

	while (true) {
		pthread_mutex_lock(&model_mutex);
		ve_model_set_data(&ve_data);
		Velocity_Estimation_step(&ve_model);
		all_model_set_data(&ve_data, &all_data);
		All0_step(&all_model);
		pthread_mutex_unlock(&model_mutex);

		fprintf(stdout, "ve: %f\n", rtu_bar_Velocity_Estimation);

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
		can_messages_parse(&message, &ve_data, &all_data);
		pthread_mutex_unlock(&model_mutex);
	}
}

bool init_model(void) {
	// Velocity Estimation
	ve_model.dwork = &ve_rtDW;
	Velocity_Estimation_initialize(&ve_model);

	all_model.dwork = &all_rtDW;
	All0_initialize(&all_model);

	return true;
}

void ve_model_set_data(ve_data_t *ve_d) {
	// Velocity Estimation Data
	rtaxG_Velocity_Estimation = ve_d->rtaxG_Velocity_Estimation;

	rtTmax_rl_Velocity_Estimation = ve_d->rtTmax_rl_Velocity_Estimation;
	rtTmax_rr_Velocity_Estimation = ve_d->rtTmax_rr_Velocity_Estimation;

	rtmap_motor_Velocity_Estimation = ve_d->rtmap_motor_Velocity_Estimation;

	rtomega_fl_Velocity_Estimation = ve_d->rtomega_fl_Velocity_Estimation;
	rtomega_fr_Velocity_Estimation = ve_d->rtomega_fr_Velocity_Estimation;
	rtomega_rl_Velocity_Estimation = ve_d->rtomega_rl_Velocity_Estimation;
	rtomega_rr_Velocity_Estimation = ve_d->rtomega_rr_Velocity_Estimation;

	rtu_bar_Velocity_Estimation = ve_d->rtu_bar_Velocity_Estimation;
}

void all_model_set_data(ve_data_t *ve_d, all_data_t *all_d) {
	// All0 Data
	rtbrake_All0 = all_d->rtbrake_All0;
	rtDriver_req_All0 = all_d->rtDriver_req_All0;
	rtSteeringangle_All0 = all_d->rtSteeringangle_All0;

	rtTm_rl_All0 = all_d->rtTm_rl_All0;
	rtTm_rl_a_All0 = all_d->rtTm_rl_a_All0;
	rtTm_rr_All0 = all_d->rtTm_rr_All0;
	rtTm_rr_m_All0 = all_d->rtTm_rr_m_All0;

	rtmap_sc_All0 = all_d->rtmap_sc_All0;
	rtmap_tv_All0 = all_d->rtmap_tv_All0;

	rtyaw_rate_All0 = all_d->rtyaw_rate_All0;

	rtu_bar_All0 = ve_d->rtu_bar_Velocity_Estimation;
	rtomega_rl_All0 = ve_d->rtomega_rl_Velocity_Estimation;
	rtomega_rr_All0 = ve_d->rtomega_rr_Velocity_Estimation;
}