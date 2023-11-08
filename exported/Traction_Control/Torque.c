/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.17
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Nov  6 16:49:11 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Torque.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_Torque;            /* '<Root>/driver_request' */
real_T rtSteeringangle_Torque;         /* '<Root>/delta' */
real_T rtTm_rl_Torque;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_Torque;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_Torque;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_Torque;               /* '<Root>/Tm_rr' */
real_T rtbrake_Torque;                 /* '<Root>/Brake' */
real_T rtmap_sc_Torque;                /* '<Root>/map_sc' */
real_T rtmap_tv_Torque;                /* '<Root>/map_tv' */
real_T rtomega_rl_Torque;              /* '<Root>/omega_rl' */
real_T rtomega_rr_Torque;              /* '<Root>/omega_rr' */
real_T rtu_bar_Torque;                 /* '<Root>/u_bar' */
real_T rtyaw_rate_Torque;              /* '<Root>/Omega' */
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Model step function */
void Torque_step(RT_MODEL_Torque *const rtM_Torque)
{
  DW_Torque *rtDW_Torque = rtM_Torque->dwork;
  real_T rtb_Gain_m;
  real_T rtb_IProdOut;
  real_T rtb_PProdOut;
  real_T rtb_SumFdbk;
  real_T rtb_Switch2_ou;
  real_T rtb_T_diff_k;
  real_T rtb_T_rr;
  real_T rtb_delta_F;
  real_T rtb_delta_F_tmp;
  int8_T tmp;
  int8_T tmp_0;

  /* MATLAB Function: '<S2>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtSteeringangle_Torque, 10.0);
  rtb_SumFdbk = pow(rtSteeringangle_Torque, 9.0);
  rtb_T_diff_k = pow(rtSteeringangle_Torque, 8.0);
  rtb_delta_F = pow(rtSteeringangle_Torque, 7.0);
  rtb_T_rr = pow(rtSteeringangle_Torque, 6.0);
  rtb_Switch2_ou = pow(rtSteeringangle_Torque, 5.0);
  rtb_Gain_m = pow(rtSteeringangle_Torque, 4.0);
  rtb_PProdOut = pow(rtSteeringangle_Torque, 3.0);
  rtb_delta_F_tmp = rtSteeringangle_Torque * rtSteeringangle_Torque;
  rtb_delta_F = (((((((((((-3.534335194E-8 * rtb_IProdOut + 1.618153531E-7 *
    rtb_SumFdbk) - 3.16758626E-7 * rtb_T_diff_k) + 1.704839325E-6 * rtb_delta_F)
                        - 8.483242635E-6 * rtb_T_rr) + 5.3472838E-5 *
                       rtb_Switch2_ou) - 0.0002074730388 * rtb_Gain_m) +
                     0.001981845031 * rtb_PProdOut) - rtb_delta_F_tmp *
                    0.006788067431) + 0.217964925 * rtSteeringangle_Torque) +
                  2.836E-7) + ((((((((((3.534215197E-8 * rtb_IProdOut +
    1.618025757E-7 * rtb_SumFdbk) + 3.167586246E-7 * rtb_T_diff_k) +
    1.704975313E-6 * rtb_delta_F) + 8.483283483E-6 * rtb_T_rr) + 5.347236085E-5 *
    rtb_Switch2_ou) + 0.0002074729834 * rtb_Gain_m) + 0.001981845682 *
    rtb_PProdOut) + rtb_delta_F_tmp * 0.006788067316) + 0.2179649246 *
    rtSteeringangle_Torque) - 2.845E-7)) / 2.0;

  /* Lookup_n-D: '<S9>/1-D Lookup Table2' incorporates:
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   */
  rtb_T_rr = look1_binlxpw(rtmap_tv_Torque, rtConstP_Torque.pooled1,
    rtConstP_Torque.pooled1, 1U);

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/Constant'
   *  Lookup_n-D: '<S9>/1-D Lookup Table2'
   */
  rtb_Switch2_ou = 374.17610837438423 * rtb_T_rr;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S8>/Constant'
   *  Gain: '<S8>/Gain'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/map_sc'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S8>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtu_bar_Torque / (0.02 * rtmap_sc_Torque *
    (rtu_bar_Torque * rtu_bar_Torque) + 1.53) - rtyaw_rate_Torque;

  /* Product: '<S51>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/P_table'
   */
  rtb_PProdOut = rtb_IProdOut * look1_binlxpw(rtu_bar_Torque,
    rtConstP_Torque.pooled2, rtConstP_Torque.P_table_tableData, 1U);

  /* Sum: '<S57>/Sum Fdbk' */
  rtb_SumFdbk = rtb_PProdOut + rtDW_Torque->Integrator_DSTATE;

  /* Switch: '<S39>/Switch' incorporates:
   *  Gain: '<S9>/Gain'
   *  RelationalOperator: '<S39>/u_GTE_up'
   *  RelationalOperator: '<S39>/u_GT_lo'
   *  Switch: '<S39>/Switch1'
   */
  if (rtb_SumFdbk >= rtb_Switch2_ou) {
    rtb_T_diff_k = rtb_Switch2_ou;
  } else if (rtb_SumFdbk > -rtb_Switch2_ou) {
    /* Switch: '<S39>/Switch1' */
    rtb_T_diff_k = rtb_SumFdbk;
  } else {
    rtb_T_diff_k = -rtb_Switch2_ou;
  }

  /* Sum: '<S39>/Diff' incorporates:
   *  Switch: '<S39>/Switch'
   */
  rtb_T_diff_k = rtb_SumFdbk - rtb_T_diff_k;

  /* Product: '<S43>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtu_bar_Torque, rtConstP_Torque.pooled2,
    rtConstP_Torque.I_table_tableData, 1U);

  /* Switch: '<S36>/Switch1' incorporates:
   *  Constant: '<S36>/Clamping_zero'
   *  Constant: '<S36>/Constant'
   *  Constant: '<S36>/Constant2'
   *  RelationalOperator: '<S36>/fix for DT propagation issue'
   */
  if (rtb_T_diff_k > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S36>/Switch2' incorporates:
   *  Constant: '<S36>/Clamping_zero'
   *  Constant: '<S36>/Constant3'
   *  Constant: '<S36>/Constant4'
   *  RelationalOperator: '<S36>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S36>/Switch' incorporates:
   *  Constant: '<S36>/Clamping_zero'
   *  Constant: '<S36>/Constant1'
   *  Logic: '<S36>/AND3'
   *  RelationalOperator: '<S36>/Equal1'
   *  RelationalOperator: '<S36>/Relational Operator'
   *  Switch: '<S36>/Switch1'
   *  Switch: '<S36>/Switch2'
   */
  if ((rtb_T_diff_k != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S36>/Switch' */

  /* DiscreteIntegrator: '<S46>/Integrator' */
  rtb_SumFdbk = 0.00025 * rtb_IProdOut + rtDW_Torque->Integrator_DSTATE;

  /* Sum: '<S56>/Sum' */
  rtb_T_diff_k = rtb_PProdOut + rtb_SumFdbk;

  /* Switch: '<S54>/Switch2' incorporates:
   *  RelationalOperator: '<S54>/LowerRelop1'
   */
  if (rtb_T_diff_k <= rtb_Switch2_ou) {
    /* Switch: '<S54>/Switch' incorporates:
     *  Gain: '<S9>/Gain'
     *  RelationalOperator: '<S54>/UpperRelop'
     */
    if (rtb_T_diff_k < -rtb_Switch2_ou) {
      rtb_Switch2_ou = -rtb_Switch2_ou;
    } else {
      rtb_Switch2_ou = rtb_T_diff_k;
    }

    /* End of Switch: '<S54>/Switch' */
  }

  /* End of Switch: '<S54>/Switch2' */

  /* Product: '<S2>/Product1' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S2>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Product: '<S2>/Product2'
   *  RelationalOperator: '<S6>/Compare'
   */
  rtb_T_diff_k = (fabs(rtb_delta_F) >= 0.034906585039886591 ? rtb_Switch2_ou :
                  0.0) * 0.080176150557382225 * rtb_T_rr;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Sum: '<S1>/Add'
   */
  rtb_Switch2_ou = (rtTm_rl_Torque + rtTm_rr_Torque) * 0.5;

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_delta_F = rtDriver_req_Torque * rtb_Switch2_ou;

  /* Sum: '<S1>/Sum2' */
  rtb_T_rr = rtb_T_diff_k + rtb_delta_F;

  /* Sum: '<S1>/Sum3' */
  rtb_T_diff_k = rtb_delta_F - rtb_T_diff_k;

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtu_bar_Torque > 5.0) {
    if (rtb_T_rr > rtb_Switch2_ou) {
      rtb_Gain_m = rtb_T_rr - rtb_Switch2_ou;
    } else {
      rtb_Gain_m = fmin(rtb_T_rr, 0.0);
    }

    if (rtb_T_diff_k > rtb_Switch2_ou) {
      rtb_Switch2_ou = rtb_T_diff_k - rtb_Switch2_ou;
    } else if (rtb_T_rr < 0.0) {
      rtb_Switch2_ou = rtb_T_diff_k;
    } else {
      rtb_Switch2_ou = 0.0;
    }

    if (fabs(rtb_Gain_m) >= fabs(rtb_Switch2_ou)) {
      rtb_delta_F = rtb_T_rr - rtb_Gain_m;
      rtb_T_diff_k -= rtb_Gain_m;
    } else {
      rtb_delta_F = rtb_T_rr - rtb_Switch2_ou;
      rtb_T_diff_k -= rtb_Switch2_ou;
    }
  } else {
    rtb_T_diff_k = rtb_delta_F;
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_delta_F > rtTm_rl_Torque) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_Torque = rtTm_rl_Torque;
  } else if (rtb_delta_F < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_Torque = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rr_m_Torque = rtb_delta_F;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_T_diff_k > rtTm_rr_Torque) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_Torque = rtTm_rr_Torque;
  } else if (rtb_T_diff_k < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_Torque = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S3>/Switch'
     */
    rtTm_rl_a_Torque = rtb_T_diff_k;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Update for DiscreteIntegrator: '<S46>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = 0.00025 * rtb_IProdOut + rtb_SumFdbk;
}

/* Model initialize function */
void Torque_initialize(RT_MODEL_Torque *const rtM_Torque)
{
  DW_Torque *rtDW_Torque = rtM_Torque->dwork;

  /* Registration code */

  /* Storage classes */
  rtDriver_req_Torque = 0.0;
  rtu_bar_Torque = 0.0;
  rtomega_rr_Torque = 0.0;
  rtomega_rl_Torque = 0.0;
  rtyaw_rate_Torque = 0.0;
  rtSteeringangle_Torque = 0.0;
  rtbrake_Torque = 0.0;
  rtTm_rl_Torque = 0.0;
  rtTm_rr_Torque = 0.0;
  rtmap_tv_Torque = 0.0;
  rtmap_sc_Torque = 0.0;

  /* Storage classes */
  rtTm_rr_m_Torque = 0.0;
  rtTm_rl_a_Torque = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_Torque, 0,
                sizeof(DW_Torque));

  /* InitializeConditions for DiscreteIntegrator: '<S46>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
