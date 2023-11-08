#ifndef __DATA_H__
#define __DATA_H__

#include "exported/Traction_Control/Torque.h"
#include "exported/Velocity_Estimation/Velocity_Estimation.h"

typedef struct {
	real_T rtTmax_rl_Velocity_Estimation;
	real_T rtTmax_rr_Velocity_Estimation;
	real_T rtaxG_Velocity_Estimation;
	real_T rtmap_motor_Velocity_Estimation;
	real_T rtomega_fl_Velocity_Estimation;
	real_T rtomega_fr_Velocity_Estimation;
	real_T rtomega_rl_Velocity_Estimation;
	real_T rtomega_rr_Velocity_Estimation;
	real_T rtu_bar_Velocity_Estimation;
} ve_data_t;

typedef struct {
	real_T rtbrake_Torque;
	real_T rtDriver_req_Torque;
	real_T rtSteeringangle_Torque;

	real_T rtTm_rl_Torque;
	real_T rtTm_rr_Torque;
	real_T rtTm_rl_a_Torque; // mangled
	real_T rtTm_rr_m_Torque; // mangled

	real_T rtmap_sc_Torque;
	real_T rtmap_tv_Torque;

	real_T rtomega_rl_Torque;
	real_T rtomega_rr_Torque;

	real_T rtyaw_rate_Torque;

	real_T rtu_bar_Torque;
} torque_data_t;

typedef struct {
	real_T rtDriver_req_SlipV2;
	real_T rtSteeringangle_SlipV2;

	real_T rtTm_rl_SlipV2;
	real_T rtTm_rr_SlipV2;
	real_T rtTm_rl_a_SlipV2;
	real_T rtTm_rr_m_SlipV2;

	real_T rtbrake_SlipV2;
	real_T rtmap_sc_SlipV2;
	real_T rtmap_tv_SlipV2;
	real_T rtomega_rl_SlipV2;
	real_T rtomega_rr_SlipV2;
	real_T rtu_bar_SlipV2;
	real_T rtyaw_rate_SlipV2;
} slip_data_t;

#endif // __DATA_H__