/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TV.h
 *
 * Code generated for Simulink model 'TV'.
 *
 * Model version                  : 6.61
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Mon Apr  8 10:17:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_TV_h_
#define RTW_HEADER_TV_h_
#ifndef TV_COMMON_INCLUDES_
#define TV_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* TV_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_TV RT_MODEL_TV;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S43>/Integrator' */
} DW_TV;

/* Real-time Model Data Structure */
struct tag_RTM_TV {
  const char_T * volatile errorStatus;
  DW_TV *dwork;
};

/* Model entry point functions */
extern void TV_initialize(RT_MODEL_TV *const TV_M);
extern void TV_step(RT_MODEL_TV *const TV_M);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T TV_Driver_req;           /* '<Root>/Inp_driver_request' */
extern real_T TV_Inp_Ki;               /* '<Root>/Inp_Ki' */
extern real_T TV_Inp_Kp;               /* '<Root>/Inp_Kp' */
extern real_T TV_Inp_Kus;              /* '<Root>/Inp_Kus' */
extern real_T TV_Out_Debug_Torque;     /* '<Root>/Out_Debug_Torque' */
extern real_T TV_Out_Tm_rl;            /* '<Root>/Out_Tm_rl' */
extern real_T TV_Out_Tm_rr;            /* '<Root>/Out_Tm_rr' */
extern real_T TV_Steeringangle;        /* '<Root>/Inp_delta' */
extern real_T TV_Tm_rl;                /* '<Root>/Inp_Tmax_rl' */
extern real_T TV_Tm_rr;                /* '<Root>/Inp_Tmax_rr' */
extern real_T TV_lambda_rr;            /* '<Root>/Inp_Tmax_rr_Slip' */
extern real_T TV_lambda_rr_n;          /* '<Root>/Inp_Tmax_rl_Slip' */
extern real_T TV_map_tv;               /* '<Root>/Inp_map_TV' */
extern real_T TV_u_bar;                /* '<Root>/Inp_u_bar' */
extern real_T TV_yaw_rate;             /* '<Root>/Inp_Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/deltarad' : Unused code path elimination
 * Block '<S3>/errore' : Unused code path elimination
 * Block '<S3>/omega' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
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
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/TV')    - opens subsystem Fenice_Vehicle_Model/Vehicle Controller/TV
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/TV/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_Vehicle_Model/Vehicle Controller'
 * '<S1>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV'
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/MATLAB Function'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/Saturation Dynamic'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/Saturation Dynamic1'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Steering angle > 2deg1'
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/SteeringModel'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Yaw-Rate estimator '
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Anti-windup'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/D Gain'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Filter'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Filter ICs'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/I Gain'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Ideal P Gain'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Integrator'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Integrator ICs'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/N Copy'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/N Gain'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/P Copy'
 * '<S22>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Parallel P Gain'
 * '<S23>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Reset Signal'
 * '<S24>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Saturation'
 * '<S25>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Saturation Fdbk'
 * '<S26>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Sum'
 * '<S27>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Sum Fdbk'
 * '<S28>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tracking Mode'
 * '<S29>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tracking Mode Sum'
 * '<S30>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tsamp - Integral'
 * '<S31>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tsamp - Ngain'
 * '<S32>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/postSat Signal'
 * '<S33>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/preSat Signal'
 * '<S34>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S35>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S36>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S37>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/D Gain/Disabled'
 * '<S38>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Filter/Disabled'
 * '<S39>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Filter ICs/Disabled'
 * '<S40>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/I Gain/External Parameters'
 * '<S41>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S42>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S43>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Integrator/Discrete'
 * '<S44>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S45>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S46>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/N Gain/Disabled'
 * '<S47>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/P Copy/Disabled'
 * '<S48>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S49>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Reset Signal/Disabled'
 * '<S50>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Saturation/Enabled'
 * '<S51>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S52>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Sum/Sum_PI'
 * '<S53>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S54>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S55>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tsamp - Integral/TsSignalSpecification'
 * '<S57>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S59>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S60>'  : 'Fenice_Vehicle_Model/Vehicle Controller/TV/PI Control/Yaw-Rate estimator /Yaw-Rate'
 */
#endif                                 /* RTW_HEADER_TV_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
