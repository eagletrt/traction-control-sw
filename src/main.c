#include "inc/main.h"
#include "inc/defines.h"

#include <unistd.h>

#define RUN_FREQUENCY 1000 // Hz

int main(void) {

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

	while (true) {
		pthread_mutex_lock(&model_mutex);
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
		// Add message to queue
		pthread_mutex_lock(&model_mutex);
		can_messages_parse(&message, &model);
		pthread_mutex_unlock(&model_mutex);
	}
}

bool init_model(void) {
	// Velocity Estimation
	model.dwork = &rtDW;
	Velocity_Estimation_initialize(&model);

	return true;
}