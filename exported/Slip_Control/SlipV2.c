/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.c
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.38
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Dec  1 17:12:13 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SlipV2.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_SlipV2;            /* '<Root>/driver_request' */
real_T rtERROR_SlipV2;                 /* '<Root>/ERROR' */
real_T rtSteeringangle_SlipV2;         /* '<Root>/delta' */
real_T rtTel_Inp_SC_PeakTorque_SlipV2; /* '<Root>/Tel_Inp_SC_PeakTorque' */
real_T rtTel_Inp_SC_SpeedCutoff_SlipV2;/* '<Root>/Tel_Inp_SC_SpeedCutoff' */
real_T rtTel_Inp_SC_StartTorque_SlipV2;/* '<Root>/Tel_Inp_SC_StartTorque' */
real_T rtTm_rl_SlipV2;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_SlipV2;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_SlipV2;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_SlipV2;               /* '<Root>/Tm_rr' */
real_T rtbrake_SlipV2;                 /* '<Root>/Brake' */
real_T rtmap_sc_SlipV2;                /* '<Root>/map_sc' */
real_T rtmap_tv_SlipV2;                /* '<Root>/map_tv' */
real_T rtomega_rl_SlipV2;              /* '<Root>/omega_rl' */
real_T rtomega_rr_SlipV2;              /* '<Root>/omega_rr' */
real_T rtu_bar_SlipV2;                 /* '<Root>/u_bar' */
real_T rtyaw_rate_SlipV2;              /* '<Root>/Omega' */

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
void SlipV2_step(RT_MODEL_SlipV2 *const rtM_SlipV2)
{
  real_T T_max_nomap;
  real_T load_transf_coeff;
  real_T load_transf_coeff_tmp;
  real_T rtb_Product;
  real_T rtb_Product2;
  real_T rtb_T_max;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtTm_rr_SlipV2 * rtDriver_req_SlipV2;

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_SC_PeakTorque'
   *  Inport: '<Root>/Tel_Inp_SC_SpeedCutoff'
   *  Inport: '<Root>/Tel_Inp_SC_StartTorque'
   *  Inport: '<Root>/map_sc'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   *  Product: '<S1>/Product2'
   */
  rtb_Product2 = (rtTel_Inp_SC_PeakTorque_SlipV2 -
                  rtTel_Inp_SC_StartTorque_SlipV2) * fmin(fmax(rtu_bar_SlipV2 /
    rtTel_Inp_SC_SpeedCutoff_SlipV2, 0.0), 1.0) +
    rtTel_Inp_SC_StartTorque_SlipV2;
  T_max_nomap = rtb_Product2;
  load_transf_coeff_tmp = rtyaw_rate_SlipV2 * rtu_bar_SlipV2 * 61.217 / 4.0;
  load_transf_coeff = (load_transf_coeff_tmp + 411.00221250000004) /
    411.00221250000004;
  if (load_transf_coeff < 1.0) {
    T_max_nomap = rtb_Product2 * load_transf_coeff;
  }

  rtb_T_max = (rtb_Product - T_max_nomap) * (1.0 - rtmap_sc_SlipV2) +
    T_max_nomap;

  /* End of MATLAB Function: '<S1>/MATLAB Function2' */

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_T_max > rtTm_rr_SlipV2) {
    rtb_T_max = rtTm_rr_SlipV2;
  } else if (rtb_T_max < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_T_max = 0.0;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Product > rtb_T_max) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_SlipV2 = rtb_T_max;
  } else if (rtb_Product < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_SlipV2 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rr_m_SlipV2 = rtb_Product;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Product: '<S1>/Product1' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtDriver_req_SlipV2 * rtTm_rl_SlipV2;

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/map_sc'
   */
  T_max_nomap = rtb_Product2;
  load_transf_coeff = (411.00221250000004 - load_transf_coeff_tmp) /
    411.00221250000004;
  if (load_transf_coeff < 1.0) {
    T_max_nomap = rtb_Product2 * load_transf_coeff;
  }

  rtb_Product2 = (rtb_Product - T_max_nomap) * (1.0 - rtmap_sc_SlipV2) +
    T_max_nomap;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Product2 > rtTm_rl_SlipV2) {
    rtb_Product2 = rtTm_rl_SlipV2;
  } else if (rtb_Product2 < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    rtb_Product2 = 0.0;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Outport: '<Root>/ERROR' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtERROR_SlipV2 = rtb_T_max - rtb_Product2;

  /* Switch: '<S7>/Switch2' incorporates:
   *  Constant: '<S1>/Constant3'
   *  RelationalOperator: '<S7>/LowerRelop1'
   *  RelationalOperator: '<S7>/UpperRelop'
   *  Switch: '<S7>/Switch'
   */
  if (rtb_Product > rtb_Product2) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_SlipV2 = rtb_Product2;
  } else if (rtb_Product < 0.0) {
    /* Switch: '<S7>/Switch' incorporates:
     *  Constant: '<S1>/Constant3'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_SlipV2 = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S7>/Switch'
     */
    rtTm_rl_a_SlipV2 = rtb_Product;
  }

  /* End of Switch: '<S7>/Switch2' */
  UNUSED_PARAMETER(rtM_SlipV2);
}

/* Model initialize function */
void SlipV2_initialize(RT_MODEL_SlipV2 *const rtM_SlipV2)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(rtM_SlipV2, (NULL));

  /* Storage classes */
  rtDriver_req_SlipV2 = 0.0;
  rtu_bar_SlipV2 = 0.0;
  rtomega_rr_SlipV2 = 0.0;
  rtomega_rl_SlipV2 = 0.0;
  rtyaw_rate_SlipV2 = 0.0;
  rtSteeringangle_SlipV2 = 0.0;
  rtbrake_SlipV2 = 0.0;
  rtTm_rl_SlipV2 = 0.0;
  rtTm_rr_SlipV2 = 0.0;
  rtmap_tv_SlipV2 = 0.0;
  rtmap_sc_SlipV2 = 0.0;
  rtTel_Inp_SC_StartTorque_SlipV2 = 0.0;
  rtTel_Inp_SC_PeakTorque_SlipV2 = 0.0;
  rtTel_Inp_SC_SpeedCutoff_SlipV2 = 0.0;

  /* Storage classes */
  rtTm_rr_m_SlipV2 = 0.0;
  rtTm_rl_a_SlipV2 = 0.0;
  rtERROR_SlipV2 = 0.0;
  UNUSED_PARAMETER(rtM_SlipV2);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
