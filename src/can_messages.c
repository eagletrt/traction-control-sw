#include "inc/data.h"
#include "inc/defines.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "inc/can_messages.h"
#include "inc/benchmark.h"

#include "external/can/lib/primary/primary_network.h"
#include "external/can/lib/canlib_device.h"

#include <assert.h>

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received);
uint8_t raw_mem[512];
uint8_t converted_mem[512];
device_t can_devices;

void can_messages_init() {
	get_timestamp_u();
	device_init(&can_devices);
	device_set_address(&can_devices, &raw_mem, sizeof(raw_mem), &converted_mem, sizeof(converted_mem));
}

void can_messages_parse(can_message_t *message, can_data_t *can_data, can_received_bitset_t *can_received) {
	assert(message && can_data);

	if (message->socket == CAN_SOCKET_PRIMARY) {
			can_messages_parse_primary(message, can_data, can_received);
	}
}

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received) {
	assert(message && can_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {

	case PRIMARY_HV_CURRENT_FRAME_ID: {
		primary_hv_current_converted_t *hv_current = (primary_hv_current_converted_t *)can_devices.message;
		can_data->hv_total_current = hv_current->current;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case PRIMARY_HV_CELLS_VOLTAGE_STATS_FRAME_ID: {
		primary_hv_cells_voltage_stats_converted_t *hv_cells_volts_stats =
				(primary_hv_cells_voltage_stats_converted_t *)can_devices.message;
		can_data->hv_min_cell_voltage = hv_cells_volts_stats->min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case PRIMARY_HV_CELLS_TEMP_STATS_FRAME_ID: {
		primary_hv_cells_temp_stats_converted_t *hv_cells_temps_stats =
				(primary_hv_cells_temp_stats_converted_t *)can_devices.message;
		can_data->hv_mean_temp = hv_cells_temps_stats->min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_HV)
		break;
	}
	case PRIMARY_LV_CURRENT_BATTERY_FRAME_ID: {
		primary_lv_current_battery_converted_t *lv_current = (primary_lv_current_battery_converted_t *)can_devices.message;
		can_data->lv_total_current = lv_current->lv_current;
		CAN_RECEIVED_SET(*can_received, CAN_REC_LV)
		break;
	}
	case PRIMARY_LV_CELLS_VOLTAGE_STATS_FRAME_ID: {
		primary_lv_cells_voltage_stats_converted_t *lv_cells_volts_stats =
				(primary_lv_cells_voltage_stats_converted_t *)can_devices.message;
		can_data->lv_min_cell_voltage = lv_cells_volts_stats->min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_LV)
		break;
	}
	case PRIMARY_LV_CELLS_TEMP_STATS_FRAME_ID: {
		primary_lv_cells_temp_stats_converted_t *lv_cells_temps_stats =
				(primary_lv_cells_temp_stats_converted_t *)can_devices.message;
		can_data->lv_mean_temp = lv_cells_temps_stats->min;
		CAN_RECEIVED_SET(*can_received, CAN_REC_LV)
		break;
	}
	default:
		break;
	}
}
