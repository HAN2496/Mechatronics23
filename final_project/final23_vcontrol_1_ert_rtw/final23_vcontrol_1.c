/*
 * final23_vcontrol_1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_vcontrol_1".
 *
 * Model version              : 1.20
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 21:20:35 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "final23_vcontrol_1.h"
#include "final23_vcontrol_1_private.h"

/* Block signals (default storage) */
B_final23_vcontrol_1_T final23_vcontrol_1_B;

/* Continuous states */
X_final23_vcontrol_1_T final23_vcontrol_1_X;

/* Block states (default storage) */
DW_final23_vcontrol_1_T final23_vcontrol_1_DW;

/* Real-time model */
static RT_MODEL_final23_vcontrol_1_T final23_vcontrol_1_M_;
RT_MODEL_final23_vcontrol_1_T *const final23_vcontrol_1_M =
  &final23_vcontrol_1_M_;
real_T sMultiWord2Double(const uint64_T u1[], int32_T n1, int32_T e1)
{
  real_T y;
  uint64_T cb;
  uint64_T u1i;
  int32_T exp_0;
  int32_T i;
  y = 0.0;
  exp_0 = e1;
  if ((u1[n1 - 1] & 9223372036854775808ULL) != 0ULL) {
    cb = 1ULL;
    for (i = 0; i < n1; i++) {
      u1i = ~u1[i];
      cb += u1i;
      y -= ldexp((real_T)cb, exp_0);
      cb = (uint64_T)(cb < u1i);
      exp_0 += 64;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += ldexp((real_T)u1[i], exp_0);
      exp_0 += 64;
    }
  }

  return y;
}

void sMultiWordMul(const uint64_T u1[], int32_T n1, const uint64_T u2[], int32_T
                   n2, uint64_T y[], int32_T n)
{
  uint64_T a0;
  uint64_T a1;
  uint64_T b1;
  uint64_T cb;
  uint64_T cb1;
  uint64_T cb2;
  uint64_T u1i;
  uint64_T w01;
  uint64_T w10;
  uint64_T yk;
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T ni;
  boolean_T isNegative1;
  boolean_T isNegative2;
  isNegative1 = ((u1[n1 - 1] & 9223372036854775808ULL) != 0ULL);
  isNegative2 = ((u2[n2 - 1] & 9223372036854775808ULL) != 0ULL);
  cb1 = 1ULL;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0ULL;
  }

  for (i = 0; i < n1; i++) {
    cb = 0ULL;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint64_T)(u1i < cb1);
    }

    a1 = u1i >> 32U;
    a0 = u1i & 4294967295ULL;
    cb2 = 1ULL;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint64_T)(u1i < cb2);
      }

      b1 = u1i >> 32U;
      u1i &= 4294967295ULL;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint64_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 32U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 32U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 32U;
      cb += w01 >> 32U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1ULL;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint64_T)(yk < cb);
    }
  }
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  final23_vcontrol_1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  final23_vcontrol_1_step();
  final23_vcontrol_1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  final23_vcontrol_1_step();
  final23_vcontrol_1_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * System initialize for atomic system:
 *    synthesized block
 *    synthesized block
 */
void final23_vcon_MovingAverage_Init(DW_MovingAverage_final23_vcon_T *localDW)
{
  g_dsp_private_SlidingWindowAv_T *obj;
  int32_T i;

  /* InitializeConditions for MATLABSystem: '<S5>/Moving Average' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pCumSum = 0.0;
    for (i = 0; i < 19; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<S5>/Moving Average' */
}

/*
 * Start for atomic system:
 *    synthesized block
 *    synthesized block
 */
void final23_vco_MovingAverage_Start(DW_MovingAverage_final23_vcon_T *localDW)
{
  /* Start for MATLABSystem: '<S5>/Moving Average' */
  localDW->obj.matlabCodegenIsDeleted = true;
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isSetupComplete = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStatistic = &localDW->obj._pobj0;
  localDW->obj.isSetupComplete = true;
  localDW->obj.TunablePropsChanged = false;
}

/*
 * Output and update for atomic system:
 *    synthesized block
 *    synthesized block
 */
void final23_vcontrol__MovingAverage(real_T rtu_0,
  B_MovingAverage_final23_vcont_T *localB, DW_MovingAverage_final23_vcon_T
  *localDW)
{
  g_dsp_private_SlidingWindowAv_T *obj;
  real_T csum;
  real_T cumRevIndex;
  real_T z;
  int32_T i;

  /* MATLABSystem: '<S5>/Moving Average' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pCumSum = 0.0;
    for (i = 0; i < 19; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->isSetupComplete = true;
    obj->pCumSum = 0.0;
    for (i = 0; i < 19; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
  }

  cumRevIndex = obj->pCumRevIndex;
  csum = obj->pCumSum;
  for (i = 0; i < 19; i++) {
    localB->csumrev[i] = obj->pCumSumRev[i];
  }

  csum += rtu_0;
  z = localB->csumrev[(int32_T)cumRevIndex - 1] + csum;
  localB->csumrev[(int32_T)cumRevIndex - 1] = rtu_0;
  if (cumRevIndex != 19.0) {
    cumRevIndex++;
  } else {
    cumRevIndex = 1.0;
    csum = 0.0;
    for (i = 17; i >= 0; i--) {
      localB->csumrev[i] += localB->csumrev[i + 1];
    }
  }

  obj->pCumSum = csum;
  for (i = 0; i < 19; i++) {
    obj->pCumSumRev[i] = localB->csumrev[i];
  }

  obj->pCumRevIndex = cumRevIndex;

  /* MATLABSystem: '<S5>/Moving Average' */
  localB->MovingAverage = z / 20.0;
}

/*
 * Termination for atomic system:
 *    synthesized block
 *    synthesized block
 */
void final23_vcon_MovingAverage_Term(DW_MovingAverage_final23_vcon_T *localDW)
{
  g_dsp_private_SlidingWindowAv_T *obj;

  /* Terminate for MATLABSystem: '<S5>/Moving Average' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/Moving Average' */
}

/* Model step function */
void final23_vcontrol_1_step(void)
{
  /* local block i/o variables */
  real_T rtb_DataTypeConversion;
  real_T rtb_DataTypeConversion_a;
  if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
    /* set solver stop time */
    if (!(final23_vcontrol_1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&final23_vcontrol_1_M->solverInfo,
                            ((final23_vcontrol_1_M->Timing.clockTickH0 + 1) *
        final23_vcontrol_1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&final23_vcontrol_1_M->solverInfo,
                            ((final23_vcontrol_1_M->Timing.clockTick0 + 1) *
        final23_vcontrol_1_M->Timing.stepSize0 +
        final23_vcontrol_1_M->Timing.clockTickH0 *
        final23_vcontrol_1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(final23_vcontrol_1_M)) {
    final23_vcontrol_1_M->Timing.t[0] = rtsiGetT
      (&final23_vcontrol_1_M->solverInfo);
  }

  {
    real_T *lastU;
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* FromWorkspace: '<Root>/From Workspace' */
      {
        real_T *pDataValues = (real_T *)
          final23_vcontrol_1_DW.FromWorkspace_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          final23_vcontrol_1_DW.FromWorkspace_PWORK.TimePtr;
        int_T currTimeIndex =
          final23_vcontrol_1_DW.FromWorkspace_IWORK.PrevIndex;
        real_T t = (((final23_vcontrol_1_M->Timing.clockTick1+
                      final23_vcontrol_1_M->Timing.clockTickH1* 4294967296.0)) *
                    0.001);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[1980]) {
          currTimeIndex = 1979;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        final23_vcontrol_1_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              final23_vcontrol_1_B.FromWorkspace = pDataValues[currTimeIndex];
            } else {
              final23_vcontrol_1_B.FromWorkspace = pDataValues[currTimeIndex + 1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex = currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            final23_vcontrol_1_B.FromWorkspace = (real_T) rtInterpolate(d1, d2,
              f1, f2);
            pDataValues += 1981;
          }
        }
      }
    }

    /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
    Quad_Encoder_sfn_Outputs_wrapper(&final23_vcontrol_1_B.QuadEncoder2axis_o1,
      &final23_vcontrol_1_B.QuadEncoder2axis_o2,
      &final23_vcontrol_1_DW.QuadEncoder2axis_DSTATE,
      &final23_vcontrol_1_P.QuadEncoder2axis_P1, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P2, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P3, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P4, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P5, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P6, 1);

    /* Gain: '<Root>/Encoder Gain1' */
    final23_vcontrol_1_B.EncoderGain1 = (int64_T)
      final23_vcontrol_1_P.EncoderGain1_Gain *
      final23_vcontrol_1_B.QuadEncoder2axis_o1;
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* Delay: '<S5>/Delay' */
      final23_vcontrol_1_B.Delay = final23_vcontrol_1_DW.Delay_DSTATE;
    }

    /* Gain: '<S5>/Gain' incorporates:
     *  Delay: '<S5>/Delay'
     *  Gain: '<Root>/Encoder Gain1'
     *  Sum: '<S5>/Sum3'
     */
    final23_vcontrol_1_B.u = (uint64_T)final23_vcontrol_1_P.Gain_Gain;
    final23_vcontrol_1_B.u1 = (uint64_T)(final23_vcontrol_1_B.EncoderGain1 -
      final23_vcontrol_1_B.Delay);
    sMultiWordMul(&final23_vcontrol_1_B.u, 1, &final23_vcontrol_1_B.u1, 1,
                  &final23_vcontrol_1_B.r.chunks[0U], 2);

    /* DataTypeConversion: '<S5>/Data Type Conversion' */
    rtb_DataTypeConversion = sMultiWord2Double(&final23_vcontrol_1_B.r.chunks[0U],
      2, 0) * 4.0389678347315804E-28;
    final23_vcontrol__MovingAverage(rtb_DataTypeConversion,
      &final23_vcontrol_1_B.MovingAverage, &final23_vcontrol_1_DW.MovingAverage);

    /* Sum: '<Root>/Sum1' */
    final23_vcontrol_1_B.Sum1 = final23_vcontrol_1_B.FromWorkspace -
      final23_vcontrol_1_B.MovingAverage.MovingAverage;

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Derivative: '<S4>/Derivative'
     */
    final23_vcontrol_1_B.Sum_d = final23_vcontrol_1_M->Timing.t[0];
    if ((final23_vcontrol_1_DW.TimeStampA >= final23_vcontrol_1_B.Sum_d) &&
        (final23_vcontrol_1_DW.TimeStampB >= final23_vcontrol_1_B.Sum_d)) {
      final23_vcontrol_1_B.Switch = 0.0;
    } else {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampA;
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA;
      if (final23_vcontrol_1_DW.TimeStampA < final23_vcontrol_1_DW.TimeStampB) {
        if (final23_vcontrol_1_DW.TimeStampB < final23_vcontrol_1_B.Sum_d) {
          final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampB;
          lastU = &final23_vcontrol_1_DW.LastUAtTimeB;
        }
      } else if (final23_vcontrol_1_DW.TimeStampA >= final23_vcontrol_1_B.Sum_d)
      {
        final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampB;
        lastU = &final23_vcontrol_1_DW.LastUAtTimeB;
      }

      final23_vcontrol_1_B.Switch = (final23_vcontrol_1_B.Sum1 - *lastU) /
        (final23_vcontrol_1_B.Sum_d - final23_vcontrol_1_B.Switch);
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* Sum: '<S3>/Sum' incorporates:
     *  Gain: '<S3>/D Gain'
     *  Gain: '<S3>/I Gain'
     *  Gain: '<S3>/P Gain'
     *  Integrator: '<S3>/Integrator'
     */
    final23_vcontrol_1_B.Sum = (final23_vcontrol_1_P.PGain_Gain *
      final23_vcontrol_1_B.Sum1 + final23_vcontrol_1_P.IGain_Gain *
      final23_vcontrol_1_X.Integrator_CSTATE) + final23_vcontrol_1_P.DGain_Gain *
      final23_vcontrol_1_B.Switch;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    if (final23_vcontrol_1_B.Sum > final23_vcontrol_1_P.Switch1_Threshold) {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_B.Sum;
    } else {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_P.Constant_Value;
    }

    /* End of Switch: '<S1>/Switch1' */

    /* Gain: '<S1>/GPIO19 Gain' */
    final23_vcontrol_1_B.Switch *= final23_vcontrol_1_P.GPIO19Gain_Gain;

    /* MATLABSystem: '<Root>/PWM' */
    if (!(final23_vcontrol_1_B.Switch < 1.0)) {
      final23_vcontrol_1_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_1_B.Switch > 0.0)) {
      final23_vcontrol_1_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_1_DW.obj_g.PinNumber,
      final23_vcontrol_1_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM' */

    /* Switch: '<S1>/Switch' incorporates:
     *  Abs: '<S1>/Abs'
     *  Constant: '<S1>/Constant'
     */
    if (final23_vcontrol_1_B.Sum > final23_vcontrol_1_P.Switch_Threshold) {
      final23_vcontrol_1_B.Sum = final23_vcontrol_1_P.Constant_Value;
    } else {
      final23_vcontrol_1_B.Sum = fabs(final23_vcontrol_1_B.Sum);
    }

    /* End of Switch: '<S1>/Switch' */

    /* Gain: '<S1>/GPIO26 Gain' */
    final23_vcontrol_1_B.Switch = final23_vcontrol_1_P.GPIO26Gain_Gain *
      final23_vcontrol_1_B.Sum;

    /* MATLABSystem: '<Root>/PWM1' */
    if (!(final23_vcontrol_1_B.Switch < 1.0)) {
      final23_vcontrol_1_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_1_B.Switch > 0.0)) {
      final23_vcontrol_1_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_1_DW.obj_e.PinNumber,
      final23_vcontrol_1_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM1' */
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* Delay: '<S6>/Delay' */
      final23_vcontrol_1_B.Delay_j = final23_vcontrol_1_DW.Delay_DSTATE_e;
    }

    /* Gain: '<Root>/Encoder Gain2' */
    final23_vcontrol_1_B.EncoderGain2 = (int64_T)
      final23_vcontrol_1_P.EncoderGain2_Gain *
      final23_vcontrol_1_B.QuadEncoder2axis_o2;

    /* Gain: '<S6>/Gain' incorporates:
     *  Delay: '<S6>/Delay'
     *  Gain: '<Root>/Encoder Gain2'
     *  Sum: '<S6>/Sum3'
     */
    final23_vcontrol_1_B.u = (uint64_T)final23_vcontrol_1_P.Gain_Gain_a;
    final23_vcontrol_1_B.u1 = (uint64_T)(final23_vcontrol_1_B.EncoderGain2 -
      final23_vcontrol_1_B.Delay_j);
    sMultiWordMul(&final23_vcontrol_1_B.u, 1, &final23_vcontrol_1_B.u1, 1,
                  &final23_vcontrol_1_B.r1.chunks[0U], 2);

    /* DataTypeConversion: '<S6>/Data Type Conversion' */
    rtb_DataTypeConversion_a = sMultiWord2Double
      (&final23_vcontrol_1_B.r1.chunks[0U], 2, 0) * 4.0389678347315804E-28;
    final23_vcontrol__MovingAverage(rtb_DataTypeConversion_a,
      &final23_vcontrol_1_B.MovingAverage_p,
      &final23_vcontrol_1_DW.MovingAverage_p);
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* FromWorkspace: '<Root>/From Workspace1' */
      {
        real_T *pDataValues = (real_T *)
          final23_vcontrol_1_DW.FromWorkspace1_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          final23_vcontrol_1_DW.FromWorkspace1_PWORK.TimePtr;
        int_T currTimeIndex =
          final23_vcontrol_1_DW.FromWorkspace1_IWORK.PrevIndex;
        real_T t = (((final23_vcontrol_1_M->Timing.clockTick1+
                      final23_vcontrol_1_M->Timing.clockTickH1* 4294967296.0)) *
                    0.001);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[1980]) {
          currTimeIndex = 1979;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        final23_vcontrol_1_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              final23_vcontrol_1_B.FromWorkspace1 = pDataValues[currTimeIndex];
            } else {
              final23_vcontrol_1_B.FromWorkspace1 = pDataValues[currTimeIndex +
                1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex = currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            final23_vcontrol_1_B.FromWorkspace1 = (real_T) rtInterpolate(d1, d2,
              f1, f2);
            pDataValues += 1981;
          }
        }
      }
    }

    /* Sum: '<Root>/Sum2' */
    final23_vcontrol_1_B.Sum2 = final23_vcontrol_1_B.FromWorkspace1 -
      final23_vcontrol_1_B.MovingAverage_p.MovingAverage;

    /* Derivative: '<S4>/Derivative' */
    if ((final23_vcontrol_1_DW.TimeStampA_a >= final23_vcontrol_1_B.Sum_d) &&
        (final23_vcontrol_1_DW.TimeStampB_o >= final23_vcontrol_1_B.Sum_d)) {
      final23_vcontrol_1_B.Switch = 0.0;
    } else {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampA_a;
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA_i;
      if (final23_vcontrol_1_DW.TimeStampA_a <
          final23_vcontrol_1_DW.TimeStampB_o) {
        if (final23_vcontrol_1_DW.TimeStampB_o < final23_vcontrol_1_B.Sum_d) {
          final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampB_o;
          lastU = &final23_vcontrol_1_DW.LastUAtTimeB_m;
        }
      } else if (final23_vcontrol_1_DW.TimeStampA_a >=
                 final23_vcontrol_1_B.Sum_d) {
        final23_vcontrol_1_B.Switch = final23_vcontrol_1_DW.TimeStampB_o;
        lastU = &final23_vcontrol_1_DW.LastUAtTimeB_m;
      }

      final23_vcontrol_1_B.Switch = (final23_vcontrol_1_B.Sum2 - *lastU) /
        (final23_vcontrol_1_B.Sum_d - final23_vcontrol_1_B.Switch);
    }

    /* Sum: '<S4>/Sum' incorporates:
     *  Gain: '<S4>/D Gain'
     *  Gain: '<S4>/I Gain'
     *  Gain: '<S4>/P Gain'
     *  Integrator: '<S4>/Integrator'
     */
    final23_vcontrol_1_B.Sum_d = (final23_vcontrol_1_P.PGain_Gain_i *
      final23_vcontrol_1_B.Sum2 + final23_vcontrol_1_P.IGain_Gain_j *
      final23_vcontrol_1_X.Integrator_CSTATE_l) +
      final23_vcontrol_1_P.DGain_Gain_h * final23_vcontrol_1_B.Switch;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Constant: '<S2>/Constant'
     */
    if (final23_vcontrol_1_B.Sum_d > final23_vcontrol_1_P.Switch1_Threshold_c) {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_B.Sum_d;
    } else {
      final23_vcontrol_1_B.Switch = final23_vcontrol_1_P.Constant_Value_e;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Gain: '<S2>/GPIO20 Gain' */
    final23_vcontrol_1_B.Switch *= final23_vcontrol_1_P.GPIO20Gain_Gain;

    /* MATLABSystem: '<Root>/PWM2' */
    if (!(final23_vcontrol_1_B.Switch < 1.0)) {
      final23_vcontrol_1_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_1_B.Switch > 0.0)) {
      final23_vcontrol_1_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_1_DW.obj_p.PinNumber,
      final23_vcontrol_1_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM2' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Abs: '<S2>/Abs'
     *  Constant: '<S2>/Constant'
     */
    if (final23_vcontrol_1_B.Sum_d > final23_vcontrol_1_P.Switch_Threshold_m) {
      final23_vcontrol_1_B.Sum_d = final23_vcontrol_1_P.Constant_Value_e;
    } else {
      final23_vcontrol_1_B.Sum_d = fabs(final23_vcontrol_1_B.Sum_d);
    }

    /* End of Switch: '<S2>/Switch' */

    /* Gain: '<S2>/GPIO21 Gain' */
    final23_vcontrol_1_B.Switch = final23_vcontrol_1_P.GPIO21Gain_Gain *
      final23_vcontrol_1_B.Sum_d;

    /* MATLABSystem: '<Root>/PWM3' */
    if (!(final23_vcontrol_1_B.Switch < 1.0)) {
      final23_vcontrol_1_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_1_B.Switch > 0.0)) {
      final23_vcontrol_1_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_1_DW.obj.PinNumber,
      final23_vcontrol_1_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM3' */
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
    }
  }

  if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
    real_T *lastU;

    /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Update_wrapper(&final23_vcontrol_1_B.QuadEncoder2axis_o1,
      &final23_vcontrol_1_B.QuadEncoder2axis_o2,
      &final23_vcontrol_1_DW.QuadEncoder2axis_DSTATE,
      &final23_vcontrol_1_P.QuadEncoder2axis_P1, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P2, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P3, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P4, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P5, 1,
      &final23_vcontrol_1_P.QuadEncoder2axis_P6, 1);
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* Update for Delay: '<S5>/Delay' incorporates:
       *  Gain: '<Root>/Encoder Gain1'
       */
      final23_vcontrol_1_DW.Delay_DSTATE = final23_vcontrol_1_B.EncoderGain1;
    }

    /* Update for Derivative: '<S3>/Derivative' */
    if (final23_vcontrol_1_DW.TimeStampA == (rtInf)) {
      final23_vcontrol_1_DW.TimeStampA = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA;
    } else if (final23_vcontrol_1_DW.TimeStampB == (rtInf)) {
      final23_vcontrol_1_DW.TimeStampB = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeB;
    } else if (final23_vcontrol_1_DW.TimeStampA <
               final23_vcontrol_1_DW.TimeStampB) {
      final23_vcontrol_1_DW.TimeStampA = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA;
    } else {
      final23_vcontrol_1_DW.TimeStampB = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeB;
    }

    *lastU = final23_vcontrol_1_B.Sum1;

    /* End of Update for Derivative: '<S3>/Derivative' */
    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
      /* Update for Delay: '<S6>/Delay' incorporates:
       *  Gain: '<Root>/Encoder Gain2'
       */
      final23_vcontrol_1_DW.Delay_DSTATE_e = final23_vcontrol_1_B.EncoderGain2;
    }

    /* Update for Derivative: '<S4>/Derivative' */
    if (final23_vcontrol_1_DW.TimeStampA_a == (rtInf)) {
      final23_vcontrol_1_DW.TimeStampA_a = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA_i;
    } else if (final23_vcontrol_1_DW.TimeStampB_o == (rtInf)) {
      final23_vcontrol_1_DW.TimeStampB_o = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeB_m;
    } else if (final23_vcontrol_1_DW.TimeStampA_a <
               final23_vcontrol_1_DW.TimeStampB_o) {
      final23_vcontrol_1_DW.TimeStampA_a = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeA_i;
    } else {
      final23_vcontrol_1_DW.TimeStampB_o = final23_vcontrol_1_M->Timing.t[0];
      lastU = &final23_vcontrol_1_DW.LastUAtTimeB_m;
    }

    *lastU = final23_vcontrol_1_B.Sum2;

    /* End of Update for Derivative: '<S4>/Derivative' */

    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, (real_T)final23_vcontrol_1_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {/* Sample time: [0.001s, 0.0s] */
      rtExtModeUpload(1, (real_T)(((final23_vcontrol_1_M->Timing.clockTick1+
        final23_vcontrol_1_M->Timing.clockTickH1* 4294967296.0)) * 0.001));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(final23_vcontrol_1_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(final23_vcontrol_1_M)!=-1) &&
          !((rtmGetTFinal(final23_vcontrol_1_M)-
             (((final23_vcontrol_1_M->Timing.clockTick1+
                final23_vcontrol_1_M->Timing.clockTickH1* 4294967296.0)) * 0.001))
            > (((final23_vcontrol_1_M->Timing.clockTick1+
                 final23_vcontrol_1_M->Timing.clockTickH1* 4294967296.0)) *
               0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(final23_vcontrol_1_M, "Simulation finished");
      }

      if (rtmGetStopRequested(final23_vcontrol_1_M)) {
        rtmSetErrorStatus(final23_vcontrol_1_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&final23_vcontrol_1_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++final23_vcontrol_1_M->Timing.clockTick0)) {
      ++final23_vcontrol_1_M->Timing.clockTickH0;
    }

    final23_vcontrol_1_M->Timing.t[0] = rtsiGetSolverStopTime
      (&final23_vcontrol_1_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      final23_vcontrol_1_M->Timing.clockTick1++;
      if (!final23_vcontrol_1_M->Timing.clockTick1) {
        final23_vcontrol_1_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void final23_vcontrol_1_derivatives(void)
{
  XDot_final23_vcontrol_1_T *_rtXdot;
  _rtXdot = ((XDot_final23_vcontrol_1_T *) final23_vcontrol_1_M->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = final23_vcontrol_1_B.Sum1;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_l = final23_vcontrol_1_B.Sum2;
}

/* Model initialize function */
void final23_vcontrol_1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)final23_vcontrol_1_M, 0,
                sizeof(RT_MODEL_final23_vcontrol_1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&final23_vcontrol_1_M->solverInfo,
                          &final23_vcontrol_1_M->Timing.simTimeStep);
    rtsiSetTPtr(&final23_vcontrol_1_M->solverInfo, &rtmGetTPtr
                (final23_vcontrol_1_M));
    rtsiSetStepSizePtr(&final23_vcontrol_1_M->solverInfo,
                       &final23_vcontrol_1_M->Timing.stepSize0);
    rtsiSetdXPtr(&final23_vcontrol_1_M->solverInfo,
                 &final23_vcontrol_1_M->derivs);
    rtsiSetContStatesPtr(&final23_vcontrol_1_M->solverInfo, (real_T **)
                         &final23_vcontrol_1_M->contStates);
    rtsiSetNumContStatesPtr(&final23_vcontrol_1_M->solverInfo,
      &final23_vcontrol_1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&final23_vcontrol_1_M->solverInfo,
      &final23_vcontrol_1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&final23_vcontrol_1_M->solverInfo,
      &final23_vcontrol_1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&final23_vcontrol_1_M->solverInfo,
      &final23_vcontrol_1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&final23_vcontrol_1_M->solverInfo, (&rtmGetErrorStatus
      (final23_vcontrol_1_M)));
    rtsiSetRTModelPtr(&final23_vcontrol_1_M->solverInfo, final23_vcontrol_1_M);
  }

  rtsiSetSimTimeStep(&final23_vcontrol_1_M->solverInfo, MAJOR_TIME_STEP);
  final23_vcontrol_1_M->intgData.y = final23_vcontrol_1_M->odeY;
  final23_vcontrol_1_M->intgData.f[0] = final23_vcontrol_1_M->odeF[0];
  final23_vcontrol_1_M->intgData.f[1] = final23_vcontrol_1_M->odeF[1];
  final23_vcontrol_1_M->intgData.f[2] = final23_vcontrol_1_M->odeF[2];
  final23_vcontrol_1_M->contStates = ((X_final23_vcontrol_1_T *)
    &final23_vcontrol_1_X);
  rtsiSetSolverData(&final23_vcontrol_1_M->solverInfo, (void *)
                    &final23_vcontrol_1_M->intgData);
  rtsiSetSolverName(&final23_vcontrol_1_M->solverInfo,"ode3");
  rtmSetTPtr(final23_vcontrol_1_M, &final23_vcontrol_1_M->Timing.tArray[0]);
  rtmSetTFinal(final23_vcontrol_1_M, 3.0);
  final23_vcontrol_1_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  final23_vcontrol_1_M->Sizes.checksums[0] = (3466295076U);
  final23_vcontrol_1_M->Sizes.checksums[1] = (2530662337U);
  final23_vcontrol_1_M->Sizes.checksums[2] = (72053245U);
  final23_vcontrol_1_M->Sizes.checksums[3] = (313262130U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[9];
    final23_vcontrol_1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(final23_vcontrol_1_M->extModeInfo,
      &final23_vcontrol_1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(final23_vcontrol_1_M->extModeInfo,
                        final23_vcontrol_1_M->Sizes.checksums);
    rteiSetTPtr(final23_vcontrol_1_M->extModeInfo, rtmGetTPtr
                (final23_vcontrol_1_M));
  }

  /* block I/O */
  (void) memset(((void *) &final23_vcontrol_1_B), 0,
                sizeof(B_final23_vcontrol_1_T));

  {
    final23_vcontrol_1_B.EncoderGain1 = (0LL);
    final23_vcontrol_1_B.Delay = (0LL);
    final23_vcontrol_1_B.EncoderGain2 = (0LL);
    final23_vcontrol_1_B.Delay_j = (0LL);
  }

  /* states (continuous) */
  {
    (void) memset((void *)&final23_vcontrol_1_X, 0,
                  sizeof(X_final23_vcontrol_1_T));
  }

  /* states (dwork) */
  (void) memset((void *)&final23_vcontrol_1_DW, 0,
                sizeof(DW_final23_vcontrol_1_T));

  {
    int32_T ret;
    static const char_T tmp[45] =
      "Unable to configure pin %u for PWM output.\\n";

    /* Start for FromWorkspace: '<Root>/From Workspace' */
    {
      static real_T pTimeValues0[] = { 0.0, 0.001, 0.002, 0.003, 0.004, 0.005,
        0.006, 0.007, 0.008, 0.0090000000000000011, 0.01, 0.011, 0.012,
        0.013000000000000001, 0.014, 0.015, 0.016, 0.017, 0.018000000000000002,
        0.019, 0.02, 0.021, 0.022, 0.023, 0.024, 0.025, 0.026000000000000002,
        0.027, 0.028, 0.029, 0.03, 0.031, 0.032, 0.033, 0.034, 0.035,
        0.036000000000000004, 0.037, 0.038, 0.039, 0.04, 0.041, 0.042, 0.043,
        0.044, 0.045, 0.046, 0.047, 0.048, 0.049, 0.05, 0.051000000000000004,
        0.052000000000000005, 0.053, 0.054, 0.055, 0.056, 0.057, 0.058,
        0.059000000000000004, 0.06, 0.061, 0.062, 0.063, 0.064, 0.065, 0.066,
        0.067, 0.068, 0.069, 0.07, 0.071000000000000008, 0.072000000000000008,
        0.073, 0.074, 0.075, 0.076, 0.077, 0.078, 0.079, 0.08, 0.081, 0.082,
        0.083, 0.084, 0.085, 0.086, 0.087000000000000008, 0.088, 0.089, 0.09,
        0.091, 0.092, 0.093, 0.094, 0.095, 0.096, 0.097, 0.098, 0.099, 0.1,
        0.101, 0.10200000000000001, 0.10300000000000001, 0.10400000000000001,
        0.105, 0.106, 0.107, 0.108, 0.109, 0.11, 0.111, 0.112, 0.113, 0.114,
        0.115, 0.116, 0.117, 0.11800000000000001, 0.11900000000000001, 0.12,
        0.121, 0.122, 0.123, 0.124, 0.125, 0.126, 0.127, 0.128, 0.129, 0.13,
        0.131, 0.132, 0.133, 0.134, 0.135, 0.136, 0.137, 0.138, 0.139, 0.14,
        0.141, 0.14200000000000002, 0.14300000000000002, 0.14400000000000002,
        0.145, 0.146, 0.147, 0.148, 0.149, 0.15, 0.151, 0.152, 0.153, 0.154,
        0.155, 0.156, 0.157, 0.158, 0.159, 0.16, 0.161, 0.162, 0.163, 0.164,
        0.165, 0.166, 0.167, 0.168, 0.169, 0.17, 0.171, 0.172,
        0.17300000000000001, 0.17400000000000002, 0.17500000000000002, 0.176,
        0.177, 0.178, 0.179, 0.18, 0.181, 0.182, 0.183, 0.184, 0.185, 0.186,
        0.187, 0.188, 0.189, 0.19, 0.191, 0.192, 0.193, 0.194, 0.195, 0.196,
        0.197, 0.198, 0.199, 0.2, 0.201, 0.202, 0.203, 0.20400000000000001,
        0.20500000000000002, 0.20600000000000002, 0.20700000000000002,
        0.20800000000000002, 0.209, 0.21, 0.211, 0.212, 0.213, 0.214, 0.215,
        0.216, 0.217, 0.218, 0.219, 0.22, 0.221, 0.222, 0.223, 0.224, 0.225,
        0.226, 0.227, 0.228, 0.229, 0.23, 0.231, 0.232, 0.233, 0.234,
        0.23500000000000004, 0.23600000000000002, 0.23700000000000002,
        0.23800000000000002, 0.23900000000000002, 0.24, 0.241, 0.242, 0.243,
        0.244, 0.245, 0.246, 0.247, 0.248, 0.249, 0.25, 0.251, 0.252, 0.253,
        0.254, 0.255, 0.256, 0.257, 0.258, 0.259, 0.26, 0.261, 0.262, 0.263,
        0.264, 0.265, 0.266, 0.267, 0.268, 0.269, 0.27, 0.271, 0.272, 0.273,
        0.274, 0.275, 0.276, 0.277, 0.278, 0.279, 0.28, 0.281, 0.282,
        0.28300000000000003, 0.28400000000000003, 0.28500000000000003,
        0.28600000000000003, 0.28700000000000003, 0.28800000000000003, 0.289,
        0.29, 0.291, 0.292, 0.293, 0.294, 0.295, 0.296, 0.297, 0.298, 0.299, 0.3,
        0.301, 0.302, 0.303, 0.304, 0.305, 0.306, 0.307, 0.308, 0.309, 0.31,
        0.311, 0.312, 0.313, 0.314, 0.315, 0.316, 0.317, 0.318, 0.319, 0.32,
        0.321, 0.322, 0.323, 0.324, 0.325, 0.326, 0.327, 0.328, 0.329, 0.33,
        0.331, 0.332, 0.333, 0.334, 0.335, 0.336, 0.337, 0.338, 0.339, 0.34,
        0.341, 0.342, 0.343, 0.344, 0.34500000000000008, 0.34600000000000003,
        0.34700000000000003, 0.34800000000000003, 0.34900000000000003,
        0.35000000000000003, 0.35100000000000003, 0.352, 0.353, 0.354, 0.355,
        0.356, 0.357, 0.358, 0.359, 0.36, 0.361, 0.362, 0.363, 0.364, 0.365,
        0.366, 0.367, 0.368, 0.369, 0.37, 0.371, 0.372, 0.373, 0.374, 0.375,
        0.376, 0.377, 0.378, 0.379, 0.38, 0.381, 0.382, 0.383, 0.384, 0.385,
        0.386, 0.387, 0.388, 0.389, 0.39, 0.391, 0.392, 0.393, 0.394, 0.395,
        0.396, 0.397, 0.398, 0.399, 0.4, 0.401, 0.402, 0.403, 0.404, 0.405,
        0.406, 0.407, 0.40800000000000003, 0.40900000000000003,
        0.41000000000000003, 0.41100000000000003, 0.41200000000000003,
        0.41300000000000003, 0.41400000000000003, 0.41500000000000004,
        0.41600000000000004, 0.417, 0.418, 0.419, 0.42, 0.421, 0.422, 0.423,
        0.424, 0.425, 0.426, 0.427, 0.428, 0.429, 0.43, 0.431, 0.432, 0.433,
        0.434, 0.435, 0.436, 0.437, 0.438, 0.439, 0.44, 0.441, 0.442, 0.443,
        0.444, 0.445, 0.446, 0.447, 0.448, 0.449, 0.45, 0.451, 0.452, 0.453,
        0.454, 0.455, 0.456, 0.457, 0.458, 0.459, 0.46, 0.461, 0.462, 0.463,
        0.464, 0.465, 0.466, 0.467, 0.468, 0.469, 0.47000000000000008,
        0.47100000000000003, 0.47200000000000003, 0.47300000000000003,
        0.47400000000000003, 0.47500000000000003, 0.47600000000000003,
        0.47700000000000004, 0.47800000000000004, 0.47900000000000004, 0.48,
        0.481, 0.482, 0.483, 0.484, 0.485, 0.486, 0.487, 0.488, 0.489, 0.49,
        0.491, 0.492, 0.493, 0.494, 0.495, 0.496, 0.497, 0.498, 0.499, 0.5,
        0.501, 0.502, 0.503, 0.504, 0.505, 0.506, 0.507, 0.508, 0.509, 0.51,
        0.511, 0.512, 0.513, 0.514, 0.515, 0.516, 0.517, 0.518, 0.519, 0.52,
        0.521, 0.522, 0.523, 0.524, 0.525, 0.526, 0.527, 0.528, 0.529, 0.53,
        0.531, 0.532, 0.533, 0.534, 0.535, 0.536, 0.537, 0.538, 0.539, 0.54,
        0.541, 0.542, 0.543, 0.544, 0.545, 0.546, 0.547, 0.548, 0.549, 0.55,
        0.551, 0.552, 0.553, 0.554, 0.555, 0.556, 0.557, 0.558, 0.559, 0.56,
        0.561, 0.562, 0.563, 0.564, 0.56500000000000017, 0.56600000000000006,
        0.56700000000000006, 0.56800000000000006, 0.56900000000000006,
        0.57000000000000006, 0.57100000000000006, 0.57200000000000006,
        0.57300000000000006, 0.57400000000000007, 0.57500000000000007,
        0.57600000000000007, 0.577, 0.578, 0.579, 0.58, 0.581, 0.582, 0.583,
        0.584, 0.585, 0.586, 0.587, 0.588, 0.589, 0.59, 0.591, 0.592, 0.593,
        0.594, 0.595, 0.596, 0.597, 0.598, 0.599, 0.6, 0.601, 0.602, 0.603,
        0.604, 0.605, 0.606, 0.607, 0.608, 0.609, 0.61, 0.611, 0.612, 0.613,
        0.614, 0.615, 0.616, 0.617, 0.618, 0.619, 0.62, 0.621, 0.622, 0.623,
        0.624, 0.625, 0.626, 0.627, 0.628, 0.629, 0.63, 0.631, 0.632, 0.633,
        0.634, 0.635, 0.636, 0.637, 0.638, 0.639, 0.64, 0.641, 0.642, 0.643,
        0.644, 0.645, 0.646, 0.647, 0.648, 0.649, 0.65, 0.651, 0.652, 0.653,
        0.654, 0.655, 0.656, 0.657, 0.658, 0.659, 0.66, 0.661, 0.662, 0.663,
        0.664, 0.665, 0.666, 0.667, 0.668, 0.669, 0.67, 0.671, 0.672, 0.673,
        0.674, 0.675, 0.676, 0.677, 0.678, 0.679, 0.68, 0.681, 0.682, 0.683,
        0.684, 0.685, 0.686, 0.687, 0.688, 0.689, 0.69000000000000017,
        0.69100000000000006, 0.69200000000000006, 0.69300000000000006,
        0.69400000000000006, 0.69500000000000006, 0.69600000000000006,
        0.69700000000000006, 0.69800000000000006, 0.69900000000000007,
        0.70000000000000007, 0.70100000000000007, 0.70200000000000007,
        0.70300000000000007, 0.704, 0.705, 0.706, 0.707, 0.708, 0.709, 0.71,
        0.711, 0.712, 0.713, 0.714, 0.715, 0.716, 0.717, 0.718, 0.719, 0.72,
        0.721, 0.722, 0.723, 0.724, 0.725, 0.726, 0.727, 0.728, 0.729, 0.73,
        0.731, 0.732, 0.733, 0.734, 0.735, 0.736, 0.737, 0.738, 0.739, 0.74,
        0.741, 0.742, 0.743, 0.744, 0.745, 0.746, 0.747, 0.748, 0.749, 0.75,
        0.751, 0.752, 0.753, 0.754, 0.755, 0.756, 0.757, 0.758, 0.759, 0.76,
        0.761, 0.762, 0.763, 0.764, 0.765, 0.766, 0.767, 0.768, 0.769, 0.77,
        0.771, 0.772, 0.773, 0.774, 0.775, 0.776, 0.777, 0.778, 0.779, 0.78,
        0.781, 0.782, 0.783, 0.784, 0.785, 0.786, 0.787, 0.788, 0.789, 0.79,
        0.791, 0.792, 0.793, 0.794, 0.795, 0.796, 0.797, 0.798, 0.799, 0.8,
        0.801, 0.802, 0.803, 0.804, 0.805, 0.806, 0.807, 0.808, 0.809, 0.81,
        0.811, 0.812, 0.813, 0.814, 0.81500000000000017, 0.81600000000000006,
        0.81700000000000006, 0.81800000000000006, 0.81900000000000006,
        0.82000000000000006, 0.82100000000000006, 0.82200000000000006,
        0.82300000000000006, 0.82400000000000007, 0.82500000000000007,
        0.82600000000000007, 0.82700000000000007, 0.82800000000000007,
        0.82900000000000007, 0.83000000000000007, 0.83100000000000007,
        0.83200000000000007, 0.833, 0.834, 0.835, 0.836, 0.837, 0.838, 0.839,
        0.84, 0.841, 0.842, 0.843, 0.844, 0.845, 0.846, 0.847, 0.848, 0.849,
        0.85, 0.851, 0.852, 0.853, 0.854, 0.855, 0.856, 0.857, 0.858, 0.859,
        0.86, 0.861, 0.862, 0.863, 0.864, 0.865, 0.866, 0.867, 0.868, 0.869,
        0.87, 0.871, 0.872, 0.873, 0.874, 0.875, 0.876, 0.877, 0.878, 0.879,
        0.88, 0.881, 0.882, 0.883, 0.884, 0.885, 0.886, 0.887, 0.888, 0.889,
        0.89, 0.891, 0.892, 0.893, 0.894, 0.895, 0.896, 0.897, 0.898, 0.899, 0.9,
        0.901, 0.902, 0.903, 0.904, 0.905, 0.906, 0.907, 0.908, 0.909, 0.91,
        0.911, 0.912, 0.913, 0.914, 0.915, 0.916, 0.917, 0.918, 0.919, 0.92,
        0.921, 0.922, 0.923, 0.924, 0.925, 0.926, 0.927, 0.928, 0.929, 0.93,
        0.931, 0.932, 0.933, 0.934, 0.935, 0.936, 0.937, 0.938, 0.939,
        0.94000000000000017, 0.94100000000000006, 0.94200000000000006,
        0.94300000000000006, 0.94400000000000006, 0.94500000000000006,
        0.94600000000000006, 0.94700000000000006, 0.94800000000000006,
        0.94900000000000007, 0.95000000000000007, 0.95100000000000007,
        0.95200000000000007, 0.95300000000000007, 0.95400000000000007,
        0.95500000000000007, 0.95600000000000007, 0.95700000000000007,
        0.95800000000000007, 0.95900000000000007, 0.96, 0.961, 0.962, 0.963,
        0.964, 0.965, 0.966, 0.967, 0.968, 0.969, 0.97, 0.971, 0.972, 0.973,
        0.974, 0.975, 0.976, 0.977, 0.978, 0.979, 0.98, 0.981, 0.982, 0.983,
        0.984, 0.985, 0.986, 0.987, 0.988, 0.989, 0.99, 0.991, 0.992, 0.993,
        0.994, 0.995, 0.996, 0.997, 0.998, 0.999, 1.0, 1.001, 1.002,
        1.0030000000000001, 1.004, 1.005, 1.006, 1.0070000000000001, 1.008,
        1.009, 1.01, 1.0110000000000001, 1.012, 1.013, 1.014, 1.0150000000000001,
        1.016, 1.017, 1.018, 1.0190000000000001, 1.02, 1.021, 1.0219999999999998,
        1.023, 1.024, 1.025, 1.0259999999999998, 1.027, 1.028, 1.029,
        1.0299999999999998, 1.031, 1.032, 1.033, 1.0339999999999998, 1.035,
        1.036, 1.037, 1.0379999999999998, 1.039, 1.04, 1.041, 1.0419999999999998,
        1.043, 1.044, 1.045, 1.0459999999999998, 1.047, 1.048, 1.049,
        1.0499999999999998, 1.051, 1.052, 1.053, 1.0539999999999998, 1.055,
        1.056, 1.057, 1.0579999999999998, 1.059, 1.06, 1.061, 1.0619999999999998,
        1.063, 1.064, 1.065, 1.0659999999999998, 1.067, 1.068, 1.069,
        1.0699999999999998, 1.071, 1.072, 1.073, 1.0739999999999998, 1.075,
        1.076, 1.077, 1.0779999999999998, 1.079, 1.08, 1.081, 1.0819999999999999,
        1.083, 1.084, 1.085, 1.0859999999999999, 1.087, 1.088, 1.089,
        1.0899999999999999, 1.091, 1.092, 1.093, 1.0939999999999999, 1.095,
        1.096, 1.097, 1.0979999999999999, 1.099, 1.1, 1.101, 1.1019999999999999,
        1.103, 1.104, 1.105, 1.1059999999999999, 1.107, 1.108, 1.109,
        1.1099999999999999, 1.111, 1.112, 1.113, 1.1139999999999999, 1.115,
        1.116, 1.117, 1.1179999999999999, 1.119, 1.12, 1.121, 1.122, 1.123,
        1.124, 1.125, 1.126, 1.127, 1.128, 1.129, 1.13, 1.131,
        1.1320000000000001, 1.133, 1.134, 1.135, 1.1360000000000001, 1.137,
        1.138, 1.139, 1.1400000000000001, 1.141, 1.142, 1.143,
        1.1440000000000001, 1.145, 1.146, 1.147, 1.148, 1.149, 1.15,
        1.1509999999999998, 1.152, 1.153, 1.154, 1.1549999999999998, 1.156,
        1.157, 1.158, 1.1589999999999998, 1.16, 1.161, 1.162, 1.1629999999999998,
        1.164, 1.165, 1.166, 1.1669999999999998, 1.168, 1.169, 1.17,
        1.1709999999999998, 1.172, 1.173, 1.174, 1.1749999999999998, 1.176,
        1.177, 1.178, 1.1789999999999998, 1.18, 1.181, 1.182, 1.1829999999999998,
        1.184, 1.185, 1.186, 1.1869999999999998, 1.188, 1.189, 1.19,
        1.1909999999999998, 1.192, 1.193, 1.194, 1.1949999999999998, 1.196,
        1.197, 1.198, 1.1989999999999998, 1.2, 1.201, 1.202, 1.2029999999999998,
        1.204, 1.205, 1.206, 1.2069999999999999, 1.208, 1.209, 1.21,
        1.2109999999999999, 1.212, 1.213, 1.214, 1.2149999999999999, 1.216,
        1.217, 1.218, 1.2189999999999999, 1.22, 1.221, 1.222, 1.2229999999999999,
        1.224, 1.225, 1.226, 1.2269999999999999, 1.228, 1.229, 1.23,
        1.2309999999999999, 1.232, 1.233, 1.234, 1.2349999999999999, 1.236,
        1.237, 1.238, 1.2389999999999999, 1.24, 1.241, 1.242, 1.2429999999999999,
        1.244, 1.245, 1.246, 1.247, 1.248, 1.249, 1.25, 1.251, 1.252, 1.253,
        1.254, 1.255, 1.256, 1.2570000000000001, 1.258, 1.259, 1.26,
        1.2610000000000001, 1.262, 1.263, 1.264, 1.2650000000000001, 1.266,
        1.267, 1.268, 1.2690000000000001, 1.27, 1.271, 1.272, 1.2730000000000001,
        1.274, 1.275, 1.276, 1.277, 1.278, 1.279, 1.2799999999999998, 1.281,
        1.282, 1.283, 1.2839999999999998, 1.285, 1.286, 1.287,
        1.2879999999999998, 1.289, 1.29, 1.291, 1.2919999999999998, 1.293, 1.294,
        1.295, 1.2959999999999998, 1.297, 1.298, 1.299, 1.2999999999999998,
        1.301, 1.302, 1.303, 1.3039999999999998, 1.305, 1.306, 1.307,
        1.3079999999999998, 1.309, 1.31, 1.311, 1.3119999999999998, 1.313, 1.314,
        1.315, 1.3159999999999998, 1.317, 1.318, 1.319, 1.3199999999999998,
        1.321, 1.322, 1.323, 1.3239999999999998, 1.325, 1.326, 1.327,
        1.3279999999999998, 1.329, 1.33, 1.331, 1.3319999999999999, 1.333, 1.334,
        1.335, 1.3359999999999999, 1.337, 1.338, 1.339, 1.3399999999999999,
        1.341, 1.342, 1.343, 1.3439999999999999, 1.345, 1.346, 1.347,
        1.3479999999999999, 1.349, 1.35, 1.351, 1.3519999999999999, 1.353, 1.354,
        1.355, 1.3559999999999999, 1.357, 1.358, 1.359, 1.3599999999999999,
        1.361, 1.362, 1.363, 1.3639999999999999, 1.365, 1.366, 1.367,
        1.3679999999999999, 1.369, 1.37, 1.371, 1.372, 1.373, 1.374, 1.375,
        1.376, 1.377, 1.378, 1.379, 1.38, 1.381, 1.3820000000000001, 1.383,
        1.384, 1.385, 1.3860000000000001, 1.387, 1.388, 1.389,
        1.3900000000000001, 1.391, 1.392, 1.393, 1.3940000000000001, 1.395,
        1.396, 1.397, 1.3980000000000001, 1.399, 1.4, 1.401, 1.4020000000000001,
        1.403, 1.404, 1.4049999999999998, 1.406, 1.407, 1.408,
        1.4089999999999998, 1.41, 1.411, 1.412, 1.4129999999999998, 1.414, 1.415,
        1.416, 1.4169999999999998, 1.418, 1.419, 1.42, 1.4209999999999998, 1.422,
        1.423, 1.424, 1.4249999999999998, 1.426, 1.427, 1.428,
        1.4289999999999998, 1.43, 1.431, 1.432, 1.4329999999999998, 1.434, 1.435,
        1.436, 1.4369999999999998, 1.438, 1.439, 1.44, 1.4409999999999998, 1.442,
        1.443, 1.444, 1.4449999999999998, 1.446, 1.447, 1.448,
        1.4489999999999998, 1.45, 1.451, 1.452, 1.4529999999999998, 1.454, 1.455,
        1.456, 1.4569999999999999, 1.458, 1.459, 1.46, 1.4609999999999999, 1.462,
        1.463, 1.464, 1.4649999999999999, 1.466, 1.467, 1.468,
        1.4689999999999999, 1.47, 1.471, 1.472, 1.4729999999999999, 1.474, 1.475,
        1.476, 1.4769999999999999, 1.478, 1.479, 1.48, 1.4809999999999999, 1.482,
        1.483, 1.484, 1.4849999999999999, 1.486, 1.487, 1.488,
        1.4889999999999999, 1.49, 1.491, 1.492, 1.4929999999999999, 1.494, 1.495,
        1.496, 1.497, 1.498, 1.499, 1.5, 1.501, 1.502, 1.503, 1.504, 1.505,
        1.506, 1.507, 1.508, 1.509, 1.51, 1.511, 1.512, 1.513, 1.514, 1.515,
        1.516, 1.517, 1.518, 1.519, 1.52, 1.521, 1.522, 1.523, 1.524, 1.525,
        1.526, 1.527, 1.528, 1.529, 1.53, 1.531, 1.532, 1.533, 1.534, 1.535,
        1.536, 1.537, 1.538, 1.539, 1.54, 1.541, 1.542, 1.543, 1.544, 1.545,
        1.546, 1.547, 1.548, 1.549, 1.55, 1.551, 1.552, 1.553, 1.554, 1.555,
        1.556, 1.557, 1.558, 1.559, 1.56, 1.561, 1.562, 1.563, 1.564, 1.565,
        1.5659999999999998, 1.567, 1.568, 1.569, 1.5699999999999998, 1.571,
        1.572, 1.573, 1.5739999999999998, 1.575, 1.576, 1.577,
        1.5779999999999998, 1.579, 1.58, 1.581, 1.5819999999999999, 1.583, 1.584,
        1.585, 1.5859999999999999, 1.587, 1.588, 1.589, 1.5899999999999999,
        1.591, 1.592, 1.593, 1.5939999999999999, 1.595, 1.596, 1.597,
        1.5979999999999999, 1.599, 1.6, 1.601, 1.6019999999999999, 1.603, 1.604,
        1.605, 1.6059999999999999, 1.607, 1.608, 1.609, 1.6099999999999999,
        1.611, 1.612, 1.613, 1.6139999999999999, 1.615, 1.616, 1.617,
        1.6179999999999999, 1.619, 1.62, 1.621, 1.622, 1.623, 1.624, 1.625,
        1.626, 1.627, 1.628, 1.629, 1.63, 1.631, 1.632, 1.633, 1.634, 1.635,
        1.636, 1.637, 1.638, 1.639, 1.64, 1.641, 1.642, 1.643, 1.644, 1.645,
        1.646, 1.647, 1.648, 1.649, 1.65, 1.651, 1.652, 1.653, 1.654, 1.655,
        1.656, 1.657, 1.658, 1.659, 1.66, 1.661, 1.662, 1.663, 1.664, 1.665,
        1.666, 1.667, 1.668, 1.669, 1.67, 1.671, 1.672, 1.673, 1.674, 1.675,
        1.676, 1.677, 1.678, 1.679, 1.68, 1.681, 1.682, 1.683, 1.684, 1.685,
        1.686, 1.687, 1.688, 1.689, 1.69, 1.691, 1.692, 1.693, 1.694,
        1.6949999999999998, 1.696, 1.697, 1.698, 1.6989999999999998, 1.7, 1.701,
        1.702, 1.7029999999999998, 1.704, 1.705, 1.706, 1.7069999999999999,
        1.708, 1.709, 1.71, 1.7109999999999999, 1.712, 1.713, 1.714,
        1.7149999999999999, 1.716, 1.717, 1.718, 1.7189999999999999, 1.72, 1.721,
        1.722, 1.7229999999999999, 1.724, 1.725, 1.726, 1.7269999999999999,
        1.728, 1.729, 1.73, 1.7309999999999999, 1.732, 1.733, 1.734,
        1.7349999999999999, 1.736, 1.737, 1.738, 1.7389999999999999, 1.74,
        1.7409999999999999, 1.742, 1.7429999999999999, 1.744, 1.7449999999999997,
        1.746, 1.747, 1.748, 1.749, 1.75, 1.751, 1.752, 1.753, 1.754, 1.755,
        1.756, 1.757, 1.758, 1.759, 1.76, 1.761, 1.762, 1.763, 1.764, 1.765,
        1.766, 1.767, 1.768, 1.769, 1.77, 1.771, 1.772, 1.773, 1.774, 1.775,
        1.776, 1.777, 1.778, 1.779, 1.78, 1.781, 1.782, 1.783, 1.784, 1.785,
        1.786, 1.787, 1.788, 1.789, 1.79, 1.791, 1.792, 1.793, 1.794, 1.795,
        1.796, 1.797, 1.798, 1.799, 1.8, 1.801, 1.802, 1.803, 1.804, 1.805,
        1.806, 1.807, 1.808, 1.809, 1.81, 1.811, 1.812, 1.813, 1.814, 1.815,
        1.816, 1.817, 1.818, 1.819, 1.82, 1.821, 1.822, 1.823, 1.824, 1.825,
        1.826, 1.827, 1.828, 1.829, 1.83, 1.831, 1.832, 1.833, 1.834, 1.835,
        1.8359999999999999, 1.837, 1.838, 1.839, 1.8399999999999999, 1.841,
        1.842, 1.843, 1.8439999999999999, 1.845, 1.846, 1.847,
        1.8479999999999999, 1.849, 1.85, 1.851, 1.8519999999999999, 1.853, 1.854,
        1.855, 1.8559999999999999, 1.857, 1.858, 1.859, 1.8599999999999999,
        1.861, 1.8619999999999999, 1.863, 1.8639999999999999, 1.865,
        1.8659999999999999, 1.867, 1.8679999999999999, 1.869, 1.8699999999999997,
        1.871, 1.872, 1.873, 1.874, 1.875, 1.876, 1.877, 1.878, 1.879, 1.88,
        1.881, 1.882, 1.883, 1.884, 1.885, 1.886, 1.887, 1.888, 1.889, 1.89,
        1.891, 1.892, 1.893, 1.894, 1.895, 1.896, 1.897, 1.898, 1.899, 1.9,
        1.901, 1.902, 1.903, 1.904, 1.905, 1.906, 1.907, 1.908, 1.909, 1.91,
        1.911, 1.912, 1.913, 1.914, 1.915, 1.916, 1.917, 1.918, 1.919, 1.92,
        1.921, 1.922, 1.923, 1.924, 1.925, 1.926, 1.927, 1.928, 1.929, 1.93,
        1.931, 1.932, 1.933, 1.934, 1.935, 1.936, 1.937, 1.938, 1.939, 1.94,
        1.941, 1.942, 1.943, 1.944, 1.945, 1.946, 1.947, 1.948, 1.949, 1.95,
        1.951, 1.952, 1.953, 1.954, 1.955, 1.956, 1.957, 1.958, 1.959, 1.96,
        1.961, 1.962, 1.963, 1.964, 1.965, 1.966, 1.967, 1.968, 1.969, 1.97,
        1.971, 1.972, 1.973, 1.974, 1.975, 1.976, 1.977, 1.978, 1.979, 1.98 } ;

      static real_T pDataValues0[] = { -2.1213203435596424, -2.1258155672156605,
        -2.1303012247052133, -2.1347772958428486, -2.1392437604862562,
        -2.1437005985363515, -2.14814778993737, -2.15258531467696,
        -2.1570131527862659, -2.1614312843400243, -2.1658396894566505,
        -2.1702383482983292, -2.1746272410711023, -2.1790063480249606,
        -2.1833756494539296, -2.187735125696161, -2.1920847571340181,
        -2.1964245241941671, -2.2007544073476648, -2.205074387110042,
        -2.2093844440413992, -2.2136845587464857, -2.2179747118747941,
        -2.2222548841206415, -2.2265250562232612, -2.2307852089668838,
        -2.2350353231808313, -2.2392753797395963, -2.2435053595629308,
        -2.2477252436159332, -2.2519350129091324, -2.2561346484985738,
        -2.2603241314859037, -2.264503443018457, -2.2686725642893375,
        -2.2728314765375077, -2.2769801610478679, -2.2811185991513465,
        -2.2852467722249785, -2.2893646616919914, -2.29347224902189,
        -2.2975695157305385, -2.3016564433802431, -2.3057330135798364,
        -2.30979920798476, -2.3138550082971454, -2.3179003962658977,
        -2.3219353536867784, -2.3259598624024855, -2.329973904302737,
        -2.3339774613243516, -2.3379705154513286, -2.3419530487149309,
        -2.3459250431937657, -2.3498864810138658, -2.3538373443487663,
        -2.3577776154195895, -2.3617072764951219, -2.3656263098918959,
        -2.3695346979742666, -2.3734324231544961, -2.3773194678928249,
        -2.3811958146975614, -2.3850614461251496, -2.3889163447802555,
        -2.39276049331584, -2.3965938744332433, -2.4004164708822557,
        -2.4042282654612, -2.4080292410170063, -2.4118193804452916,
        -2.415598666690435, -2.419367082745655, -2.4231246116530851,
        -2.4268712365038518, -2.4306069404381496, -2.4343317066453172,
        -2.4380455183639125, -2.4417483588817892, -2.4454402115361717,
        -2.449121059713729, -2.4527908868506509, -2.4564496764327206,
        -2.4600974119953913, -2.4637340771238594, -2.4673596554531385,
        -2.4709741306681319, -2.4745774865037067, -2.4781697067447679,
        -2.4817507752263306, -2.4853206758335937, -2.4888793925020085,
        -2.492426909217357, -2.4959632100158204, -2.4994882789840505,
        -2.5030021002592435, -2.506504658029209, -2.5099959365324427,
        -2.5134759200581978, -2.5169445929465541, -2.5204019395884893,
        -2.5238479444259503, -2.5272825919519195, -2.5307058667104902,
        -2.5341177532969312, -2.5375182363577582, -2.5409073005908045,
        -2.5442849307452855, -2.5476511116218714, -2.5510058280727543,
        -2.5543490650017158, -2.557680807364195, -2.5610010401673575,
        -2.5643097484701607, -2.5676069173834231, -2.5708925320698905,
        -2.5741665777443017, -2.5774290396734569, -2.5806799031762826,
        -2.5839191536238992, -2.5871467764396852, -2.590362757099343,
        -2.5935670811309643, -2.5967597341150981, -2.5999407016848104,
        -2.6031099695257516, -2.6062675233762236, -2.6094133490272378,
        -2.612547432322585, -2.6156697591588958, -2.6187803154857039,
        -2.6218790873055111, -2.6249660606738505, -2.628041221699347,
        -2.6311045565437796, -2.6341560514221483, -2.6371956926027305,
        -2.6402234664071464, -2.6432393592104186, -2.6462433574410356,
        -2.6492354475810087, -2.6522156161659387, -2.6551838497850713,
        -2.6581401350813603, -2.6610844587515281, -2.6640168075461217,
        -2.6669371682695764, -2.6698455277802742, -2.6727418729906032,
        -2.6756261908670131, -2.67849846843008, -2.6813586927545585,
        -2.6842068509694439, -2.6870429302580305, -2.6898669178579646,
        -2.6926788010613079, -2.6954785672145904, -2.6982662037188692,
        -2.7010416980297838, -2.7038050376576157, -2.7065562101673408,
        -2.7092952031786868, -2.712022004366192, -2.7147366014592538,
        -2.7174389822421889, -2.72012913455429, -2.7228070462898759,
        -2.725472705398349, -2.7281260998842467, -2.7307672178072981,
        -2.7333960472824779, -2.7360125764800576, -2.73861679362566,
        -2.7412086870003125, -2.7437882449404993, -2.7463554558382137,
        -2.7489103081410118, -2.7514527903520611, -2.7539828910301982,
        -2.7565005987899722, -2.7590059023017037, -2.76149879029153,
        -2.7639792515414605, -2.7664472748894235, -2.7689028492293177,
        -2.7713459635110631, -2.7737766067406486, -2.7761947679801855,
        -2.7786004363479511, -2.7809936010184417, -2.78337425122242,
        -2.7857423762469655, -2.7880979654355191, -2.7904410081879325,
        -2.7927714939605188, -2.7950894122660941, -2.7973947526740313,
        -2.799687504810302, -2.8019676583575257, -2.8042352030550153,
        -2.8064901286988229, -2.8087324251417871, -2.8109620822935781,
        -2.8131790901207427, -2.8153834386467489, -2.8175751179520314,
        -2.8197541181740386, -2.821920429507272, -2.8240740422033346,
        -2.8262149465709729, -2.8283431329761211, -2.830458591841944,
        -2.8325613136488794, -2.8346512889346833, -2.8367285082944709,
        -2.838792962380758, -2.8408446419035047, -2.8428835376301569,
        -2.8449096403856866, -2.8469229410526364, -2.8489234305711553,
        -2.8509110999390437, -2.8528859402117934, -2.854847942502627,
        -2.8567970979825361, -2.8587333978803251, -2.8606568334826488,
        -2.8625673961340481, -2.8644650772369955, -2.86634986825193,
        -2.8682217606972933, -2.8700807461495743, -2.8719268162433407,
        -2.87375996267128, -2.8755801771842369, -2.877387451591249,
        -2.8791817777595847, -2.880963147614779, -2.8827315531406712,
        -2.8844869863794385, -2.8862294394316348, -2.8879589044562231,
        -2.8896753736706158, -2.8913788393507032, -2.8930692938308922,
        -2.894746729504142, -2.8964111388219935, -2.8980625142946077,
        -2.8997008484907978, -2.9013261340380634, -2.902938363622622,
        -2.9045375299894429, -2.90612362594228, -2.9076966443437047,
        -2.9092565781151363, -2.910803420236876, -2.9123371637481368,
        -2.9138578017470746, -2.9153653273908224, -2.916859733895516,
        -2.9183410145363298, -2.9198091626475025, -2.9212641716223713,
        -2.9227060349133964, -2.9241347460321969, -2.9255502985495747,
        -2.9269526860955457, -2.9283419023593691, -2.9297179410895722,
        -2.931080796093986, -2.932430461239762, -2.9337669304534115,
        -2.9350901977208252, -2.9364002570873016, -2.9376971026575762,
        -2.9389807285958471, -2.940251129125798, -2.9415082985306293,
        -2.942752231153082, -2.9439829213954591, -2.9452003637196591,
        -2.9464045526471914, -2.9475954827592088, -2.9487731486965281,
        -2.949937545159655, -2.9510886669088063, -2.9522265087639368,
        -2.9533510656047595, -2.9544623323707704, -2.955560304061271,
        -2.956644975735391, -2.9577163425121107, -2.9587743995702791,
        -2.9598191421486426, -2.960850565545861, -2.9618686651205315,
        -2.9628734362912064, -2.963864874536418, -2.9648429753946961,
        -2.9658077344645877, -2.9667591474046793, -2.9676972099336134,
        -2.9686219178301116, -2.9695332669329884, -2.9704312531411756,
        -2.9713158724137361, -2.9721871207698847, -2.9730449942890056,
        -2.9738894891106691, -2.9747206014346497, -2.9755383275209439,
        -2.9763426636897856, -2.9771336063216634, -2.9779111518573367,
        -2.9786752967978516, -2.9794260377045578, -2.9801633711991218,
        -2.9808872939635442, -2.9815978027401746, -2.9822948943317238,
        -2.9829785656012811, -2.9836488134723265, -2.9843056349287469,
        -2.9849490270148462, -2.9855789868353604, -2.9861955115554726,
        -2.9867985984008225, -2.9873882446575184, -2.9879644476721552,
        -2.9885272048518203, -2.9890765136641058, -2.9896123716371243,
        -2.9901347763595152, -2.9906437254804583, -2.9911392167096831,
        -2.9916212478174811, -2.9920898166347123, -2.9925449210528168,
        -2.9929865590238269, -2.9934147285603725, -2.9938294277356907,
        -2.9942306546836366, -2.9946184075986881, -2.9949926847359603,
        -2.9953534844112042, -2.9957008050008236, -2.9960346449418749,
        -2.9963550027320793, -2.9966618769298292, -2.9969552661541896,
        -2.9972351690849086, -2.9975015844624258, -2.9977545110878707,
        -2.9979939478230739, -2.9982198935905715, -2.9984323473736079,
        -2.9986313082161393, -2.9988167752228456, -2.9989887475591233,
        -2.9991472244510979, -2.9992922051856232, -2.9994236891102872,
        -2.9995416756334108, -2.9996461642240564, -2.999737154412025,
        -2.9998146457878607, -2.9998786380028517, -2.9999291307690354,
        -2.9999661238591915, -2.9999896171068534, -2.9999996104063014,
        -2.9999961037125642, -2.9999790970414235, -2.9999485904694079,
        -2.9999045841337981, -2.9998470782326216, -2.9997760730246554,
        -2.999691568829423, -2.9995935660271926, -2.9994820650589764,
        -2.9993570664265303, -2.9992185706923453, -2.9990665784796549,
        -2.9989010904724211, -2.998722107415341, -2.998529630113838,
        -2.99832365943406, -2.9981041963028736, -2.9978712417078635,
        -2.9976247966973242, -2.9973648623802589, -2.99709143992637,
        -2.9968045305660596, -2.9965041355904187, -2.9961902563512246,
        -2.9958628942609322, -2.9955220507926721, -2.9951677274802377,
        -2.994799925918084, -2.9944186477613179, -2.994023894725689,
        -2.9936156685875872, -2.9931939711840276, -2.9927588044126496,
        -2.9923101702317014, -2.991848070660037, -2.9913725077771032,
        -2.9908834837229326, -2.9903810006981315, -2.9898650609638744,
        -2.9893356668418885, -2.9887928207144463, -2.9882365250243539,
        -2.9876667822749421, -2.9870835950300512, -2.9864869659140232,
        -2.9858768976116887, -2.985253392868354, -2.9846164544897889,
        -2.9839660853422147, -2.9833022883522924, -2.9826250665071057,
        -2.9819344228541542, -2.9812303605013311, -2.9805128826169169,
        -2.97978199242956, -2.9790376932282667, -2.9782799883623796,
        -2.9775088812415715, -2.9767243753358228, -2.9759264741754072,
        -2.9751151813508807, -2.974290500513058, -2.973452435373003,
        -2.9726009897020047, -2.9717361673315708, -2.9708579721533974,
        -2.9699664081193635, -2.9690614792415055, -2.968143189592,
        -2.9672115433031507, -2.9662665445673637, -2.9653081976371305,
        -2.9643365068250129, -2.9633514765036173, -2.9623531111055774,
        -2.9613414151235373, -2.9603163931101255, -2.9592780496779412,
        -2.9582263894995253, -2.957161417307351, -2.9560831378937875,
        -2.9549915561110915, -2.9538866768713814, -2.9527685051466084,
        -2.9516370459685453, -2.950492304428757, -2.9493342856785771,
        -2.9481629949290888, -2.9469784374510986, -2.9457806185751125,
        -2.9445695436913142, -2.9433452182495379, -2.9421076477592463,
        -2.940856837789505, -2.9395927939689561, -2.9383155219857953,
        -2.9370250275877434, -2.9357213165820237, -2.9344043948353331,
        -2.9330742682738182, -2.9317309428830458, -2.9303744247079773,
        -2.9290047198529421, -2.9276218344816107, -2.9262257748169653,
        -2.92481654714127, -2.9233941577960487, -2.9219586131820505,
        -2.9205099197592239, -2.919048084046687, -2.9175731126226969,
        -2.9160850121246238, -2.9145837892489177, -2.9130694507510775,
        -2.911542003445625, -2.9100014542060704, -2.9084478099648821,
        -2.9068810777134582, -2.9053012645020879, -2.9037083774399313,
        -2.9021024236949762, -2.9004834104940111, -2.8988513451225946,
        -2.8972062349250156, -2.8955480873042689, -2.8938769097220165,
        -2.892192709698552, -2.8904954948127752, -2.88878527270215,
        -2.8870620510626721, -2.885325837648836, -2.8835766402736005,
        -2.8818144668083487, -2.8800393251828589, -2.8782512233852673,
        -2.8764501694620264, -2.8746361715178779, -2.8728092377158081,
        -2.8709693762770163, -2.8691165954808762, -2.8672509036648974,
        -2.8653723092246914, -2.8634808206139293, -2.8615764463443054,
        -2.859659194985503, -2.8577290751651483, -2.8557860955687779,
        -2.8538302649397966, -2.8518615920794392, -2.84988008584673,
        -2.8478857551584431, -2.845878608989064, -2.8438586563707471,
        -2.8418259063932751, -2.8397803682040204, -2.8377220510079004,
        -2.8356509640673404, -2.8335671167022256, -2.8314705182898687,
        -2.829361178264957, -2.827239106119519, -2.8251043114028729,
        -2.8229568037215933, -2.8207965927394607, -2.8186236881774205,
        -2.8164380998135408, -2.814239837482964, -2.8120289110778671,
        -2.8098053305474164, -2.8075691058977195, -2.805320247191784,
        -2.8030587645494704, -2.8007846681474455, -2.7984979682191415,
        -2.7961986750547023, -2.7938867990009442, -2.7915623504613052,
        -2.7892253398957991, -2.7868757778209718, -2.7845136748098458,
        -2.7821390414918827, -2.7797518885529278, -2.7773522267351645,
        -2.7749400668370687, -2.7725154197133546, -2.7700782962749297,
        -2.7676287074888468, -2.7651666643782504, -2.76269217802233,
        -2.7602052595562712, -2.7577059201712024, -2.7551941711141454,
        -2.7526700236879691, -2.7501334892513305, -2.7475845792186306,
        -2.7450233050599619, -2.7424496783010519, -2.7398637105232182,
        -2.7372654133633105, -2.7346547985136618, -2.7320318777220343,
        -2.7293966627915669, -2.7267491655807228, -2.7240893980032355,
        -2.7214173720280539, -2.7187330996792909, -2.7160365930361672,
        -2.7133278642329581, -2.7106069254589387, -2.7078737889583278,
        -2.7051284670302369, -2.7023709720286098, -2.6996013163621684,
        -2.696819512494359, -2.694025572943294, -2.6912195102816967,
        -2.6884013371368454, -2.6855710661905126, -2.6827287101789148,
        -2.6798742818926482, -2.6770077941766353, -2.6741292599300652,
        -2.6712386921063387, -2.6683361037130058, -2.6654215078117085,
        -2.6624949175181247, -2.6595563460019038, -2.6566058064866147,
        -2.6536433122496788, -2.6506688766223161, -2.6476825129894817,
        -2.6446842347898074, -2.6416740555155394, -2.638651988712478,
        -2.6356180479799209, -2.6325722469705961, -2.6295145993906015,
        -2.6264451189993476, -2.6233638196094904, -2.6202707150868707,
        -2.6171658193504559, -2.6140491463722704, -2.6109207101773375,
        -2.6077805248436148, -2.6046286045019307, -2.6014649633359213,
        -2.598289615581967, -2.5951025755291273, -2.5919038575190769,
        -2.5886934759460423, -2.5854714452567338, -2.5822377799502836,
        -2.5789924945781828, -2.5757356037442074, -2.5724671221043622,
        -2.5691870643668082, -2.5658954452918, -2.5625922796916178,
        -2.5592775824305019, -2.555951368424584, -2.5526136526418211,
        -2.5492644501019286, -2.545903775876313, -2.5425316450880016,
        -2.5391480729115785, -2.5357530745731109, -2.5323466653500879,
        -2.528928860571344, -2.5254996756169956, -2.5220591259183673,
        -2.5186072269579292, -2.5151439942692195, -2.5116694434367806,
        -2.5081835900960847, -2.5046864499334656, -2.5011780386860485,
        -2.4976583721416765, -2.4941274661388468, -2.4905853365666282,
        -2.4870319993645968, -2.4834674705227657, -2.4798917660815079,
        -2.4763049021314885, -2.4727068948135864, -2.469097760318832,
        -2.4654775148883221, -2.4618461748131564, -2.4582037564343571,
        -2.4545502761428026, -2.4508857503791477, -2.447210195633752,
        -2.4435236284466053, -2.4398260654072552, -2.4361175231547274,
        -2.4323980183774543, -2.4286675678132053, -2.4249261882489987,
        -2.4211738965210383, -2.4174107095146278, -2.4136366441641051,
        -2.4098517174527552, -2.4060559464127445, -2.4022493481250353,
        -2.398431939719313, -2.3946037383739092, -2.3907647613157232,
        -2.3869150258201466, -2.3830545492109807, -2.3791833488603658,
        -2.3753014421886953, -2.371408846664544, -2.3675055798045843,
        -2.3635916591735082, -2.3596671023839573, -2.3557319270964268,
        -2.3517861510192, -2.3478297919082611, -2.3438628675672217,
        -2.3398853958472321, -2.3358973946469113, -2.3318988819122564,
        -2.3278898756365676, -2.3238703938603664, -2.3198404546713141,
        -2.3158000762041313, -2.311749276640513, -2.3076880742090511,
        -2.30361648718515, -2.299534533890943, -2.2954422326952146,
        -2.291339602013311, -2.2872266603070663, -2.2831034260847103,
        -2.2789699179007896, -2.2748261543560844, -2.2706721540975225,
        -2.2665079358180988, -2.26233351825679, -2.2581489201984648,
        -2.25395416047381, -2.2497492579592375, -2.2455342315768005,
        -2.24130910029411, -2.2370738831242507, -2.2328285991256922,
        -2.2285732674022047, -2.2243079071027765, -2.2200325374215191,
        -2.2157471775975894, -2.2114518469150983, -2.20714656470303,
        -2.2028313503351447, -2.1985062232299, -2.1941712028503608,
        -2.1898263087041108, -2.1854715603431676, -2.1811069773638896,
        -2.1767325794068957, -2.1723483861569672, -2.1679544173429668,
        -2.1635506927377466, -2.15913723215806, -2.1547140554644728,
        -2.1502811825612711, -2.1458386333963775, -2.1413864279612547,
        -2.1369245862908195, -2.13245312846335, -2.1279720746004029,
        -2.123481444866711, -2.1189812594701012, -2.1144715386613995,
        -2.10995230273434, -2.1054235720254808, -2.100885366914099,
        -2.0963377078221122, -2.091780615213978, -2.0872141095966046,
        -2.0826382115192597, -2.0780529415734783, -2.0734583203929673,
        -2.0688543686535112, -2.0642411070728892, -2.0596185564107681,
        -2.0549867374686195, -2.0503456710896182, -2.0456953781585581,
        -2.0410358796017487, -2.0363671963869256, -2.0316893495231549,
        -2.027002360060739, -2.0223062490911246, -2.0176010377468003,
        -2.0128867472012124, -2.0081633986686582, -2.0034310134041995,
        -1.9986896127035598, -1.9939392179030371, -1.989179850379398,
        -1.9844115315497886, -1.9796342828716362, -1.9748481258425523,
        -1.9700530820002344, -1.9652491729223709, -1.9604364202265456,
        -1.9556148455701381, -1.9507844706502262, -1.9459453172034884,
        -1.9410974070061067, -1.9362407618736681, -1.9313754036610693,
        -1.9265013542624132, -1.9216186356109133, -1.9167272696787965,
        -1.911827278477201, -1.9069186840560783, -1.9020015085040944,
        -1.8970757739485327, -1.8921415025551889, -1.8871987165282771,
        -1.8822474381103258, -1.8772876895820791, -1.8723194932623979,
        -1.8673428715081535, -1.8623578467141411, -1.8573644413129613,
        -1.8523626777749296, -1.8473525786079728, -1.842334166357531,
        -1.8373074636064479, -1.8322724929748804, -1.8272292771201866,
        -1.822177838736829, -1.8171182005562725, -1.8120503853468781,
        -1.806974415913809, -1.8018903150989163, -1.7967981057806472,
        -1.7916978108739343, -1.7865894533300963, -1.7814730561367331,
        -1.7763486423176214, -1.7712162349326188, -1.7660758570775479,
        -1.7609275318841007, -1.7557712825197302, -1.7506071321875525,
        -1.7454351041262328, -1.7402552216098914, -1.7350675079479889,
        -1.7298719864852292, -1.7246686806014488, -1.7194576137115156,
        -1.714238809265223, -1.7090122907471808, -1.7037780816767145,
        -1.6985362056077564, -1.6932866861287392, -1.688029546862492,
        -1.6827648114661302, -1.6774925036309587, -1.6722126470823517,
        -1.6669252655796543, -1.6616303829160746, -1.6563280229185753,
        -1.6510182094477672, -1.6457009663978044, -1.6403763176962698,
        -1.635044287304074, -1.6297048992153438, -1.6243581774573168,
        -1.6190041460902329, -1.6136428292072227, -1.6082742509342054,
        -1.6028984354297728, -1.5975154068850854, -1.5921251895237623,
        -1.5867278076017732, -1.5813232854073271, -1.5759116472607662,
        -1.570492917514452, -1.565067120552659, -1.5596342807914632,
        -1.5541944226786364, -1.5487475706935312, -1.5432937493469707,
        -1.5378329831811433, -1.5323652967694863, -1.5268907147165787,
        -1.5214092616580321, -1.5159209622603749, -1.5104258412209466,
        -1.5049239232677816, -1.4994152331595014, -1.4938997956852016,
        -1.4883776356643428, -1.4828487779466342, -1.4773132474119279,
        -1.4717710689701018, -1.4662222675609486, -1.4606668681540658,
        -1.4551048957487387, -1.4495363753738386, -1.4439613320876954,
        -1.4383797909779943, -1.4327917771616616, -1.4271973157847482,
        -1.4215964320223227, -1.4159891510783513, -1.4103754981855909,
        -1.4047554986054684, -1.3991291776279731, -1.3934965605715377,
        -1.3878576727829328, -1.3822125396371425, -1.3765611865372549,
        -1.3709036389143523, -1.3652399222273877, -1.3595700619630768,
        -1.3538940836357793, -1.3482120127873922, -1.3425238749872228,
        -1.3368296958318817, -1.3311295009451651, -1.3254233159779392,
        -1.3197111666080295, -1.3139930785400955, -1.3082690775055268,
        -1.302539189262317, -1.2968034395949537, -1.2910618543142995,
        -1.2853144592574806, -1.2795612802877638, -1.2738023432944441,
        -1.2680376741927302, -1.2622672989236219, -1.2564912434537989,
        -1.2507095337755008, -1.2449221959064096, -1.2391292558895382,
        -1.233330739793107, -1.2275266737104282, -1.2217170837597893,
        -1.2159019960843336, -1.210081436851949, -1.2042554322551389,
        -1.1984240085109172, -1.1925871918606796, -1.1867450085700912,
        -1.1808974849289671, -1.1750446472511518, -1.1691865218744084,
        -1.1633231351602882, -1.157454513494024, -1.1515806832844024,
        -1.1457016709636494, -1.139817502987309, -1.1339282058341287,
        -1.1280338060059367, -1.1221343300275217, -1.1162298044465147,
        -1.1103202558332703, -1.1044057107807494, -1.0984861959043926,
        -1.0925617378420092, -1.086632363253649, -1.080698098821488,
        -1.0747589712497061, -1.0688150072643658, -1.0628662336132977,
        -1.0569126770659707, -1.0509543644133816, -1.0449913224679253,
        -1.0390235780632819, -1.0330511580542912, -1.0270740893168322,
        -1.0210923987477045, -1.0151061132645041, -1.0091152598055084,
        -1.0031198653295454, -0.99711995681588217, -0.99111556126409484,
        -0.98510670569395531, -0.97909341714530285, -0.9730757226779253,
        -0.9670536493714379, -0.96102722432515886, -0.95499647465799331,
        -0.94896142750830215, -0.9429221100337899, -0.93687854941137227,
        -0.93083077283706461, -0.92477880752584984, -0.91872268071156182,
        -0.9126624196467612, -0.90659805160261064, -0.90052960386875913,
        -0.89445710375320875, -0.8883805785822021, -0.88230005570008962,
        -0.87621556246921661, -0.87012712626979116, -0.86403477449976585,
        -0.85793853457471358, -0.85183843392770175, -0.84573450000917627,
        -0.83962676028682659, -0.8335152422454738, -0.827399973386936,
        -0.82128098122991589, -0.81515829330986589, -0.80903193717887167,
        -0.80290194040552509, -0.79676833057480068, -0.79063113528793427,
        -0.78449038216229194, -0.77834609883125516, -0.7721983129440857,
        -0.76604705216581248, -0.75989234417709728, -0.75373421667411533,
        -0.74757269736843057, -0.74140781398686773, -0.7352395942713944,
        -0.72906806597898621, -0.72289325688151274, -0.71671519476560186,
        -0.71053390743252542, -0.70434942269806444, -0.69816176839238986,
        -0.69197097235993588, -0.6857770624592725, -0.67958006656298664,
        -0.67338001255754665, -0.6671769283431892, -0.66097084183377619,
        -0.65476178095669413, -0.64854977365270017, -0.6423348478758204,
        -0.63611703159320909, -0.62989635278502909, -0.62367283944432339,
        -0.61744651957689367, -0.61121742120116673, -0.60498557234807715,
        -0.59875100106093138, -0.59251373539529262, -0.58627380341884439,
        -0.58003123321127015, -0.573786052864124, -0.56753829048070958,
        -0.56128797417594423, -0.55503513207624511, -0.54877979231938423,
        -0.54252198305438781, -0.53626173244138076, -0.52999906865148372,
        -0.52373401986667234, -0.51746661427965512, -0.51119688009374575,
        -0.50492484552273986, -0.49865053879077992, -0.49237398813223815,
        -0.48609522179157927, -0.47981426802324406, -0.47353115509151233,
        -0.4672459112703819, -0.46095856484343783, -0.4546691441037311,
        -0.44837767735364187, -0.44208419290476259, -0.4357887190777599,
        -0.42949128420225935, -0.423191916616702, -0.41689064466823539,
        -0.41058749671256989, -0.40428250111386477, -0.39797568624458429,
        -0.39166708048538845, -0.38535671222499013, -0.37904460986003841,
        -0.37273080179498058, -0.36641531644194497, -0.36009818222060375,
        -0.35377942755805014, -0.34745908088866834, -0.34113717065401006,
        -0.33481372530265818, -0.32848877329010884, -0.32216234307863267,
        -0.31583446313715896, -0.30950516194113142, -0.30317446797239878,
        -0.29684240971907055, -0.2905090156754021, -0.28417431434165208,
        -0.2778383342239657, -0.2715011038342442, -0.26516265169001491,
        -0.2588230063143005, -0.25248219623549312, -0.24614024998723003,
        -0.23979719610825737, -0.2334530631423069, -0.22710787963796492,
        -0.22076167414854778, -0.21441447523197085, -0.20806631145061855,
        -0.20171721137121312, -0.195367203564697, -0.18901631660609577,
        -0.18266457907438882, -0.17631201955238426, -0.16995866662658796,
        -0.16360454888707993, -0.157249694927378, -0.15089413334431293,
        -0.14453789273790243, -0.13818100171121986, -0.13182348887026277,
        -0.12546538282382821, -0.11910671218338134, -0.11274750556293198,
        -0.10638779157889917, -0.10002759884997978, -0.0936669559970357,
        -0.087305891642949038, -0.080944434412498614, -0.074582612932227288,
        -0.068220455830323615, -0.061857991736486491, -0.055495249281789616,
        -0.049132257098563288, -0.04276904382026292, -0.036405638081338877,
        -0.030042068517104895, -0.023678363763611945, -0.017314552457523356,
        -0.010950663235977922, -0.0045867247364664082, 0.0017772344033000146,
        0.00814118554551462, 0.014505100052406678, 0.020868949286371643,
        0.027232704610104033, 0.033596337386708974, 0.039959818979852367,
        0.046323120753877768, 0.052686214073937962, 0.0590490703061264,
        0.065411660817594086, 0.071773956976699832, 0.078135930153121619,
        0.084497551717989575, 0.090858793044016048, 0.097219625505627169,
        0.10358002047908757, 0.10993994934263192, 0.11629938347658841,
        0.12265829426351423, 0.1290166530883268, 0.1353744313384142,
        0.14173160040379304, 0.14808813167720522, 0.15444399655427743,
        0.16079916643362438, 0.1671536127169938, 0.17350730680938803,
        0.17986022011919578, 0.18621232405831512, 0.19256359004229179,
        0.19891398949043693, 0.20526349382596629, 0.21161207447611852,
        0.21795970287229269, 0.22430635045017175, 0.23065198864985365,
        0.23699658891597317, 0.24334012269784644, 0.24968256144957435,
        0.25602387663020093, 0.26236403970381078, 0.26870302213968739,
        0.27504079541241638, 0.28137733100203022, 0.28771260039412944,
        0.29404657508001364, 0.30037922655680482, 0.30671052632758483,
        0.31304044590151248, 0.31936895679396327, 0.32569603052664603,
        0.33202163862774103, 0.33834575263202249, 0.3446683440809894,
        0.35098938452298828, 0.35730884551335046, 0.363626698614508,
        0.36994291539613822, 0.376257467435272, 0.38257032631643861,
        0.38888146363178105, 0.39519085098119344, 0.40149845997244316,
        0.40780426222130195, 0.41410822935166758, 0.42041033299570124,
        0.4267105447939446, 0.43300883639545767, 0.4393051794579364,
        0.44559954564784904, 0.45189190664055806, 0.458182234120451,
        0.46447049978106247, 0.47075667532520993, 0.47704073246511014,
        0.48332264292252197, 0.48960237842885496, 0.49587991072531251,
        0.50215521156300724, 0.50842825270309733, 0.51469900591690831,
        0.52096744298606246, 0.527233535702601, 0.53349725586911856,
        0.53975857529888638, 0.54601746581597488, 0.55227389925538994,
        0.55852784746318751, 0.56477928229661678, 0.5710281756242287,
        0.57727449932601271, 0.58351822529352249, 0.58975932543000587,
        0.59599777165052, 0.60223353588206607, 0.608466590063717,
        0.61469690614674066, 0.6209244560947228, 0.62714921188370032,
        0.63337114550228246, 0.63959022895178019, 0.64580643424632678,
        0.6520197334130079, 0.65823009849198877, 0.66443750153663861,
        0.67064191461365152, 0.6768433098031803, 0.6830416591989571,
        0.68923693490842164, 0.69542910905284194, 0.70161815376744385,
        0.7078040412015365, 0.71398674351864067, 0.72016623289660386,
        0.72634248152773317, 0.73251546161892112, 0.738685145391768,
        0.74485150508270837, 0.7510145129431316, 0.75717414123951376,
        0.76333036225353967, 0.769483148282222, 0.77563247163803573,
        0.78177830464903719, 0.78792061965898563, 0.79405938902747653,
        0.8001945851300557, 0.80632618035835046, 0.81245414712019826,
        0.81857845783975136, 0.824699084957628, 0.83081600093101271,
        0.83692917823379631, 0.84303858935668929, 0.84914420680735259,
        0.85524600311051813, 0.86134395080811432, 0.867438022459384,
        0.87352819064101772, 0.87961442794726641, 0.88569670699007375,
        0.89177500039919522, 0.89784928082231885, 0.90391952092519379,
        0.909985693391751, 0.91604777092422118, 0.92210572624327181,
        0.92815953208810664, 0.93420916121661579, 0.94025458640547488,
        0.94629578045028273, 0.95233271616567461, 0.95836536638545033,
        0.964393703962695, 0.97041770176990017, 0.97643733269908384,
        0.98245256966191929, 0.988463385589848, 0.99446975343420974,
        1.0004716461663588, 1.00646903677779, 1.0124618982802525,
        1.0184502037058816, 1.0244339261073125, 1.0304130385578072,
        1.0363875141513648, 1.0423573260028576, 1.0483224472481421,
        1.0542828510441844, 1.0602385105691752, 1.0661893990226572,
        1.072135489625643, 1.0780767556207369, 1.0840131702722451,
        1.0899447068663213, 1.0958713387110532, 1.1017930391366102,
        1.1077097814953505, 1.1136215391619446, 1.1195282855334905,
        1.1254299940296406, 1.1313266380927165, 1.137218191187833,
        1.1431046268030056, 1.1489859184492863, 1.1548620396608731,
        1.1607329639952315, 1.1665986650332096, 1.1724591163791633,
        1.178314291661072, 1.1841641645306593, 1.1900087086634994,
        1.1958478977591636, 1.2016817055413032, 1.2075101057577959,
        1.2133330721808504, 1.2191505786071286, 1.2249625988578594,
        1.2307691067789623, 1.2365700762411618, 1.2423654811401073,
        1.2481552953964816, 1.2539394929561329, 1.2597180477901819,
        1.265490933895143, 1.2712581252930357, 1.2770195960315103,
        1.2827753201839569, 1.2885252718496303, 1.29426942515375,
        1.3000077542476451, 1.3057402333088377, 1.3114668365411848,
        1.3171875381749785, 1.3229023124670753, 1.3286111337009971,
        1.3343139761870597, 1.3400108142624809, 1.3457016222915017,
        1.3513863746654904, 1.3570650458030735, 1.3627376101502409,
        1.3684040421804631, 1.3740643163948039, 1.3797184073220381,
        1.3853662895187697, 1.3910079375695381, 1.3966433260869295,
        1.4022724297117133, 1.4078952231129318, 1.4135116809880208,
        1.4191217780629286, 1.4247254890922307, 1.4303227888592376,
        1.4359136521761071, 1.4414980538839646, 1.4470759688530124,
        1.4526473719826447, 1.4582122382015519, 1.463770542467848,
        1.4693222597691729, 1.47486736512281, 1.480405833575791,
        1.4859376402050197, 1.4914627601173747, 1.4969811684498262,
        1.5024928403695479, 1.5079977510740212, 1.5134958757911596,
        1.5189871897794112, 1.5244716683278714, 1.5299492867563984,
        1.5354200204157151, 1.5408838446875313, 1.5463407349846463,
        1.5517906667510661, 1.5572336154621016, 1.5626695566244955,
        1.5680984657765213, 1.5735203184880988, 1.5789350903608956,
        1.5843427570284532, 1.5897432941562764, 1.5951366774419582,
        1.6005228826152835, 1.6059018854383402, 1.6112736617056203,
        1.6166381872441415, 1.6219954379135484, 1.6273453896062227,
        1.6326880182473889, 1.6380232997952284, 1.6433512102409826,
        1.6486717256090662, 1.6539848219571645, 1.6592904753763551,
        1.6645886619912065, 1.6698793579598892, 1.6751625394742771,
        1.6804381827600656, 1.6857062640768667, 1.6909667597183262,
        1.6962196460122163, 1.7014648993205659, 1.7067024960397379,
        1.7119324126005573, 1.7171546254684091, 1.722369111143345,
        1.7275758461601864, 1.7327748070886355, 1.7379659705333763,
        1.7431493131341853, 1.7483248115660237, 1.7534924425391611,
        1.7586521827992656, 1.7638040091275169, 1.768947898340701,
        1.7740838272913297, 1.7792117728677286, 1.7843317119941537,
        1.789443621630882, 1.794547478774337, 1.7996432604571628,
        1.8047309437483547, 1.8098105057533442, 1.8148819236141136,
        1.8199451745092883, 1.8250002356542485, 1.8300470843012278,
        1.8350856977394183, 1.840116053295064, 1.8451381283315744,
        1.850151900249621, 1.85515734648724, 1.8601544445199281,
        1.8651431718607572, 1.8701235060604589, 1.8750954247075418,
        1.8800589054283732, 1.8850139258873071, 1.8899604637867531,
        1.8948984968673017, 1.8998280029078121, 1.9047489597255161,
        1.9096613451761144, 1.9145651371538823, 1.9194603135917638,
        1.9243468524614755, 1.9292247317735962, 1.9340939295776793,
        1.9389544239623433, 1.9438061930553723, 1.9486492150238122,
        1.9534834680740722, 1.9583089304520225, 1.9631255804430925,
        1.9679333963723595, 1.9727323566046671, 1.9775224395446978,
        1.982303623637087, 1.9870758873665151, 1.9918392092578046,
        1.9965935678760125, 2.0013389418265337, 2.0060753097551949,
        2.0108026503483485, 2.0155209423329667, 2.0202301644767466,
        2.0249302955881947, 2.029621314516731, 2.0343032001527761,
        2.0389759314278533, 2.0436394873146795, 2.0482938468272636,
        2.05293898902099, 2.0575748929927333, 2.0622015378809286,
        2.0668189028656836, 2.0714269671688634, 2.0760257100541879,
        2.0806151108273183, 2.0851951488359619, 2.0897658034699544,
        2.0943270541613592, 2.0988788803845533, 2.1034212616563273,
        2.1079541775359734, 2.1124776076253782, 2.1169915315691128, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

      final23_vcontrol_1_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
      final23_vcontrol_1_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
      final23_vcontrol_1_DW.FromWorkspace_IWORK.PrevIndex = 0;
    }

    /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Start_wrapper
      (&final23_vcontrol_1_DW.QuadEncoder2axis_DSTATE,
       &final23_vcontrol_1_P.QuadEncoder2axis_P1, 1,
       &final23_vcontrol_1_P.QuadEncoder2axis_P2, 1,
       &final23_vcontrol_1_P.QuadEncoder2axis_P3, 1,
       &final23_vcontrol_1_P.QuadEncoder2axis_P4, 1,
       &final23_vcontrol_1_P.QuadEncoder2axis_P5, 1,
       &final23_vcontrol_1_P.QuadEncoder2axis_P6, 1);
    final23_vco_MovingAverage_Start(&final23_vcontrol_1_DW.MovingAverage);

    /* Start for MATLABSystem: '<Root>/PWM' */
    final23_vcontrol_1_DW.obj_g.matlabCodegenIsDeleted = false;
    final23_vcontrol_1_DW.objisempty_l = true;
    final23_vcontrol_1_DW.obj_g.isInitialized = 1;
    final23_vcontrol_1_DW.obj_g.PinNumber = 19U;
    ret = EXT_PWMBlock_init(final23_vcontrol_1_DW.obj_g.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_1_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_1_B.b[0], final23_vcontrol_1_DW.obj_g.PinNumber);
    }

    final23_vcontrol_1_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */

    /* Start for MATLABSystem: '<Root>/PWM1' */
    final23_vcontrol_1_DW.obj_e.matlabCodegenIsDeleted = false;
    final23_vcontrol_1_DW.objisempty_p = true;
    final23_vcontrol_1_DW.obj_e.isInitialized = 1;
    final23_vcontrol_1_DW.obj_e.PinNumber = 26U;
    ret = EXT_PWMBlock_init(final23_vcontrol_1_DW.obj_e.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_1_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_1_B.b[0], final23_vcontrol_1_DW.obj_e.PinNumber);
    }

    final23_vcontrol_1_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM1' */
    final23_vco_MovingAverage_Start(&final23_vcontrol_1_DW.MovingAverage_p);

    /* Start for FromWorkspace: '<Root>/From Workspace1' */
    {
      static real_T pTimeValues0[] = { 0.0, 0.001, 0.002, 0.003, 0.004, 0.005,
        0.006, 0.007, 0.008, 0.0090000000000000011, 0.01, 0.011, 0.012,
        0.013000000000000001, 0.014, 0.015, 0.016, 0.017, 0.018000000000000002,
        0.019, 0.02, 0.021, 0.022, 0.023, 0.024, 0.025, 0.026000000000000002,
        0.027, 0.028, 0.029, 0.03, 0.031, 0.032, 0.033, 0.034, 0.035,
        0.036000000000000004, 0.037, 0.038, 0.039, 0.04, 0.041, 0.042, 0.043,
        0.044, 0.045, 0.046, 0.047, 0.048, 0.049, 0.05, 0.051000000000000004,
        0.052000000000000005, 0.053, 0.054, 0.055, 0.056, 0.057, 0.058,
        0.059000000000000004, 0.06, 0.061, 0.062, 0.063, 0.064, 0.065, 0.066,
        0.067, 0.068, 0.069, 0.07, 0.071000000000000008, 0.072000000000000008,
        0.073, 0.074, 0.075, 0.076, 0.077, 0.078, 0.079, 0.08, 0.081, 0.082,
        0.083, 0.084, 0.085, 0.086, 0.087000000000000008, 0.088, 0.089, 0.09,
        0.091, 0.092, 0.093, 0.094, 0.095, 0.096, 0.097, 0.098, 0.099, 0.1,
        0.101, 0.10200000000000001, 0.10300000000000001, 0.10400000000000001,
        0.105, 0.106, 0.107, 0.108, 0.109, 0.11, 0.111, 0.112, 0.113, 0.114,
        0.115, 0.116, 0.117, 0.11800000000000001, 0.11900000000000001, 0.12,
        0.121, 0.122, 0.123, 0.124, 0.125, 0.126, 0.127, 0.128, 0.129, 0.13,
        0.131, 0.132, 0.133, 0.134, 0.135, 0.136, 0.137, 0.138, 0.139, 0.14,
        0.141, 0.14200000000000002, 0.14300000000000002, 0.14400000000000002,
        0.145, 0.146, 0.147, 0.148, 0.149, 0.15, 0.151, 0.152, 0.153, 0.154,
        0.155, 0.156, 0.157, 0.158, 0.159, 0.16, 0.161, 0.162, 0.163, 0.164,
        0.165, 0.166, 0.167, 0.168, 0.169, 0.17, 0.171, 0.172,
        0.17300000000000001, 0.17400000000000002, 0.17500000000000002, 0.176,
        0.177, 0.178, 0.179, 0.18, 0.181, 0.182, 0.183, 0.184, 0.185, 0.186,
        0.187, 0.188, 0.189, 0.19, 0.191, 0.192, 0.193, 0.194, 0.195, 0.196,
        0.197, 0.198, 0.199, 0.2, 0.201, 0.202, 0.203, 0.20400000000000001,
        0.20500000000000002, 0.20600000000000002, 0.20700000000000002,
        0.20800000000000002, 0.209, 0.21, 0.211, 0.212, 0.213, 0.214, 0.215,
        0.216, 0.217, 0.218, 0.219, 0.22, 0.221, 0.222, 0.223, 0.224, 0.225,
        0.226, 0.227, 0.228, 0.229, 0.23, 0.231, 0.232, 0.233, 0.234,
        0.23500000000000004, 0.23600000000000002, 0.23700000000000002,
        0.23800000000000002, 0.23900000000000002, 0.24, 0.241, 0.242, 0.243,
        0.244, 0.245, 0.246, 0.247, 0.248, 0.249, 0.25, 0.251, 0.252, 0.253,
        0.254, 0.255, 0.256, 0.257, 0.258, 0.259, 0.26, 0.261, 0.262, 0.263,
        0.264, 0.265, 0.266, 0.267, 0.268, 0.269, 0.27, 0.271, 0.272, 0.273,
        0.274, 0.275, 0.276, 0.277, 0.278, 0.279, 0.28, 0.281, 0.282,
        0.28300000000000003, 0.28400000000000003, 0.28500000000000003,
        0.28600000000000003, 0.28700000000000003, 0.28800000000000003, 0.289,
        0.29, 0.291, 0.292, 0.293, 0.294, 0.295, 0.296, 0.297, 0.298, 0.299, 0.3,
        0.301, 0.302, 0.303, 0.304, 0.305, 0.306, 0.307, 0.308, 0.309, 0.31,
        0.311, 0.312, 0.313, 0.314, 0.315, 0.316, 0.317, 0.318, 0.319, 0.32,
        0.321, 0.322, 0.323, 0.324, 0.325, 0.326, 0.327, 0.328, 0.329, 0.33,
        0.331, 0.332, 0.333, 0.334, 0.335, 0.336, 0.337, 0.338, 0.339, 0.34,
        0.341, 0.342, 0.343, 0.344, 0.34500000000000008, 0.34600000000000003,
        0.34700000000000003, 0.34800000000000003, 0.34900000000000003,
        0.35000000000000003, 0.35100000000000003, 0.352, 0.353, 0.354, 0.355,
        0.356, 0.357, 0.358, 0.359, 0.36, 0.361, 0.362, 0.363, 0.364, 0.365,
        0.366, 0.367, 0.368, 0.369, 0.37, 0.371, 0.372, 0.373, 0.374, 0.375,
        0.376, 0.377, 0.378, 0.379, 0.38, 0.381, 0.382, 0.383, 0.384, 0.385,
        0.386, 0.387, 0.388, 0.389, 0.39, 0.391, 0.392, 0.393, 0.394, 0.395,
        0.396, 0.397, 0.398, 0.399, 0.4, 0.401, 0.402, 0.403, 0.404, 0.405,
        0.406, 0.407, 0.40800000000000003, 0.40900000000000003,
        0.41000000000000003, 0.41100000000000003, 0.41200000000000003,
        0.41300000000000003, 0.41400000000000003, 0.41500000000000004,
        0.41600000000000004, 0.417, 0.418, 0.419, 0.42, 0.421, 0.422, 0.423,
        0.424, 0.425, 0.426, 0.427, 0.428, 0.429, 0.43, 0.431, 0.432, 0.433,
        0.434, 0.435, 0.436, 0.437, 0.438, 0.439, 0.44, 0.441, 0.442, 0.443,
        0.444, 0.445, 0.446, 0.447, 0.448, 0.449, 0.45, 0.451, 0.452, 0.453,
        0.454, 0.455, 0.456, 0.457, 0.458, 0.459, 0.46, 0.461, 0.462, 0.463,
        0.464, 0.465, 0.466, 0.467, 0.468, 0.469, 0.47000000000000008,
        0.47100000000000003, 0.47200000000000003, 0.47300000000000003,
        0.47400000000000003, 0.47500000000000003, 0.47600000000000003,
        0.47700000000000004, 0.47800000000000004, 0.47900000000000004, 0.48,
        0.481, 0.482, 0.483, 0.484, 0.485, 0.486, 0.487, 0.488, 0.489, 0.49,
        0.491, 0.492, 0.493, 0.494, 0.495, 0.496, 0.497, 0.498, 0.499, 0.5,
        0.501, 0.502, 0.503, 0.504, 0.505, 0.506, 0.507, 0.508, 0.509, 0.51,
        0.511, 0.512, 0.513, 0.514, 0.515, 0.516, 0.517, 0.518, 0.519, 0.52,
        0.521, 0.522, 0.523, 0.524, 0.525, 0.526, 0.527, 0.528, 0.529, 0.53,
        0.531, 0.532, 0.533, 0.534, 0.535, 0.536, 0.537, 0.538, 0.539, 0.54,
        0.541, 0.542, 0.543, 0.544, 0.545, 0.546, 0.547, 0.548, 0.549, 0.55,
        0.551, 0.552, 0.553, 0.554, 0.555, 0.556, 0.557, 0.558, 0.559, 0.56,
        0.561, 0.562, 0.563, 0.564, 0.56500000000000017, 0.56600000000000006,
        0.56700000000000006, 0.56800000000000006, 0.56900000000000006,
        0.57000000000000006, 0.57100000000000006, 0.57200000000000006,
        0.57300000000000006, 0.57400000000000007, 0.57500000000000007,
        0.57600000000000007, 0.577, 0.578, 0.579, 0.58, 0.581, 0.582, 0.583,
        0.584, 0.585, 0.586, 0.587, 0.588, 0.589, 0.59, 0.591, 0.592, 0.593,
        0.594, 0.595, 0.596, 0.597, 0.598, 0.599, 0.6, 0.601, 0.602, 0.603,
        0.604, 0.605, 0.606, 0.607, 0.608, 0.609, 0.61, 0.611, 0.612, 0.613,
        0.614, 0.615, 0.616, 0.617, 0.618, 0.619, 0.62, 0.621, 0.622, 0.623,
        0.624, 0.625, 0.626, 0.627, 0.628, 0.629, 0.63, 0.631, 0.632, 0.633,
        0.634, 0.635, 0.636, 0.637, 0.638, 0.639, 0.64, 0.641, 0.642, 0.643,
        0.644, 0.645, 0.646, 0.647, 0.648, 0.649, 0.65, 0.651, 0.652, 0.653,
        0.654, 0.655, 0.656, 0.657, 0.658, 0.659, 0.66, 0.661, 0.662, 0.663,
        0.664, 0.665, 0.666, 0.667, 0.668, 0.669, 0.67, 0.671, 0.672, 0.673,
        0.674, 0.675, 0.676, 0.677, 0.678, 0.679, 0.68, 0.681, 0.682, 0.683,
        0.684, 0.685, 0.686, 0.687, 0.688, 0.689, 0.69000000000000017,
        0.69100000000000006, 0.69200000000000006, 0.69300000000000006,
        0.69400000000000006, 0.69500000000000006, 0.69600000000000006,
        0.69700000000000006, 0.69800000000000006, 0.69900000000000007,
        0.70000000000000007, 0.70100000000000007, 0.70200000000000007,
        0.70300000000000007, 0.704, 0.705, 0.706, 0.707, 0.708, 0.709, 0.71,
        0.711, 0.712, 0.713, 0.714, 0.715, 0.716, 0.717, 0.718, 0.719, 0.72,
        0.721, 0.722, 0.723, 0.724, 0.725, 0.726, 0.727, 0.728, 0.729, 0.73,
        0.731, 0.732, 0.733, 0.734, 0.735, 0.736, 0.737, 0.738, 0.739, 0.74,
        0.741, 0.742, 0.743, 0.744, 0.745, 0.746, 0.747, 0.748, 0.749, 0.75,
        0.751, 0.752, 0.753, 0.754, 0.755, 0.756, 0.757, 0.758, 0.759, 0.76,
        0.761, 0.762, 0.763, 0.764, 0.765, 0.766, 0.767, 0.768, 0.769, 0.77,
        0.771, 0.772, 0.773, 0.774, 0.775, 0.776, 0.777, 0.778, 0.779, 0.78,
        0.781, 0.782, 0.783, 0.784, 0.785, 0.786, 0.787, 0.788, 0.789, 0.79,
        0.791, 0.792, 0.793, 0.794, 0.795, 0.796, 0.797, 0.798, 0.799, 0.8,
        0.801, 0.802, 0.803, 0.804, 0.805, 0.806, 0.807, 0.808, 0.809, 0.81,
        0.811, 0.812, 0.813, 0.814, 0.81500000000000017, 0.81600000000000006,
        0.81700000000000006, 0.81800000000000006, 0.81900000000000006,
        0.82000000000000006, 0.82100000000000006, 0.82200000000000006,
        0.82300000000000006, 0.82400000000000007, 0.82500000000000007,
        0.82600000000000007, 0.82700000000000007, 0.82800000000000007,
        0.82900000000000007, 0.83000000000000007, 0.83100000000000007,
        0.83200000000000007, 0.833, 0.834, 0.835, 0.836, 0.837, 0.838, 0.839,
        0.84, 0.841, 0.842, 0.843, 0.844, 0.845, 0.846, 0.847, 0.848, 0.849,
        0.85, 0.851, 0.852, 0.853, 0.854, 0.855, 0.856, 0.857, 0.858, 0.859,
        0.86, 0.861, 0.862, 0.863, 0.864, 0.865, 0.866, 0.867, 0.868, 0.869,
        0.87, 0.871, 0.872, 0.873, 0.874, 0.875, 0.876, 0.877, 0.878, 0.879,
        0.88, 0.881, 0.882, 0.883, 0.884, 0.885, 0.886, 0.887, 0.888, 0.889,
        0.89, 0.891, 0.892, 0.893, 0.894, 0.895, 0.896, 0.897, 0.898, 0.899, 0.9,
        0.901, 0.902, 0.903, 0.904, 0.905, 0.906, 0.907, 0.908, 0.909, 0.91,
        0.911, 0.912, 0.913, 0.914, 0.915, 0.916, 0.917, 0.918, 0.919, 0.92,
        0.921, 0.922, 0.923, 0.924, 0.925, 0.926, 0.927, 0.928, 0.929, 0.93,
        0.931, 0.932, 0.933, 0.934, 0.935, 0.936, 0.937, 0.938, 0.939,
        0.94000000000000017, 0.94100000000000006, 0.94200000000000006,
        0.94300000000000006, 0.94400000000000006, 0.94500000000000006,
        0.94600000000000006, 0.94700000000000006, 0.94800000000000006,
        0.94900000000000007, 0.95000000000000007, 0.95100000000000007,
        0.95200000000000007, 0.95300000000000007, 0.95400000000000007,
        0.95500000000000007, 0.95600000000000007, 0.95700000000000007,
        0.95800000000000007, 0.95900000000000007, 0.96, 0.961, 0.962, 0.963,
        0.964, 0.965, 0.966, 0.967, 0.968, 0.969, 0.97, 0.971, 0.972, 0.973,
        0.974, 0.975, 0.976, 0.977, 0.978, 0.979, 0.98, 0.981, 0.982, 0.983,
        0.984, 0.985, 0.986, 0.987, 0.988, 0.989, 0.99, 0.991, 0.992, 0.993,
        0.994, 0.995, 0.996, 0.997, 0.998, 0.999, 1.0, 1.001, 1.002,
        1.0030000000000001, 1.004, 1.005, 1.006, 1.0070000000000001, 1.008,
        1.009, 1.01, 1.0110000000000001, 1.012, 1.013, 1.014, 1.0150000000000001,
        1.016, 1.017, 1.018, 1.0190000000000001, 1.02, 1.021, 1.0219999999999998,
        1.023, 1.024, 1.025, 1.0259999999999998, 1.027, 1.028, 1.029,
        1.0299999999999998, 1.031, 1.032, 1.033, 1.0339999999999998, 1.035,
        1.036, 1.037, 1.0379999999999998, 1.039, 1.04, 1.041, 1.0419999999999998,
        1.043, 1.044, 1.045, 1.0459999999999998, 1.047, 1.048, 1.049,
        1.0499999999999998, 1.051, 1.052, 1.053, 1.0539999999999998, 1.055,
        1.056, 1.057, 1.0579999999999998, 1.059, 1.06, 1.061, 1.0619999999999998,
        1.063, 1.064, 1.065, 1.0659999999999998, 1.067, 1.068, 1.069,
        1.0699999999999998, 1.071, 1.072, 1.073, 1.0739999999999998, 1.075,
        1.076, 1.077, 1.0779999999999998, 1.079, 1.08, 1.081, 1.0819999999999999,
        1.083, 1.084, 1.085, 1.0859999999999999, 1.087, 1.088, 1.089,
        1.0899999999999999, 1.091, 1.092, 1.093, 1.0939999999999999, 1.095,
        1.096, 1.097, 1.0979999999999999, 1.099, 1.1, 1.101, 1.1019999999999999,
        1.103, 1.104, 1.105, 1.1059999999999999, 1.107, 1.108, 1.109,
        1.1099999999999999, 1.111, 1.112, 1.113, 1.1139999999999999, 1.115,
        1.116, 1.117, 1.1179999999999999, 1.119, 1.12, 1.121, 1.122, 1.123,
        1.124, 1.125, 1.126, 1.127, 1.128, 1.129, 1.13, 1.131,
        1.1320000000000001, 1.133, 1.134, 1.135, 1.1360000000000001, 1.137,
        1.138, 1.139, 1.1400000000000001, 1.141, 1.142, 1.143,
        1.1440000000000001, 1.145, 1.146, 1.147, 1.148, 1.149, 1.15,
        1.1509999999999998, 1.152, 1.153, 1.154, 1.1549999999999998, 1.156,
        1.157, 1.158, 1.1589999999999998, 1.16, 1.161, 1.162, 1.1629999999999998,
        1.164, 1.165, 1.166, 1.1669999999999998, 1.168, 1.169, 1.17,
        1.1709999999999998, 1.172, 1.173, 1.174, 1.1749999999999998, 1.176,
        1.177, 1.178, 1.1789999999999998, 1.18, 1.181, 1.182, 1.1829999999999998,
        1.184, 1.185, 1.186, 1.1869999999999998, 1.188, 1.189, 1.19,
        1.1909999999999998, 1.192, 1.193, 1.194, 1.1949999999999998, 1.196,
        1.197, 1.198, 1.1989999999999998, 1.2, 1.201, 1.202, 1.2029999999999998,
        1.204, 1.205, 1.206, 1.2069999999999999, 1.208, 1.209, 1.21,
        1.2109999999999999, 1.212, 1.213, 1.214, 1.2149999999999999, 1.216,
        1.217, 1.218, 1.2189999999999999, 1.22, 1.221, 1.222, 1.2229999999999999,
        1.224, 1.225, 1.226, 1.2269999999999999, 1.228, 1.229, 1.23,
        1.2309999999999999, 1.232, 1.233, 1.234, 1.2349999999999999, 1.236,
        1.237, 1.238, 1.2389999999999999, 1.24, 1.241, 1.242, 1.2429999999999999,
        1.244, 1.245, 1.246, 1.247, 1.248, 1.249, 1.25, 1.251, 1.252, 1.253,
        1.254, 1.255, 1.256, 1.2570000000000001, 1.258, 1.259, 1.26,
        1.2610000000000001, 1.262, 1.263, 1.264, 1.2650000000000001, 1.266,
        1.267, 1.268, 1.2690000000000001, 1.27, 1.271, 1.272, 1.2730000000000001,
        1.274, 1.275, 1.276, 1.277, 1.278, 1.279, 1.2799999999999998, 1.281,
        1.282, 1.283, 1.2839999999999998, 1.285, 1.286, 1.287,
        1.2879999999999998, 1.289, 1.29, 1.291, 1.2919999999999998, 1.293, 1.294,
        1.295, 1.2959999999999998, 1.297, 1.298, 1.299, 1.2999999999999998,
        1.301, 1.302, 1.303, 1.3039999999999998, 1.305, 1.306, 1.307,
        1.3079999999999998, 1.309, 1.31, 1.311, 1.3119999999999998, 1.313, 1.314,
        1.315, 1.3159999999999998, 1.317, 1.318, 1.319, 1.3199999999999998,
        1.321, 1.322, 1.323, 1.3239999999999998, 1.325, 1.326, 1.327,
        1.3279999999999998, 1.329, 1.33, 1.331, 1.3319999999999999, 1.333, 1.334,
        1.335, 1.3359999999999999, 1.337, 1.338, 1.339, 1.3399999999999999,
        1.341, 1.342, 1.343, 1.3439999999999999, 1.345, 1.346, 1.347,
        1.3479999999999999, 1.349, 1.35, 1.351, 1.3519999999999999, 1.353, 1.354,
        1.355, 1.3559999999999999, 1.357, 1.358, 1.359, 1.3599999999999999,
        1.361, 1.362, 1.363, 1.3639999999999999, 1.365, 1.366, 1.367,
        1.3679999999999999, 1.369, 1.37, 1.371, 1.372, 1.373, 1.374, 1.375,
        1.376, 1.377, 1.378, 1.379, 1.38, 1.381, 1.3820000000000001, 1.383,
        1.384, 1.385, 1.3860000000000001, 1.387, 1.388, 1.389,
        1.3900000000000001, 1.391, 1.392, 1.393, 1.3940000000000001, 1.395,
        1.396, 1.397, 1.3980000000000001, 1.399, 1.4, 1.401, 1.4020000000000001,
        1.403, 1.404, 1.4049999999999998, 1.406, 1.407, 1.408,
        1.4089999999999998, 1.41, 1.411, 1.412, 1.4129999999999998, 1.414, 1.415,
        1.416, 1.4169999999999998, 1.418, 1.419, 1.42, 1.4209999999999998, 1.422,
        1.423, 1.424, 1.4249999999999998, 1.426, 1.427, 1.428,
        1.4289999999999998, 1.43, 1.431, 1.432, 1.4329999999999998, 1.434, 1.435,
        1.436, 1.4369999999999998, 1.438, 1.439, 1.44, 1.4409999999999998, 1.442,
        1.443, 1.444, 1.4449999999999998, 1.446, 1.447, 1.448,
        1.4489999999999998, 1.45, 1.451, 1.452, 1.4529999999999998, 1.454, 1.455,
        1.456, 1.4569999999999999, 1.458, 1.459, 1.46, 1.4609999999999999, 1.462,
        1.463, 1.464, 1.4649999999999999, 1.466, 1.467, 1.468,
        1.4689999999999999, 1.47, 1.471, 1.472, 1.4729999999999999, 1.474, 1.475,
        1.476, 1.4769999999999999, 1.478, 1.479, 1.48, 1.4809999999999999, 1.482,
        1.483, 1.484, 1.4849999999999999, 1.486, 1.487, 1.488,
        1.4889999999999999, 1.49, 1.491, 1.492, 1.4929999999999999, 1.494, 1.495,
        1.496, 1.497, 1.498, 1.499, 1.5, 1.501, 1.502, 1.503, 1.504, 1.505,
        1.506, 1.507, 1.508, 1.509, 1.51, 1.511, 1.512, 1.513, 1.514, 1.515,
        1.516, 1.517, 1.518, 1.519, 1.52, 1.521, 1.522, 1.523, 1.524, 1.525,
        1.526, 1.527, 1.528, 1.529, 1.53, 1.531, 1.532, 1.533, 1.534, 1.535,
        1.536, 1.537, 1.538, 1.539, 1.54, 1.541, 1.542, 1.543, 1.544, 1.545,
        1.546, 1.547, 1.548, 1.549, 1.55, 1.551, 1.552, 1.553, 1.554, 1.555,
        1.556, 1.557, 1.558, 1.559, 1.56, 1.561, 1.562, 1.563, 1.564, 1.565,
        1.5659999999999998, 1.567, 1.568, 1.569, 1.5699999999999998, 1.571,
        1.572, 1.573, 1.5739999999999998, 1.575, 1.576, 1.577,
        1.5779999999999998, 1.579, 1.58, 1.581, 1.5819999999999999, 1.583, 1.584,
        1.585, 1.5859999999999999, 1.587, 1.588, 1.589, 1.5899999999999999,
        1.591, 1.592, 1.593, 1.5939999999999999, 1.595, 1.596, 1.597,
        1.5979999999999999, 1.599, 1.6, 1.601, 1.6019999999999999, 1.603, 1.604,
        1.605, 1.6059999999999999, 1.607, 1.608, 1.609, 1.6099999999999999,
        1.611, 1.612, 1.613, 1.6139999999999999, 1.615, 1.616, 1.617,
        1.6179999999999999, 1.619, 1.62, 1.621, 1.622, 1.623, 1.624, 1.625,
        1.626, 1.627, 1.628, 1.629, 1.63, 1.631, 1.632, 1.633, 1.634, 1.635,
        1.636, 1.637, 1.638, 1.639, 1.64, 1.641, 1.642, 1.643, 1.644, 1.645,
        1.646, 1.647, 1.648, 1.649, 1.65, 1.651, 1.652, 1.653, 1.654, 1.655,
        1.656, 1.657, 1.658, 1.659, 1.66, 1.661, 1.662, 1.663, 1.664, 1.665,
        1.666, 1.667, 1.668, 1.669, 1.67, 1.671, 1.672, 1.673, 1.674, 1.675,
        1.676, 1.677, 1.678, 1.679, 1.68, 1.681, 1.682, 1.683, 1.684, 1.685,
        1.686, 1.687, 1.688, 1.689, 1.69, 1.691, 1.692, 1.693, 1.694,
        1.6949999999999998, 1.696, 1.697, 1.698, 1.6989999999999998, 1.7, 1.701,
        1.702, 1.7029999999999998, 1.704, 1.705, 1.706, 1.7069999999999999,
        1.708, 1.709, 1.71, 1.7109999999999999, 1.712, 1.713, 1.714,
        1.7149999999999999, 1.716, 1.717, 1.718, 1.7189999999999999, 1.72, 1.721,
        1.722, 1.7229999999999999, 1.724, 1.725, 1.726, 1.7269999999999999,
        1.728, 1.729, 1.73, 1.7309999999999999, 1.732, 1.733, 1.734,
        1.7349999999999999, 1.736, 1.737, 1.738, 1.7389999999999999, 1.74,
        1.7409999999999999, 1.742, 1.7429999999999999, 1.744, 1.7449999999999997,
        1.746, 1.747, 1.748, 1.749, 1.75, 1.751, 1.752, 1.753, 1.754, 1.755,
        1.756, 1.757, 1.758, 1.759, 1.76, 1.761, 1.762, 1.763, 1.764, 1.765,
        1.766, 1.767, 1.768, 1.769, 1.77, 1.771, 1.772, 1.773, 1.774, 1.775,
        1.776, 1.777, 1.778, 1.779, 1.78, 1.781, 1.782, 1.783, 1.784, 1.785,
        1.786, 1.787, 1.788, 1.789, 1.79, 1.791, 1.792, 1.793, 1.794, 1.795,
        1.796, 1.797, 1.798, 1.799, 1.8, 1.801, 1.802, 1.803, 1.804, 1.805,
        1.806, 1.807, 1.808, 1.809, 1.81, 1.811, 1.812, 1.813, 1.814, 1.815,
        1.816, 1.817, 1.818, 1.819, 1.82, 1.821, 1.822, 1.823, 1.824, 1.825,
        1.826, 1.827, 1.828, 1.829, 1.83, 1.831, 1.832, 1.833, 1.834, 1.835,
        1.8359999999999999, 1.837, 1.838, 1.839, 1.8399999999999999, 1.841,
        1.842, 1.843, 1.8439999999999999, 1.845, 1.846, 1.847,
        1.8479999999999999, 1.849, 1.85, 1.851, 1.8519999999999999, 1.853, 1.854,
        1.855, 1.8559999999999999, 1.857, 1.858, 1.859, 1.8599999999999999,
        1.861, 1.8619999999999999, 1.863, 1.8639999999999999, 1.865,
        1.8659999999999999, 1.867, 1.8679999999999999, 1.869, 1.8699999999999997,
        1.871, 1.872, 1.873, 1.874, 1.875, 1.876, 1.877, 1.878, 1.879, 1.88,
        1.881, 1.882, 1.883, 1.884, 1.885, 1.886, 1.887, 1.888, 1.889, 1.89,
        1.891, 1.892, 1.893, 1.894, 1.895, 1.896, 1.897, 1.898, 1.899, 1.9,
        1.901, 1.902, 1.903, 1.904, 1.905, 1.906, 1.907, 1.908, 1.909, 1.91,
        1.911, 1.912, 1.913, 1.914, 1.915, 1.916, 1.917, 1.918, 1.919, 1.92,
        1.921, 1.922, 1.923, 1.924, 1.925, 1.926, 1.927, 1.928, 1.929, 1.93,
        1.931, 1.932, 1.933, 1.934, 1.935, 1.936, 1.937, 1.938, 1.939, 1.94,
        1.941, 1.942, 1.943, 1.944, 1.945, 1.946, 1.947, 1.948, 1.949, 1.95,
        1.951, 1.952, 1.953, 1.954, 1.955, 1.956, 1.957, 1.958, 1.959, 1.96,
        1.961, 1.962, 1.963, 1.964, 1.965, 1.966, 1.967, 1.968, 1.969, 1.97,
        1.971, 1.972, 1.973, 1.974, 1.975, 1.976, 1.977, 1.978, 1.979, 1.98 } ;

      static real_T pDataValues0[] = { 2.1213203435596433, 2.1168155739656589,
        2.1123012787051643, 2.10777747809248, 2.1032441924847012,
        2.0987014422816053, 2.0941492479255608, 2.0895876299014344,
        2.0850166087365, 2.080436205000344, 2.0758464393047769,
        2.0712473323037357, 2.0666389046931948, 2.0620211772110695,
        2.057394170637127, 2.0527579057928884, 2.0481124035415372,
        2.043457684787827, 2.0387937704779828, 2.0341206815996125,
        2.0294384391816074, 2.0247470642940506, 2.0200465780481216,
        2.015337001596, 2.010618356130772, 2.0058906628863342,
        2.0011539431372984, 1.9964082181988956, 1.9916535094268797,
        1.9868898382174329, 1.9821172260070661, 1.9773356942725273,
        1.9725452645307013, 1.9677459583385135, 1.9629377972928337,
        1.9581208030303787, 1.9532949972276139, 1.9484604016006584,
        1.9436170379051836, 1.9387649279363179, 1.9339040935285479,
        1.9290345565556211, 1.9241563389304448, 1.91926946260499,
        1.9143739495701926, 1.9094698218558523, 1.904557101530536,
        1.8996358107014768, 1.894705971514475, 1.8897676061537989,
        1.8848207368420842, 1.8798653858402343, 1.87490157544732,
        1.86992932800048, 1.8649486658748202, 1.8599596114833108,
        1.8549621872766882, 1.8499564157433532, 1.8449423194092693,
        1.8399199208378609, 1.8348892426299142, 1.8298503074234718,
        1.8248031378937339, 1.819747756752955, 1.8146841867503409,
        1.8096124506719493, 1.8045325713405833, 1.7994445716156915,
        1.7943484743932634, 1.789244302605729, 1.7841320792218522,
        1.7790118272466293, 1.7738835697211863, 1.7687473297226728,
        1.7636031303641604, 1.7584509947945375, 1.7532909461984054,
        1.748123007795974, 1.7429472028429576, 1.7377635546304693,
        1.7325720864849172, 1.7273728217679007, 1.7221657838761006,
        1.7169509962411797, 1.7117284823296726, 1.706498265642884,
        1.7012603697167787, 1.6960148181218815, 1.6907616344631646,
        1.685500842379946, 1.68023246554578, 1.6749565276683558,
        1.6696730524893828, 1.6643820637844913, 1.6590835853631212,
        1.6537776410684168, 1.6484642547771184, 1.6431434503994551,
        1.6378152518790383, 1.6324796831927517, 1.627136768350645,
        1.6217865313958271, 1.6164289964043546, 1.6110641874851255,
        1.6056921287797714, 1.6003128444625485, 1.5949263587402249,
        1.5895326958519795, 1.5841318800692841, 1.5787239356958012,
        1.5733088870672731, 1.5678867585514078, 1.5624575745477742,
        1.5570213594876925, 1.5515781378341202, 1.5461279340815457,
        1.5406707727558773, 1.535206678414331, 1.5297356756453226,
        1.5242577890683562, 1.51877304333391, 1.5132814631233318,
        1.5077830731487241, 1.5022778981528309, 1.4967659629089309,
        1.4912472922207243, 1.4857219109222184, 1.4801898438776209,
        1.4746511159812241, 1.4691057521572934, 1.4635537773599567,
        1.4579952165730927, 1.452430094810214, 1.4468584371143594,
        1.4412802685579802, 1.4356956142428234, 1.4301044992998257,
        1.424506948888995, 1.4189029881992976, 1.4132926424485477,
        1.4076759368832921, 1.4020528967786956, 1.3964235474384297,
        1.3907879141945569, 1.3851460224074172, 1.3794978974655134,
        1.3738435647854004, 1.3681830498115628, 1.3625163780163103,
        1.3568435748996563, 1.3511646659892043, 1.3454796768400357,
        1.3397886330345923, 1.3340915601825607, 1.3283884839207594,
        1.3226794299130227, 1.3169644238500826, 1.3112434914494582,
        1.305516658455335, 1.2997839506384514, 1.2940453937959833,
        1.2883010137514272, 1.2825508363544831, 1.2767948874809396,
        1.2710331930325574, 1.2652657789369508, 1.2594926711474748,
        1.2537138956431033, 1.2479294784283175, 1.2421394455329844,
        1.236343823012243, 1.2305426369463839, 1.2247359134407352,
        1.2189236786255431, 1.2131059586558535, 1.2072827797113976,
        1.20145416799647, 1.1956201497398145, 1.189780751194502,
        1.1839359986378166, 1.1780859183711356, 1.1722305367198107,
        1.1663698800330478, 1.1605039746837937, 1.1546328470686111,
        1.1487565236075654, 1.1428750307441025, 1.1369883949449291,
        1.131096642699897, 1.1251998005218817, 1.1192978949466634,
        1.1133909525328061, 1.1074789998615422, 1.1015620635366465,
        1.0956401701843241, 1.0897133464530855, 1.0837816190136258,
        1.0778450145587097, 1.0719035598030477, 1.0659572814831746,
        1.0600062063573337, 1.0540503612053533, 1.0480897728285259,
        1.0421244680494892, 1.0361544737121056, 1.0301798166813383,
        1.024200523843134, 1.0182166221043016, 1.0122281383923875,
        1.0062350996555585, 1.0002375328624797, 0.9942354650021904,
        0.98822892308398647, 0.982217934137297, 0.97620252521156048,
        0.97018272337610767, 0.964158555720038, 0.95813004935209367,
        0.95209723140054414, 0.9460601290130608, 0.94001876935659245,
        0.93397317961724835, 0.92792338700017285, 0.92186941872942085,
        0.91581130204784034, 0.90974906421694668, 0.90368273251679887,
        0.89761233424587927, 0.89153789672097117, 0.88545944727703152,
        0.87937701326707352, 0.87329062206204033, 0.86720030105068058,
        0.86110607763943, 0.85500797925228345, 0.84890603333067283,
        0.84280026733334423, 0.83669070873623586, 0.83057738503234946,
        0.82446032373163192, 0.81833955236084932, 0.81221509846346229,
        0.80608698959950154, 0.79995525334544892, 0.79381991729410628,
        0.78768100905447425, 0.78153855625163182, 0.77539258652660459,
        0.76924312753624691, 0.76309020695311292, 0.75693385246533573,
        0.75077409177649868, 0.74461095260551691, 0.73844446268650488,
        0.73227464976865575, 0.72610154161611951, 0.71992516600787071,
        0.71374555073759027, 0.70756272361353545, 0.70137671245841893,
        0.69518754510927872, 0.68899524941735979, 0.6827998532479812,
        0.67660138448041407, 0.67039987100775966, 0.66419534073681663,
        0.65798782158796087, 0.65177734149501887, 0.64556392840514032,
        0.63934761027867193, 0.6331284150890375, 0.62690637082260348,
        0.62068150547855738, 0.61445384706878536, 0.60822342361773785,
        0.6019902631623103, 0.595754393751715, 0.5895158434473533,
        0.58327464032268961, 0.57703081246312993, 0.57078438796588726,
        0.56453539493986193, 0.5582838615055129, 0.552029815794729,
        0.54577328595070429, 0.53951430012781509, 0.53325288649148561,
        0.52698907321806565, 0.52072288849470694, 0.51445436051922844,
        0.50818351749999535, 0.50191038765579077, 0.4956349992156896,
        0.48935738041892757, 0.48307755951477943, 0.47679556476242951,
        0.47051142443084193, 0.4642251667986384, 0.45793682015396842,
        0.45164641279437978, 0.44535397302669572, 0.43905952916688534,
        0.4327631095399338, 0.42646474247971966, 0.42016445632888472,
        0.41386227943870457, 0.40755824016896552, 0.401252366887834,
        0.394944687971728, 0.38863523180519249, 0.38232402678077038,
        0.37601110129887233, 0.36969648376765296, 0.36338020260288112,
        0.35706228622781011, 0.35074276307305363, 0.34442166157645576,
        0.33809901018296146, 0.33177483734449181, 0.32544917151981473,
        0.31912204117441428, 0.31279347478036712, 0.30646350081621193,
        0.30013214776682018, 0.29379944412326864, 0.28746541838271567,
        0.28113009904826441, 0.27479351462884183, 0.26845569363906779,
        0.26211666459912475, 0.25577645603463334, 0.24943509647652207,
        0.24309261446089758, 0.23674903852891688, 0.23040439722666364,
        0.22405871910501102, 0.21771203271950057, 0.21136436663021091,
        0.2050157494016274, 0.19866620960251757, 0.19231577580580042,
        0.18596447658841669, 0.17961234053120084, 0.17325939621875702,
        0.16690567223932185, 0.16055119718464331, 0.15419599964984906,
        0.14784010823331586, 0.14148355153654513, 0.1351263581640319,
        0.12876855672313495, 0.12241017582394872, 0.11605124407917917,
        0.10969179010400712, 0.10333184251596401, 0.09697142993480401,
        0.09061058098237354, 0.084249324282480928, 0.0778876884607712,
        0.071525702144595513, 0.06516339396287954, 0.058800792546002012,
        0.05243792652565727, 0.046074824534730975, 0.039711515207172025,
        0.033348027177862345, 0.02698438908248595, 0.020620629557404225,
        0.014256777239524957, 0.0078928607661708349, 0.0015289087749579184,
        -0.0048350500963419054, -0.011198987209925123, -0.017562873928084789,
        -0.023926681613340758, -0.030290381628570503, -0.036653945337134036,
        -0.043017344103004743, -0.049380549290900896, -0.055743532266407256,
        -0.062106264396112477, -0.068468717047733385, -0.074830861590243117,
        -0.081192669394001313, -0.087554111830884893, -0.093915160274413018,
        -0.10027578609987768, -0.10663596068447483, -0.11299565540742879,
        -0.11935484165012346, -0.12571349079623276, -0.13207157423184565,
        -0.13842906334559668, -0.14478592952879693, -0.15114214417555863,
        -0.15749767868292591, -0.16385250445100558, -0.1702065928830917,
        -0.17655991538579641, -0.1829124433691805, -0.18926414824687809,
        -0.19561500143622729, -0.20196497435840077, -0.20831403843853052,
        -0.21466216510583813, -0.22100932579376562, -0.22735549194010007,
        -0.23370063498710375, -0.24004472638164498, -0.24638773757532259,
        -0.2527296400245963, -0.25907040519091695, -0.26541000454085145,
        -0.27174840954621282, -0.27808559168419034, -0.28442152243747459,
        -0.29075617329438719, -0.29708951574901066, -0.30342152130131583,
        -0.30975216145728585, -0.31608140772905213, -0.3224092316350175,
        -0.32873560469998475, -0.33506049845528485, -0.341383884438908,
        -0.34770573419562723, -0.35402601927712873, -0.36034471124214212,
        -0.36666178165656182, -0.3729772020935827, -0.37929094413382425,
        -0.38560297936545718, -0.39191327938433318, -0.39822181579411381,
        -0.40452856020639544, -0.41083348424083804, -0.41713655952529627,
        -0.42343775769593917, -0.429737050397387, -0.43603440928283393,
        -0.44232980601417482, -0.44862321226213447, -0.45491459970639664,
        -0.46120394003572784, -0.46749120494810642, -0.47377636615085295,
        -0.48005939536075004, -0.486340264304178, -0.49261894471723811,
        -0.49889540834587809, -0.50516962694602185, -0.51144157228369747,
        -0.51771121613516091, -0.52397853028702479, -0.53024348653638775,
        -0.53650605669095486, -0.54276621256917279, -0.54902392600034955,
        -0.55527916882478623, -0.56153191289389992, -0.56778213007035361,
        -0.57402979222818, -0.58027487125290955, -0.58651733904169889,
        -0.592757167503451, -0.59899432855895041, -0.6052287941409813,
        -0.61146053619446072, -0.61768952667655819, -0.62391573755682872,
        -0.63013914081733324, -0.63635970845276657, -0.64257741247058653,
        -0.64879222489113453, -0.65500411774776568, -0.66121306308697148,
        -0.66741903296850968, -0.67362199946552537, -0.67982193466468077,
        -0.68601881066627723, -0.69221259958438286, -0.69840327354695908,
        -0.70459080469598223, -0.71077516518757411, -0.71695632719212166,
        -0.72313426289440708, -0.72930894449372885, -0.73548034420403141,
        -0.74164843425402638, -0.74781318688731924, -0.75397457436253279,
        -0.76013256895343329, -0.766287142949057, -0.77243826865383058,
        -0.77858591838769842, -0.78473006448624716, -0.79087067930082977,
        -0.79700773519869073, -0.80314120456308813, -0.80927105979342051,
        -0.81539727330534884, -0.82151981753092385, -0.82763866491870608,
        -0.8337537879338931, -0.83986515905844061, -0.84597275079118961,
        -0.85207653564798846, -0.85817648616181463, -0.8642725748829011,
        -0.87036477437885862, -0.87645305723480071, -0.88253739605346437,
        -0.88861776345533494, -0.89469413207876891, -0.90076647458011838,
        -0.90683476363385285, -0.9128989719326811, -0.91895907218767658,
        -0.92501503712839694, -0.93106683950301206, -0.93711445207842048,
        -0.943157847640376, -0.94919699899360777, -0.95523187896194683,
        -0.96126246038844188, -0.96728871613548773, -0.97331061908494343,
        -0.97932814213825492, -0.98534125821658025, -0.99134994026090639,
        -0.99735416123217413, -1.0033538941113986, -1.0093491118997935,
        -1.0153397876188877, -1.0213258943106513, -1.0273074050376141,
        -1.0332842928829873, -1.0392565309507866, -1.0452240923659504,
        -1.0511869502744626, -1.0571450778434717, -1.0630984482614152,
        -1.0690470347381344, -1.0749908105050021, -1.0809297488150369,
        -1.0868638229430252, -1.0927930061856452, -1.0987172718615814,
        -1.1046365933116482, -1.1105509438989083, -1.1164602970087958,
        -1.1223646260492308, -1.1282639044507421, -1.1341581056665877,
        -1.140047203172871, -1.1459311704686646, -1.1518099810761249,
        -1.1576836085406141, -1.1635520264308177, -1.1694152083388663,
        -1.1752731278804509, -1.1811257586949431, -1.1869730744455145,
        -1.1928150488192533, -1.1986516555272859, -1.2044828683048916,
        -1.2103086609116216, -1.2161290071314206, -1.2219438807727399,
        -1.2277532556686575, -1.2335571056769958, -1.2393554046804411,
        -1.245148126586656, -1.2509352453284028, -1.2567167348636574,
        -1.2624925691757247, -1.2682627222733611, -1.2740271681908872,
        -1.2797858809883067, -1.2855388347514214, -1.29128600359195,
        -1.2970273616476415, -1.3027628830823934, -1.3084925420863698,
        -1.3142163128761146, -1.3199341696946696, -1.3256460868116893,
        -1.3313520385235542, -1.3370519991534937, -1.3427459430516917,
        -1.3484338445954125, -1.3541156781891077, -1.3597914182645374,
        -1.3654610392808784, -1.3711245157248477, -1.376781822110809,
        -1.3824329329808946, -1.3880778229051141, -1.3937164664814741,
        -1.3993488383360873, -1.4049749131232876, -1.4105946655257504,
        -1.4162080702545981, -1.4218151020495196, -1.4274157356788824,
        -1.4330099459398424, -1.4385977076584651, -1.4441789956898297,
        -1.4497537849181505, -1.455322050256886, -1.4608837666488523,
        -1.4664389090663339, -1.4719874525111982, -1.47752937201501,
        -1.483064642639141, -1.4885932394748829, -1.4941151376435606,
        -1.4996303122966388, -1.5051387386158432, -1.5106403918132629,
        -1.5161352471314689, -1.5216232798436209, -1.5271044652535826,
        -1.5325787786960263, -1.5380461955365536, -1.5435066911717952,
        -1.5489602410295311, -1.5544068205687962, -1.5598464052799927,
        -1.5652789706849981, -1.5707044923372757, -1.5761229458219881,
        -1.5815343067561043, -1.5869385507885088, -1.5923356536001136,
        -1.5977255909039636, -1.6031083384453517, -1.6084838720019206,
        -1.6138521673837798, -1.6192132004336095, -1.6245669470267703,
        -1.6299133830714105, -1.6352524845085779, -1.6405842273123235,
        -1.6459085874898149, -1.6512255410814403, -1.6565350641609164,
        -1.6618371328354022, -1.6671317232455922, -1.6724188115658405,
        -1.6776983740042597, -1.6829703868028272, -1.6882348262374935,
        -1.6934916686182906, -1.6987408902894374, -1.7039824676294437,
        -1.7092163770512214, -1.7144425950021867, -1.7196610979643685,
        -1.72487186245451, -1.7300748650241828, -1.7352700822598808,
        -1.7404574907831374, -1.7456370672506223, -1.7508087883542507,
        -1.7559726308212873, -1.7611285714144471, -1.7662765869320072,
        -1.7714166542079066, -1.7765487501118522, -1.7816728515494193,
        -1.7867889354621624, -1.7918969788277095, -1.7969969586598764,
        -1.8020888520087612, -1.8071726359608531, -1.8122482876391341,
        -1.8173157842031773, -1.8223751028492596, -1.8274262208104535,
        -1.8324691153567372, -1.8375037637950944, -1.8425301434696155,
        -1.8475482317616017, -1.8525580060896611, -1.8575594439098193,
        -1.8625525227156141, -1.8675372200382012, -1.8725135134464486,
        -1.8774813805470458, -1.8824407989845984, -1.8873917464417318,
        -1.8923342006391919, -1.8972681393359416, -1.9021935403292671,
        -1.9071103814548702, -1.9120186405869759, -1.9169182956384248,
        -1.9218093245607777, -1.926691705344413, -1.9315654160186262,
        -1.9364304346517285, -1.9412867393511406, -1.9461343082635019,
        -1.9509731195747595, -1.9558031515102716, -1.9606243823349021,
        -1.965436790353122, -1.9702403539091005, -1.9750350513868122,
        -1.9798208612101253, -1.9845977618429034, -1.9893657317891023,
        -1.9941247495928651, -1.9988747938386204, -2.0036158431511764,
        -2.00834787619582, -2.0130708716784085, -2.0177848083454717,
        -2.0224896649843025, -2.0271854204230557, -2.0318720535308357,
        -2.0365495432178036, -2.0412178684352638, -2.0458770081757609,
        -2.0505269414731742, -2.0551676474028104, -2.0597991050815021,
        -2.0644212936676962, -2.0690341923615523, -2.0736377804050345,
        -2.0782320370820049, -2.0828169417183142, -2.0873924736819007,
        -2.0919586123828795, -2.0965153372736314, -2.1010626278489033,
        -2.1056004636458958, -2.1101288242443572, -2.1146476892666679,
        -2.1191570383779452, -2.1236568512861265, -2.1281471077420604,
        -2.1326277875396018, -2.1370988705156972, -2.1415603365504823,
        -2.1460121655673654, -2.1504543375331253, -2.1548868324579957,
        -2.1593096303957569, -2.1637227114438242, -2.1681260557433415,
        -2.1725196434792675, -2.1769034548804629, -2.1812774702197846,
        -2.1856416698141721, -2.1899960340247349, -2.1943405432568381,
        -2.1986751779602, -2.2029999186289708, -2.2073147458018263,
        -2.2116196400620507, -2.2159145820376263, -2.2201995524013229,
        -2.2244745318707797, -2.2287395012085969, -2.2329944412224187,
        -2.2372393327650251, -2.2414741567344079, -2.2456988940738682,
        -2.2499135257720964, -2.2541180328632531, -2.2583123964270664,
        -2.2624965975889064, -2.2666706175198765, -2.2708344374368923,
        -2.2749880386027712, -2.2791314023263154, -2.2832645099623954,
        -2.2873873429120328, -2.2914998826224884, -2.2956021105873385,
        -2.299694008346564, -2.3037755574866345, -2.3078467396405822,
        -2.3119075364880968, -2.3159579297555983, -2.3199979012163245,
        -2.32402743269041, -2.3280465060449704, -2.3320551031941816,
        -2.336053206099364, -2.3400407967690606, -2.344017857259121,
        -2.3479843696727807, -2.3519403161607371, -2.3558856789212403,
        -2.359820440200163, -2.3637445822910892, -2.3676580875353821,
        -2.3715609383222778, -2.3754531170889521, -2.379334606320608,
        -2.38320538855055, -2.3870654463602663, -2.3909147623795022,
        -2.3947533192863415, -2.3985810998072856, -2.4023980867173278,
        -2.406204262840034, -2.4099996110476174, -2.4137841142610186,
        -2.41755775544998, -2.4213205176331196, -2.4250723838780166,
        -2.4288133373012775, -2.4325433610686207, -2.4362624383949432,
        -2.4399705525444046, -2.4436676868304965, -2.4473538246161213,
        -2.451028949313665, -2.4546930443850727, -2.4583460933419246,
        -2.4619880797455034, -2.465618987206879, -2.469238799386972,
        -2.4728474999966346, -2.4764450727967198, -2.4800315015981576,
        -2.4836067702620235, -2.4871708626996134, -2.4907237628725181,
        -2.4942654547926932, -2.4977959225225304, -2.501315150174932,
        -2.5048231219133794, -2.508319821952004, -2.5118052345556627,
        -2.5152793440400045, -2.5187421347715424, -2.5221935911677251,
        -2.5256336976970029, -2.529062438878904, -2.5324797992840975,
        -2.5358857635344672, -2.5392803163031803, -2.5426634423147565,
        -2.546035126345132, -2.5493953532217355, -2.5527441078235511,
        -2.55608137508119, -2.5594071399769538, -2.5627213875449075,
        -2.5660241028709416, -2.5693152710928429, -2.5725948774003595,
        -2.575862907035269, -2.5791193452914438, -2.5823641775149171,
        -2.58559738910395, -2.5888189655090947, -2.5920288922332628,
        -2.5952271548317905, -2.5984137389125, -2.6015886301357707,
        -2.6047518142145947, -2.6079032769146511, -2.6110430040543613,
        -2.6141709815049596, -2.6172871951905528, -2.6203916310881841,
        -2.6234842752278986, -2.6265651136928003, -2.6296341326191235,
        -2.6326913181962865, -2.6357366566669609, -2.6387701343271286,
        -2.6417917375261442, -2.6448014526667993, -2.6477992662053795,
        -2.6507851646517304, -2.6537591345693139, -2.6567211625752702,
        -2.6596712353404777, -2.6626093395896144, -2.6655354621012162,
        -2.6684495897077367, -2.6713517092956067, -2.6742418078052923,
        -2.6771198722313567, -2.6799858896225124, -2.682839847081687,
        -2.6856817317660777, -2.6885115308872076, -2.6913292317109856,
        -2.6941348215577618, -2.6969282878023884, -2.6997096178742708,
        -2.702478799257428, -2.7052358194905484, -2.7079806661670469,
        -2.7107133269351174, -2.7134337894977905, -2.7161420416129904,
        -2.7188380710935864, -2.7215218658074507, -2.7241934136775106,
        -2.7268527026818061, -2.7294997208535423, -2.73213445628114,
        -2.7347568971082947, -2.7373670315340273, -2.7399648478127379,
        -2.7425503342542563, -2.7451234792238992, -2.7476842711425178,
        -2.7502326984865526, -2.7527687497880851, -2.7552924136348893,
        -2.7578036786704816, -2.7603025335941744, -2.7627889671611232,
        -2.7652629681823826, -2.767724525524951, -2.7701736281118245,
        -2.7726102649220472, -2.7750344249907566, -2.7774460974092361,
        -2.7798452713249633, -2.7822319359416618, -2.7846060805193429,
        -2.7869676943743609, -2.7893167668794567, -2.7916532874638103,
        -2.7939772456130796, -2.7962886308694586, -2.7985874328317175,
        -2.8008736411552513, -2.8031472455521267, -2.805408235791127,
        -2.8076566016978006, -2.8098923331545045, -2.8121154201004517,
        -2.8143258525317529, -2.8165236205014663, -2.8187087141196412,
        -2.8208811235533586, -2.8230408390267816, -2.8251878508211914,
        -2.8273221492750404, -2.8294437247839888, -2.831552567800951,
        -2.8336486688361351, -2.8357320184570924, -2.8378026072887508,
        -2.8398604260134661, -2.8419054653710565, -2.8439377161588482,
        -2.8459571692317169, -2.8479638155021259, -2.8499576459401714,
        -2.8519386515736191, -2.8539068234879474, -2.8558621528263868,
        -2.8578046307899569, -2.859734248637511, -2.8616509976857722,
        -2.8635548693093735, -2.8654458549408948, -2.8673239460709041,
        -2.8691891342479949, -2.8710414110788225, -2.8728807682281459,
        -2.8747071974188594, -2.8765206904320371, -2.878321239106961,
        -2.8801088353411659, -2.8818834710904722, -2.8836451383690225,
        -2.8853938292493155, -2.8871295358622455, -2.8888522503971368,
        -2.8905619651017762, -2.892258672282451, -2.8939423643039808,
        -2.895613033589755, -2.8972706726217634, -2.8989152739406356,
        -2.9005468301456658, -2.902165333894855, -2.9037707779049393,
        -2.9053631549514236, -2.9069424578686136, -2.908508679549648,
        -2.9100618129465325, -2.91160185107017, -2.913128786990391,
        -2.9146426138359858, -2.9161433247947373, -2.9176309131134479,
        -2.9191053720979729, -2.92056669511325, -2.9220148755833271,
        -2.9234499069913955, -2.9248717828798148, -2.9262804968501479,
        -2.9276760425631827, -2.929058413738967, -2.9304276041568316,
        -2.9317836076554227, -2.9331264181327268, -2.9344560295460989,
        -2.9357724359122908, -2.937075631307474, -2.9383656098672728,
        -2.9396423657867863, -2.9409058933206143, -2.9421561867828845,
        -2.9433932405472794, -2.9446170490470593, -2.9458276067750866,
        -2.9470249082838551, -2.9482089481855089, -2.949379721151872,
        -2.9505372219144661, -2.951681445264541, -2.9528123860530933,
        -2.9539300391908907, -2.9550343996484969, -2.9561254624562912,
        -2.9572032227044929, -2.9582676755431829, -2.9593188161823245,
        -2.9603566398917875, -2.9613811420013669, -2.9623923179008038,
        -2.9633901630398105, -2.9643746729280833, -2.96534584313533,
        -2.9663036692912872, -2.9672481470857379, -2.9681792722685345,
        -2.969097040649614, -2.9700014480990209, -2.9708924905469236,
        -2.9717701639836327, -2.9726344644596177, -2.97348538808553,
        -2.974322931032213, -2.9751470895307262, -2.9759578598723557,
        -2.9767552384086389, -2.9775392215513721, -2.9783098057726329,
        -2.9790669876047935, -2.979810763640538, -2.9805411305328731,
        -2.9812580849951513, -2.981961623801078, -2.9826517437847295,
        -2.9833284418405666, -2.9839917149234507, -2.9846415600486522,
        -2.9852779742918711, -2.9859009547892423, -2.9865104987373563,
        -2.9871066033932658, -2.9876892660745002, -2.9882584841590796,
        -2.988814255085523, -2.9893565763528618, -2.9898854455206516,
        -2.9904008602089815, -2.9909028180984878, -2.9913913169303594,
        -2.9918663545063526, -2.9923279286887996, -2.9927760374006165,
        -2.9932106786253154, -2.9936318504070121, -2.9940395508504332,
        -2.9944337781209289, -2.9948145304444753, -2.9951818061076882,
        -2.9955356034578284, -2.9958759209028076, -2.9962027569111984,
        -2.9965161100122404, -2.9968159787958424, -2.997102361912598,
        -2.9973752580737822, -2.9976346660513631, -2.9978805846780046,
        -2.998113012847075, -2.9983319495126461, -2.9985373936895057,
        -2.9987293444531526, -2.9989078009398087, -2.9990727623464224,
        -2.9992242279306662, -2.9993621970109459, -2.9994866689664006,
        -2.999597643236906, -2.999695119323079, -2.999779096786277,
        -2.9998495752486014, -2.9999065543928998, -2.9999500339627652,
        -2.9999800137625408, -2.9999964936573162, -2.9999994735729332,
        -2.9999889534959818, -2.9999649334738021, -2.9999274136144831,
        -2.9998763940868662, -2.999811875120538, -2.9997338570058343,
        -2.9996423400938359, -2.9995373247963686, -2.9994188115860014,
        -2.9992868009960443, -2.9991412936205437, -2.9989822901142826,
        -2.9988097911927771, -2.9986237976322716, -2.9984243102697361,
        -2.9982113300028659, -2.997984857790069, -2.9977448946504714,
        -2.9974914416639065, -2.9972244999709128, -2.9969440707727264,
        -2.9966501553312792, -2.9963427549691906, -2.9960218710697593,
        -2.9956875050769649, -2.9953396584954532, -2.9949783328905331,
        -2.9946035298881681, -2.994215251174972, -2.993813498498199,
        -2.9933982736657345, -2.9929695785460897, -2.9925274150683925,
        -2.9920717852223766, -2.9916026910583775, -2.9911201346873164,
        -2.9906241182806967, -2.9901146440705908, -2.9895917143496331,
        -2.9890553314710062, -2.9885054978484313, -2.9879422159561586,
        -2.9873654883289564, -2.986775317562099, -2.9861717063113518,
        -2.9855546572929654, -2.9849241732836598, -2.9842802571206111,
        -2.9836229117014406, -2.9829521399842029, -2.9822679449873695,
        -2.981570329789816, -2.9808592975308095, -2.9801348514099941,
        -2.9793969946873773, -2.9786457306833114, -2.9778810627784846,
        -2.9771029944138996, -2.9763115290908639, -2.9755066703709696,
        -2.9746884218760807, -2.9738567872883124, -2.9730117703500194,
        -2.972153374863777, -2.971281604692364, -2.9703964637587426,
        -2.9694979560460473, -2.9685860855975617, -2.9676608565166993,
        -2.9667222729669911, -2.9657703391720611, -2.964805059415609,
        -2.963826438041393, -2.9628344794532069, -2.9618291881148635,
        -2.9608105685501713, -2.9597786253429175, -2.9587333631368438,
        -2.957674786635629, -2.9566029006028653, -2.9555177098620384,
        -2.9544192192965042, -2.9533074338494689, -2.9521823585239653,
        -2.9510439983828296, -2.9498923585486811, -2.9487274442038971,
        -2.9475492605905909, -2.946357813010585, -2.9451531068253933,
        -2.9439351474561906, -2.9427039403837925, -2.941459491148628,
        -2.9402018053507168, -2.9389308886496437, -2.9376467467645306,
        -2.9363493854740148, -2.9350388106162195, -2.9337150280887294,
        -2.9323780438485638, -2.9310278639121488, -2.9296644943552916,
        -2.9282879413131542, -2.9268982109802222, -2.9254953096102803,
        -2.9240792435163816, -2.9226500190708227, -2.9212076427051086,
        -2.9197521209099317, -2.9182834602351386, -2.9168016672896981,
        -2.9153067487416786, -2.9137987113182078, -2.9122775618054528,
        -2.9107433070485862, -2.9091959539517478, -2.9076355094780268,
        -2.9060619806494192, -2.904475374546803, -2.9028756983099031,
        -2.9012629591372585, -2.8996371642861942, -2.8979983210727838,
        -2.8963464368718181, -2.8946815191167752, -2.89300357529978,
        -2.8913126129715785, -2.8896086397414984, -2.8878916632774141,
        -2.88616169130572, -2.8844187316112846, -2.8826627920374244,
        -2.8808938804858641, -2.879112004916704, -2.8773171733483807,
        -2.8755093938576319, -2.873688674579463, -2.8718550237071083,
        -2.8700084494919929, -2.8681489602436976, -2.8662765643299219,
        -2.8643912701764429, -2.8624930862670821, -2.8605820211436637,
        -2.8586580834059774, -2.8567212817117404, -2.8547716247765549,
        -2.852809121373876, -2.8508337803349657, -2.8488456105488535,
        -2.846844620962302, -2.8448308205797597, -2.8428042184633262,
        -2.8407648237327066, -2.8387126455651739, -2.8366476931955256,
        -2.8345699759160459, -2.8324795030764576, -2.8303762840838855,
        -2.8282603284028114, -2.8261316455550314, -2.8239902451196164,
        -2.821836136732863, -2.8196693300882569, -2.8174898349364228,
        -2.8152976610850859, -2.8130928183990256, -2.81087531680003,
        -2.8086451662668508, -2.8064023768351642, -2.8041469585975172,
        -2.8018789217032891, -2.79959827635864, -2.7973050328264732,
        -2.794999201426378, -2.7926807925345938, -2.7903498165839555,
        -2.7880062840638513, -2.7856502055201733, -2.7832815915552716,
        -2.7809004528279049, -2.7785068000531927, -2.7761006440025686,
        -2.7736819955037313, -2.7712508654405958, -2.7688072647532422,
        -2.7663512044378686, -2.7638826955467439, -2.7614017491881535,
        -2.7589083765263513, -2.7564025887815093, -2.7538843972296716,
        -2.7513538132026918, -2.7488108480881959, -2.7462555133295221,
        -2.7436878204256727, -2.7411077809312614, -2.7385154064564619,
        -2.7359107086669541, -2.733293699283875, -2.7306643900837595,
        -2.728022792898499, -2.7253689196152728, -2.7227027821765071,
        -2.7200243925798167, -2.7173337628779493, -2.7146309051787356,
        -2.7119158316450291, -2.7091885544946548, -2.70644908600036,
        -2.7036974384897423, -2.7009336243452156, -2.6981576560039366,
        -2.6953695459577593, -2.6925693067531733, -2.6897569509912516,
        -2.686932491327588, -2.6840959404722482, -2.6812473111897046,
        -2.6783866162987868, -2.6755138686726148, -2.6726290812385494,
        -2.6697322669781269, -2.6668234389270093, -2.6639026101749179,
        -2.6609697938655739, -2.6580250031966481, -2.6550682514196957,
        -2.6520995518400907, -2.6491189178169767, -2.6461263627632037,
        -2.6431219001452648, -2.6401055434832341, -2.6370773063507134,
        -2.6340372023747642, -2.6309852452358498, -2.6279214486677711,
        -2.6248458264576069, -2.621758392445654, -2.61865916052536,
        -2.6155481446432622, -2.612425358798927, -2.6092908170448856,
        -2.6061445334865709, -2.6029865222822539, -2.5998167976429789,
        -2.5966353738325, -2.5934422651672224, -2.5902374860161284,
        -2.5870210508007174, -2.5837929739949437, -2.5805532701251468,
        -2.57730195376999, -2.5740390395603892, -2.5707645421794552,
        -2.5674784763624179, -2.5641808568965709, -2.5608716986211948,
        -2.5575510164274964, -2.5542188252585389, -2.5508751401091803,
        -2.5475199760259941, -2.5441533481072152, -2.540775271502663,
        -2.5373857614136766, -2.5339848330930446, -2.5305725018449405,
        -2.5271487830248494, -2.5237136920394989, -2.5202672443467922,
        -2.5168094554557392, -2.5133403409263844, -2.5098599163697362,
        -2.5063681974476988, -2.5028651998730029, -2.4993509394091324,
        -2.4958254318702511, -2.4922886931211377, -2.4887407390771128,
        -2.4851815857039603, -2.4816112490178659, -2.4780297450853381,
        -2.4744370900231418, -2.4708332999982128, -2.4672183912276049,
        -2.4635923799783996, -2.4599552825676421, -2.4563071153622635,
        -2.4526478947790116, -2.4489776372843717, -2.4452963593944967,
        -2.4416040776751298, -2.4379008087415346, -2.4341865692584141,
        -2.43046137593984, -2.4267252455491741, -2.4229781948990006,
        -2.4192202408510366, -2.4154514003160723, -2.4116716902538817,
        -2.4078811276731571, -2.4040797296314182, -2.4002675132349545,
        -2.3964444956387316, -2.3926106940463225, -2.3887661257098265,
        -2.3849108079297974, -2.3810447580551566, -2.3771679934831229,
        -2.3732805316591277, -2.3693823900767472, -2.3654735862776093,
        -2.3615541378513254, -2.3576240624354052, -2.3536833777151842,
        -2.3497321014237338, -2.3457702513417922, -2.3417978452976773,
        -2.3378149011672136, -2.3338214368736359, -2.3298174703875327,
        -2.3258030197267443, -2.3217781029562916, -2.3177427381882927,
        -2.3136969435818848, -2.309640737343134, -2.3055741377249634,
        -2.301497163027062, -2.2974098315958122, -2.2933121618241974,
        -2.2892041721517238, -2.2850858810643384, -2.2809573070943441,
        -2.2768184688203181, -2.2726693848670241, -2.2685100739053312,
        -2.2643405546521373, -2.2601608458702658, -2.2559709663684036,
        -2.2517709350009993, -2.2475607706681875, -2.2433404923156997,
        -2.2391101189347826, -2.2348696695621091, -2.2306191632796937,
        -2.2263586192148064, -2.2220880565398908, -2.2178074944724706,
        -2.213516952275068, -2.209216449255115, -2.2049060047648688,
        -2.2005856382013218, -2.1962553690061171, -2.1919152166654556,
        -2.1875652007100217, -2.1832053407148724, -2.1788356562993765,
        -2.174456167127103, -2.1700668929057474, -2.1656678533870348,
        -2.1612590683666375, -2.1568405576840797, -2.1524123412226515,
        -2.1479744389093187, -2.1435268707146369, -2.1390696566526546,
        -2.1346028167808271, -2.1301263711999252, -2.1256403400539479, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

      final23_vcontrol_1_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
      final23_vcontrol_1_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
      final23_vcontrol_1_DW.FromWorkspace1_IWORK.PrevIndex = 0;
    }

    /* Start for MATLABSystem: '<Root>/PWM2' */
    final23_vcontrol_1_DW.obj_p.matlabCodegenIsDeleted = false;
    final23_vcontrol_1_DW.objisempty_d = true;
    final23_vcontrol_1_DW.obj_p.isInitialized = 1;
    final23_vcontrol_1_DW.obj_p.PinNumber = 20U;
    ret = EXT_PWMBlock_init(final23_vcontrol_1_DW.obj_p.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_1_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_1_B.b[0], final23_vcontrol_1_DW.obj_p.PinNumber);
    }

    final23_vcontrol_1_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM2' */

    /* Start for MATLABSystem: '<Root>/PWM3' */
    final23_vcontrol_1_DW.obj.matlabCodegenIsDeleted = false;
    final23_vcontrol_1_DW.objisempty = true;
    final23_vcontrol_1_DW.obj.isInitialized = 1;
    final23_vcontrol_1_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(final23_vcontrol_1_DW.obj.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_1_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_1_B.b[0], final23_vcontrol_1_DW.obj.PinNumber);
    }

    final23_vcontrol_1_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM3' */
  }

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        final23_vcontrol_1_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for Delay: '<S5>/Delay' */
  final23_vcontrol_1_DW.Delay_DSTATE =
    final23_vcontrol_1_P.Delay_InitialCondition;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  final23_vcontrol_1_X.Integrator_CSTATE = final23_vcontrol_1_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S3>/Derivative' */
  final23_vcontrol_1_DW.TimeStampA = (rtInf);
  final23_vcontrol_1_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Delay: '<S6>/Delay' */
  final23_vcontrol_1_DW.Delay_DSTATE_e =
    final23_vcontrol_1_P.Delay_InitialCondition_o;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  final23_vcontrol_1_X.Integrator_CSTATE_l =
    final23_vcontrol_1_P.Integrator_IC_m;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  final23_vcontrol_1_DW.TimeStampA_a = (rtInf);
  final23_vcontrol_1_DW.TimeStampB_o = (rtInf);
  final23_vcon_MovingAverage_Init(&final23_vcontrol_1_DW.MovingAverage);
  final23_vcon_MovingAverage_Init(&final23_vcontrol_1_DW.MovingAverage_p);
}

/* Model terminate function */
void final23_vcontrol_1_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper
    (&final23_vcontrol_1_DW.QuadEncoder2axis_DSTATE,
     &final23_vcontrol_1_P.QuadEncoder2axis_P1, 1,
     &final23_vcontrol_1_P.QuadEncoder2axis_P2, 1,
     &final23_vcontrol_1_P.QuadEncoder2axis_P3, 1,
     &final23_vcontrol_1_P.QuadEncoder2axis_P4, 1,
     &final23_vcontrol_1_P.QuadEncoder2axis_P5, 1,
     &final23_vcontrol_1_P.QuadEncoder2axis_P6, 1);
  final23_vcon_MovingAverage_Term(&final23_vcontrol_1_DW.MovingAverage);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!final23_vcontrol_1_DW.obj_g.matlabCodegenIsDeleted) {
    final23_vcontrol_1_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_1_DW.obj_g.isInitialized == 1) &&
        final23_vcontrol_1_DW.obj_g.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_1_DW.obj_g.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */

  /* Terminate for MATLABSystem: '<Root>/PWM1' */
  if (!final23_vcontrol_1_DW.obj_e.matlabCodegenIsDeleted) {
    final23_vcontrol_1_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_1_DW.obj_e.isInitialized == 1) &&
        final23_vcontrol_1_DW.obj_e.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_1_DW.obj_e.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM1' */
  final23_vcon_MovingAverage_Term(&final23_vcontrol_1_DW.MovingAverage_p);

  /* Terminate for MATLABSystem: '<Root>/PWM2' */
  if (!final23_vcontrol_1_DW.obj_p.matlabCodegenIsDeleted) {
    final23_vcontrol_1_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_1_DW.obj_p.isInitialized == 1) &&
        final23_vcontrol_1_DW.obj_p.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_1_DW.obj_p.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM2' */

  /* Terminate for MATLABSystem: '<Root>/PWM3' */
  if (!final23_vcontrol_1_DW.obj.matlabCodegenIsDeleted) {
    final23_vcontrol_1_DW.obj.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_1_DW.obj.isInitialized == 1) &&
        final23_vcontrol_1_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_1_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM3' */
}
