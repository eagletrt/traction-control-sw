#ifndef __DATA_H__
#define __DATA_H__

#include "exported/All0_ert_rtw/All0.h"
#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

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
	real_T rtbrake_All0;
	real_T rtDriver_req_All0;
	real_T rtSteeringangle_All0;

	real_T rtTm_rl_All0;
	real_T rtTm_rr_All0;
	real_T rtTm_rl_a_All0; // mangled
	real_T rtTm_rr_m_All0; // mangled

	real_T rtmap_sc_All0;
	real_T rtmap_tv_All0;

	real_T rtomega_rl_All0;
	real_T rtomega_rr_All0;

	real_T rtyaw_rate_All0;

	real_T rtu_bar_All0;
} all_data_t;

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
}slip_data_t;

#endif // __DATA_H__