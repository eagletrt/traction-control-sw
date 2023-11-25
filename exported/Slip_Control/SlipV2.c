/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.c
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.29
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Nov 25 17:00:43 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SlipV2.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_SlipV2;            /* '<Root>/driver_request' */
real_T rtERROR_SlipV2;                 /* '<Root>/ERROR' */
real_T rtSteeringangle_SlipV2;         /* '<Root>/delta' */
real_T rtTel_Inp_SC_Ki_SlipV2;         /* '<Root>/Tel_Inp_SC_Ki' */
real_T rtTel_Inp_SC_Kp_SlipV2;         /* '<Root>/Tel_Inp_SC_Kp' */
real_T rtTel_Inp_SC_LambdaRef_SlipV2;  /* '<Root>/Tel_Inp_SC_LambdaRef' */
real_T rtTel_Inp_SC_SpeedCutoff_SlipV2;/* '<Root>/Tel_Inp_SC_SpeedCutoff' */
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

/* Model step function */
void SlipV2_step(RT_MODEL_SlipV2 *const rtM_SlipV2)
{
  DW_SlipV2 *rtDW_SlipV2 = rtM_SlipV2->dwork;
  real_T Integrator;
  real_T Vmax;
  real_T rtb_Rr;
  real_T rtb_Rr_e;
  real_T rtb_Sum;
  real_T rtb_Switch;
  real_T rtb_vms;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_fixforDTpropagationissue;

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
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_Rr = rtTel_Inp_SC_LambdaRef_SlipV2 - rtb_Rr;

  /* Product: '<S102>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   */
  rtb_Sum = rtb_Rr * rtTel_Inp_SC_Kp_SlipV2;

  /* Sum: '<S107>/Sum Fdbk' */
  Vmax = rtb_Sum + rtDW_SlipV2->Integrator_DSTATE;

  /* DeadZone: '<S90>/DeadZone' */
  if (Vmax > 100.0) {
    Vmax -= 100.0;
  } else if (Vmax >= 0.0) {
    Vmax = 0.0;
  }

  /* End of DeadZone: '<S90>/DeadZone' */

  /* RelationalOperator: '<S88>/Relational Operator' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   */
  rtb_RelationalOperator = (Vmax != 0.0);

  /* RelationalOperator: '<S88>/fix for DT propagation issue' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (Vmax > 0.0);

  /* Product: '<S94>/IProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  Vmax = rtb_Rr * rtTel_Inp_SC_Ki_SlipV2;

  /* Switch: '<S88>/Switch1' incorporates:
   *  Constant: '<S88>/Constant'
   *  Constant: '<S88>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
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
  if (Vmax > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S88>/Switch' incorporates:
   *  Constant: '<S88>/Constant1'
   *  Logic: '<S88>/AND3'
   *  RelationalOperator: '<S88>/Equal1'
   *  Switch: '<S88>/Switch1'
   *  Switch: '<S88>/Switch2'
   */
  if (rtb_RelationalOperator && (tmp == tmp_0)) {
    rtb_Switch = 0.0;
  } else {
    rtb_Switch = Vmax;
  }

  /* End of Switch: '<S88>/Switch' */

  /* DiscreteIntegrator: '<S97>/Integrator' */
  Integrator = 0.00025 * rtb_Switch + rtDW_SlipV2->Integrator_DSTATE;

  /* Sum: '<S106>/Sum' */
  Vmax = rtb_Sum + Integrator;

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
   */
  if (Vmax > rtTm_rr_SlipV2) {
    Vmax = rtTm_rr_SlipV2;
  }

  /* End of Switch: '<S61>/Switch2' */

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_SpeedCutoff'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/map_sc'
   */
  rtb_vms = (1.0 - fmin(fmax(rtb_vms / rtTel_Inp_SC_SpeedCutoff_SlipV2 *
    rtmap_sc_SlipV2, 0.0), 1.0)) * (rtTm_rr_SlipV2 - Vmax) + Vmax;

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  Vmax = rtDriver_req_SlipV2 * rtTm_rr_SlipV2;

  /* Switch: '<S60>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  RelationalOperator: '<S60>/LowerRelop1'
   *  RelationalOperator: '<S60>/UpperRelop'
   *  Switch: '<S60>/Switch'
   */
  if (Vmax > rtb_vms) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_SlipV2 = rtb_vms;
  } else if (Vmax < 0.0) {
    /* Switch: '<S60>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV2 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S60>/Switch'
     */
    rtTm_rr_m_SlipV2 = Vmax;
  }

  /* End of Switch: '<S60>/Switch2' */

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/omega_rl'
   */
  rtb_Rr_e = 0.203 * rtomega_rl_SlipV2;

  /* Sum: '<S2>/Add2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = rtu_bar_SlipV2 - 0.605 * rtyaw_rate_SlipV2;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_vms), fabs(rtb_Rr_e));
  if (Vmax > 1.0) {
    Vmax = fabs((rtb_vms - rtb_Rr_e) / Vmax);
  } else {
    Vmax = fabs((rtb_vms - rtb_Rr_e) * 2.0 / (Vmax * Vmax + 1.0));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  Vmax = rtTel_Inp_SC_LambdaRef_SlipV2 - Vmax;

  /* Product: '<S47>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   */
  rtb_Sum = Vmax * rtTel_Inp_SC_Kp_SlipV2;

  /* Sum: '<S52>/Sum Fdbk' */
  rtb_Rr_e = rtb_Sum + rtDW_SlipV2->Integrator_DSTATE_o;

  /* DeadZone: '<S35>/DeadZone' */
  if (rtb_Rr_e > 100.0) {
    rtb_Rr_e -= 100.0;
  } else if (rtb_Rr_e >= 0.0) {
    rtb_Rr_e = 0.0;
  }

  /* End of DeadZone: '<S35>/DeadZone' */

  /* Product: '<S39>/IProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  Vmax *= rtTel_Inp_SC_Ki_SlipV2;

  /* Switch: '<S33>/Switch1' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S33>/Constant2'
   *  RelationalOperator: '<S33>/fix for DT propagation issue'
   */
  if (rtb_Rr_e > 0.0) {
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
  if ((rtb_Rr_e != 0.0) && (tmp == tmp_0)) {
    Vmax = 0.0;
  }

  /* End of Switch: '<S33>/Switch' */

  /* DiscreteIntegrator: '<S42>/Integrator' */
  rtb_Rr_e = 0.00025 * Vmax + rtDW_SlipV2->Integrator_DSTATE_o;

  /* Sum: '<S51>/Sum' */
  rtb_Sum += rtb_Rr_e;

  /* Saturate: '<S49>/Saturation' */
  if (rtb_Sum > 100.0) {
    rtb_Sum = 100.0;
  } else if (rtb_Sum < 0.0) {
    rtb_Sum = 0.0;
  }

  /* End of Saturate: '<S49>/Saturation' */

  /* Switch: '<S6>/Switch2' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   */
  if (rtb_Sum > rtTm_rl_SlipV2) {
    rtb_Sum = rtTm_rl_SlipV2;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_SpeedCutoff'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/map_sc'
   */
  rtb_vms = (1.0 - fmin(fmax(rtb_vms / rtTel_Inp_SC_SpeedCutoff_SlipV2 *
    rtmap_sc_SlipV2, 0.0), 1.0)) * (rtTm_rl_SlipV2 - rtb_Sum) + rtb_Sum;

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
  if (rtb_Sum > rtb_vms) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_SlipV2 = rtb_vms;
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

  /* Outport: '<Root>/ERROR' */
  rtERROR_SlipV2 = rtb_Rr;

  /* Update for DiscreteIntegrator: '<S97>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE = 0.00025 * rtb_Switch + Integrator;

  /* Update for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW_SlipV2->Integrator_DSTATE_o = 0.00025 * Vmax + rtb_Rr_e;
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
  rtTel_Inp_SC_LambdaRef_SlipV2 = 0.0;
  rtTel_Inp_SC_Kp_SlipV2 = 0.0;
  rtTel_Inp_SC_Ki_SlipV2 = 0.0;
  rtTel_Inp_SC_SpeedCutoff_SlipV2 = 0.0;

  /* Storage classes */
  rtTm_rr_m_SlipV2 = 0.0;
  rtTm_rl_a_SlipV2 = 0.0;
  rtERROR_SlipV2 = 0.0;

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
