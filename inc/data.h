#ifndef __DATA_H__
#define __DATA_H__

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

#endif // __DATA_H__
