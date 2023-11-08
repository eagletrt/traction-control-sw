/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.c
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.17
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Nov  6 16:53:02 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SlipV2.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_SlipV2;            /* '<Root>/driver_request' */
real_T rtSteeringangle_SlipV2;         /* '<Root>/delta' */
real_T rtTm_rl_SlipV2;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_SlipV2;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_SlipV2;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_SlipV2;               /* '<Root>/Tm_rr' */
real_T rtbrake_SlipV2;                 /* '<Root>/Brake' */
real_T rtmap_sc_SlipV2;                /* '<Root>/map_sc' */
real_T rtmap_tv_SlipV2;                /* '<Root>/map_tv' */
real_T rtomega_rl_SlipV2;              /* '<Root>/omega_rl' */
real_T rtomega_rr_SlipV2;              /* '<Root>/omega_rr' */
real_T rtu_bar_SlipV2;                 /* '<Root>/u_bar' */
real_T rtyaw_rate_SlipV2;              /* '<Root>/Omega' */
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
void SlipV2_step(RT_MODEL_SlipV2 *const rtM_SlipV2)
{
  DW_SlipV2 *rtDW_SlipV2 = rtM_SlipV2->dwork;
  real_T Vmax;
  real_T rtb_DeadZone;
  real_T rtb_Rr;
  real_T rtb_Sum;
  real_T rtb_vms;
  real_T rtb_vms_p;
  int8_T tmp;
  int8_T tmp_0;

  /* Gain: '<S3>/Rr' incorporates:
   *  Inport: '<Root>/omega_rr'
   */
  rtb_Rr = 0.203 * rtomega_rr_SlipV2;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtyaw_rate_SlipV2 + rtu_bar_SlipV2;

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
   *  Inport: '<Root>/map_tv'
   */
  rtb_DeadZone = rtmap_tv_SlipV2 - rtb_Rr;

  /* Product: '<S102>/PProd Out' incorporates:
   *  Constant: '<S3>/Constant5'
   */
  rtb_Sum = rtb_DeadZone * 200.0;

  /* Sum: '<S107>/Sum Fdbk' */
  Vmax = rtb_Sum + rtDW_SlipV2->Integrator_DSTATE;

  /* DeadZone: '<S90>/DeadZone' */
  if (Vmax > 100.0) {
    Vmax -= 100.0;
  } else if (Vmax >= 0.0) {
    Vmax = 0.0;
  }

  /* End of DeadZone: '<S90>/DeadZone' */

  /* Product: '<S94>/IProd Out' incorporates:
   *  Constant: '<S3>/Constant6'
   */
  rtb_DeadZone *= 850.0;

  /* Switch: '<S88>/Switch1' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   *  Constant: '<S88>/Constant'
   *  Constant: '<S88>/Constant2'
   *  RelationalOperator: '<S88>/fix for DT propagation issue'
   */
  if (Vmax > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S88>/Switch2' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   *  Constant: '<S88>/Constant3'
   *  Constant: '<S88>/Constant4'
   *  RelationalOperator: '<S88>/fix for DT propagation issue1'
   */
  if (rtb_DeadZone > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S88>/Switch' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   *  Constant: '<S88>/Constant1'
   *  Logic: '<S88>/AND3'
   *  RelationalOperator: '<S88>/Equal1'
   *  RelationalOperator: '<S88>/Relational Operator'
   *  Switch: '<S88>/Switch1'
   *  Switch: '<S88>/Switch2'
   */
  if ((Vmax != 0.0) && (tmp == tmp_0)) {
    rtb_Rr = 0.0;
  } else {
    rtb_Rr = rtb_DeadZone;
  }

  /* End of Switch: '<S88>/Switch' */

  /* DiscreteIntegrator: '<S97>/Integrator' */
  rtb_vms = 0.00025 * rtb_Rr + rtDW_SlipV2->Integrator_DSTATE;

  /* Sum: '<S106>/Sum' */
  Vmax = rtb_Sum + rtb_vms;

  /* Saturate: '<S104>/Saturation' */
  if (Vmax > 100.0) {
    Vmax = 100.0;
  } else if (Vmax < 0.0) {
    Vmax = 0.0;
  }

  /* End of Saturate: '<S104>/Saturation' */

  /* Switch: '<S61>/Switch2' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S61>/LowerRelop1'
   *  Switch: '<S61>/Switch'
   */
  if (Vmax > rtTm_rr_SlipV2) {
    rtb_Sum = rtTm_rr_SlipV2;
  } else {
    rtb_Sum = Vmax;
  }

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/map_sc'
   *  Switch: '<S61>/Switch2'
   */
  map(rtb_Sum, rtTm_rr_SlipV2, rtmap_sc_SlipV2, &Vmax);

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_DeadZone = rtDriver_req_SlipV2 * rtTm_rr_SlipV2;

  /* Switch: '<S60>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  RelationalOperator: '<S60>/LowerRelop1'
   *  RelationalOperator: '<S60>/UpperRelop'
   *  Switch: '<S60>/Switch'
   */
  if (rtb_DeadZone > Vmax) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_SlipV2 = Vmax;
  } else if (rtb_DeadZone < 0.0) {
    /* Switch: '<S60>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV2 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S60>/Switch'
     */
    rtTm_rr_m_SlipV2 = rtb_DeadZone;
  }

  /* End of Switch: '<S60>/Switch2' */

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/omega_rl'
   */
  rtb_DeadZone = 0.203 * rtomega_rl_SlipV2;

  /* Sum: '<S2>/Add2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms_p = rtu_bar_SlipV2 - 0.605 * rtyaw_rate_SlipV2;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_vms_p), fabs(rtb_DeadZone));
  if (Vmax > 1.0) {
    Vmax = fabs((rtb_vms_p - rtb_DeadZone) / Vmax);
  } else {
    Vmax = fabs((rtb_vms_p - rtb_DeadZone) * 2.0 / (Vmax * Vmax + 1.0));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/map_tv'
   */
  Vmax = rtmap_tv_SlipV2 - Vmax;

  /* Product: '<S47>/PProd Out' incorporates:
   *  Constant: '<S2>/Constant5'
   */
  rtb_Sum = Vmax * 200.0;

  /* Sum: '<S52>/Sum Fdbk' */
  rtb_DeadZone = rtb_Sum + rtDW_SlipV2->Integrator_DSTATE_o;

  /* DeadZone: '<S35>/DeadZone' */
  if (rtb_DeadZone > 100.0) {
    rtb_DeadZone -= 100.0;
  } else if (rtb_DeadZone >= 0.0) {
    rtb_DeadZone = 0.0;
  }

  /* End of DeadZone: '<S35>/DeadZone' */

  /* Product: '<S39>/IProd Out' incorporates:
   *  Constant: '<S2>/Constant6'
   */
  Vmax *= 850.0;

  /* Switch: '<S33>/Switch1' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S33>/Constant2'
   *  RelationalOperator: '<S33>/fix for DT propagation issue'
   */
  if (rtb_DeadZone > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S33>/Switch2' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant3'
   *  Constant: '<S33>/Constant4'
   *  RelationalOperator: '<S33>/fix for DT propagation issue1'
   */
  if (Vmax > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S33>/Switch' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant1'
   *  Logic: '<S33>/AND3'
   *  RelationalOperator: '<S33>/Equal1'
   *  RelationalOperator: '<S33>/Relational Operator'
   *  Switch: '<S33>/Switch1'
   *  Switch: '<S33>/Switch2'
   */
  if ((rtb_DeadZone != 0.0) && (tmp == tmp_0)) {
    rtb_DeadZone = 0.0;
  } else {
    rtb_DeadZone = Vmax;
  }

  /* End of Switch: '<S33>/Switch' */

  /* DiscreteIntegrator: '<S42>/Integrator' */
  rtb_vms_p = 0.00025 * rtb_DeadZone + rtDW_SlipV2->Integrator_DSTATE_o;

  /* Sum: '<S51>/Sum' */
  Vmax = rtb_Sum + rtb_vms_p;

  /* Saturate: '<S49>/Saturation' */
  if (Vmax > 100.0) {
    Vmax = 100.0;
  } else if (Vmax < 0.0) {
    Vmax = 0.0;
  }

  /* End of Saturate: '<S49>/Saturation' */

  /* Switch: '<S6>/Switch2' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  Switch: '<S6>/Switch'
   */
  if (Vmax > rtTm_rl_SlipV2) {
    rtb_Sum = rtTm_rl_SlipV2;
  } else {
    rtb_Sum = Vmax;
  }

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/map_sc'
   *  Switch: '<S6>/Switch2'
   */
  map(rtb_Sum, rtTm_rl_SlipV2, rtmap_sc_SlipV2, &Vmax);

  /* Product: '<S2>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Sum = rtDriver_req_SlipV2 * rtTm_rl_SlipV2;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Sum > Vmax) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_SlipV2 = Vmax;
  } else if (rtb_Sum < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_SlipV2 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    rtTm_rl_a_SlipV2 = rtb_Sum;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Update for DiscreteIntegrator: '<S97>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE = 0.00025 * rtb_Rr + rtb_vms;

  /* Update for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE_o = 0.00025 * rtb_DeadZone + rtb_vms_p;
}

/* Model initialize function */
void SlipV2_initialize(RT_MODEL_SlipV2 *const rtM_SlipV2)
{
  DW_SlipV2 *rtDW_SlipV2 = rtM_SlipV2->dwork;

  /* Registration code */

  /* Storage classes */
  rtDriver_req_SlipV2 = 0.0;
  rtu_bar_SlipV2 = 0.0;
  rtomega_rr_SlipV2 = 0.0;
  rtomega_rl_SlipV2 = 0.0;
  rtyaw_rate_SlipV2 = 0.0;
  rtSteeringangle_SlipV2 = 0.0;
  rtbrake_SlipV2 = 0.0;
  rtTm_rl_SlipV2 = 0.0;
  rtTm_rr_SlipV2 = 0.0;
  rtmap_tv_SlipV2 = 0.0;
  rtmap_sc_SlipV2 = 0.0;

  /* Storage classes */
  rtTm_rr_m_SlipV2 = 0.0;
  rtTm_rl_a_SlipV2 = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_SlipV2, 0,
                sizeof(DW_SlipV2));

  /* InitializeConditions for DiscreteIntegrator: '<S97>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE_o = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
