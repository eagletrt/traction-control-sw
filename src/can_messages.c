#include "inc/can_messages.h"

#define CANLIB_DEVICE_IMPLEMENTATION
#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/inverters/inverters_network.h"

#include <assert.h>

static inline void can_messages_parse_primary(can_message_t *message, ve_data_t *ve_data);
static inline void can_messages_parse_secondary(can_message_t *message, ve_data_t *ve_data);
static inline void can_messages_parse_inverters(can_message_t *message, ve_data_t *ve_data);

uint8_t raw_mem[512];
uint8_t converted_mem[512];
device_t can_devices;

void can_messages_init() {
	device_init(&can_devices);
	device_set_address(&can_devices, &raw_mem, sizeof(raw_mem), &converted_mem, sizeof(converted_mem));
}

void can_messages_parse(can_message_t *message, ve_data_t *ve_data) {
	assert(message && ve_data);

	if (message->socket == CAN_SOCKET_PRIMARY) {
		if (primary_id_is_message(message->frame.can_id)) {
			can_messages_parse_primary(message, ve_data);
		} else if (inverters_id_is_message(message->frame.can_id)) {
			can_messages_parse_inverters(message, ve_data);
		}
	} else if (message->socket == CAN_SOCKET_SECONDARY) {
		if (secondary_id_is_message(message->frame.can_id)) {
			can_messages_parse_secondary(message, ve_data);
		}
	}
}

static inline void can_messages_parse_primary(can_message_t *message, ve_data_t *ve_data) {
	assert(message && ve_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case PRIMARY_SPEED_FRAME_ID: {
		primary_speed_converted_t *speed = (primary_speed_converted_t *)can_devices.message;
		ve_data->rtomega_fl = speed->encoder_l;
		ve_data->rtomega_fr = speed->encoder_r;
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_secondary(can_message_t *message, ve_data_t *ve_data) {
	assert(message && ve_data);

	secondary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SECONDARY_PEDALS_OUTPUT_FRAME_ID: {
		secondary_pedals_output_converted_t *pedals_output = (secondary_pedals_output_converted_t *)can_devices.message;

		UNUSED(pedals_output);
		break;
	}
	case SECONDARY_IMU_ACCELERATION_FRAME_ID: {
		secondary_imu_acceleration_converted_t *acceleration =
				(secondary_imu_acceleration_converted_t *)can_devices.message;

		UNUSED(acceleration);
		break;
	}
	case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {
		secondary_imu_angular_rate_converted_t *angular_rate =
				(secondary_imu_angular_rate_converted_t *)can_devices.message;

		UNUSED(angular_rate);
		break;
	}
	case SECONDARY_STEERING_ANGLE_FRAME_ID: {
		secondary_steering_angle_converted_t *steering_angle = (secondary_steering_angle_converted_t *)can_devices.message;

		UNUSED(steering_angle);
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_inverters(can_message_t *message, ve_data_t *ve_data) {
	assert(message && ve_data);

	inverters_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case INVERTERS_INV_L_RCV_FRAME_ID: {
		inverters_inv_l_rcv_converted_t *rcv = (inverters_inv_l_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_L_RCV_RCV_MUX_ID_27_IQ_ACTUAL_CHOICE:

			break;
		default:
			break;
		}
		break;
	}
	case INVERTERS_INV_R_RCV_FRAME_ID: {
		inverters_inv_r_rcv_converted_t *rcv = (inverters_inv_r_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_R_RCV_RCV_MUX_ID_27_IQ_ACTUAL_CHOICE:

			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}