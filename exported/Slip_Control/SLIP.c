/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.c
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.281
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Aug 29 18:46:57 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SLIP.h"
#include "rtwtypes.h"
#include <math.h>

/* Exported data definition */

/* Data with Exported storage */
real_T SLIP_Driver_req;	 /* '<Root>/throttle' */
real_T SLIP_T_max;			 /* '<Root>/in_T_max' */
real_T SLIP_in_omega_rl; /* '<Root>/in_omega_rl' */
real_T SLIP_in_omega_rr; /* '<Root>/in_omega_rr' */
real_T SLIP_u;					 /* '<Root>/in_u_bar' */
real_T SLIP_yaw_rate;		 /* '<Root>/in_yaw_rate' */

real_T SLIP_in_Kd; /* '<Root>/in_Kd' */
real_T SLIP_in_Ki; /* '<Root>/in_Ki' */
real_T SLIP_in_Kp; /* '<Root>/in_Kp' */

real_T SLIP_in_iteration_step_seconds; /* '<Root>/in_iteration_step_seconds' */
real_T SLIP_in_lambda_reference;			 /* '<Root>/in_lambda_reference' */
real_T SLIP_in_minimum_torque;				 /* '<Root>/in_minimum_torque' */
real_T SLIP_in_window_size_seconds;		 /* '<Root>/in_window_size_seconds' */
real_T in_differentiation_step_seconds;
/* '<Root>/in_differentiation_step_seconds' */
real_T in_shallow_window_size_seconds;
/* '<Root>/in_shallow_window_size_seconds' */

real_T SLIP_out_T_max_rl_slip; /* '<Root>/out_T_max_rl_slip' */
real_T SLIP_out_T_max_rr_slip; /* '<Root>/out_T_max_rr_slip' */
real_T SLIP_out_T_motor_rl;		 /* '<Root>/out_T_motor_rl' */
real_T SLIP_out_T_motor_rr;		 /* '<Root>/out_T_motor_rr' */
real_T SLIP_out_lambda_rl;		 /* '<Root>/out_lambda_rl' */
real_T SLIP_out_lambda_rr;		 /* '<Root>/out_lambda_rr' */

static void MATLABFunction(real_T rtu_new_sample, boolean_T rtu_external_reset, real_T rtu_lower_bound,
													 real_T rtu_upper_bound, real_T rtu_sample_time, real_T *rty_integral);
static void MATLABFunction1(real_T rtu_newSample, real_T rtu_window, real_T *rty_hist);
static void Slip_estimation(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow, real_T *rty_lambda);

/*
 * Output and update for atomic system:
 *    '<S9>/MATLAB Function'
 *    '<S19>/MATLAB Function'
 */
static void MATLABFunction(real_T rtu_new_sample, boolean_T rtu_external_reset, real_T rtu_lower_bound,
													 real_T rtu_upper_bound, real_T rtu_sample_time, real_T *rty_integral) {
	*rty_integral += rtu_new_sample * rtu_sample_time;
	if (rtu_external_reset) {
		*rty_integral = 0.0;
	}

	*rty_integral = fmax(fmin(*rty_integral, rtu_upper_bound), rtu_lower_bound);
}

/*
 * Output and update for atomic system:
 *    '<S5>/MATLAB Function1'
 *    '<S5>/MATLAB Function2'
 *    '<S15>/MATLAB Function1'
 *    '<S15>/MATLAB Function2'
 */
static void MATLABFunction1(real_T rtu_newSample, real_T rtu_window, real_T *rty_hist) {
	*rty_hist = (1.0 - 1.0 / rtu_window) * *rty_hist + rtu_newSample / rtu_window;
}

/*
 * Output and update for atomic system:
 *    '<S2>/Slip_estimation'
 *    '<S3>/Slip_estimation'
 */
static void Slip_estimation(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow, real_T *rty_lambda) {
	real_T Vmax;
	real_T Vmax_tmp;
	Vmax_tmp = fabs(rtu_omegaR);
	Vmax = fmax(fabs(rtu_u_bar), Vmax_tmp);
	if (Vmax > rtu_Vlow) {
		*rty_lambda = (rtu_omegaR - rtu_u_bar) / Vmax_tmp;
	} else {
		*rty_lambda = (rtu_omegaR - rtu_u_bar) * 2.0 / (Vmax * Vmax / rtu_Vlow + rtu_Vlow);
	}
}

/* Model step function */
void SLIP_step(RT_MODEL_SLIP *const SLIP_M) {
	DW_SLIP *SLIP_DW = SLIP_M->dwork;
	real_T rtb_Product;
	real_T rtb_Product_tmp;
	real_T rtb_Switch2_c;
	real_T rtb_Switch2_p_tmp;
	real_T rtb_error;
	real_T rtb_hist_d;
	real_T rtb_hist_f;
	real_T rtb_hist_g;
	real_T rtb_integral_n;
	int32_T idxDelay;

	/* Product: '<S2>/Product' incorporates:
	 *  Inport: '<Root>/in_T_max'
	 *  Inport: '<Root>/throttle'
	 *  Product: '<S3>/Product'
	 */
	rtb_Product_tmp = SLIP_Driver_req * SLIP_T_max;

	/* MATLAB Function: '<S2>/Slip_estimation' incorporates:
	 *  Constant: '<S1>/Constant'
	 *  Constant: '<S2>/Constant'
	 *  Gain: '<S2>/Rr'
	 *  Inport: '<Root>/in_omega_rr'
	 *  Inport: '<Root>/in_u_bar'
	 *  Inport: '<Root>/in_yaw_rate'
	 *  Outport: '<Root>/out_lambda_rr'
	 *  Product: '<S2>/Product1'
	 *  Sum: '<S2>/Add2'
	 */
	Slip_estimation(0.2286 * SLIP_in_omega_rr, SLIP_u + SLIP_yaw_rate * -0.605, 1.0, &SLIP_out_lambda_rr);

	/* Sum: '<S2>/Add1' incorporates:
	 *  Inport: '<Root>/in_lambda_reference'
	 *  Outport: '<Root>/out_lambda_rr'
	 */
	rtb_error = SLIP_in_lambda_reference - SLIP_out_lambda_rr;

	/* InitialCondition: '<S5>/IC2' */
	if (SLIP_DW->IC2_FirstOutputTime) {
		SLIP_DW->IC2_FirstOutputTime = false;

		/* MATLAB Function: '<S5>/MATLAB Function2' incorporates:
		 *  InitialCondition: '<S5>/IC2'
		 */
		rtb_hist_f = 0.0;
	} else {
		/* MATLAB Function: '<S5>/MATLAB Function2' incorporates:
		 *  Delay: '<S5>/Delay One Step2'
		 *  InitialCondition: '<S5>/IC2'
		 */
		rtb_hist_f = SLIP_DW->DelayOneStep2_DSTATE;
	}

	/* End of InitialCondition: '<S5>/IC2' */

	/* MATLAB Function: '<S5>/MATLAB Function2' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_shallow_window_size_seconds'
	 *  Product: '<S5>/Divide3'
	 */
	MATLABFunction1(rtb_error, in_shallow_window_size_seconds / SLIP_in_iteration_step_seconds, &rtb_hist_f);

	/* Delay: '<S9>/Delay One Step' */
	rtb_integral_n = SLIP_DW->DelayOneStep_DSTATE;

	/* Switch: '<S9>/Switch' incorporates:
	 *  Gain: '<S9>/Gain'
	 *  Inport: '<Root>/in_Ki'
	 */
	if (rtb_error > 0.0) {
		rtb_hist_g = SLIP_in_Ki;
	} else {
		rtb_hist_g = 0.16666666666666666 * SLIP_in_Ki;
	}

	/* MATLAB Function: '<S9>/MATLAB Function' incorporates:
	 *  Constant: '<S4>/Constant'
	 *  Constant: '<S5>/Constant'
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Inport: '<Root>/throttle'
	 *  Product: '<S9>/Product1'
	 *  RelationalOperator: '<S4>/Compare'
	 *  Switch: '<S9>/Switch'
	 */
	MATLABFunction(rtb_error * rtb_hist_g, (SLIP_Driver_req < 0.03), SLIP_in_minimum_torque, 100.0,
								 SLIP_in_iteration_step_seconds, &rtb_integral_n);

	/* InitialCondition: '<S5>/IC1' */
	if (SLIP_DW->IC1_FirstOutputTime) {
		SLIP_DW->IC1_FirstOutputTime = false;

		/* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
		 *  InitialCondition: '<S5>/IC1'
		 */
		rtb_hist_d = 0.0;
	} else {
		/* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
		 *  Delay: '<S5>/Delay One Step1'
		 *  InitialCondition: '<S5>/IC1'
		 */
		rtb_hist_d = SLIP_DW->DelayOneStep1_DSTATE;
	}

	/* End of InitialCondition: '<S5>/IC1' */

	/* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_window_size_seconds'
	 *  Product: '<S5>/Divide1'
	 */
	MATLABFunction1(rtb_error, SLIP_in_window_size_seconds / SLIP_in_iteration_step_seconds, &rtb_hist_d);

	/* Product: '<S5>/Divide2' incorporates:
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Product: '<S15>/Divide2'
	 */
	rtb_Switch2_p_tmp = in_differentiation_step_seconds / SLIP_in_iteration_step_seconds;

	/* Delay: '<S5>/Delay' incorporates:
	 *  DataTypeConversion: '<S5>/Cast To Single'
	 *  Product: '<S5>/Divide2'
	 */
	if ((real32_T)rtb_Switch2_p_tmp < 1.0F) {
		rtb_Switch2_c = rtb_hist_d;
	} else {
		if ((real32_T)rtb_Switch2_p_tmp > 100.0F) {
			idxDelay = 100;
		} else {
			idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_Switch2_p_tmp), 4.2949673E+9F);
		}

		rtb_Switch2_c = SLIP_DW->Delay_DSTATE[100U - (uint32_T)idxDelay];
	}

	/* End of Delay: '<S5>/Delay' */

	/* MinMax: '<S5>/Max' incorporates:
	 *  Inport: '<Root>/in_Kd'
	 *  Inport: '<Root>/in_Kp'
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Product: '<S12>/Product'
	 *  Product: '<S5>/Divide'
	 *  Product: '<S5>/Product'
	 *  Sum: '<S5>/Sum'
	 *  Sum: '<S5>/Sum2'
	 */
	rtb_Switch2_c = fmax((rtb_hist_d - rtb_Switch2_c) / in_differentiation_step_seconds * SLIP_in_Kd +
													 (rtb_hist_f * SLIP_in_Kp + rtb_integral_n),
											 SLIP_in_minimum_torque);

	/* Switch: '<S7>/Switch2' incorporates:
	 *  Constant: '<S2>/Constant3'
	 *  Product: '<S2>/Product'
	 *  RelationalOperator: '<S7>/LowerRelop1'
	 *  RelationalOperator: '<S7>/UpperRelop'
	 *  Switch: '<S7>/Switch'
	 */
	if (rtb_Switch2_c > rtb_Product_tmp) {
		rtb_Switch2_c = rtb_Product_tmp;
	} else if (rtb_Switch2_c < 0.0) {
		/* Switch: '<S7>/Switch' incorporates:
		 *  Constant: '<S2>/Constant3'
		 */
		rtb_Switch2_c = 0.0;
	}

	/* End of Switch: '<S7>/Switch2' */

	/* Switch: '<S6>/Switch2' incorporates:
	 *  Constant: '<S2>/Constant2'
	 *  Product: '<S2>/Product'
	 *  RelationalOperator: '<S6>/LowerRelop1'
	 *  RelationalOperator: '<S6>/UpperRelop'
	 *  Switch: '<S6>/Switch'
	 */
	if (rtb_Product_tmp > rtb_Switch2_c) {
		/* Outport: '<Root>/out_T_motor_rr' */
		SLIP_out_T_motor_rr = rtb_Switch2_c;
	} else if (rtb_Product_tmp < 0.0) {
		/* Switch: '<S6>/Switch' incorporates:
		 *  Constant: '<S2>/Constant2'
		 *  Outport: '<Root>/out_T_motor_rr'
		 */
		SLIP_out_T_motor_rr = 0.0;
	} else {
		/* Outport: '<Root>/out_T_motor_rr' */
		SLIP_out_T_motor_rr = rtb_Product_tmp;
	}

	/* End of Switch: '<S6>/Switch2' */

	/* Outport: '<Root>/out_T_max_rr_slip' */
	SLIP_out_T_max_rr_slip = rtb_Switch2_c;

	/* MATLAB Function: '<S3>/Slip_estimation' incorporates:
	 *  Constant: '<S1>/Constant1'
	 *  Constant: '<S3>/Constant'
	 *  Gain: '<S3>/Rr'
	 *  Inport: '<Root>/in_omega_rl'
	 *  Inport: '<Root>/in_u_bar'
	 *  Inport: '<Root>/in_yaw_rate'
	 *  Outport: '<Root>/out_lambda_rl'
	 *  Product: '<S3>/Product1'
	 *  Sum: '<S3>/Add2'
	 */
	Slip_estimation(0.2286 * SLIP_in_omega_rl, SLIP_u + SLIP_yaw_rate * 0.605, 1.0, &SLIP_out_lambda_rl);

	/* Sum: '<S3>/Add1' incorporates:
	 *  Inport: '<Root>/in_lambda_reference'
	 *  Outport: '<Root>/out_lambda_rl'
	 */
	rtb_Switch2_c = SLIP_in_lambda_reference - SLIP_out_lambda_rl;

	/* Delay: '<S19>/Delay One Step' */
	rtb_Product = SLIP_DW->DelayOneStep_DSTATE_j;

	/* Switch: '<S19>/Switch' incorporates:
	 *  Gain: '<S19>/Gain'
	 *  Inport: '<Root>/in_Ki'
	 */
	if (rtb_Switch2_c > 0.0) {
		rtb_hist_g = SLIP_in_Ki;
	} else {
		rtb_hist_g = 0.16666666666666666 * SLIP_in_Ki;
	}

	/* MATLAB Function: '<S19>/MATLAB Function' incorporates:
	 *  Constant: '<S14>/Constant'
	 *  Constant: '<S15>/Constant'
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Inport: '<Root>/throttle'
	 *  Product: '<S19>/Product1'
	 *  RelationalOperator: '<S14>/Compare'
	 *  Switch: '<S19>/Switch'
	 */
	MATLABFunction(rtb_Switch2_c * rtb_hist_g, (SLIP_Driver_req < 0.03), SLIP_in_minimum_torque, 100.0,
								 SLIP_in_iteration_step_seconds, &rtb_Product);

	/* InitialCondition: '<S15>/IC2' */
	if (SLIP_DW->IC2_FirstOutputTime_d) {
		SLIP_DW->IC2_FirstOutputTime_d = false;

		/* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
		 *  InitialCondition: '<S15>/IC2'
		 */
		rtb_error = 0.0;
	} else {
		/* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
		 *  Delay: '<S15>/Delay One Step2'
		 *  InitialCondition: '<S15>/IC2'
		 */
		rtb_error = SLIP_DW->DelayOneStep2_DSTATE_d;
	}

	/* End of InitialCondition: '<S15>/IC2' */

	/* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_shallow_window_size_seconds'
	 *  Product: '<S15>/Divide3'
	 */
	MATLABFunction1(rtb_Switch2_c, in_shallow_window_size_seconds / SLIP_in_iteration_step_seconds, &rtb_error);

	/* InitialCondition: '<S15>/IC1' */
	if (SLIP_DW->IC1_FirstOutputTime_b) {
		SLIP_DW->IC1_FirstOutputTime_b = false;

		/* MATLAB Function: '<S15>/MATLAB Function1' incorporates:
		 *  InitialCondition: '<S15>/IC1'
		 */
		rtb_hist_g = 0.0;
	} else {
		/* MATLAB Function: '<S15>/MATLAB Function1' incorporates:
		 *  Delay: '<S15>/Delay One Step1'
		 *  InitialCondition: '<S15>/IC1'
		 */
		rtb_hist_g = SLIP_DW->DelayOneStep1_DSTATE_n;
	}

	/* End of InitialCondition: '<S15>/IC1' */

	/* MATLAB Function: '<S15>/MATLAB Function1' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_window_size_seconds'
	 *  Product: '<S15>/Divide1'
	 */
	MATLABFunction1(rtb_Switch2_c, SLIP_in_window_size_seconds / SLIP_in_iteration_step_seconds, &rtb_hist_g);

	/* Delay: '<S15>/Delay' incorporates:
	 *  DataTypeConversion: '<S15>/Cast To Single'
	 */
	if ((real32_T)rtb_Switch2_p_tmp < 1.0F) {
		rtb_Switch2_c = rtb_hist_g;
	} else {
		if ((real32_T)rtb_Switch2_p_tmp > 100.0F) {
			idxDelay = 100;
		} else {
			idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_Switch2_p_tmp), 4.2949673E+9F);
		}

		rtb_Switch2_c = SLIP_DW->Delay_DSTATE_j[100U - (uint32_T)idxDelay];
	}

	/* End of Delay: '<S15>/Delay' */

	/* MinMax: '<S15>/Max' incorporates:
	 *  Inport: '<Root>/in_Kd'
	 *  Inport: '<Root>/in_Kp'
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Product: '<S15>/Divide'
	 *  Product: '<S15>/Product'
	 *  Product: '<S22>/Product'
	 *  Sum: '<S15>/Sum'
	 *  Sum: '<S15>/Sum2'
	 */
	rtb_Switch2_c = fmax((rtb_hist_g - rtb_Switch2_c) / in_differentiation_step_seconds * SLIP_in_Kd +
													 (rtb_error * SLIP_in_Kp + rtb_Product),
											 SLIP_in_minimum_torque);

	/* Switch: '<S17>/Switch2' incorporates:
	 *  Constant: '<S3>/Constant3'
	 *  RelationalOperator: '<S17>/LowerRelop1'
	 *  RelationalOperator: '<S17>/UpperRelop'
	 *  Switch: '<S17>/Switch'
	 */
	if (rtb_Switch2_c > rtb_Product_tmp) {
		rtb_Switch2_c = rtb_Product_tmp;
	} else if (rtb_Switch2_c < 0.0) {
		/* Switch: '<S17>/Switch' incorporates:
		 *  Constant: '<S3>/Constant3'
		 */
		rtb_Switch2_c = 0.0;
	}

	/* End of Switch: '<S17>/Switch2' */

	/* Switch: '<S16>/Switch2' incorporates:
	 *  Constant: '<S3>/Constant2'
	 *  RelationalOperator: '<S16>/LowerRelop1'
	 *  RelationalOperator: '<S16>/UpperRelop'
	 *  Switch: '<S16>/Switch'
	 */
	if (rtb_Product_tmp > rtb_Switch2_c) {
		/* Outport: '<Root>/out_T_motor_rl' */
		SLIP_out_T_motor_rl = rtb_Switch2_c;
	} else if (rtb_Product_tmp < 0.0) {
		/* Switch: '<S16>/Switch' incorporates:
		 *  Constant: '<S3>/Constant2'
		 *  Outport: '<Root>/out_T_motor_rl'
		 */
		SLIP_out_T_motor_rl = 0.0;
	} else {
		/* Outport: '<Root>/out_T_motor_rl' */
		SLIP_out_T_motor_rl = rtb_Product_tmp;
	}

	/* End of Switch: '<S16>/Switch2' */

	/* Outport: '<Root>/out_T_max_rl_slip' */
	SLIP_out_T_max_rl_slip = rtb_Switch2_c;

	/* Update for Delay: '<S5>/Delay One Step2' */
	SLIP_DW->DelayOneStep2_DSTATE = rtb_hist_f;

	/* Update for Delay: '<S9>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE = rtb_integral_n;

	/* Update for Delay: '<S5>/Delay One Step1' */
	SLIP_DW->DelayOneStep1_DSTATE = rtb_hist_d;

	/* Update for Delay: '<S19>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_j = rtb_Product;

	/* Update for Delay: '<S15>/Delay One Step2' */
	SLIP_DW->DelayOneStep2_DSTATE_d = rtb_error;

	/* Update for Delay: '<S15>/Delay One Step1' */
	SLIP_DW->DelayOneStep1_DSTATE_n = rtb_hist_g;
	for (idxDelay = 0; idxDelay < 99; idxDelay++) {
		/* Update for Delay: '<S5>/Delay' */
		SLIP_DW->Delay_DSTATE[idxDelay] = SLIP_DW->Delay_DSTATE[idxDelay + 1];

		/* Update for Delay: '<S15>/Delay' */
		SLIP_DW->Delay_DSTATE_j[idxDelay] = SLIP_DW->Delay_DSTATE_j[idxDelay + 1];
	}

	/* Update for Delay: '<S5>/Delay' */
	SLIP_DW->Delay_DSTATE[99] = rtb_hist_d;

	/* Update for Delay: '<S15>/Delay' */
	SLIP_DW->Delay_DSTATE_j[99] = rtb_hist_g;
}

/* Model initialize function */
void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M) {
	DW_SLIP *SLIP_DW = SLIP_M->dwork;

	/* Registration code */

	/* Storage classes */
	SLIP_out_T_motor_rr = 0.0;
	SLIP_out_T_motor_rl = 0.0;
	SLIP_out_lambda_rr = 0.0;
	SLIP_out_lambda_rl = 0.0;
	SLIP_out_T_max_rr_slip = 0.0;
	SLIP_out_T_max_rl_slip = 0.0;

	/* Storage classes */
	SLIP_Driver_req = 0.0;
	SLIP_u = 0.0;
	SLIP_in_omega_rr = 0.0;
	SLIP_in_omega_rl = 0.0;
	SLIP_yaw_rate = 0.0;
	SLIP_T_max = 0.0;
	SLIP_in_lambda_reference = 0.0;
	SLIP_in_Kp = 0.0;
	SLIP_in_Ki = 0.0;
	SLIP_in_Kd = 0.0;
	SLIP_in_minimum_torque = 0.0;
	SLIP_in_iteration_step_seconds = 0.0;
	SLIP_in_window_size_seconds = 0.0;
	in_shallow_window_size_seconds = 0.0;
	in_differentiation_step_seconds = 0.0;

	/* states (dwork) */
	(void)memset((void *)SLIP_DW, 0, sizeof(DW_SLIP));

	/* Start for InitialCondition: '<S5>/IC2' */
	SLIP_DW->IC2_FirstOutputTime = true;

	/* Start for InitialCondition: '<S5>/IC1' */
	SLIP_DW->IC1_FirstOutputTime = true;

	/* Start for InitialCondition: '<S15>/IC2' */
	SLIP_DW->IC2_FirstOutputTime_d = true;

	/* Start for InitialCondition: '<S15>/IC1' */
	SLIP_DW->IC1_FirstOutputTime_b = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
