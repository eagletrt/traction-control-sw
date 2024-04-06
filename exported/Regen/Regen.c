/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Regen.c
 *
 * Code generated for Simulink model 'Regen'.
 *
 * Model version                  : 6.57
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Apr  6 09:22:03 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Regen.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported data definition */

/* Data with Exported storage */
real_T Regen_Driver_req;               /* '<Root>/Inp_driver_request' */
real_T Regen_Inp_map_sc;               /* '<Root>/Inp_map_sc' */
real_T Regen_Inp_omega_inv_rl;         /* '<Root>/Inp_omega_inv_rl' */
real_T Regen_Inp_omega_inv_rr;         /* '<Root>/Inp_omega_inv_rr' */
real_T Regen_Out_Tm_rl;                /* '<Root>/Out_Tm_rl' */
real_T Regen_Out_Tm_rr;                /* '<Root>/Out_Tm_rr' */
real_T Regen_Out_brake_balance;        /* '<Root>/Out_brake_balance' */
real_T Regen_Tm_rl;                    /* '<Root>/Inp_Tmax_rl' */
real_T Regen_Tm_rr;                    /* '<Root>/Inp_Tmax_rr' */
real_T Regen_pressure_f;               /* '<Root>/Inp_pressure_f' */
real_T Regen_pressure_r;               /* '<Root>/Inp_pressure_r' */

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/* Model step function */
void Regen_step(RT_MODEL_Regen *const Regen_M)
{
  real_T Fx_f;
  real_T Fx_f_tmp;
  real_T Fx_f_tmp_0;
  real_T rtb_Gain2;
  real_T tmp;

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Inport: '<Root>/Inp_pressure_f'
   *  MATLAB Function: '<S1>/MATLAB Function4'
   */
  Fx_f_tmp = -Regen_pressure_f * 0.1 * 490.62500000000006 * 4.0 * 0.42;
  Fx_f = Fx_f_tmp * 69.0 / 203.0;

  /* MATLAB Function: '<S1>/MATLAB Function3' incorporates:
   *  Inport: '<Root>/Inp_omega_inv_rl'
   */
  if (Regen_Inp_omega_inv_rl <= 300.0) {
    rtb_Gain2 = -20.42861;
  } else {
    rtb_Gain2 = 0.0607143 * Regen_Inp_omega_inv_rl - 38.6429;
  }

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/Inp_omega_inv_rr'
   */
  if (Regen_Inp_omega_inv_rr <= 300.0) {
    tmp = -20.42861;
  } else {
    tmp = 0.0607143 * Regen_Inp_omega_inv_rr - 38.6429;
  }

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Inport: '<Root>/Inp_pressure_r'
   *  MATLAB Function: '<S1>/MATLAB Function4'
   */
  Fx_f_tmp_0 = -Regen_pressure_r * 0.1 * 490.62500000000006 * 2.0 * 0.42;

  /* MinMax: '<S1>/Min' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/Inp_map_sc'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   *  MATLAB Function: '<S1>/MATLAB Function2'
   *  MATLAB Function: '<S1>/MATLAB Function3'
   *  Product: '<S1>/Product2'
   */
  Fx_f = fmax(fmax((((3198.788742857143 - sqrt(4.092899768571832E+7 -
    4.1425668E+7 * Fx_f / 875.0) / 2.0) - Fx_f) * 203.0 / 78.75 - Fx_f_tmp_0) *
                   78.75 * 0.001 * (2.0 * Regen_Inp_map_sc), rtb_Gain2), tmp);

  /* Switch: '<S7>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S7>/LowerRelop1'
   */
  if (Fx_f > 59.737156511350051) {
    Fx_f = 59.737156511350051;
  }

  /* End of Switch: '<S7>/Switch2' */

  /* Gain: '<S1>/Gain2' */
  rtb_Gain2 = 0.5 * Fx_f;

  /* Outport: '<Root>/Out_Tm_rr' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_driver_request'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add'
   */
  Regen_Out_Tm_rr = Regen_Driver_req * Regen_Tm_rr + rtb_Gain2;

  /* Outport: '<Root>/Out_Tm_rl' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  Inport: '<Root>/Inp_driver_request'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Add1'
   */
  Regen_Out_Tm_rl = Regen_Tm_rl * Regen_Driver_req + rtb_Gain2;

  /* MATLAB Function: '<S1>/MATLAB Function4' */
  rtb_Gain2 = Fx_f_tmp * 0.069;

  /* Outport: '<Root>/Out_brake_balance' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   *  MATLAB Function: '<S1>/MATLAB Function4'
   */
  Regen_Out_brake_balance = rtb_Gain2 / ((Fx_f * 4.5 * 0.93 + rtb_Gain2) +
    Fx_f_tmp_0 * 0.07875);
  UNUSED_PARAMETER(Regen_M);
}

/* Model initialize function */
void Regen_initialize(RT_MODEL_Regen *const Regen_M)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Regen_M, (NULL));

  /* Storage classes */
  Regen_pressure_f = 0.0;
  Regen_pressure_r = 0.0;
  Regen_Inp_omega_inv_rl = 0.0;
  Regen_Inp_omega_inv_rr = 0.0;
  Regen_Driver_req = 0.0;
  Regen_Tm_rl = 0.0;
  Regen_Tm_rr = 0.0;
  Regen_Inp_map_sc = 0.0;

  /* Storage classes */
  Regen_Out_Tm_rr = 0.0;
  Regen_Out_Tm_rl = 0.0;
  Regen_Out_brake_balance = 0.0;
  UNUSED_PARAMETER(Regen_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
