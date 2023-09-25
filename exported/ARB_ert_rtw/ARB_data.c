/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ARB_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: stiff_matrix
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  { 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0,
    20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0,
    20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0,
    20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0, 20000.0,
    20000.0, 20000.0, 20000.0 },

  /* Expression: ARBvel
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  { 0.0, 10.0, 20.0, 30.0, 40.0 },

  /* Expression: ARBdelta
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  { 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0 },

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  { 4U, 6U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
