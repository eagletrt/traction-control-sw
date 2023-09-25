/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ARB.c
 *
 * Code generated for Simulink model 'ARB'.
 *
 * Model version                  : 6.144
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue May  9 18:09:06 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "ARB.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtSteeringangle;                /* '<Root>/delta' */
real_T rtknife_angle;                  /* '<Root>/knife_angle' */
real_T rtknife_angle1;                 /* '<Root>/knife_angle1' */
real_T rtu_bar;                        /* '<Root>/vel' */
static real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride);
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
void ARB_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T rtb_Sum;

  /* Sum: '<S46>/Sum' incorporates:
   *  DiscreteIntegrator: '<S37>/Integrator'
   *  Gain: '<S2>/Gain'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/knife_angle'
   *  Inport: '<Root>/vel'
   *  Lookup_n-D: '<S2>/2-D Lookup Table'
   *  MATLAB Function: '<S1>/knifeangle2stiff'
   *  Sum: '<S2>/Add2'
   */
  rtb_Sum = (6.5 * look2_binlxpw(rtu_bar, rtSteeringangle,
              rtConstP.uDLookupTable_bp01Data, rtConstP.uDLookupTable_bp02Data,
              rtConstP.uDLookupTable_tableData, rtConstP.uDLookupTable_maxIndex,
              5U) - (((((((((-174.4 * pow(rtknife_angle, 9.0) + 1265.0 * pow
    (rtknife_angle, 8.0)) - 3755.0 * pow(rtknife_angle, 7.0)) + 5679.0 * pow
    (rtknife_angle, 6.0)) - 4079.0 * pow(rtknife_angle, 5.0)) + 87.29 * pow
    (rtknife_angle, 4.0)) + 2061.0 * pow(rtknife_angle, 3.0)) - rtknife_angle *
                       rtknife_angle * 1285.0) + 23.29 * rtknife_angle) + 321.6))
    + rtDW->Integrator_DSTATE;

  /* Outport: '<Root>/knife_angle1' incorporates:
   *  MATLAB Function: '<S1>/stiff2knifeangle'
   */
  rtknife_angle1 = ((((-7.427E-11 * pow(rtb_Sum, 5.0) + 8.606E-8 * pow(rtb_Sum,
    4.0)) - 3.935E-5 * pow(rtb_Sum, 3.0)) + rtb_Sum * rtb_Sum * 0.008879) -
                    0.9942 * rtb_Sum) + 45.12;
}

/* Model initialize function */
void ARB_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* Storage classes */
  rtknife_angle1 = 0.0;

  /* Storage classes */
  rtu_bar = 0.0;
  rtSteeringangle = 0.0;
  rtknife_angle = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
