/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.c
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.372
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Aug 31 14:47:29 2024
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

const debug_bus SLIP_rtZdebug_bus = {
		0.0, /* lambda */
		0.0, /* filtered_lambda_error */
		0.0, /* shallow_filtered_lambda_error */
		0.0, /* proportional */
		0.0, /* integral */
		0.0	 /* derivative */
}; /* debug_bus ground */

/* Exported data definition */

/* Data with Exported storage */
real_T SLIP_T_max;										 /* '<Root>/in_T_max' */
real_T SLIP_in_Kd;										 /* '<Root>/in_Kd' */
real_T SLIP_in_Ki;										 /* '<Root>/in_Ki' */
real_T SLIP_in_Kp;										 /* '<Root>/in_Kp' */
real_T SLIP_in_iteration_step_seconds; /* '<Root>/in_iteration_step_seconds' */
real_T SLIP_in_lambda_reference;			 /* '<Root>/in_lambda_reference' */
real_T SLIP_in_minimum_torque;				 /* '<Root>/in_minimum_torque' */
real_T SLIP_in_omega_rl;							 /* '<Root>/in_omega_rl' */
real_T SLIP_in_omega_rr;							 /* '<Root>/in_omega_rr' */
real_T SLIP_in_shallow_window_seconds; /* '<Root>/in_shallow_window_seconds' */
real_T SLIP_in_window_seconds;				 /* '<Root>/in_window_seconds' */
real_T SLIP_out_T_max_rl_slip;				 /* '<Root>/out_T_max_rl_slip' */
real_T SLIP_out_T_max_rr_slip;				 /* '<Root>/out_T_max_rr_slip' */
real_T SLIP_out_T_motor_rl;						 /* '<Root>/out_T_motor_rl' */
real_T SLIP_out_T_motor_rr;						 /* '<Root>/out_T_motor_rr' */
debug_bus SLIP_out_debug_bus_rl;			 /* '<Root>/out_debug_bus_rl' */
debug_bus SLIP_out_debug_bus_rr;			 /* '<Root>/out_debug_bus_rr' */
real_T SLIP_throttle;									 /* '<Root>/throttle' */
real_T SLIP_u;												 /* '<Root>/in_u_bar' */
real_T SLIP_yaw_rate;									 /* '<Root>/in_yaw_rate' */
real_T in_differentiation_step_seconds;
/* '<Root>/in_differentiation_step_seconds' */
static void MATLABFunction(real_T rtu_new_sample, boolean_T rtu_external_reset, real_T rtu_lower_bound,
													 real_T rtu_upper_bound, real_T rtu_sample_time, real_T *rty_integral);
static void MATLABFunction_h(real_T rtu_newSample, real_T rtu_window_length, real_T *rty_mem);
static void Slip_estimation(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow, real_T *rty_lambda);

/*
 * Output and update for atomic system:
 *    '<S9>/MATLAB Function'
 *    '<S21>/MATLAB Function'
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
 *    '<S10>/MATLAB Function'
 *    '<S11>/MATLAB Function'
 *    '<S22>/MATLAB Function'
 *    '<S23>/MATLAB Function'
 */
static void MATLABFunction_h(real_T rtu_newSample, real_T rtu_window_length, real_T *rty_mem) {
	*rty_mem = (1.0 - 1.0 / rtu_window_length) * *rty_mem + 1.0 / rtu_window_length * rtu_newSample;
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
	real_T rtb_Switch2_j;
	real_T rtb_derivative;
	real_T rtb_derivative_tmp;
	real_T rtb_error;
	real_T rtb_integral;
	real_T rtb_lambda;
	real_T rtb_mem;
	real_T rtb_mem_b;
	real_T rtb_mem_e;
	real_T rtb_mem_f;
	int32_T idxDelay;

	/* Product: '<S3>/Product' incorporates:
	 *  Inport: '<Root>/in_T_max'
	 *  Inport: '<Root>/throttle'
	 *  Product: '<S2>/Product'
	 */
	rtb_Product_tmp = SLIP_throttle * SLIP_T_max;

	/* MATLAB Function: '<S3>/Slip_estimation' incorporates:
	 *  Constant: '<S1>/Constant1'
	 *  Constant: '<S3>/Constant'
	 *  Gain: '<S3>/Rr'
	 *  Inport: '<Root>/in_omega_rl'
	 *  Inport: '<Root>/in_u_bar'
	 *  Inport: '<Root>/in_yaw_rate'
	 *  Product: '<S3>/Product1'
	 *  Sum: '<S3>/Add2'
	 */
	Slip_estimation(0.2286 * SLIP_in_omega_rl, SLIP_u + SLIP_yaw_rate * 0.605, 1.0, &rtb_lambda);

	/* Sum: '<S3>/Add1' incorporates:
	 *  Constant: '<S3>/Constant1'
	 *  Inport: '<Root>/in_lambda_reference'
	 *  MinMax: '<S3>/Max'
	 */
	rtb_error = SLIP_in_lambda_reference - fmax(rtb_lambda, 0.0);

	/* Delay: '<S23>/Delay One Step' */
	rtb_mem = SLIP_DW->DelayOneStep_DSTATE;

	/* MATLAB Function: '<S23>/MATLAB Function' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_shallow_window_seconds'
	 *  Product: '<S17>/Divide3'
	 */
	MATLABFunction_h(rtb_error, SLIP_in_shallow_window_seconds / SLIP_in_iteration_step_seconds, &rtb_mem);

	/* Product: '<S24>/Product' incorporates:
	 *  Inport: '<Root>/in_Kp'
	 */
	rtb_Switch2_j = rtb_mem * SLIP_in_Kp;

	/* Delay: '<S21>/Delay One Step' */
	rtb_integral = SLIP_DW->DelayOneStep_DSTATE_g;

	/* Switch: '<S21>/Switch' incorporates:
	 *  Gain: '<S21>/Gain'
	 *  Inport: '<Root>/in_Ki'
	 */
	if (rtb_error > 0.0) {
		rtb_derivative = SLIP_in_Ki;
	} else {
		rtb_derivative = 0.1 * SLIP_in_Ki;
	}

	/* MATLAB Function: '<S21>/MATLAB Function' incorporates:
	 *  Constant: '<S16>/Constant'
	 *  Constant: '<S17>/Constant'
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Inport: '<Root>/throttle'
	 *  Product: '<S21>/Product1'
	 *  RelationalOperator: '<S16>/Compare'
	 *  Switch: '<S21>/Switch'
	 */
	MATLABFunction(rtb_error * rtb_derivative, (SLIP_throttle < 0.03), SLIP_in_minimum_torque, 100.0,
								 SLIP_in_iteration_step_seconds, &rtb_integral);

	/* Delay: '<S22>/Delay One Step' */
	rtb_mem_b = SLIP_DW->DelayOneStep_DSTATE_m;

	/* MATLAB Function: '<S22>/MATLAB Function' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_window_seconds'
	 *  Product: '<S17>/Divide2'
	 */
	MATLABFunction_h(rtb_error, SLIP_in_window_seconds / SLIP_in_iteration_step_seconds, &rtb_mem_b);

	/* Product: '<S17>/Divide1' incorporates:
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Product: '<S5>/Divide1'
	 */
	rtb_derivative_tmp = in_differentiation_step_seconds / SLIP_in_iteration_step_seconds;

	/* Delay: '<S17>/Delay' incorporates:
	 *  DataTypeConversion: '<S17>/Cast To Single'
	 *  Product: '<S17>/Divide1'
	 */
	if ((real32_T)rtb_derivative_tmp < 1.0F) {
		rtb_derivative = rtb_mem_b;
	} else {
		if ((real32_T)rtb_derivative_tmp > 100.0F) {
			idxDelay = 100;
		} else {
			idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_derivative_tmp), 4.2949673E+9F);
		}

		rtb_derivative = SLIP_DW->Delay_DSTATE[100U - (uint32_T)idxDelay];
	}

	/* End of Delay: '<S17>/Delay' */

	/* Product: '<S17>/Product' incorporates:
	 *  Inport: '<Root>/in_Kd'
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Product: '<S17>/Divide'
	 *  Sum: '<S17>/Sum'
	 */
	rtb_derivative = (rtb_mem_b - rtb_derivative) / in_differentiation_step_seconds * SLIP_in_Kd;

	/* MinMax: '<S17>/Max' incorporates:
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Sum: '<S17>/Sum2'
	 */
	rtb_error = fmax((rtb_Switch2_j + rtb_integral) + rtb_derivative, SLIP_in_minimum_torque);

	/* Switch: '<S19>/Switch2' incorporates:
	 *  Constant: '<S3>/Constant3'
	 *  Product: '<S3>/Product'
	 *  RelationalOperator: '<S19>/LowerRelop1'
	 *  RelationalOperator: '<S19>/UpperRelop'
	 *  Switch: '<S19>/Switch'
	 */
	if (rtb_error > rtb_Product_tmp) {
		rtb_error = rtb_Product_tmp;
	} else if (rtb_error < 0.0) {
		/* Switch: '<S19>/Switch' incorporates:
		 *  Constant: '<S3>/Constant3'
		 */
		rtb_error = 0.0;
	}

	/* End of Switch: '<S19>/Switch2' */

	/* Switch: '<S18>/Switch2' incorporates:
	 *  Constant: '<S3>/Constant2'
	 *  Product: '<S3>/Product'
	 *  RelationalOperator: '<S18>/LowerRelop1'
	 *  RelationalOperator: '<S18>/UpperRelop'
	 *  Switch: '<S18>/Switch'
	 */
	if (rtb_Product_tmp > rtb_error) {
		/* Outport: '<Root>/out_T_motor_rl' */
		SLIP_out_T_motor_rl = rtb_error;
	} else if (rtb_Product_tmp < 0.0) {
		/* Switch: '<S18>/Switch' incorporates:
		 *  Constant: '<S3>/Constant2'
		 *  Outport: '<Root>/out_T_motor_rl'
		 */
		SLIP_out_T_motor_rl = 0.0;
	} else {
		/* Outport: '<Root>/out_T_motor_rl' */
		SLIP_out_T_motor_rl = rtb_Product_tmp;
	}

	/* End of Switch: '<S18>/Switch2' */

	/* Outport: '<Root>/out_T_max_rl_slip' */
	SLIP_out_T_max_rl_slip = rtb_error;

	/* BusCreator: '<S3>/Bus Creator' incorporates:
	 *  Outport: '<Root>/out_debug_bus_rl'
	 */
	SLIP_out_debug_bus_rl.lambda = rtb_lambda;
	SLIP_out_debug_bus_rl.filtered_lambda_error = rtb_mem_b;
	SLIP_out_debug_bus_rl.shallow_filtered_lambda_error = rtb_mem;
	SLIP_out_debug_bus_rl.proportional = rtb_Switch2_j;
	SLIP_out_debug_bus_rl.integral = rtb_integral;
	SLIP_out_debug_bus_rl.derivative = rtb_derivative;

	/* MATLAB Function: '<S2>/Slip_estimation' incorporates:
	 *  Constant: '<S1>/Constant'
	 *  Constant: '<S2>/Constant'
	 *  Gain: '<S2>/Rr'
	 *  Inport: '<Root>/in_omega_rr'
	 *  Inport: '<Root>/in_u_bar'
	 *  Inport: '<Root>/in_yaw_rate'
	 *  Product: '<S2>/Product1'
	 *  Sum: '<S2>/Add2'
	 */
	Slip_estimation(0.2286 * SLIP_in_omega_rr, SLIP_u + SLIP_yaw_rate * -0.605, 1.0, &rtb_lambda);

	/* Sum: '<S2>/Add1' incorporates:
	 *  Constant: '<S2>/Constant1'
	 *  Inport: '<Root>/in_lambda_reference'
	 *  MinMax: '<S2>/Max'
	 */
	rtb_Switch2_j = SLIP_in_lambda_reference - fmax(rtb_lambda, 0.0);

	/* Delay: '<S9>/Delay One Step' */
	rtb_Product = SLIP_DW->DelayOneStep_DSTATE_l;

	/* Switch: '<S9>/Switch' incorporates:
	 *  Gain: '<S9>/Gain'
	 *  Inport: '<Root>/in_Ki'
	 */
	if (rtb_Switch2_j > 0.0) {
		rtb_derivative = SLIP_in_Ki;
	} else {
		rtb_derivative = 0.16666666666666666 * SLIP_in_Ki;
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
	MATLABFunction(rtb_Switch2_j * rtb_derivative, (SLIP_throttle < 0.03), SLIP_in_minimum_torque, 100.0,
								 SLIP_in_iteration_step_seconds, &rtb_Product);

	/* Delay: '<S11>/Delay One Step' */
	rtb_mem_e = SLIP_DW->DelayOneStep_DSTATE_l5;

	/* MATLAB Function: '<S11>/MATLAB Function' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_shallow_window_seconds'
	 *  Product: '<S5>/Divide3'
	 */
	MATLABFunction_h(rtb_Switch2_j, SLIP_in_shallow_window_seconds / SLIP_in_iteration_step_seconds, &rtb_mem_e);

	/* Product: '<S12>/Product' incorporates:
	 *  Inport: '<Root>/in_Kp'
	 */
	rtb_error = rtb_mem_e * SLIP_in_Kp;

	/* Delay: '<S10>/Delay One Step' */
	rtb_mem_f = SLIP_DW->DelayOneStep_DSTATE_j;

	/* MATLAB Function: '<S10>/MATLAB Function' incorporates:
	 *  Inport: '<Root>/in_iteration_step_seconds'
	 *  Inport: '<Root>/in_window_seconds'
	 *  Product: '<S5>/Divide2'
	 */
	MATLABFunction_h(rtb_Switch2_j, SLIP_in_window_seconds / SLIP_in_iteration_step_seconds, &rtb_mem_f);

	/* Delay: '<S5>/Delay' incorporates:
	 *  DataTypeConversion: '<S5>/Cast To Single'
	 */
	if ((real32_T)rtb_derivative_tmp < 1.0F) {
		rtb_Switch2_j = rtb_mem_f;
	} else {
		if ((real32_T)rtb_derivative_tmp > 100.0F) {
			idxDelay = 100;
		} else {
			idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_derivative_tmp), 4.2949673E+9F);
		}

		rtb_Switch2_j = SLIP_DW->Delay_DSTATE_m[100U - (uint32_T)idxDelay];
	}

	/* End of Delay: '<S5>/Delay' */

	/* Product: '<S5>/Product' incorporates:
	 *  Inport: '<Root>/in_Kd'
	 *  Inport: '<Root>/in_differentiation_step_seconds'
	 *  Product: '<S5>/Divide'
	 *  Sum: '<S5>/Sum'
	 */
	rtb_derivative = (rtb_mem_f - rtb_Switch2_j) / in_differentiation_step_seconds * SLIP_in_Kd;

	/* MinMax: '<S5>/Max' incorporates:
	 *  Inport: '<Root>/in_minimum_torque'
	 *  Sum: '<S5>/Sum2'
	 */
	rtb_Switch2_j = fmax((rtb_error + rtb_Product) + rtb_derivative, SLIP_in_minimum_torque);

	/* Switch: '<S7>/Switch2' incorporates:
	 *  Constant: '<S2>/Constant3'
	 *  RelationalOperator: '<S7>/LowerRelop1'
	 *  RelationalOperator: '<S7>/UpperRelop'
	 *  Switch: '<S7>/Switch'
	 */
	if (rtb_Switch2_j > rtb_Product_tmp) {
		rtb_Switch2_j = rtb_Product_tmp;
	} else if (rtb_Switch2_j < 0.0) {
		/* Switch: '<S7>/Switch' incorporates:
		 *  Constant: '<S2>/Constant3'
		 */
		rtb_Switch2_j = 0.0;
	}

	/* End of Switch: '<S7>/Switch2' */

	/* Outport: '<Root>/out_T_max_rr_slip' */
	SLIP_out_T_max_rr_slip = rtb_Switch2_j;

	/* Switch: '<S6>/Switch2' incorporates:
	 *  Constant: '<S2>/Constant2'
	 *  RelationalOperator: '<S6>/LowerRelop1'
	 *  RelationalOperator: '<S6>/UpperRelop'
	 *  Switch: '<S6>/Switch'
	 */
	if (rtb_Product_tmp > rtb_Switch2_j) {
		/* Outport: '<Root>/out_T_motor_rr' */
		SLIP_out_T_motor_rr = rtb_Switch2_j;
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

	/* BusCreator: '<S2>/Bus Creator' incorporates:
	 *  Outport: '<Root>/out_debug_bus_rr'
	 */
	SLIP_out_debug_bus_rr.lambda = rtb_lambda;
	SLIP_out_debug_bus_rr.filtered_lambda_error = rtb_mem_f;
	SLIP_out_debug_bus_rr.shallow_filtered_lambda_error = rtb_mem_e;
	SLIP_out_debug_bus_rr.proportional = rtb_error;
	SLIP_out_debug_bus_rr.integral = rtb_Product;
	SLIP_out_debug_bus_rr.derivative = rtb_derivative;

	/* Update for Delay: '<S23>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE = rtb_mem;

	/* Update for Delay: '<S21>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_g = rtb_integral;

	/* Update for Delay: '<S22>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_m = rtb_mem_b;

	/* Update for Delay: '<S9>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_l = rtb_Product;

	/* Update for Delay: '<S11>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_l5 = rtb_mem_e;

	/* Update for Delay: '<S10>/Delay One Step' */
	SLIP_DW->DelayOneStep_DSTATE_j = rtb_mem_f;
	for (idxDelay = 0; idxDelay < 99; idxDelay++) {
		/* Update for Delay: '<S17>/Delay' */
		SLIP_DW->Delay_DSTATE[idxDelay] = SLIP_DW->Delay_DSTATE[idxDelay + 1];

		/* Update for Delay: '<S5>/Delay' */
		SLIP_DW->Delay_DSTATE_m[idxDelay] = SLIP_DW->Delay_DSTATE_m[idxDelay + 1];
	}

	/* Update for Delay: '<S17>/Delay' */
	SLIP_DW->Delay_DSTATE[99] = rtb_mem_b;

	/* Update for Delay: '<S5>/Delay' */
	SLIP_DW->Delay_DSTATE_m[99] = rtb_mem_f;
}

/* Model initialize function */
void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M) {
	DW_SLIP *SLIP_DW = SLIP_M->dwork;

	/* Registration code */

	/* Storage classes */
	SLIP_out_debug_bus_rl = SLIP_rtZdebug_bus;
	SLIP_out_debug_bus_rr = SLIP_rtZdebug_bus;
	SLIP_out_T_max_rl_slip = 0.0;
	SLIP_out_T_max_rr_slip = 0.0;
	SLIP_out_T_motor_rr = 0.0;
	SLIP_out_T_motor_rl = 0.0;

	/* Storage classes */
	SLIP_throttle = 0.0;
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
	in_differentiation_step_seconds = 0.0;
	SLIP_in_window_seconds = 0.0;
	SLIP_in_shallow_window_seconds = 0.0;

	/* states (dwork) */
	(void)memset((void *)SLIP_DW, 0, sizeof(DW_SLIP));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
