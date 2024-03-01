/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1_data.c
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

/* Block parameters (default storage) */
P_SlipV1 rtP_SlipV1 = {
  /* Variable: controlData
   * Referenced by:
   *   '<S2>/Constant'
   *   '<S2>/Rr'
   *   '<S2>/Wr//2'
   *   '<S3>/Constant'
   *   '<S3>/Rr'
   *   '<S3>/Wr//2'
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
   * Referenced by: '<S97>/Integrator'
   */
  0.0,

  /* Mask Parameter: DiscreteVaryingPID_InitialCon_o
   * Referenced by: '<S42>/Integrator'
   */
  0.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerIntegra
   * Referenced by: '<S97>/Integrator'
   */
  -70.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerInteg_d
   * Referenced by: '<S42>/Integrator'
   */
  -70.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerSaturat
   * Referenced by:
   *   '<S104>/Saturation'
   *   '<S90>/DeadZone'
   */
  0.0,

  /* Mask Parameter: DiscreteVaryingPID_LowerSatur_b
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S35>/DeadZone'
   */
  0.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperIntegra
   * Referenced by: '<S97>/Integrator'
   */
  70.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperInteg_m
   * Referenced by: '<S42>/Integrator'
   */
  70.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperSaturat
   * Referenced by:
   *   '<S104>/Saturation'
   *   '<S90>/DeadZone'
   */
  100.0,

  /* Mask Parameter: DiscreteVaryingPID_UpperSatur_f
   * Referenced by:
   *   '<S49>/Saturation'
   *   '<S35>/DeadZone'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/Constant2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S33>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S88>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S88>/Clamping_zero'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S97>/Integrator'
   */
  0.00025,

  /* Expression: 0
   * Referenced by: '<S33>/Clamping_zero'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S42>/Integrator'
   */
  0.00025,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S33>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_a
   * Referenced by: '<S33>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S33>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S33>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S88>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_i
   * Referenced by: '<S88>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_l
   * Referenced by: '<S88>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_f
   * Referenced by: '<S88>/Constant4'
   */
  -1
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
