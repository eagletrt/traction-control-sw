/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AllControl.h
 *
 * Code generated for Simulink model 'AllControl'.
 *
 * Model version                  : 6.39
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Dec  2 16:40:32 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_AllControl_h_
#define RTW_HEADER_AllControl_h_
#ifndef AllControl_COMMON_INCLUDES_
#define AllControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* AllControl_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_AllControl RT_MODEL_AllControl;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S51>/Integrator' */
} DW_AllControl;

/* Real-time Model Data Structure */
struct tag_RTM_AllControl {
  const char_T * volatile errorStatus;
  DW_AllControl *dwork;
};

/* Model entry point functions */
extern void AllControl_initialize(RT_MODEL_AllControl *const rtM_AllControl);
extern void AllControl_step(RT_MODEL_AllControl *const rtM_AllControl);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_AllControl; /* '<Root>/driver_request' */
extern real_T rtSteeringangle_AllControl;/* '<Root>/delta' */
extern real_T rtTel_Inp_SC_PeakTorque_AllCont;/* '<Root>/Tel_Inp_SC_PeakTorque' */
extern real_T rtTel_Inp_SC_SpeedCutoff_AllCon;/* '<Root>/Tel_Inp_SC_SpeedCutoff' */
extern real_T rtTel_Inp_SC_StartTorque_AllCon;/* '<Root>/Tel_Inp_SC_StartTorque' */
extern real_T rtTel_Inp_TV_Ki_AllControl;/* '<Root>/Tel_Inp_TV_Ki' */
extern real_T rtTel_Inp_TV_Kp_AllControl;/* '<Root>/Tel_Inp_TV_Kp' */
extern real_T rtTel_Inp_TV_Kus_AllControl;/* '<Root>/Tel_Inp_TV_Kus' */
extern real_T rtTel_Out_error_AllControl;/* '<Root>/Tel_Out_error' */
extern real_T rtTm_rl_AllControl;      /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_AllControl;    /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_AllControl;      /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_AllControl;    /* '<Root>/Tm_rr' */
extern real_T rtbrake_AllControl;      /* '<Root>/Brake' */
extern real_T rtmap_sc_AllControl;     /* '<Root>/map_sc' */
extern real_T rtmap_tv_AllControl;     /* '<Root>/map_TV' */
extern real_T rtomega_rl_AllControl;   /* '<Root>/omega_rl' */
extern real_T rtomega_rr_AllControl;   /* '<Root>/omega_rr' */
extern real_T rtu_bar_AllControl;      /* '<Root>/u_bar' */
extern real_T rtyaw_rate_AllControl;   /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S5>/deltarad' : Unused code path elimination
 * Block '<S5>/errore' : Unused code path elimination
 * Block '<S5>/omega' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/Data Type Duplicate' : Unused code path elimination
 * Block '<S9>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Propagation' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/AllControl')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/AllControl
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/AllControl/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/MATLAB Function'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/MATLAB Function1'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/MATLAB Function2'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic1'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic2'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic3'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic4'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic5'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic6'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/Saturation Dynamic7'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Steering angle > 2deg1'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/SteeringModel'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Yaw-Rate estimator '
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Anti-windup'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/D Gain'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Filter'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Filter ICs'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/I Gain'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Ideal P Gain'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Integrator'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Integrator ICs'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/N Copy'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/N Gain'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/P Copy'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Parallel P Gain'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Reset Signal'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Saturation'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Saturation Fdbk'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Sum'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Sum Fdbk'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tracking Mode'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tracking Mode Sum'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tsamp - Integral'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tsamp - Ngain'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/postSat Signal'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/preSat Signal'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/D Gain/Disabled'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Filter/Disabled'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Filter ICs/Disabled'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/I Gain/External Parameters'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Integrator/Discrete'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/N Gain/Disabled'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/P Copy/Disabled'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Reset Signal/Disabled'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Saturation/Enabled'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Sum/Sum_PI'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S64>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S65>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S66>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S67>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S68>'  : 'Fenice_VehicleModel/Vehicle Controller/AllControl/PI Control/Yaw-Rate estimator /Yaw-Rate'
 */
#endif                                 /* RTW_HEADER_AllControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
