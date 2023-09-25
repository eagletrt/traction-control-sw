/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.h
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec 12 11:53:33 2022
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
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Probe[2];                     /* '<S12>/Probe' */
  real_T UnitDelay1_DSTATE;            /* '<S6>/Unit Delay1' */
  real_T UD_DSTATE;                    /* '<S7>/UD' */
  real_T UnitDelay_DSTATE;             /* '<S6>/Unit Delay' */
  real_T Integrator_DSTATE;            /* '<S18>/Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S18>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S18>/Integrator' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const boolean_T Compare;             /* '<S15>/Compare' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: TV.KusT.K_us
   * Referenced by: '<S11>/K_us_table'
   */
  real_T K_us_table_tableData[10];

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S11>/K_us_table'
   */
  real_T K_us_table_bp01Data[10];

  /* Expression: LookUpFuzzy
   * Referenced by: '<S6>/2-D Lookup Table'
   */
  real_T uDLookupTable_tableData[441];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S6>/2-D Lookup Table'
   */
  real_T pooled4[21];

  /* Pooled Parameter (Expression: [0 1])
   * Referenced by: '<S2>/1-D Lookup Table2'
   */
  real_T pooled5[2];

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S6>/2-D Lookup Table'
   */
  uint32_T uDLookupTable_maxIndex[2];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Torque_initialize(RT_MODEL *const rtM);
extern void Torque_step(RT_MODEL *const rtM);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req;            /* '<Root>/driver_request' */
extern real_T rtSteeringangle;         /* '<Root>/delta' */
extern real_T rtTm_rl;                 /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a;               /* '<Root>/Tm_rl' */
extern real_T rtTm_rr;                 /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m;               /* '<Root>/Tm_rr' */
extern real_T rtbrake;                 /* '<Root>/Brake' */
extern real_T rtmap_sc;                /* '<Root>/map_sc' */
extern real_T rtmap_tv;                /* '<Root>/map_tv' */
extern real_T rtomega_rl;              /* '<Root>/omega_rl' */
extern real_T rtomega_rr;              /* '<Root>/omega_rr' */
extern real_T rtu_bar;                 /* '<Root>/u_bar' */
extern real_T rtyaw_rate;              /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S6>/Scope1' : Unused code path elimination
 * Block '<S6>/deltarad' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S18>/Saturation' : Eliminated Saturate block
 * Block '<S8>/K' : Eliminated nontunable gain of 1
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
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation Dynamic'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation Dynamic1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Saturation block'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Discrete Derivative'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/MATLAB Function2'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/SteeringModel'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Yaw-Rate estimator'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Constant'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_u'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Fuzzy Control/Yaw-Rate Controller/Yaw-Rate estimator/Yaw-Rate'
 */
#endif                                 /* RTW_HEADER_Torque_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
