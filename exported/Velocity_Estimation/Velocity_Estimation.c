/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Velocity_Estimation.c
 *
 * Code generated for Simulink model 'Velocity_Estimation'.
 *
 * Model version                  : 6.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Sep 26 17:00:24 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Velocity_Estimation.h"
#include "rtwtypes.h"
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtTmax_rl_Velocity_Estimation;  /* '<Root>/Tmax_rl' */
real_T rtTmax_rr_Velocity_Estimation;  /* '<Root>/Tmax_rr' */
real_T rtaxG_Velocity_Estimation;      /* '<Root>/a_x' */
real_T rtmap_motor_Velocity_Estimation;/* '<Root>/map' */
real_T rtomega_fl_Velocity_Estimation; /* '<Root>/omega_fl' */
real_T rtomega_fr_Velocity_Estimation; /* '<Root>/omega_fr' */
real_T rtomega_rl_Velocity_Estimation; /* '<Root>/omega_rl' */
real_T rtomega_rr_Velocity_Estimation; /* '<Root>/omega_rr' */
real_T rtu_bar_Velocity_Estimation;    /* '<Root>/u_bar' */
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
void Velocity_Estimation_step(RT_MODEL_Velocity_Estimation *const
  rtM_Velocity_Estimation)
{
  DW_Velocity_Estimation *rtDW_Velocity_Estimation =
    rtM_Velocity_Estimation->dwork;
  real_T omega__mot_l;
  real_T omega__mot_r;
  real_T rtb_Tmax_rr;
  real_T slopeTorqueCut;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/map'
   *  Lookup_n-D: '<S1>/1-D Lookup Table2'
   */
  rtb_Tmax_rr = 100.0 * look1_binlxpw(rtmap_motor_Velocity_Estimation,
    rtConstP_Velocity_Estimation.uDLookupTable2_bp01Data,
    rtConstP_Velocity_Estimation.uDLookupTable2_tableData, 5U);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/omega_rl'
   *  Inport: '<Root>/omega_rr'
   */
  slopeTorqueCut = (rtb_Tmax_rr - 47.746482927568607) / -157.07963267948958;
  omega__mot_r = rtomega_rr_Velocity_Estimation * 4.5;
  omega__mot_l = rtomega_rl_Velocity_Estimation * 4.5;
  if (omega__mot_r <= 680.67840827778855) {
    /* Outport: '<Root>/Tmax_rr' */
    rtTmax_rr_Velocity_Estimation = rtb_Tmax_rr;
  } else {
    /* Outport: '<Root>/Tmax_rr' */
    rtTmax_rr_Velocity_Estimation = (omega__mot_r - 680.67840827778855) *
      slopeTorqueCut + rtb_Tmax_rr;
  }

  if (omega__mot_l <= 680.67840827778855) {
    /* Outport: '<Root>/Tmax_rl' */
    rtTmax_rl_Velocity_Estimation = rtb_Tmax_rr;
  } else {
    /* Outport: '<Root>/Tmax_rl' */
    rtTmax_rl_Velocity_Estimation = (omega__mot_l - 680.67840827778855) *
      slopeTorqueCut + rtb_Tmax_rr;
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function1' */

  /* Product: '<S3>/Product' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant6'
   *  Inport: '<Root>/omega_fl'
   *  Inport: '<Root>/omega_fr'
   *  Product: '<S3>/Divide'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Tmax_rr = (rtomega_fl_Velocity_Estimation + rtomega_fr_Velocity_Estimation)
    / 2.0 * 0.203;

  /* DiscreteFilter: '<S3>/Discrete Filter1' */
  slopeTorqueCut = (0.0050000000000000027 * rtb_Tmax_rr + -0.0050000000000000018
                    * rtDW_Velocity_Estimation->DiscreteFilter1_states) -
    -0.99950012497916929 * rtDW_Velocity_Estimation->DiscreteFilter1_denStates;

  /* Outport: '<Root>/u_bar' incorporates:
   *  Sum: '<S3>/Sum'
   *  Sum: '<S3>/Sum2'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtu_bar_Velocity_Estimation = (rtb_Tmax_rr - slopeTorqueCut) +
    rtDW_Velocity_Estimation->UnitDelay_DSTATE;

  /* DiscreteFilter: '<S3>/Discrete Filter2' incorporates:
   *  Inport: '<Root>/a_x'
   */
  omega__mot_r = (0.0050000000000000027 * rtaxG_Velocity_Estimation +
                  -0.0050000000000000018 *
                  rtDW_Velocity_Estimation->DiscreteFilter2_states) -
    -0.99950012497916929 * rtDW_Velocity_Estimation->DiscreteFilter2_denStates;

  /* Update for DiscreteFilter: '<S3>/Discrete Filter1' */
  rtDW_Velocity_Estimation->DiscreteFilter1_states = rtb_Tmax_rr;
  rtDW_Velocity_Estimation->DiscreteFilter1_denStates = slopeTorqueCut;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW_Velocity_Estimation->UnitDelay_DSTATE = omega__mot_r;

  /* Update for DiscreteFilter: '<S3>/Discrete Filter2' incorporates:
   *  Inport: '<Root>/a_x'
   */
  rtDW_Velocity_Estimation->DiscreteFilter2_states = rtaxG_Velocity_Estimation;
  rtDW_Velocity_Estimation->DiscreteFilter2_denStates = omega__mot_r;
}

/* Model initialize function */
void Velocity_Estimation_initialize(RT_MODEL_Velocity_Estimation *const
  rtM_Velocity_Estimation)
{
  DW_Velocity_Estimation *rtDW_Velocity_Estimation =
    rtM_Velocity_Estimation->dwork;

  /* Registration code */

  /* Storage classes */
  rtomega_fl_Velocity_Estimation = 0.0;
  rtomega_fr_Velocity_Estimation = 0.0;
  rtomega_rl_Velocity_Estimation = 0.0;
  rtomega_rr_Velocity_Estimation = 0.0;
  rtaxG_Velocity_Estimation = 0.0;
  rtmap_motor_Velocity_Estimation = 0.0;

  /* Storage classes */
  rtu_bar_Velocity_Estimation = 0.0;
  rtTmax_rr_Velocity_Estimation = 0.0;
  rtTmax_rl_Velocity_Estimation = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_Velocity_Estimation, 0,
                sizeof(DW_Velocity_Estimation));

  /* InitializeConditions for DiscreteFilter: '<S3>/Discrete Filter1' */
  rtDW_Velocity_Estimation->DiscreteFilter1_states = 0.0;
  rtDW_Velocity_Estimation->DiscreteFilter1_denStates = 0.0;

  /* InitializeConditions for DiscreteFilter: '<S3>/Discrete Filter2' */
  rtDW_Velocity_Estimation->DiscreteFilter2_states = 0.0;
  rtDW_Velocity_Estimation->DiscreteFilter2_denStates = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
