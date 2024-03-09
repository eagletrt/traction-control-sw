/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.h
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.32
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Mar  9 12:22:29 2024
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
  real_T Integrator_DSTATE;            /* '<S41>/Integrator' */
} DW_Torque;

/* Real-time Model Data Structure */
struct tag_RTM_Torque {
  const char_T * volatile errorStatus;
  DW_Torque *dwork;
};

/* Model entry point functions */
extern void Torque_initialize(RT_MODEL_Torque *const rtM_Torque);
extern void Torque_step(RT_MODEL_Torque *const rtM_Torque);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_Torque;     /* '<Root>/driver_request' */
extern real_T rtSteeringangle_Torque;  /* '<Root>/delta' */
extern real_T rtTel_Inp_Ki_Torque;     /* '<Root>/Tel_Inp_Ki' */
extern real_T rtTel_Inp_Kp_Torque;     /* '<Root>/Tel_Inp_Kp' */
extern real_T rtTel_Inp_Kus_Torque;    /* '<Root>/Tel_Inp_Kus' */
extern real_T rtTel_Out_Debug_Torque_Torque;/* '<Root>/Tel_Out_Debug_Torque' */
extern real_T rtTm_rl_Torque;          /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_Torque;        /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_Torque;          /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_Torque;        /* '<Root>/Tm_rr' */
extern real_T rtbrake_Torque;          /* '<Root>/Brake' */
extern real_T rtlambda_rr_Torque;      /* '<Root>/Tmax_rr_Slip' */
extern real_T rtlambda_rr_n_Torque;    /* '<Root>/Tmax_rl_Slip' */
extern real_T rtmap_sc_Torque;         /* '<Root>/map_sc' */
extern real_T rtmap_tv_Torque;         /* '<Root>/map_TV' */
extern real_T rtomega_rl_Torque;       /* '<Root>/omega_rl' */
extern real_T rtomega_rr_Torque;       /* '<Root>/omega_rr' */
extern real_T rtu_bar_Torque;          /* '<Root>/u_bar' */
extern real_T rtyaw_rate_Torque;       /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/deltarad' : Unused code path elimination
 * Block '<S3>/errore' : Unused code path elimination
 * Block '<S3>/omega' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
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
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring')    - opens subsystem Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_Vehicle_Model/Vehicle Controller'
 * '<S1>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring'
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/MATLAB Function'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Steering angle > 2deg1'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/SteeringModel'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate estimator '
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Anti-windup'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/D Gain'
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Filter'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Filter ICs'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/I Gain'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Ideal P Gain'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Integrator'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Integrator ICs'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/N Copy'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/N Gain'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/P Copy'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Parallel P Gain'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Reset Signal'
 * '<S22>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Saturation'
 * '<S23>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Saturation Fdbk'
 * '<S24>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Sum'
 * '<S25>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Sum Fdbk'
 * '<S26>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tracking Mode'
 * '<S27>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tracking Mode Sum'
 * '<S28>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tsamp - Integral'
 * '<S29>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tsamp - Ngain'
 * '<S30>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/postSat Signal'
 * '<S31>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/preSat Signal'
 * '<S32>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S33>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S34>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S35>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/D Gain/Disabled'
 * '<S36>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Filter/Disabled'
 * '<S37>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Filter ICs/Disabled'
 * '<S38>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/I Gain/External Parameters'
 * '<S39>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S40>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S41>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Integrator/Discrete'
 * '<S42>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S43>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S44>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/N Gain/Disabled'
 * '<S45>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/P Copy/Disabled'
 * '<S46>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S47>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Reset Signal/Disabled'
 * '<S48>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Saturation/Enabled'
 * '<S49>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S50>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Sum/Sum_PI'
 * '<S51>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S52>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S53>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S54>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tsamp - Integral/TsSignalSpecification'
 * '<S55>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S56>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S57>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S58>'  : 'Fenice_Vehicle_Model/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate estimator /Yaw-Rate'
 */
#endif                                 /* RTW_HEADER_Torque_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
