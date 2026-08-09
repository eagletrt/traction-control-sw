#include "can-networks.h"
#include "can-primary-api.h"
#include "inc/data.h"
#include "inc/defines.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "inc/can_messages.h"
#include "inc/benchmark.h"

#include <assert.h>

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received);
void can_messages_init() { get_timestamp_u(); }

void can_messages_parse(can_message_t *message, can_data_t *can_data, can_received_bitset_t *can_received) {
	assert(message && can_data);

	if (message->socket == CAN_SOCKET_PRIMARY) {
		can_messages_parse_primary(message, can_data, can_received);
	}
}

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received) {
	assert(message && can_data);
	union CanNetworkMessage networkMessage;
	int msgSize = can_primary_api_deserialize_from_id((enum CanPrimaryMessageFrameId)message->frame.can_id,
																										message->frame.data, &networkMessage.can_primary_message);
  (void) msgSize;
	switch (message->frame.can_id) {

	case CAN_PRIMARY_MESSAGE_FRAME_ID_TSACMAINBOARDCURRENTINFO: {
		can_data->hv_total_current = networkMessage.can_primary_message.tsacmainboardcurrentinfo.current;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case CAN_PRIMARY_MESSAGE_FRAME_ID_TSACMAINBOARDVOLTAGEINFO: {
		can_data->hv_min_cell_voltage = networkMessage.can_primary_message.tsacmainboardvoltageinfo.min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case CAN_PRIMARY_MESSAGE_FRAME_ID_TSACMAINBOARDTEMPERATUREINFO: {
		can_data->hv_mean_temp = networkMessage.can_primary_message.tsacmainboardtemperatureinfo.min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case CAN_PRIMARY_MESSAGE_FRAME_ID_LVACVOLTAGEINFO: {
		can_data->lv_min_cell_voltage = networkMessage.can_primary_message.lvacvoltageinfo.min;
		can_data->lv_total_current = networkMessage.can_primary_message.lvacvoltageinfo.current;
		CAN_RECEIVED_SET(*can_received, CAN_REC_LV)
		break;
	}
	case CAN_PRIMARY_MESSAGE_FRAME_ID_LVACTEMPERATUREINFO: {
		can_data->lv_mean_temp = networkMessage.can_primary_message.lvactemperatureinfo.min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_LV)
		break;
	}
	default:
		break;
	}
}
