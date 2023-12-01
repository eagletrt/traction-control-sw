/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV2.h
 *
 * Code generated for Simulink model 'SlipV2'.
 *
 * Model version                  : 6.38
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Dec  1 17:12:13 2023
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

#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_SlipV2 RT_MODEL_SlipV2;

/* Real-time Model Data Structure */
struct tag_RTM_SlipV2 {
  const char_T * volatile errorStatus;
};

/* Model entry point functions */
extern void SlipV2_initialize(RT_MODEL_SlipV2 *const rtM_SlipV2);
extern void SlipV2_step(RT_MODEL_SlipV2 *const rtM_SlipV2);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_SlipV2;     /* '<Root>/driver_request' */
extern real_T rtERROR_SlipV2;          /* '<Root>/ERROR' */
extern real_T rtSteeringangle_SlipV2;  /* '<Root>/delta' */
extern real_T rtTel_Inp_SC_PeakTorque_SlipV2;/* '<Root>/Tel_Inp_SC_PeakTorque' */
extern real_T rtTel_Inp_SC_SpeedCutoff_SlipV2;/* '<Root>/Tel_Inp_SC_SpeedCutoff' */
extern real_T rtTel_Inp_SC_StartTorque_SlipV2;/* '<Root>/Tel_Inp_SC_StartTorque' */
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
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/SlipV2')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/SlipV2
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/SlipV2/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/MATLAB Function1'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/MATLAB Function2'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/Saturation Dynamic1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/Saturation Dynamic2'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/Saturation Dynamic3'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/SlipV2/Saturation Dynamic4'
 */
#endif                                 /* RTW_HEADER_SlipV2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
