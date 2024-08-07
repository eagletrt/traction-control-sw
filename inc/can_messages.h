#ifndef __CAN_MESSAGES_H__
#define __CAN_MESSAGES_H__

#include "can.h"
#include "data.h"
#include "defines.h"

typedef enum {
	NETWORK_PRIMARY,
	NETWORK_SECONDARY,
	NETWORK_INVERTERS,

	NETWORK_COUNT
} can_network_t;

typedef enum {
	CAN_SOCKET_PRIMARY,
	CAN_SOCKET_SECONDARY,

	CAN_SOCKET_COUNT
} can_socket_t;

typedef struct {
	can_t *can;
	uint64_t timestamp;
	can_socket_t socket;
	can_network_t network;
	struct can_frame frame;
} can_message_t;

void can_messages_init();
void can_messages_parse(can_message_t *message, can_data_t *can_data, can_received_bitset_t *can_received);

#endif // __CAN_MESSAGES_H__
