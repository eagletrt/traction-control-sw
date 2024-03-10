/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.h
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.35
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun Mar 10 15:13:56 2024
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

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S19>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_g;/* '<S10>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S19>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_k;/* '<S10>/Discrete-Time Integrator1' */
} DW_SLIP;

/* Real-time Model Data Structure */
struct tag_RTM_SLIP {
  const char_T * volatile errorStatus;
  DW_SLIP *dwork;
};

/* Model entry point functions */
extern void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M);
extern void SLIP_step(RT_MODEL_SLIP *const SLIP_M);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T SLIP_Driver_req;         /* '<Root>/Inp_driver_request' */
extern real_T SLIP_Inp_IntegralResetValue;/* '<Root>/Inp_IntegralResetValue' */
extern real_T SLIP_Inp_Ki;             /* '<Root>/Inp_Ki' */
extern real_T SLIP_Inp_Kp;             /* '<Root>/Inp_Kp' */
extern real_T SLIP_Inp_LambdaRef;      /* '<Root>/Inp_LambdaRef' */
extern real_T SLIP_Inp_UppSatLim;      /* '<Root>/Inp_UppSatLim' */
extern real_T SLIP_Inp_minT;           /* '<Root>/Inp_minT' */
extern real_T SLIP_Out_Debug_slip;     /* '<Root>/Out_Debug_slip' */
extern real_T SLIP_Out_Tm_rl;          /* '<Root>/Out_Tm_rl' */
extern real_T SLIP_Out_Tm_rr;          /* '<Root>/Out_Tm_rr' */
extern real_T SLIP_Out_Tmax_rl_slip;   /* '<Root>/Out_Tmax_rl_slip' */
extern real_T SLIP_Out_Tmax_rr_slip;   /* '<Root>/Out_Tmax_rr_slip' */
extern real_T SLIP_Tm_rl;              /* '<Root>/Inp_Tmax_rl' */
extern real_T SLIP_Tm_rr;              /* '<Root>/Inp_Tmax_rr' */
extern real_T SLIP_map_sc;             /* '<Root>/Inp_map_sc' */
extern real_T SLIP_omega_rl;           /* '<Root>/Inp_omega_rl' */
extern real_T SLIP_omega_rr;           /* '<Root>/Inp_omega_rr' */
extern real_T SLIP_u_bar;              /* '<Root>/Inp_u_bar' */
extern real_T SLIP_yaw_rate;           /* '<Root>/Inp_Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S10>/Scope' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope2' : Unused code path elimination
 * Block '<S4>/Scope3' : Unused code path elimination
 * Block '<S4>/Scope4' : Unused code path elimination
 * Block '<S4>/Scope5' : Unused code path elimination
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
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/MATLAB Function'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Low Level PID'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Saturation Dynamic1'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Saturation Dynamic2'
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Slip_est1'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/map'
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Low Level PID/Integral Part'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Low Level PID/Proportional Part'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Low Level PID/Saturation Dynamic1'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Left Wheel/Low Level PID/Integral Part/IsNegative'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Low Level PID'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Saturation Dynamic1'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Saturation Dynamic2'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Slip_est1'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/map'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Low Level PID/Integral Part'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Low Level PID/Proportional Part'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Low Level PID/Saturation Dynamic1'
 * '<S22>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SLIP/TCS Rear Right Wheel/Low Level PID/Integral Part/IsNegative'
 */
#endif                                 /* RTW_HEADER_SLIP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
