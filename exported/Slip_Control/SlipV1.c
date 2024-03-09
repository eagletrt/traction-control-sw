/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1.c
 *
 * Code generated for Simulink model 'SlipV1'.
 *
 * Model version                  : 6.32
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Mar  9 12:19:17 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SlipV1.h"
#include "rtwtypes.h"
#include <math.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_SlipV1;            /* '<Root>/driver_request' */
real_T rtSteeringangle_SlipV1;         /* '<Root>/delta' */
real_T rtTel_Inp_IntegralResetValue_Sl;/* '<Root>/Tel_Inp_IntegralResetValue' */
real_T rtTel_Inp_SC_Ki_SlipV1;         /* '<Root>/Tel_Inp_SC_Ki' */
real_T rtTel_Inp_SC_Kp_SlipV1;         /* '<Root>/Tel_Inp_SC_Kp' */
real_T rtTel_Inp_SC_LambdaRef_SlipV1;  /* '<Root>/Tel_Inp_SC_LambdaRef' */
real_T rtTel_Inp_UppSatLim_SlipV1;     /* '<Root>/Tel_Inp_UppSatLim' */
real_T rtTel_Inp_minT_SlipV1;          /* '<Root>/Tel_Inp_minT' */
real_T rtTel_Out_Debug_Torque_SlipV1;  /* '<Root>/Tel_Out_Debug_Torque' */
real_T rtTm_rl_SlipV1;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_SlipV1;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_SlipV1;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_SlipV1;               /* '<Root>/Tm_rr' */
real_T rtTmax_rl_slip_SlipV1;          /* '<Root>/Tmax_rl_slip' */
real_T rtTmax_rr_slip_SlipV1;          /* '<Root>/Tmax_rr_slip' */
real_T rtbrake_SlipV1;                 /* '<Root>/Brake' */
real_T rtmap_sc_SlipV1;                /* '<Root>/map_sc' */
real_T rtmap_tv_SlipV1;                /* '<Root>/map_tv' */
real_T rtomega_rl_SlipV1;              /* '<Root>/omega_rl' */
real_T rtomega_rr_SlipV1;              /* '<Root>/omega_rr' */
real_T rtu_bar_SlipV1;                 /* '<Root>/u_bar' */
real_T rtyaw_rate_SlipV1;              /* '<Root>/Omega' */
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
  *rty_T_max = (rtu_Tmax_motor - rtu_Tmax_slip) * (1.0 - rtu_map_sc) +
    rtu_Tmax_slip;
}

/* Model step function */
void SlipV1_step(RT_MODEL_SlipV1 *const rtM_SlipV1)
{
  DW_SlipV1 *rtDW_SlipV1 = rtM_SlipV1->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T Vmax;
  real_T rtb_Add_d;
  real_T rtb_Product_d;
  real_T rtb_Product_ik;
  real_T rtb_Rr;
  real_T rtb_Switch2_g;
  real_T rtb_vms;
  real_T rtb_vms_h;

  /* Gain: '<S3>/Rr' incorporates:
   *  Inport: '<Root>/omega_rr'
   */
  rtb_Rr = 0.203 * rtomega_rr_SlipV1;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtyaw_rate_SlipV1 + rtu_bar_SlipV1;

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
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_Switch2_g = rtTel_Inp_SC_LambdaRef_SlipV1 - rtb_Rr;

  /* Product: '<S18>/Product1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  rtb_Rr = rtb_Switch2_g * rtTel_Inp_SC_Ki_SlipV1;

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product_ik = rtDriver_req_SlipV1 * rtTm_rr_SlipV1;

  /* Sum: '<S3>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_vms = rtb_Product_ik - rtTel_Inp_minT_SlipV1;

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  if ((rtb_vms > 0.0) && (rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes <= 0)) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 0.00025 * rtb_Rr +
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S18>/Add' incorporates:
   *  Constant: '<S21>/Constant'
   *  Inport: '<Root>/Tel_Inp_IntegralResetValue'
   *  Product: '<S18>/Product'
   *  RelationalOperator: '<S21>/Compare'
   */
  rtb_Add_d = (rtb_vms > 0.0 ? rtTel_Inp_IntegralResetValue_Sl : 0.0) +
    DiscreteTimeIntegrator1;

  /* Switch: '<S20>/Switch2' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Inport: '<Root>/Tel_Inp_UppSatLim'
   *  RelationalOperator: '<S20>/LowerRelop1'
   *  RelationalOperator: '<S20>/UpperRelop'
   *  Switch: '<S20>/Switch'
   */
  if (rtb_Add_d > rtTel_Inp_UppSatLim_SlipV1) {
    rtb_Add_d = rtTel_Inp_UppSatLim_SlipV1;
  } else if (rtb_Add_d < -70.0) {
    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    rtb_Add_d = -70.0;
  }

  /* Sum: '<S13>/Sum2' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   *  Product: '<S19>/Product'
   *  Switch: '<S20>/Switch2'
   */
  Vmax = rtb_Switch2_g * rtTel_Inp_SC_Kp_SlipV1 + rtb_Add_d;

  /* Switch: '<S15>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S15>/LowerRelop1'
   *  RelationalOperator: '<S15>/UpperRelop'
   *  Switch: '<S15>/Switch'
   */
  if (Vmax > rtTm_rr_SlipV1) {
    Vmax = rtTm_rr_SlipV1;
  } else if (Vmax < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S15>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    Vmax = rtTel_Inp_minT_SlipV1;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/map_sc'
   *  Outport: '<Root>/Tmax_rr_slip'
   */
  map(Vmax, rtTm_rr_SlipV1, rtmap_sc_SlipV1, &rtTmax_rr_slip_SlipV1);

  /* Switch: '<S14>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Outport: '<Root>/Tmax_rr_slip'
   *  RelationalOperator: '<S14>/LowerRelop1'
   *  RelationalOperator: '<S14>/UpperRelop'
   *  Switch: '<S14>/Switch'
   */
  if (rtb_Product_ik > rtTmax_rr_slip_SlipV1) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_SlipV1 = rtTmax_rr_slip_SlipV1;
  } else if (rtb_Product_ik < 0.0) {
    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV1 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S14>/Switch'
     */
    rtTm_rr_m_SlipV1 = rtb_Product_ik;
  }

  /* End of Switch: '<S14>/Switch2' */

  /* Product: '<S2>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product_ik = rtDriver_req_SlipV1 * rtTm_rl_SlipV1;

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/omega_rl'
   */
  rtb_Add_d = 0.203 * rtomega_rl_SlipV1;

  /* Sum: '<S2>/Add2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms_h = rtu_bar_SlipV1 - 0.605 * rtyaw_rate_SlipV1;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_vms_h), fabs(rtb_Add_d));
  if (Vmax > 1.0) {
    Vmax = fabs((rtb_vms_h - rtb_Add_d) / Vmax);
  } else {
    Vmax = fabs((rtb_vms_h - rtb_Add_d) * 2.0 / (Vmax * Vmax + 1.0));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_Switch2_g = rtTel_Inp_SC_LambdaRef_SlipV1 - Vmax;

  /* Product: '<S10>/Product' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   */
  rtb_Product_d = rtb_Switch2_g * rtTel_Inp_SC_Kp_SlipV1;

  /* Product: '<S9>/Product1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  Vmax = rtb_Switch2_g * rtTel_Inp_SC_Ki_SlipV1;

  /* Sum: '<S2>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_Add_d = rtb_Product_ik - rtTel_Inp_minT_SlipV1;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  if ((rtb_Add_d > 0.0) && (rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k <= 0))
  {
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g = 0.0;
  }

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtb_vms_h = 0.00025 * Vmax + rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g;

  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S12>/Constant'
   *  Inport: '<Root>/Tel_Inp_IntegralResetValue'
   *  Product: '<S9>/Product'
   *  RelationalOperator: '<S12>/Compare'
   */
  rtb_Switch2_g = (rtb_Add_d > 0.0 ? rtTel_Inp_IntegralResetValue_Sl : 0.0) +
    rtb_vms_h;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/Tel_Inp_UppSatLim'
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (rtb_Switch2_g > rtTel_Inp_UppSatLim_SlipV1) {
    rtb_Switch2_g = rtTel_Inp_UppSatLim_SlipV1;
  } else if (rtb_Switch2_g < -70.0) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    rtb_Switch2_g = -70.0;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Sum: '<S4>/Sum2' */
  rtb_Switch2_g += rtb_Product_d;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Switch2_g > rtTm_rl_SlipV1) {
    rtb_Switch2_g = rtTm_rl_SlipV1;
  } else if (rtb_Switch2_g < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    rtb_Switch2_g = rtTel_Inp_minT_SlipV1;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/map_sc'
   *  Outport: '<Root>/Tmax_rl_slip'
   */
  map(rtb_Switch2_g, rtTm_rl_SlipV1, rtmap_sc_SlipV1, &rtTmax_rl_slip_SlipV1);

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Outport: '<Root>/Tmax_rl_slip'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Product_ik > rtTmax_rl_slip_SlipV1) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_SlipV1 = rtTmax_rl_slip_SlipV1;
  } else if (rtb_Product_ik < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_SlipV1 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    rtTm_rl_a_SlipV1 = rtb_Product_ik;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE = 0.00025 * rtb_Rr +
    DiscreteTimeIntegrator1;
  if (rtb_vms > 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = 1;
  } else if (rtb_vms < 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = -1;
  } else if (rtb_vms == 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = 0;
  } else {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g = 0.00025 * Vmax + rtb_vms_h;
  if (rtb_Add_d > 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 1;
  } else if (rtb_Add_d < 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = -1;
  } else if (rtb_Add_d == 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 0;
  } else {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
}

/* Model initialize function */
void SlipV1_initialize(RT_MODEL_SlipV1 *const rtM_SlipV1)
{
  DW_SlipV1 *rtDW_SlipV1 = rtM_SlipV1->dwork;

  /* Registration code */

  /* Storage classes */
  rtDriver_req_SlipV1 = 0.0;
  rtu_bar_SlipV1 = 0.0;
  rtomega_rr_SlipV1 = 0.0;
  rtomega_rl_SlipV1 = 0.0;
  rtyaw_rate_SlipV1 = 0.0;
  rtSteeringangle_SlipV1 = 0.0;
  rtbrake_SlipV1 = 0.0;
  rtTm_rl_SlipV1 = 0.0;
  rtTm_rr_SlipV1 = 0.0;
  rtmap_tv_SlipV1 = 0.0;
  rtmap_sc_SlipV1 = 0.0;
  rtTel_Inp_SC_LambdaRef_SlipV1 = 0.0;
  rtTel_Inp_SC_Kp_SlipV1 = 0.0;
  rtTel_Inp_SC_Ki_SlipV1 = 0.0;
  rtTel_Inp_minT_SlipV1 = 0.0;
  rtTel_Inp_UppSatLim_SlipV1 = 0.0;
  rtTel_Inp_IntegralResetValue_Sl = 0.0;

  /* Storage classes */
  rtTm_rr_m_SlipV1 = 0.0;
  rtTm_rl_a_SlipV1 = 0.0;
  rtTel_Out_Debug_Torque_SlipV1 = 0.0;
  rtTmax_rr_slip_SlipV1 = 0.0;
  rtTmax_rl_slip_SlipV1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_SlipV1, 0,
                sizeof(DW_SlipV1));

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 2;

  /* ConstCode for Outport: '<Root>/Tel_Out_Debug_Torque' incorporates:
   *  Constant: '<S3>/Constant4'
   */
  rtTel_Out_Debug_Torque_SlipV1 = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
