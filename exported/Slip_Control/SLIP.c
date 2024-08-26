/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.c
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.210
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun Aug 25 20:16:31 2024
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
real_T SLIP_Driver_req;                /* '<Root>/Inp_driver_request' */
real_T SLIP_Inp_IntegralOffset;        /* '<Root>/Inp_IntegralOffset' */
real_T SLIP_Inp_Ki;                    /* '<Root>/Inp_Ki' */
real_T SLIP_Inp_Kp;                    /* '<Root>/Inp_Kp' */
real_T SLIP_Inp_LambdaRef;             /* '<Root>/Inp_LambdaRef' */
real_T SLIP_Out_Tm_rl;                 /* '<Root>/Out_Tm_rl' */
real_T SLIP_Out_Tm_rr;                 /* '<Root>/Out_Tm_rr' */
real_T SLIP_Out_Tmax_rl_slip;          /* '<Root>/Out_Tmax_rl_slip' */
real_T SLIP_Out_Tmax_rr_slip;          /* '<Root>/Out_Tmax_rr_slip' */
real_T SLIP_Out_lambda_rl;             /* '<Root>/Out_lambda_rl' */
real_T SLIP_Out_lambda_rr;             /* '<Root>/Out_lambda_rr' */
real_T SLIP_Tmax_rl;                   /* '<Root>/Inp_Tmax_rl' */
real_T SLIP_Tmax_rr;                   /* '<Root>/Inp_Tmax_rr' */
real_T SLIP_map_sc;                    /* '<Root>/Inp_map_sc' */
real_T SLIP_omega_rl;                  /* '<Root>/Inp_omega_rl' */
real_T SLIP_omega_rr;                  /* '<Root>/Inp_omega_rr' */
real_T SLIP_u;                         /* '<Root>/Inp_u_bar' */
real_T SLIP_yaw_rate;                  /* '<Root>/Inp_Omega' */
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
static void map(real_T rtu_Tmax_slip, real_T rtu_Tmax_motor, real_T rtu_map_sc,
                real_T *rty_T_max);

/*
 * Output and update for atomic system:
 *    '<S2>/Slip_est1'
 *    '<S3>/Slip_est1'
 */
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda)
{
  real_T Vmax;
  Vmax = fmax(fabs(rtu_u_bar), fabs(rtu_omegaR));
  if (Vmax > rtu_Vlow) {
    *rty_lambda = (rtu_omegaR - rtu_u_bar) / Vmax;
  } else {
    *rty_lambda = (rtu_omegaR - rtu_u_bar) * 2.0 / (Vmax * Vmax / rtu_Vlow +
      rtu_Vlow);
  }
}

/*
 * Output and update for atomic system:
 *    '<S2>/map'
 *    '<S3>/map'
 */
static void map(real_T rtu_Tmax_slip, real_T rtu_Tmax_motor, real_T rtu_map_sc,
                real_T *rty_T_max)
{
  *rty_T_max = (rtu_Tmax_motor - rtu_Tmax_slip) * (1.0 - rtu_map_sc) +
    rtu_Tmax_slip;
}

/* Model step function */
void SLIP_step(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T DiscreteTimeIntegrator1_j;
  real_T rtb_Product1;
  real_T rtb_Switch_e;
  real_T rtb_error;
  boolean_T rtb_Compare;
  boolean_T rtb_Compare_f;

  /* MATLAB Function: '<S3>/Slip_est1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Gain: '<S3>/Rr'
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Inp_Omega'
   *  Inport: '<Root>/Inp_omega_rr'
   *  Inport: '<Root>/Inp_u_bar'
   *  Outport: '<Root>/Out_lambda_rr'
   *  Sum: '<S3>/Add2'
   */
  Slip_est1(0.203 * SLIP_omega_rr, SLIP_u + 0.605 * SLIP_yaw_rate, 1.0,
            &SLIP_Out_lambda_rr);

  /* Sum: '<S3>/Add1' incorporates:
   *  Inport: '<Root>/Inp_LambdaRef'
   *  Outport: '<Root>/Out_lambda_rr'
   */
  rtb_Switch_e = SLIP_Inp_LambdaRef - SLIP_Out_lambda_rr;

  /* Switch: '<S18>/Switch' incorporates:
   *  Gain: '<S18>/Gain'
   *  Inport: '<Root>/Inp_Ki'
   */
  if (rtb_Switch_e > 0.0) {
    DiscreteTimeIntegrator1_j = SLIP_Inp_Ki;
  } else {
    DiscreteTimeIntegrator1_j = 0.5 * SLIP_Inp_Ki;
  }

  /* Product: '<S18>/Product1' incorporates:
   *  Switch: '<S18>/Switch'
   */
  rtb_Product1 = rtb_Switch_e * DiscreteTimeIntegrator1_j;

  /* RelationalOperator: '<S12>/Compare' incorporates:
   *  Constant: '<S12>/Constant'
   *  Inport: '<Root>/Inp_driver_request'
   */
  rtb_Compare = (SLIP_Driver_req >= 0.03);

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  if (rtb_Compare && (SLIP_DW->DiscreteTimeIntegrator1_PrevRes <= 0)) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 5.0E-5 * rtb_Product1 +
    SLIP_DW->DiscreteTimeIntegrator1_DSTATE;

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  if (DiscreteTimeIntegrator1 < 0.0) {
    /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
    DiscreteTimeIntegrator1 = 0.0;
  }

  /* Sum: '<S13>/Sum2' incorporates:
   *  Inport: '<Root>/Inp_IntegralOffset'
   *  Inport: '<Root>/Inp_Kp'
   *  Product: '<S19>/Product'
   *  Sum: '<S18>/Add'
   */
  rtb_Switch_e = rtb_Switch_e * SLIP_Inp_Kp + (DiscreteTimeIntegrator1 +
    SLIP_Inp_IntegralOffset);

  /* Switch: '<S15>/Switch2' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  RelationalOperator: '<S15>/LowerRelop1'
   *  RelationalOperator: '<S15>/UpperRelop'
   *  Switch: '<S15>/Switch'
   */
  if (rtb_Switch_e > SLIP_Tmax_rr) {
    rtb_Switch_e = SLIP_Tmax_rr;
  } else if (rtb_Switch_e < 0.0) {
    /* Switch: '<S15>/Switch' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    rtb_Switch_e = 0.0;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_map_sc'
   *  Outport: '<Root>/Out_Tmax_rr_slip'
   */
  map(rtb_Switch_e, SLIP_Tmax_rr, SLIP_map_sc, &SLIP_Out_Tmax_rr_slip);

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_driver_request'
   */
  rtb_Switch_e = SLIP_Driver_req * SLIP_Tmax_rr;

  /* Switch: '<S14>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Outport: '<Root>/Out_Tmax_rr_slip'
   *  RelationalOperator: '<S14>/LowerRelop1'
   *  RelationalOperator: '<S14>/UpperRelop'
   *  Switch: '<S14>/Switch'
   */
  if (rtb_Switch_e > SLIP_Out_Tmax_rr_slip) {
    /* Outport: '<Root>/Out_Tm_rr' */
    SLIP_Out_Tm_rr = SLIP_Out_Tmax_rr_slip;
  } else if (rtb_Switch_e < 0.0) {
    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Out_Tm_rr'
     */
    SLIP_Out_Tm_rr = 0.0;
  } else {
    /* Outport: '<Root>/Out_Tm_rr' incorporates:
     *  Switch: '<S14>/Switch'
     */
    SLIP_Out_Tm_rr = rtb_Switch_e;
  }

  /* End of Switch: '<S14>/Switch2' */

  /* RelationalOperator: '<S4>/Compare' incorporates:
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/Inp_driver_request'
   */
  rtb_Compare_f = (SLIP_Driver_req >= 0.03);

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Rr'
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Inp_Omega'
   *  Inport: '<Root>/Inp_omega_rl'
   *  Inport: '<Root>/Inp_u_bar'
   *  Outport: '<Root>/Out_lambda_rl'
   *  Sum: '<S2>/Add2'
   */
  Slip_est1(0.203 * SLIP_omega_rl, SLIP_u - 0.605 * SLIP_yaw_rate, 1.0,
            &SLIP_Out_lambda_rl);

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Inp_LambdaRef'
   *  Outport: '<Root>/Out_lambda_rl'
   */
  rtb_error = SLIP_Inp_LambdaRef - SLIP_Out_lambda_rl;

  /* Switch: '<S10>/Switch' incorporates:
   *  Gain: '<S10>/Gain'
   *  Inport: '<Root>/Inp_Ki'
   */
  if (rtb_error > 0.0) {
    DiscreteTimeIntegrator1_j = SLIP_Inp_Ki;
  } else {
    DiscreteTimeIntegrator1_j = 0.5 * SLIP_Inp_Ki;
  }

  /* Product: '<S10>/Product1' incorporates:
   *  Switch: '<S10>/Switch'
   */
  rtb_Switch_e = rtb_error * DiscreteTimeIntegrator1_j;

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  if (rtb_Compare_f && (SLIP_DW->DiscreteTimeIntegrator1_PrevR_h <= 0)) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 0.0;
  }

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1_j = 5.0E-5 * rtb_Switch_e +
    SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j;

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  if (DiscreteTimeIntegrator1_j < 0.0) {
    /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
    DiscreteTimeIntegrator1_j = 0.0;
  }

  /* Sum: '<S5>/Sum2' incorporates:
   *  Inport: '<Root>/Inp_IntegralOffset'
   *  Inport: '<Root>/Inp_Kp'
   *  Product: '<S11>/Product'
   *  Sum: '<S10>/Add'
   */
  rtb_error = rtb_error * SLIP_Inp_Kp + (DiscreteTimeIntegrator1_j +
    SLIP_Inp_IntegralOffset);

  /* Switch: '<S7>/Switch2' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  RelationalOperator: '<S7>/LowerRelop1'
   *  RelationalOperator: '<S7>/UpperRelop'
   *  Switch: '<S7>/Switch'
   */
  if (rtb_error > SLIP_Tmax_rl) {
    rtb_error = SLIP_Tmax_rl;
  } else if (rtb_error < 0.0) {
    /* Switch: '<S7>/Switch' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    rtb_error = 0.0;
  }

  /* End of Switch: '<S7>/Switch2' */

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  Inport: '<Root>/Inp_map_sc'
   *  Outport: '<Root>/Out_Tmax_rl_slip'
   */
  map(rtb_error, SLIP_Tmax_rl, SLIP_map_sc, &SLIP_Out_Tmax_rl_slip);

  /* Product: '<S2>/Product' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  Inport: '<Root>/Inp_driver_request'
   */
  rtb_error = SLIP_Driver_req * SLIP_Tmax_rl;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Outport: '<Root>/Out_Tmax_rl_slip'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_error > SLIP_Out_Tmax_rl_slip) {
    /* Outport: '<Root>/Out_Tm_rl' */
    SLIP_Out_Tm_rl = SLIP_Out_Tmax_rl_slip;
  } else if (rtb_error < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Out_Tm_rl'
     */
    SLIP_Out_Tm_rl = 0.0;
  } else {
    /* Outport: '<Root>/Out_Tm_rl' incorporates:
     *  Switch: '<S6>/Switch'
     */
    SLIP_Out_Tm_rl = rtb_error;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 5.0E-5 * rtb_Product1 +
    DiscreteTimeIntegrator1;
  if (SLIP_DW->DiscreteTimeIntegrator1_DSTATE < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  SLIP_DW->DiscreteTimeIntegrator1_PrevRes = (int8_T)rtb_Compare;

  /* End of Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 5.0E-5 * rtb_Switch_e +
    DiscreteTimeIntegrator1_j;
  if (SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 0.0;
  }

  SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = (int8_T)rtb_Compare_f;

  /* End of Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
}

/* Model initialize function */
void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;

  /* Registration code */

  /* Storage classes */
  SLIP_Out_Tm_rr = 0.0;
  SLIP_Out_Tm_rl = 0.0;
  SLIP_Out_lambda_rr = 0.0;
  SLIP_Out_lambda_rl = 0.0;
  SLIP_Out_Tmax_rr_slip = 0.0;
  SLIP_Out_Tmax_rl_slip = 0.0;

  /* Storage classes */
  SLIP_Driver_req = 0.0;
  SLIP_u = 0.0;
  SLIP_omega_rr = 0.0;
  SLIP_omega_rl = 0.0;
  SLIP_yaw_rate = 0.0;
  SLIP_Tmax_rl = 0.0;
  SLIP_Tmax_rr = 0.0;
  SLIP_map_sc = 0.0;
  SLIP_Inp_LambdaRef = 0.0;
  SLIP_Inp_Kp = 0.0;
  SLIP_Inp_Ki = 0.0;
  SLIP_Inp_IntegralOffset = 0.0;

  /* states (dwork) */
  (void) memset((void *)SLIP_DW, 0,
                sizeof(DW_SLIP));

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
