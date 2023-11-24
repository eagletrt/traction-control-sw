/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 6.28
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Nov 24 22:36:36 2023
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
  real_T Integrator;
  real_T rtb_IProdOut;
  real_T rtb_T_diff_k;
  real_T rtb_Tm_req_o;
  real_T rtb_Tm_rr;
  real_T rtb_error;
  real_T rtb_error_tmp;
  real_T rtb_error_tmp_0;
  real_T rtb_error_tmp_1;

  /* MATLAB Function: '<S3>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_error = pow(rtSteeringangle_Torque, 10.0);
  rtb_IProdOut = pow(rtSteeringangle_Torque, 9.0);
  Integrator = pow(rtSteeringangle_Torque, 8.0);
  rtb_T_diff_k = pow(rtSteeringangle_Torque, 7.0);
  rtb_Tm_req_o = pow(rtSteeringangle_Torque, 6.0);
  rtb_Tm_rr = pow(rtSteeringangle_Torque, 5.0);
  rtb_error_tmp = pow(rtSteeringangle_Torque, 4.0);
  rtb_error_tmp_0 = pow(rtSteeringangle_Torque, 3.0);
  rtb_error_tmp_1 = rtSteeringangle_Torque * rtSteeringangle_Torque;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S8>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_Kus'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S3>/SteeringModel'
   *  MATLAB Function: '<S8>/Yaw-Rate'
   */
  rtb_error = (((((((((((-3.534335194E-8 * rtb_error + 1.618153531E-7 *
    rtb_IProdOut) - 3.16758626E-7 * Integrator) + 1.704839325E-6 * rtb_T_diff_k)
                      - 8.483242635E-6 * rtb_Tm_req_o) + 5.3472838E-5 *
                     rtb_Tm_rr) - 0.0002074730388 * rtb_error_tmp) +
                   0.001981845031 * rtb_error_tmp_0) - rtb_error_tmp_1 *
                  0.006788067431) + 0.217964925 * rtSteeringangle_Torque) +
                2.836E-7) + ((((((((((3.534215197E-8 * rtb_error +
    1.618025757E-7 * rtb_IProdOut) + 3.167586246E-7 * Integrator) +
    1.704975313E-6 * rtb_T_diff_k) + 8.483283483E-6 * rtb_Tm_req_o) +
    5.347236085E-5 * rtb_Tm_rr) + 0.0002074729834 * rtb_error_tmp) +
    0.001981845682 * rtb_error_tmp_0) + rtb_error_tmp_1 * 0.006788067316) +
    0.2179649246 * rtSteeringangle_Torque) - 2.845E-7)) / 2.0 * rtu_bar_Torque /
    (rtu_bar_Torque * rtu_bar_Torque * rtTel_Inp_Kus_Torque + 1.53) -
    rtyaw_rate_Torque;

  /* Product: '<S37>/IProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_Ki'
   */
  rtb_IProdOut = rtb_error * rtTel_Inp_Ki_Torque;

  /* DiscreteIntegrator: '<S40>/Integrator' */
  Integrator = 0.00025 * rtb_IProdOut + rtDW_Torque->Integrator_DSTATE;

  /* Product: '<S3>/Product1' incorporates:
   *  Gain: '<S3>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Inport: '<Root>/Tel_Inp_Kp'
   *  Inport: '<Root>/map_TV'
   *  Product: '<S45>/PProd Out'
   *  Sum: '<S49>/Sum'
   */
  rtb_T_diff_k = (rtb_error * rtTel_Inp_Kp_Torque + Integrator) *
    0.080176150557382225 * rtmap_tv_Torque;

  /* Product: '<S1>/Product2' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req_o = (rtTm_rl_Torque + rtTm_rr_Torque) * 0.5 * rtDriver_req_Torque;

  /* MATLAB Function: '<S1>/MATLAB Function' */
  if (rtb_T_diff_k >= 0.0) {
    rtb_Tm_rr = rtb_Tm_req_o;
    rtb_Tm_req_o -= rtb_T_diff_k;
  } else {
    rtb_Tm_rr = rtb_Tm_req_o + rtb_T_diff_k;
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function' */

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
  if (rtb_Tm_req_o > rtTm_rr_Torque) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_Torque = rtTm_rr_Torque;
  } else if (rtb_Tm_req_o < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_Torque = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rl_a_Torque = rtb_Tm_req_o;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Outport: '<Root>/Tel_Out_error' */
  rtTel_Out_error_Torque = rtb_error;

  /* Update for DiscreteIntegrator: '<S40>/Integrator' */
  rtDW_Torque->Integrator_DSTATE = 0.00025 * rtb_IProdOut + Integrator;
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
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
