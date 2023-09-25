/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Velocity_Estimation.h
 *
 * Code generated for Simulink model 'Velocity_Estimation'.
 *
 * Model version                  : 5.305
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Sep  5 11:19:11 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Velocity_Estimation_h_
#define RTW_HEADER_Velocity_Estimation_h_
#ifndef Velocity_Estimation_COMMON_INCLUDES_
#define Velocity_Estimation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                /* Velocity_Estimation_COMMON_INCLUDES_ */

#include <string.h>

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteFilter1_states;       /* '<S4>/Discrete Filter1' */
  real_T DiscreteFilter1_denStates;    /* '<S4>/Discrete Filter1' */
  real_T UnitDelay_DSTATE;             /* '<S4>/Unit Delay' */
  real_T DiscreteFilter2_states;       /* '<S4>/Discrete Filter2' */
  real_T DiscreteFilter2_denStates;    /* '<S4>/Discrete Filter2' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [0.2 0.3 0.4 0.6 0.8 1]
   * Referenced by: '<S1>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_tableData[6];

  /* Expression: [1 2 3 4 5 6]
   * Referenced by: '<S1>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_bp01Data[6];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Velocity_Estimation_initialize(RT_MODEL *const rtM);
extern void Velocity_Estimation_step(RT_MODEL *const rtM);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtTmax_rl;               /* '<Root>/Tmax_rl' */
extern real_T rtTmax_rr;               /* '<Root>/Tmax_rr' */
extern real_T rtaxG;                   /* '<Root>/a_x' */
extern real_T rtmap_motor;             /* '<Root>/map' */
extern real_T rtomega_fl;              /* '<Root>/omega_fl' */
extern real_T rtomega_fr;              /* '<Root>/omega_fr' */
extern real_T rtomega_rl;              /* '<Root>/omega_rl' */
extern real_T rtomega_rr;              /* '<Root>/omega_rr' */
extern real_T rtu_bar;                 /* '<Root>/u_bar' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/To Workspace' : Unused code path elimination
 * Block '<S1>/Buffer' : Eliminated nontunable gain of 1
 * Block '<S1>/Max motor torque' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation/MATLAB Function'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation/MATLAB Function1'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/Velocity_Estimation/Velocity_Panzani'
 */
#endif                                 /* RTW_HEADER_Velocity_Estimation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
