/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Regen.h
 *
 * Code generated for Simulink model 'Regen'.
 *
 * Model version                  : 6.58
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Apr  6 13:56:23 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Regen_h_
#define RTW_HEADER_Regen_h_
#ifndef Regen_COMMON_INCLUDES_
#define Regen_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Regen_COMMON_INCLUDES_ */

#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Regen RT_MODEL_Regen;

/* Real-time Model Data Structure */
struct tag_RTM_Regen {
  const char_T * volatile errorStatus;
};

/* Model entry point functions */
extern void Regen_initialize(RT_MODEL_Regen *const Regen_M);
extern void Regen_step(RT_MODEL_Regen *const Regen_M);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T Regen_Driver_req;        /* '<Root>/Inp_driver_request' */
extern real_T Regen_Inp_map_sc;        /* '<Root>/Inp_map_sc' */
extern real_T Regen_Inp_omega_inv_rl;  /* '<Root>/Inp_omega_inv_rl' */
extern real_T Regen_Inp_omega_inv_rr;  /* '<Root>/Inp_omega_inv_rr' */
extern real_T Regen_Out_Tm_rl;         /* '<Root>/Out_Tm_rl' */
extern real_T Regen_Out_Tm_rr;         /* '<Root>/Out_Tm_rr' */
extern real_T Regen_Out_brake_balance; /* '<Root>/Out_brake_balance' */
extern real_T Regen_Tm_rl;             /* '<Root>/Inp_Tmax_rl' */
extern real_T Regen_Tm_rr;             /* '<Root>/Inp_Tmax_rr' */
extern real_T Regen_pressure_f;        /* '<Root>/Inp_pressure_f' */
extern real_T Regen_pressure_r;        /* '<Root>/Inp_pressure_r' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 * Block '<S1>/Scope5' : Unused code path elimination
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
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/Regen')    - opens subsystem Fenice_Vehicle_Model/Vehicle Controller/Regen
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/Regen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_Vehicle_Model/Vehicle Controller'
 * '<S1>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen'
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/MATLAB Function'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/MATLAB Function1'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/MATLAB Function2'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/MATLAB Function3'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/MATLAB Function4'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/Regen/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_Regen_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
