#include "inc/can.h"

#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>

void can_init(can_t *can, const char *device) {
	assert(can && device);

	strncpy(can->device, device, sizeof(can->device) - 1);
	can->opened = false;
	can->bytes_exchanged = 0;
}

bool can_is_open(can_t *can) {
	assert(can);
	return can->opened;
}

const char *can_get_device(can_t *can) {
	assert(can);
	return can->device;
}

int can_open_socket(can_t *can) {
	assert(can);
	int can_socket;
	struct ifreq ifr;

	can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (can_socket < 0)
		return -1;

	// If can_socket is set to 0,
	// messages are received from all interfaces (can0, can1, vcan0)
	strcpy(ifr.ifr_name, can->device);
	ioctl(can_socket, SIOCGIFINDEX, &ifr);

	can->address.can_family = AF_CAN;
	can->address.can_ifindex = ifr.ifr_ifindex;

	if (bind(can_socket, (struct sockaddr *)&can->address, sizeof(can->address)) < 0) {
		return -2;
	}

	can->opened = true;
	can->sock = can_socket;
	return can_socket;
}

bool can_close_socket(can_t *can) {
	assert(can);
	if (can->opened && close(can->sock) < 0) {
		fprintf(stderr, "Error closing can socket: %d\n", errno);
		return false;
	}
	can->opened = false;
	return true;
}

int can_send(can_t *can, uint16_t id, uint8_t *data, uint8_t len) {
	assert(can);
	if (!can->opened || len > 8)
		return -1;

	struct can_frame frame;
	frame.can_id = id;
	frame.can_dlc = len;
	can->bytes_exchanged += len;

	memcpy(frame.data, data, len * sizeof(char));

	return write(can->sock, &frame, sizeof(frame));
}

uint64_t can_get_bytes_exchanged(can_t *can) {
	assert(can);
	return can->bytes_exchanged;
}

int can_receive(can_t *can, struct can_frame *frame) {
	assert(can);
	int bytes_read = read(can->sock, frame, sizeof(struct can_frame));
	can->bytes_exchanged += bytes_read;
	return bytes_read;
}

int can_set_filters(can_t *can, struct can_filter *filter) {
	assert(can);
	return setsockopt(can->sock, SOL_CAN_RAW, CAN_RAW_FILTER, filter, sizeof(filter));
}