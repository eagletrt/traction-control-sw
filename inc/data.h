#ifndef __DATA_H__
#define __DATA_H__

#include "exported/All0_ert_rtw/All0.h"
#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

typedef struct {
	real_T rtTmax_rl;
	real_T rtTmax_rr;
	real_T rtaxG;
	real_T rtmap_motor;
	real_T rtomega_fl;
	real_T rtomega_fr;
	real_T rtomega_rl;
	real_T rtomega_rr;
	real_T rtu_bar;
} ve_data_t;

#endif // __DATA_H__