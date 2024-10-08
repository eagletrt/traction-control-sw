#include "inc/data.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "inc/can_messages.h"
#include "inc/benchmark.h"

#include "external/can/lib/primary/primary_network.h"
#include "external/can/lib/secondary/secondary_network.h"
#include "external/can/lib/inverters/inverters_network.h"
#include "external/can/lib/simulator/simulator_network.h"
#include "external/can/lib/canlib_device.h"

#include <assert.h>

static inline double inverter_convert_speed(double val);
static inline double convert_gyro(double val);
static inline double convert_accel(double val);
static inline double convert_brake(double val);
static inline double convert_throttle(double val);
static inline double convert_steering_angle(double val);

#if SIMULATOR == 1
static inline void can_messages_parse_simulator(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received);
#else
static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received);
static inline void can_messages_parse_secondary(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received);
static inline void can_messages_parse_inverters(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received);
#endif
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

	// #if SIMULATOR == 1
	// 	if (message->socket == CAN_SOCKET_PRIMARY) {
	// 		if (simulator_id_is_message(message->frame.can_id)) {
	// 			can_messages_parse_simulator(message, can_data, can_received);
	// 		}
	// 	}
	// #else
	if (message->socket == CAN_SOCKET_PRIMARY) {
		if (inverters_id_is_message(message->frame.can_id)) {
			can_messages_parse_inverters(message, can_data, can_received);
		} else if (primary_id_is_message(message->frame.can_id)) {
			can_messages_parse_primary(message, can_data, can_received);
		}
	} else if (message->socket == CAN_SOCKET_SECONDARY) {
		if (secondary_id_is_message(message->frame.can_id)) {
			can_messages_parse_secondary(message, can_data, can_received);
		}
	}
	// #endif // SIMULATOR
}

#if SIMULATOR == 1
static inline void can_messages_parse_simulator(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received) {
	assert(message && can_data);

	simulator_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SIMULATOR_IMU_ANGULAR_RATE_FRAME_ID: {
		simulator_imu_angular_rate_converted_t *angular_rate =
				(simulator_imu_angular_rate_converted_t *)can_devices.message;
		can_data->gyro_x = convert_gyro(angular_rate->x);
		can_data->gyro_y = convert_gyro(angular_rate->y);
		can_data->gyro_z = convert_gyro(angular_rate->z);
		break;
	}
	case SIMULATOR_IMU_ACCELERATION_FRAME_ID: {
		simulator_imu_acceleration_converted_t *acceleration =
				(simulator_imu_acceleration_converted_t *)can_devices.message;
		can_data->accel_x = convert_accel(acceleration->x);
		can_data->accel_y = convert_accel(acceleration->y);
		can_data->accel_z = convert_accel(acceleration->z);
		break;
	}
	case SIMULATOR_PEDAL_THROTTLE_FRAME_ID: {
		simulator_pedal_throttle_converted_t *pedals = (simulator_pedal_throttle_converted_t *)can_devices.message;
		can_data->throttle = convert_throttle(pedals->throttle);
		break;
	}
	case SIMULATOR_PEDAL_BRAKES_PRESSURE_FRAME_ID: {
		simulator_pedal_brakes_pressure_converted_t *brakes =
				(simulator_pedal_brakes_pressure_converted_t *)can_devices.message;
		can_data->brake_f = convert_brake(brakes->front);
		can_data->brake_r = convert_brake(brakes->rear);
	}
	case SIMULATOR_STEER_ANGLE_FRAME_ID: {
		simulator_steer_angle_converted_t *steer_angle = (simulator_steer_angle_converted_t *)can_devices.message;
		can_data->steering_angle = convert_steering_angle(steer_angle->angle);
		break;
	}
	case SIMULATOR_SPEED_FRAME_ID: {
		simulator_speed_converted_t *speed = (simulator_speed_converted_t *)can_devices.message;
		can_data->omega_fl = speed->fl;
		can_data->omega_fr = speed->fr;
		break;
	}
	}
}
#else
static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data,
																							can_received_bitset_t *can_received) {
	assert(message && can_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {

	case PRIMARY_ECU_POWER_MAPS_FRAME_ID: {
		primary_ecu_power_maps_converted_t *power_maps = (primary_ecu_power_maps_converted_t *)can_devices.message;
		can_data->map_power = power_maps->map_power;
		can_data->sc_state = power_maps->sc_state;
		can_data->tv_state = power_maps->tv_state;
		can_data->reg_state = power_maps->reg_state;
		CAN_RECEIVED_SET(*can_received, CAN_REC_MAPS)
		break;
	}
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
static inline void can_messages_parse_secondary(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received) {
	assert(message && can_data);

	secondary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SECONDARY_FRONT_ANGULAR_VELOCITY_FRAME_ID: {
		secondary_front_angular_velocity_converted_t *speed =
				(secondary_front_angular_velocity_converted_t *)can_devices.message;
		can_data->omega_fl = speed->fl;
		can_data->omega_fr = speed->fr;
		CAN_RECEIVED_SET(*can_received, CAN_REC_OMEGA_F)
		break;
	}
		// 	case SECONDARY_REAR_ANGULAR_VELOCITY_FRAME_ID: {
		// #if USE_INVERTERS_SPEED == 0
		// 		secondary_rear_angular_velocity_converted_t *speed =
		// 				(secondary_rear_angular_velocity_converted_t *)can_devices.message;
		// 		can_data->omega_rl = speed->rl;
		// 		can_data->omega_rr = speed->rr;
		// 		CAN_RECEIVED_SET(*can_received, CAN_REC_OMEGA_R)
		// #endif
		// 		break;
		// 	}
	case SECONDARY_PEDAL_THROTTLE_FRAME_ID: {
		secondary_pedal_throttle_converted_t *pedals_output = (secondary_pedal_throttle_converted_t *)can_devices.message;
		can_data->throttle = convert_throttle(pedals_output->throttle);
		CAN_RECEIVED_SET(*can_received, CAN_REC_THROTTLE)
		break;
	}
	case SECONDARY_PEDAL_BRAKES_PRESSURE_FRAME_ID: {
		secondary_pedal_brakes_pressure_converted_t *pedals_output =
				(secondary_pedal_brakes_pressure_converted_t *)can_devices.message;
		can_data->brake_f = convert_brake(pedals_output->front);
		can_data->brake_r = convert_brake(pedals_output->rear);
		CAN_RECEIVED_SET(*can_received, CAN_REC_BRAKE)
		break;
	}
	case SECONDARY_IMU_ACCELERATION_FRAME_ID: {
		secondary_imu_acceleration_converted_t *acceleration =
				(secondary_imu_acceleration_converted_t *)can_devices.message;
		can_data->accel_x = convert_accel(acceleration->x);
		can_data->accel_y = convert_accel(acceleration->y);
		can_data->accel_z = convert_accel(acceleration->z);
		CAN_RECEIVED_SET(*can_received, CAN_REC_ACCEL)
		break;
	}
	case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {
		secondary_imu_angular_rate_converted_t *angular_rate =
				(secondary_imu_angular_rate_converted_t *)can_devices.message;
		can_data->gyro_x = convert_gyro(angular_rate->x);
		can_data->gyro_y = convert_gyro(angular_rate->y);
		can_data->gyro_z = convert_gyro(angular_rate->z);
		CAN_RECEIVED_SET(*can_received, CAN_REC_GYRO)
		break;
	}
	case SECONDARY_STEER_ANGLE_FRAME_ID: {
		secondary_steer_angle_converted_t *steer_angle = (secondary_steer_angle_converted_t *)can_devices.message;
		can_data->steering_angle = convert_steering_angle(steer_angle->angle);
		CAN_RECEIVED_SET(*can_received, CAN_REC_STEER_ANGLE)
		break;
	}
	case SECONDARY_VEHICLE_SPEED_FRAME_ID: {
		secondary_vehicle_speed_converted_t *speed = (secondary_vehicle_speed_converted_t *)can_devices.message;
		// if (USE_TLM_VELOCITY_ESTIMATION == 1) {
		can_data->u = speed->u;
		// }
		CAN_RECEIVED_SET(*can_received, CAN_REC_U)
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_inverters(can_message_t *message, can_data_t *can_data,
																								can_received_bitset_t *can_received) {
	assert(message && can_data);

	inverters_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case INVERTERS_INV_L_RCV_FRAME_ID: {
		inverters_inv_l_rcv_converted_t *rcv = (inverters_inv_l_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_L_RCV_RCV_MUX_ID_A8_N_ACTUAL_FILT_CHOICE:
			// #if USE_INVERTERS_SPEED == 1
			can_data->omega_rl = -inverter_convert_speed(rcv->n_actual_filt);
			CAN_RECEIVED_SET(*can_received, CAN_REC_OMEGA_R)
			// #endif
			break;
		default:
			break;
		}
		break;
	}
	case INVERTERS_INV_R_RCV_FRAME_ID: {
		inverters_inv_r_rcv_converted_t *rcv = (inverters_inv_r_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_R_RCV_RCV_MUX_ID_A8_N_ACTUAL_FILT_CHOICE:
			// #if USE_INVERTERS_SPEED == 1
			can_data->omega_rr = inverter_convert_speed(rcv->n_actual_filt);
			CAN_RECEIVED_SET(*can_received, CAN_REC_OMEGA_R)
			// #endif
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
#endif

static inline double inverter_convert_speed(double val) {
	return (val * 10.0 / 4.5 * (M_PI / 30.0) * (INV_MAX_SPEED / INT16_MAX));
}
static inline double convert_gyro(double val) { return -val * M_PI / 180.0; };
static inline double convert_accel(double val) { return -val * 9.81; };
static inline double convert_brake(double val) { return val; };
static inline double convert_throttle(double val) { return val; };
static inline double convert_steering_angle(double val) { return val * (M_PI / 180.0); };
