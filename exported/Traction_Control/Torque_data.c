/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_data.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.25
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  1 17:31:38 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Torque.h"

/* Block parameters (default storage) */
P_Torque rtP_Torque = {
  /* Variable: controlData
   * Referenced by:
   *   '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *   '<S7>/Constant'
   */
  {
    1.53,
    1.0,
    1.21,
    4.5,
    0.93,
    0.203,
    0.203,
    100.0,
    234.0,
    96.13,
    7.5,
    -0.3,
    0.4,
    1.17,
    2.34
  },

  /* Mask Parameter: DiscreteVaryingPID_InitialCondi
   * Referenced by: '<S41>/Integrator'
   */
  0.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerIntegra
   * Referenced by: '<S41>/Integrator'
   */
  -20.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerSaturat
   * Referenced by:
   *   '<S48>/Saturation'
   *   '<S34>/DeadZone'
   */
  -300.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperIntegra
   * Referenced by: '<S41>/Integrator'
   */
  20.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperSaturat
   * Referenced by:
   *   '<S48>/Saturation'
   *   '<S34>/DeadZone'
   */
  300.0,

  /* Mask Parameter: Steeringangle2deg1_const
   * Referenced by: '<S5>/Constant'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S32>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S32>/Clamping_zero'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S41>/Integrator'
   */
  0.00025,

  /* Expression: 0.5
   * Referenced by: '<S1>/Constant3'
   */
  0.5,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S32>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S32>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_c
   * Referenced by: '<S32>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S32>/Constant4'
   */
  -1
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
