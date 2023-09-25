/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip.c
 *
 * Code generated for Simulink model 'Slip'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec 12 11:51:52 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Slip.h"
#include "rtwtypes.h"
#include <math.h>
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
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

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

/*
 * Output and update for atomic system:
 *    '<S4>/Slip_est1'
 *    '<S5>/Slip_est1'
 */
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda)
{
  real_T Vmax;
  Vmax = fmax(fabs(rtu_u_bar), fabs(rtu_omegaR));
  if (Vmax > rtu_Vlow) {
    *rty_lambda = fabs((rtu_u_bar - rtu_omegaR) / Vmax);
  } else {
    *rty_lambda = fabs((rtu_u_bar - rtu_omegaR) * 2.0 / (Vmax * Vmax / rtu_Vlow
      + rtu_Vlow));
  }
}

/* Model step function */
void Slip_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T rtb_Add;
  real_T rtb_Product;
  real_T rtb_Product1;
  real_T rtb_Saturation_tmp;
  real_T rtb_e_rr;
  real_T rtb_lambda;
  real_T rtb_vms;

  /* Product: '<S4>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtDriver_req * rtTm_rl;

  /* Sum: '<S4>/Add5' incorporates:
   *  Gain: '<S4>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = rtu_bar - 0.605 * rtyaw_rate;

  /* MATLAB Function: '<S4>/Slip_est1' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Rl'
   *  Inport: '<Root>/omega_rl'
   */
  Slip_est1(0.203 * rtomega_rl, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S6>/Add' incorporates:
   *  Constant: '<S6>/lambda_rl_max [-]'
   */
  rtb_Add = rtb_lambda - 0.124;

  /* Lookup_n-D: '<S4>/1-D Lookup Table1' incorporates:
   *  Sum: '<S4>/Add5'
   */
  rtb_lambda = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled12,
    &rtDW->m_bpIndex, 13U);

  /* Product: '<S10>/Product1' */
  rtb_Product1 = rtb_Add * rtb_lambda;

  /* Saturate: '<S10>/Saturation' incorporates:
   *  Constant: '<S10>/Constant'
   *  Inport: '<Root>/Brake'
   *  Saturate: '<S18>/Saturation'
   *  Sum: '<S10>/Subtract'
   */
  rtb_Saturation_tmp = fmax(rtbrake - 0.1, 0.0);

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' incorporates:
   *  Saturate: '<S10>/Saturation'
   */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevRes != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 0.00025 * rtb_Product1 +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* If: '<S9>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtbrake >= 0.1) {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     */
    rtTm_rl_a = rtb_Product;
  } else {
    /* Lookup_n-D: '<S4>/1-D Lookup Table' incorporates:
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     *  Sum: '<S4>/Add5'
     */
    rtb_lambda = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled3,
      &rtDW->m_bpIndex_l, 13U);

    /* Sum: '<S4>/Add1' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S4>/1-D Lookup Table2'
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     *  Product: '<S11>/Product'
     *  Product: '<S4>/Product2'
     *  Saturate: '<S6>/Saturation'
     *  Sum: '<S6>/Sum'
     */
    rtb_lambda = rtb_Product - fmax(rtb_Add * rtb_lambda +
      DiscreteTimeIntegrator1, 0.0) * look1_binlxpw(rtmap_sc, rtConstP.pooled2,
      rtConstP.pooled2, 1U);

    /* Lookup_n-D: '<S4>/1-D Lookup Table3' incorporates:
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     *  Sum: '<S4>/Add5'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled6,
      &rtDW->m_bpIndex_d, 13U);

    /* Switch: '<S7>/Switch2' incorporates:
     *  Constant: '<S4>/Constant1'
     *  Inport: '<Root>/Tmax_rl'
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     *  RelationalOperator: '<S7>/LowerRelop1'
     *  RelationalOperator: '<S7>/UpperRelop'
     *  Switch: '<S7>/Switch'
     */
    if (rtb_lambda > rtTm_rl) {
      rtb_lambda = rtTm_rl;
    } else if (rtb_lambda < 0.0) {
      /* Switch: '<S7>/Switch' incorporates:
       *  Constant: '<S4>/Constant1'
       */
      rtb_lambda = 0.0;
    }

    /* End of Switch: '<S7>/Switch2' */

    /* Outport: '<Root>/Tm_rl' incorporates:
     *  MultiPortSwitch: '<S4>/Multiport Switch'
     *  Product: '<S4>/Product1'
     */
    rtTm_rl_a = rtb_lambda * rtb_vms;
  }

  /* End of If: '<S9>/If' */

  /* Product: '<S5>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Add = rtDriver_req * rtTm_rr;

  /* Sum: '<S5>/Add2' incorporates:
   *  Gain: '<S5>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtyaw_rate + rtu_bar;

  /* MATLAB Function: '<S5>/Slip_est1' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Rr'
   *  Inport: '<Root>/omega_rr'
   */
  Slip_est1(0.203 * rtomega_rr, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S14>/Add' incorporates:
   *  Constant: '<S14>/lambda_rr_max [-]'
   */
  rtb_e_rr = rtb_lambda - 0.124;

  /* Lookup_n-D: '<S5>/1-D Lookup Table1' incorporates:
   *  Sum: '<S5>/Add2'
   */
  rtb_lambda = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled12,
    &rtDW->m_bpIndex_o, 13U);

  /* Product: '<S18>/Product1' */
  rtb_lambda *= rtb_e_rr;

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevR_d != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTAT_b = 0.0;
  }

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtb_Product = 0.00025 * rtb_lambda + rtDW->DiscreteTimeIntegrator1_DSTAT_b;

  /* If: '<S17>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtbrake >= 0.1) {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     */
    rtTm_rr_m = rtb_Add;
  } else {
    real_T rtb_uDLookupTable;

    /* Lookup_n-D: '<S5>/1-D Lookup Table' incorporates:
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     *  Sum: '<S5>/Add2'
     */
    rtb_uDLookupTable = look1_pbinlcapw(rtb_vms, rtConstP.pooled4,
      rtConstP.pooled3, &rtDW->m_bpIndex_h, 13U);

    /* Sum: '<S5>/Add1' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S5>/1-D Lookup Table2'
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     *  Product: '<S19>/Product'
     *  Product: '<S5>/Product2'
     *  Saturate: '<S14>/Saturation'
     *  Sum: '<S14>/Sum'
     */
    rtb_Add -= fmax(rtb_e_rr * rtb_uDLookupTable + rtb_Product, 0.0) *
      look1_binlxpw(rtmap_sc, rtConstP.pooled2, rtConstP.pooled2, 1U);

    /* Lookup_n-D: '<S5>/1-D Lookup Table3' incorporates:
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     *  Sum: '<S5>/Add2'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled6,
      &rtDW->m_bpIndex_i, 13U);

    /* Switch: '<S15>/Switch2' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Inport: '<Root>/Tmax_rr'
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     *  RelationalOperator: '<S15>/LowerRelop1'
     *  RelationalOperator: '<S15>/UpperRelop'
     *  Switch: '<S15>/Switch'
     */
    if (rtb_Add > rtTm_rr) {
      rtb_Add = rtTm_rr;
    } else if (rtb_Add < 0.0) {
      /* Switch: '<S15>/Switch' incorporates:
       *  Constant: '<S5>/Constant1'
       */
      rtb_Add = 0.0;
    }

    /* End of Switch: '<S15>/Switch2' */

    /* Outport: '<Root>/Tm_rr' incorporates:
     *  MultiPortSwitch: '<S5>/Multiport Switch'
     *  Product: '<S5>/Product1'
     */
    rtTm_rr_m = rtb_Add * rtb_vms;
  }

  /* End of If: '<S17>/If' */

  /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S18>/Discrete-Time Integrator1'
   *  Saturate: '<S10>/Saturation'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.00025 * rtb_Product1 +
    DiscreteTimeIntegrator1;
  if (rtb_Saturation_tmp > 0.0) {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
    rtDW->DiscreteTimeIntegrator1_PrevR_d = 1;
  } else {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    rtDW->DiscreteTimeIntegrator1_PrevR_d = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_b = 0.00025 * rtb_lambda + rtb_Product;
}

/* Model initialize function */
void Slip_initialize(RT_MODEL *const rtM)
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

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevR_d = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
