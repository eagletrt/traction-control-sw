/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.h
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.300
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Aug 30 19:02:51 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SLIP_h_
#define RTW_HEADER_SLIP_h_
#ifndef SLIP_COMMON_INCLUDES_
#define SLIP_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* SLIP_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_SLIP RT_MODEL_SLIP;

#ifndef DEFINED_TYPEDEF_FOR_debug_bus_
#define DEFINED_TYPEDEF_FOR_debug_bus_

typedef struct {
  real_T lambda;
  real_T filtered_lambda_error;
  real_T shallow_filtered_lambda_error;
  real_T proportional;
  real_T integral;
  real_T derivative;
} debug_bus;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[100];            /* '<S15>/Delay' */
  real_T Delay_DSTATE_j[100];          /* '<S5>/Delay' */
  real_T DelayOneStep2_DSTATE;         /* '<S15>/Delay One Step2' */
  real_T DelayOneStep_DSTATE;          /* '<S19>/Delay One Step' */
  real_T DelayOneStep1_DSTATE;         /* '<S15>/Delay One Step1' */
  real_T DelayOneStep2_DSTATE_f;       /* '<S5>/Delay One Step2' */
  real_T DelayOneStep_DSTATE_h;        /* '<S9>/Delay One Step' */
  real_T DelayOneStep1_DSTATE_c;       /* '<S5>/Delay One Step1' */
  boolean_T IC2_FirstOutputTime;       /* '<S15>/IC2' */
  boolean_T IC1_FirstOutputTime;       /* '<S15>/IC1' */
  boolean_T IC2_FirstOutputTime_g;     /* '<S5>/IC2' */
  boolean_T IC1_FirstOutputTime_n;     /* '<S5>/IC1' */
} DW_SLIP;

/* Real-time Model Data Structure */
struct tag_RTM_SLIP {
  const char_T * volatile errorStatus;
  DW_SLIP *dwork;
};

/* External data declarations for dependent source files */
extern const debug_bus SLIP_rtZdebug_bus;/* debug_bus ground */

/* Model entry point functions */
extern void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M);
extern void SLIP_step(RT_MODEL_SLIP *const SLIP_M);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T SLIP_T_max;              /* '<Root>/in_T_max' */
extern real_T SLIP_in_Kd;              /* '<Root>/in_Kd' */
extern real_T SLIP_in_Ki;              /* '<Root>/in_Ki' */
extern real_T SLIP_in_Kp;              /* '<Root>/in_Kp' */
extern real_T SLIP_in_iteration_step_seconds;/* '<Root>/in_iteration_step_seconds' */
extern real_T SLIP_in_lambda_reference;/* '<Root>/in_lambda_reference' */
extern real_T SLIP_in_minimum_torque;  /* '<Root>/in_minimum_torque' */
extern real_T SLIP_in_omega_rl;        /* '<Root>/in_omega_rl' */
extern real_T SLIP_in_omega_rr;        /* '<Root>/in_omega_rr' */
extern real_T SLIP_in_window_size_seconds;/* '<Root>/in_window_size_seconds' */
extern real_T SLIP_out_T_max_rl_slip;  /* '<Root>/out_T_max_rl_slip' */
extern real_T SLIP_out_T_max_rr_slip;  /* '<Root>/out_T_max_rr_slip' */
extern real_T SLIP_out_T_motor_rl;     /* '<Root>/out_T_motor_rl' */
extern real_T SLIP_out_T_motor_rr;     /* '<Root>/out_T_motor_rr' */
extern debug_bus SLIP_out_debug_bus_rl;/* '<Root>/out_debug_bus_rl' */
extern debug_bus SLIP_out_debug_bus_rr;/* '<Root>/out_debug_bus_rr' */
extern real_T SLIP_throttle;           /* '<Root>/throttle' */
extern real_T SLIP_u;                  /* '<Root>/in_u_bar' */
extern real_T SLIP_yaw_rate;           /* '<Root>/in_yaw_rate' */
extern real_T in_differentiation_step_seconds;
                                  /* '<Root>/in_differentiation_step_seconds' */
extern real_T in_shallow_window_size_seconds;
                                   /* '<Root>/in_shallow_window_size_seconds' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S5>/Scope1' : Unused code path elimination
 * Block '<S5>/Scope2' : Unused code path elimination
 * Block '<S5>/Scope3' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S2>/Scope5' : Unused code path elimination
 * Block '<S2>/Scope6' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S15>/Scope2' : Unused code path elimination
 * Block '<S15>/Scope3' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S17>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S3>/Scope2' : Unused code path elimination
 * Block '<S3>/Scope3' : Unused code path elimination
 * Block '<S3>/Scope4' : Unused code path elimination
 * Block '<S3>/Scope5' : Unused code path elimination
 * Block '<S3>/Scope6' : Unused code path elimination
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
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/SLIP')    - opens subsystem Fenice_Vehicle_Model/Vehicle Controller/SLIP
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/SLIP/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_Vehicle_Model/Vehicle Controller'
 * '<S1>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP'
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Compare To Constant'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Saturation Dynamic1'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Saturation Dynamic2'
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Slip_estimation'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID/Integral Part'
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID/MATLAB Function1'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID/MATLAB Function2'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID/Proportional Part'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference/Low Level PID/Integral Part/MATLAB Function'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Compare To Constant'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Saturation Dynamic1'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Saturation Dynamic2'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Slip_estimation'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID/Integral Part'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID/MATLAB Function1'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID/MATLAB Function2'
 * '<S22>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID/Proportional Part'
 * '<S23>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/Subsystem Reference1/Low Level PID/Integral Part/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_SLIP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
