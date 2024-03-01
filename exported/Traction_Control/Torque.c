/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.25
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Mar  1 17:31:38 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Torque.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_Torque;            /* '<Root>/driver_request' */
real_T rtSteeringangle_Torque;         /* '<Root>/delta' */
real_T rtTel_Inp_Ki_Torque;            /* '<Root>/Tel_Inp_Ki' */
real_T rtTel_Inp_Kp_Torque;            /* '<Root>/Tel_Inp_Kp' */
real_T rtTel_Inp_Kus_Torque;           /* '<Root>/Tel_Inp_Kus' */
real_T rtTel_Out_error_Torque;         /* '<Root>/Tel_Out_error' */
real_T rtTm_rl_Torque;                 /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_Torque;               /* '<Root>/Tm_rl' */
real_T rtTm_rr_Torque;                 /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_Torque;               /* '<Root>/Tm_rr' */
real_T rtbrake_Torque;                 /* '<Root>/Brake' */
real_T rtmap_sc_Torque;                /* '<Root>/map_sc' */
real_T rtmap_tv_Torque;                /* '<Root>/map_TV' */
real_T rtomega_rl_Torque;              /* '<Root>/omega_rl' */
real_T rtomega_rr_Torque;              /* '<Root>/omega_rr' */
real_T rtu_bar_Torque;                 /* '<Root>/u_bar' */
real_T rtyaw_rate_Torque;              /* '<Root>/Omega' */

/* Model step function */
void Torque_step(RT_MODEL_Torque *const rtM_Torque)
{
  DW_Torque *rtDW_Torque = rtM_Torque->dwork;
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
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtSteeringangle_Torque, 10.0);
  rtb_Delta_T_g = pow(rtSteeringangle_Torque, 9.0);
  rtb_Saturation = pow(rtSteeringangle_Torque, 8.0);
  rtb_IProdOut_tmp = pow(rtSteeringangle_Torque, 7.0);
  rtb_Tm_req = pow(rtSteeringangle_Torque, 6.0);
  coeff = pow(rtSteeringangle_Torque, 5.0);
  rtb_IProdOut_tmp_0 = pow(rtSteeringangle_Torque, 4.0);
  rtb_IProdOut_tmp_1 = pow(rtSteeringangle_Torque, 3.0);
  rtb_IProdOut_tmp_2 = rtSteeringangle_Torque * rtSteeringangle_Torque;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_Kus'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S3>/SteeringModel'
   *  MATLAB Function: '<S7>/Yaw-Rate'
   */
  rtb_IProdOut = (((((((((((-3.534335194E-8 * rtb_IProdOut + 1.618153531E-7 *
    rtb_Delta_T_g) - 3.16758626E-7 * rtb_Saturation) + 1.704839325E-6 *
    rtb_IProdOut_tmp) - 8.483242635E-6 * rtb_Tm_req) + 5.3472838E-5 * coeff) -
                       0.0002074730388 * rtb_IProdOut_tmp_0) + 0.001981845031 *
                      rtb_IProdOut_tmp_1) - rtb_IProdOut_tmp_2 * 0.006788067431)
                    + 0.217964925 * rtSteeringangle_Torque) + 2.836E-7) +
                  ((((((((((3.534215197E-8 * rtb_IProdOut + 1.618025757E-7 *
    rtb_Delta_T_g) + 3.167586246E-7 * rtb_Saturation) + 1.704975313E-6 *
    rtb_IProdOut_tmp) + 8.483283483E-6 * rtb_Tm_req) + 5.347236085E-5 * coeff) +
                       0.0002074729834 * rtb_IProdOut_tmp_0) + 0.001981845682 *
                      rtb_IProdOut_tmp_1) + rtb_IProdOut_tmp_2 * 0.006788067316)
                    + 0.2179649246 * rtSteeringangle_Torque) - 2.845E-7)) / 2.0 *
    rtu_bar_Torque / (rtu_bar_Torque * rtu_bar_Torque * rtTel_Inp_Kus_Torque +
                      rtP_Torque.controlData.L) - rtyaw_rate_Torque;

  /* Product: '<S46>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_Kp'
   */
  rtb_Saturation = rtb_IProdOut * rtTel_Inp_Kp_Torque;

  /* Sum: '<S51>/Sum Fdbk' */
  rtb_Delta_T_g = rtb_Saturation + rtDW_Torque->Integrator_DSTATE;

  /* DeadZone: '<S34>/DeadZone' */
  if (rtb_Delta_T_g > rtP_Torque.DiscreteVaryingPID_UpperSaturat) {
    rtb_Delta_T_g -= rtP_Torque.DiscreteVaryingPID_UpperSaturat;
  } else if (rtb_Delta_T_g >= rtP_Torque.DiscreteVaryingPID_LowerSaturat) {
    rtb_Delta_T_g = 0.0;
  } else {
    rtb_Delta_T_g -= rtP_Torque.DiscreteVaryingPID_LowerSaturat;
  }

  /* End of DeadZone: '<S34>/DeadZone' */

  /* Product: '<S38>/IProd Out' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/Tel_Inp_Ki'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S3>/Product3'
   *  RelationalOperator: '<S5>/Compare'
   */
  rtb_IProdOut *= rtDriver_req_Torque >= rtP_Torque.Steeringangle2deg1_const ?
    rtTel_Inp_Ki_Torque : 0.0;

  /* Switch: '<S32>/Switch1' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S32>/Constant2'
   *  RelationalOperator: '<S32>/fix for DT propagation issue'
   */
  if (rtb_Delta_T_g > rtP_Torque.Clamping_zero_Value) {
    tmp = rtP_Torque.Constant_Value;
  } else {
    tmp = rtP_Torque.Constant2_Value;
  }

  /* Switch: '<S32>/Switch2' incorporates:
   *  Constant: '<S32>/Clamping_zero'
   *  Constant: '<S32>/Constant3'
   *  Constant: '<S32>/Constant4'
   *  RelationalOperator: '<S32>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > rtP_Torque.Clamping_zero_Value) {
    tmp_0 = rtP_Torque.Constant3_Value_c;
  } else {
    tmp_0 = rtP_Torque.Constant4_Value;
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
  if ((rtP_Torque.Clamping_zero_Value != rtb_Delta_T_g) && (tmp == tmp_0)) {
    rtb_IProdOut = rtP_Torque.Constant1_Value;
  }

  /* End of Switch: '<S32>/Switch' */

  /* DiscreteIntegrator: '<S41>/Integrator' */
  rtb_IProdOut *= rtP_Torque.Integrator_gainval;

  /* DiscreteIntegrator: '<S41>/Integrator' */
  rtb_Delta_T_g = rtb_IProdOut + rtDW_Torque->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S41>/Integrator' */
  if (rtb_Delta_T_g > rtP_Torque.DiscreteVaryingPID_UpperIntegra) {
    /* DiscreteIntegrator: '<S41>/Integrator' */
    rtb_Delta_T_g = rtP_Torque.DiscreteVaryingPID_UpperIntegra;
  } else if (rtb_Delta_T_g < rtP_Torque.DiscreteVaryingPID_LowerIntegra) {
    /* DiscreteIntegrator: '<S41>/Integrator' */
    rtb_Delta_T_g = rtP_Torque.DiscreteVaryingPID_LowerIntegra;
  }

  /* Sum: '<S50>/Sum' */
  rtb_Saturation += rtb_Delta_T_g;

  /* Saturate: '<S48>/Saturation' */
  if (rtb_Saturation > rtP_Torque.DiscreteVaryingPID_UpperSaturat) {
    rtb_Saturation = rtP_Torque.DiscreteVaryingPID_UpperSaturat;
  } else if (rtb_Saturation < rtP_Torque.DiscreteVaryingPID_LowerSaturat) {
    rtb_Saturation = rtP_Torque.DiscreteVaryingPID_LowerSaturat;
  }

  /* Product: '<S3>/Product1' incorporates:
   *  Gain: '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Inport: '<Root>/map_TV'
   *  Saturate: '<S48>/Saturation'
   */
  rtb_Saturation = 2.0 * rtP_Torque.controlData.Rr / (rtP_Torque.controlData.Wr *
    rtP_Torque.controlData.tau_red * rtP_Torque.controlData.eff_red) *
    rtb_Saturation * rtmap_tv_Torque;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req = (rtTm_rl_Torque + rtTm_rr_Torque) * rtDriver_req_Torque *
    rtP_Torque.Constant3_Value;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  coeff = fmin(fmax(rtDriver_req_Torque * 10.0, 0.0), 1.0);
  rtb_IProdOut_tmp = (rtb_Saturation * 0.5 + rtb_Tm_req) * coeff;
  rtb_Tm_req = (rtb_Tm_req - rtb_Saturation * 0.5) * coeff;
  coeff = fmax(fmax(rtb_IProdOut_tmp - rtTm_rl_Torque, 0.0), fmax(rtb_Tm_req -
    rtTm_rr_Torque, 0.0));

  /* Outport: '<Root>/Tm_rr' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtTm_rr_m_Torque = rtb_IProdOut_tmp - coeff;

  /* Outport: '<Root>/Tm_rl' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtTm_rl_a_Torque = rtb_Tm_req - coeff;

  /* Outport: '<Root>/Tel_Out_error' */
  rtTel_Out_error_Torque = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S41>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = rtb_IProdOut + rtb_Delta_T_g;
  if (rtDW_Torque->Integrator_DSTATE >
      rtP_Torque.DiscreteVaryingPID_UpperIntegra) {
    rtDW_Torque->Integrator_DSTATE = rtP_Torque.DiscreteVaryingPID_UpperIntegra;
  } else if (rtDW_Torque->Integrator_DSTATE <
             rtP_Torque.DiscreteVaryingPID_LowerIntegra) {
    rtDW_Torque->Integrator_DSTATE = rtP_Torque.DiscreteVaryingPID_LowerIntegra;
  }
}

/* Model initialize function */
void Torque_initialize(RT_MODEL_Torque *const rtM_Torque)
{
  DW_Torque *rtDW_Torque = rtM_Torque->dwork;

  /* Registration code */

  /* Storage classes */
  rtDriver_req_Torque = 0.0;
  rtu_bar_Torque = 0.0;
  rtomega_rr_Torque = 0.0;
  rtomega_rl_Torque = 0.0;
  rtyaw_rate_Torque = 0.0;
  rtSteeringangle_Torque = 0.0;
  rtbrake_Torque = 0.0;
  rtTm_rl_Torque = 0.0;
  rtTm_rr_Torque = 0.0;
  rtmap_tv_Torque = 0.0;
  rtmap_sc_Torque = 0.0;
  rtTel_Inp_Kus_Torque = 0.0;
  rtTel_Inp_Kp_Torque = 0.0;
  rtTel_Inp_Ki_Torque = 0.0;

  /* Storage classes */
  rtTm_rr_m_Torque = 0.0;
  rtTm_rl_a_Torque = 0.0;
  rtTel_Out_error_Torque = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_Torque, 0,
                sizeof(DW_Torque));

  /* InitializeConditions for DiscreteIntegrator: '<S41>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = rtP_Torque.DiscreteVaryingPID_InitialCondi;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
