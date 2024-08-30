/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TV.c
 *
 * Code generated for Simulink model 'TV'.
 *
 * Model version                  : 6.289
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Aug 30 10:31:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "TV.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported data definition */

/* Data with Exported storage */
real_T TV_Driver_req;                  /* '<Root>/throttle' */
real_T TV_Steeringangle;               /* '<Root>/delta' */
real_T TV_in_KUS;                      /* '<Root>/in_KUS' */
real_T TV_in_Ki;                       /* '<Root>/in_Ki' */
real_T TV_in_Kp;                       /* '<Root>/in_Kp' */
real_T TV_in_T_max_rl;                 /* '<Root>/in_T_max_rl' */
real_T TV_in_T_max_rl_slip;            /* '<Root>/in_T_max_rl_slip' */
real_T TV_in_T_max_rr;                 /* '<Root>/in_T_max_rr' */
real_T TV_in_T_max_rr_slip;            /* '<Root>/in_T_max_rr_slip' */
real_T TV_out_T_motor_rl;              /* '<Root>/out_T_motor_rl' */
real_T TV_out_T_motor_rr;              /* '<Root>/out_T_motor_rr' */
real_T TV_out_debug_torque;            /* '<Root>/out_debug_torque' */
real_T TV_u;                           /* '<Root>/u_bar' */
real_T TV_yaw_rate;                    /* '<Root>/yaw_rate' */

/* Model step function */
void TV_step(RT_MODEL_TV *const TV_M)
{
  DW_TV *TV_DW = TV_M->dwork;
  real_T coeff;
  real_T rtb_Delta_T;
  real_T rtb_IProdOut;
  real_T rtb_Saturation;
  real_T rtb_T_motor_req;
  real_T rtb_Tm_rr;
  int8_T tmp;
  int8_T tmp_0;

  /* MATLAB Function: '<S3>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(TV_Steeringangle, 3.0);
  rtb_Delta_T = TV_Steeringangle * TV_Steeringangle * 0.0001216671;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/in_KUS'
   *  Inport: '<Root>/u_bar'
   *  Inport: '<Root>/yaw_rate'
   *  MATLAB Function: '<S3>/SteeringModel'
   *  MATLAB Function: '<S9>/Yaw-Rate'
   */
  rtb_IProdOut = (((0.2154468685 * TV_Steeringangle - rtb_Delta_T)
                   + 6.4879691888999994E-7 * rtb_IProdOut) + ((0.2154468682 *
    TV_Steeringangle + rtb_Delta_T) + 6.4879696257999991E-7 * rtb_IProdOut)) /
    2.0 * TV_u / (TV_u * TV_u * TV_in_KUS + 1.53) - TV_yaw_rate;

  /* Product: '<S48>/PProd Out' incorporates:
   *  Inport: '<Root>/in_Kp'
   */
  rtb_Saturation = rtb_IProdOut * TV_in_Kp;

  /* Sum: '<S53>/Sum Fdbk' */
  rtb_Delta_T = rtb_Saturation + TV_DW->Integrator_DSTATE;

  /* DeadZone: '<S36>/DeadZone' */
  if (rtb_Delta_T > 300.0) {
    rtb_Delta_T -= 300.0;
  } else if (rtb_Delta_T >= -300.0) {
    rtb_Delta_T = 0.0;
  } else {
    rtb_Delta_T -= -300.0;
  }

  /* End of DeadZone: '<S36>/DeadZone' */

  /* Product: '<S40>/IProd Out' incorporates:
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/in_Ki'
   *  Inport: '<Root>/throttle'
   *  Product: '<S3>/Product3'
   *  RelationalOperator: '<S7>/Compare'
   */
  rtb_IProdOut *= TV_Driver_req >= 0.01 ? TV_in_Ki : 0.0;

  /* Switch: '<S34>/Switch1' incorporates:
   *  Constant: '<S34>/Clamping_zero'
   *  Constant: '<S34>/Constant'
   *  Constant: '<S34>/Constant2'
   *  RelationalOperator: '<S34>/fix for DT propagation issue'
   */
  if (rtb_Delta_T > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S34>/Switch2' incorporates:
   *  Constant: '<S34>/Clamping_zero'
   *  Constant: '<S34>/Constant3'
   *  Constant: '<S34>/Constant4'
   *  RelationalOperator: '<S34>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S34>/Switch' incorporates:
   *  Constant: '<S34>/Clamping_zero'
   *  Constant: '<S34>/Constant1'
   *  Logic: '<S34>/AND3'
   *  RelationalOperator: '<S34>/Equal1'
   *  RelationalOperator: '<S34>/Relational Operator'
   *  Switch: '<S34>/Switch1'
   *  Switch: '<S34>/Switch2'
   */
  if ((rtb_Delta_T != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S34>/Switch' */

  /* DiscreteIntegrator: '<S43>/Integrator' */
  rtb_Delta_T = 5.0E-5 * rtb_IProdOut + TV_DW->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S43>/Integrator' */
  if (rtb_Delta_T > 20.0) {
    /* DiscreteIntegrator: '<S43>/Integrator' */
    rtb_Delta_T = 20.0;
  } else if (rtb_Delta_T < -20.0) {
    /* DiscreteIntegrator: '<S43>/Integrator' */
    rtb_Delta_T = -20.0;
  }

  /* Sum: '<S52>/Sum' */
  rtb_Saturation += rtb_Delta_T;

  /* Saturate: '<S50>/Saturation' */
  if (rtb_Saturation > 300.0) {
    rtb_Saturation = 300.0;
  } else if (rtb_Saturation < -300.0) {
    rtb_Saturation = -300.0;
  }

  /* Gain: '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)' incorporates:
   *  Saturate: '<S50>/Saturation'
   */
  rtb_Saturation *= 0.0902870345685595;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/in_T_max_rl'
   *  Inport: '<Root>/in_T_max_rr'
   *  Inport: '<Root>/throttle'
   *  Sum: '<S1>/Add'
   */
  rtb_T_motor_req = (TV_in_T_max_rl + TV_in_T_max_rr) * 0.5 * TV_Driver_req;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/in_T_max_rl_slip'
   *  Inport: '<Root>/in_T_max_rr_slip'
   *  Inport: '<Root>/throttle'
   */
  coeff = fmin(fmax(TV_Driver_req * 10.0, 0.0), 1.0);
  rtb_Tm_rr = (rtb_Saturation * 0.5 + rtb_T_motor_req) * coeff;
  rtb_T_motor_req = (rtb_T_motor_req - rtb_Saturation * 0.5) * coeff;
  coeff = fmax(fmax(rtb_Tm_rr - TV_in_T_max_rr_slip, 0.0), fmax(rtb_T_motor_req
    - TV_in_T_max_rl_slip, 0.0));
  rtb_Tm_rr -= coeff;
  rtb_T_motor_req -= coeff;

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Tm_rr > 100.0) {
    /* Outport: '<Root>/out_T_motor_rr' */
    TV_out_T_motor_rr = 100.0;
  } else if (rtb_Tm_rr < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant5'
     *  Outport: '<Root>/out_T_motor_rr'
     */
    TV_out_T_motor_rr = 0.0;
  } else {
    /* Outport: '<Root>/out_T_motor_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    TV_out_T_motor_rr = rtb_Tm_rr;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_T_motor_req > 100.0) {
    /* Outport: '<Root>/out_T_motor_rl' */
    TV_out_T_motor_rl = 100.0;
  } else if (rtb_T_motor_req < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S1>/Constant5'
     *  Outport: '<Root>/out_T_motor_rl'
     */
    TV_out_T_motor_rl = 0.0;
  } else {
    /* Outport: '<Root>/out_T_motor_rl' incorporates:
     *  Switch: '<S5>/Switch'
     */
    TV_out_T_motor_rl = rtb_T_motor_req;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Outport: '<Root>/out_debug_torque' */
  TV_out_debug_torque = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S43>/Integrator' */
  TV_DW->Integrator_DSTATE = 5.0E-5 * rtb_IProdOut + rtb_Delta_T;
  if (TV_DW->Integrator_DSTATE > 20.0) {
    TV_DW->Integrator_DSTATE = 20.0;
  } else if (TV_DW->Integrator_DSTATE < -20.0) {
    TV_DW->Integrator_DSTATE = -20.0;
  }

  /* End of Update for DiscreteIntegrator: '<S43>/Integrator' */
}

/* Model initialize function */
void TV_initialize(RT_MODEL_TV *const TV_M)
{
  DW_TV *TV_DW = TV_M->dwork;

  /* Registration code */

  /* Storage classes */
  TV_out_T_motor_rr = 0.0;
  TV_out_T_motor_rl = 0.0;
  TV_out_debug_torque = 0.0;

  /* Storage classes */
  TV_Driver_req = 0.0;
  TV_u = 0.0;
  TV_yaw_rate = 0.0;
  TV_Steeringangle = 0.0;
  TV_in_T_max_rl = 0.0;
  TV_in_T_max_rr = 0.0;
  TV_in_KUS = 0.0;
  TV_in_Kp = 0.0;
  TV_in_Ki = 0.0;
  TV_in_T_max_rr_slip = 0.0;
  TV_in_T_max_rl_slip = 0.0;

  /* states (dwork) */
  (void) memset((void *)TV_DW, 0,
                sizeof(DW_TV));

  /* InitializeConditions for DiscreteIntegrator: '<S43>/Integrator' */
  TV_DW->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
