/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.h
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.17
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Nov  6 16:49:11 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Torque_h_
#define RTW_HEADER_Torque_h_
#ifndef Torque_COMMON_INCLUDES_
#define Torque_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Torque_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Torque RT_MODEL_Torque;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S46>/Integrator' */
} DW_Torque;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S9>/1-D Lookup Table2'
   */
  real_T pooled1[2];

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S9>/P_table'
   */
  real_T P_table_tableData[2];

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S9>/I_table'
   *   '<S9>/P_table'
   */
  real_T pooled2[2];

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S9>/I_table'
   */
  real_T I_table_tableData[2];
} ConstP_Torque;

/* Real-time Model Data Structure */
struct tag_RTM_Torque {
  const char_T * volatile errorStatus;
  DW_Torque *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP_Torque rtConstP_Torque;

/* Model entry point functions */
extern void Torque_initialize(RT_MODEL_Torque *const rtM_Torque);
extern void Torque_step(RT_MODEL_Torque *const rtM_Torque);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_Torque;     /* '<Root>/driver_request' */
extern real_T rtSteeringangle_Torque;  /* '<Root>/delta' */
extern real_T rtTm_rl_Torque;          /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_Torque;        /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_Torque;          /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_Torque;        /* '<Root>/Tm_rr' */
extern real_T rtbrake_Torque;          /* '<Root>/Brake' */
extern real_T rtmap_sc_Torque;         /* '<Root>/map_sc' */
extern real_T rtmap_tv_Torque;         /* '<Root>/map_tv' */
extern real_T rtomega_rl_Torque;       /* '<Root>/omega_rl' */
extern real_T rtomega_rr_Torque;       /* '<Root>/omega_rr' */
extern real_T rtu_bar_Torque;          /* '<Root>/u_bar' */
extern real_T rtyaw_rate_Torque;       /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S54>/Data Type Duplicate' : Unused code path elimination
 * Block '<S54>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/deltaT' : Unused code path elimination
 * Block '<S2>/deltarad' : Unused code path elimination
 * Block '<S2>/errore' : Unused code path elimination
 * Block '<S2>/omega' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S8>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S8>/K_us_table' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Torque vectoring')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/Torque vectoring
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation Dynamic'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation Dynamic1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation block'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Steering angle > 2deg'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/SteeringModel'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate estimator '
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate estimator /Yaw-Rate'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/D Gain'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter ICs'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/I Gain'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Copy'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Gain'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/P Copy'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Reset Signal'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/postSat Signal'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/preSat Signal'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/D Gain/Disabled'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter/Disabled'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter ICs/Disabled'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/I Gain/External Parameters'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator/Discrete'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Gain/Disabled'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/P Copy/Disabled'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Reset Signal/Disabled'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation/External'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation/External/Saturation Dynamic'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum/Sum_PI'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate tracking/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_Torque_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
