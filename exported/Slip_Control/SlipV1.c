/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1.c
 *
 * Code generated for Simulink model 'SlipV1'.
 *
 * Model version                  : 6.25
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  1 17:13:29 2024
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
real_T rtERROR_SlipV1;                 /* '<Root>/ERROR' */
real_T rtSteeringangle_SlipV1;         /* '<Root>/delta' */
real_T rtTel_Inp_SC_Ki_SlipV1;         /* '<Root>/Tel_Inp_SC_Ki' */
real_T rtTel_Inp_SC_Kp_SlipV1;         /* '<Root>/Tel_Inp_SC_Kp' */
real_T rtTel_Inp_SC_LambdaRef_SlipV1;  /* '<Root>/Tel_Inp_SC_LambdaRef' */
real_T rtTel_Inp_T0_SlipV1;            /* '<Root>/Tel_Inp_T0' */
real_T rtTel_Inp_Vramp_SlipV1;         /* '<Root>/Tel_Inp_Vramp' */
real_T rtTel_Inp_minT_SlipV1;          /* '<Root>/Tel_Inp_minT' */
real_T rtTm_rl_SlipV1;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_SlipV1;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_SlipV1;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_SlipV1;               /* '<Root>/Tm_rr' */
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
  real_T Integrator;
  real_T Integrator_n;
  real_T Vmax;
  real_T rtb_Add;
  real_T rtb_Add_d;
  real_T rtb_IProdOut;
  real_T rtb_Product_o;
  real_T rtb_Rr;
  real_T rtb_Sum;
  real_T rtb_vms;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_fixforDTpropagationissue;

  /* Gain: '<S3>/Rr' incorporates:
   *  Inport: '<Root>/omega_rr'
   */
  rtb_Rr = rtP_SlipV1.controlData.Rr * rtomega_rr_SlipV1;

  /* Gain: '<S3>/Wr//2' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   */
  rtb_Product_o = rtP_SlipV1.controlData.Wr / 2.0 * rtyaw_rate_SlipV1;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = rtb_Product_o + rtu_bar_SlipV1;

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

  /* Product: '<S102>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   */
  rtb_Sum = rtb_Rr * rtTel_Inp_SC_Kp_SlipV1;

  /* Sum: '<S107>/Sum Fdbk' */
  rtb_IProdOut = rtb_Sum + rtDW_SlipV1->Integrator_DSTATE;

  /* DeadZone: '<S90>/DeadZone' */
  if (rtb_IProdOut > rtP_SlipV1.DiscreteVaryingPID_UpperSaturat) {
    rtb_IProdOut -= rtP_SlipV1.DiscreteVaryingPID_UpperSaturat;
  } else if (rtb_IProdOut >= rtP_SlipV1.DiscreteVaryingPID_LowerSaturat) {
    rtb_IProdOut = 0.0;
  } else {
    rtb_IProdOut -= rtP_SlipV1.DiscreteVaryingPID_LowerSaturat;
  }

  /* End of DeadZone: '<S90>/DeadZone' */

  /* RelationalOperator: '<S88>/Relational Operator' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   */
  rtb_RelationalOperator = (rtP_SlipV1.Clamping_zero_Value != rtb_IProdOut);

  /* RelationalOperator: '<S88>/fix for DT propagation issue' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (rtb_IProdOut > rtP_SlipV1.Clamping_zero_Value);

  /* Product: '<S94>/IProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  rtb_IProdOut = rtb_Rr * rtTel_Inp_SC_Ki_SlipV1;

  /* Switch: '<S88>/Switch1' incorporates:
   *  Constant: '<S88>/Constant'
   *  Constant: '<S88>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
    tmp = rtP_SlipV1.Constant_Value_n;
  } else {
    tmp = rtP_SlipV1.Constant2_Value_i;
  }

  /* Switch: '<S88>/Switch2' incorporates:
   *  Constant: '<S88>/Clamping_zero'
   *  Constant: '<S88>/Constant3'
   *  Constant: '<S88>/Constant4'
   *  RelationalOperator: '<S88>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > rtP_SlipV1.Clamping_zero_Value) {
    tmp_0 = rtP_SlipV1.Constant3_Value_l;
  } else {
    tmp_0 = rtP_SlipV1.Constant4_Value_f;
  }

  /* Switch: '<S88>/Switch' incorporates:
   *  Constant: '<S88>/Constant1'
   *  Logic: '<S88>/AND3'
   *  RelationalOperator: '<S88>/Equal1'
   *  Switch: '<S88>/Switch1'
   *  Switch: '<S88>/Switch2'
   */
  if (rtb_RelationalOperator && (tmp == tmp_0)) {
    rtb_vms = rtP_SlipV1.Constant1_Value_d;
  } else {
    rtb_vms = rtb_IProdOut;
  }

  /* End of Switch: '<S88>/Switch' */

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_IProdOut = rtDriver_req_SlipV1 * rtTm_rr_SlipV1;

  /* Sum: '<S3>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_Add = rtb_IProdOut - rtTel_Inp_minT_SlipV1;

  /* DiscreteIntegrator: '<S97>/Integrator' */
  if ((rtb_Add > 0.0) && (rtDW_SlipV1->Integrator_PrevResetState <= 0)) {
    rtDW_SlipV1->Integrator_DSTATE = rtP_SlipV1.DiscreteVaryingPID_InitialCondi;
  }

  rtb_vms *= rtP_SlipV1.Integrator_gainval;

  /* DiscreteIntegrator: '<S97>/Integrator' */
  Integrator = rtb_vms + rtDW_SlipV1->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S97>/Integrator' */
  if (Integrator > rtP_SlipV1.DiscreteVaryingPID_UpperIntegra) {
    /* DiscreteIntegrator: '<S97>/Integrator' */
    Integrator = rtP_SlipV1.DiscreteVaryingPID_UpperIntegra;
  } else if (Integrator < rtP_SlipV1.DiscreteVaryingPID_LowerIntegra) {
    /* DiscreteIntegrator: '<S97>/Integrator' */
    Integrator = rtP_SlipV1.DiscreteVaryingPID_LowerIntegra;
  }

  /* Sum: '<S106>/Sum' */
  Vmax = rtb_Sum + Integrator;

  /* Saturate: '<S104>/Saturation' */
  if (Vmax > rtP_SlipV1.DiscreteVaryingPID_UpperSaturat) {
    Vmax = rtP_SlipV1.DiscreteVaryingPID_UpperSaturat;
  } else if (Vmax < rtP_SlipV1.DiscreteVaryingPID_LowerSaturat) {
    Vmax = rtP_SlipV1.DiscreteVaryingPID_LowerSaturat;
  }

  /* End of Saturate: '<S104>/Saturation' */

  /* Switch: '<S61>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S61>/LowerRelop1'
   *  RelationalOperator: '<S61>/UpperRelop'
   *  Switch: '<S61>/Switch'
   */
  if (Vmax > rtTm_rr_SlipV1) {
    rtb_Sum = rtTm_rr_SlipV1;
  } else if (Vmax < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S61>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    rtb_Sum = rtTel_Inp_minT_SlipV1;
  } else {
    rtb_Sum = Vmax;
  }

  /* MATLAB Function: '<S3>/map' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/map_sc'
   *  Switch: '<S61>/Switch2'
   */
  map(rtb_Sum, rtTm_rr_SlipV1, rtmap_sc_SlipV1, &Vmax);

  /* Switch: '<S60>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  RelationalOperator: '<S60>/LowerRelop1'
   *  RelationalOperator: '<S60>/UpperRelop'
   *  Switch: '<S60>/Switch'
   */
  if (rtb_IProdOut > Vmax) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_SlipV1 = Vmax;
  } else if (rtb_IProdOut < rtP_SlipV1.Constant2_Value_l) {
    /* Switch: '<S60>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV1 = rtP_SlipV1.Constant2_Value_l;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S60>/Switch'
     */
    rtTm_rr_m_SlipV1 = rtb_IProdOut;
  }

  /* End of Switch: '<S60>/Switch2' */

  /* Gain: '<S2>/Rr' incorporates:
   *  Inport: '<Root>/omega_rl'
   */
  rtb_Sum = rtP_SlipV1.controlData.Rr * rtomega_rl_SlipV1;

  /* Sum: '<S2>/Add2' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  rtb_IProdOut = rtu_bar_SlipV1 - rtb_Product_o;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  Vmax = fmax(fabs(rtb_IProdOut), fabs(rtb_Sum));
  if (Vmax > rtP_SlipV1.controlData.Vlow) {
    Vmax = fabs((rtb_IProdOut - rtb_Sum) / Vmax);
  } else {
    Vmax = fabs((rtb_IProdOut - rtb_Sum) * 2.0 / (Vmax * Vmax /
      rtP_SlipV1.controlData.Vlow + rtP_SlipV1.controlData.Vlow));
  }

  /* End of MATLAB Function: '<S2>/Slip_est1' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_LambdaRef'
   */
  rtb_IProdOut = rtTel_Inp_SC_LambdaRef_SlipV1 - Vmax;

  /* Product: '<S47>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Kp'
   */
  rtb_Sum = rtb_IProdOut * rtTel_Inp_SC_Kp_SlipV1;

  /* Sum: '<S52>/Sum Fdbk' */
  Vmax = rtb_Sum + rtDW_SlipV1->Integrator_DSTATE_o;

  /* DeadZone: '<S35>/DeadZone' */
  if (Vmax > rtP_SlipV1.DiscreteVaryingPID_UpperSatur_f) {
    Vmax -= rtP_SlipV1.DiscreteVaryingPID_UpperSatur_f;
  } else if (Vmax >= rtP_SlipV1.DiscreteVaryingPID_LowerSatur_b) {
    Vmax = 0.0;
  } else {
    Vmax -= rtP_SlipV1.DiscreteVaryingPID_LowerSatur_b;
  }

  /* End of DeadZone: '<S35>/DeadZone' */

  /* Product: '<S39>/IProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_SC_Ki'
   */
  rtb_IProdOut *= rtTel_Inp_SC_Ki_SlipV1;

  /* Switch: '<S33>/Switch1' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S33>/Constant2'
   *  RelationalOperator: '<S33>/fix for DT propagation issue'
   */
  if (Vmax > rtP_SlipV1.Clamping_zero_Value_c) {
    tmp = rtP_SlipV1.Constant_Value;
  } else {
    tmp = rtP_SlipV1.Constant2_Value_a;
  }

  /* Switch: '<S33>/Switch2' incorporates:
   *  Constant: '<S33>/Clamping_zero'
   *  Constant: '<S33>/Constant3'
   *  Constant: '<S33>/Constant4'
   *  RelationalOperator: '<S33>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > rtP_SlipV1.Clamping_zero_Value_c) {
    tmp_0 = rtP_SlipV1.Constant3_Value;
  } else {
    tmp_0 = rtP_SlipV1.Constant4_Value;
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
  if ((rtP_SlipV1.Clamping_zero_Value_c != Vmax) && (tmp == tmp_0)) {
    rtb_IProdOut = rtP_SlipV1.Constant1_Value;
  }

  /* End of Switch: '<S33>/Switch' */

  /* Product: '<S2>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product_o = rtDriver_req_SlipV1 * rtTm_rl_SlipV1;

  /* Sum: '<S2>/Add' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   */
  rtb_Add_d = rtb_Product_o - rtTel_Inp_minT_SlipV1;

  /* DiscreteIntegrator: '<S42>/Integrator' */
  if ((rtb_Add_d > 0.0) && (rtDW_SlipV1->Integrator_PrevResetState_p <= 0)) {
    rtDW_SlipV1->Integrator_DSTATE_o =
      rtP_SlipV1.DiscreteVaryingPID_InitialCon_o;
  }

  rtb_IProdOut *= rtP_SlipV1.Integrator_gainval_i;

  /* DiscreteIntegrator: '<S42>/Integrator' */
  Integrator_n = rtb_IProdOut + rtDW_SlipV1->Integrator_DSTATE_o;

  /* DiscreteIntegrator: '<S42>/Integrator' */
  if (Integrator_n > rtP_SlipV1.DiscreteVaryingPID_UpperInteg_m) {
    /* DiscreteIntegrator: '<S42>/Integrator' */
    Integrator_n = rtP_SlipV1.DiscreteVaryingPID_UpperInteg_m;
  } else if (Integrator_n < rtP_SlipV1.DiscreteVaryingPID_LowerInteg_d) {
    /* DiscreteIntegrator: '<S42>/Integrator' */
    Integrator_n = rtP_SlipV1.DiscreteVaryingPID_LowerInteg_d;
  }

  /* Sum: '<S51>/Sum' */
  Vmax = rtb_Sum + Integrator_n;

  /* Saturate: '<S49>/Saturation' */
  if (Vmax > rtP_SlipV1.DiscreteVaryingPID_UpperSatur_f) {
    Vmax = rtP_SlipV1.DiscreteVaryingPID_UpperSatur_f;
  } else if (Vmax < rtP_SlipV1.DiscreteVaryingPID_LowerSatur_b) {
    Vmax = rtP_SlipV1.DiscreteVaryingPID_LowerSatur_b;
  }

  /* End of Saturate: '<S49>/Saturation' */

  /* Switch: '<S6>/Switch2' incorporates:
   *  Inport: '<Root>/Tel_Inp_minT'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (Vmax > rtTm_rl_SlipV1) {
    rtb_Sum = rtTm_rl_SlipV1;
  } else if (Vmax < rtTel_Inp_minT_SlipV1) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Inport: '<Root>/Tel_Inp_minT'
     */
    rtb_Sum = rtTel_Inp_minT_SlipV1;
  } else {
    rtb_Sum = Vmax;
  }

  /* MATLAB Function: '<S2>/map' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/map_sc'
   *  Switch: '<S6>/Switch2'
   */
  map(rtb_Sum, rtTm_rl_SlipV1, rtmap_sc_SlipV1, &Vmax);

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Product_o > Vmax) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_SlipV1 = Vmax;
  } else if (rtb_Product_o < rtP_SlipV1.Constant2_Value) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_SlipV1 = rtP_SlipV1.Constant2_Value;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    rtTm_rl_a_SlipV1 = rtb_Product_o;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Outport: '<Root>/ERROR' */
  rtERROR_SlipV1 = rtb_Rr;

  /* Update for DiscreteIntegrator: '<S97>/Integrator' */
  rtDW_SlipV1->Integrator_DSTATE = rtb_vms + Integrator;
  if (rtDW_SlipV1->Integrator_DSTATE >
      rtP_SlipV1.DiscreteVaryingPID_UpperIntegra) {
    rtDW_SlipV1->Integrator_DSTATE = rtP_SlipV1.DiscreteVaryingPID_UpperIntegra;
  } else if (rtDW_SlipV1->Integrator_DSTATE <
             rtP_SlipV1.DiscreteVaryingPID_LowerIntegra) {
    rtDW_SlipV1->Integrator_DSTATE = rtP_SlipV1.DiscreteVaryingPID_LowerIntegra;
  }

  if (rtb_Add > 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState = 1;
  } else if (rtb_Add < 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState = -1;
  } else if (rtb_Add == 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState = 0;
  } else {
    rtDW_SlipV1->Integrator_PrevResetState = 2;
  }

  /* Update for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW_SlipV1->Integrator_DSTATE_o = rtb_IProdOut + Integrator_n;
  if (rtDW_SlipV1->Integrator_DSTATE_o >
      rtP_SlipV1.DiscreteVaryingPID_UpperInteg_m) {
    rtDW_SlipV1->Integrator_DSTATE_o =
      rtP_SlipV1.DiscreteVaryingPID_UpperInteg_m;
  } else if (rtDW_SlipV1->Integrator_DSTATE_o <
             rtP_SlipV1.DiscreteVaryingPID_LowerInteg_d) {
    rtDW_SlipV1->Integrator_DSTATE_o =
      rtP_SlipV1.DiscreteVaryingPID_LowerInteg_d;
  }

  if (rtb_Add_d > 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState_p = 1;
  } else if (rtb_Add_d < 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState_p = -1;
  } else if (rtb_Add_d == 0.0) {
    rtDW_SlipV1->Integrator_PrevResetState_p = 0;
  } else {
    rtDW_SlipV1->Integrator_PrevResetState_p = 2;
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
  rtTel_Inp_T0_SlipV1 = 0.0;
  rtTel_Inp_Vramp_SlipV1 = 0.0;

  /* Storage classes */
  rtTm_rr_m_SlipV1 = 0.0;
  rtTm_rl_a_SlipV1 = 0.0;
  rtERROR_SlipV1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_SlipV1, 0,
                sizeof(DW_SlipV1));

  /* InitializeConditions for DiscreteIntegrator: '<S97>/Integrator' */
  rtDW_SlipV1->Integrator_DSTATE = rtP_SlipV1.DiscreteVaryingPID_InitialCondi;
  rtDW_SlipV1->Integrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW_SlipV1->Integrator_DSTATE_o = rtP_SlipV1.DiscreteVaryingPID_InitialCon_o;
  rtDW_SlipV1->Integrator_PrevResetState_p = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
