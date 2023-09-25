/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.c
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec 12 11:45:34 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "All0.h"
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
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride);
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
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

/*
 * Output and update for atomic system:
 *    '<S13>/Slip_est1'
 *    '<S14>/Slip_est1'
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
void All0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T rtb_Add_h;
  real_T rtb_Product;
  real_T rtb_Product1;
  real_T rtb_TSamp;
  real_T rtb_T_diff_map;
  real_T rtb_T_rr;
  real_T rtb_e_rr;
  real_T rtb_errore_yaw;
  real_T rtb_errore_yaw_tmp;
  real_T rtb_lambda;
  real_T rtb_vms;
  real_T rtb_vms_i;
  real_T rtb_y;

  /* MATLAB Function: '<S7>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_errore_yaw = pow(rtSteeringangle, 10.0);
  rtb_TSamp = pow(rtSteeringangle, 9.0);
  rtb_y = pow(rtSteeringangle, 8.0);
  rtb_T_rr = pow(rtSteeringangle, 7.0);
  rtb_T_diff_map = pow(rtSteeringangle, 6.0);
  rtb_Product1 = pow(rtSteeringangle, 5.0);
  rtb_errore_yaw_tmp = pow(rtSteeringangle, 4.0);
  DiscreteTimeIntegrator1 = pow(rtSteeringangle, 3.0);
  rtb_lambda = rtSteeringangle * rtSteeringangle;

  /* Sum: '<S7>/Sum2' incorporates:
   *  Constant: '<S11>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S11>/K_us_table'
   *  MATLAB Function: '<S11>/Yaw-Rate'
   *  MATLAB Function: '<S7>/SteeringModel'
   */
  rtb_errore_yaw = (((((((((((-2.511353952E-8 * rtb_errore_yaw + 1.204729921E-7 *
    rtb_TSamp) - 2.613187764E-7 * rtb_y) + 1.437082334E-6 * rtb_T_rr) -
    7.12221471E-6 * rtb_T_diff_map) + 4.68525841E-5 * rtb_Product1) -
    0.0001855092357 * rtb_errore_yaw_tmp) + 0.001856824887 *
                        DiscreteTimeIntegrator1) - rtb_lambda * 0.006374606899)
                      + 0.2126142315 * rtSteeringangle) + 3.3E-9) +
                    ((((((((((2.5259036849999997E-8 * rtb_errore_yaw +
    1.206067049E-7 * rtb_TSamp) + 2.599089767E-7 * rtb_y) + 1.435718737E-6 *
    rtb_T_rr) + 7.1264231E-6 * rtb_T_diff_map) + 4.685692282E-5 * rtb_Product1)
    + 0.0001855053075 * rtb_errore_yaw_tmp) + 0.001856820364 *
                        DiscreteTimeIntegrator1) + rtb_lambda * 0.006374607119)
                      + 0.2126142321 * rtSteeringangle) - 3.3E-9)) / 2.0 *
    rtu_bar / (rtu_bar * rtu_bar * look1_binlxpw(rtu_bar,
    rtConstP.K_us_table_bp01Data, rtConstP.K_us_table_tableData, 9U) + 1.53) -
    rtyaw_rate;

  /* SampleTimeMath: '<S8>/TSamp'
   *
   * About '<S8>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_errore_yaw * 20.0;

  /* MATLAB Function: '<S7>/MATLAB Function2' incorporates:
   *  Sum: '<S8>/Diff'
   *  UnitDelay: '<S7>/Unit Delay'
   *  UnitDelay: '<S7>/Unit Delay1'
   *  UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S8>/UD':
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

  /* End of MATLAB Function: '<S7>/MATLAB Function2' */

  /* Saturate: '<S7>/Saturation1' */
  if (rtb_errore_yaw > 1.0) {
    rtb_T_rr = 1.0;
  } else if (rtb_errore_yaw < -1.0) {
    rtb_T_rr = -1.0;
  } else {
    rtb_T_rr = rtb_errore_yaw;
  }

  /* Saturate: '<S7>/Saturation3' */
  if (rtb_y > 1.0) {
    rtb_T_diff_map = 1.0;
  } else if (rtb_y < -1.0) {
    rtb_T_diff_map = -1.0;
  } else {
    rtb_T_diff_map = rtb_y;
  }

  /* Product: '<S2>/Product4' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S7>/Gain'
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   *  Lookup_n-D: '<S7>/2-D Lookup Table'
   *  Saturate: '<S7>/Saturation1'
   *  Saturate: '<S7>/Saturation3'
   */
  rtb_T_diff_map = look1_binlxpw(rtmap_tv, rtConstP.pooled2, rtConstP.pooled2,
    1U) * -look2_binlxpw(rtb_T_rr, rtb_T_diff_map, rtConstP.pooled10,
    rtConstP.pooled10, rtConstP.uDLookupTable_tableData,
    rtConstP.uDLookupTable_maxIndex, 21U) * 55.0;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_lambda = (rtTm_rr + rtTm_rl) * 0.5 * rtDriver_req;

  /* Sum: '<S1>/Sum3' */
  rtb_T_rr = rtb_T_diff_map + rtb_lambda;

  /* Sum: '<S1>/Sum4' */
  rtb_T_diff_map = rtb_lambda - rtb_T_diff_map;

  /* Product: '<S14>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtDriver_req * rtTm_rr;

  /* Sum: '<S14>/Add2' incorporates:
   *  Gain: '<S14>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtyaw_rate + rtu_bar;

  /* MATLAB Function: '<S14>/Slip_est1' incorporates:
   *  Constant: '<S14>/Constant'
   *  Gain: '<S14>/Rr'
   *  Inport: '<Root>/omega_rr'
   */
  Slip_est1(0.203 * rtomega_rr, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S23>/Add' incorporates:
   *  Constant: '<S23>/lambda_rr_max [-]'
   */
  rtb_e_rr = rtb_lambda - 0.124;

  /* Lookup_n-D: '<S14>/1-D Lookup Table1' incorporates:
   *  Sum: '<S14>/Add2'
   */
  rtb_lambda = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled13,
    &rtDW->m_bpIndex, 13U);

  /* Product: '<S27>/Product1' */
  rtb_Product1 = rtb_e_rr * rtb_lambda;

  /* Saturate: '<S27>/Saturation' incorporates:
   *  Constant: '<S27>/Constant'
   *  Inport: '<Root>/Brake'
   *  Saturate: '<S19>/Saturation'
   *  Sum: '<S27>/Subtract'
   */
  rtb_errore_yaw_tmp = fmax(rtbrake - 0.1, 0.0);

  /* DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' incorporates:
   *  Saturate: '<S27>/Saturation'
   */
  if ((rtb_errore_yaw_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevRes != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 0.00025 * rtb_Product1 +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* If: '<S26>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtbrake < 0.1) {
    /* Lookup_n-D: '<S14>/1-D Lookup Table' incorporates:
     *  MultiPortSwitch: '<S14>/Multiport Switch'
     *  Sum: '<S14>/Add2'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled3,
      &rtDW->m_bpIndex_e, 13U);

    /* Sum: '<S14>/Add1' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S14>/1-D Lookup Table2'
     *  MultiPortSwitch: '<S14>/Multiport Switch'
     *  Product: '<S14>/Product2'
     *  Product: '<S28>/Product'
     *  Saturate: '<S23>/Saturation'
     *  Sum: '<S23>/Sum'
     */
    rtb_Product -= fmax(rtb_e_rr * rtb_vms + DiscreteTimeIntegrator1, 0.0) *
      look1_binlxpw(rtmap_sc, rtConstP.pooled2, rtConstP.pooled2, 1U);

    /* Switch: '<S24>/Switch2' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Inport: '<Root>/Tmax_rr'
     *  MultiPortSwitch: '<S14>/Multiport Switch'
     *  RelationalOperator: '<S24>/LowerRelop1'
     *  RelationalOperator: '<S24>/UpperRelop'
     *  Switch: '<S24>/Switch'
     */
    if (rtb_Product > rtTm_rr) {
      rtb_Product = rtTm_rr;
    } else if (rtb_Product < 0.0) {
      /* Switch: '<S24>/Switch' incorporates:
       *  Constant: '<S14>/Constant1'
       */
      rtb_Product = 0.0;
    }

    /* End of Switch: '<S24>/Switch2' */
  }

  /* End of If: '<S26>/If' */

  /* Product: '<S13>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_vms = rtDriver_req * rtTm_rl;

  /* Sum: '<S13>/Add5' incorporates:
   *  Gain: '<S13>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms_i = rtu_bar - 0.605 * rtyaw_rate;

  /* MATLAB Function: '<S13>/Slip_est1' incorporates:
   *  Constant: '<S13>/Constant'
   *  Gain: '<S13>/Rl'
   *  Inport: '<Root>/omega_rl'
   */
  Slip_est1(0.203 * rtomega_rl, rtb_vms_i, 1.0, &rtb_lambda);

  /* Sum: '<S15>/Add' incorporates:
   *  Constant: '<S15>/lambda_rl_max [-]'
   */
  rtb_Add_h = rtb_lambda - 0.124;

  /* Lookup_n-D: '<S13>/1-D Lookup Table1' incorporates:
   *  Sum: '<S13>/Add5'
   */
  rtb_lambda = look1_pbinlcapw(rtb_vms_i, rtConstP.pooled4, rtConstP.pooled13,
    &rtDW->m_bpIndex_h, 13U);

  /* Product: '<S19>/Product1' */
  rtb_lambda *= rtb_Add_h;

  /* DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' */
  if ((rtb_errore_yaw_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevR_p != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTAT_e = 0.0;
  }

  /* DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' */
  rtb_e_rr = 0.00025 * rtb_lambda + rtDW->DiscreteTimeIntegrator1_DSTAT_e;

  /* If: '<S18>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtbrake < 0.1) {
    /* Lookup_n-D: '<S13>/1-D Lookup Table' incorporates:
     *  MultiPortSwitch: '<S13>/Multiport Switch'
     *  Sum: '<S13>/Add5'
     */
    rtb_vms_i = look1_pbinlcapw(rtb_vms_i, rtConstP.pooled4, rtConstP.pooled3,
      &rtDW->m_bpIndex_m, 13U);

    /* Sum: '<S13>/Add1' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S13>/1-D Lookup Table2'
     *  MultiPortSwitch: '<S13>/Multiport Switch'
     *  Product: '<S13>/Product2'
     *  Product: '<S20>/Product'
     *  Saturate: '<S15>/Saturation'
     *  Sum: '<S15>/Sum'
     */
    rtb_vms -= fmax(rtb_Add_h * rtb_vms_i + rtb_e_rr, 0.0) * look1_binlxpw
      (rtmap_sc, rtConstP.pooled2, rtConstP.pooled2, 1U);

    /* Switch: '<S16>/Switch2' incorporates:
     *  Constant: '<S13>/Constant1'
     *  Inport: '<Root>/Tmax_rl'
     *  MultiPortSwitch: '<S13>/Multiport Switch'
     *  RelationalOperator: '<S16>/LowerRelop1'
     *  RelationalOperator: '<S16>/UpperRelop'
     *  Switch: '<S16>/Switch'
     */
    if (rtb_vms > rtTm_rl) {
      rtb_vms = rtTm_rl;
    } else if (rtb_vms < 0.0) {
      /* Switch: '<S16>/Switch' incorporates:
       *  Constant: '<S13>/Constant1'
       */
      rtb_vms = 0.0;
    }

    /* End of Switch: '<S16>/Switch2' */
  }

  /* End of If: '<S18>/If' */

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtu_bar > 5.0) {
    if (rtb_T_rr > rtb_Product) {
      rtb_vms_i = rtb_T_rr - rtb_Product;
    } else {
      rtb_vms_i = fmin(rtb_T_rr, 0.0);
    }

    if (rtb_T_diff_map > rtb_vms) {
      rtb_vms = rtb_T_diff_map - rtb_vms;
    } else if (rtb_T_rr < 0.0) {
      rtb_vms = rtb_T_diff_map;
    } else {
      rtb_vms = 0.0;
    }

    if (fabs(rtb_vms_i) >= fabs(rtb_vms)) {
      rtb_Product = rtb_T_rr - rtb_vms_i;
      rtb_vms = rtb_T_diff_map - rtb_vms_i;
    } else {
      rtb_Product = rtb_T_rr - rtb_vms;
      rtb_vms = rtb_T_diff_map - rtb_vms;
    }
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_Product > rtTm_rr) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m = rtTm_rr;
  } else if (rtb_Product < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S3>/Switch'
     */
    rtTm_rr_m = rtb_Product;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_vms > rtTm_rl) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a = rtTm_rl;
  } else if (rtb_vms < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rl_a = rtb_vms;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Update for UnitDelay: '<S7>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE = rtb_y;

  /* Update for UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S7>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtb_errore_yaw;

  /* Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S19>/Discrete-Time Integrator1'
   *  Saturate: '<S27>/Saturation'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.00025 * rtb_Product1 +
    DiscreteTimeIntegrator1;
  if (rtb_errore_yaw_tmp > 0.0) {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
    rtDW->DiscreteTimeIntegrator1_PrevR_p = 1;
  } else {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    rtDW->DiscreteTimeIntegrator1_PrevR_p = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_e = 0.00025 * rtb_lambda + rtb_e_rr;
}

/* Model initialize function */
void All0_initialize(RT_MODEL *const rtM)
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

  /* InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S19>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevR_p = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
