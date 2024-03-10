#ifndef __DATA_H__
#define __DATA_H__

typedef struct {
	double steering_angle;
	double throttle;
	double brake;
	double accel_x;
	double accel_y;
	double accel_z;
	double gyro_x;
	double gyro_y;
	double gyro_z;
	double omega_fl;
	double omega_fr;
	double omega_rl;
	double omega_rr;
	double map_pw;
	double map_sc;
	double map_tv;
} can_data_t;

#endif // __DATA_H__
