#include "inc/can_messages.h"

#define CANLIB_DEVICE_IMPLEMENTATION
#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/inverters/inverters_network.h"
#include "lib/can/lib/simulator/simulator_network.h"

#include <assert.h>

static inline double inverter_convert_speed(double val);

static inline void can_messages_parse_primary(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																							slip_data_t *slip_data);
static inline void can_messages_parse_secondary(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data);
static inline void can_messages_parse_inverters(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data);
static inline void can_messages_parse_simulator(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data);

uint8_t raw_mem[512];
uint8_t converted_mem[512];
device_t can_devices;

void can_messages_init() {
	(void)equal_d;
	get_timestamp_u();
	device_init(&can_devices);
	device_set_address(&can_devices, &raw_mem, sizeof(raw_mem), &converted_mem, sizeof(converted_mem));
}

void can_messages_parse(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data, slip_data_t *slip_data) {
	assert(message && ve_data);

	if (message->socket == CAN_SOCKET_PRIMARY) {
#ifdef SIMULATOR
		if (primary_id_is_message(message->frame.can_id)) {
			can_messages_parse_primary(message, ve_data, all_data, slip_data);
		}
#else	 // SIMULATOR
		if (simulator_id_is_message(message->frame.can_id)) {
			can_messages_parse_simulator(message, ve_data, all_data, slip_data);
		} else if (inverters_id_is_message(message->frame.can_id)) {
			can_messages_parse_inverters(message, ve_data, all_data, slip_data);
		}
#endif // SIMULATOR
	} else if (message->socket == CAN_SOCKET_SECONDARY) {
		if (secondary_id_is_message(message->frame.can_id)) {
			can_messages_parse_secondary(message, ve_data, all_data, slip_data);
		}
	}
}

static inline void can_messages_parse_simulator(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data) {
	assert(message && ve_data);

	simulator_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SIMULATOR_IMU_ANGULAR_RATE_FRAME_ID: {
		simulator_imu_angular_rate_converted_t *angular_rate = (simulator_imu_angular_rate_converted_t *)can_devices.message;
		all_data->rtyaw_rate_All0 = angular_rate->ang_rate_z;
		slip_data->rtyaw_rate_SlipV2 = all_data->rtyaw_rate_All0;
		break;
	}
	case SIMULATOR_IMU_ACCELERATION_FRAME_ID: {
		simulator_imu_acceleration_converted_t *acceleration = (simulator_imu_acceleration_converted_t *)can_devices.message;
		ve_data->rtaxG_Velocity_Estimation = acceleration->accel_x;
		break;
	}
	case SIMULATOR_PEDALS_OUTPUT_FRAME_ID: {
		simulator_pedals_output_converted_t *pedals = (simulator_pedals_output_converted_t *)can_devices.message;
		all_data->rtbrake_All0 = (pedals->bse_front + pedals->bse_rear) / 2.0;
		all_data->rtDriver_req_All0 = pedals->apps;
		slip_data->rtbrake_SlipV2 = all_data->rtbrake_All0;
		slip_data->rtDriver_req_SlipV2 = all_data->rtDriver_req_All0;
		break;
	}
	case SIMULATOR_STEERING_ANGLE_FRAME_ID: {
		simulator_steering_angle_converted_t *steering_angle = (simulator_steering_angle_converted_t *)can_devices.message;
		all_data->rtSteeringangle_All0 = steering_angle->angle;
		slip_data->rtSteeringangle_SlipV2 = all_data->rtSteeringangle_All0;
		break;
	}
	case SIMULATOR_SPEED_FRAME_ID: {
		simulator_speed_converted_t *speed = (simulator_speed_converted_t *)can_devices.message;
		ve_data->rtomega_fl_Velocity_Estimation = speed->encoder_l;
		ve_data->rtomega_fr_Velocity_Estimation = speed->encoder_r;
		break;
	}
	}
}

static inline void can_messages_parse_primary(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																							slip_data_t *slip_data) {
	assert(message && ve_data);

	primary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case PRIMARY_SPEED_FRAME_ID: {
		primary_speed_converted_t *speed = (primary_speed_converted_t *)can_devices.message;
		ve_data->rtomega_fl_Velocity_Estimation = speed->encoder_l;
		ve_data->rtomega_fr_Velocity_Estimation = speed->encoder_r;
		break;
	}
	case PRIMARY_STEER_STATUS_FRAME_ID: {
		primary_steer_status_converted_t *steer_status = (primary_steer_status_converted_t *)can_devices.message;
		ve_data->rtmap_motor_Velocity_Estimation = steer_status->map_pw;
		all_data->rtmap_sc_All0 = steer_status->map_sc;
		all_data->rtmap_tv_All0 = steer_status->map_tv;
		slip_data->rtmap_sc_SlipV2 = steer_status->map_sc;
		slip_data->rtmap_tv_SlipV2 = steer_status->map_tv;
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_secondary(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data) {
	assert(message && ve_data);

	secondary_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case SECONDARY_PEDALS_OUTPUT_FRAME_ID: {
		secondary_pedals_output_converted_t *pedals_output = (secondary_pedals_output_converted_t *)can_devices.message;
		all_data->rtbrake_All0 = (pedals_output->bse_rear + pedals_output->bse_front) / 2.0;
		all_data->rtDriver_req_All0 = pedals_output->apps;
		slip_data->rtbrake_SlipV2 = all_data->rtbrake_All0;
		slip_data->rtDriver_req_SlipV2 = all_data->rtDriver_req_All0;
		break;
	}
	case SECONDARY_IMU_ACCELERATION_FRAME_ID: {
		secondary_imu_acceleration_converted_t *acceleration =
				(secondary_imu_acceleration_converted_t *)can_devices.message;
		ve_data->rtaxG_Velocity_Estimation = acceleration->accel_x;
		break;
	}
	case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {
		secondary_imu_angular_rate_converted_t *angular_rate =
				(secondary_imu_angular_rate_converted_t *)can_devices.message;
		all_data->rtyaw_rate_All0 = angular_rate->ang_rate_z;
		slip_data->rtyaw_rate_SlipV2 = all_data->rtyaw_rate_All0;
		break;
	}
	case SECONDARY_STEERING_ANGLE_FRAME_ID: {
		secondary_steering_angle_converted_t *steering_angle = (secondary_steering_angle_converted_t *)can_devices.message;
		all_data->rtSteeringangle_All0 = steering_angle->angle;
		slip_data->rtSteeringangle_SlipV2 = all_data->rtSteeringangle_All0;
		break;
	}
	default:
		break;
	}
}
static inline void can_messages_parse_inverters(can_message_t *message, ve_data_t *ve_data, all_data_t *all_data,
																								slip_data_t *slip_data) {
	assert(message && ve_data);
	UNUSED(all_data);

	inverters_devices_deserialize_from_id(&can_devices, message->frame.can_id, message->frame.data, 0);

	switch (message->frame.can_id) {
	case INVERTERS_INV_L_RCV_FRAME_ID: {
		inverters_inv_l_rcv_converted_t *rcv = (inverters_inv_l_rcv_converted_t *)can_devices.message;
		switch (rcv->rcv_mux) {
		case INVERTERS_INV_L_RCV_RCV_MUX_ID_A8_N_ACTUAL_FILT_CHOICE:
			ve_data->rtomega_rl_Velocity_Estimation = -inverter_convert_speed(rcv->n_actual_filt);
			slip_data->rtomega_rl_SlipV2 = ve_data->rtomega_rl_Velocity_Estimation;
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
			ve_data->rtomega_rr_Velocity_Estimation = inverter_convert_speed(rcv->n_actual_filt);
			slip_data->rtomega_rr_SlipV2 = ve_data->rtomega_rr_Velocity_Estimation;
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

static inline double inverter_convert_speed(double val) { return (val * 10.0f * INV_MAX_SPEED) / 32767.f; }