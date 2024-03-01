/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1.h
 *
 * Code generated for Simulink model 'SlipV1'.
 *
 * Model version                  : 6.25
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  1 17:13:29 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SlipV1_h_
#define RTW_HEADER_SlipV1_h_
#ifndef SlipV1_COMMON_INCLUDES_
#define SlipV1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* SlipV1_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_SlipV1 RT_MODEL_SlipV1;

#ifndef DEFINED_TYPEDEF_FOR_struct_XXZzH7IZw0BprRxUKGpB6E_
#define DEFINED_TYPEDEF_FOR_struct_XXZzH7IZw0BprRxUKGpB6E_

typedef struct {
  real_T L;
  real_T Vlow;
  real_T Wr;
  real_T tau_red;
  real_T eff_red;
  real_T Rf;
  real_T Rr;
  real_T maxTorque;
  real_T ms;
  real_T izz;
  real_T ixz;
  real_T static_toe_f;
  real_T static_toe_r;
  real_T static_camber_f;
  real_T static_camber_r;
} struct_XXZzH7IZw0BprRxUKGpB6E;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S97>/Integrator' */
  real_T Integrator_DSTATE_o;          /* '<S42>/Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S97>/Integrator' */
  int8_T Integrator_PrevResetState_p;  /* '<S42>/Integrator' */
} DW_SlipV1;

/* Parameters (default storage) */
struct P_SlipV1_ {
  struct_XXZzH7IZw0BprRxUKGpB6E controlData;/* Variable: controlData
                                             * Referenced by:
                                             *   '<S2>/Constant'
                                             *   '<S2>/Rr'
                                             *   '<S2>/Wr//2'
                                             *   '<S3>/Constant'
                                             *   '<S3>/Rr'
                                             *   '<S3>/Wr//2'
                                             */
  real_T DiscreteVaryingPID_InitialCondi;
                              /* Mask Parameter: DiscreteVaryingPID_InitialCondi
                               * Referenced by: '<S97>/Integrator'
                               */
  real_T DiscreteVaryingPID_InitialCon_o;
                              /* Mask Parameter: DiscreteVaryingPID_InitialCon_o
                               * Referenced by: '<S42>/Integrator'
                               */
  real_T DiscreteVaryingPID_LowerIntegra;
                              /* Mask Parameter: DiscreteVaryingPID_LowerIntegra
                               * Referenced by: '<S97>/Integrator'
                               */
  real_T DiscreteVaryingPID_LowerInteg_d;
                              /* Mask Parameter: DiscreteVaryingPID_LowerInteg_d
                               * Referenced by: '<S42>/Integrator'
                               */
  real_T DiscreteVaryingPID_LowerSaturat;
                              /* Mask Parameter: DiscreteVaryingPID_LowerSaturat
                               * Referenced by:
                               *   '<S104>/Saturation'
                               *   '<S90>/DeadZone'
                               */
  real_T DiscreteVaryingPID_LowerSatur_b;
                              /* Mask Parameter: DiscreteVaryingPID_LowerSatur_b
                               * Referenced by:
                               *   '<S49>/Saturation'
                               *   '<S35>/DeadZone'
                               */
  real_T DiscreteVaryingPID_UpperIntegra;
                              /* Mask Parameter: DiscreteVaryingPID_UpperIntegra
                               * Referenced by: '<S97>/Integrator'
                               */
  real_T DiscreteVaryingPID_UpperInteg_m;
                              /* Mask Parameter: DiscreteVaryingPID_UpperInteg_m
                               * Referenced by: '<S42>/Integrator'
                               */
  real_T DiscreteVaryingPID_UpperSaturat;
                              /* Mask Parameter: DiscreteVaryingPID_UpperSaturat
                               * Referenced by:
                               *   '<S104>/Saturation'
                               *   '<S90>/DeadZone'
                               */
  real_T DiscreteVaryingPID_UpperSatur_f;
                              /* Mask Parameter: DiscreteVaryingPID_UpperSatur_f
                               * Referenced by:
                               *   '<S49>/Saturation'
                               *   '<S35>/DeadZone'
                               */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T Constant2_Value_l;            /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S33>/Constant1'
                                        */
  real_T Constant1_Value_d;            /* Expression: 0
                                        * Referenced by: '<S88>/Constant1'
                                        */
  real_T Clamping_zero_Value;          /* Expression: 0
                                        * Referenced by: '<S88>/Clamping_zero'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S97>/Integrator'
                                        */
  real_T Clamping_zero_Value_c;        /* Expression: 0
                                        * Referenced by: '<S33>/Clamping_zero'
                                        */
  real_T Integrator_gainval_i;       /* Computed Parameter: Integrator_gainval_i
                                      * Referenced by: '<S42>/Integrator'
                                      */
  int8_T Constant_Value;               /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S33>/Constant'
                                        */
  int8_T Constant2_Value_a;            /* Computed Parameter: Constant2_Value_a
                                        * Referenced by: '<S33>/Constant2'
                                        */
  int8_T Constant3_Value;              /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S33>/Constant3'
                                        */
  int8_T Constant4_Value;              /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S33>/Constant4'
                                        */
  int8_T Constant_Value_n;             /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S88>/Constant'
                                        */
  int8_T Constant2_Value_i;            /* Computed Parameter: Constant2_Value_i
                                        * Referenced by: '<S88>/Constant2'
                                        */
  int8_T Constant3_Value_l;            /* Computed Parameter: Constant3_Value_l
                                        * Referenced by: '<S88>/Constant3'
                                        */
  int8_T Constant4_Value_f;            /* Computed Parameter: Constant4_Value_f
                                        * Referenced by: '<S88>/Constant4'
                                        */
};

/* Parameters (default storage) */
typedef struct P_SlipV1_ P_SlipV1;

/* Real-time Model Data Structure */
struct tag_RTM_SlipV1 {
  const char_T * volatile errorStatus;
  DW_SlipV1 *dwork;
};

/* Block parameters (default storage) */
extern P_SlipV1 rtP_SlipV1;

/* Model entry point functions */
extern void SlipV1_initialize(RT_MODEL_SlipV1 *const rtM_SlipV1);
extern void SlipV1_step(RT_MODEL_SlipV1 *const rtM_SlipV1);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T rtDriver_req_SlipV1;     /* '<Root>/driver_request' */
extern real_T rtERROR_SlipV1;          /* '<Root>/ERROR' */
extern real_T rtSteeringangle_SlipV1;  /* '<Root>/delta' */
extern real_T rtTel_Inp_SC_Ki_SlipV1;  /* '<Root>/Tel_Inp_SC_Ki' */
extern real_T rtTel_Inp_SC_Kp_SlipV1;  /* '<Root>/Tel_Inp_SC_Kp' */
extern real_T rtTel_Inp_SC_LambdaRef_SlipV1;/* '<Root>/Tel_Inp_SC_LambdaRef' */
extern real_T rtTel_Inp_T0_SlipV1;     /* '<Root>/Tel_Inp_T0' */
extern real_T rtTel_Inp_Vramp_SlipV1;  /* '<Root>/Tel_Inp_Vramp' */
extern real_T rtTel_Inp_minT_SlipV1;   /* '<Root>/Tel_Inp_minT' */
extern real_T rtTm_rl_SlipV1;          /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_SlipV1;        /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_SlipV1;          /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_SlipV1;        /* '<Root>/Tm_rr' */
extern real_T rtbrake_SlipV1;          /* '<Root>/Brake' */
extern real_T rtmap_sc_SlipV1;         /* '<Root>/map_sc' */
extern real_T rtmap_tv_SlipV1;         /* '<Root>/map_tv' */
extern real_T rtomega_rl_SlipV1;       /* '<Root>/omega_rl' */
extern real_T rtomega_rr_SlipV1;       /* '<Root>/omega_rr' */
extern real_T rtu_bar_SlipV1;          /* '<Root>/u_bar' */
extern real_T rtyaw_rate_SlipV1;       /* '<Root>/Omega' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S61>/Data Type Duplicate' : Unused code path elimination
 * Block '<S61>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope2' : Unused code path elimination
 * Block '<S3>/Scope3' : Unused code path elimination
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
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/SlipV1')    - opens subsystem Fenice_Vehicle_Model/Vehicle Controller/SlipV1
 * hilite_system('Fenice_Vehicle_Model/Vehicle Controller/SlipV1/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_Vehicle_Model/Vehicle Controller'
 * '<S1>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1'
 * '<S2>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel'
 * '<S3>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel'
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Saturation Dynamic1'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Saturation Dynamic2'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Slip_est1'
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/map'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup'
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/D Gain'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Filter'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Filter ICs'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/I Gain'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Integrator'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Integrator ICs'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/N Copy'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/N Gain'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/P Copy'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Parallel P Gain'
 * '<S22>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Reset Signal'
 * '<S23>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Saturation'
 * '<S24>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Saturation Fdbk'
 * '<S25>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Sum'
 * '<S26>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Sum Fdbk'
 * '<S27>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode'
 * '<S28>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode Sum'
 * '<S29>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Integral'
 * '<S30>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Ngain'
 * '<S31>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/postSat Signal'
 * '<S32>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/preSat Signal'
 * '<S33>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S34>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S35>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S36>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/D Gain/Disabled'
 * '<S37>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Filter/Disabled'
 * '<S38>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Filter ICs/Disabled'
 * '<S39>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/I Gain/External Parameters'
 * '<S40>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S41>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S42>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Integrator/Discrete'
 * '<S43>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S44>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S45>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/N Gain/Disabled'
 * '<S46>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/P Copy/Disabled'
 * '<S47>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S48>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Reset Signal/External Reset'
 * '<S49>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Saturation/Enabled'
 * '<S50>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S51>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Sum/Sum_PI'
 * '<S52>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S53>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S54>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Integral/TsSignalSpecification'
 * '<S56>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S58>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S59>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID'
 * '<S60>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Saturation Dynamic1'
 * '<S61>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Saturation Dynamic2'
 * '<S62>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Slip_est1'
 * '<S63>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/map'
 * '<S64>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Anti-windup'
 * '<S65>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/D Gain'
 * '<S66>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Filter'
 * '<S67>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Filter ICs'
 * '<S68>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/I Gain'
 * '<S69>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Ideal P Gain'
 * '<S70>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S71>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Integrator'
 * '<S72>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Integrator ICs'
 * '<S73>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/N Copy'
 * '<S74>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/N Gain'
 * '<S75>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/P Copy'
 * '<S76>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Parallel P Gain'
 * '<S77>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Reset Signal'
 * '<S78>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Saturation'
 * '<S79>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Saturation Fdbk'
 * '<S80>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Sum'
 * '<S81>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Sum Fdbk'
 * '<S82>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tracking Mode'
 * '<S83>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tracking Mode Sum'
 * '<S84>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tsamp - Integral'
 * '<S85>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tsamp - Ngain'
 * '<S86>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/postSat Signal'
 * '<S87>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/preSat Signal'
 * '<S88>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S89>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S90>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S91>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/D Gain/Disabled'
 * '<S92>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Filter/Disabled'
 * '<S93>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Filter ICs/Disabled'
 * '<S94>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/I Gain/External Parameters'
 * '<S95>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S96>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S97>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Integrator/Discrete'
 * '<S98>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S99>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S100>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/N Gain/Disabled'
 * '<S101>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/P Copy/Disabled'
 * '<S102>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S103>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Reset Signal/External Reset'
 * '<S104>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Saturation/Enabled'
 * '<S105>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S106>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Sum/Sum_PI'
 * '<S107>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S108>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S109>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S110>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tsamp - Integral/TsSignalSpecification'
 * '<S111>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S112>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S113>' : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_SlipV1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
