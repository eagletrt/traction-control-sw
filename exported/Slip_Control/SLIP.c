/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SLIP.c
 *
 * Code generated for Simulink model 'SLIP'.
 *
 * Model version                  : 6.365
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Aug 31 11:36:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "SLIP.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

const debug_bus SLIP_rtZdebug_bus = {
  0.0,                                 /* lambda */
  0.0,                                 /* filtered_lambda_error */
  0.0,                                 /* shallow_filtered_lambda_error */
  0.0,                                 /* proportional */
  0.0,                                 /* integral */
  0.0                                  /* derivative */
};                                     /* debug_bus ground */

/* Exported data definition */

/* Data with Exported storage */
real_T SLIP_T_max;                     /* '<Root>/in_T_max' */
real_T SLIP_in_Kd;                     /* '<Root>/in_Kd' */
real_T SLIP_in_Ki;                     /* '<Root>/in_Ki' */
real_T SLIP_in_Kp;                     /* '<Root>/in_Kp' */
real_T SLIP_in_iteration_step_seconds; /* '<Root>/in_iteration_step_seconds' */
real_T SLIP_in_lambda_reference;       /* '<Root>/in_lambda_reference' */
real_T SLIP_in_minimum_torque;         /* '<Root>/in_minimum_torque' */
real_T SLIP_in_omega_rl;               /* '<Root>/in_omega_rl' */
real_T SLIP_in_omega_rr;               /* '<Root>/in_omega_rr' */
real_T SLIP_in_shallow_window_seconds; /* '<Root>/in_shallow_window_seconds' */
real_T SLIP_in_window_seconds;         /* '<Root>/in_window_seconds' */
real_T SLIP_out_T_max_rl_slip;         /* '<Root>/out_T_max_rl_slip' */
real_T SLIP_out_T_max_rr_slip;         /* '<Root>/out_T_max_rr_slip' */
real_T SLIP_out_T_motor_rl;            /* '<Root>/out_T_motor_rl' */
real_T SLIP_out_T_motor_rr;            /* '<Root>/out_T_motor_rr' */
debug_bus SLIP_out_debug_bus_rl;       /* '<Root>/out_debug_bus_rl' */
debug_bus SLIP_out_debug_bus_rr;       /* '<Root>/out_debug_bus_rr' */
real_T SLIP_throttle;                  /* '<Root>/throttle' */
real_T SLIP_u;                         /* '<Root>/in_u_bar' */
real_T SLIP_yaw_rate;                  /* '<Root>/in_yaw_rate' */
real_T in_differentiation_step_seconds;
                                  /* '<Root>/in_differentiation_step_seconds' */
static void MATLABFunction(real_T rtu_new_sample, boolean_T rtu_external_reset,
  real_T rtu_lower_bound, real_T rtu_upper_bound, real_T rtu_sample_time, real_T
  *rty_integral);
static void MATLABFunction_i_Init(DW_MATLABFunction_l_SLIP *localDW);
static void MATLABFunction_e(real_T rtu_u, real_T rtu_window_length, real_T
  *rty_y, DW_MATLABFunction_l_SLIP *localDW);
static void Slip_estimation(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
  real_T *rty_lambda);

/* Forward declaration for local functions */
static void merge(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                  np, int32_T nq, int32_T iwork_data[], real_T xwork_data[]);
static void merge_block(int32_T idx_data[], real_T x_data[], int32_T offset,
  int32_T n, int32_T preSortLevel, int32_T iwork_data[], real_T xwork_data[]);
static void sort(real_T x_data[], const int32_T *x_size,
                 DW_MATLABFunction_l_SLIP *localDW);

/*
 * Output and update for atomic system:
 *    '<S9>/MATLAB Function'
 *    '<S19>/MATLAB Function'
 */
static void MATLABFunction(real_T rtu_new_sample, boolean_T rtu_external_reset,
  real_T rtu_lower_bound, real_T rtu_upper_bound, real_T rtu_sample_time, real_T
  *rty_integral)
{
  *rty_integral += rtu_new_sample * rtu_sample_time;
  if (rtu_external_reset) {
    *rty_integral = 0.0;
  }

  *rty_integral = fmax(fmin(*rty_integral, rtu_upper_bound), rtu_lower_bound);
}

/* Function for MATLAB Function: '<S5>/MATLAB Function' */
static void merge(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                  np, int32_T nq, int32_T iwork_data[], real_T xwork_data[])
{
  int32_T q;
  if (nq != 0) {
    int32_T iout;
    int32_T n;
    int32_T qend;
    qend = np + nq;
    for (q = 0; q < qend; q++) {
      iout = offset + q;
      iwork_data[q] = idx_data[iout];
      xwork_data[q] = x_data[iout];
    }

    n = 0;
    q = np;
    iout = offset - 1;
    int32_T exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[n] <= xwork_data[q]) {
        idx_data[iout] = iwork_data[n];
        x_data[iout] = xwork_data[n];
        if (n + 1 < np) {
          n++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < qend) {
          q++;
        } else {
          qend = iout - n;
          for (q = n + 1; q <= np; q++) {
            iout = qend + q;
            idx_data[iout] = iwork_data[q - 1];
            x_data[iout] = xwork_data[q - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/* Function for MATLAB Function: '<S5>/MATLAB Function' */
static void merge_block(int32_T idx_data[], real_T x_data[], int32_T offset,
  int32_T n, int32_T preSortLevel, int32_T iwork_data[], real_T xwork_data[])
{
  int32_T b;
  int32_T bLen;
  int32_T nPairs;
  int32_T nTail;
  int32_T tailOffset;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if (((uint32_T)nPairs & 1U) != 0U) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
              iwork_data, xwork_data);
      }
    }

    nTail = bLen << 1;
    nPairs >>= 1;
    b = (uint8_T)nPairs;
    for (tailOffset = 0; tailOffset < b; tailOffset++) {
      merge(idx_data, x_data, offset + tailOffset * nTail, bLen, bLen,
            iwork_data, xwork_data);
    }

    bLen = nTail;
  }

  if (n > bLen) {
    merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

/* Function for MATLAB Function: '<S5>/MATLAB Function' */
static void sort(real_T x_data[], const int32_T *x_size,
                 DW_MATLABFunction_l_SLIP *localDW)
{
  real_T b_xwork[256];
  real_T x4[4];
  real_T b_x;
  real_T tmp;
  int32_T idx_data[999];
  int32_T iwork_data[999];
  int32_T perm[4];
  int32_T b;
  int32_T bLen2;
  int32_T blockOffset;
  int32_T dim;
  int32_T e;
  int32_T exitg1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T ib;
  int32_T m;
  int32_T n;
  int32_T nLastBlock;
  int32_T p;
  int32_T q;
  int32_T vstride;
  int32_T vwork;
  int32_T vwork_size_idx_0;
  int16_T b_iwork[256];
  int16_T idx4[4];
  e = 0;
  if (*x_size != 1) {
    e = -1;
    nLastBlock = *x_size;
  } else {
    nLastBlock = 1;
  }

  b = nLastBlock - 1;
  vwork_size_idx_0 = nLastBlock;
  vstride = 1;
  for (dim = 0; dim <= e; dim++) {
    vstride *= *x_size;
  }

  for (dim = 0; dim < 1; dim++) {
    for (e = 0; e < vstride; e++) {
      for (n = 0; n <= b; n++) {
        localDW->vwork_data[n] = x_data[n * vstride + e];
      }

      if (vwork_size_idx_0 != 0) {
        x4[0] = 0.0;
        idx4[0] = 0;
        x4[1] = 0.0;
        idx4[1] = 0;
        x4[2] = 0.0;
        idx4[2] = 0;
        x4[3] = 0.0;
        idx4[3] = 0;
        ib = 0;
        for (nLastBlock = 0; nLastBlock < vwork_size_idx_0; nLastBlock++) {
          idx_data[nLastBlock] = 0;
          b_x = localDW->vwork_data[nLastBlock];
          localDW->b_x_data[nLastBlock] = b_x;
          ib++;
          idx4[ib - 1] = (int16_T)(nLastBlock + 1);
          x4[ib - 1] = b_x;
          if (ib == 4) {
            if (x4[0] <= x4[1]) {
              ib = 1;
              i2 = 2;
            } else {
              ib = 2;
              i2 = 1;
            }

            if (x4[2] <= x4[3]) {
              i3 = 3;
              i4 = 4;
            } else {
              i3 = 4;
              i4 = 3;
            }

            b_x = x4[i3 - 1];
            tmp = x4[ib - 1];
            if (tmp <= b_x) {
              tmp = x4[i2 - 1];
              if (tmp <= b_x) {
                blockOffset = ib;
                p = i2;
                ib = i3;
                i2 = i4;
              } else if (tmp <= x4[i4 - 1]) {
                blockOffset = ib;
                p = i3;
                ib = i2;
                i2 = i4;
              } else {
                blockOffset = ib;
                p = i3;
                ib = i4;
              }
            } else {
              b_x = x4[i4 - 1];
              if (tmp <= b_x) {
                if (x4[i2 - 1] <= b_x) {
                  blockOffset = i3;
                  p = ib;
                  ib = i2;
                  i2 = i4;
                } else {
                  blockOffset = i3;
                  p = ib;
                  ib = i4;
                }
              } else {
                blockOffset = i3;
                p = i4;
              }
            }

            idx_data[nLastBlock - 3] = idx4[blockOffset - 1];
            idx_data[nLastBlock - 2] = idx4[p - 1];
            idx_data[nLastBlock - 1] = idx4[ib - 1];
            idx_data[nLastBlock] = idx4[i2 - 1];
            localDW->b_x_data[nLastBlock - 3] = x4[blockOffset - 1];
            localDW->b_x_data[nLastBlock - 2] = x4[p - 1];
            localDW->b_x_data[nLastBlock - 1] = x4[ib - 1];
            localDW->b_x_data[nLastBlock] = x4[i2 - 1];
            ib = 0;
          }
        }

        if (ib > 0) {
          perm[1] = 0;
          perm[2] = 0;
          perm[3] = 0;
          switch (ib) {
           case 1:
            perm[0] = 1;
            break;

           case 2:
            if (x4[0] <= x4[1]) {
              perm[0] = 1;
              perm[1] = 2;
            } else {
              perm[0] = 2;
              perm[1] = 1;
            }
            break;

           default:
            if (x4[0] <= x4[1]) {
              if (x4[1] <= x4[2]) {
                perm[0] = 1;
                perm[1] = 2;
                perm[2] = 3;
              } else if (x4[0] <= x4[2]) {
                perm[0] = 1;
                perm[1] = 3;
                perm[2] = 2;
              } else {
                perm[0] = 3;
                perm[1] = 1;
                perm[2] = 2;
              }
            } else if (x4[0] <= x4[2]) {
              perm[0] = 2;
              perm[1] = 1;
              perm[2] = 3;
            } else if (x4[1] <= x4[2]) {
              perm[0] = 2;
              perm[1] = 3;
              perm[2] = 1;
            } else {
              perm[0] = 3;
              perm[1] = 2;
              perm[2] = 1;
            }
            break;
          }

          vwork = (uint8_T)ib;
          for (nLastBlock = 0; nLastBlock < vwork; nLastBlock++) {
            blockOffset = perm[nLastBlock];
            i2 = (vwork_size_idx_0 - ib) + nLastBlock;
            idx_data[i2] = idx4[blockOffset - 1];
            localDW->b_x_data[i2] = x4[blockOffset - 1];
          }
        }

        if (vwork_size_idx_0 - 1 >= 0) {
          memset(&iwork_data[0], 0, (uint32_T)vwork_size_idx_0 * sizeof(int32_T));
        }

        if (vwork_size_idx_0 - 1 >= 0) {
          memset(&localDW->vwork_data[0], 0, (uint32_T)vwork_size_idx_0 * sizeof
                 (real_T));
        }

        n = 2;
        if (vwork_size_idx_0 > 1) {
          if (vwork_size_idx_0 >= 256) {
            ib = vwork_size_idx_0 >> 8;
            for (n = 0; n < ib; n++) {
              i3 = (n << 8) - 1;
              for (nLastBlock = 0; nLastBlock < 6; nLastBlock++) {
                i4 = 1 << (nLastBlock + 2);
                bLen2 = i4 << 1;
                m = 256 >> (nLastBlock + 3);
                for (vwork = 0; vwork < m; vwork++) {
                  blockOffset = vwork * bLen2 + i3;
                  for (p = 0; p < bLen2; p++) {
                    i2 = (blockOffset + p) + 1;
                    b_iwork[p] = (int16_T)idx_data[i2];
                    b_xwork[p] = localDW->b_x_data[i2];
                  }

                  p = 0;
                  q = i4;
                  do {
                    exitg1 = 0;
                    blockOffset++;
                    if (b_xwork[p] <= b_xwork[q]) {
                      idx_data[blockOffset] = b_iwork[p];
                      localDW->b_x_data[blockOffset] = b_xwork[p];
                      if (p + 1 < i4) {
                        p++;
                      } else {
                        exitg1 = 1;
                      }
                    } else {
                      idx_data[blockOffset] = b_iwork[q];
                      localDW->b_x_data[blockOffset] = b_xwork[q];
                      if (q + 1 < bLen2) {
                        q++;
                      } else {
                        q = blockOffset - p;
                        for (blockOffset = p + 1; blockOffset <= i4; blockOffset
                             ++) {
                          i2 = q + blockOffset;
                          idx_data[i2] = b_iwork[blockOffset - 1];
                          localDW->b_x_data[i2] = b_xwork[blockOffset - 1];
                        }

                        exitg1 = 1;
                      }
                    }
                  } while (exitg1 == 0);
                }
              }
            }

            n = ib << 8;
            nLastBlock = vwork_size_idx_0 - n;
            if (nLastBlock > 0) {
              merge_block(idx_data, localDW->b_x_data, n, nLastBlock, 2,
                          iwork_data, localDW->vwork_data);
            }

            n = 8;
          }

          merge_block(idx_data, localDW->b_x_data, 0, vwork_size_idx_0, n,
                      iwork_data, localDW->vwork_data);
        }

        if (vwork_size_idx_0 - 1 >= 0) {
          memcpy(&localDW->vwork_data[0], &localDW->b_x_data[0], (uint32_T)
                 vwork_size_idx_0 * sizeof(real_T));
        }
      }

      for (n = 0; n <= b; n++) {
        x_data[e + n * vstride] = localDW->vwork_data[n];
      }
    }
  }
}

/*
 * System initialize for atomic system:
 *    '<S5>/MATLAB Function'
 *    '<S5>/MATLAB Function1'
 *    '<S15>/MATLAB Function'
 *    '<S15>/MATLAB Function1'
 */
static void MATLABFunction_i_Init(DW_MATLABFunction_l_SLIP *localDW)
{
  memset(&localDW->buffer[0], 0, 1000U * sizeof(real_T));
}

/*
 * Output and update for atomic system:
 *    '<S5>/MATLAB Function'
 *    '<S5>/MATLAB Function1'
 *    '<S15>/MATLAB Function'
 *    '<S15>/MATLAB Function1'
 */
static void MATLABFunction_e(real_T rtu_u, real_T rtu_window_length, real_T
  *rty_y, DW_MATLABFunction_l_SLIP *localDW)
{
  int32_T loop_ub;
  int32_T sorted_size;
  localDW->rtu_u[0] = rtu_u;
  memcpy(&localDW->rtu_u[1], &localDW->buffer[0], 999U * sizeof(real_T));
  memcpy(&localDW->buffer[0], &localDW->rtu_u[0], 1000U * sizeof(real_T));
  if (rtu_window_length < 1.0) {
    loop_ub = -1;
  } else {
    loop_ub = (int32_T)rtu_window_length - 1;
  }

  sorted_size = loop_ub + 1;
  if (loop_ub >= 0) {
    memcpy(&localDW->sorted_data[0], &localDW->buffer[0], (uint32_T)(loop_ub + 1)
           * sizeof(real_T));
  }

  sort(localDW->sorted_data, &sorted_size, localDW);
  *rty_y = localDW->sorted_data[(int32_T)((real_T)(loop_ub + 1) / 2.0) - 1];
}

/*
 * Output and update for atomic system:
 *    '<S2>/Slip_estimation'
 *    '<S3>/Slip_estimation'
 */
static void Slip_estimation(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
  real_T *rty_lambda)
{
  real_T Vmax;
  real_T Vmax_tmp;
  Vmax_tmp = fabs(rtu_omegaR);
  Vmax = fmax(fabs(rtu_u_bar), Vmax_tmp);
  if (Vmax > rtu_Vlow) {
    *rty_lambda = (rtu_omegaR - rtu_u_bar) / Vmax_tmp;
  } else {
    *rty_lambda = (rtu_omegaR - rtu_u_bar) * 2.0 / (Vmax * Vmax / rtu_Vlow +
      rtu_Vlow);
  }
}

/* Model step function */
void SLIP_step(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;
  real_T rtb_Product;
  real_T rtb_Product_tmp;
  real_T rtb_derivative;
  real_T rtb_derivative_tmp;
  real_T rtb_error;
  real_T rtb_error_h;
  real_T rtb_integral;
  real_T rtb_lambda;
  real_T rtb_y;
  real_T rtb_y_f;
  real_T rtb_y_k;
  int32_T idxDelay;

  /* Product: '<S3>/Product' incorporates:
   *  Inport: '<Root>/in_T_max'
   *  Inport: '<Root>/throttle'
   *  Product: '<S2>/Product'
   */
  rtb_Product_tmp = SLIP_throttle * SLIP_T_max;

  /* MATLAB Function: '<S3>/Slip_estimation' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S3>/Constant'
   *  Gain: '<S3>/Rr'
   *  Inport: '<Root>/in_omega_rl'
   *  Inport: '<Root>/in_u_bar'
   *  Inport: '<Root>/in_yaw_rate'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Add2'
   */
  Slip_estimation(0.2286 * SLIP_in_omega_rl, SLIP_u + SLIP_yaw_rate * 0.605, 1.0,
                  &rtb_y_k);

  /* Sum: '<S3>/Add1' incorporates:
   *  Inport: '<Root>/in_lambda_reference'
   */
  rtb_error = SLIP_in_lambda_reference - rtb_y_k;

  /* MATLAB Function: '<S15>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_shallow_window_seconds'
   *  Product: '<S15>/Divide3'
   */
  MATLABFunction_e(rtb_error, SLIP_in_shallow_window_seconds /
                   SLIP_in_iteration_step_seconds, &rtb_lambda,
                   &SLIP_DW->sf_MATLABFunction1_e);

  /* Product: '<S22>/Product' incorporates:
   *  Inport: '<Root>/in_Kp'
   */
  rtb_y_f = rtb_lambda * SLIP_in_Kp;

  /* Delay: '<S19>/Delay One Step' */
  rtb_integral = SLIP_DW->DelayOneStep_DSTATE;

  /* Switch: '<S19>/Switch' incorporates:
   *  Gain: '<S19>/Gain'
   *  Inport: '<Root>/in_Ki'
   */
  if (rtb_error > 0.0) {
    rtb_derivative = SLIP_in_Ki;
  } else {
    rtb_derivative = 0.16666666666666666 * SLIP_in_Ki;
  }

  /* MATLAB Function: '<S19>/MATLAB Function' incorporates:
   *  Constant: '<S14>/Constant'
   *  Constant: '<S15>/Constant'
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_minimum_torque'
   *  Inport: '<Root>/throttle'
   *  Product: '<S19>/Product1'
   *  RelationalOperator: '<S14>/Compare'
   *  Switch: '<S19>/Switch'
   */
  MATLABFunction(rtb_error * rtb_derivative, (SLIP_throttle < 0.03),
                 SLIP_in_minimum_torque, 100.0, SLIP_in_iteration_step_seconds,
                 &rtb_integral);

  /* MATLAB Function: '<S15>/MATLAB Function' incorporates:
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_window_seconds'
   *  Product: '<S15>/Divide2'
   */
  MATLABFunction_e(rtb_error, SLIP_in_window_seconds /
                   SLIP_in_iteration_step_seconds, &rtb_y,
                   &SLIP_DW->sf_MATLABFunction_f);

  /* Product: '<S15>/Divide1' incorporates:
   *  Inport: '<Root>/in_differentiation_step_seconds'
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Product: '<S5>/Divide1'
   */
  rtb_derivative_tmp = in_differentiation_step_seconds /
    SLIP_in_iteration_step_seconds;

  /* Delay: '<S15>/Delay' incorporates:
   *  DataTypeConversion: '<S15>/Cast To Single'
   *  Product: '<S15>/Divide1'
   */
  if ((real32_T)rtb_derivative_tmp < 1.0F) {
    rtb_derivative = rtb_y;
  } else {
    if ((real32_T)rtb_derivative_tmp > 100.0F) {
      idxDelay = 100;
    } else {
      idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_derivative_tmp),
        4.2949673E+9F);
    }

    rtb_derivative = SLIP_DW->Delay_DSTATE[100U - (uint32_T)idxDelay];
  }

  /* End of Delay: '<S15>/Delay' */

  /* Product: '<S15>/Product' incorporates:
   *  Inport: '<Root>/in_Kd'
   *  Inport: '<Root>/in_differentiation_step_seconds'
   *  Product: '<S15>/Divide'
   *  Sum: '<S15>/Sum'
   */
  rtb_derivative = (rtb_y - rtb_derivative) / in_differentiation_step_seconds *
    SLIP_in_Kd;

  /* MinMax: '<S15>/Max' incorporates:
   *  Inport: '<Root>/in_minimum_torque'
   *  Sum: '<S15>/Sum2'
   */
  rtb_error = fmax((rtb_y_f + rtb_integral) + rtb_derivative,
                   SLIP_in_minimum_torque);

  /* Switch: '<S17>/Switch2' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Product: '<S3>/Product'
   *  RelationalOperator: '<S17>/LowerRelop1'
   *  RelationalOperator: '<S17>/UpperRelop'
   *  Switch: '<S17>/Switch'
   */
  if (rtb_error > rtb_Product_tmp) {
    rtb_error = rtb_Product_tmp;
  } else if (rtb_error < 0.0) {
    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    rtb_error = 0.0;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Switch: '<S16>/Switch2' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Product: '<S3>/Product'
   *  RelationalOperator: '<S16>/LowerRelop1'
   *  RelationalOperator: '<S16>/UpperRelop'
   *  Switch: '<S16>/Switch'
   */
  if (rtb_Product_tmp > rtb_error) {
    /* Outport: '<Root>/out_T_motor_rl' */
    SLIP_out_T_motor_rl = rtb_error;
  } else if (rtb_Product_tmp < 0.0) {
    /* Switch: '<S16>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Outport: '<Root>/out_T_motor_rl'
     */
    SLIP_out_T_motor_rl = 0.0;
  } else {
    /* Outport: '<Root>/out_T_motor_rl' */
    SLIP_out_T_motor_rl = rtb_Product_tmp;
  }

  /* End of Switch: '<S16>/Switch2' */

  /* Outport: '<Root>/out_T_max_rl_slip' */
  SLIP_out_T_max_rl_slip = rtb_error;

  /* BusCreator: '<S3>/Bus Creator' incorporates:
   *  Outport: '<Root>/out_debug_bus_rl'
   */
  SLIP_out_debug_bus_rl.lambda = rtb_y_k;
  SLIP_out_debug_bus_rl.filtered_lambda_error = rtb_y;
  SLIP_out_debug_bus_rl.shallow_filtered_lambda_error = rtb_lambda;
  SLIP_out_debug_bus_rl.proportional = rtb_y_f;
  SLIP_out_debug_bus_rl.integral = rtb_integral;
  SLIP_out_debug_bus_rl.derivative = rtb_derivative;

  /* MATLAB Function: '<S2>/Slip_estimation' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Rr'
   *  Inport: '<Root>/in_omega_rr'
   *  Inport: '<Root>/in_u_bar'
   *  Inport: '<Root>/in_yaw_rate'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Add2'
   */
  Slip_estimation(0.2286 * SLIP_in_omega_rr, SLIP_u + SLIP_yaw_rate * -0.605,
                  1.0, &rtb_lambda);

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/in_lambda_reference'
   */
  rtb_error_h = SLIP_in_lambda_reference - rtb_lambda;

  /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_shallow_window_seconds'
   *  Product: '<S5>/Divide3'
   */
  MATLABFunction_e(rtb_error_h, SLIP_in_shallow_window_seconds /
                   SLIP_in_iteration_step_seconds, &rtb_y_k,
                   &SLIP_DW->sf_MATLABFunction1);

  /* Product: '<S12>/Product' incorporates:
   *  Inport: '<Root>/in_Kp'
   */
  rtb_error = rtb_y_k * SLIP_in_Kp;

  /* Delay: '<S9>/Delay One Step' */
  rtb_Product = SLIP_DW->DelayOneStep_DSTATE_h;

  /* Switch: '<S9>/Switch' incorporates:
   *  Gain: '<S9>/Gain'
   *  Inport: '<Root>/in_Ki'
   */
  if (rtb_error_h > 0.0) {
    rtb_derivative = SLIP_in_Ki;
  } else {
    rtb_derivative = 0.16666666666666666 * SLIP_in_Ki;
  }

  /* MATLAB Function: '<S9>/MATLAB Function' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_minimum_torque'
   *  Inport: '<Root>/throttle'
   *  Product: '<S9>/Product1'
   *  RelationalOperator: '<S4>/Compare'
   *  Switch: '<S9>/Switch'
   */
  MATLABFunction(rtb_error_h * rtb_derivative, (SLIP_throttle < 0.03),
                 SLIP_in_minimum_torque, 100.0, SLIP_in_iteration_step_seconds,
                 &rtb_Product);

  /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
   *  Inport: '<Root>/in_iteration_step_seconds'
   *  Inport: '<Root>/in_window_seconds'
   *  Product: '<S5>/Divide2'
   */
  MATLABFunction_e(rtb_error_h, SLIP_in_window_seconds /
                   SLIP_in_iteration_step_seconds, &rtb_y_f,
                   &SLIP_DW->sf_MATLABFunction_e);

  /* Delay: '<S5>/Delay' incorporates:
   *  DataTypeConversion: '<S5>/Cast To Single'
   */
  if ((real32_T)rtb_derivative_tmp < 1.0F) {
    rtb_derivative = rtb_y_f;
  } else {
    if ((real32_T)rtb_derivative_tmp > 100.0F) {
      idxDelay = 100;
    } else {
      idxDelay = (int32_T)(uint32_T)fmodf(truncf((real32_T)rtb_derivative_tmp),
        4.2949673E+9F);
    }

    rtb_derivative = SLIP_DW->Delay_DSTATE_d[100U - (uint32_T)idxDelay];
  }

  /* End of Delay: '<S5>/Delay' */

  /* Product: '<S5>/Product' incorporates:
   *  Inport: '<Root>/in_Kd'
   *  Inport: '<Root>/in_differentiation_step_seconds'
   *  Product: '<S5>/Divide'
   *  Sum: '<S5>/Sum'
   */
  rtb_derivative = (rtb_y_f - rtb_derivative) / in_differentiation_step_seconds *
    SLIP_in_Kd;

  /* BusCreator: '<S2>/Bus Creator' incorporates:
   *  Outport: '<Root>/out_debug_bus_rr'
   */
  SLIP_out_debug_bus_rr.lambda = rtb_lambda;
  SLIP_out_debug_bus_rr.filtered_lambda_error = rtb_y_f;
  SLIP_out_debug_bus_rr.shallow_filtered_lambda_error = rtb_y_k;
  SLIP_out_debug_bus_rr.proportional = rtb_error;
  SLIP_out_debug_bus_rr.integral = rtb_Product;
  SLIP_out_debug_bus_rr.derivative = rtb_derivative;

  /* MinMax: '<S5>/Max' incorporates:
   *  Inport: '<Root>/in_minimum_torque'
   *  Sum: '<S5>/Sum2'
   */
  rtb_lambda = fmax((rtb_error + rtb_Product) + rtb_derivative,
                    SLIP_in_minimum_torque);

  /* Switch: '<S7>/Switch2' incorporates:
   *  Constant: '<S2>/Constant3'
   *  RelationalOperator: '<S7>/LowerRelop1'
   *  RelationalOperator: '<S7>/UpperRelop'
   *  Switch: '<S7>/Switch'
   */
  if (rtb_lambda > rtb_Product_tmp) {
    rtb_error = rtb_Product_tmp;
  } else if (rtb_lambda < 0.0) {
    /* Switch: '<S7>/Switch' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    rtb_error = 0.0;
  } else {
    rtb_error = rtb_lambda;
  }

  /* End of Switch: '<S7>/Switch2' */

  /* Outport: '<Root>/out_T_max_rr_slip' */
  SLIP_out_T_max_rr_slip = rtb_error;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Product_tmp > rtb_error) {
    /* Outport: '<Root>/out_T_motor_rr' */
    SLIP_out_T_motor_rr = rtb_error;
  } else if (rtb_Product_tmp < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S2>/Constant2'
     *  Outport: '<Root>/out_T_motor_rr'
     */
    SLIP_out_T_motor_rr = 0.0;
  } else {
    /* Outport: '<Root>/out_T_motor_rr' */
    SLIP_out_T_motor_rr = rtb_Product_tmp;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Update for Delay: '<S19>/Delay One Step' */
  SLIP_DW->DelayOneStep_DSTATE = rtb_integral;

  /* Update for Delay: '<S9>/Delay One Step' */
  SLIP_DW->DelayOneStep_DSTATE_h = rtb_Product;
  for (idxDelay = 0; idxDelay < 99; idxDelay++) {
    /* Update for Delay: '<S15>/Delay' */
    SLIP_DW->Delay_DSTATE[idxDelay] = SLIP_DW->Delay_DSTATE[idxDelay + 1];

    /* Update for Delay: '<S5>/Delay' */
    SLIP_DW->Delay_DSTATE_d[idxDelay] = SLIP_DW->Delay_DSTATE_d[idxDelay + 1];
  }

  /* Update for Delay: '<S15>/Delay' */
  SLIP_DW->Delay_DSTATE[99] = rtb_y;

  /* Update for Delay: '<S5>/Delay' */
  SLIP_DW->Delay_DSTATE_d[99] = rtb_y_f;
}

/* Model initialize function */
void SLIP_initialize(RT_MODEL_SLIP *const SLIP_M)
{
  DW_SLIP *SLIP_DW = SLIP_M->dwork;

  /* Registration code */

  /* Storage classes */
  SLIP_out_debug_bus_rl = SLIP_rtZdebug_bus;
  SLIP_out_debug_bus_rr = SLIP_rtZdebug_bus;
  SLIP_out_T_max_rl_slip = 0.0;
  SLIP_out_T_max_rr_slip = 0.0;
  SLIP_out_T_motor_rr = 0.0;
  SLIP_out_T_motor_rl = 0.0;

  /* Storage classes */
  SLIP_throttle = 0.0;
  SLIP_u = 0.0;
  SLIP_in_omega_rr = 0.0;
  SLIP_in_omega_rl = 0.0;
  SLIP_yaw_rate = 0.0;
  SLIP_T_max = 0.0;
  SLIP_in_lambda_reference = 0.0;
  SLIP_in_Kp = 0.0;
  SLIP_in_Ki = 0.0;
  SLIP_in_Kd = 0.0;
  SLIP_in_minimum_torque = 0.0;
  SLIP_in_iteration_step_seconds = 0.0;
  in_differentiation_step_seconds = 0.0;
  SLIP_in_window_seconds = 0.0;
  SLIP_in_shallow_window_seconds = 0.0;

  /* states (dwork) */
  (void) memset((void *)SLIP_DW, 0,
                sizeof(DW_SLIP));

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function1' */
  MATLABFunction_i_Init(&SLIP_DW->sf_MATLABFunction1_e);

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function' */
  MATLABFunction_i_Init(&SLIP_DW->sf_MATLABFunction_f);

  /* SystemInitialize for MATLAB Function: '<S5>/MATLAB Function1' */
  MATLABFunction_i_Init(&SLIP_DW->sf_MATLABFunction1);

  /* SystemInitialize for MATLAB Function: '<S5>/MATLAB Function' */
  MATLABFunction_i_Init(&SLIP_DW->sf_MATLABFunction_e);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
