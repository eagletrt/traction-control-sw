/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S4>/1-D Lookup Table2'
   *   '<S5>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S4>/1-D Lookup Table'
   *   '<S5>/1-D Lookup Table'
   */
  { 30.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0,
    170.0, 170.0, 170.0 },

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S4>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table1'
   *   '<S4>/1-D Lookup Table3'
   *   '<S5>/1-D Lookup Table'
   *   '<S5>/1-D Lookup Table1'
   *   '<S5>/1-D Lookup Table3'
   */
  { 0.0, 1.3888888888888888, 2.7777777777777777, 5.5555555555555554,
    8.3333333333333339, 11.111111111111111, 13.888888888888889,
    16.666666666666668, 19.444444444444443, 22.222222222222221, 25.0,
    27.777777777777779, 30.555555555555554, 33.333333333333336 },

  /* Pooled Parameter (Expression: sc_sched.Map)
   * Referenced by:
   *   '<S4>/1-D Lookup Table3'
   *   '<S5>/1-D Lookup Table3'
   */
  { 0.81, 0.85, 0.88, 0.93, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S4>/1-D Lookup Table1'
   *   '<S5>/1-D Lookup Table1'
   */
  { 150.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0,
    2000.0, 2000.0, 2000.0, 2000.0, 2000.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
