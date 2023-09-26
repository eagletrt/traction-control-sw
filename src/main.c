#include "inc/main.h"
#include "inc/defines.h"

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

	while (true) {
		pthread_mutex_lock(&model_mutex);
		model_set_data(&ve_data);
		Velocity_Estimation_step(&model);
		pthread_mutex_unlock(&model_mutex);

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
		can_messages_parse(&message, &ve_data);
		pthread_mutex_unlock(&model_mutex);
	}
}

bool init_model(void) {
	// Velocity Estimation
	model.dwork = &rtDW;
	Velocity_Estimation_initialize(&model);

	return true;
}

void model_set_data(ve_data_t *data) {
	// Velocity Estimation Data
	rtTmax_rl_Velocity_Estimation = data->rtTmax_rl;
	rtTmax_rr_Velocity_Estimation = data->rtTmax_rr;
	rtaxG_Velocity_Estimation = data->rtaxG;
	rtmap_motor_Velocity_Estimation = data->rtmap_motor;
	rtomega_fl_Velocity_Estimation = data->rtomega_fl;
	rtomega_fr_Velocity_Estimation = data->rtomega_fr;
	rtomega_rl_Velocity_Estimation = data->rtomega_rl;
	rtomega_rr_Velocity_Estimation = data->rtomega_rr;
	rtu_bar_Velocity_Estimation = data->rtu_bar;
}