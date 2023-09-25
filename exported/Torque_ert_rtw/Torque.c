/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec 12 11:53:33 2022
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
real_T rtDriver_req;                   /* '<Root>/driver_request' */
real_T rtSteeringangle;                /* '<Root>/delta' */
real_T rtTm_rl;                        /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a;                      /* '<Root>/Tm_rl' */
real_T rtTm_rr;                        /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m;                      /* '<Root>/Tm_rr' */
real_T rtbrake;                        /* '<Root>/Brake' */
real_T rtmap_sc;                       /* '<Root>/map_sc' */
real_T rtmap_tv;                       /* '<Root>/map_tv' */
real_T rtomega_rl;                     /* '<Root>/omega_rl' */
real_T rtomega_rr;                     /* '<Root>/omega_rr' */
real_T rtu_bar;                        /* '<Root>/u_bar' */
real_T rtyaw_rate;                     /* '<Root>/Omega' */
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride);
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

static real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride)
{
  real_T fractions[2];
  real_T frac;
  real_T yL_0d0;
  real_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
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
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
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
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

/* Model step function */
void Torque_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T T_rr_sat;
  real_T rtb_Max;
  real_T rtb_TSamp;
  real_T rtb_T_rr;
  real_T rtb_Tm_req;
  real_T rtb_Tm_req_o;
  real_T rtb_errore_yaw;
  real_T rtb_errore_yaw_tmp;
  real_T rtb_y;
  boolean_T rtb_LogicalOperator;

  /* Logic: '<S12>/Logical Operator' incorporates:
   *  Constant: '<S12>/Time constant'
   *  Constant: '<S16>/Constant'
   *  RelationalOperator: '<S16>/Compare'
   *  Sum: '<S12>/Sum1'
   */
  rtb_LogicalOperator = ((0.001 - rtDW->Probe[0] <= 0.0) && rtConstB.Compare);

  /* MATLAB Function: '<S6>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_errore_yaw = pow(rtSteeringangle, 10.0);
  rtb_TSamp = pow(rtSteeringangle, 9.0);
  rtb_y = pow(rtSteeringangle, 8.0);
  rtb_Tm_req_o = pow(rtSteeringangle, 7.0);
  rtb_T_rr = pow(rtSteeringangle, 6.0);
  rtb_Tm_req = pow(rtSteeringangle, 5.0);
  rtb_Max = pow(rtSteeringangle, 4.0);
  T_rr_sat = pow(rtSteeringangle, 3.0);
  rtb_errore_yaw_tmp = rtSteeringangle * rtSteeringangle;

  /* Sum: '<S6>/Sum2' incorporates:
   *  Constant: '<S11>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S11>/K_us_table'
   *  MATLAB Function: '<S11>/Yaw-Rate'
   *  MATLAB Function: '<S6>/SteeringModel'
   */
  rtb_errore_yaw = (((((((((((-2.511353952E-8 * rtb_errore_yaw + 1.204729921E-7 *
    rtb_TSamp) - 2.613187764E-7 * rtb_y) + 1.437082334E-6 * rtb_Tm_req_o) -
    7.12221471E-6 * rtb_T_rr) + 4.68525841E-5 * rtb_Tm_req) - 0.0001855092357 *
    rtb_Max) + 0.001856824887 * T_rr_sat) - rtb_errore_yaw_tmp * 0.006374606899)
                      + 0.2126142315 * rtSteeringangle) + 3.3E-9) +
                    ((((((((((2.5259036849999997E-8 * rtb_errore_yaw +
    1.206067049E-7 * rtb_TSamp) + 2.599089767E-7 * rtb_y) + 1.435718737E-6 *
    rtb_Tm_req_o) + 7.1264231E-6 * rtb_T_rr) + 4.685692282E-5 * rtb_Tm_req) +
    0.0001855053075 * rtb_Max) + 0.001856820364 * T_rr_sat) + rtb_errore_yaw_tmp
                       * 0.006374607119) + 0.2126142321 * rtSteeringangle) -
                     3.3E-9)) / 2.0 * rtu_bar / (rtu_bar * rtu_bar *
    look1_binlxpw(rtu_bar, rtConstP.K_us_table_bp01Data,
                  rtConstP.K_us_table_tableData, 9U) + 1.53) - rtyaw_rate;

  /* SampleTimeMath: '<S7>/TSamp'
   *
   * About '<S7>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_errore_yaw * 10.0;

  /* MATLAB Function: '<S6>/MATLAB Function2' incorporates:
   *  Sum: '<S7>/Diff'
   *  UnitDelay: '<S6>/Unit Delay'
   *  UnitDelay: '<S6>/Unit Delay1'
   *  UnitDelay: '<S7>/UD'
   *
   * Block description for '<S7>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S7>/UD':
   *
   *  Store in Global RAM
   */
  if (rtb_errore_yaw == 0.0) {
    rtb_y = 0.0;
  } else if (rtDW->UnitDelay_DSTATE == rtb_errore_yaw) {
    rtb_y = rtDW->UnitDelay1_DSTATE;
  } else {
    rtb_y = rtb_TSamp - rtDW->UD_DSTATE;
  }

  /* End of MATLAB Function: '<S6>/MATLAB Function2' */

  /* DiscreteIntegrator: '<S18>/Integrator' */
  if (rtDW->Integrator_IC_LOADING != 0) {
    rtDW->Integrator_DSTATE = rtb_y;
  }

  if (rtb_LogicalOperator || (rtDW->Integrator_PrevResetState != 0)) {
    rtDW->Integrator_DSTATE = rtb_y;
  }

  /* Saturate: '<S6>/Saturation1' */
  if (rtb_errore_yaw > 1.0) {
    rtb_Tm_req_o = 1.0;
  } else if (rtb_errore_yaw < -1.0) {
    rtb_Tm_req_o = -1.0;
  } else {
    rtb_Tm_req_o = rtb_errore_yaw;
  }

  /* Saturate: '<S6>/Saturation2' incorporates:
   *  DiscreteIntegrator: '<S18>/Integrator'
   */
  if (rtDW->Integrator_DSTATE > 1.0) {
    rtb_T_rr = 1.0;
  } else if (rtDW->Integrator_DSTATE < -1.0) {
    rtb_T_rr = -1.0;
  } else {
    rtb_T_rr = rtDW->Integrator_DSTATE;
  }

  /* Product: '<S2>/Product4' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S6>/Gain'
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   *  Lookup_n-D: '<S6>/2-D Lookup Table'
   *  Saturate: '<S6>/Saturation1'
   *  Saturate: '<S6>/Saturation2'
   */
  rtb_Max = look1_binlxpw(rtmap_tv, rtConstP.pooled5, rtConstP.pooled5, 1U) *
    -look2_binlxpw(rtb_Tm_req_o, rtb_T_rr, rtConstP.pooled4, rtConstP.pooled4,
                   rtConstP.uDLookupTable_tableData,
                   rtConstP.uDLookupTable_maxIndex, 21U) * 55.0;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req = (rtTm_rl + rtTm_rr) * 0.5;

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_Tm_req_o = rtDriver_req * rtb_Tm_req;

  /* Sum: '<S1>/Sum2' */
  rtb_T_rr = rtb_Max + rtb_Tm_req_o;

  /* Sum: '<S1>/Sum3' */
  rtb_Max = rtb_Tm_req_o - rtb_Max;

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtu_bar > 5.0) {
    if (rtb_T_rr > rtb_Tm_req) {
      T_rr_sat = rtb_T_rr - rtb_Tm_req;
    } else {
      T_rr_sat = fmin(rtb_T_rr, 0.0);
    }

    if (rtb_Max > rtb_Tm_req) {
      rtb_Tm_req = rtb_Max - rtb_Tm_req;
    } else if (rtb_T_rr < 0.0) {
      rtb_Tm_req = rtb_Max;
    } else {
      rtb_Tm_req = 0.0;
    }

    if (fabs(T_rr_sat) >= fabs(rtb_Tm_req)) {
      rtb_Tm_req_o = rtb_T_rr - T_rr_sat;
      rtb_T_rr = rtb_Max - T_rr_sat;
    } else {
      rtb_Tm_req_o = rtb_T_rr - rtb_Tm_req;
      rtb_T_rr = rtb_Max - rtb_Tm_req;
    }
  } else {
    rtb_T_rr = rtb_Tm_req_o;
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Tm_req_o > rtTm_rl) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m = rtTm_rl;
  } else if (rtb_Tm_req_o < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rr_m = rtb_Tm_req_o;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_T_rr > rtTm_rr) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a = rtTm_rr;
  } else if (rtb_T_rr < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S3>/Switch'
     */
    rtTm_rl_a = rtb_T_rr;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Update for UnitDelay: '<S6>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE = rtb_y;

  /* Update for UnitDelay: '<S7>/UD'
   *
   * Block description for '<S7>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S6>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtb_errore_yaw;

  /* Update for DiscreteIntegrator: '<S18>/Integrator' incorporates:
   *  Constant: '<S12>/Time constant'
   *  MinMax: '<S12>/Max'
   *  Product: '<S8>/1//T'
   *  Sum: '<S8>/Sum1'
   */
  rtDW->Integrator_IC_LOADING = 0U;
  rtDW->Integrator_DSTATE += 1.0 / fmax(rtDW->Probe[0], 0.001) * (rtb_y -
    rtDW->Integrator_DSTATE) * 0.0005;
  rtDW->Integrator_PrevResetState = (int8_T)rtb_LogicalOperator;
}

/* Model initialize function */
void Torque_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* Storage classes */
  rtTm_rr_m = 0.0;
  rtTm_rl_a = 0.0;

  /* Storage classes */
  rtDriver_req = 0.0;
  rtu_bar = 0.0;
  rtomega_rr = 0.0;
  rtomega_rl = 0.0;
  rtyaw_rate = 0.0;
  rtSteeringangle = 0.0;
  rtbrake = 0.0;
  rtTm_rl = 0.0;
  rtTm_rr = 0.0;
  rtmap_tv = 0.0;
  rtmap_sc = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* Start for Probe: '<S12>/Probe' */
  rtDW->Probe[0] = 0.0005;
  rtDW->Probe[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Integrator' */
  rtDW->Integrator_PrevResetState = 0;
  rtDW->Integrator_IC_LOADING = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
