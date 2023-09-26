#include "inc/can_messages.h"

#include <assert.h>

void can_messages_parse(can_message_t *message, RT_MODEL *model) {
	assert(message && model);

	if (message->socket == CAN_SOCKET_PRIMARY) {
	} else if (message->socket == CAN_SOCKET_SECONDARY) {
	}
}

void can_messages_parse_primary(can_message_t *message, RT_MODEL *model) { assert(message && model); }
void can_messages_parse_secondary(can_message_t *message, RT_MODEL *model) { assert(message && model); }
void can_messages_parse_inverters(can_message_t *message, RT_MODEL *model) { assert(message && model); }