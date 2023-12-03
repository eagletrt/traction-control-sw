/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AllControl.c
 *
 * Code generated for Simulink model 'AllControl'.
 *
 * Model version                  : 6.39
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Dec  2 16:40:32 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "AllControl.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req_AllControl;        /* '<Root>/driver_request' */
real_T rtSteeringangle_AllControl;     /* '<Root>/delta' */
real_T rtTel_Inp_SC_PeakTorque_AllCont;/* '<Root>/Tel_Inp_SC_PeakTorque' */
real_T rtTel_Inp_SC_SpeedCutoff_AllCon;/* '<Root>/Tel_Inp_SC_SpeedCutoff' */
real_T rtTel_Inp_SC_StartTorque_AllCon;/* '<Root>/Tel_Inp_SC_StartTorque' */
real_T rtTel_Inp_TV_Ki_AllControl;     /* '<Root>/Tel_Inp_TV_Ki' */
real_T rtTel_Inp_TV_Kp_AllControl;     /* '<Root>/Tel_Inp_TV_Kp' */
real_T rtTel_Inp_TV_Kus_AllControl;    /* '<Root>/Tel_Inp_TV_Kus' */
real_T rtTel_Out_error_AllControl;     /* '<Root>/Tel_Out_error' */
real_T rtTm_rl_AllControl;             /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a_AllControl;           /* '<Root>/Tm_rl' */
real_T rtTm_rr_AllControl;             /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m_AllControl;           /* '<Root>/Tm_rr' */
real_T rtbrake_AllControl;             /* '<Root>/Brake' */
real_T rtmap_sc_AllControl;            /* '<Root>/map_sc' */
real_T rtmap_tv_AllControl;            /* '<Root>/map_TV' */
real_T rtomega_rl_AllControl;          /* '<Root>/omega_rl' */
real_T rtomega_rr_AllControl;          /* '<Root>/omega_rr' */
real_T rtu_bar_AllControl;             /* '<Root>/u_bar' */
real_T rtyaw_rate_AllControl;          /* '<Root>/Omega' */

/* Model step function */
void AllControl_step(RT_MODEL_AllControl *const rtM_AllControl)
{
  DW_AllControl *rtDW_AllControl = rtM_AllControl->dwork;
  real_T Integrator;
  real_T T_max_nomap;
  real_T load_transf_coeff;
  real_T load_transf_coeff_tmp;
  real_T rtb_Product;
  real_T rtb_Product2;
  real_T rtb_Product3;
  real_T rtb_Product_tmp;
  real_T rtb_Saturation;
  real_T rtb_Switch2;
  real_T rtb_T_max;
  real_T rtb_Tm_req;
  int8_T tmp;
  int8_T tmp_0;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtTm_rl_AllControl * rtDriver_req_AllControl;

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_SC_PeakTorque'
   *  Inport: '<Root>/Tel_Inp_SC_SpeedCutoff'
   *  Inport: '<Root>/Tel_Inp_SC_StartTorque'
   *  Inport: '<Root>/map_sc'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   *  Product: '<S1>/Product3'
   */
  rtb_Product3 = (rtTel_Inp_SC_PeakTorque_AllCont -
                  rtTel_Inp_SC_StartTorque_AllCon) * fmin(fmax
    (rtu_bar_AllControl / rtTel_Inp_SC_SpeedCutoff_AllCon, 0.0), 1.0) +
    rtTel_Inp_SC_StartTorque_AllCon;
  T_max_nomap = rtb_Product3;
  load_transf_coeff_tmp = rtyaw_rate_AllControl * rtu_bar_AllControl * 61.217 /
    4.0;
  load_transf_coeff = (load_transf_coeff_tmp + 411.00221250000004) /
    411.00221250000004;
  if (load_transf_coeff < 1.0) {
    T_max_nomap = rtb_Product3 * load_transf_coeff;
  }

  rtb_T_max = (rtb_Product - T_max_nomap) * (1.0 - rtmap_sc_AllControl) +
    T_max_nomap;

  /* End of MATLAB Function: '<S1>/MATLAB Function2' */

  /* Switch: '<S9>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S9>/LowerRelop1'
   *  RelationalOperator: '<S9>/UpperRelop'
   *  Switch: '<S9>/Switch'
   */
  if (rtb_T_max > rtTm_rl_AllControl) {
    rtb_T_max = rtTm_rl_AllControl;
  } else if (rtb_T_max < 0.0) {
    /* Switch: '<S9>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_T_max = 0.0;
  }

  /* End of Switch: '<S9>/Switch2' */

  /* Switch: '<S8>/Switch2' incorporates:
   *  RelationalOperator: '<S8>/LowerRelop1'
   */
  if (rtb_Product <= rtb_T_max) {
    /* Switch: '<S8>/Switch' incorporates:
     *  Constant: '<S1>/Constant4'
     *  RelationalOperator: '<S8>/UpperRelop'
     */
    if (rtb_Product < 0.0) {
      rtb_T_max = 0.0;
    } else {
      rtb_T_max = rtb_Product;
    }

    /* End of Switch: '<S8>/Switch' */
  }

  /* End of Switch: '<S8>/Switch2' */

  /* MATLAB Function: '<S5>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_Product = pow(rtSteeringangle_AllControl, 10.0);
  Integrator = pow(rtSteeringangle_AllControl, 9.0);
  rtb_Saturation = pow(rtSteeringangle_AllControl, 8.0);
  T_max_nomap = pow(rtSteeringangle_AllControl, 7.0);
  rtb_Switch2 = pow(rtSteeringangle_AllControl, 6.0);
  rtb_Tm_req = pow(rtSteeringangle_AllControl, 5.0);
  rtb_Product2 = pow(rtSteeringangle_AllControl, 4.0);
  load_transf_coeff = pow(rtSteeringangle_AllControl, 3.0);
  rtb_Product_tmp = rtSteeringangle_AllControl * rtSteeringangle_AllControl;

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S17>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/Tel_Inp_TV_Kus'
   *  Inport: '<Root>/delta'
   *  Inport: '<Root>/u_bar'
   *  MATLAB Function: '<S17>/Yaw-Rate'
   *  MATLAB Function: '<S5>/SteeringModel'
   */
  rtb_Product = (((((((((((-3.534335194E-8 * rtb_Product + 1.618153531E-7 *
    Integrator) - 3.16758626E-7 * rtb_Saturation) + 1.704839325E-6 * T_max_nomap)
                        - 8.483242635E-6 * rtb_Switch2) + 5.3472838E-5 *
                       rtb_Tm_req) - 0.0002074730388 * rtb_Product2) +
                     0.001981845031 * load_transf_coeff) - rtb_Product_tmp *
                    0.006788067431) + 0.217964925 * rtSteeringangle_AllControl)
                  + 2.836E-7) + ((((((((((3.534215197E-8 * rtb_Product +
    1.618025757E-7 * Integrator) + 3.167586246E-7 * rtb_Saturation) +
    1.704975313E-6 * T_max_nomap) + 8.483283483E-6 * rtb_Switch2) +
    5.347236085E-5 * rtb_Tm_req) + 0.0002074729834 * rtb_Product2) +
    0.001981845682 * load_transf_coeff) + rtb_Product_tmp * 0.006788067316) +
    0.2179649246 * rtSteeringangle_AllControl) - 2.845E-7)) / 2.0 *
    rtu_bar_AllControl / (rtu_bar_AllControl * rtu_bar_AllControl *
    rtTel_Inp_TV_Kus_AllControl + 1.53) - rtyaw_rate_AllControl;

  /* Product: '<S56>/PProd Out' incorporates:
   *  Inport: '<Root>/Tel_Inp_TV_Kp'
   */
  rtb_Saturation = rtb_Product * rtTel_Inp_TV_Kp_AllControl;

  /* Sum: '<S61>/Sum Fdbk' */
  T_max_nomap = rtb_Saturation + rtDW_AllControl->Integrator_DSTATE;

  /* DeadZone: '<S44>/DeadZone' */
  if (T_max_nomap > 300.0) {
    T_max_nomap -= 300.0;
  } else if (T_max_nomap >= -300.0) {
    T_max_nomap = 0.0;
  } else {
    T_max_nomap -= -300.0;
  }

  /* End of DeadZone: '<S44>/DeadZone' */

  /* Product: '<S48>/IProd Out' incorporates:
   *  Constant: '<S15>/Constant'
   *  Inport: '<Root>/Tel_Inp_TV_Ki'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S5>/Product3'
   *  RelationalOperator: '<S15>/Compare'
   */
  rtb_Product *= rtDriver_req_AllControl >= 0.01 ? rtTel_Inp_TV_Ki_AllControl :
    0.0;

  /* Switch: '<S42>/Switch1' incorporates:
   *  Constant: '<S42>/Clamping_zero'
   *  Constant: '<S42>/Constant'
   *  Constant: '<S42>/Constant2'
   *  RelationalOperator: '<S42>/fix for DT propagation issue'
   */
  if (T_max_nomap > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S42>/Switch2' incorporates:
   *  Constant: '<S42>/Clamping_zero'
   *  Constant: '<S42>/Constant3'
   *  Constant: '<S42>/Constant4'
   *  RelationalOperator: '<S42>/fix for DT propagation issue1'
   */
  if (rtb_Product > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S42>/Switch' incorporates:
   *  Constant: '<S42>/Clamping_zero'
   *  Constant: '<S42>/Constant1'
   *  Logic: '<S42>/AND3'
   *  RelationalOperator: '<S42>/Equal1'
   *  RelationalOperator: '<S42>/Relational Operator'
   *  Switch: '<S42>/Switch1'
   *  Switch: '<S42>/Switch2'
   */
  if ((T_max_nomap != 0.0) && (tmp == tmp_0)) {
    rtb_Product = 0.0;
  }

  /* End of Switch: '<S42>/Switch' */

  /* DiscreteIntegrator: '<S51>/Integrator' */
  Integrator = 0.00025 * rtb_Product + rtDW_AllControl->Integrator_DSTATE;

  /* DiscreteIntegrator: '<S51>/Integrator' */
  if (Integrator >= 20.0) {
    /* DiscreteIntegrator: '<S51>/Integrator' */
    Integrator = 20.0;
  } else if (Integrator <= -20.0) {
    /* DiscreteIntegrator: '<S51>/Integrator' */
    Integrator = -20.0;
  }

  /* Sum: '<S60>/Sum' */
  T_max_nomap = rtb_Saturation + Integrator;

  /* Saturate: '<S58>/Saturation' */
  if (T_max_nomap > 300.0) {
    T_max_nomap = 300.0;
  } else if (T_max_nomap < -300.0) {
    T_max_nomap = -300.0;
  }

  /* Product: '<S5>/Product1' incorporates:
   *  Gain: '<S5>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Inport: '<Root>/map_TV'
   *  Saturate: '<S58>/Saturation'
   */
  rtb_Saturation = 0.080176150557382225 * T_max_nomap * rtmap_tv_AllControl;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_Tm_req = (rtTm_rl_AllControl + rtTm_rr_AllControl) *
    rtDriver_req_AllControl * 0.5;

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product2 = rtDriver_req_AllControl * rtTm_rr_AllControl;

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/map_sc'
   */
  T_max_nomap = rtb_Product3;
  load_transf_coeff = (411.00221250000004 - load_transf_coeff_tmp) /
    411.00221250000004;
  if (load_transf_coeff < 1.0) {
    T_max_nomap = rtb_Product3 * load_transf_coeff;
  }

  rtb_Product3 = (rtb_Product2 - T_max_nomap) * (1.0 - rtmap_sc_AllControl) +
    T_max_nomap;

  /* Switch: '<S10>/Switch2' incorporates:
   *  Constant: '<S1>/Constant5'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S10>/LowerRelop1'
   *  RelationalOperator: '<S10>/UpperRelop'
   *  Switch: '<S10>/Switch'
   */
  if (rtb_Product3 > rtTm_rr_AllControl) {
    T_max_nomap = rtTm_rr_AllControl;
  } else if (rtb_Product3 < 0.0) {
    /* Switch: '<S10>/Switch' incorporates:
     *  Constant: '<S1>/Constant5'
     */
    T_max_nomap = 0.0;
  } else {
    T_max_nomap = rtb_Product3;
  }

  /* End of Switch: '<S10>/Switch2' */

  /* Switch: '<S11>/Switch2' incorporates:
   *  RelationalOperator: '<S11>/LowerRelop1'
   */
  if (rtb_Product2 <= T_max_nomap) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S1>/Constant6'
     *  RelationalOperator: '<S11>/UpperRelop'
     */
    if (rtb_Product2 < 0.0) {
      T_max_nomap = 0.0;
    } else {
      T_max_nomap = rtb_Product2;
    }

    /* End of Switch: '<S11>/Switch' */
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Switch: '<S13>/Switch2' incorporates:
   *  Constant: '<S1>/Constant8'
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S13>/Switch'
   */
  if (rtb_Tm_req > rtb_T_max) {
    rtb_Product3 = rtb_T_max;
  } else if (rtb_Tm_req < 0.0) {
    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S1>/Constant8'
     */
    rtb_Product3 = 0.0;
  } else {
    rtb_Product3 = rtb_Tm_req;
  }

  /* Switch: '<S12>/Switch2' incorporates:
   *  Constant: '<S1>/Constant7'
   *  RelationalOperator: '<S12>/LowerRelop1'
   *  RelationalOperator: '<S12>/UpperRelop'
   *  Switch: '<S12>/Switch'
   */
  if (rtb_Tm_req > T_max_nomap) {
    rtb_Tm_req = T_max_nomap;
  } else if (rtb_Tm_req < 0.0) {
    /* Switch: '<S12>/Switch' incorporates:
     *  Constant: '<S1>/Constant7'
     */
    rtb_Tm_req = 0.0;
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/driver_request'
   *  Switch: '<S12>/Switch2'
   *  Switch: '<S13>/Switch2'
   */
  rtb_Switch2 = fmax(rtb_Product3, rtb_Tm_req);
  rtb_Tm_req = fmin(fmax(rtDriver_req_AllControl * 10.0, 0.0), 1.0);
  rtb_Product3 = (rtb_Saturation * 0.5 + rtb_Switch2) * rtb_Tm_req;
  rtb_Switch2 = (rtb_Switch2 - rtb_Saturation * 0.5) * rtb_Tm_req;

  /* Switch: '<S7>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  RelationalOperator: '<S7>/LowerRelop1'
   *  RelationalOperator: '<S7>/UpperRelop'
   *  Switch: '<S7>/Switch'
   */
  if (rtb_Product3 > rtb_T_max) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m_AllControl = rtb_T_max;
  } else if (rtb_Product3 < 0.0) {
    /* Switch: '<S7>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m_AllControl = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S7>/Switch'
     */
    rtTm_rr_m_AllControl = rtb_Product3;
  }

  /* End of Switch: '<S7>/Switch2' */

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Switch2 > T_max_nomap) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a_AllControl = T_max_nomap;
  } else if (rtb_Switch2 < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a_AllControl = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S6>/Switch'
     */
    rtTm_rl_a_AllControl = rtb_Switch2;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Outport: '<Root>/Tel_Out_error' */
  rtTel_Out_error_AllControl = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S51>/Integrator' */
  rtDW_AllControl->Integrator_DSTATE = 0.00025 * rtb_Product + Integrator;
  if (rtDW_AllControl->Integrator_DSTATE >= 20.0) {
    rtDW_AllControl->Integrator_DSTATE = 20.0;
  } else if (rtDW_AllControl->Integrator_DSTATE <= -20.0) {
    rtDW_AllControl->Integrator_DSTATE = -20.0;
  }

  /* End of Update for DiscreteIntegrator: '<S51>/Integrator' */
}

/* Model initialize function */
void AllControl_initialize(RT_MODEL_AllControl *const rtM_AllControl)
{
  DW_AllControl *rtDW_AllControl = rtM_AllControl->dwork;

  /* Registration code */

  /* Storage classes */
  rtDriver_req_AllControl = 0.0;
  rtu_bar_AllControl = 0.0;
  rtomega_rr_AllControl = 0.0;
  rtomega_rl_AllControl = 0.0;
  rtyaw_rate_AllControl = 0.0;
  rtSteeringangle_AllControl = 0.0;
  rtbrake_AllControl = 0.0;
  rtTm_rl_AllControl = 0.0;
  rtTm_rr_AllControl = 0.0;
  rtmap_tv_AllControl = 0.0;
  rtmap_sc_AllControl = 0.0;
  rtTel_Inp_SC_StartTorque_AllCon = 0.0;
  rtTel_Inp_SC_PeakTorque_AllCont = 0.0;
  rtTel_Inp_SC_SpeedCutoff_AllCon = 0.0;
  rtTel_Inp_TV_Kus_AllControl = 0.0;
  rtTel_Inp_TV_Kp_AllControl = 0.0;
  rtTel_Inp_TV_Ki_AllControl = 0.0;

  /* Storage classes */
  rtTm_rr_m_AllControl = 0.0;
  rtTm_rl_a_AllControl = 0.0;
  rtTel_Out_error_AllControl = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW_AllControl, 0,
                sizeof(DW_AllControl));

  /* InitializeConditions for DiscreteIntegrator: '<S51>/Integrator' */
  rtDW_AllControl->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
