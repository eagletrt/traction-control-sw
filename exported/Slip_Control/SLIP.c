/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.c
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.194
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun Jul 21 11:37:30 2024
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
real_T SLIP_Inp_UppSatLim;             /* '<Root>/Inp_UppSatLim' */
real_T SLIP_Out_Debug_slip;            /* '<Root>/Out_Debug_slip' */
real_T SLIP_Out_Tm_rl;                 /* '<Root>/Out_Tm_rl' */
real_T SLIP_Out_Tm_rr;                 /* '<Root>/Out_Tm_rr' */
real_T SLIP_Out_Tmax_rl_slip;          /* '<Root>/Out_Tmax_rl_slip' */
real_T SLIP_Out_Tmax_rr_slip;          /* '<Root>/Out_Tmax_rr_slip' */
real_T SLIP_Tmax_rl;                   /* '<Root>/Inp_Tmax_rl' */
real_T SLIP_Tmax_rr;                   /* '<Root>/Inp_Tmax_rr' */
real_T SLIP_map_sc;                    /* '<Root>/Inp_map_sc' */
real_T SLIP_omega_rl;                  /* '<Root>/Inp_omega_rl' */
real_T SLIP_omega_rr;                  /* '<Root>/Inp_omega_rr' */
real_T SLIP_u;                         /* '<Root>/Inp_u_bar' */
real_T SLIP_yaw_rate;                  /* '<Root>/Inp_Omega' */
static void map(real_T rtu_Tmax_slip, real_T rtu_Tmax_motor, real_T rtu_map_sc,
                real_T *rty_T_max);

/*
 * Output and update for atomic system:
 *    '<S2>/map'
 *    '<S3>/map'
 */
static void map(real_T rtu_Tmax_slip, real_T rtu_Tmax_motor, real_T rtu_map_sc,
                real_T *rty_T_max)
{
  if (rtu_map_sc > 0.05) {
    *rty_T_max = rtu_Tmax_slip;
  } else {
    *rty_T_max = rtu_Tmax_motor;
  }
}

/* Model step function */
void SLIP_step(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;
  real_T Vmax;
  real_T rtb_Add_f;
  real_T rtb_Rr;
  real_T rtb_Rr_n;
  real_T rtb_error;
  real_T rtb_vms;

  /* Gain: '<S3>/Rr' incorporates:
   *  Inport: '<Root>/Inp_omega_rr'
   */
  rtb_Rr = 0.203 * SLIP_omega_rr;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Inp_Omega'
   *  Inport: '<Root>/Inp_u_bar'
   */
  rtb_vms = 0.605 * SLIP_yaw_rate + SLIP_u;

  /* MATLAB Function: '<S3>/Slip_est1' incorporates:
   *  Constant: '<S3>/Constant'
   */
  Vmax = fmax(fabs(rtb_vms), fabs(rtb_Rr));
  if (Vmax > 1.0) {
    rtb_Rr = fabs((rtb_vms - rtb_Rr) / Vmax);
  } else {
    rtb_Rr = fabs((rtb_vms - rtb_Rr) * 2.0 / (Vmax * Vmax + 1.0));
  }

  /* End of MATLAB Function: '<S3>/Slip_est1' */

  /* Sum: '<S3>/Add1' incorporates:
   *  Inport: '<Root>/Inp_LambdaRef'
   */
  rtb_error = SLIP_Inp_LambdaRef - rtb_Rr;

  /* Product: '<S3>/Product1' incorporates:
   *  Inport: '<Root>/Inp_Ki'
   *  Inport: '<Root>/Inp_map_sc'
   *  Product: '<S2>/Product1'
   */
  rtb_Add_f = SLIP_map_sc * SLIP_Inp_Ki;

  /* Product: '<S17>/Product1' incorporates:
   *  Product: '<S3>/Product1'
   */
  rtb_Rr = rtb_Add_f * rtb_error;

  /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/Inp_driver_request'
   *  Sum: '<S3>/Add'
   */
  if ((SLIP_Driver_req - 0.03 > 0.0) &&
      (SLIP_DW->DiscreteTimeIntegrator1_PrevRes <= 0)) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
  rtb_vms = 5.0E-5 * rtb_Rr + SLIP_DW->DiscreteTimeIntegrator1_DSTATE;

  /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
  if (rtb_vms < 0.0) {
    /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
    rtb_vms = 0.0;
  }

  /* Sum: '<S17>/Add' incorporates:
   *  Inport: '<Root>/Inp_IntegralOffset'
   */
  Vmax = rtb_vms + SLIP_Inp_IntegralOffset;

  /* Switch: '<S19>/Switch2' incorporates:
   *  Constant: '<S12>/Constant'
   *  Inport: '<Root>/Inp_UppSatLim'
   *  RelationalOperator: '<S19>/LowerRelop1'
   *  RelationalOperator: '<S19>/UpperRelop'
   *  Switch: '<S19>/Switch'
   */
  if (Vmax > SLIP_Inp_UppSatLim) {
    Vmax = SLIP_Inp_UppSatLim;
  } else if (Vmax < 0.0) {
    /* Switch: '<S19>/Switch' incorporates:
     *  Constant: '<S12>/Constant'
     */
    Vmax = 0.0;
  }

  /* Sum: '<S12>/Sum2' incorporates:
   *  Inport: '<Root>/Inp_Kp'
   *  Product: '<S18>/Product'
   *  Switch: '<S19>/Switch2'
   */
  Vmax += rtb_error * SLIP_Inp_Kp;

  /* Switch: '<S14>/Switch2' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  RelationalOperator: '<S14>/LowerRelop1'
   *  RelationalOperator: '<S14>/UpperRelop'
   *  Switch: '<S14>/Switch'
   */
  if (Vmax > SLIP_Tmax_rr) {
    Vmax = SLIP_Tmax_rr;
  } else if (Vmax < 0.0) {
    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    Vmax = 0.0;
  }

  /* End of Switch: '<S14>/Switch2' */

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_map_sc'
   *  Outport: '<Root>/Out_Tmax_rr_slip'
   */
  map(Vmax, SLIP_Tmax_rr, SLIP_map_sc, &SLIP_Out_Tmax_rr_slip);

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_driver_request'
   */
  Vmax = SLIP_Driver_req * SLIP_Tmax_rr;

  /* Switch: '<S13>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Outport: '<Root>/Out_Tmax_rr_slip'
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S13>/Switch'
   */
  if (Vmax > SLIP_Out_Tmax_rr_slip) {
    /* Outport: '<Root>/Out_Tm_rr' */
    SLIP_Out_Tm_rr = SLIP_Out_Tmax_rr_slip;
  } else if (Vmax < 0.0) {
    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Out_Tm_rr'
     */
    SLIP_Out_Tm_rr = 0.0;
  } else {
    /* Outport: '<Root>/Out_Tm_rr' incorporates:
     *  Switch: '<S13>/Switch'
     */
    SLIP_Out_Tm_rr = Vmax;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/Inp_omega_rl'
   */
  rtb_Rr_n = 0.203 * SLIP_omega_rl;

  /* Sum: '<S2>/Add2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Inp_Omega'
   *  Inport: '<Root>/Inp_u_bar'
   */
  rtb_error = SLIP_u - 0.605 * SLIP_yaw_rate;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_error), fabs(rtb_Rr_n));
  if (Vmax > 1.0) {
    Vmax = fabs((rtb_error - rtb_Rr_n) / Vmax);
  } else {
    Vmax = fabs((rtb_error - rtb_Rr_n) * 2.0 / (Vmax * Vmax + 1.0));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Inp_LambdaRef'
   */
  rtb_error = SLIP_Inp_LambdaRef - Vmax;

  /* Product: '<S9>/Product1' */
  Vmax = rtb_Add_f * rtb_error;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport: '<Root>/Inp_driver_request'
   *  Sum: '<S2>/Add'
   */
  if ((SLIP_Driver_req - 0.03 > 0.0) &&
      (SLIP_DW->DiscreteTimeIntegrator1_PrevR_h <= 0)) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 0.0;
  }

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtb_Rr_n = 5.0E-5 * Vmax + SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  if (rtb_Rr_n < 0.0) {
    /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
    rtb_Rr_n = 0.0;
  }

  /* Sum: '<S9>/Add' incorporates:
   *  Inport: '<Root>/Inp_IntegralOffset'
   */
  rtb_Add_f = rtb_Rr_n + SLIP_Inp_IntegralOffset;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/Inp_UppSatLim'
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (rtb_Add_f > SLIP_Inp_UppSatLim) {
    rtb_Add_f = SLIP_Inp_UppSatLim;
  } else if (rtb_Add_f < 0.0) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S4>/Constant'
     */
    rtb_Add_f = 0.0;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Sum: '<S4>/Sum2' incorporates:
   *  Inport: '<Root>/Inp_Kp'
   *  Product: '<S10>/Product'
   */
  rtb_error = rtb_error * SLIP_Inp_Kp + rtb_Add_f;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_error > SLIP_Tmax_rl) {
    rtb_error = SLIP_Tmax_rl;
  } else if (rtb_error < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    rtb_error = 0.0;
  }

  /* End of Switch: '<S6>/Switch2' */

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

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Outport: '<Root>/Out_Tmax_rl_slip'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_error > SLIP_Out_Tmax_rl_slip) {
    /* Outport: '<Root>/Out_Tm_rl' */
    SLIP_Out_Tm_rl = SLIP_Out_Tmax_rl_slip;
  } else if (rtb_error < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Out_Tm_rl'
     */
    SLIP_Out_Tm_rl = 0.0;
  } else {
    /* Outport: '<Root>/Out_Tm_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    SLIP_Out_Tm_rl = rtb_error;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/Inp_driver_request'
   *  Sum: '<S3>/Add'
   */
  SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 5.0E-5 * rtb_Rr + rtb_vms;
  if (SLIP_DW->DiscreteTimeIntegrator1_DSTATE < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  if (SLIP_Driver_req - 0.03 > 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevRes = 1;
  } else if (SLIP_Driver_req - 0.03 < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevRes = -1;
  } else if (SLIP_Driver_req - 0.03 == 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevRes = 0;
  } else {
    SLIP_DW->DiscreteTimeIntegrator1_PrevRes = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport: '<Root>/Inp_driver_request'
   *  Sum: '<S2>/Add'
   */
  SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 5.0E-5 * Vmax + rtb_Rr_n;
  if (SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_DSTAT_j = 0.0;
  }

  if (SLIP_Driver_req - 0.03 > 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = 1;
  } else if (SLIP_Driver_req - 0.03 < 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = -1;
  } else if (SLIP_Driver_req - 0.03 == 0.0) {
    SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = 0;
  } else {
    SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
}

/* Model initialize function */
void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;

  /* Registration code */

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
  SLIP_Inp_UppSatLim = 0.0;
  SLIP_Inp_IntegralOffset = 0.0;

  /* Storage classes */
  SLIP_Out_Tm_rr = 0.0;
  SLIP_Out_Tm_rl = 0.0;
  SLIP_Out_Debug_slip = 0.0;
  SLIP_Out_Tmax_rr_slip = 0.0;
  SLIP_Out_Tmax_rl_slip = 0.0;

  /* states (dwork) */
  (void) memset((void *)SLIP_DW, 0,
                sizeof(DW_SLIP));

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  SLIP_DW->DiscreteTimeIntegrator1_PrevR_h = 2;

  /* ConstCode for Outport: '<Root>/Out_Debug_slip' incorporates:
   *  Constant: '<S3>/Constant4'
   */
  SLIP_Out_Debug_slip = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
