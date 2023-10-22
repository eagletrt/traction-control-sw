/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.h
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.12
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Oct 19 11:53:57 2023
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
  real_T Integrator_DSTATE;            /* '<S41>/Integrator' */
  real_T Integrator_DSTATE_o;          /* '<S95>/Integrator' */
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
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S2>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S3>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S3>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S2>/1-D Lookup Table' : Unused code path elimination
 * Block '<S2>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S3>/1-D Lookup Table' : Unused code path elimination
 * Block '<S3>/1-D Lookup Table1' : Unused code path elimination
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
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Saturation Dynamic1'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Slip_est1'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/map'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/D Gain'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter ICs'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/I Gain'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator ICs'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Copy'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Gain'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/P Copy'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Parallel P Gain'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Reset Signal'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation Fdbk'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum Fdbk'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode Sum'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Integral'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Ngain'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/postSat Signal'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/preSat Signal'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/D Gain/Disabled'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter/Disabled'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Filter ICs/Disabled'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/I Gain/External Parameters'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator/Discrete'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/N Gain/Disabled'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/P Copy/Disabled'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Reset Signal/Disabled'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation/Enabled'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum/Sum_PI'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel1/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Saturation Dynamic1'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Slip_est1'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/map'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Anti-windup'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/D Gain'
 * '<S64>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Filter'
 * '<S65>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Filter ICs'
 * '<S66>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/I Gain'
 * '<S67>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Ideal P Gain'
 * '<S68>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S69>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Integrator'
 * '<S70>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Integrator ICs'
 * '<S71>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/N Copy'
 * '<S72>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/N Gain'
 * '<S73>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/P Copy'
 * '<S74>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Parallel P Gain'
 * '<S75>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Reset Signal'
 * '<S76>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Saturation'
 * '<S77>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Saturation Fdbk'
 * '<S78>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Sum'
 * '<S79>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Sum Fdbk'
 * '<S80>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tracking Mode'
 * '<S81>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tracking Mode Sum'
 * '<S82>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tsamp - Integral'
 * '<S83>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tsamp - Ngain'
 * '<S84>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/postSat Signal'
 * '<S85>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/preSat Signal'
 * '<S86>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S87>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S88>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S89>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/D Gain/Disabled'
 * '<S90>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Filter/Disabled'
 * '<S91>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Filter ICs/Disabled'
 * '<S92>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/I Gain/External Parameters'
 * '<S93>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S94>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S95>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Integrator/Discrete'
 * '<S96>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S97>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S98>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/N Gain/Disabled'
 * '<S99>'  : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/P Copy/Disabled'
 * '<S100>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S101>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Reset Signal/Disabled'
 * '<S102>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Saturation/Enabled'
 * '<S103>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S104>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Sum/Sum_PI'
 * '<S105>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S106>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S107>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S109>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S111>' : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/TCS Rear Right Wheel2/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_SlipV2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
