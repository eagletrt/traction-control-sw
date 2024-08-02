#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>

typedef struct {
	double steering_angle;
	double throttle;
	double brake_f;
	double brake_r;
	double accel_x;
	double accel_y;
	double accel_z;
	double gyro_x;
	double gyro_y;
	double gyro_z;
	double u;
	double omega_fl;
	double omega_fr;
	double omega_rl;
	double omega_rr;
	double map_pw;
	double map_sc;
	double map_tv;
	double hv_min_cell_voltage;
	double hv_total_current;
	double hv_mean_temp;
	double lv_min_cell_voltage;
	double lv_total_current;
	double lv_mean_temp;
} can_data_t;

typedef enum {
	CAN_REC_STEER_ANGLE,
	CAN_REC_THROTTLE,
	CAN_REC_BRAKE,
	CAN_REC_ACCEL,
	CAN_REC_GYRO,
	CAN_REC_U,
	CAN_REC_OMEGA_F,
	CAN_REC_OMEGA_R,
	CAN_REC_MAPS,
	CAN_REC_HV,
	CAN_REC_LV,
	CAN_REC_COUNT
} can_received_t;

typedef uint32_t can_received_bitset_t;

#define RECEIVED_CONTROLS_MASK                                                                                         \
	(CAN_REC_STEER_ANGLE | CAN_REC_THROTTLE | CAN_REC_BRAKE | CAN_REC_ACCEL | CAN_REC_GYRO | CAN_REC_U |                 \
	 CAN_REC_OMEGA_F | CAN_REC_OMEGA_R | CAN_REC_MAPS)
#define RECEIVED_HV_SOC_MASK (CAN_REC_HV)
#define RECEIVED_LV_SOC_MASK (CAN_REC_LV)

#define CAN_RECEIVED_ALL(value) (value & (CAN_REC_COUNT - 1))
#define CAN_RECEIVED_SET(value, bitset) value = value | (1 << bitset);
#define CAN_RECEIVED_CLEAR(value) value = 0;

#endif // __DATA_H__
