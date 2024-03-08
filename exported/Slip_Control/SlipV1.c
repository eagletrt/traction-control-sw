/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1.c
 *
 * Code generated for Simulink model 'SlipV1'.
 *
 * Model version                  : 6.31
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  8 13:25:54 2024
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
  real_T DiscreteTimeIntegrator1_tmp;
  real_T Vmax;
  real_T rtb_Product;
  real_T rtb_Product_ik;
  real_T rtb_Rr;
  real_T rtb_Rr_j;
  real_T rtb_error;
  real_T rtb_vms;

  /* Gain: '<S3>/Rr' incorporates:
   *  Inport: '<Root>/omega_rr'
   */
  rtb_Rr = rtP_SlipV1.controlData.Rr * rtomega_rr_SlipV1;

  /* Gain: '<S3>/Wr//2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   */
  rtb_error = rtP_SlipV1.controlData.Wr / 2.0 * rtyaw_rate_SlipV1;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = rtb_error + rtu_bar_SlipV1;

  /* MATLAB Function: '<S3>/Slip_est1' incorporates:
   *  Constant: '<S3>/Constant'
   */
  Vmax = fmax(fabs(rtb_vms), fabs(rtb_Rr));
  if (Vmax > rtP_SlipV1.controlData.Vlow) {
    rtb_Rr = fabs((rtb_vms - rtb_Rr) / Vmax);
  } else {
    rtb_Rr = fabs((rtb_vms - rtb_Rr) * 2.0 / (Vmax * Vmax /
      rtP_SlipV1.controlData.Vlow + rtP_SlipV1.controlData.Vlow));
  }

  /* End of MATLAB Function: '<S3>/Slip_est1' */

  /* Sum: '<S3>/Add1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_Rr = rtTel_Inp_SC_LambdaRef_SlipV1 - rtb_Rr;

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product_ik = rtDriver_req_SlipV1 * rtTm_rr_SlipV1;

  /* Sum: '<S3>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_vms = rtb_Product_ik - rtTel_Inp_minT_SlipV1;

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   *  Product: '<S18>/Product1'
   */
  if ((rtb_vms > 0.0) && (rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes <= 0)) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE =
      rtP_SlipV1.DiscreteTimeIntegrator1_IC;
  }

  DiscreteTimeIntegrator1_tmp = rtb_Rr * rtTel_Inp_SC_Ki_SlipV1 *
    rtP_SlipV1.DiscreteTimeIntegrator1_gainval;

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = DiscreteTimeIntegrator1_tmp +
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S18>/Add' incorporates:
   *  Constant: '<S21>/Constant'
   *  Inport: '<Root>/Tel_Inp_IntegralResetValue'
   *  Product: '<S18>/Product'
   *  RelationalOperator: '<S21>/Compare'
   */
  Vmax = (rtb_vms > rtP_SlipV1.Constant_Value_h ?
          rtTel_Inp_IntegralResetValue_Sl : 0.0) + DiscreteTimeIntegrator1;

  /* Switch: '<S20>/Switch2' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Inport: '<Root>/Tel_Inp_UppSatLim'
   *  RelationalOperator: '<S20>/LowerRelop1'
   *  RelationalOperator: '<S20>/UpperRelop'
   *  Switch: '<S20>/Switch'
   */
  if (Vmax > rtTel_Inp_UppSatLim_SlipV1) {
    Vmax = rtTel_Inp_UppSatLim_SlipV1;
  } else if (Vmax < rtP_SlipV1.Constant3_Value_h) {
    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    Vmax = rtP_SlipV1.Constant3_Value_h;
  }

  /* Sum: '<S13>/Sum2' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   *  Product: '<S19>/Product'
   *  Switch: '<S20>/Switch2'
   */
  rtb_Product = rtb_Rr * rtTel_Inp_SC_Kp_SlipV1 + Vmax;

  /* Switch: '<S15>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S15>/LowerRelop1'
   *  RelationalOperator: '<S15>/UpperRelop'
   *  Switch: '<S15>/Switch'
   */
  if (rtb_Product > rtTm_rr_SlipV1) {
    rtb_Product = rtTm_rr_SlipV1;
  } else if (rtb_Product < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S15>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    rtb_Product = rtTel_Inp_minT_SlipV1;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/map_sc'
   *  Outport: '<Root>/Tmax_rr_slip'
   */
  map(rtb_Product, rtTm_rr_SlipV1, rtmap_sc_SlipV1, &rtTmax_rr_slip_SlipV1);

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
  } else if (rtb_Product_ik < rtP_SlipV1.Constant2_Value_l) {
    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV1 = rtP_SlipV1.Constant2_Value_l;
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

  /* Sum: '<S2>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_Product = rtb_Product_ik - rtTel_Inp_minT_SlipV1;

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/omega_rl'
   */
  rtb_Rr_j = rtP_SlipV1.controlData.Rr * rtomega_rl_SlipV1;

  /* Sum: '<S2>/Add2' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  rtb_Rr = rtu_bar_SlipV1 - rtb_error;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_Rr), fabs(rtb_Rr_j));
  if (Vmax > rtP_SlipV1.controlData.Vlow) {
    Vmax = fabs((rtb_Rr - rtb_Rr_j) / Vmax);
  } else {
    Vmax = fabs((rtb_Rr - rtb_Rr_j) * 2.0 / (Vmax * Vmax /
      rtP_SlipV1.controlData.Vlow + rtP_SlipV1.controlData.Vlow));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_error = rtTel_Inp_SC_LambdaRef_SlipV1 - Vmax;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   *  Product: '<S9>/Product1'
   */
  if ((rtb_Product > 0.0) && (rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k <= 0))
  {
    rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g =
      rtP_SlipV1.DiscreteTimeIntegrator1_IC_o;
  }

  Vmax = rtb_error * rtTel_Inp_SC_Ki_SlipV1 *
    rtP_SlipV1.DiscreteTimeIntegrator1_gainv_l;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtb_Rr_j = Vmax + rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g;

  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S12>/Constant'
   *  Inport: '<Root>/Tel_Inp_IntegralResetValue'
   *  Product: '<S9>/Product'
   *  RelationalOperator: '<S12>/Compare'
   */
  rtb_Rr = (rtb_Product > rtP_SlipV1.Constant_Value ?
            rtTel_Inp_IntegralResetValue_Sl : 0.0) + rtb_Rr_j;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Inport: '<Root>/Tel_Inp_UppSatLim'
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (rtb_Rr > rtTel_Inp_UppSatLim_SlipV1) {
    rtb_Rr = rtTel_Inp_UppSatLim_SlipV1;
  } else if (rtb_Rr < rtP_SlipV1.Constant3_Value) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    rtb_Rr = rtP_SlipV1.Constant3_Value;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Sum: '<S4>/Sum2' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   *  Product: '<S10>/Product'
   */
  rtb_Rr += rtb_error * rtTel_Inp_SC_Kp_SlipV1;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Rr > rtTm_rl_SlipV1) {
    rtb_Rr = rtTm_rl_SlipV1;
  } else if (rtb_Rr < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    rtb_Rr = rtTel_Inp_minT_SlipV1;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/map_sc'
   *  Outport: '<Root>/Tmax_rl_slip'
   */
  map(rtb_Rr, rtTm_rl_SlipV1, rtmap_sc_SlipV1, &rtTmax_rl_slip_SlipV1);

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
  } else if (rtb_Product_ik < rtP_SlipV1.Constant2_Value) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_SlipV1 = rtP_SlipV1.Constant2_Value;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    rtTm_rl_a_SlipV1 = rtb_Product_ik;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Outport: '<Root>/Tel_Out_Debug_Torque' incorporates:
   *  Constant: '<S3>/Constant4'
   */
  rtTel_Out_Debug_Torque_SlipV1 = rtP_SlipV1.Constant4_Value;

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE = DiscreteTimeIntegrator1_tmp +
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

  /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g = Vmax + rtb_Rr_j;
  if (rtb_Product > 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 1;
  } else if (rtb_Product < 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = -1;
  } else if (rtb_Product == 0.0) {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 0;
  } else {
    rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 2;
  }
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
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTATE =
    rtP_SlipV1.DiscreteTimeIntegrator1_IC;
  rtDW_SlipV1->DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW_SlipV1->DiscreteTimeIntegrator1_DSTAT_g =
    rtP_SlipV1.DiscreteTimeIntegrator1_IC_o;
  rtDW_SlipV1->DiscreteTimeIntegrator1_PrevR_k = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
