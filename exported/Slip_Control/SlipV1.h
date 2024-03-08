/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SlipV1.h
 *
 * Code generated for Simulink model 'SlipV1'.
 *
 * Model version                  : 6.31
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  8 13:25:54 2024
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
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S18>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_g;/* '<S9>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S18>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_k;/* '<S9>/Discrete-Time Integrator1' */
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
  real_T Constant3_Value;              /* Expression: -70
                                        * Referenced by: '<S2>/Constant3'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T Constant3_Value_h;            /* Expression: -70
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real_T Constant2_Value_l;            /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * Referenced by: '<S21>/Constant'
                                        */
  real_T DiscreteTimeIntegrator1_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                           * Referenced by: '<S18>/Discrete-Time Integrator1'
                           */
  real_T DiscreteTimeIntegrator1_IC;   /* Expression: 0
                                        * Referenced by: '<S18>/Discrete-Time Integrator1'
                                        */
  real_T DiscreteTimeIntegrator1_gainv_l;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_l
                           * Referenced by: '<S9>/Discrete-Time Integrator1'
                           */
  real_T DiscreteTimeIntegrator1_IC_o; /* Expression: 0
                                        * Referenced by: '<S9>/Discrete-Time Integrator1'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/Constant4'
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
extern real_T rtSteeringangle_SlipV1;  /* '<Root>/delta' */
extern real_T rtTel_Inp_IntegralResetValue_Sl;/* '<Root>/Tel_Inp_IntegralResetValue' */
extern real_T rtTel_Inp_SC_Ki_SlipV1;  /* '<Root>/Tel_Inp_SC_Ki' */
extern real_T rtTel_Inp_SC_Kp_SlipV1;  /* '<Root>/Tel_Inp_SC_Kp' */
extern real_T rtTel_Inp_SC_LambdaRef_SlipV1;/* '<Root>/Tel_Inp_SC_LambdaRef' */
extern real_T rtTel_Inp_UppSatLim_SlipV1;/* '<Root>/Tel_Inp_UppSatLim' */
extern real_T rtTel_Inp_minT_SlipV1;   /* '<Root>/Tel_Inp_minT' */
extern real_T rtTel_Out_Debug_Torque_SlipV1;/* '<Root>/Tel_Out_Debug_Torque' */
extern real_T rtTm_rl_SlipV1;          /* '<Root>/Tmax_rl' */
extern real_T rtTm_rl_a_SlipV1;        /* '<Root>/Tm_rl' */
extern real_T rtTm_rr_SlipV1;          /* '<Root>/Tmax_rr' */
extern real_T rtTm_rr_m_SlipV1;        /* '<Root>/Tm_rr' */
extern real_T rtTmax_rl_slip_SlipV1;   /* '<Root>/Tmax_rl_slip' */
extern real_T rtTmax_rr_slip_SlipV1;   /* '<Root>/Tmax_rr_slip' */
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
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Scope' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
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
 * '<S4>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Low Level PID'
 * '<S5>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Saturation Dynamic1'
 * '<S6>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Saturation Dynamic2'
 * '<S7>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Slip_est1'
 * '<S8>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/map'
 * '<S9>'   : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Low Level PID/Integral Part'
 * '<S10>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Low Level PID/Proportional Part'
 * '<S11>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Low Level PID/Saturation Dynamic1'
 * '<S12>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Left Wheel/Low Level PID/Integral Part/IsNegative'
 * '<S13>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Low Level PID'
 * '<S14>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Saturation Dynamic1'
 * '<S15>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Saturation Dynamic2'
 * '<S16>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Slip_est1'
 * '<S17>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/map'
 * '<S18>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Low Level PID/Integral Part'
 * '<S19>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Low Level PID/Proportional Part'
 * '<S20>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Low Level PID/Saturation Dynamic1'
 * '<S21>'  : 'Fenice_Vehicle_Model/Vehicle Controller/SlipV1/TCS Rear Right Wheel/Low Level PID/Integral Part/IsNegative'
 */
#endif                                 /* RTW_HEADER_SlipV1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
