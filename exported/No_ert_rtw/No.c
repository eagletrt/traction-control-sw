/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: No.c
 *
 * Code generated for Simulink model 'No'.
 *
 * Model version                  : 5.308
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Nov 21 17:49:20 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "No.h"
#include "rtwtypes.h"

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req;                   /* '<Root>/driver_request' */
real_T rtSteeringangle;                /* '<Root>/delta' */
real_T rtTm_rl;                        /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a;                      /* '<Root>/Tm_rl' */
real_T rtTm_rr;                        /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m;                      /* '<Root>/Tm_rr' */
real_T rtbrake;                        /* '<Root>/Brake' */
real_T rtmap_sc;                       /* '<Root>/map_sc' */
real_T rtmap_tv;                       /* '<Root>/map_tv' */
real_T rtomega_rl;                     /* '<Root>/omega_rl' */
real_T rtomega_rr;                     /* '<Root>/omega_rr' */
real_T rtu_bar;                        /* '<Root>/u_bar' */
real_T rtyaw_rate;                     /* '<Root>/Omega' */

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
void No_step(RT_MODEL *const rtM)
{
  /* Outport: '<Root>/Tm_rr' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S1>/Product'
   */
  rtTm_rr_m = rtDriver_req * rtTm_rr;

  /* Outport: '<Root>/Tm_rl' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S1>/Product1'
   */
  rtTm_rl_a = rtTm_rl * rtDriver_req;
  UNUSED_PARAMETER(rtM);
}

/* Model initialize function */
void No_initialize(RT_MODEL *const rtM)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(rtM, (NULL));

  /* Storage classes */
  rtTm_rr_m = 0.0;
  rtTm_rl_a = 0.0;

  /* Storage classes */
  rtDriver_req = 0.0;
  rtu_bar = 0.0;
  rtomega_rr = 0.0;
  rtomega_rl = 0.0;
  rtyaw_rate = 0.0;
  rtSteeringangle = 0.0;
  rtbrake = 0.0;
  rtTm_rl = 0.0;
  rtTm_rr = 0.0;
  rtmap_tv = 0.0;
  rtmap_sc = 0.0;
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
