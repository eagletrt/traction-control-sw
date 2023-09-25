/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.h
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec 12 11:45:34 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_All0_h_
#define RTW_HEADER_All0_h_
#ifndef All0_COMMON_INCLUDES_
#define All0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* All0_COMMON_INCLUDES_ */

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
  real_T UnitDelay1_DSTATE;            /* '<S7>/Unit Delay1' */
  real_T UD_DSTATE;                    /* '<S8>/UD' */
  real_T UnitDelay_DSTATE;             /* '<S7>/Unit Delay' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S27>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_e;/* '<S19>/Discrete-Time Integrator1' */
  uint32_T m_bpIndex;                  /* '<S14>/1-D Lookup Table1' */
  uint32_T m_bpIndex_h;                /* '<S13>/1-D Lookup Table1' */
  uint32_T m_bpIndex_e;                /* '<S14>/1-D Lookup Table' */
  uint32_T m_bpIndex_m;                /* '<S13>/1-D Lookup Table' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S27>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_p;/* '<S19>/Discrete-Time Integrator1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S13>/1-D Lookup Table2'
   *   '<S14>/1-D Lookup Table2'
   */
  real_T pooled2[2];

  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S13>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table'
   */
  real_T pooled3[14];

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S13>/1-D Lookup Table'
   *   '<S13>/1-D Lookup Table1'
   *   '<S14>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table1'
   */
  real_T pooled4[14];

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S11>/K_us_table'
   */
  real_T K_us_table_tableData[10];

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S11>/K_us_table'
   */
  real_T K_us_table_bp01Data[10];

  /* Expression: LookUpFuzzy
   * Referenced by: '<S7>/2-D Lookup Table'
   */
  real_T uDLookupTable_tableData[441];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S7>/2-D Lookup Table'
   */
  real_T pooled10[21];

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S13>/1-D Lookup Table1'
   *   '<S14>/1-D Lookup Table1'
   */
  real_T pooled13[14];

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S7>/2-D Lookup Table'
   */
  uint32_T uDLookupTable_maxIndex[2];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void All0_initialize(RT_MODEL *const rtM);
extern void All0_step(RT_MODEL *const rtM);

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
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S7>/deltarad' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Scope' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/All Control Active')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/All Control Active
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/All Control Active/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation Dynamic'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation Dynamic1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation block'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller/Discrete Derivative'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller/MATLAB Function2'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller/SteeringModel'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller/Yaw-Rate estimator'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Fuzzy Control/Yaw-Rate Controller/Yaw-Rate estimator/Yaw-Rate'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/Saturation Dynamic'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/Slip_est1'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control/Integral Part'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control/Proportional Part'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch/If Action Subsystem'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch/If Action Subsystem1'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/Saturation Dynamic'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/Slip_est1'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control/Integral Part'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control/Proportional Part'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic/If Action Subsystem'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic/If Action Subsystem1'
 */
#endif                                 /* RTW_HEADER_All0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
