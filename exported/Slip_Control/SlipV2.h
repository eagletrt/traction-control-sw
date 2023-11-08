/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.h
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.17
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Nov  6 16:53:02 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SlipV2_h_
#define RTW_HEADER_SlipV2_h_
#ifndef SlipV2_COMMON_INCLUDES_
#define SlipV2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* SlipV2_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_SlipV2 RT_MODEL_SlipV2;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S97>/Integrator' */
  real_T Integrator_DSTATE_o;          /* '<S42>/Integrator' */
} DW_SlipV2;

/* Real-time Model Data Structure */
struct tag_RTM_SlipV2 {
  const char_T * volatile errorStatus;
  DW_SlipV2 *dwork;
};

/* Model entry point functions */
extern void SlipV2_initialize(RT_MODEL_SlipV2 *const rtM_SlipV2);
extern void SlipV2_step(RT_MODEL_SlipV2 *const rtM_SlipV2);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_SlipV2;     /* '<Root>/driver_request' */
extern real_T rtSteeringangle_SlipV2;  /* '<Root>/delta' */
extern real_T rtTm_rl_SlipV2;          /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_SlipV2;        /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_SlipV2;          /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_SlipV2;        /* '<Root>/Tm_rr' */
extern real_T rtbrake_SlipV2;          /* '<Root>/Brake' */
extern real_T rtmap_sc_SlipV2;         /* '<Root>/map_sc' */
extern real_T rtmap_tv_SlipV2;         /* '<Root>/map_tv' */
extern real_T rtomega_rl_SlipV2;       /* '<Root>/omega_rl' */
extern real_T rtomega_rr_SlipV2;       /* '<Root>/omega_rr' */
extern real_T rtu_bar_SlipV2;          /* '<Root>/u_bar' */
extern real_T rtyaw_rate_SlipV2;       /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S61>/Data Type Duplicate' : Unused code path elimination
 * Block '<S61>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S2>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S2>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S2>/Manual Switch2' : Eliminated due to constant selection input
 * Block '<S3>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S3>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S3>/Manual Switch2' : Eliminated due to constant selection input
 * Block '<S2>/1-D Lookup Table' : Unused code path elimination
 * Block '<S2>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S2>/Constant8' : Unused code path elimination
 * Block '<S3>/1-D Lookup Table' : Unused code path elimination
 * Block '<S3>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S3>/Constant8' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/SlipV2')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/SlipV2
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/SlipV2/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Saturation Dynamic1'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Saturation Dynamic2'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Slip_est1'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/map'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/D Gain'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Filter'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Filter ICs'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/I Gain'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Integrator'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Integrator ICs'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/N Copy'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/N Gain'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/P Copy'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Parallel P Gain'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Reset Signal'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Saturation'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Saturation Fdbk'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Sum'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Sum Fdbk'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode Sum'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Integral'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Ngain'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/postSat Signal'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/preSat Signal'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/D Gain/Disabled'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Filter/Disabled'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Filter ICs/Disabled'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/I Gain/External Parameters'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Integrator/Discrete'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/N Gain/Disabled'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/P Copy/Disabled'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Reset Signal/Disabled'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Saturation/Enabled'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Sum/Sum_PI'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Left Wheel/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Saturation Dynamic1'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Saturation Dynamic2'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Slip_est1'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/map'
 * '<S64>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup'
 * '<S65>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/D Gain'
 * '<S66>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter'
 * '<S67>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter ICs'
 * '<S68>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/I Gain'
 * '<S69>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain'
 * '<S70>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S71>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator'
 * '<S72>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator ICs'
 * '<S73>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Copy'
 * '<S74>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Gain'
 * '<S75>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/P Copy'
 * '<S76>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Parallel P Gain'
 * '<S77>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Reset Signal'
 * '<S78>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation'
 * '<S79>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation Fdbk'
 * '<S80>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum'
 * '<S81>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum Fdbk'
 * '<S82>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode'
 * '<S83>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode Sum'
 * '<S84>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Integral'
 * '<S85>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Ngain'
 * '<S86>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/postSat Signal'
 * '<S87>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/preSat Signal'
 * '<S88>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S89>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S90>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S91>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/D Gain/Disabled'
 * '<S92>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter/Disabled'
 * '<S93>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter ICs/Disabled'
 * '<S94>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/I Gain/External Parameters'
 * '<S95>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S96>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S97>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator/Discrete'
 * '<S98>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S99>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S100>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Gain/Disabled'
 * '<S101>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/P Copy/Disabled'
 * '<S102>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S103>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Reset Signal/Disabled'
 * '<S104>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation/Enabled'
 * '<S105>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S106>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum/Sum_PI'
 * '<S107>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S108>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S109>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S110>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S111>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S112>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S113>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_SlipV2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
