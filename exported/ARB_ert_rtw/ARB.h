/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ARB.h
 *
 * Code generated for Simulink model 'ARB'.
 *
 * Model version                  : 6.144
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue May  9 18:09:06 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ARB_h_
#define RTW_HEADER_ARB_h_
#ifndef ARB_COMMON_INCLUDES_
#define ARB_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* ARB_COMMON_INCLUDES_ */

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
  real_T Integrator_DSTATE;            /* '<S37>/Integrator' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: stiff_matrix
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  real_T uDLookupTable_tableData[35];

  /* Expression: ARBvel
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  real_T uDLookupTable_bp01Data[5];

  /* Expression: ARBdelta
   * Referenced by: '<S2>/2-D Lookup Table'
   */
  real_T uDLookupTable_bp02Data[7];

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S2>/2-D Lookup Table'
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
extern void ARB_initialize(RT_MODEL *const rtM);
extern void ARB_step(RT_MODEL *const rtM);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtSteeringangle;         /* '<Root>/delta' */
extern real_T rtknife_angle;           /* '<Root>/knife_angle' */
extern real_T rtknife_angle1;          /* '<Root>/knife_angle1' */
extern real_T rtu_bar;                 /* '<Root>/vel' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/ARB')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/ARB
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/ARB/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/knifeangle2stiff'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/stiff2knifeangle'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Anti-windup'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/D Gain'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Filter'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Filter ICs'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/I Gain'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Ideal P Gain'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Ideal P Gain Fdbk'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Integrator'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Integrator ICs'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/N Copy'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/N Gain'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/P Copy'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Parallel P Gain'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Reset Signal'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Saturation'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Saturation Fdbk'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Sum'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Sum Fdbk'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tracking Mode'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tracking Mode Sum'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tsamp - Integral'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tsamp - Ngain'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/postSat Signal'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/preSat Signal'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Anti-windup/Passthrough'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/D Gain/Disabled'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Filter/Disabled'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Filter ICs/Disabled'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/I Gain/External Parameters'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Integrator/Discrete'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Integrator ICs/Internal IC'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/N Gain/Disabled'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/P Copy/Disabled'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Parallel P Gain/External Parameters'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Reset Signal/Disabled'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Saturation/Passthrough'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Sum/Sum_PI'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/postSat Signal/Forward_Path'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/ARB/ARB controller/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_ARB_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
