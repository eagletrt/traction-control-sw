/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_data.c
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

/* Constant parameters (default storage) */
const ConstP_Torque rtConstP_Torque = {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S9>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S9>/P_table'
   */
  { 738.851472, 705.299936 },

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S9>/I_table'
   *   '<S9>/P_table'
   */
  { 5.555556, 8.333333 },

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S9>/I_table'
   */
  { 22708.413425, 15073.39619 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
