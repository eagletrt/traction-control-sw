/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0_data.c
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 6.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Sep 26 16:59:25 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "All0.h"

/* Constant parameters (default storage) */
const ConstP_All0 rtConstP_All0 = {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S10>/1-D Lookup Table2'
   *   '<S65>/1-D Lookup Table2'
   *   '<S66>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S65>/1-D Lookup Table'
   *   '<S66>/1-D Lookup Table'
   */
  { 30.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0, 170.0,
    170.0, 170.0, 170.0 },

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S65>/1-D Lookup Table'
   *   '<S65>/1-D Lookup Table1'
   *   '<S66>/1-D Lookup Table'
   *   '<S66>/1-D Lookup Table1'
   */
  { 0.0, 1.3888888888888888, 2.7777777777777777, 5.5555555555555554,
    8.3333333333333339, 11.111111111111111, 13.888888888888889,
    16.666666666666668, 19.444444444444443, 22.222222222222221, 25.0,
    27.777777777777779, 30.555555555555554, 33.333333333333336 },

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S9>/K_us_table'
   */
  { 0.000153, 0.000226, 0.000267, 0.000307, 0.000355, 0.000409 },

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S9>/K_us_table'
   */
  { 30.0, 40.0, 50.0, 60.0, 70.0, 80.0 },

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S10>/P_table'
   */
  { 570.33177, 570.443555, 570.500875, 570.527051, 570.540698, 570.547337,
    570.550509, 570.552078 },

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S10>/I_table'
   *   '<S10>/P_table'
   */
  { 5.555556, 8.333333, 11.111111, 13.888889, 16.666667, 19.444444, 22.222222,
    25.0 },

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S10>/I_table'
   */
  { 947.145201, 946.822102, 946.645372, 946.562035, 946.516717, 946.494749,
    946.484338, 946.479506 },

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S65>/1-D Lookup Table1'
   *   '<S66>/1-D Lookup Table1'
   */
  { 150.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0, 2000.0,
    2000.0, 2000.0, 2000.0, 2000.0, 2000.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
