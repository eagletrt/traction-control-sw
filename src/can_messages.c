#include "inc/can_messages.h"
#include "inc/benchmark.h"

#define CANLIB_DEVICE_IMPLEMENTATION
#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/inverters/inverters_network.h"
#include "lib/can/lib/simulator/simulator_network.h"

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
		can_data->gyro_x = convert_gyro(angular_rate->ang_rate_x);
		can_data->gyro_y = convert_gyro(angular_rate->ang_rate_y);
		can_data->gyro_z = convert_gyro(angular_rate->ang_rate_z);
		break;
	}
	case SIMULATOR_IMU_ACCELERATION_FRAME_ID: {
		simulator_imu_acceleration_converted_t *acceleration =
				(simulator_imu_acceleration_converted_t *)can_devices.message;
		can_data->accel_x = convert_accel(acceleration->accel_x);
		can_data->accel_y = convert_accel(acceleration->accel_y);
		can_data->accel_z = convert_accel(acceleration->accel_z);
		break;
	}
	case SIMULATOR_PEDALS_OUTPUT_FRAME_ID: {
		simulator_pedals_output_converted_t *pedals = (simulator_pedals_output_converted_t *)can_devices.message;
		can_data->throttle = pedals->apps;
		can_data->brake = convert_brake((pedals->bse_front + pedals->bse_rear) / 2.0);
		break;
	}
	case SIMULATOR_STEERING_ANGLE_FRAME_ID: {
		simulator_steering_angle_converted_t *steering_angle = (simulator_steering_angle_converted_t *)can_devices.message;
		can_data->steering_angle = convert_steering_angle(steering_angle->angle);
		break;
	}
	case SIMULATOR_SPEED_FRAME_ID: {
		simulator_speed_converted_t *speed = (simulator_speed_converted_t *)can_devices.message;
		can_data->omega_fl = speed->encoder_l;
		can_data->omega_fr = speed->encoder_r;
		break;
	}
	}
}

static inline void can_messages_parse_primary(can_message_t *message, can_data_t *can_data) {
	assert(message && can_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case PRIMARY_SPEED_FRAME_ID: {
		primary_speed_converted_t *speed = (primary_speed_converted_t *)can_devices.message;
		can_data->omega_fl = speed->encoder_l;
		can_data->omega_fr = speed->encoder_r;
		break;
	}
	case PRIMARY_STEER_STATUS_FRAME_ID: {
		primary_steer_status_converted_t *steer_status = (primary_steer_status_converted_t *)can_devices.message;
		can_data->map_pw = steer_status->map_pw;
		can_data->map_sc = steer_status->map_sc;
		can_data->map_tv = steer_status->map_tv;
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
	case SECONDARY_PEDALS_OUTPUT_FRAME_ID: {
		secondary_pedals_output_converted_t *pedals_output = (secondary_pedals_output_converted_t *)can_devices.message;
		can_data->throttle = convert_throttle(pedals_output->apps);
		can_data->brake = convert_brake((pedals_output->bse_front + pedals_output->bse_rear) / 2.0);
		break;
	}
	case SECONDARY_IMU_ACCELERATION_FRAME_ID: {
		secondary_imu_acceleration_converted_t *acceleration =
				(secondary_imu_acceleration_converted_t *)can_devices.message;
		can_data->accel_x = convert_accel(acceleration->accel_x);
		can_data->accel_y = convert_accel(acceleration->accel_y);
		can_data->accel_z = convert_accel(acceleration->accel_z);
		break;
	}
	case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {
		secondary_imu_angular_rate_converted_t *angular_rate =
				(secondary_imu_angular_rate_converted_t *)can_devices.message;
		can_data->gyro_x = convert_gyro(angular_rate->ang_rate_x);
		can_data->gyro_y = convert_gyro(angular_rate->ang_rate_y);
		can_data->gyro_z = convert_gyro(angular_rate->ang_rate_z);
		break;
	}
	case SECONDARY_STEERING_ANGLE_FRAME_ID: {
		secondary_steering_angle_converted_t *steering_angle = (secondary_steering_angle_converted_t *)can_devices.message;
		can_data->steering_angle = convert_steering_angle(steering_angle->angle);
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
static inline double convert_brake(double val) { return val / 100.0; };
static inline double convert_throttle(double val) { return val / 100.0; };
static inline double convert_steering_angle(double val) { return val * (M_PI / 180.0); };