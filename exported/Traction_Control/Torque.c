/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.38
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Dec  1 18:14:08 2023
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
#include <string.h>

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
  real_T rtb_Delta_T_o;
  real_T rtb_IProdOut;
  real_T rtb_IProdOut_tmp;
  real_T rtb_IProdOut_tmp_0;
  real_T rtb_IProdOut_tmp_1;
  real_T rtb_Saturation;
  real_T rtb_Tm_req;
  real_T rtb_Tm_rr;
  int8_T tmp;
  int8_T tmp_0;

  /* MATLAB Function: '<S3>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtSteeringangle_Torque, 10.0);
  rtb_Delta_T_o = pow(rtSteeringangle_Torque, 9.0);
  rtb_Saturation = pow(rtSteeringangle_Torque, 8.0);
  rtb_Tm_rr = pow(rtSteeringangle_Torque, 7.0);
  rtb_Tm_req = pow(rtSteeringangle_Torque, 6.0);
  coeff = pow(rtSteeringangle_Torque, 5.0);
  rtb_IProdOut_tmp = pow(rtSteeringangle_Torque, 4.0);
  rtb_IProdOut_tmp_0 = pow(rtSteeringangle_Torque, 3.0);
  rtb_IProdOut_tmp_1 = rtSteeringangle_Torque * rtSteeringangle_Torque;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S10>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_Kus'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S10>/Yaw-Rate'
   *  MATLAB Function: '<S3>/SteeringModel'
   */
  rtb_IProdOut = (((((((((((-3.534335194E-8 * rtb_IProdOut + 1.618153531E-7 *
    rtb_Delta_T_o) - 3.16758626E-7 * rtb_Saturation) + 1.704839325E-6 *
    rtb_Tm_rr) - 8.483242635E-6 * rtb_Tm_req) + 5.3472838E-5 * coeff) -
                       0.0002074730388 * rtb_IProdOut_tmp) + 0.001981845031 *
                      rtb_IProdOut_tmp_0) - rtb_IProdOut_tmp_1 * 0.006788067431)
                    + 0.217964925 * rtSteeringangle_Torque) + 2.836E-7) +
                  ((((((((((3.534215197E-8 * rtb_IProdOut + 1.618025757E-7 *
    rtb_Delta_T_o) + 3.167586246E-7 * rtb_Saturation) + 1.704975313E-6 *
    rtb_Tm_rr) + 8.483283483E-6 * rtb_Tm_req) + 5.347236085E-5 * coeff) +
                       0.0002074729834 * rtb_IProdOut_tmp) + 0.001981845682 *
                      rtb_IProdOut_tmp_0) + rtb_IProdOut_tmp_1 * 0.006788067316)
                    + 0.2179649246 * rtSteeringangle_Torque) - 2.845E-7)) / 2.0 *
    rtu_bar_Torque / (rtu_bar_Torque * rtu_bar_Torque * rtTel_Inp_Kus_Torque +
                      1.53) - rtyaw_rate_Torque;

  /* Product: '<S49>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_Kp'
   */
  rtb_Saturation = rtb_IProdOut * rtTel_Inp_Kp_Torque;

  /* Sum: '<S54>/Sum Fdbk' */
  rtb_Delta_T_o = rtb_Saturation + rtDW_Torque->Integrator_DSTATE;

  /* DeadZone: '<S37>/DeadZone' */
  if (rtb_Delta_T_o > 300.0) {
    rtb_Delta_T_o -= 300.0;
  } else if (rtb_Delta_T_o >= -300.0) {
    rtb_Delta_T_o = 0.0;
  } else {
    rtb_Delta_T_o -= -300.0;
  }

  /* End of DeadZone: '<S37>/DeadZone' */

  /* Product: '<S41>/IProd Out' incorporates:
   *  Constant: '<S8>/Constant'
   *  Inport: '<Root>/Tel_Inp_Ki'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S3>/Product3'
   *  RelationalOperator: '<S8>/Compare'
   */
  rtb_IProdOut *= rtDriver_req_Torque >= 0.01 ? rtTel_Inp_Ki_Torque : 0.0;

  /* Switch: '<S35>/Switch1' incorporates:
   *  Constant: '<S35>/Clamping_zero'
   *  Constant: '<S35>/Constant'
   *  Constant: '<S35>/Constant2'
   *  RelationalOperator: '<S35>/fix for DT propagation issue'
   */
  if (rtb_Delta_T_o > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S35>/Switch2' incorporates:
   *  Constant: '<S35>/Clamping_zero'
   *  Constant: '<S35>/Constant3'
   *  Constant: '<S35>/Constant4'
   *  RelationalOperator: '<S35>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S35>/Switch' incorporates:
   *  Constant: '<S35>/Clamping_zero'
   *  Constant: '<S35>/Constant1'
   *  Logic: '<S35>/AND3'
   *  RelationalOperator: '<S35>/Equal1'
   *  RelationalOperator: '<S35>/Relational Operator'
   *  Switch: '<S35>/Switch1'
   *  Switch: '<S35>/Switch2'
   */
  if ((rtb_Delta_T_o != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S35>/Switch' */

  /* DiscreteIntegrator: '<S44>/Integrator' */
  rtb_Delta_T_o = 0.00025 * rtb_IProdOut + rtDW_Torque->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S44>/Integrator' */
  if (rtb_Delta_T_o >= 20.0) {
    /* DiscreteIntegrator: '<S44>/Integrator' */
    rtb_Delta_T_o = 20.0;
  } else if (rtb_Delta_T_o <= -20.0) {
    /* DiscreteIntegrator: '<S44>/Integrator' */
    rtb_Delta_T_o = -20.0;
  }

  /* Sum: '<S53>/Sum' */
  rtb_Saturation += rtb_Delta_T_o;

  /* Saturate: '<S51>/Saturation' */
  if (rtb_Saturation > 300.0) {
    rtb_Saturation = 300.0;
  } else if (rtb_Saturation < -300.0) {
    rtb_Saturation = -300.0;
  }

  /* Product: '<S3>/Product1' incorporates:
   *  Gain: '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Inport: '<Root>/map_TV'
   *  Saturate: '<S51>/Saturation'
   */
  rtb_Saturation = 0.080176150557382225 * rtb_Saturation * rtmap_tv_Torque;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req = (rtTm_rl_Torque + rtTm_rr_Torque) * rtDriver_req_Torque * 0.5;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  coeff = fmin(fmax(rtDriver_req_Torque * 10.0, 0.0), 1.0);
  rtb_Tm_rr = (rtb_Saturation * 0.5 + rtb_Tm_req) * coeff;
  rtb_Tm_req = (rtb_Tm_req - rtb_Saturation * 0.5) * coeff;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Tm_rr > rtTm_rl_Torque) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_Torque = rtTm_rl_Torque;
  } else if (rtb_Tm_rr < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_Torque = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S5>/Switch'
     */
    rtTm_rr_m_Torque = rtb_Tm_rr;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Tm_req > rtTm_rr_Torque) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_Torque = rtTm_rr_Torque;
  } else if (rtb_Tm_req < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_Torque = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rl_a_Torque = rtb_Tm_req;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Outport: '<Root>/Tel_Out_error' */
  rtTel_Out_error_Torque = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S44>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = 0.00025 * rtb_IProdOut + rtb_Delta_T_o;
  if (rtDW_Torque->Integrator_DSTATE >= 20.0) {
    rtDW_Torque->Integrator_DSTATE = 20.0;
  } else if (rtDW_Torque->Integrator_DSTATE <= -20.0) {
    rtDW_Torque->Integrator_DSTATE = -20.0;
  }

  /* End of Update for DiscreteIntegrator: '<S44>/Integrator' */
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

  /* InitializeConditions for DiscreteIntegrator: '<S44>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
