/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TV.c
 *
 * Code generated for Simulink model 'TV'.
 *
 * Model version                  : 6.35
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun Mar 10 15:17:09 2024
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
real_T TV_Driver_req;                  /* '<Root>/Inp_driver_request' */
real_T TV_Inp_Ki;                      /* '<Root>/Inp_Ki' */
real_T TV_Inp_Kp;                      /* '<Root>/Inp_Kp' */
real_T TV_Inp_Kus;                     /* '<Root>/Inp_Kus' */
real_T TV_Out_Debug_Torque;            /* '<Root>/Out_Debug_Torque' */
real_T TV_Out_Tm_rl;                   /* '<Root>/Out_Tm_rl' */
real_T TV_Out_Tm_rr;                   /* '<Root>/Out_Tm_rr' */
real_T TV_Steeringangle;               /* '<Root>/Inp_delta' */
real_T TV_Tm_rl;                       /* '<Root>/Inp_Tmax_rl' */
real_T TV_Tm_rr;                       /* '<Root>/Inp_Tmax_rr' */
real_T TV_lambda_rr;                   /* '<Root>/Inp_Tmax_rr_Slip' */
real_T TV_lambda_rr_n;                 /* '<Root>/Inp_Tmax_rl_Slip' */
real_T TV_map_tv;                      /* '<Root>/Inp_map_TV' */
real_T TV_u_bar;                       /* '<Root>/Inp_u_bar' */
real_T TV_yaw_rate;                    /* '<Root>/Inp_Omega' */

/* Model step function */
void TV_step(RT_MODEL_TV *const TV_M)
{
  DW_TV *TV_DW = TV_M->dwork;
  real_T coeff;
  real_T rtb_Delta_T_g;
  real_T rtb_IProdOut;
  real_T rtb_IProdOut_tmp;
  real_T rtb_IProdOut_tmp_0;
  real_T rtb_IProdOut_tmp_1;
  real_T rtb_IProdOut_tmp_2;
  real_T rtb_Saturation;
  real_T rtb_Tm_req;
  int8_T tmp;
  int8_T tmp_0;

  /* MATLAB Function: '<S3>/SteeringModel' incorporates:
   *  Inport: '<Root>/Inp_delta'
   */
  rtb_IProdOut = pow(TV_Steeringangle, 10.0);
  rtb_Delta_T_g = pow(TV_Steeringangle, 9.0);
  rtb_Saturation = pow(TV_Steeringangle, 8.0);
  rtb_IProdOut_tmp = pow(TV_Steeringangle, 7.0);
  rtb_Tm_req = pow(TV_Steeringangle, 6.0);
  coeff = pow(TV_Steeringangle, 5.0);
  rtb_IProdOut_tmp_0 = pow(TV_Steeringangle, 4.0);
  rtb_IProdOut_tmp_1 = pow(TV_Steeringangle, 3.0);
  rtb_IProdOut_tmp_2 = TV_Steeringangle * TV_Steeringangle;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/Inp_Kus'
   *  Inport: '<Root>/Inp_Omega'
   *  Inport: '<Root>/Inp_delta'
   *  Inport: '<Root>/Inp_u_bar'
   *  MATLAB Function: '<S3>/SteeringModel'
   *  MATLAB Function: '<S7>/Yaw-Rate'
   */
  rtb_IProdOut = (((((((((((-3.534335194E-8 * rtb_IProdOut + 1.618153531E-7 *
    rtb_Delta_T_g) - 3.16758626E-7 * rtb_Saturation) + 1.704839325E-6 *
    rtb_IProdOut_tmp) - 8.483242635E-6 * rtb_Tm_req) + 5.3472838E-5 * coeff) -
                       0.0002074730388 * rtb_IProdOut_tmp_0) + 0.001981845031 *
                      rtb_IProdOut_tmp_1) - rtb_IProdOut_tmp_2 * 0.006788067431)
                    + 0.217964925 * TV_Steeringangle) + 2.836E-7) +
                  ((((((((((3.534215197E-8 * rtb_IProdOut + 1.618025757E-7 *
    rtb_Delta_T_g) + 3.167586246E-7 * rtb_Saturation) + 1.704975313E-6 *
    rtb_IProdOut_tmp) + 8.483283483E-6 * rtb_Tm_req) + 5.347236085E-5 * coeff) +
                       0.0002074729834 * rtb_IProdOut_tmp_0) + 0.001981845682 *
                      rtb_IProdOut_tmp_1) + rtb_IProdOut_tmp_2 * 0.006788067316)
                    + 0.2179649246 * TV_Steeringangle) - 2.845E-7)) / 2.0 *
    TV_u_bar / (TV_u_bar * TV_u_bar * TV_Inp_Kus + 1.53) - TV_yaw_rate;

  /* Product: '<S46>/PProd Out' incorporates:
   *  Inport: '<Root>/Inp_Kp'
   */
  rtb_Saturation = rtb_IProdOut * TV_Inp_Kp;

  /* Sum: '<S51>/Sum Fdbk' */
  rtb_Delta_T_g = rtb_Saturation + TV_DW->Integrator_DSTATE;

  /* DeadZone: '<S34>/DeadZone' */
  if (rtb_Delta_T_g > 300.0) {
    rtb_Delta_T_g -= 300.0;
  } else if (rtb_Delta_T_g >= -300.0) {
    rtb_Delta_T_g = 0.0;
  } else {
    rtb_Delta_T_g -= -300.0;
  }

  /* End of DeadZone: '<S34>/DeadZone' */

  /* Product: '<S38>/IProd Out' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/Inp_Ki'
   *  Inport: '<Root>/Inp_driver_request'
   *  Product: '<S3>/Product3'
   *  RelationalOperator: '<S5>/Compare'
   */
  rtb_IProdOut *= TV_Driver_req >= 0.01 ? TV_Inp_Ki : 0.0;

  /* Switch: '<S32>/Switch1' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S32>/Constant2'
   *  RelationalOperator: '<S32>/fix for DT propagation issue'
   */
  if (rtb_Delta_T_g > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S32>/Switch2' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant3'
   *  Constant: '<S32>/Constant4'
   *  RelationalOperator: '<S32>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S32>/Switch' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant1'
   *  Logic: '<S32>/AND3'
   *  RelationalOperator: '<S32>/Equal1'
   *  RelationalOperator: '<S32>/Relational Operator'
   *  Switch: '<S32>/Switch1'
   *  Switch: '<S32>/Switch2'
   */
  if ((rtb_Delta_T_g != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S32>/Switch' */

  /* DiscreteIntegrator: '<S41>/Integrator' */
  rtb_Delta_T_g = 0.00025 * rtb_IProdOut + TV_DW->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S41>/Integrator' */
  if (rtb_Delta_T_g > 20.0) {
    /* DiscreteIntegrator: '<S41>/Integrator' */
    rtb_Delta_T_g = 20.0;
  } else if (rtb_Delta_T_g < -20.0) {
    /* DiscreteIntegrator: '<S41>/Integrator' */
    rtb_Delta_T_g = -20.0;
  }

  /* Sum: '<S50>/Sum' */
  rtb_Saturation += rtb_Delta_T_g;

  /* Saturate: '<S48>/Saturation' */
  if (rtb_Saturation > 300.0) {
    rtb_Saturation = 300.0;
  } else if (rtb_Saturation < -300.0) {
    rtb_Saturation = -300.0;
  }

  /* Product: '<S3>/Product1' incorporates:
   *  Gain: '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Inport: '<Root>/Inp_map_TV'
   *  Saturate: '<S48>/Saturation'
   */
  rtb_Saturation = 0.080176150557382225 * rtb_Saturation * TV_map_tv;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Inp_Tmax_rl'
   *  Inport: '<Root>/Inp_Tmax_rr'
   *  Inport: '<Root>/Inp_driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req = (TV_Tm_rl + TV_Tm_rr) * TV_Driver_req * 0.5;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Inp_Tmax_rl_Slip'
   *  Inport: '<Root>/Inp_Tmax_rr_Slip'
   *  Inport: '<Root>/Inp_driver_request'
   */
  coeff = fmin(fmax(TV_Driver_req * 10.0, 0.0), 1.0);
  rtb_IProdOut_tmp = (rtb_Saturation * 0.5 + rtb_Tm_req) * coeff;
  rtb_Tm_req = (rtb_Tm_req - rtb_Saturation * 0.5) * coeff;
  coeff = fmax(fmax(rtb_IProdOut_tmp - TV_lambda_rr, 0.0), fmax(rtb_Tm_req -
    TV_lambda_rr_n, 0.0));

  /* Outport: '<Root>/Out_Tm_rr' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  TV_Out_Tm_rr = rtb_IProdOut_tmp - coeff;

  /* Outport: '<Root>/Out_Tm_rl' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  TV_Out_Tm_rl = rtb_Tm_req - coeff;

  /* Outport: '<Root>/Out_Debug_Torque' */
  TV_Out_Debug_Torque = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S41>/Integrator' */
  TV_DW->Integrator_DSTATE = 0.00025 * rtb_IProdOut + rtb_Delta_T_g;
  if (TV_DW->Integrator_DSTATE > 20.0) {
    TV_DW->Integrator_DSTATE = 20.0;
  } else if (TV_DW->Integrator_DSTATE < -20.0) {
    TV_DW->Integrator_DSTATE = -20.0;
  }

  /* End of Update for DiscreteIntegrator: '<S41>/Integrator' */
}

/* Model initialize function */
void TV_initialize(RT_MODEL_TV *const TV_M)
{
  DW_TV *TV_DW = TV_M->dwork;

  /* Registration code */

  /* Storage classes */
  TV_Driver_req = 0.0;
  TV_u_bar = 0.0;
  TV_yaw_rate = 0.0;
  TV_Steeringangle = 0.0;
  TV_Tm_rl = 0.0;
  TV_Tm_rr = 0.0;
  TV_map_tv = 0.0;
  TV_Inp_Kus = 0.0;
  TV_Inp_Kp = 0.0;
  TV_Inp_Ki = 0.0;
  TV_lambda_rr = 0.0;
  TV_lambda_rr_n = 0.0;

  /* Storage classes */
  TV_Out_Tm_rr = 0.0;
  TV_Out_Tm_rl = 0.0;
  TV_Out_Debug_Torque = 0.0;

  /* states (dwork) */
  (void) memset((void *)TV_DW, 0,
                sizeof(DW_TV));

  /* InitializeConditions for DiscreteIntegrator: '<S41>/Integrator' */
  TV_DW->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
