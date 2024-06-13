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

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data);
static inline void can_messages_parse_secondary(can_message_t *message, can_data_t *can_data);
static inline void can_messages_parse_inverters(can_message_t *message, can_data_t *can_data);
static inline void can_messages_parse_simulator(can_message_t *message, can_data_t *can_data);

uint8_t raw_mem[512];
uint8_t converted_mem[512];
device_t can_devices;

void can_messages_init() {
	get_timestamp_u();
	device_init(&can_devices);
	device_set_address(&can_devices, &raw_mem, sizeof(raw_mem), &converted_mem, sizeof(converted_mem));
}

void can_messages_parse(can_message_t *message, can_data_t *can_data) {
	assert(message && can_data);

#if SIMULATOR == 1
	if (message->socket == CAN_SOCKET_PRIMARY) {
		if (simulator_id_is_message(message->frame.can_id)) {
			can_messages_parse_simulator(message, can_data);
		}
	}
#else
	if (message->socket == CAN_SOCKET_PRIMARY) {
		if (inverters_id_is_message(message->frame.can_id)) {
			can_messages_parse_inverters(message, can_data);
		} else if (primary_id_is_message(message->frame.can_id)) {
			can_messages_parse_primary(message, can_data);
		}
	} else if (message->socket == CAN_SOCKET_SECONDARY) {
		if (secondary_id_is_message(message->frame.can_id)) {
			can_messages_parse_secondary(message, can_data);
		}
	}
#endif // SIMULATOR
}

static inline void can_messages_parse_simulator(can_message_t *message, can_data_t *can_data) {
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

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data) {
	assert(message && can_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {

	case PRIMARY_ECU_SET_POWER_MAPS_FRAME_ID: {
		primary_ecu_set_power_maps_converted_t *power_maps = (primary_ecu_set_power_maps_converted_t *)can_devices.message;
		can_data->map_pw = power_maps->map_pw;
		can_data->map_sc = power_maps->map_sc;
		can_data->map_tv = power_maps->map_tv;
		break;
	}
	case PRIMARY_HV_CURRENT_FRAME_ID: {
		primary_hv_current_converted_t *hv_current = (primary_hv_current_converted_t *)can_devices.message;
		can_data->hv_total_current = hv_current->current;
		break;
	}
	case PRIMARY_HV_CELLS_VOLTAGE_STATS_FRAME_ID: {
		primary_hv_cells_voltage_stats_converted_t *hv_cells_volts_stats =
				(primary_hv_cells_voltage_stats_converted_t *)can_devices.message;
		can_data->hv_min_cell_voltage = hv_cells_volts_stats->min;
		break;
	}
	case PRIMARY_HV_CELLS_TEMP_STATS_FRAME_ID: {
		primary_hv_cells_temp_stats_converted_t *hv_cells_temps_stats =
				(primary_hv_cells_temp_stats_converted_t *)can_devices.message;
		can_data->hv_mean_temp = hv_cells_temps_stats->min;
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_secondary(can_message_t *message, can_data_t *can_data) {
	assert(message && can_data);

	secondary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SECONDARY_ANGULAR_VELOCITY_FRAME_ID: {
		secondary_angular_velocity_converted_t *speed = (secondary_angular_velocity_converted_t *)can_devices.message;
		can_data->omega_fl = speed->fl;
		can_data->omega_fr = speed->fr;
		break;
	}
	case SECONDARY_PEDAL_THROTTLE_FRAME_ID: {
		secondary_pedal_throttle_converted_t *pedals_output = (secondary_pedal_throttle_converted_t *)can_devices.message;
		can_data->throttle = convert_throttle(pedals_output->throttle);
		break;
	}
	case SECONDARY_PEDAL_BRAKES_PRESSURE_FRAME_ID: {
		secondary_pedal_brakes_pressure_converted_t *pedals_output =
				(secondary_pedal_brakes_pressure_converted_t *)can_devices.message;
		can_data->brake_f = convert_brake(pedals_output->front);
		can_data->brake_r = convert_brake(pedals_output->rear);
		break;
	}
	case SECONDARY_IMU_ACCELERATION_FRAME_ID: {
		secondary_imu_acceleration_converted_t *acceleration =
				(secondary_imu_acceleration_converted_t *)can_devices.message;
		can_data->accel_x = convert_accel(acceleration->x);
		can_data->accel_y = convert_accel(acceleration->y);
		can_data->accel_z = convert_accel(acceleration->z);
		break;
	}
	case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {
		secondary_imu_angular_rate_converted_t *angular_rate =
				(secondary_imu_angular_rate_converted_t *)can_devices.message;
		can_data->gyro_x = convert_gyro(angular_rate->x);
		can_data->gyro_y = convert_gyro(angular_rate->y);
		can_data->gyro_z = convert_gyro(angular_rate->z);
		break;
	}
	case SECONDARY_STEER_ANGLE_FRAME_ID: {
		secondary_steer_angle_converted_t *steer_angle = (secondary_steer_angle_converted_t *)can_devices.message;
		can_data->steering_angle = convert_steering_angle(steer_angle->angle);
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_inverters(can_message_t *message, can_data_t *can_data) {
	assert(message && can_data);

	inverters_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case INVERTERS_INV_L_RCV_FRAME_ID: {
		inverters_inv_l_rcv_converted_t *rcv = (inverters_inv_l_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_L_RCV_RCV_MUX_ID_A8_N_ACTUAL_FILT_CHOICE:
			can_data->omega_rl = -inverter_convert_speed(rcv->n_actual_filt);
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
			can_data->omega_rr = inverter_convert_speed(rcv->n_actual_filt);
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

static inline double inverter_convert_speed(double val) {
	return (val * 4.5 * (M_PI / 60.0) * (INV_MAX_SPEED / 32767.f));
}
static inline double convert_gyro(double val) { return -val * M_PI / 180.0; };
static inline double convert_accel(double val) { return -val * 9.81; };
static inline double convert_brake(double val) { return val; };
static inline double convert_throttle(double val) { return val; };
static inline double convert_steering_angle(double val) { return val * (M_PI / 180.0); };
