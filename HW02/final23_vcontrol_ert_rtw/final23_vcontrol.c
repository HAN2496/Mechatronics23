/*
 * final23_vcontrol.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_vcontrol".
 *
 * Model version              : 1.17
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 17:46:37 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "final23_vcontrol.h"
#include "final23_vcontrol_private.h"

/* Block signals (default storage) */
B_final23_vcontrol_T final23_vcontrol_B;

/* Continuous states */
X_final23_vcontrol_T final23_vcontrol_X;

/* Block states (default storage) */
DW_final23_vcontrol_T final23_vcontrol_DW;

/* Real-time model */
static RT_MODEL_final23_vcontrol_T final23_vcontrol_M_;
RT_MODEL_final23_vcontrol_T *const final23_vcontrol_M = &final23_vcontrol_M_;
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
  final23_vcontrol_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  final23_vcontrol_step();
  final23_vcontrol_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  final23_vcontrol_step();
  final23_vcontrol_derivatives();

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

  /* InitializeConditions for MATLABSystem: '<S3>/Moving Average' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pCumSum = 0.0;
    for (i = 0; i < 19; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<S3>/Moving Average' */
}

/*
 * Start for atomic system:
 *    synthesized block
 *    synthesized block
 */
void final23_vco_MovingAverage_Start(DW_MovingAverage_final23_vcon_T *localDW)
{
  /* Start for MATLABSystem: '<S3>/Moving Average' */
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
void final23_vcontrol_MovingAverage(real_T rtu_0,
  B_MovingAverage_final23_vcont_T *localB, DW_MovingAverage_final23_vcon_T
  *localDW)
{
  g_dsp_private_SlidingWindowAv_T *obj;
  real_T csum;
  real_T cumRevIndex;
  real_T z;
  int32_T i;

  /* MATLABSystem: '<S3>/Moving Average' */
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

  /* MATLABSystem: '<S3>/Moving Average' */
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

  /* Terminate for MATLABSystem: '<S3>/Moving Average' */
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

  /* End of Terminate for MATLABSystem: '<S3>/Moving Average' */
}

/* Model step function */
void final23_vcontrol_step(void)
{
  /* local block i/o variables */
  real_T rtb_CastToDouble;
  real_T rtb_CastToDouble1;
  if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
    /* set solver stop time */
    if (!(final23_vcontrol_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&final23_vcontrol_M->solverInfo,
                            ((final23_vcontrol_M->Timing.clockTickH0 + 1) *
        final23_vcontrol_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&final23_vcontrol_M->solverInfo,
                            ((final23_vcontrol_M->Timing.clockTick0 + 1) *
        final23_vcontrol_M->Timing.stepSize0 +
        final23_vcontrol_M->Timing.clockTickH0 *
        final23_vcontrol_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(final23_vcontrol_M)) {
    final23_vcontrol_M->Timing.t[0] = rtsiGetT(&final23_vcontrol_M->solverInfo);
  }

  {
    real_T *lastU;
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
      /* FromWorkspace: '<Root>/From Workspace' */
      {
        real_T *pDataValues = (real_T *)
          final23_vcontrol_DW.FromWorkspace_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          final23_vcontrol_DW.FromWorkspace_PWORK.TimePtr;
        int_T currTimeIndex = final23_vcontrol_DW.FromWorkspace_IWORK.PrevIndex;
        real_T t = (((final23_vcontrol_M->Timing.clockTick1+
                      final23_vcontrol_M->Timing.clockTickH1* 4294967296.0)) *
                    0.001);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[10000]) {
          currTimeIndex = 9999;
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

        final23_vcontrol_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              final23_vcontrol_B.FromWorkspace = pDataValues[currTimeIndex];
            } else {
              final23_vcontrol_B.FromWorkspace = pDataValues[currTimeIndex + 1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex = currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            final23_vcontrol_B.FromWorkspace = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 10001;
          }
        }
      }
    }

    /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
    Quad_Encoder_sfn_Outputs_wrapper(&final23_vcontrol_B.QuadEncoder2axis_o1,
      &final23_vcontrol_B.QuadEncoder2axis_o2,
      &final23_vcontrol_DW.QuadEncoder2axis_DSTATE,
      &final23_vcontrol_P.QuadEncoder2axis_P1, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P2, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P3, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P4, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P5, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P6, 1);

    /* Gain: '<S3>/Encoder Gain1' */
    final23_vcontrol_B.EncoderGain1 = (int64_T)
      final23_vcontrol_P.EncoderGain1_Gain *
      final23_vcontrol_B.QuadEncoder2axis_o1;
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
      /* Delay: '<S3>/Delay' */
      final23_vcontrol_B.Delay = final23_vcontrol_DW.Delay_DSTATE;
    }

    /* Gain: '<S3>/Gain' incorporates:
     *  Delay: '<S3>/Delay'
     *  Gain: '<S3>/Encoder Gain1'
     *  Sum: '<S3>/Sum3'
     */
    final23_vcontrol_B.u = (uint64_T)final23_vcontrol_P.Gain_Gain;
    final23_vcontrol_B.u1 = (uint64_T)(final23_vcontrol_B.EncoderGain1 -
      final23_vcontrol_B.Delay);
    sMultiWordMul(&final23_vcontrol_B.u, 1, &final23_vcontrol_B.u1, 1,
                  &final23_vcontrol_B.r.chunks[0U], 2);

    /* DataTypeConversion: '<S3>/Cast To Double' */
    rtb_CastToDouble = sMultiWord2Double(&final23_vcontrol_B.r.chunks[0U], 2, 0)
      * 4.0389678347315804E-28;
    final23_vcontrol_MovingAverage(rtb_CastToDouble,
      &final23_vcontrol_B.MovingAverage, &final23_vcontrol_DW.MovingAverage);

    /* Sum: '<Root>/Sum1' */
    final23_vcontrol_B.Sum1 = final23_vcontrol_B.FromWorkspace -
      final23_vcontrol_B.MovingAverage.MovingAverage;

    /* Derivative: '<S5>/Derivative' incorporates:
     *  Derivative: '<S6>/Derivative'
     */
    final23_vcontrol_B.Sum_d = final23_vcontrol_M->Timing.t[0];
    if ((final23_vcontrol_DW.TimeStampA >= final23_vcontrol_B.Sum_d) &&
        (final23_vcontrol_DW.TimeStampB >= final23_vcontrol_B.Sum_d)) {
      final23_vcontrol_B.Switch = 0.0;
    } else {
      final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampA;
      lastU = &final23_vcontrol_DW.LastUAtTimeA;
      if (final23_vcontrol_DW.TimeStampA < final23_vcontrol_DW.TimeStampB) {
        if (final23_vcontrol_DW.TimeStampB < final23_vcontrol_B.Sum_d) {
          final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampB;
          lastU = &final23_vcontrol_DW.LastUAtTimeB;
        }
      } else if (final23_vcontrol_DW.TimeStampA >= final23_vcontrol_B.Sum_d) {
        final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampB;
        lastU = &final23_vcontrol_DW.LastUAtTimeB;
      }

      final23_vcontrol_B.Switch = (final23_vcontrol_B.Sum1 - *lastU) /
        (final23_vcontrol_B.Sum_d - final23_vcontrol_B.Switch);
    }

    /* End of Derivative: '<S5>/Derivative' */

    /* Sum: '<S5>/Sum' incorporates:
     *  Gain: '<S5>/D Gain'
     *  Gain: '<S5>/I Gain'
     *  Gain: '<S5>/P Gain'
     *  Integrator: '<S5>/Integrator'
     */
    final23_vcontrol_B.Sum = (final23_vcontrol_P.PGain_Gain *
      final23_vcontrol_B.Sum1 + final23_vcontrol_P.IGain_Gain *
      final23_vcontrol_X.Integrator_CSTATE) + final23_vcontrol_P.DGain_Gain *
      final23_vcontrol_B.Switch;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    if (final23_vcontrol_B.Sum > final23_vcontrol_P.Switch1_Threshold) {
      final23_vcontrol_B.Switch = final23_vcontrol_B.Sum;
    } else {
      final23_vcontrol_B.Switch = final23_vcontrol_P.Constant_Value;
    }

    /* End of Switch: '<S1>/Switch1' */

    /* Gain: '<S1>/GPIO19 Gain' */
    final23_vcontrol_B.Switch *= final23_vcontrol_P.GPIO19Gain_Gain;

    /* MATLABSystem: '<Root>/PWM' */
    if (!(final23_vcontrol_B.Switch < 1.0)) {
      final23_vcontrol_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_B.Switch > 0.0)) {
      final23_vcontrol_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_DW.obj_g.PinNumber,
      final23_vcontrol_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM' */

    /* Switch: '<S1>/Switch' incorporates:
     *  Abs: '<S1>/Abs'
     *  Constant: '<S1>/Constant'
     */
    if (final23_vcontrol_B.Sum > final23_vcontrol_P.Switch_Threshold) {
      final23_vcontrol_B.Sum = final23_vcontrol_P.Constant_Value;
    } else {
      final23_vcontrol_B.Sum = fabs(final23_vcontrol_B.Sum);
    }

    /* End of Switch: '<S1>/Switch' */

    /* Gain: '<S1>/GPIO26 Gain' */
    final23_vcontrol_B.Switch = final23_vcontrol_P.GPIO26Gain_Gain *
      final23_vcontrol_B.Sum;

    /* MATLABSystem: '<Root>/PWM1' */
    if (!(final23_vcontrol_B.Switch < 1.0)) {
      final23_vcontrol_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_B.Switch > 0.0)) {
      final23_vcontrol_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_DW.obj_e.PinNumber,
      final23_vcontrol_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM1' */
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
      /* Delay: '<S4>/Delay1' */
      final23_vcontrol_B.Delay1 = final23_vcontrol_DW.Delay1_DSTATE;
    }

    /* Gain: '<S4>/Encoder Gain2' */
    final23_vcontrol_B.EncoderGain2 = (int64_T)
      final23_vcontrol_P.EncoderGain2_Gain *
      final23_vcontrol_B.QuadEncoder2axis_o2;

    /* Gain: '<S4>/Gain1' incorporates:
     *  Delay: '<S4>/Delay1'
     *  Gain: '<S4>/Encoder Gain2'
     *  Sum: '<S4>/Sum4'
     */
    final23_vcontrol_B.u = (uint64_T)final23_vcontrol_P.Gain1_Gain;
    final23_vcontrol_B.u1 = (uint64_T)(final23_vcontrol_B.EncoderGain2 -
      final23_vcontrol_B.Delay1);
    sMultiWordMul(&final23_vcontrol_B.u, 1, &final23_vcontrol_B.u1, 1,
                  &final23_vcontrol_B.r1.chunks[0U], 2);

    /* DataTypeConversion: '<S4>/Cast To Double1' */
    rtb_CastToDouble1 = sMultiWord2Double(&final23_vcontrol_B.r1.chunks[0U], 2,
      0) * 4.0389678347315804E-28;
    final23_vcontrol_MovingAverage(rtb_CastToDouble1,
      &final23_vcontrol_B.MovingAverage1, &final23_vcontrol_DW.MovingAverage1);
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
    }

    /* Sum: '<Root>/Sum2' */
    final23_vcontrol_B.Sum2 = final23_vcontrol_B.FromWorkspace -
      final23_vcontrol_B.MovingAverage1.MovingAverage;

    /* Derivative: '<S6>/Derivative' */
    if ((final23_vcontrol_DW.TimeStampA_a >= final23_vcontrol_B.Sum_d) &&
        (final23_vcontrol_DW.TimeStampB_o >= final23_vcontrol_B.Sum_d)) {
      final23_vcontrol_B.Switch = 0.0;
    } else {
      final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampA_a;
      lastU = &final23_vcontrol_DW.LastUAtTimeA_i;
      if (final23_vcontrol_DW.TimeStampA_a < final23_vcontrol_DW.TimeStampB_o) {
        if (final23_vcontrol_DW.TimeStampB_o < final23_vcontrol_B.Sum_d) {
          final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampB_o;
          lastU = &final23_vcontrol_DW.LastUAtTimeB_m;
        }
      } else if (final23_vcontrol_DW.TimeStampA_a >= final23_vcontrol_B.Sum_d) {
        final23_vcontrol_B.Switch = final23_vcontrol_DW.TimeStampB_o;
        lastU = &final23_vcontrol_DW.LastUAtTimeB_m;
      }

      final23_vcontrol_B.Switch = (final23_vcontrol_B.Sum2 - *lastU) /
        (final23_vcontrol_B.Sum_d - final23_vcontrol_B.Switch);
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Gain: '<S6>/D Gain'
     *  Gain: '<S6>/I Gain'
     *  Gain: '<S6>/P Gain'
     *  Integrator: '<S6>/Integrator'
     */
    final23_vcontrol_B.Sum_d = (final23_vcontrol_P.PGain_Gain_i *
      final23_vcontrol_B.Sum2 + final23_vcontrol_P.IGain_Gain_j *
      final23_vcontrol_X.Integrator_CSTATE_l) + final23_vcontrol_P.DGain_Gain_h *
      final23_vcontrol_B.Switch;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Constant: '<S2>/Constant'
     */
    if (final23_vcontrol_B.Sum_d > final23_vcontrol_P.Switch1_Threshold_c) {
      final23_vcontrol_B.Switch = final23_vcontrol_B.Sum_d;
    } else {
      final23_vcontrol_B.Switch = final23_vcontrol_P.Constant_Value_e;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Gain: '<S2>/GPIO20 Gain' */
    final23_vcontrol_B.Switch *= final23_vcontrol_P.GPIO20Gain_Gain;

    /* MATLABSystem: '<Root>/PWM2' */
    if (!(final23_vcontrol_B.Switch < 1.0)) {
      final23_vcontrol_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_B.Switch > 0.0)) {
      final23_vcontrol_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_DW.obj_p.PinNumber,
      final23_vcontrol_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM2' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Abs: '<S2>/Abs'
     *  Constant: '<S2>/Constant'
     */
    if (final23_vcontrol_B.Sum_d > final23_vcontrol_P.Switch_Threshold_m) {
      final23_vcontrol_B.Sum_d = final23_vcontrol_P.Constant_Value_e;
    } else {
      final23_vcontrol_B.Sum_d = fabs(final23_vcontrol_B.Sum_d);
    }

    /* End of Switch: '<S2>/Switch' */

    /* Gain: '<S2>/GPIO21 Gain' */
    final23_vcontrol_B.Switch = final23_vcontrol_P.GPIO21Gain_Gain *
      final23_vcontrol_B.Sum_d;

    /* MATLABSystem: '<Root>/PWM3' */
    if (!(final23_vcontrol_B.Switch < 1.0)) {
      final23_vcontrol_B.Switch = 1.0;
    }

    if (!(final23_vcontrol_B.Switch > 0.0)) {
      final23_vcontrol_B.Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(final23_vcontrol_DW.obj.PinNumber,
      final23_vcontrol_B.Switch);

    /* End of MATLABSystem: '<Root>/PWM3' */
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
    }
  }

  if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
    real_T *lastU;

    /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Update_wrapper(&final23_vcontrol_B.QuadEncoder2axis_o1,
      &final23_vcontrol_B.QuadEncoder2axis_o2,
      &final23_vcontrol_DW.QuadEncoder2axis_DSTATE,
      &final23_vcontrol_P.QuadEncoder2axis_P1, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P2, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P3, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P4, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P5, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P6, 1);
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
      /* Update for Delay: '<S3>/Delay' incorporates:
       *  Gain: '<S3>/Encoder Gain1'
       */
      final23_vcontrol_DW.Delay_DSTATE = final23_vcontrol_B.EncoderGain1;
    }

    /* Update for Derivative: '<S5>/Derivative' */
    if (final23_vcontrol_DW.TimeStampA == (rtInf)) {
      final23_vcontrol_DW.TimeStampA = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeA;
    } else if (final23_vcontrol_DW.TimeStampB == (rtInf)) {
      final23_vcontrol_DW.TimeStampB = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeB;
    } else if (final23_vcontrol_DW.TimeStampA < final23_vcontrol_DW.TimeStampB)
    {
      final23_vcontrol_DW.TimeStampA = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeA;
    } else {
      final23_vcontrol_DW.TimeStampB = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeB;
    }

    *lastU = final23_vcontrol_B.Sum1;

    /* End of Update for Derivative: '<S5>/Derivative' */
    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
      /* Update for Delay: '<S4>/Delay1' incorporates:
       *  Gain: '<S4>/Encoder Gain2'
       */
      final23_vcontrol_DW.Delay1_DSTATE = final23_vcontrol_B.EncoderGain2;
    }

    /* Update for Derivative: '<S6>/Derivative' */
    if (final23_vcontrol_DW.TimeStampA_a == (rtInf)) {
      final23_vcontrol_DW.TimeStampA_a = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeA_i;
    } else if (final23_vcontrol_DW.TimeStampB_o == (rtInf)) {
      final23_vcontrol_DW.TimeStampB_o = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeB_m;
    } else if (final23_vcontrol_DW.TimeStampA_a <
               final23_vcontrol_DW.TimeStampB_o) {
      final23_vcontrol_DW.TimeStampA_a = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeA_i;
    } else {
      final23_vcontrol_DW.TimeStampB_o = final23_vcontrol_M->Timing.t[0];
      lastU = &final23_vcontrol_DW.LastUAtTimeB_m;
    }

    *lastU = final23_vcontrol_B.Sum2;

    /* End of Update for Derivative: '<S6>/Derivative' */

    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, (real_T)final23_vcontrol_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(final23_vcontrol_M)) {/* Sample time: [0.001s, 0.0s] */
      rtExtModeUpload(1, (real_T)(((final23_vcontrol_M->Timing.clockTick1+
        final23_vcontrol_M->Timing.clockTickH1* 4294967296.0)) * 0.001));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(final23_vcontrol_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(final23_vcontrol_M)!=-1) &&
          !((rtmGetTFinal(final23_vcontrol_M)-
             (((final23_vcontrol_M->Timing.clockTick1+
                final23_vcontrol_M->Timing.clockTickH1* 4294967296.0)) * 0.001))
            > (((final23_vcontrol_M->Timing.clockTick1+
                 final23_vcontrol_M->Timing.clockTickH1* 4294967296.0)) * 0.001)
            * (DBL_EPSILON))) {
        rtmSetErrorStatus(final23_vcontrol_M, "Simulation finished");
      }

      if (rtmGetStopRequested(final23_vcontrol_M)) {
        rtmSetErrorStatus(final23_vcontrol_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&final23_vcontrol_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++final23_vcontrol_M->Timing.clockTick0)) {
      ++final23_vcontrol_M->Timing.clockTickH0;
    }

    final23_vcontrol_M->Timing.t[0] = rtsiGetSolverStopTime
      (&final23_vcontrol_M->solverInfo);

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
      final23_vcontrol_M->Timing.clockTick1++;
      if (!final23_vcontrol_M->Timing.clockTick1) {
        final23_vcontrol_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void final23_vcontrol_derivatives(void)
{
  XDot_final23_vcontrol_T *_rtXdot;
  _rtXdot = ((XDot_final23_vcontrol_T *) final23_vcontrol_M->derivs);

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = final23_vcontrol_B.Sum1;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE_l = final23_vcontrol_B.Sum2;
}

/* Model initialize function */
void final23_vcontrol_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)final23_vcontrol_M, 0,
                sizeof(RT_MODEL_final23_vcontrol_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&final23_vcontrol_M->solverInfo,
                          &final23_vcontrol_M->Timing.simTimeStep);
    rtsiSetTPtr(&final23_vcontrol_M->solverInfo, &rtmGetTPtr(final23_vcontrol_M));
    rtsiSetStepSizePtr(&final23_vcontrol_M->solverInfo,
                       &final23_vcontrol_M->Timing.stepSize0);
    rtsiSetdXPtr(&final23_vcontrol_M->solverInfo, &final23_vcontrol_M->derivs);
    rtsiSetContStatesPtr(&final23_vcontrol_M->solverInfo, (real_T **)
                         &final23_vcontrol_M->contStates);
    rtsiSetNumContStatesPtr(&final23_vcontrol_M->solverInfo,
      &final23_vcontrol_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&final23_vcontrol_M->solverInfo,
      &final23_vcontrol_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&final23_vcontrol_M->solverInfo,
      &final23_vcontrol_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&final23_vcontrol_M->solverInfo,
      &final23_vcontrol_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&final23_vcontrol_M->solverInfo, (&rtmGetErrorStatus
      (final23_vcontrol_M)));
    rtsiSetRTModelPtr(&final23_vcontrol_M->solverInfo, final23_vcontrol_M);
  }

  rtsiSetSimTimeStep(&final23_vcontrol_M->solverInfo, MAJOR_TIME_STEP);
  final23_vcontrol_M->intgData.y = final23_vcontrol_M->odeY;
  final23_vcontrol_M->intgData.f[0] = final23_vcontrol_M->odeF[0];
  final23_vcontrol_M->intgData.f[1] = final23_vcontrol_M->odeF[1];
  final23_vcontrol_M->intgData.f[2] = final23_vcontrol_M->odeF[2];
  final23_vcontrol_M->contStates = ((X_final23_vcontrol_T *) &final23_vcontrol_X);
  rtsiSetSolverData(&final23_vcontrol_M->solverInfo, (void *)
                    &final23_vcontrol_M->intgData);
  rtsiSetSolverName(&final23_vcontrol_M->solverInfo,"ode3");
  rtmSetTPtr(final23_vcontrol_M, &final23_vcontrol_M->Timing.tArray[0]);
  rtmSetTFinal(final23_vcontrol_M, 20.0);
  final23_vcontrol_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  final23_vcontrol_M->Sizes.checksums[0] = (3167250059U);
  final23_vcontrol_M->Sizes.checksums[1] = (4214581175U);
  final23_vcontrol_M->Sizes.checksums[2] = (1358953634U);
  final23_vcontrol_M->Sizes.checksums[3] = (1405019215U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[9];
    final23_vcontrol_M->extModeInfo = (&rt_ExtModeInfo);
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
    rteiSetModelMappingInfoPtr(final23_vcontrol_M->extModeInfo,
      &final23_vcontrol_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(final23_vcontrol_M->extModeInfo,
                        final23_vcontrol_M->Sizes.checksums);
    rteiSetTPtr(final23_vcontrol_M->extModeInfo, rtmGetTPtr(final23_vcontrol_M));
  }

  /* block I/O */
  (void) memset(((void *) &final23_vcontrol_B), 0,
                sizeof(B_final23_vcontrol_T));

  {
    final23_vcontrol_B.EncoderGain1 = (0LL);
    final23_vcontrol_B.Delay = (0LL);
    final23_vcontrol_B.EncoderGain2 = (0LL);
    final23_vcontrol_B.Delay1 = (0LL);
  }

  /* states (continuous) */
  {
    (void) memset((void *)&final23_vcontrol_X, 0,
                  sizeof(X_final23_vcontrol_T));
  }

  /* states (dwork) */
  (void) memset((void *)&final23_vcontrol_DW, 0,
                sizeof(DW_final23_vcontrol_T));

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
        0.994, 0.995, 0.996, 0.997, 0.998, 0.999, 1.0, 1.0010000000000001, 1.002,
        1.0030000000000001, 1.004, 1.0050000000000001, 1.006, 1.0070000000000001,
        1.008, 1.0090000000000001, 1.01, 1.0110000000000001, 1.012,
        1.0130000000000001, 1.014, 1.0150000000000001, 1.016, 1.0170000000000001,
        1.018, 1.0190000000000001, 1.02, 1.0210000000000001, 1.022,
        1.0230000000000001, 1.024, 1.025, 1.026, 1.027, 1.028, 1.029, 1.03,
        1.031, 1.032, 1.033, 1.034, 1.035, 1.036, 1.037, 1.038, 1.039, 1.04,
        1.041, 1.042, 1.043, 1.044, 1.045, 1.046, 1.047, 1.048, 1.049, 1.05,
        1.051, 1.052, 1.053, 1.054, 1.055, 1.056, 1.057, 1.058, 1.059, 1.06,
        1.061, 1.062, 1.063, 1.064, 1.065, 1.066, 1.067, 1.068, 1.069, 1.07,
        1.071, 1.072, 1.073, 1.074, 1.075, 1.076, 1.077, 1.078, 1.079, 1.08,
        1.081, 1.082, 1.083, 1.084, 1.085, 1.086, 1.087, 1.088, 1.089, 1.09,
        1.091, 1.092, 1.093, 1.094, 1.095, 1.096, 1.097, 1.098, 1.099, 1.1,
        1.101, 1.102, 1.103, 1.104, 1.105, 1.106, 1.107, 1.108, 1.109, 1.11,
        1.111, 1.112, 1.113, 1.114, 1.115, 1.116, 1.117, 1.118, 1.119, 1.12,
        1.121, 1.122, 1.123, 1.124, 1.125, 1.126, 1.127, 1.128, 1.129,
        1.1300000000000003, 1.131, 1.1320000000000001, 1.133, 1.1340000000000001,
        1.135, 1.1360000000000001, 1.137, 1.1380000000000001, 1.139,
        1.1400000000000001, 1.141, 1.1420000000000001, 1.143, 1.1440000000000001,
        1.145, 1.1460000000000001, 1.147, 1.1480000000000001, 1.149,
        1.1500000000000001, 1.151, 1.1520000000000001, 1.153, 1.154, 1.155,
        1.156, 1.157, 1.158, 1.159, 1.16, 1.161, 1.162, 1.163, 1.164, 1.165,
        1.166, 1.167, 1.168, 1.169, 1.17, 1.171, 1.172, 1.173, 1.174, 1.175,
        1.176, 1.177, 1.178, 1.179, 1.18, 1.181, 1.182, 1.183, 1.184, 1.185,
        1.186, 1.187, 1.188, 1.189, 1.19, 1.191, 1.192, 1.193, 1.194, 1.195,
        1.196, 1.197, 1.198, 1.199, 1.2, 1.201, 1.202, 1.203, 1.204, 1.205,
        1.206, 1.207, 1.208, 1.209, 1.21, 1.211, 1.212, 1.213, 1.214, 1.215,
        1.216, 1.217, 1.218, 1.219, 1.22, 1.221, 1.222, 1.223, 1.224, 1.225,
        1.226, 1.227, 1.228, 1.229, 1.23, 1.231, 1.232, 1.233, 1.234, 1.235,
        1.236, 1.237, 1.238, 1.239, 1.24, 1.241, 1.242, 1.243, 1.244, 1.245,
        1.246, 1.247, 1.248, 1.249, 1.25, 1.251, 1.252, 1.253, 1.254,
        1.2550000000000003, 1.256, 1.2570000000000001, 1.258, 1.2590000000000001,
        1.26, 1.2610000000000001, 1.262, 1.2630000000000001, 1.264,
        1.2650000000000001, 1.266, 1.2670000000000001, 1.268, 1.2690000000000001,
        1.27, 1.2710000000000001, 1.272, 1.2730000000000001, 1.274,
        1.2750000000000001, 1.276, 1.2770000000000001, 1.278, 1.2790000000000001,
        1.28, 1.281, 1.282, 1.283, 1.284, 1.285, 1.286, 1.287, 1.288, 1.289,
        1.29, 1.291, 1.292, 1.293, 1.294, 1.295, 1.296, 1.297, 1.298, 1.299, 1.3,
        1.301, 1.302, 1.303, 1.304, 1.305, 1.306, 1.307, 1.308, 1.309, 1.31,
        1.311, 1.312, 1.313, 1.314, 1.315, 1.316, 1.317, 1.318, 1.319, 1.32,
        1.321, 1.322, 1.323, 1.324, 1.325, 1.326, 1.327, 1.328, 1.329, 1.33,
        1.331, 1.332, 1.333, 1.334, 1.335, 1.336, 1.337, 1.338, 1.339, 1.34,
        1.341, 1.342, 1.343, 1.344, 1.345, 1.346, 1.347, 1.348, 1.349, 1.35,
        1.351, 1.352, 1.353, 1.354, 1.355, 1.356, 1.357, 1.358, 1.359, 1.36,
        1.361, 1.362, 1.363, 1.364, 1.365, 1.366, 1.367, 1.368, 1.369, 1.37,
        1.371, 1.372, 1.373, 1.374, 1.375, 1.376, 1.377, 1.378, 1.379,
        1.3800000000000003, 1.381, 1.3820000000000001, 1.383, 1.3840000000000001,
        1.385, 1.3860000000000001, 1.387, 1.3880000000000001, 1.389,
        1.3900000000000001, 1.391, 1.3920000000000001, 1.393, 1.3940000000000001,
        1.395, 1.3960000000000001, 1.397, 1.3980000000000001, 1.399,
        1.4000000000000001, 1.401, 1.4020000000000001, 1.403, 1.4040000000000001,
        1.405, 1.4060000000000001, 1.407, 1.408, 1.409, 1.41, 1.411, 1.412,
        1.413, 1.414, 1.415, 1.416, 1.417, 1.418, 1.419, 1.42, 1.421, 1.422,
        1.423, 1.424, 1.425, 1.426, 1.427, 1.428, 1.429, 1.43, 1.431, 1.432,
        1.433, 1.434, 1.435, 1.436, 1.437, 1.438, 1.439, 1.44, 1.441, 1.442,
        1.443, 1.444, 1.445, 1.446, 1.447, 1.448, 1.449, 1.45, 1.451, 1.452,
        1.453, 1.454, 1.455, 1.456, 1.457, 1.458, 1.459, 1.46, 1.461, 1.462,
        1.463, 1.464, 1.465, 1.466, 1.467, 1.468, 1.469, 1.47, 1.471, 1.472,
        1.473, 1.474, 1.475, 1.476, 1.477, 1.478, 1.479, 1.48, 1.481, 1.482,
        1.483, 1.484, 1.485, 1.486, 1.487, 1.488, 1.489, 1.49, 1.491, 1.492,
        1.493, 1.494, 1.495, 1.496, 1.497, 1.498, 1.499, 1.5, 1.501, 1.502,
        1.503, 1.504, 1.5050000000000003, 1.506, 1.5070000000000001, 1.508,
        1.5090000000000001, 1.51, 1.5110000000000001, 1.512, 1.5130000000000001,
        1.514, 1.5150000000000001, 1.516, 1.5170000000000001, 1.518,
        1.5190000000000001, 1.52, 1.5210000000000001, 1.522, 1.5230000000000001,
        1.524, 1.5250000000000001, 1.526, 1.5270000000000001, 1.528,
        1.5290000000000001, 1.53, 1.5310000000000001, 1.532, 1.5330000000000001,
        1.534, 1.5350000000000001, 1.536, 1.537, 1.538, 1.539, 1.54, 1.541,
        1.542, 1.543, 1.544, 1.545, 1.546, 1.547, 1.548, 1.549, 1.55, 1.551,
        1.552, 1.553, 1.554, 1.555, 1.556, 1.557, 1.558, 1.559, 1.56, 1.561,
        1.562, 1.563, 1.564, 1.565, 1.566, 1.567, 1.568, 1.569, 1.57, 1.571,
        1.572, 1.573, 1.574, 1.575, 1.576, 1.577, 1.578, 1.579, 1.58, 1.581,
        1.582, 1.583, 1.584, 1.585, 1.586, 1.587, 1.588, 1.589, 1.59, 1.591,
        1.592, 1.593, 1.594, 1.595, 1.596, 1.597, 1.598, 1.599, 1.6, 1.601,
        1.602, 1.603, 1.604, 1.605, 1.606, 1.607, 1.608, 1.609, 1.61, 1.611,
        1.612, 1.613, 1.614, 1.615, 1.616, 1.617, 1.618, 1.619, 1.62, 1.621,
        1.622, 1.623, 1.624, 1.625, 1.626, 1.627, 1.628, 1.629,
        1.6300000000000003, 1.631, 1.6320000000000001, 1.633, 1.6340000000000001,
        1.635, 1.6360000000000001, 1.637, 1.6380000000000001, 1.639,
        1.6400000000000001, 1.641, 1.6420000000000001, 1.643, 1.6440000000000001,
        1.645, 1.6460000000000001, 1.647, 1.6480000000000001, 1.649,
        1.6500000000000001, 1.651, 1.6520000000000001, 1.653, 1.6540000000000001,
        1.655, 1.6560000000000001, 1.657, 1.6580000000000001, 1.659,
        1.6600000000000001, 1.661, 1.6620000000000001, 1.663, 1.6640000000000001,
        1.665, 1.666, 1.667, 1.668, 1.669, 1.67, 1.671, 1.672, 1.673, 1.674,
        1.675, 1.676, 1.677, 1.678, 1.679, 1.68, 1.681, 1.682, 1.683, 1.684,
        1.685, 1.686, 1.687, 1.688, 1.689, 1.69, 1.691, 1.692, 1.693, 1.694,
        1.695, 1.696, 1.697, 1.698, 1.699, 1.7, 1.701, 1.702, 1.703, 1.704,
        1.705, 1.706, 1.707, 1.708, 1.709, 1.71, 1.711, 1.712, 1.713, 1.714,
        1.715, 1.716, 1.717, 1.718, 1.719, 1.72, 1.721, 1.722, 1.723, 1.724,
        1.725, 1.726, 1.727, 1.728, 1.729, 1.73, 1.731, 1.732, 1.733, 1.734,
        1.735, 1.736, 1.737, 1.738, 1.739, 1.74, 1.741, 1.742, 1.743, 1.744,
        1.745, 1.746, 1.747, 1.748, 1.749, 1.75, 1.751, 1.752, 1.753, 1.754,
        1.7550000000000003, 1.756, 1.7570000000000001, 1.758, 1.7590000000000001,
        1.76, 1.7610000000000001, 1.762, 1.7630000000000001, 1.764,
        1.7650000000000001, 1.766, 1.7670000000000001, 1.768, 1.7690000000000001,
        1.77, 1.7710000000000001, 1.772, 1.7730000000000001, 1.774,
        1.7750000000000001, 1.776, 1.7770000000000001, 1.778, 1.7790000000000001,
        1.78, 1.7810000000000001, 1.782, 1.7830000000000001, 1.784,
        1.7850000000000001, 1.786, 1.7870000000000001, 1.788, 1.7890000000000001,
        1.79, 1.7910000000000001, 1.792, 1.793, 1.794, 1.795, 1.796, 1.797,
        1.798, 1.799, 1.8, 1.801, 1.802, 1.803, 1.804, 1.805, 1.806, 1.807,
        1.808, 1.809, 1.81, 1.811, 1.812, 1.813, 1.814, 1.815, 1.816, 1.817,
        1.818, 1.819, 1.82, 1.821, 1.822, 1.823, 1.824, 1.825, 1.826, 1.827,
        1.828, 1.829, 1.83, 1.831, 1.832, 1.833, 1.834, 1.835, 1.836, 1.837,
        1.838, 1.839, 1.84, 1.841, 1.842, 1.843, 1.844, 1.845, 1.846, 1.847,
        1.848, 1.849, 1.85, 1.851, 1.852, 1.853, 1.854, 1.855, 1.856, 1.857,
        1.858, 1.859, 1.86, 1.861, 1.862, 1.863, 1.864, 1.865, 1.866, 1.867,
        1.868, 1.869, 1.87, 1.871, 1.872, 1.873, 1.874, 1.875, 1.876, 1.877,
        1.878, 1.879, 1.8800000000000003, 1.881, 1.8820000000000001, 1.883,
        1.8840000000000001, 1.885, 1.8860000000000001, 1.887, 1.8880000000000001,
        1.889, 1.8900000000000001, 1.891, 1.8920000000000001, 1.893,
        1.8940000000000001, 1.895, 1.8960000000000001, 1.897, 1.8980000000000001,
        1.899, 1.9000000000000001, 1.901, 1.9020000000000001, 1.903,
        1.9040000000000001, 1.905, 1.9060000000000001, 1.907, 1.9080000000000001,
        1.909, 1.9100000000000001, 1.911, 1.9120000000000001, 1.913,
        1.9140000000000001, 1.915, 1.9160000000000001, 1.917, 1.9180000000000001,
        1.919, 1.92, 1.921, 1.922, 1.923, 1.924, 1.925, 1.926, 1.927, 1.928,
        1.929, 1.93, 1.931, 1.932, 1.933, 1.934, 1.935, 1.936, 1.937, 1.938,
        1.939, 1.94, 1.941, 1.942, 1.943, 1.944, 1.945, 1.946, 1.947, 1.948,
        1.949, 1.95, 1.951, 1.952, 1.953, 1.954, 1.955, 1.956, 1.957, 1.958,
        1.959, 1.96, 1.961, 1.962, 1.963, 1.964, 1.965, 1.966, 1.967, 1.968,
        1.969, 1.97, 1.971, 1.972, 1.973, 1.974, 1.975, 1.976, 1.977, 1.978,
        1.979, 1.98, 1.981, 1.982, 1.983, 1.984, 1.985, 1.986, 1.987, 1.988,
        1.989, 1.99, 1.991, 1.992, 1.993, 1.994, 1.995, 1.996, 1.997, 1.998,
        1.999, 2.0, 2.001, 2.0020000000000002, 2.003, 2.004, 2.005,
        2.0060000000000002, 2.007, 2.008, 2.009, 2.0100000000000002, 2.011,
        2.012, 2.013, 2.0140000000000002, 2.015, 2.016, 2.017,
        2.0180000000000002, 2.019, 2.02, 2.021, 2.0220000000000002, 2.023, 2.024,
        2.025, 2.0260000000000002, 2.027, 2.028, 2.029, 2.0300000000000002,
        2.031, 2.032, 2.033, 2.0340000000000003, 2.035, 2.036, 2.037,
        2.0380000000000003, 2.039, 2.04, 2.041, 2.0420000000000003, 2.043, 2.044,
        2.045, 2.0460000000000003, 2.047, 2.048, 2.049, 2.05, 2.051, 2.052,
        2.053, 2.054, 2.055, 2.056, 2.057, 2.058, 2.059, 2.06, 2.061, 2.062,
        2.063, 2.064, 2.065, 2.066, 2.067, 2.068, 2.069, 2.07, 2.071, 2.072,
        2.073, 2.074, 2.075, 2.076, 2.077, 2.078, 2.079, 2.08, 2.081, 2.082,
        2.083, 2.084, 2.085, 2.086, 2.087, 2.088, 2.089, 2.09, 2.091, 2.092,
        2.093, 2.094, 2.095, 2.096, 2.097, 2.098, 2.099, 2.1, 2.101, 2.102,
        2.103, 2.104, 2.105, 2.106, 2.107, 2.108, 2.109, 2.11, 2.111, 2.112,
        2.113, 2.114, 2.115, 2.116, 2.117, 2.118, 2.119, 2.12, 2.121, 2.122,
        2.123, 2.124, 2.125, 2.126, 2.127, 2.128, 2.129, 2.13, 2.131, 2.132,
        2.133, 2.134, 2.1350000000000007, 2.136, 2.137, 2.138,
        2.1390000000000002, 2.14, 2.141, 2.142, 2.1430000000000002, 2.144, 2.145,
        2.146, 2.1470000000000002, 2.148, 2.149, 2.15, 2.1510000000000002, 2.152,
        2.153, 2.154, 2.1550000000000002, 2.156, 2.157, 2.158,
        2.1590000000000003, 2.16, 2.161, 2.162, 2.1630000000000003, 2.164, 2.165,
        2.166, 2.1670000000000003, 2.168, 2.169, 2.17, 2.1710000000000003, 2.172,
        2.173, 2.174, 2.1750000000000003, 2.176, 2.177, 2.178, 2.179, 2.18,
        2.181, 2.182, 2.183, 2.184, 2.185, 2.186, 2.187, 2.188, 2.189, 2.19,
        2.191, 2.192, 2.193, 2.194, 2.195, 2.196, 2.197, 2.198, 2.199, 2.2,
        2.201, 2.202, 2.203, 2.204, 2.205, 2.206, 2.207, 2.208, 2.209, 2.21,
        2.211, 2.212, 2.213, 2.214, 2.215, 2.216, 2.217, 2.218, 2.219, 2.22,
        2.221, 2.222, 2.223, 2.224, 2.225, 2.226, 2.227, 2.228, 2.229, 2.23,
        2.231, 2.232, 2.233, 2.234, 2.235, 2.236, 2.237, 2.238, 2.239, 2.24,
        2.241, 2.242, 2.243, 2.244, 2.245, 2.246, 2.247, 2.248, 2.249, 2.25,
        2.251, 2.252, 2.253, 2.254, 2.255, 2.256, 2.257, 2.258, 2.259,
        2.2600000000000007, 2.261, 2.262, 2.263, 2.2640000000000002, 2.265,
        2.266, 2.267, 2.2680000000000002, 2.269, 2.27, 2.271, 2.2720000000000002,
        2.273, 2.274, 2.275, 2.2760000000000002, 2.277, 2.278, 2.279,
        2.2800000000000002, 2.281, 2.282, 2.283, 2.2840000000000003, 2.285,
        2.286, 2.287, 2.2880000000000003, 2.289, 2.29, 2.291, 2.2920000000000003,
        2.293, 2.294, 2.295, 2.2960000000000003, 2.297, 2.298, 2.299,
        2.3000000000000003, 2.301, 2.302, 2.303, 2.3040000000000003, 2.305,
        2.306, 2.307, 2.308, 2.309, 2.31, 2.311, 2.312, 2.313, 2.314, 2.315,
        2.316, 2.317, 2.318, 2.319, 2.32, 2.321, 2.322, 2.323, 2.324, 2.325,
        2.326, 2.327, 2.328, 2.329, 2.33, 2.331, 2.332, 2.333, 2.334, 2.335,
        2.336, 2.337, 2.338, 2.339, 2.34, 2.341, 2.342, 2.343, 2.344, 2.345,
        2.346, 2.347, 2.348, 2.349, 2.35, 2.351, 2.352, 2.353, 2.354, 2.355,
        2.356, 2.357, 2.358, 2.359, 2.36, 2.361, 2.362, 2.363, 2.364, 2.365,
        2.366, 2.367, 2.368, 2.369, 2.37, 2.371, 2.372, 2.373, 2.374, 2.375,
        2.376, 2.377, 2.378, 2.379, 2.38, 2.381, 2.382, 2.383, 2.384,
        2.3850000000000007, 2.386, 2.387, 2.388, 2.3890000000000002, 2.39, 2.391,
        2.392, 2.3930000000000002, 2.394, 2.395, 2.396, 2.3970000000000002,
        2.398, 2.399, 2.4, 2.4010000000000002, 2.402, 2.403, 2.404,
        2.4050000000000002, 2.406, 2.407, 2.408, 2.4090000000000003, 2.41, 2.411,
        2.412, 2.4130000000000003, 2.414, 2.415, 2.416, 2.4170000000000003,
        2.418, 2.419, 2.42, 2.4210000000000003, 2.422, 2.423, 2.424,
        2.4250000000000003, 2.426, 2.427, 2.428, 2.4290000000000003, 2.43, 2.431,
        2.432, 2.433, 2.434, 2.435, 2.436, 2.437, 2.438, 2.439, 2.44, 2.441,
        2.442, 2.443, 2.444, 2.445, 2.446, 2.447, 2.448, 2.449, 2.45, 2.451,
        2.452, 2.453, 2.454, 2.455, 2.456, 2.457, 2.458, 2.459, 2.46, 2.461,
        2.462, 2.463, 2.464, 2.465, 2.466, 2.467, 2.468, 2.469, 2.47, 2.471,
        2.472, 2.473, 2.474, 2.475, 2.476, 2.477, 2.478, 2.479, 2.48, 2.481,
        2.482, 2.483, 2.484, 2.485, 2.486, 2.487, 2.488, 2.489, 2.49, 2.491,
        2.492, 2.493, 2.494, 2.495, 2.496, 2.497, 2.498, 2.499, 2.5, 2.501,
        2.502, 2.503, 2.504, 2.505, 2.506, 2.507, 2.508, 2.509,
        2.5100000000000007, 2.511, 2.512, 2.513, 2.5140000000000002, 2.515,
        2.516, 2.517, 2.5180000000000002, 2.519, 2.52, 2.521, 2.5220000000000002,
        2.523, 2.524, 2.525, 2.5260000000000002, 2.527, 2.528, 2.529,
        2.5300000000000002, 2.531, 2.532, 2.533, 2.5340000000000003, 2.535,
        2.536, 2.537, 2.5380000000000003, 2.539, 2.54, 2.541, 2.5420000000000003,
        2.543, 2.544, 2.545, 2.5460000000000003, 2.547, 2.548, 2.549,
        2.5500000000000003, 2.551, 2.552, 2.553, 2.5540000000000003, 2.555,
        2.556, 2.557, 2.5580000000000003, 2.559, 2.56, 2.561, 2.562, 2.563,
        2.564, 2.565, 2.566, 2.567, 2.568, 2.569, 2.57, 2.571, 2.572, 2.573,
        2.574, 2.575, 2.576, 2.577, 2.578, 2.579, 2.58, 2.581, 2.582, 2.583,
        2.584, 2.585, 2.586, 2.587, 2.588, 2.589, 2.59, 2.591, 2.592, 2.593,
        2.594, 2.595, 2.596, 2.597, 2.598, 2.599, 2.6, 2.601, 2.602, 2.603,
        2.604, 2.605, 2.606, 2.607, 2.608, 2.609, 2.61, 2.611, 2.612, 2.613,
        2.614, 2.615, 2.616, 2.617, 2.618, 2.619, 2.62, 2.621, 2.622, 2.623,
        2.624, 2.625, 2.626, 2.627, 2.628, 2.629, 2.63, 2.631, 2.632, 2.633,
        2.634, 2.6350000000000007, 2.636, 2.637, 2.638, 2.6390000000000002, 2.64,
        2.641, 2.642, 2.6430000000000002, 2.644, 2.645, 2.646,
        2.6470000000000002, 2.648, 2.649, 2.65, 2.6510000000000002, 2.652, 2.653,
        2.654, 2.6550000000000002, 2.656, 2.657, 2.658, 2.6590000000000003, 2.66,
        2.661, 2.662, 2.6630000000000003, 2.664, 2.665, 2.666,
        2.6670000000000003, 2.668, 2.669, 2.67, 2.6710000000000003, 2.672, 2.673,
        2.674, 2.6750000000000003, 2.676, 2.677, 2.678, 2.6790000000000003, 2.68,
        2.681, 2.682, 2.6830000000000003, 2.684, 2.685, 2.686,
        2.6870000000000003, 2.688, 2.689, 2.69, 2.691, 2.692, 2.693, 2.694,
        2.695, 2.696, 2.697, 2.698, 2.699, 2.7, 2.701, 2.702, 2.703, 2.704,
        2.705, 2.706, 2.707, 2.708, 2.709, 2.71, 2.711, 2.712, 2.713, 2.714,
        2.715, 2.716, 2.717, 2.718, 2.719, 2.72, 2.721, 2.722, 2.723, 2.724,
        2.725, 2.726, 2.727, 2.728, 2.729, 2.73, 2.731, 2.732, 2.733, 2.734,
        2.735, 2.736, 2.737, 2.738, 2.739, 2.74, 2.741, 2.742, 2.743, 2.744,
        2.745, 2.746, 2.747, 2.748, 2.749, 2.75, 2.751, 2.752, 2.753, 2.754,
        2.755, 2.756, 2.757, 2.758, 2.759, 2.7600000000000007, 2.761, 2.762,
        2.763, 2.7640000000000002, 2.765, 2.766, 2.767, 2.7680000000000002,
        2.769, 2.77, 2.771, 2.7720000000000002, 2.773, 2.774, 2.775,
        2.7760000000000002, 2.777, 2.778, 2.779, 2.7800000000000002, 2.781,
        2.782, 2.783, 2.7840000000000003, 2.785, 2.786, 2.787,
        2.7880000000000003, 2.789, 2.79, 2.791, 2.7920000000000003, 2.793, 2.794,
        2.795, 2.7960000000000003, 2.797, 2.798, 2.799, 2.8000000000000003,
        2.801, 2.802, 2.803, 2.8040000000000003, 2.805, 2.806, 2.807,
        2.8080000000000003, 2.809, 2.81, 2.811, 2.8120000000000003, 2.813, 2.814,
        2.815, 2.816, 2.817, 2.818, 2.819, 2.82, 2.821, 2.822, 2.823, 2.824,
        2.825, 2.826, 2.827, 2.828, 2.829, 2.83, 2.831, 2.832, 2.833, 2.834,
        2.835, 2.836, 2.837, 2.838, 2.839, 2.84, 2.841, 2.842, 2.843, 2.844,
        2.845, 2.846, 2.847, 2.848, 2.849, 2.85, 2.851, 2.852, 2.853, 2.854,
        2.855, 2.856, 2.857, 2.858, 2.859, 2.86, 2.861, 2.862, 2.863, 2.864,
        2.865, 2.866, 2.867, 2.868, 2.869, 2.87, 2.871, 2.872, 2.873, 2.874,
        2.875, 2.876, 2.877, 2.878, 2.879, 2.88, 2.881, 2.882, 2.883, 2.884,
        2.8850000000000007, 2.886, 2.887, 2.888, 2.8890000000000002, 2.89, 2.891,
        2.892, 2.8930000000000002, 2.894, 2.895, 2.896, 2.8970000000000002,
        2.898, 2.899, 2.9, 2.9010000000000002, 2.902, 2.903, 2.904,
        2.9050000000000002, 2.906, 2.907, 2.908, 2.9090000000000003, 2.91, 2.911,
        2.912, 2.9130000000000003, 2.914, 2.915, 2.916, 2.9170000000000003,
        2.918, 2.919, 2.92, 2.9210000000000003, 2.922, 2.923, 2.924,
        2.9250000000000003, 2.926, 2.927, 2.928, 2.9290000000000003, 2.93, 2.931,
        2.932, 2.9330000000000003, 2.934, 2.935, 2.936, 2.9370000000000003,
        2.938, 2.939, 2.94, 2.9410000000000003, 2.942, 2.943, 2.944, 2.945,
        2.946, 2.947, 2.948, 2.949, 2.95, 2.951, 2.952, 2.953, 2.954, 2.955,
        2.956, 2.957, 2.958, 2.959, 2.96, 2.961, 2.962, 2.963, 2.964, 2.965,
        2.966, 2.967, 2.968, 2.969, 2.97, 2.971, 2.972, 2.973, 2.974, 2.975,
        2.976, 2.977, 2.978, 2.979, 2.98, 2.981, 2.982, 2.983, 2.984, 2.985,
        2.986, 2.987, 2.988, 2.989, 2.99, 2.991, 2.992, 2.993, 2.994, 2.995,
        2.996, 2.997, 2.998, 2.999, 3.0, 3.001, 3.002, 3.003, 3.004, 3.005,
        3.006, 3.007, 3.008, 3.009, 3.0100000000000007, 3.011, 3.012, 3.013,
        3.0140000000000002, 3.015, 3.016, 3.017, 3.0180000000000002, 3.019, 3.02,
        3.021, 3.0220000000000002, 3.023, 3.024, 3.025, 3.0260000000000002,
        3.027, 3.028, 3.029, 3.0300000000000002, 3.031, 3.032, 3.033,
        3.0340000000000003, 3.035, 3.036, 3.037, 3.0380000000000003, 3.039, 3.04,
        3.041, 3.0420000000000003, 3.043, 3.044, 3.045, 3.0460000000000003,
        3.047, 3.048, 3.049, 3.0500000000000003, 3.051, 3.052, 3.053,
        3.0540000000000003, 3.055, 3.056, 3.057, 3.0580000000000003, 3.059, 3.06,
        3.061, 3.0620000000000003, 3.063, 3.064, 3.065, 3.0660000000000003,
        3.067, 3.068, 3.069, 3.0700000000000003, 3.071, 3.072, 3.073, 3.074,
        3.075, 3.076, 3.077, 3.078, 3.079, 3.08, 3.081, 3.082, 3.083, 3.084,
        3.085, 3.086, 3.087, 3.088, 3.089, 3.09, 3.091, 3.092, 3.093, 3.094,
        3.095, 3.096, 3.097, 3.098, 3.099, 3.1, 3.101, 3.102, 3.103, 3.104,
        3.105, 3.106, 3.107, 3.108, 3.109, 3.11, 3.111, 3.112, 3.113, 3.114,
        3.115, 3.116, 3.117, 3.118, 3.119, 3.12, 3.121, 3.122, 3.123, 3.124,
        3.125, 3.126, 3.127, 3.128, 3.129, 3.13, 3.131, 3.132, 3.133, 3.134,
        3.1350000000000007, 3.136, 3.137, 3.138, 3.1390000000000002, 3.14, 3.141,
        3.142, 3.1430000000000002, 3.144, 3.145, 3.146, 3.1470000000000002,
        3.148, 3.149, 3.15, 3.1510000000000002, 3.152, 3.153, 3.154,
        3.1550000000000002, 3.156, 3.157, 3.158, 3.1590000000000003, 3.16, 3.161,
        3.162, 3.1630000000000003, 3.164, 3.165, 3.166, 3.1670000000000003,
        3.168, 3.169, 3.17, 3.1710000000000003, 3.172, 3.173, 3.174,
        3.1750000000000003, 3.176, 3.177, 3.178, 3.1790000000000003, 3.18, 3.181,
        3.182, 3.1830000000000003, 3.184, 3.185, 3.186, 3.1870000000000003,
        3.188, 3.189, 3.19, 3.1910000000000003, 3.192, 3.193, 3.194,
        3.1950000000000003, 3.196, 3.197, 3.198, 3.1990000000000003, 3.2, 3.201,
        3.202, 3.203, 3.204, 3.205, 3.206, 3.207, 3.208, 3.209, 3.21, 3.211,
        3.212, 3.213, 3.214, 3.215, 3.216, 3.217, 3.218, 3.219, 3.22, 3.221,
        3.222, 3.223, 3.224, 3.225, 3.226, 3.227, 3.228, 3.229, 3.23, 3.231,
        3.232, 3.233, 3.234, 3.235, 3.236, 3.237, 3.238, 3.239, 3.24, 3.241,
        3.242, 3.243, 3.244, 3.245, 3.246, 3.247, 3.248, 3.249, 3.25, 3.251,
        3.252, 3.253, 3.254, 3.255, 3.256, 3.257, 3.258, 3.259,
        3.2600000000000007, 3.261, 3.262, 3.263, 3.2640000000000002, 3.265,
        3.266, 3.267, 3.2680000000000002, 3.269, 3.27, 3.271, 3.2720000000000002,
        3.273, 3.274, 3.275, 3.2760000000000002, 3.277, 3.278, 3.279,
        3.2800000000000002, 3.281, 3.282, 3.283, 3.2840000000000003, 3.285,
        3.286, 3.287, 3.2880000000000003, 3.289, 3.29, 3.291, 3.2920000000000003,
        3.293, 3.294, 3.295, 3.2960000000000003, 3.297, 3.298, 3.299,
        3.3000000000000003, 3.301, 3.302, 3.303, 3.3040000000000003, 3.305,
        3.306, 3.307, 3.3080000000000003, 3.309, 3.31, 3.311, 3.3120000000000003,
        3.313, 3.314, 3.315, 3.3160000000000003, 3.317, 3.318, 3.319,
        3.3200000000000003, 3.321, 3.322, 3.323, 3.3240000000000003, 3.325,
        3.326, 3.327, 3.3280000000000003, 3.329, 3.33, 3.331, 3.332, 3.333,
        3.334, 3.335, 3.336, 3.337, 3.338, 3.339, 3.34, 3.341, 3.342, 3.343,
        3.344, 3.345, 3.346, 3.347, 3.348, 3.349, 3.35, 3.351, 3.352, 3.353,
        3.354, 3.355, 3.356, 3.357, 3.358, 3.359, 3.36, 3.361, 3.362, 3.363,
        3.364, 3.365, 3.366, 3.367, 3.368, 3.369, 3.37, 3.371, 3.372, 3.373,
        3.374, 3.375, 3.376, 3.377, 3.378, 3.379, 3.38, 3.381, 3.382, 3.383,
        3.384, 3.3850000000000007, 3.386, 3.387, 3.388, 3.3890000000000002, 3.39,
        3.391, 3.392, 3.3930000000000002, 3.394, 3.395, 3.396,
        3.3970000000000002, 3.398, 3.399, 3.4, 3.4010000000000002, 3.402, 3.403,
        3.404, 3.4050000000000002, 3.406, 3.407, 3.408, 3.4090000000000003, 3.41,
        3.411, 3.412, 3.4130000000000003, 3.414, 3.415, 3.416,
        3.4170000000000003, 3.418, 3.419, 3.42, 3.4210000000000003, 3.422, 3.423,
        3.424, 3.4250000000000003, 3.426, 3.427, 3.428, 3.4290000000000003, 3.43,
        3.431, 3.432, 3.4330000000000003, 3.434, 3.435, 3.436,
        3.4370000000000003, 3.438, 3.439, 3.44, 3.4410000000000003, 3.442, 3.443,
        3.444, 3.4450000000000003, 3.446, 3.447, 3.448, 3.4490000000000003, 3.45,
        3.451, 3.452, 3.4530000000000003, 3.454, 3.455, 3.456, 3.457, 3.458,
        3.459, 3.46, 3.461, 3.462, 3.463, 3.464, 3.465, 3.466, 3.467, 3.468,
        3.469, 3.47, 3.471, 3.472, 3.473, 3.474, 3.475, 3.476, 3.477, 3.478,
        3.479, 3.48, 3.481, 3.482, 3.483, 3.484, 3.485, 3.486, 3.487, 3.488,
        3.489, 3.49, 3.491, 3.492, 3.493, 3.494, 3.495, 3.496, 3.497, 3.498,
        3.499, 3.5, 3.501, 3.502, 3.503, 3.504, 3.505, 3.506, 3.507, 3.508,
        3.509, 3.5100000000000007, 3.511, 3.512, 3.513, 3.5140000000000002,
        3.515, 3.516, 3.517, 3.5180000000000002, 3.519, 3.52, 3.521,
        3.5220000000000002, 3.523, 3.524, 3.525, 3.5260000000000002, 3.527,
        3.528, 3.529, 3.5300000000000002, 3.531, 3.532, 3.533,
        3.5340000000000003, 3.535, 3.536, 3.537, 3.5380000000000003, 3.539, 3.54,
        3.541, 3.5420000000000003, 3.543, 3.544, 3.545, 3.5460000000000003,
        3.547, 3.548, 3.549, 3.5500000000000003, 3.551, 3.552, 3.553,
        3.5540000000000003, 3.555, 3.556, 3.557, 3.5580000000000003, 3.559, 3.56,
        3.561, 3.5620000000000003, 3.563, 3.564, 3.565, 3.5660000000000003,
        3.567, 3.568, 3.569, 3.5700000000000003, 3.571, 3.572, 3.573,
        3.5740000000000003, 3.575, 3.576, 3.577, 3.5780000000000003, 3.579, 3.58,
        3.581, 3.5820000000000003, 3.583, 3.584, 3.585, 3.586, 3.587, 3.588,
        3.589, 3.59, 3.591, 3.592, 3.593, 3.594, 3.595, 3.596, 3.597, 3.598,
        3.599, 3.6, 3.601, 3.602, 3.603, 3.604, 3.605, 3.606, 3.607, 3.608,
        3.609, 3.61, 3.611, 3.612, 3.613, 3.614, 3.615, 3.616, 3.617, 3.618,
        3.619, 3.62, 3.621, 3.622, 3.623, 3.624, 3.625, 3.626, 3.627, 3.628,
        3.629, 3.63, 3.631, 3.632, 3.633, 3.634, 3.6350000000000007, 3.636,
        3.637, 3.638, 3.6390000000000002, 3.64, 3.641, 3.642, 3.6430000000000002,
        3.644, 3.645, 3.646, 3.6470000000000002, 3.648, 3.649, 3.65,
        3.6510000000000002, 3.652, 3.653, 3.654, 3.6550000000000002, 3.656,
        3.657, 3.658, 3.6590000000000003, 3.66, 3.661, 3.662, 3.6630000000000003,
        3.664, 3.665, 3.666, 3.6670000000000003, 3.668, 3.669, 3.67,
        3.6710000000000003, 3.672, 3.673, 3.674, 3.6750000000000003, 3.676,
        3.677, 3.678, 3.6790000000000003, 3.68, 3.681, 3.682, 3.6830000000000003,
        3.684, 3.685, 3.686, 3.6870000000000003, 3.688, 3.689, 3.69,
        3.6910000000000003, 3.692, 3.693, 3.694, 3.6950000000000003, 3.696,
        3.697, 3.698, 3.6990000000000003, 3.7, 3.701, 3.702, 3.7030000000000003,
        3.704, 3.705, 3.706, 3.7070000000000003, 3.708, 3.709, 3.71,
        3.7110000000000003, 3.712, 3.713, 3.714, 3.715, 3.716, 3.717, 3.718,
        3.719, 3.72, 3.721, 3.722, 3.723, 3.724, 3.725, 3.726, 3.727, 3.728,
        3.729, 3.73, 3.731, 3.732, 3.733, 3.734, 3.735, 3.736, 3.737, 3.738,
        3.739, 3.74, 3.741, 3.742, 3.743, 3.744, 3.745, 3.746, 3.747, 3.748,
        3.749, 3.75, 3.751, 3.752, 3.753, 3.754, 3.755, 3.756, 3.757, 3.758,
        3.759, 3.7600000000000007, 3.761, 3.762, 3.763, 3.7640000000000002,
        3.765, 3.766, 3.767, 3.7680000000000002, 3.769, 3.77, 3.771,
        3.7720000000000002, 3.773, 3.774, 3.775, 3.7760000000000002, 3.777,
        3.778, 3.779, 3.7800000000000002, 3.781, 3.782, 3.783,
        3.7840000000000003, 3.785, 3.786, 3.787, 3.7880000000000003, 3.789, 3.79,
        3.791, 3.7920000000000003, 3.793, 3.794, 3.795, 3.7960000000000003,
        3.797, 3.798, 3.799, 3.8000000000000003, 3.801, 3.802, 3.803,
        3.8040000000000003, 3.805, 3.806, 3.807, 3.8080000000000003, 3.809, 3.81,
        3.811, 3.8120000000000003, 3.813, 3.814, 3.815, 3.8160000000000003,
        3.817, 3.818, 3.819, 3.8200000000000003, 3.821, 3.822, 3.823,
        3.8240000000000003, 3.825, 3.826, 3.827, 3.8280000000000003, 3.829, 3.83,
        3.831, 3.8320000000000003, 3.833, 3.834, 3.835, 3.8360000000000003,
        3.837, 3.838, 3.839, 3.84, 3.841, 3.842, 3.843, 3.844, 3.845, 3.846,
        3.847, 3.848, 3.849, 3.85, 3.851, 3.852, 3.853, 3.854, 3.855, 3.856,
        3.857, 3.858, 3.859, 3.86, 3.861, 3.862, 3.863, 3.864, 3.865, 3.866,
        3.867, 3.868, 3.869, 3.87, 3.871, 3.872, 3.873, 3.874, 3.875, 3.876,
        3.877, 3.878, 3.879, 3.88, 3.881, 3.882, 3.883, 3.884,
        3.8850000000000007, 3.886, 3.887, 3.888, 3.8890000000000002, 3.89, 3.891,
        3.892, 3.8930000000000002, 3.894, 3.895, 3.896, 3.8970000000000002,
        3.898, 3.899, 3.9, 3.9010000000000002, 3.902, 3.903, 3.904,
        3.9050000000000002, 3.906, 3.907, 3.908, 3.9090000000000003, 3.91, 3.911,
        3.912, 3.9130000000000003, 3.914, 3.915, 3.916, 3.9170000000000003,
        3.918, 3.919, 3.92, 3.9210000000000003, 3.922, 3.923, 3.924,
        3.9250000000000003, 3.926, 3.927, 3.928, 3.9290000000000003, 3.93, 3.931,
        3.932, 3.9330000000000003, 3.934, 3.935, 3.936, 3.9370000000000003,
        3.938, 3.939, 3.94, 3.9410000000000003, 3.942, 3.943, 3.944,
        3.9450000000000003, 3.946, 3.947, 3.948, 3.9490000000000003, 3.95, 3.951,
        3.952, 3.9530000000000003, 3.954, 3.955, 3.956, 3.9570000000000003,
        3.958, 3.959, 3.96, 3.9610000000000003, 3.962, 3.963, 3.964,
        3.9650000000000003, 3.966, 3.967, 3.968, 3.969, 3.97, 3.971, 3.972,
        3.973, 3.974, 3.975, 3.976, 3.977, 3.978, 3.979, 3.98, 3.981, 3.982,
        3.983, 3.984, 3.985, 3.986, 3.987, 3.988, 3.989, 3.99, 3.991, 3.992,
        3.993, 3.994, 3.995, 3.996, 3.997, 3.998, 3.999, 4.0, 4.001, 4.002,
        4.003, 4.0040000000000004, 4.005, 4.006, 4.007, 4.008, 4.009, 4.01,
        4.011, 4.0120000000000005, 4.013, 4.014, 4.015, 4.016, 4.017, 4.018,
        4.019, 4.0200000000000005, 4.021, 4.022, 4.023, 4.024, 4.025, 4.026,
        4.027, 4.0280000000000005, 4.029, 4.03, 4.031, 4.032, 4.033, 4.034,
        4.035, 4.0360000000000005, 4.037, 4.038, 4.039, 4.04, 4.041, 4.042,
        4.043, 4.0440000000000005, 4.045, 4.046, 4.047, 4.048, 4.049, 4.05,
        4.051, 4.0520000000000005, 4.053, 4.054, 4.055, 4.056, 4.057, 4.058,
        4.059, 4.0600000000000005, 4.061, 4.062, 4.063, 4.064, 4.065, 4.066,
        4.067, 4.0680000000000005, 4.069, 4.07, 4.071, 4.072, 4.073, 4.074,
        4.075, 4.0760000000000005, 4.077, 4.078, 4.079, 4.08, 4.081, 4.082,
        4.083, 4.0840000000000005, 4.085, 4.086, 4.087, 4.088, 4.089, 4.09,
        4.091, 4.0920000000000005, 4.093, 4.094, 4.095, 4.096, 4.097, 4.098,
        4.099, 4.1, 4.101, 4.102, 4.103, 4.104, 4.105, 4.106, 4.107, 4.108,
        4.109, 4.11, 4.111, 4.112, 4.113, 4.114, 4.115, 4.116, 4.117, 4.118,
        4.119, 4.12, 4.121, 4.122, 4.123, 4.124, 4.125, 4.126, 4.127, 4.128,
        4.129, 4.13, 4.131, 4.132, 4.133, 4.134, 4.135, 4.136, 4.137, 4.138,
        4.139, 4.14, 4.141, 4.142, 4.143, 4.144, 4.1450000000000014, 4.146,
        4.147, 4.148, 4.149, 4.15, 4.151, 4.152, 4.1530000000000005, 4.154,
        4.155, 4.156, 4.157, 4.158, 4.159, 4.16, 4.1610000000000005, 4.162,
        4.163, 4.164, 4.165, 4.166, 4.167, 4.168, 4.1690000000000005, 4.17,
        4.171, 4.172, 4.173, 4.174, 4.175, 4.176, 4.1770000000000005, 4.178,
        4.179, 4.18, 4.181, 4.182, 4.183, 4.184, 4.1850000000000005, 4.186,
        4.187, 4.188, 4.189, 4.19, 4.191, 4.192, 4.1930000000000005, 4.194,
        4.195, 4.196, 4.197, 4.198, 4.199, 4.2, 4.2010000000000005, 4.202, 4.203,
        4.204, 4.205, 4.206, 4.207, 4.208, 4.2090000000000005, 4.21, 4.211,
        4.212, 4.213, 4.214, 4.215, 4.216, 4.2170000000000005, 4.218, 4.219,
        4.22, 4.221, 4.222, 4.223, 4.224, 4.225, 4.226, 4.227, 4.228, 4.229,
        4.23, 4.231, 4.232, 4.233, 4.234, 4.235, 4.236, 4.237, 4.238, 4.239,
        4.24, 4.241, 4.242, 4.243, 4.244, 4.245, 4.246, 4.247, 4.248, 4.249,
        4.25, 4.251, 4.252, 4.253, 4.254, 4.255, 4.256, 4.257, 4.258, 4.259,
        4.26, 4.261, 4.262, 4.263, 4.264, 4.265, 4.266, 4.267, 4.268, 4.269,
        4.2700000000000014, 4.271, 4.272, 4.273, 4.274, 4.275, 4.276, 4.277,
        4.2780000000000005, 4.279, 4.28, 4.281, 4.282, 4.283, 4.284, 4.285,
        4.2860000000000005, 4.287, 4.288, 4.289, 4.29, 4.291, 4.292, 4.293,
        4.2940000000000005, 4.295, 4.296, 4.297, 4.298, 4.299, 4.3, 4.301,
        4.3020000000000005, 4.303, 4.304, 4.305, 4.306, 4.307, 4.308, 4.309,
        4.3100000000000005, 4.311, 4.312, 4.313, 4.314, 4.315, 4.316, 4.317,
        4.3180000000000005, 4.319, 4.32, 4.321, 4.322, 4.323, 4.324, 4.325,
        4.3260000000000005, 4.327, 4.328, 4.329, 4.33, 4.331, 4.332, 4.333,
        4.3340000000000005, 4.335, 4.336, 4.337, 4.338, 4.339, 4.34, 4.341,
        4.3420000000000005, 4.343, 4.344, 4.345, 4.346, 4.347, 4.348, 4.349,
        4.3500000000000005, 4.351, 4.352, 4.353, 4.354, 4.355, 4.356, 4.357,
        4.358, 4.359, 4.36, 4.361, 4.362, 4.363, 4.364, 4.365, 4.366, 4.367,
        4.368, 4.369, 4.37, 4.371, 4.372, 4.373, 4.374, 4.375, 4.376, 4.377,
        4.378, 4.379, 4.38, 4.381, 4.382, 4.383, 4.384, 4.385, 4.386, 4.387,
        4.388, 4.389, 4.39, 4.391, 4.392, 4.393, 4.394, 4.3950000000000014,
        4.396, 4.397, 4.398, 4.399, 4.4, 4.401, 4.402, 4.4030000000000005, 4.404,
        4.405, 4.406, 4.407, 4.408, 4.409, 4.41, 4.4110000000000005, 4.412,
        4.413, 4.414, 4.415, 4.416, 4.417, 4.418, 4.4190000000000005, 4.42,
        4.421, 4.422, 4.423, 4.424, 4.425, 4.426, 4.4270000000000005, 4.428,
        4.429, 4.43, 4.431, 4.432, 4.433, 4.434, 4.4350000000000005, 4.436,
        4.437, 4.438, 4.439, 4.44, 4.441, 4.442, 4.4430000000000005, 4.444,
        4.445, 4.446, 4.447, 4.448, 4.449, 4.45, 4.4510000000000005, 4.452,
        4.453, 4.454, 4.455, 4.456, 4.457, 4.458, 4.4590000000000005, 4.46,
        4.461, 4.462, 4.463, 4.464, 4.465, 4.466, 4.4670000000000005, 4.468,
        4.469, 4.47, 4.471, 4.472, 4.473, 4.474, 4.4750000000000005, 4.476,
        4.477, 4.478, 4.479, 4.48, 4.481, 4.482, 4.483, 4.484, 4.485, 4.486,
        4.487, 4.488, 4.489, 4.49, 4.491, 4.492, 4.493, 4.494, 4.495, 4.496,
        4.497, 4.498, 4.499, 4.5, 4.501, 4.502, 4.503, 4.504, 4.505, 4.506,
        4.507, 4.508, 4.509, 4.51, 4.511, 4.512, 4.513, 4.514, 4.515, 4.516,
        4.517, 4.518, 4.519, 4.5200000000000014, 4.521, 4.522, 4.523, 4.524,
        4.525, 4.526, 4.527, 4.5280000000000005, 4.529, 4.53, 4.531, 4.532,
        4.533, 4.534, 4.535, 4.5360000000000005, 4.537, 4.538, 4.539, 4.54,
        4.541, 4.542, 4.543, 4.5440000000000005, 4.545, 4.546, 4.547, 4.548,
        4.549, 4.55, 4.551, 4.5520000000000005, 4.553, 4.554, 4.555, 4.556,
        4.557, 4.558, 4.559, 4.5600000000000005, 4.561, 4.562, 4.563, 4.564,
        4.565, 4.566, 4.567, 4.5680000000000005, 4.569, 4.57, 4.571, 4.572,
        4.573, 4.574, 4.575, 4.5760000000000005, 4.577, 4.578, 4.579, 4.58,
        4.581, 4.582, 4.583, 4.5840000000000005, 4.585, 4.586, 4.587, 4.588,
        4.589, 4.59, 4.591, 4.5920000000000005, 4.593, 4.594, 4.595, 4.596,
        4.597, 4.598, 4.599, 4.6000000000000005, 4.601, 4.602, 4.603, 4.604,
        4.605, 4.606, 4.607, 4.6080000000000005, 4.609, 4.61, 4.611, 4.612,
        4.613, 4.614, 4.615, 4.616, 4.617, 4.618, 4.619, 4.62, 4.621, 4.622,
        4.623, 4.624, 4.625, 4.626, 4.627, 4.628, 4.629, 4.63, 4.631, 4.632,
        4.633, 4.634, 4.635, 4.636, 4.637, 4.638, 4.639, 4.64, 4.641, 4.642,
        4.643, 4.644, 4.6450000000000014, 4.646, 4.647, 4.648, 4.649, 4.65,
        4.651, 4.652, 4.6530000000000005, 4.654, 4.655, 4.656, 4.657, 4.658,
        4.659, 4.66, 4.6610000000000005, 4.662, 4.663, 4.664, 4.665, 4.666,
        4.667, 4.668, 4.6690000000000005, 4.67, 4.671, 4.672, 4.673, 4.674,
        4.675, 4.676, 4.6770000000000005, 4.678, 4.679, 4.68, 4.681, 4.682,
        4.683, 4.684, 4.6850000000000005, 4.686, 4.687, 4.688, 4.689, 4.69,
        4.691, 4.692, 4.6930000000000005, 4.694, 4.695, 4.696, 4.697, 4.698,
        4.699, 4.7, 4.7010000000000005, 4.702, 4.703, 4.704, 4.705, 4.706, 4.707,
        4.708, 4.7090000000000005, 4.71, 4.711, 4.712, 4.713, 4.714, 4.715,
        4.716, 4.7170000000000005, 4.718, 4.719, 4.72, 4.721, 4.722, 4.723,
        4.724, 4.7250000000000005, 4.726, 4.727, 4.728, 4.729, 4.73, 4.731,
        4.732, 4.7330000000000005, 4.734, 4.735, 4.736, 4.737, 4.738, 4.739,
        4.74, 4.741, 4.742, 4.743, 4.744, 4.745, 4.746, 4.747, 4.748, 4.749,
        4.75, 4.751, 4.752, 4.753, 4.754, 4.755, 4.756, 4.757, 4.758, 4.759,
        4.76, 4.761, 4.762, 4.763, 4.764, 4.765, 4.766, 4.767, 4.768, 4.769,
        4.7700000000000014, 4.771, 4.772, 4.773, 4.774, 4.775, 4.776, 4.777,
        4.7780000000000005, 4.779, 4.78, 4.781, 4.782, 4.783, 4.784, 4.785,
        4.7860000000000005, 4.787, 4.788, 4.789, 4.79, 4.791, 4.792, 4.793,
        4.7940000000000005, 4.795, 4.796, 4.797, 4.798, 4.799, 4.8, 4.801,
        4.8020000000000005, 4.803, 4.804, 4.805, 4.806, 4.807, 4.808, 4.809,
        4.8100000000000005, 4.811, 4.812, 4.813, 4.814, 4.815, 4.816, 4.817,
        4.8180000000000005, 4.819, 4.82, 4.821, 4.822, 4.823, 4.824, 4.825,
        4.8260000000000005, 4.827, 4.828, 4.829, 4.83, 4.831, 4.832, 4.833,
        4.8340000000000005, 4.835, 4.836, 4.837, 4.838, 4.839, 4.84, 4.841,
        4.8420000000000005, 4.843, 4.844, 4.845, 4.846, 4.847, 4.848, 4.849,
        4.8500000000000005, 4.851, 4.852, 4.853, 4.854, 4.855, 4.856, 4.857,
        4.8580000000000005, 4.859, 4.86, 4.861, 4.862, 4.863, 4.864, 4.865,
        4.866, 4.867, 4.868, 4.869, 4.87, 4.871, 4.872, 4.873, 4.874, 4.875,
        4.876, 4.877, 4.878, 4.879, 4.88, 4.881, 4.882, 4.883, 4.884, 4.885,
        4.886, 4.887, 4.888, 4.889, 4.89, 4.891, 4.892, 4.893, 4.894,
        4.8950000000000014, 4.896, 4.897, 4.898, 4.899, 4.9, 4.901, 4.902,
        4.9030000000000005, 4.904, 4.905, 4.906, 4.907, 4.908, 4.909, 4.91,
        4.9110000000000005, 4.912, 4.913, 4.914, 4.915, 4.916, 4.917, 4.918,
        4.9190000000000005, 4.92, 4.921, 4.922, 4.923, 4.924, 4.925, 4.926,
        4.9270000000000005, 4.928, 4.929, 4.93, 4.931, 4.932, 4.933, 4.934,
        4.9350000000000005, 4.936, 4.937, 4.938, 4.939, 4.94, 4.941, 4.942,
        4.9430000000000005, 4.944, 4.945, 4.946, 4.947, 4.948, 4.949, 4.95,
        4.9510000000000005, 4.952, 4.953, 4.954, 4.955, 4.956, 4.957, 4.958,
        4.9590000000000005, 4.96, 4.961, 4.962, 4.963, 4.964, 4.965, 4.966,
        4.9670000000000005, 4.968, 4.969, 4.97, 4.971, 4.972, 4.973, 4.974,
        4.9750000000000005, 4.976, 4.977, 4.978, 4.979, 4.98, 4.981, 4.982,
        4.9830000000000005, 4.984, 4.985, 4.986, 4.987, 4.988, 4.989, 4.99,
        4.9910000000000005, 4.992, 4.993, 4.994, 4.995, 4.996, 4.997, 4.998,
        4.999, 5.0, 5.001, 5.002, 5.003, 5.004, 5.005, 5.006, 5.007, 5.008,
        5.0089999999999995, 5.01, 5.011, 5.012, 5.013, 5.014, 5.015, 5.016,
        5.0169999999999995, 5.018, 5.019, 5.02, 5.021, 5.022, 5.023, 5.024,
        5.0249999999999995, 5.026, 5.027, 5.028, 5.029, 5.03, 5.031, 5.032,
        5.0329999999999995, 5.034, 5.035, 5.036, 5.037, 5.038, 5.039, 5.04,
        5.0409999999999995, 5.042, 5.043, 5.044, 5.045, 5.046, 5.047, 5.048,
        5.0489999999999995, 5.05, 5.051, 5.052, 5.053, 5.054, 5.055, 5.056,
        5.0569999999999995, 5.058, 5.059, 5.06, 5.061, 5.062, 5.063, 5.064,
        5.0649999999999995, 5.066, 5.067, 5.068, 5.069, 5.07, 5.071, 5.072,
        5.0729999999999995, 5.074, 5.075, 5.076, 5.077, 5.078, 5.079, 5.08,
        5.0809999999999995, 5.082, 5.083, 5.084, 5.085, 5.086, 5.087, 5.088,
        5.0889999999999995, 5.09, 5.091, 5.092, 5.093, 5.094, 5.095, 5.096,
        5.0969999999999995, 5.098, 5.099, 5.1, 5.101, 5.102, 5.103, 5.104,
        5.1049999999999986, 5.106, 5.107, 5.108, 5.109, 5.11, 5.111, 5.112,
        5.113, 5.114, 5.115, 5.116, 5.117, 5.118, 5.119, 5.12, 5.121, 5.122,
        5.123, 5.124, 5.125, 5.126, 5.127, 5.128, 5.129, 5.13, 5.131, 5.132,
        5.133, 5.134, 5.135, 5.136, 5.137, 5.138, 5.139, 5.14, 5.141,
        5.1419999999999995, 5.143, 5.144, 5.145, 5.146, 5.147, 5.148, 5.149,
        5.1499999999999995, 5.151, 5.152, 5.153, 5.154, 5.155, 5.156, 5.157,
        5.1579999999999995, 5.159, 5.16, 5.161, 5.162, 5.163, 5.164, 5.165,
        5.1659999999999995, 5.167, 5.168, 5.169, 5.17, 5.171, 5.172, 5.173,
        5.1739999999999995, 5.175, 5.176, 5.177, 5.178, 5.179, 5.18, 5.181,
        5.1819999999999995, 5.183, 5.184, 5.185, 5.186, 5.187, 5.188, 5.189,
        5.1899999999999995, 5.191, 5.192, 5.193, 5.194, 5.195, 5.196, 5.197,
        5.1979999999999995, 5.199, 5.2, 5.201, 5.202, 5.203, 5.204, 5.205,
        5.2059999999999995, 5.207, 5.208, 5.209, 5.21, 5.211, 5.212, 5.213,
        5.2139999999999995, 5.215, 5.216, 5.217, 5.218, 5.219, 5.22, 5.221,
        5.2219999999999995, 5.223, 5.224, 5.225, 5.226, 5.227, 5.228, 5.229,
        5.2299999999999986, 5.231, 5.232, 5.233, 5.234, 5.235, 5.236, 5.237,
        5.238, 5.239, 5.24, 5.241, 5.242, 5.243, 5.244, 5.245, 5.246, 5.247,
        5.248, 5.249, 5.25, 5.251, 5.252, 5.253, 5.254, 5.255, 5.256, 5.257,
        5.258, 5.259, 5.26, 5.261, 5.262, 5.263, 5.264, 5.265, 5.266,
        5.2669999999999995, 5.268, 5.269, 5.27, 5.271, 5.272, 5.273, 5.274,
        5.2749999999999995, 5.276, 5.277, 5.278, 5.279, 5.28, 5.281, 5.282,
        5.2829999999999995, 5.284, 5.285, 5.286, 5.287, 5.288, 5.289, 5.29,
        5.2909999999999995, 5.292, 5.293, 5.294, 5.295, 5.296, 5.297, 5.298,
        5.2989999999999995, 5.3, 5.301, 5.302, 5.303, 5.304, 5.305, 5.306,
        5.3069999999999995, 5.308, 5.309, 5.31, 5.311, 5.312, 5.313, 5.314,
        5.3149999999999995, 5.316, 5.317, 5.318, 5.319, 5.32, 5.321, 5.322,
        5.3229999999999995, 5.324, 5.325, 5.326, 5.327, 5.328, 5.329, 5.33,
        5.3309999999999995, 5.332, 5.333, 5.334, 5.335, 5.336, 5.337, 5.338,
        5.3389999999999995, 5.34, 5.341, 5.342, 5.343, 5.344, 5.345, 5.346,
        5.3469999999999995, 5.348, 5.349, 5.35, 5.351, 5.352, 5.353, 5.354,
        5.3549999999999986, 5.356, 5.357, 5.358, 5.359, 5.36, 5.361, 5.362,
        5.363, 5.364, 5.365, 5.366, 5.367, 5.368, 5.369, 5.37, 5.371, 5.372,
        5.373, 5.374, 5.375, 5.376, 5.377, 5.378, 5.379, 5.38, 5.381, 5.382,
        5.383, 5.384, 5.385, 5.386, 5.387, 5.388, 5.389, 5.39, 5.391,
        5.3919999999999995, 5.393, 5.394, 5.395, 5.396, 5.397, 5.398, 5.399,
        5.3999999999999995, 5.401, 5.402, 5.403, 5.404, 5.405, 5.406, 5.407,
        5.4079999999999995, 5.409, 5.41, 5.411, 5.412, 5.413, 5.414, 5.415,
        5.4159999999999995, 5.417, 5.418, 5.419, 5.42, 5.421, 5.422, 5.423,
        5.4239999999999995, 5.425, 5.426, 5.427, 5.428, 5.429, 5.43, 5.431,
        5.4319999999999995, 5.433, 5.434, 5.435, 5.436, 5.437, 5.438, 5.439,
        5.4399999999999995, 5.441, 5.442, 5.443, 5.444, 5.445, 5.446, 5.447,
        5.4479999999999995, 5.449, 5.45, 5.451, 5.452, 5.453, 5.454, 5.455,
        5.4559999999999995, 5.457, 5.458, 5.459, 5.46, 5.461, 5.462, 5.463,
        5.4639999999999995, 5.465, 5.466, 5.467, 5.468, 5.469, 5.47, 5.471,
        5.4719999999999995, 5.473, 5.474, 5.475, 5.476, 5.477, 5.478, 5.479,
        5.4799999999999986, 5.481, 5.482, 5.483, 5.484, 5.485, 5.486, 5.487,
        5.488, 5.489, 5.49, 5.491, 5.492, 5.493, 5.494, 5.495, 5.496, 5.497,
        5.498, 5.499, 5.5, 5.501, 5.502, 5.503, 5.504, 5.505, 5.506, 5.507,
        5.508, 5.509, 5.51, 5.511, 5.512, 5.513, 5.514, 5.515, 5.516, 5.517,
        5.518, 5.519, 5.52, 5.521, 5.522, 5.523, 5.524, 5.5249999999999995,
        5.526, 5.527, 5.528, 5.529, 5.53, 5.531, 5.532, 5.5329999999999995,
        5.534, 5.535, 5.536, 5.537, 5.538, 5.539, 5.54, 5.5409999999999995,
        5.542, 5.543, 5.544, 5.545, 5.546, 5.547, 5.548, 5.5489999999999995,
        5.55, 5.551, 5.552, 5.553, 5.554, 5.555, 5.556, 5.5569999999999995,
        5.558, 5.559, 5.56, 5.561, 5.562, 5.563, 5.564, 5.5649999999999995,
        5.566, 5.567, 5.568, 5.569, 5.57, 5.571, 5.572, 5.5729999999999995,
        5.574, 5.575, 5.576, 5.577, 5.578, 5.579, 5.58, 5.5809999999999995,
        5.582, 5.583, 5.584, 5.585, 5.586, 5.587, 5.588, 5.5889999999999995,
        5.59, 5.591, 5.592, 5.593, 5.594, 5.595, 5.596, 5.5969999999999995,
        5.598, 5.599, 5.6, 5.601, 5.602, 5.603, 5.604, 5.6049999999999986, 5.606,
        5.607, 5.608, 5.609, 5.61, 5.611, 5.612, 5.613, 5.614, 5.615, 5.616,
        5.617, 5.618, 5.619, 5.62, 5.621, 5.622, 5.623, 5.624, 5.625, 5.626,
        5.627, 5.628, 5.629, 5.63, 5.631, 5.632, 5.633, 5.634, 5.635, 5.636,
        5.637, 5.638, 5.639, 5.64, 5.641, 5.642, 5.643, 5.644, 5.645, 5.646,
        5.647, 5.648, 5.649, 5.6499999999999995, 5.651, 5.652, 5.653, 5.654,
        5.655, 5.656, 5.657, 5.6579999999999995, 5.659, 5.66, 5.661, 5.662,
        5.663, 5.664, 5.665, 5.6659999999999995, 5.667, 5.668, 5.669, 5.67,
        5.671, 5.672, 5.673, 5.6739999999999995, 5.675, 5.676, 5.677, 5.678,
        5.679, 5.68, 5.681, 5.6819999999999995, 5.683, 5.684, 5.685, 5.686,
        5.687, 5.688, 5.689, 5.6899999999999995, 5.691, 5.692, 5.693, 5.694,
        5.695, 5.696, 5.697, 5.6979999999999995, 5.699, 5.7, 5.701, 5.702, 5.703,
        5.704, 5.705, 5.7059999999999995, 5.707, 5.708, 5.709, 5.71, 5.711,
        5.712, 5.713, 5.7139999999999995, 5.715, 5.716, 5.717, 5.718, 5.719,
        5.72, 5.721, 5.7219999999999995, 5.723, 5.724, 5.725, 5.726, 5.727,
        5.728, 5.729, 5.7299999999999986, 5.731, 5.732, 5.733, 5.734, 5.735,
        5.736, 5.737, 5.738, 5.739, 5.74, 5.741, 5.742, 5.743, 5.744, 5.745,
        5.746, 5.747, 5.748, 5.749, 5.75, 5.751, 5.752, 5.753, 5.754, 5.755,
        5.756, 5.757, 5.758, 5.759, 5.76, 5.761, 5.762, 5.763, 5.764, 5.765,
        5.766, 5.767, 5.768, 5.769, 5.77, 5.771, 5.772, 5.773, 5.774, 5.775,
        5.776, 5.777, 5.778, 5.779, 5.78, 5.781, 5.782, 5.7829999999999995,
        5.784, 5.785, 5.786, 5.787, 5.788, 5.789, 5.79, 5.7909999999999995,
        5.792, 5.793, 5.794, 5.795, 5.796, 5.797, 5.798, 5.7989999999999995, 5.8,
        5.801, 5.802, 5.803, 5.804, 5.805, 5.806, 5.8069999999999995, 5.808,
        5.809, 5.81, 5.811, 5.812, 5.813, 5.814, 5.8149999999999995, 5.816,
        5.817, 5.818, 5.819, 5.82, 5.821, 5.822, 5.8229999999999995, 5.824,
        5.825, 5.826, 5.827, 5.828, 5.829, 5.83, 5.8309999999999995, 5.832,
        5.833, 5.834, 5.835, 5.836, 5.837, 5.838, 5.8389999999999995, 5.84,
        5.841, 5.842, 5.843, 5.844, 5.845, 5.846, 5.8469999999999995, 5.848,
        5.849, 5.85, 5.851, 5.852, 5.853, 5.854, 5.8549999999999986, 5.856,
        5.857, 5.858, 5.859, 5.86, 5.861, 5.862, 5.863, 5.864, 5.865, 5.866,
        5.867, 5.868, 5.869, 5.87, 5.871, 5.872, 5.873, 5.874, 5.875, 5.876,
        5.877, 5.878, 5.879, 5.88, 5.881, 5.882, 5.883, 5.884, 5.885, 5.886,
        5.887, 5.888, 5.889, 5.89, 5.891, 5.892, 5.893, 5.894, 5.895, 5.896,
        5.897, 5.898, 5.899, 5.9, 5.901, 5.902, 5.903, 5.904, 5.905, 5.906,
        5.907, 5.9079999999999995, 5.909, 5.91, 5.911, 5.912, 5.913, 5.914,
        5.915, 5.9159999999999995, 5.917, 5.918, 5.919, 5.92, 5.921, 5.922,
        5.923, 5.9239999999999995, 5.925, 5.926, 5.927, 5.928, 5.929, 5.93,
        5.931, 5.9319999999999995, 5.933, 5.934, 5.935, 5.936, 5.937, 5.938,
        5.939, 5.9399999999999995, 5.941, 5.942, 5.943, 5.944, 5.945, 5.946,
        5.947, 5.9479999999999995, 5.949, 5.95, 5.951, 5.952, 5.953, 5.954,
        5.955, 5.9559999999999995, 5.957, 5.958, 5.959, 5.96, 5.961, 5.962,
        5.963, 5.9639999999999995, 5.965, 5.966, 5.967, 5.968, 5.969, 5.97,
        5.971, 5.9719999999999995, 5.973, 5.974, 5.975, 5.976, 5.977, 5.978,
        5.979, 5.9799999999999986, 5.981, 5.982, 5.983, 5.984, 5.985, 5.986,
        5.987, 5.988, 5.989, 5.99, 5.991, 5.992, 5.993, 5.994, 5.995, 5.996,
        5.997, 5.998, 5.999, 6.0, 6.0009999999999994, 6.002, 6.003, 6.004, 6.005,
        6.006, 6.007, 6.008, 6.009, 6.01, 6.011, 6.012, 6.013,
        6.0139999999999993, 6.0150000000000006, 6.016, 6.0169999999999995, 6.018,
        6.019, 6.02, 6.021, 6.022, 6.023, 6.024, 6.025, 6.026, 6.027,
        6.0280000000000005, 6.029, 6.0299999999999994, 6.0310000000000006, 6.032,
        6.0329999999999995, 6.034, 6.035, 6.036, 6.037, 6.038, 6.039, 6.04,
        6.041, 6.042, 6.0429999999999993, 6.0440000000000005, 6.045,
        6.0459999999999994, 6.047, 6.048, 6.0489999999999995, 6.05, 6.051, 6.052,
        6.053, 6.054, 6.055, 6.056, 6.057, 6.058, 6.0589999999999993,
        6.0600000000000005, 6.061, 6.0619999999999994, 6.063, 6.064,
        6.0649999999999995, 6.066, 6.067, 6.068, 6.069, 6.07, 6.071, 6.072,
        6.073, 6.074, 6.0749999999999993, 6.0760000000000005, 6.077,
        6.0779999999999994, 6.079, 6.08, 6.0809999999999995, 6.082, 6.083, 6.084,
        6.085, 6.086, 6.087, 6.088, 6.089, 6.09, 6.0909999999999993,
        6.0920000000000005, 6.093, 6.0939999999999994, 6.095, 6.096,
        6.0969999999999995, 6.098, 6.099, 6.1, 6.101, 6.102, 6.103, 6.104, 6.105,
        6.106, 6.1069999999999993, 6.1080000000000005, 6.109, 6.1099999999999994,
        6.111, 6.112, 6.113, 6.114, 6.115, 6.116, 6.117, 6.118, 6.119, 6.12,
        6.121, 6.122, 6.1229999999999993, 6.1240000000000006, 6.125,
        6.1259999999999994, 6.127, 6.128, 6.129, 6.13, 6.131, 6.132, 6.133,
        6.134, 6.135, 6.136, 6.137, 6.138, 6.1389999999999993,
        6.1400000000000006, 6.141, 6.1419999999999995, 6.143, 6.144, 6.145,
        6.146, 6.147, 6.148, 6.149, 6.15, 6.151, 6.152, 6.1530000000000005,
        6.154, 6.1549999999999994, 6.1560000000000006, 6.157, 6.1579999999999995,
        6.159, 6.16, 6.161, 6.162, 6.163, 6.164, 6.165, 6.166, 6.167,
        6.1679999999999993, 6.1690000000000005, 6.17, 6.1709999999999994, 6.172,
        6.173, 6.1739999999999995, 6.175, 6.176, 6.177, 6.178, 6.179, 6.18,
        6.181, 6.182, 6.183, 6.1839999999999993, 6.1850000000000005, 6.186,
        6.1869999999999994, 6.188, 6.189, 6.1899999999999995, 6.191, 6.192,
        6.193, 6.194, 6.195, 6.196, 6.197, 6.198, 6.199, 6.1999999999999993,
        6.2010000000000005, 6.202, 6.2029999999999994, 6.204, 6.205,
        6.2059999999999995, 6.207, 6.208, 6.209, 6.21, 6.211, 6.212, 6.213,
        6.214, 6.215, 6.2159999999999993, 6.2170000000000005, 6.218,
        6.2189999999999994, 6.22, 6.221, 6.2219999999999995, 6.223, 6.224, 6.225,
        6.226, 6.227, 6.228, 6.229, 6.23, 6.231, 6.2319999999999993,
        6.2330000000000005, 6.234, 6.2349999999999994, 6.236, 6.237, 6.238,
        6.239, 6.24, 6.241, 6.242, 6.243, 6.244, 6.245, 6.246, 6.247,
        6.2479999999999993, 6.2490000000000006, 6.25, 6.2509999999999994, 6.252,
        6.253, 6.254, 6.255, 6.256, 6.257, 6.258, 6.259, 6.26, 6.261, 6.262,
        6.263, 6.2639999999999993, 6.2650000000000006, 6.266, 6.2669999999999995,
        6.268, 6.269, 6.27, 6.271, 6.272, 6.273, 6.274, 6.275, 6.276, 6.277,
        6.2780000000000005, 6.279, 6.2799999999999994, 6.2810000000000006, 6.282,
        6.2829999999999995, 6.284, 6.285, 6.286, 6.287, 6.288, 6.289, 6.29,
        6.291, 6.292, 6.2929999999999993, 6.2940000000000005, 6.295,
        6.2959999999999994, 6.297, 6.298, 6.2989999999999995, 6.3, 6.301, 6.302,
        6.303, 6.304, 6.305, 6.306, 6.307, 6.308, 6.3089999999999993,
        6.3100000000000005, 6.311, 6.3119999999999994, 6.313, 6.314,
        6.3149999999999995, 6.316, 6.317, 6.318, 6.319, 6.32, 6.321, 6.322,
        6.323, 6.324, 6.3249999999999993, 6.3260000000000005, 6.327,
        6.3279999999999994, 6.329, 6.33, 6.3309999999999995, 6.332, 6.333, 6.334,
        6.335, 6.336, 6.337, 6.338, 6.339, 6.34, 6.3409999999999993,
        6.3420000000000005, 6.343, 6.3439999999999994, 6.345, 6.346,
        6.3469999999999995, 6.348, 6.349, 6.35, 6.351, 6.352, 6.353, 6.354,
        6.355, 6.356, 6.3569999999999993, 6.3580000000000005, 6.359,
        6.3599999999999994, 6.361, 6.362, 6.363, 6.364, 6.365, 6.366, 6.367,
        6.368, 6.369, 6.37, 6.371, 6.372, 6.3729999999999993, 6.3740000000000006,
        6.375, 6.3759999999999994, 6.377, 6.378, 6.379, 6.38, 6.381, 6.382,
        6.383, 6.384, 6.385, 6.386, 6.387, 6.388, 6.3889999999999993,
        6.3900000000000006, 6.391, 6.3919999999999995, 6.393, 6.394, 6.395,
        6.396, 6.397, 6.398, 6.399, 6.4, 6.401, 6.402, 6.4030000000000005, 6.404,
        6.4049999999999994, 6.4060000000000006, 6.407, 6.4079999999999995, 6.409,
        6.41, 6.411, 6.412, 6.413, 6.414, 6.415, 6.416, 6.417,
        6.4179999999999993, 6.4190000000000005, 6.42, 6.4209999999999994, 6.422,
        6.423, 6.4239999999999995, 6.425, 6.426, 6.427, 6.428, 6.429, 6.43,
        6.431, 6.432, 6.433, 6.4339999999999993, 6.4350000000000005, 6.436,
        6.4369999999999994, 6.438, 6.439, 6.4399999999999995, 6.441, 6.442,
        6.443, 6.444, 6.445, 6.446, 6.447, 6.448, 6.449, 6.4499999999999993,
        6.4510000000000005, 6.452, 6.4529999999999994, 6.454, 6.455,
        6.4559999999999995, 6.457, 6.458, 6.459, 6.46, 6.461, 6.462, 6.463,
        6.464, 6.465, 6.4659999999999993, 6.4670000000000005, 6.468,
        6.4689999999999994, 6.47, 6.471, 6.4719999999999995, 6.473, 6.474, 6.475,
        6.476, 6.477, 6.478, 6.479, 6.48, 6.481, 6.4819999999999993,
        6.4830000000000005, 6.484, 6.4849999999999994, 6.486, 6.487, 6.488,
        6.489, 6.49, 6.491, 6.492, 6.493, 6.494, 6.495, 6.496, 6.497,
        6.4979999999999993, 6.4990000000000006, 6.5, 6.5009999999999994, 6.502,
        6.503, 6.504, 6.505, 6.506, 6.507, 6.508, 6.509, 6.51, 6.511, 6.512,
        6.513, 6.5139999999999993, 6.5150000000000006, 6.516, 6.5169999999999995,
        6.518, 6.519, 6.52, 6.521, 6.522, 6.523, 6.524, 6.525, 6.526, 6.527,
        6.5280000000000005, 6.529, 6.5299999999999994, 6.5310000000000006, 6.532,
        6.5329999999999995, 6.534, 6.535, 6.536, 6.537, 6.538, 6.539, 6.54,
        6.541, 6.542, 6.543, 6.5440000000000005, 6.545, 6.5459999999999994,
        6.547, 6.548, 6.5489999999999995, 6.55, 6.551, 6.552, 6.553, 6.554,
        6.555, 6.556, 6.557, 6.558, 6.5589999999999993, 6.5600000000000005,
        6.561, 6.5619999999999994, 6.563, 6.564, 6.5649999999999995, 6.566,
        6.567, 6.568, 6.569, 6.57, 6.571, 6.572, 6.573, 6.574,
        6.5749999999999993, 6.5760000000000005, 6.577, 6.5779999999999994, 6.579,
        6.58, 6.5809999999999995, 6.582, 6.583, 6.584, 6.585, 6.586, 6.587,
        6.588, 6.589, 6.59, 6.5909999999999993, 6.5920000000000005, 6.593,
        6.5939999999999994, 6.595, 6.596, 6.5969999999999995, 6.598, 6.599, 6.6,
        6.601, 6.602, 6.603, 6.604, 6.605, 6.606, 6.6069999999999993,
        6.6080000000000005, 6.609, 6.6099999999999994, 6.611, 6.612, 6.613,
        6.614, 6.615, 6.616, 6.617, 6.618, 6.619, 6.62, 6.621, 6.622,
        6.6229999999999993, 6.6240000000000006, 6.625, 6.6259999999999994, 6.627,
        6.628, 6.629, 6.63, 6.631, 6.632, 6.633, 6.634, 6.635, 6.636, 6.637,
        6.638, 6.6389999999999993, 6.6400000000000006, 6.641, 6.6419999999999995,
        6.643, 6.644, 6.645, 6.646, 6.647, 6.648, 6.649, 6.65, 6.651, 6.652,
        6.6530000000000005, 6.654, 6.6549999999999994, 6.6560000000000006, 6.657,
        6.6579999999999995, 6.659, 6.66, 6.661, 6.662, 6.663, 6.664, 6.665,
        6.666, 6.667, 6.668, 6.6690000000000005, 6.67, 6.6709999999999994, 6.672,
        6.673, 6.6739999999999995, 6.675, 6.676, 6.677, 6.678, 6.679, 6.68,
        6.681, 6.682, 6.683, 6.6839999999999993, 6.6850000000000005, 6.686,
        6.6869999999999994, 6.688, 6.689, 6.6899999999999995, 6.691, 6.692,
        6.693, 6.694, 6.695, 6.696, 6.697, 6.698, 6.699, 6.6999999999999993,
        6.7010000000000005, 6.702, 6.7029999999999994, 6.704, 6.705,
        6.7059999999999995, 6.707, 6.708, 6.709, 6.71, 6.711, 6.712, 6.713,
        6.714, 6.715, 6.7159999999999993, 6.7170000000000005, 6.718,
        6.7189999999999994, 6.72, 6.721, 6.7219999999999995, 6.723, 6.724, 6.725,
        6.726, 6.727, 6.728, 6.729, 6.73, 6.731, 6.7319999999999993,
        6.7330000000000005, 6.734, 6.7349999999999994, 6.736, 6.737, 6.738,
        6.739, 6.74, 6.741, 6.742, 6.743, 6.744, 6.745, 6.746, 6.747,
        6.7479999999999993, 6.7490000000000006, 6.75, 6.7509999999999994, 6.752,
        6.753, 6.754, 6.755, 6.756, 6.757, 6.758, 6.759, 6.76, 6.761, 6.762,
        6.763, 6.7639999999999993, 6.7650000000000006, 6.766, 6.7669999999999995,
        6.768, 6.769, 6.77, 6.771, 6.772, 6.773, 6.774, 6.775, 6.776, 6.777,
        6.7780000000000005, 6.779, 6.7799999999999994, 6.7810000000000006, 6.782,
        6.7829999999999995, 6.784, 6.785, 6.786, 6.787, 6.788, 6.789, 6.79,
        6.791, 6.792, 6.793, 6.7940000000000005, 6.795, 6.7959999999999994,
        6.7970000000000006, 6.798, 6.7989999999999995, 6.8, 6.801, 6.802, 6.803,
        6.804, 6.805, 6.806, 6.807, 6.808, 6.8089999999999993,
        6.8100000000000005, 6.811, 6.8119999999999994, 6.813, 6.814,
        6.8149999999999995, 6.816, 6.817, 6.818, 6.819, 6.82, 6.821, 6.822,
        6.823, 6.824, 6.8249999999999993, 6.8260000000000005, 6.827,
        6.8279999999999994, 6.829, 6.83, 6.8309999999999995, 6.832, 6.833, 6.834,
        6.835, 6.836, 6.837, 6.838, 6.839, 6.84, 6.8409999999999993,
        6.8420000000000005, 6.843, 6.8439999999999994, 6.845, 6.846,
        6.8469999999999995, 6.848, 6.849, 6.85, 6.851, 6.852, 6.853, 6.854,
        6.855, 6.856, 6.8569999999999993, 6.8580000000000005, 6.859,
        6.8599999999999994, 6.861, 6.862, 6.863, 6.864, 6.865, 6.866, 6.867,
        6.868, 6.869, 6.87, 6.871, 6.872, 6.8729999999999993, 6.8740000000000006,
        6.875, 6.8759999999999994, 6.877, 6.878, 6.879, 6.88, 6.881, 6.882,
        6.883, 6.884, 6.885, 6.886, 6.887, 6.888, 6.8889999999999993,
        6.8900000000000006, 6.891, 6.8919999999999995, 6.893, 6.894, 6.895,
        6.896, 6.897, 6.898, 6.899, 6.9, 6.901, 6.902, 6.9030000000000005, 6.904,
        6.9049999999999994, 6.9060000000000006, 6.907, 6.9079999999999995, 6.909,
        6.91, 6.911, 6.912, 6.913, 6.914, 6.915, 6.916, 6.917, 6.918,
        6.9190000000000005, 6.92, 6.9209999999999994, 6.9220000000000006, 6.923,
        6.9239999999999995, 6.925, 6.926, 6.927, 6.928, 6.929, 6.93, 6.931,
        6.932, 6.933, 6.9339999999999993, 6.9350000000000005, 6.936,
        6.9369999999999994, 6.938, 6.939, 6.9399999999999995, 6.941, 6.942,
        6.943, 6.944, 6.945, 6.946, 6.947, 6.948, 6.949, 6.9499999999999993,
        6.9510000000000005, 6.952, 6.9529999999999994, 6.954, 6.955,
        6.9559999999999995, 6.957, 6.958, 6.959, 6.96, 6.961, 6.962, 6.963,
        6.964, 6.965, 6.9659999999999993, 6.9670000000000005, 6.968,
        6.9689999999999994, 6.97, 6.971, 6.9719999999999995, 6.973, 6.974, 6.975,
        6.976, 6.977, 6.978, 6.979, 6.98, 6.981, 6.9819999999999993,
        6.9830000000000005, 6.984, 6.9849999999999994, 6.986, 6.987, 6.988,
        6.989, 6.99, 6.991, 6.992, 6.993, 6.994, 6.995, 6.996, 6.997,
        6.9979999999999993, 6.9990000000000006, 7.0, 7.0009999999999994, 7.002,
        7.003, 7.004, 7.005, 7.006, 7.007, 7.008, 7.009, 7.01, 7.011, 7.012,
        7.013, 7.0139999999999993, 7.0150000000000006, 7.016, 7.0169999999999995,
        7.018, 7.019, 7.02, 7.021, 7.022, 7.023, 7.024, 7.025, 7.026, 7.027,
        7.0280000000000005, 7.029, 7.0299999999999994, 7.0310000000000006, 7.032,
        7.0329999999999995, 7.034, 7.035, 7.036, 7.037, 7.038, 7.039, 7.04,
        7.041, 7.042, 7.043, 7.0440000000000005, 7.045, 7.0459999999999994,
        7.0470000000000006, 7.048, 7.0489999999999995, 7.05, 7.051, 7.052, 7.053,
        7.054, 7.055, 7.056, 7.057, 7.058, 7.0589999999999993,
        7.0600000000000005, 7.061, 7.0619999999999994, 7.063, 7.064,
        7.0649999999999995, 7.066, 7.067, 7.068, 7.069, 7.07, 7.071, 7.072,
        7.073, 7.074, 7.0749999999999993, 7.0760000000000005, 7.077,
        7.0779999999999994, 7.079, 7.08, 7.0809999999999995, 7.082, 7.083, 7.084,
        7.085, 7.086, 7.087, 7.088, 7.089, 7.09, 7.0909999999999993,
        7.0920000000000005, 7.093, 7.0939999999999994, 7.095, 7.096,
        7.0969999999999995, 7.098, 7.099, 7.1, 7.101, 7.102, 7.103, 7.104, 7.105,
        7.106, 7.1069999999999993, 7.1080000000000005, 7.109, 7.1099999999999994,
        7.111, 7.112, 7.113, 7.114, 7.115, 7.116, 7.117, 7.118, 7.119, 7.12,
        7.121, 7.122, 7.1229999999999993, 7.1240000000000006, 7.125,
        7.1259999999999994, 7.127, 7.128, 7.129, 7.13, 7.131, 7.132, 7.133,
        7.134, 7.135, 7.136, 7.137, 7.138, 7.1389999999999993,
        7.1400000000000006, 7.141, 7.1419999999999995, 7.143, 7.144, 7.145,
        7.146, 7.147, 7.148, 7.149, 7.15, 7.151, 7.152, 7.1530000000000005,
        7.154, 7.1549999999999994, 7.1560000000000006, 7.157, 7.1579999999999995,
        7.159, 7.16, 7.161, 7.162, 7.163, 7.164, 7.165, 7.166, 7.167, 7.168,
        7.1690000000000005, 7.17, 7.1709999999999994, 7.1720000000000006, 7.173,
        7.1739999999999995, 7.175, 7.176, 7.177, 7.178, 7.179, 7.18, 7.181,
        7.182, 7.183, 7.184, 7.1850000000000005, 7.186, 7.1869999999999994,
        7.188, 7.189, 7.1899999999999995, 7.191, 7.192, 7.193, 7.194, 7.195,
        7.196, 7.197, 7.198, 7.199, 7.1999999999999993, 7.2010000000000005,
        7.202, 7.2029999999999994, 7.204, 7.205, 7.2059999999999995, 7.207,
        7.208, 7.209, 7.21, 7.211, 7.212, 7.213, 7.214, 7.215,
        7.2159999999999993, 7.2170000000000005, 7.218, 7.2189999999999994, 7.22,
        7.221, 7.2219999999999995, 7.223, 7.224, 7.225, 7.226, 7.227, 7.228,
        7.229, 7.23, 7.231, 7.2319999999999993, 7.2330000000000005, 7.234,
        7.2349999999999994, 7.236, 7.237, 7.238, 7.239, 7.24, 7.241, 7.242,
        7.243, 7.244, 7.245, 7.246, 7.247, 7.2479999999999993,
        7.2490000000000006, 7.25, 7.2509999999999994, 7.252, 7.253, 7.254, 7.255,
        7.256, 7.257, 7.258, 7.259, 7.26, 7.261, 7.262, 7.263,
        7.2639999999999993, 7.2650000000000006, 7.266, 7.2669999999999995, 7.268,
        7.269, 7.27, 7.271, 7.272, 7.273, 7.274, 7.275, 7.276, 7.277,
        7.2780000000000005, 7.279, 7.2799999999999994, 7.2810000000000006, 7.282,
        7.2829999999999995, 7.284, 7.285, 7.286, 7.287, 7.288, 7.289, 7.29,
        7.291, 7.292, 7.293, 7.2940000000000005, 7.295, 7.2959999999999994,
        7.2970000000000006, 7.298, 7.2989999999999995, 7.3, 7.301, 7.302, 7.303,
        7.304, 7.305, 7.306, 7.307, 7.308, 7.309, 7.3100000000000005, 7.311,
        7.3119999999999994, 7.313, 7.314, 7.3149999999999995, 7.316, 7.317,
        7.318, 7.319, 7.32, 7.321, 7.322, 7.323, 7.324, 7.3249999999999993,
        7.3260000000000005, 7.327, 7.3279999999999994, 7.329, 7.33,
        7.3309999999999995, 7.332, 7.333, 7.334, 7.335, 7.336, 7.337, 7.338,
        7.339, 7.34, 7.3409999999999993, 7.3420000000000005, 7.343,
        7.3439999999999994, 7.345, 7.346, 7.3469999999999995, 7.348, 7.349, 7.35,
        7.351, 7.352, 7.353, 7.354, 7.355, 7.356, 7.3569999999999993,
        7.3580000000000005, 7.359, 7.3599999999999994, 7.361, 7.362, 7.363,
        7.364, 7.365, 7.366, 7.367, 7.368, 7.369, 7.37, 7.371, 7.372,
        7.3729999999999993, 7.3740000000000006, 7.375, 7.3759999999999994, 7.377,
        7.378, 7.379, 7.38, 7.381, 7.382, 7.383, 7.384, 7.385, 7.386, 7.387,
        7.388, 7.3889999999999993, 7.3900000000000006, 7.391, 7.3919999999999995,
        7.393, 7.394, 7.395, 7.396, 7.397, 7.398, 7.399, 7.4, 7.401, 7.402,
        7.4030000000000005, 7.404, 7.4049999999999994, 7.4060000000000006, 7.407,
        7.4079999999999995, 7.409, 7.41, 7.411, 7.412, 7.413, 7.414, 7.415,
        7.416, 7.417, 7.418, 7.4190000000000005, 7.42, 7.4209999999999994,
        7.4220000000000006, 7.423, 7.4239999999999995, 7.425, 7.426, 7.427,
        7.428, 7.429, 7.43, 7.431, 7.432, 7.433, 7.434, 7.4350000000000005,
        7.436, 7.4369999999999994, 7.4380000000000006, 7.439, 7.4399999999999995,
        7.441, 7.442, 7.443, 7.444, 7.445, 7.446, 7.447, 7.448, 7.449,
        7.4499999999999993, 7.4510000000000005, 7.452, 7.4529999999999994, 7.454,
        7.455, 7.4559999999999995, 7.457, 7.458, 7.459, 7.46, 7.461, 7.462,
        7.463, 7.464, 7.465, 7.4659999999999993, 7.4670000000000005, 7.468,
        7.4689999999999994, 7.47, 7.471, 7.4719999999999995, 7.473, 7.474, 7.475,
        7.476, 7.477, 7.478, 7.479, 7.48, 7.481, 7.4819999999999993,
        7.4830000000000005, 7.484, 7.4849999999999994, 7.486, 7.487, 7.488,
        7.489, 7.49, 7.491, 7.492, 7.493, 7.494, 7.495, 7.496, 7.497,
        7.4979999999999993, 7.4990000000000006, 7.5, 7.5009999999999994, 7.502,
        7.503, 7.504, 7.505, 7.506, 7.507, 7.508, 7.509, 7.51, 7.511, 7.512,
        7.513, 7.5139999999999993, 7.5150000000000006, 7.516, 7.5169999999999995,
        7.518, 7.519, 7.52, 7.521, 7.522, 7.523, 7.524, 7.525, 7.526, 7.527,
        7.5280000000000005, 7.529, 7.5299999999999994, 7.5310000000000006, 7.532,
        7.5329999999999995, 7.534, 7.535, 7.536, 7.537, 7.538, 7.539, 7.54,
        7.541, 7.542, 7.543, 7.5440000000000005, 7.545, 7.5459999999999994,
        7.5470000000000006, 7.548, 7.5489999999999995, 7.55, 7.551, 7.552, 7.553,
        7.554, 7.555, 7.556, 7.557, 7.558, 7.559, 7.5600000000000005, 7.561,
        7.5619999999999994, 7.5630000000000006, 7.564, 7.5649999999999995, 7.566,
        7.567, 7.568, 7.569, 7.57, 7.571, 7.572, 7.573, 7.574,
        7.5749999999999993, 7.5760000000000005, 7.577, 7.5779999999999994, 7.579,
        7.58, 7.5809999999999995, 7.582, 7.583, 7.584, 7.585, 7.586, 7.587,
        7.588, 7.589, 7.59, 7.5909999999999993, 7.5920000000000005, 7.593,
        7.5939999999999994, 7.595, 7.596, 7.5969999999999995, 7.598, 7.599, 7.6,
        7.601, 7.602, 7.603, 7.604, 7.605, 7.606, 7.6069999999999993,
        7.6080000000000005, 7.609, 7.6099999999999994, 7.611, 7.612, 7.613,
        7.614, 7.615, 7.616, 7.617, 7.618, 7.619, 7.62, 7.621, 7.622,
        7.6229999999999993, 7.6240000000000006, 7.625, 7.6259999999999994, 7.627,
        7.628, 7.629, 7.63, 7.631, 7.632, 7.633, 7.634, 7.635, 7.636, 7.637,
        7.638, 7.6389999999999993, 7.6400000000000006, 7.641, 7.6419999999999995,
        7.643, 7.644, 7.645, 7.646, 7.647, 7.648, 7.649, 7.65, 7.651, 7.652,
        7.6530000000000005, 7.654, 7.6549999999999994, 7.6560000000000006, 7.657,
        7.6579999999999995, 7.659, 7.66, 7.661, 7.662, 7.663, 7.664, 7.665,
        7.666, 7.667, 7.668, 7.6690000000000005, 7.67, 7.6709999999999994,
        7.6720000000000006, 7.673, 7.6739999999999995, 7.675, 7.676, 7.677,
        7.678, 7.679, 7.68, 7.681, 7.682, 7.683, 7.684, 7.6850000000000005,
        7.686, 7.6869999999999994, 7.6880000000000006, 7.689, 7.6899999999999995,
        7.691, 7.692, 7.693, 7.694, 7.695, 7.696, 7.697, 7.698, 7.699,
        7.6999999999999993, 7.7010000000000005, 7.702, 7.7029999999999994, 7.704,
        7.705, 7.7059999999999995, 7.707, 7.708, 7.709, 7.71, 7.711, 7.712,
        7.713, 7.714, 7.715, 7.7159999999999993, 7.7170000000000005, 7.718,
        7.7189999999999994, 7.72, 7.721, 7.7219999999999995, 7.723, 7.724, 7.725,
        7.726, 7.727, 7.728, 7.729, 7.73, 7.731, 7.7319999999999993,
        7.7330000000000005, 7.734, 7.7349999999999994, 7.736, 7.737, 7.738,
        7.739, 7.74, 7.741, 7.742, 7.743, 7.744, 7.745, 7.746, 7.747,
        7.7479999999999993, 7.7490000000000006, 7.75, 7.7509999999999994, 7.752,
        7.753, 7.754, 7.755, 7.756, 7.757, 7.758, 7.759, 7.76, 7.761, 7.762,
        7.763, 7.7639999999999993, 7.7650000000000006, 7.766, 7.7669999999999995,
        7.768, 7.769, 7.77, 7.771, 7.772, 7.773, 7.774, 7.775, 7.776, 7.777,
        7.7780000000000005, 7.779, 7.7799999999999994, 7.7810000000000006, 7.782,
        7.7829999999999995, 7.784, 7.785, 7.786, 7.787, 7.788, 7.789, 7.79,
        7.791, 7.792, 7.793, 7.7940000000000005, 7.795, 7.7959999999999994,
        7.7970000000000006, 7.798, 7.7989999999999995, 7.8, 7.801, 7.802, 7.803,
        7.804, 7.805, 7.806, 7.807, 7.808, 7.809, 7.8100000000000005, 7.811,
        7.8119999999999994, 7.8130000000000006, 7.814, 7.8149999999999995, 7.816,
        7.817, 7.818, 7.819, 7.82, 7.821, 7.822, 7.823, 7.824,
        7.8249999999999993, 7.8260000000000005, 7.827, 7.8279999999999994, 7.829,
        7.83, 7.8309999999999995, 7.832, 7.833, 7.834, 7.835, 7.836, 7.837,
        7.838, 7.839, 7.84, 7.8409999999999993, 7.8420000000000005, 7.843,
        7.8439999999999994, 7.845, 7.846, 7.8469999999999995, 7.848, 7.849, 7.85,
        7.851, 7.852, 7.853, 7.854, 7.855, 7.856, 7.8569999999999993,
        7.8580000000000005, 7.859, 7.8599999999999994, 7.861, 7.862, 7.863,
        7.864, 7.865, 7.866, 7.867, 7.868, 7.869, 7.87, 7.871, 7.872,
        7.8729999999999993, 7.8740000000000006, 7.875, 7.8759999999999994, 7.877,
        7.878, 7.879, 7.88, 7.881, 7.882, 7.883, 7.884, 7.885, 7.886, 7.887,
        7.888, 7.8889999999999993, 7.8900000000000006, 7.891, 7.8919999999999995,
        7.893, 7.894, 7.895, 7.896, 7.897, 7.898, 7.899, 7.9, 7.901, 7.902,
        7.9030000000000005, 7.904, 7.9049999999999994, 7.9060000000000006, 7.907,
        7.9079999999999995, 7.909, 7.91, 7.911, 7.912, 7.913, 7.914, 7.915,
        7.916, 7.917, 7.918, 7.9190000000000005, 7.92, 7.9209999999999994,
        7.9220000000000006, 7.923, 7.9239999999999995, 7.925, 7.926, 7.927,
        7.928, 7.929, 7.93, 7.931, 7.932, 7.933, 7.934, 7.9350000000000005,
        7.936, 7.9369999999999994, 7.9380000000000006, 7.939, 7.9399999999999995,
        7.941, 7.942, 7.943, 7.944, 7.945, 7.946, 7.947, 7.948, 7.949, 7.95,
        7.9510000000000005, 7.952, 7.9529999999999994, 7.954, 7.955,
        7.9559999999999995, 7.957, 7.958, 7.959, 7.96, 7.961, 7.962, 7.963,
        7.964, 7.965, 7.9659999999999993, 7.9670000000000005, 7.968,
        7.9689999999999994, 7.97, 7.971, 7.9719999999999995, 7.973, 7.974, 7.975,
        7.976, 7.977, 7.978, 7.979, 7.98, 7.981, 7.9819999999999993,
        7.9830000000000005, 7.984, 7.9849999999999994, 7.986, 7.987, 7.988,
        7.989, 7.99, 7.991, 7.992, 7.993, 7.994, 7.995, 7.996, 7.997,
        7.9979999999999993, 7.9990000000000006, 8.0, 8.001, 8.002, 8.003, 8.004,
        8.004999999999999, 8.006, 8.007, 8.008, 8.009, 8.01, 8.011, 8.012, 8.013,
        8.014, 8.015, 8.016, 8.017, 8.018, 8.019, 8.02, 8.021, 8.022, 8.023,
        8.0240000000000009, 8.025, 8.026, 8.027, 8.028, 8.029, 8.03, 8.031,
        8.032, 8.033, 8.034, 8.035, 8.036, 8.036999999999999, 8.038, 8.039, 8.04,
        8.041, 8.042, 8.043, 8.044, 8.045, 8.046, 8.047, 8.048, 8.049, 8.05,
        8.051, 8.052, 8.053, 8.054, 8.055, 8.0560000000000009, 8.057, 8.058,
        8.059, 8.06, 8.061, 8.062, 8.063, 8.064, 8.065, 8.066, 8.067, 8.068,
        8.0689999999999991, 8.07, 8.071, 8.072, 8.073, 8.074, 8.075, 8.076,
        8.077, 8.078, 8.079, 8.08, 8.081, 8.082, 8.083, 8.084, 8.085, 8.086,
        8.087, 8.088, 8.089, 8.09, 8.091, 8.092, 8.093, 8.094, 8.095, 8.096,
        8.097, 8.097999999999999, 8.099, 8.1, 8.1009999999999991, 8.102, 8.103,
        8.104, 8.105, 8.106, 8.107, 8.108, 8.109, 8.11, 8.111, 8.112, 8.113,
        8.114, 8.115, 8.116, 8.117, 8.118, 8.119, 8.12, 8.121, 8.122, 8.123,
        8.124, 8.125, 8.126, 8.127, 8.128, 8.129, 8.129999999999999, 8.131,
        8.132, 8.133, 8.134, 8.135, 8.136, 8.137, 8.138, 8.139, 8.14, 8.141,
        8.142, 8.143, 8.144, 8.145, 8.146, 8.147, 8.148, 8.1490000000000009,
        8.15, 8.151, 8.152, 8.153, 8.154, 8.155, 8.156, 8.157, 8.158, 8.159,
        8.16, 8.161, 8.161999999999999, 8.163, 8.164, 8.165, 8.166, 8.167, 8.168,
        8.169, 8.17, 8.171, 8.172, 8.173, 8.174, 8.175, 8.176, 8.177, 8.178,
        8.179, 8.18, 8.1810000000000009, 8.182, 8.183, 8.184, 8.185, 8.186,
        8.187, 8.188, 8.189, 8.19, 8.191, 8.192, 8.193, 8.1939999999999991,
        8.195, 8.196, 8.197, 8.198, 8.199, 8.2, 8.201, 8.202, 8.203, 8.204,
        8.205, 8.206, 8.207, 8.208, 8.209, 8.21, 8.211, 8.212, 8.213, 8.214,
        8.215, 8.216, 8.217, 8.218, 8.219, 8.22, 8.221, 8.222, 8.222999999999999,
        8.224, 8.225, 8.226, 8.227, 8.228, 8.229, 8.23, 8.231, 8.232, 8.233,
        8.234, 8.235, 8.236, 8.237, 8.238, 8.239, 8.24, 8.241, 8.242, 8.243,
        8.244, 8.245, 8.246, 8.247, 8.248, 8.249, 8.25, 8.251, 8.252, 8.253,
        8.254, 8.254999999999999, 8.256, 8.257, 8.258, 8.259, 8.26, 8.261, 8.262,
        8.263, 8.264, 8.265, 8.266, 8.267, 8.268, 8.269, 8.27, 8.271, 8.272,
        8.273, 8.274, 8.275, 8.276, 8.277, 8.278, 8.279, 8.28, 8.281, 8.282,
        8.283, 8.284, 8.285, 8.286, 8.286999999999999, 8.288, 8.289, 8.29, 8.291,
        8.292, 8.293, 8.294, 8.295, 8.296, 8.297, 8.298, 8.299, 8.3, 8.301,
        8.302, 8.303, 8.304, 8.305, 8.3060000000000009, 8.307, 8.308, 8.309,
        8.31, 8.311, 8.312, 8.313, 8.314, 8.315, 8.316, 8.317, 8.318,
        8.3189999999999991, 8.32, 8.321, 8.322, 8.323, 8.324, 8.325, 8.326,
        8.327, 8.328, 8.329, 8.33, 8.331, 8.332, 8.333, 8.334, 8.335, 8.336,
        8.337, 8.338, 8.339, 8.34, 8.341, 8.342, 8.343, 8.344, 8.345, 8.346,
        8.347, 8.347999999999999, 8.349, 8.35, 8.351, 8.352, 8.353, 8.354, 8.355,
        8.356, 8.357, 8.358, 8.359, 8.36, 8.361, 8.362, 8.363, 8.364, 8.365,
        8.366, 8.367, 8.368, 8.369, 8.37, 8.371, 8.372, 8.373, 8.374, 8.375,
        8.376, 8.377, 8.378, 8.379, 8.379999999999999, 8.381, 8.382, 8.383,
        8.384, 8.385, 8.386, 8.387, 8.388, 8.389, 8.39, 8.391, 8.392, 8.393,
        8.394, 8.395, 8.396, 8.397, 8.398, 8.399, 8.4, 8.401, 8.402, 8.403,
        8.404, 8.405, 8.406, 8.407, 8.408, 8.409, 8.41, 8.411, 8.411999999999999,
        8.413, 8.414, 8.415, 8.416, 8.417, 8.418, 8.419, 8.42, 8.421, 8.422,
        8.423, 8.424, 8.425, 8.426, 8.427, 8.428, 8.429, 8.43,
        8.4310000000000009, 8.432, 8.433, 8.434, 8.435, 8.436, 8.437, 8.438,
        8.439, 8.44, 8.441, 8.442, 8.443, 8.4439999999999991, 8.445, 8.446,
        8.447, 8.448, 8.449, 8.45, 8.451, 8.452, 8.453, 8.454, 8.455, 8.456,
        8.457, 8.458, 8.459, 8.46, 8.461, 8.462, 8.463000000000001, 8.464, 8.465,
        8.466, 8.467, 8.468, 8.469, 8.47, 8.471, 8.472, 8.472999999999999, 8.474,
        8.475, 8.476, 8.477, 8.478, 8.479, 8.48, 8.481, 8.482, 8.483, 8.484,
        8.485, 8.486, 8.487, 8.488, 8.489, 8.49, 8.491, 8.492, 8.493, 8.494,
        8.495, 8.496, 8.497, 8.498, 8.499, 8.5, 8.501, 8.502, 8.503, 8.504,
        8.504999999999999, 8.506, 8.507, 8.508, 8.509, 8.51, 8.511, 8.512, 8.513,
        8.514, 8.515, 8.516, 8.517, 8.518, 8.519, 8.52, 8.521, 8.522, 8.523,
        8.524, 8.525, 8.526, 8.527, 8.528, 8.529, 8.53, 8.531, 8.532, 8.533,
        8.534, 8.535, 8.536, 8.536999999999999, 8.538, 8.539, 8.54, 8.541, 8.542,
        8.543, 8.544, 8.545, 8.546, 8.547, 8.548, 8.549, 8.55, 8.551, 8.552,
        8.553, 8.554, 8.555, 8.5560000000000009, 8.557, 8.558, 8.559, 8.56,
        8.561, 8.562, 8.563, 8.564, 8.565, 8.566, 8.567, 8.568,
        8.5689999999999991, 8.57, 8.571, 8.572, 8.573, 8.574, 8.575, 8.576,
        8.577, 8.578, 8.579, 8.58, 8.581, 8.582, 8.583, 8.584, 8.585, 8.586,
        8.587, 8.588000000000001, 8.589, 8.59, 8.591, 8.592, 8.593, 8.594, 8.595,
        8.596, 8.597, 8.597999999999999, 8.599, 8.6, 8.601, 8.602, 8.603, 8.604,
        8.605, 8.606, 8.607, 8.608, 8.609, 8.61, 8.611, 8.612, 8.613, 8.614,
        8.615, 8.616, 8.617, 8.618, 8.619, 8.62, 8.621, 8.622, 8.623, 8.624,
        8.625, 8.626, 8.627, 8.628, 8.629, 8.629999999999999, 8.631, 8.632,
        8.633, 8.634, 8.635, 8.636, 8.637, 8.638, 8.639, 8.64, 8.641, 8.642,
        8.643, 8.644, 8.645, 8.646, 8.647, 8.648, 8.649, 8.65, 8.651, 8.652,
        8.653, 8.654, 8.655, 8.656, 8.657, 8.658, 8.659, 8.66, 8.661,
        8.661999999999999, 8.663, 8.664, 8.665, 8.666, 8.667, 8.668, 8.669, 8.67,
        8.671, 8.672, 8.673, 8.674, 8.675, 8.676, 8.677, 8.678, 8.679, 8.68,
        8.6810000000000009, 8.682, 8.683, 8.684, 8.685, 8.686, 8.687, 8.688,
        8.689, 8.69, 8.691, 8.692, 8.693, 8.6939999999999991, 8.695, 8.696,
        8.697, 8.698, 8.699, 8.7, 8.701, 8.702, 8.703, 8.704, 8.705, 8.706,
        8.707, 8.708, 8.709, 8.71, 8.711, 8.712, 8.713000000000001, 8.714, 8.715,
        8.716, 8.717, 8.718, 8.719, 8.72, 8.721, 8.722, 8.722999999999999, 8.724,
        8.725, 8.726, 8.727, 8.728, 8.729, 8.73, 8.731, 8.732, 8.733, 8.734,
        8.735, 8.736, 8.737, 8.738, 8.739, 8.74, 8.741, 8.742, 8.743, 8.744,
        8.745, 8.746, 8.747, 8.748, 8.749, 8.75, 8.751, 8.752, 8.753, 8.754,
        8.754999999999999, 8.756, 8.757, 8.758, 8.759, 8.76, 8.761, 8.762, 8.763,
        8.764, 8.765, 8.766, 8.767, 8.768, 8.769, 8.77, 8.771, 8.772, 8.773,
        8.774, 8.775, 8.776, 8.777, 8.778, 8.779, 8.78, 8.781, 8.782, 8.783,
        8.784, 8.785, 8.786, 8.786999999999999, 8.788, 8.789, 8.79, 8.791, 8.792,
        8.793, 8.794, 8.795, 8.796, 8.797, 8.798, 8.799, 8.8, 8.801, 8.802,
        8.803, 8.804, 8.805, 8.8060000000000009, 8.807, 8.808, 8.809, 8.81,
        8.811, 8.812, 8.813, 8.814, 8.815, 8.816, 8.817, 8.818,
        8.8189999999999991, 8.82, 8.821, 8.822, 8.823, 8.824, 8.825, 8.826,
        8.827, 8.828, 8.829, 8.83, 8.831, 8.832, 8.833, 8.834, 8.835, 8.836,
        8.837, 8.838000000000001, 8.839, 8.84, 8.841, 8.842, 8.843, 8.844, 8.845,
        8.846, 8.847, 8.847999999999999, 8.849, 8.85, 8.851, 8.852, 8.853, 8.854,
        8.855, 8.856, 8.857, 8.858, 8.859, 8.86, 8.861, 8.862, 8.863, 8.864,
        8.865, 8.866, 8.867, 8.868, 8.869, 8.87, 8.871, 8.872, 8.873, 8.874,
        8.875, 8.876, 8.877, 8.878, 8.879, 8.879999999999999, 8.881, 8.882,
        8.883, 8.884, 8.885, 8.886, 8.887, 8.888, 8.889, 8.89, 8.891, 8.892,
        8.893, 8.894, 8.895, 8.896, 8.897, 8.898, 8.899, 8.9, 8.901, 8.902,
        8.903, 8.904, 8.905, 8.906, 8.907, 8.908, 8.909, 8.91, 8.911,
        8.911999999999999, 8.913, 8.914, 8.915, 8.916, 8.917, 8.918, 8.919, 8.92,
        8.921, 8.922, 8.923, 8.924, 8.925, 8.926, 8.927, 8.928, 8.929, 8.93,
        8.9310000000000009, 8.932, 8.933, 8.934, 8.935, 8.936, 8.937, 8.938,
        8.939, 8.94, 8.941, 8.942, 8.943, 8.9439999999999991, 8.945, 8.946,
        8.947, 8.948, 8.949, 8.95, 8.951, 8.952, 8.953, 8.954, 8.955, 8.956,
        8.957, 8.958, 8.959, 8.96, 8.961, 8.962, 8.963000000000001, 8.964, 8.965,
        8.966, 8.967, 8.968, 8.969, 8.97, 8.971, 8.972, 8.973, 8.974, 8.975,
        8.976, 8.977, 8.978, 8.979, 8.98, 8.981, 8.982, 8.983, 8.984, 8.985,
        8.986, 8.987, 8.988, 8.989, 8.99, 8.991, 8.992, 8.993, 8.994, 8.995,
        8.996, 8.997, 8.998, 8.999, 9.0, 9.001, 9.002, 9.003, 9.004, 9.005,
        9.006, 9.007, 9.008, 9.009, 9.01, 9.011, 9.012, 9.013, 9.014, 9.015,
        9.016, 9.017, 9.018, 9.019, 9.02, 9.021, 9.022, 9.023, 9.024, 9.025,
        9.026, 9.027, 9.028, 9.029, 9.03, 9.031, 9.032, 9.033, 9.034, 9.035,
        9.036, 9.037, 9.038, 9.039, 9.04, 9.041, 9.042, 9.043, 9.044, 9.045,
        9.046, 9.047, 9.048, 9.049, 9.05, 9.051, 9.052, 9.053, 9.054, 9.055,
        9.056, 9.057, 9.058, 9.059, 9.06, 9.061, 9.062, 9.063, 9.064, 9.065,
        9.066, 9.067, 9.068, 9.0689999999999991, 9.07, 9.071, 9.072, 9.073,
        9.074, 9.075, 9.076, 9.077, 9.078, 9.079, 9.08, 9.081, 9.082, 9.083,
        9.084, 9.085, 9.086, 9.087, 9.088, 9.089, 9.09, 9.091, 9.092, 9.093,
        9.094, 9.095, 9.096, 9.097, 9.098, 9.099, 9.1, 9.101, 9.102, 9.103,
        9.104, 9.105, 9.106, 9.107, 9.108, 9.109, 9.11, 9.111, 9.112, 9.113,
        9.114, 9.115, 9.116, 9.117, 9.118, 9.119, 9.12, 9.121, 9.122, 9.123,
        9.124, 9.125, 9.126, 9.127, 9.128, 9.129, 9.13, 9.131, 9.132, 9.133,
        9.134, 9.135, 9.136, 9.137, 9.138, 9.139, 9.14, 9.141, 9.142, 9.143,
        9.144, 9.145, 9.146, 9.147, 9.148, 9.149, 9.15, 9.151, 9.152, 9.153,
        9.154, 9.155, 9.156, 9.157, 9.158, 9.159, 9.16, 9.161, 9.162, 9.163,
        9.164, 9.165, 9.166, 9.167, 9.168, 9.169, 9.17, 9.171, 9.172, 9.173,
        9.174, 9.175, 9.176, 9.177, 9.178, 9.179, 9.18, 9.181, 9.182, 9.183,
        9.184, 9.185, 9.186, 9.187, 9.188, 9.189, 9.19, 9.191, 9.192, 9.193,
        9.1939999999999991, 9.195, 9.196, 9.197, 9.198, 9.199, 9.2, 9.201, 9.202,
        9.203, 9.204, 9.205, 9.206, 9.207, 9.208, 9.209, 9.21, 9.211, 9.212,
        9.213, 9.214, 9.215, 9.216, 9.217, 9.218, 9.219, 9.22, 9.221, 9.222,
        9.223, 9.224, 9.225, 9.226, 9.227, 9.228, 9.229, 9.23, 9.231, 9.232,
        9.233, 9.234, 9.235, 9.236, 9.237, 9.238, 9.239, 9.24, 9.241, 9.242,
        9.243, 9.244, 9.245, 9.246, 9.247, 9.248, 9.249, 9.25, 9.251, 9.252,
        9.253, 9.254, 9.255, 9.256, 9.257, 9.258, 9.259, 9.26, 9.261, 9.262,
        9.263, 9.264, 9.265, 9.266, 9.267, 9.268, 9.269, 9.27, 9.271, 9.272,
        9.273, 9.274, 9.275, 9.276, 9.277, 9.278, 9.279, 9.28, 9.281, 9.282,
        9.283, 9.284, 9.285, 9.286, 9.287, 9.288, 9.289, 9.29, 9.291, 9.292,
        9.293, 9.294, 9.295, 9.296, 9.297, 9.298, 9.299, 9.3, 9.301, 9.302,
        9.303, 9.304, 9.305, 9.306, 9.307, 9.308, 9.309, 9.31, 9.311, 9.312,
        9.313, 9.314, 9.315, 9.316, 9.317, 9.318, 9.3189999999999991, 9.32,
        9.321, 9.322, 9.323, 9.324, 9.325, 9.326, 9.327, 9.328, 9.329, 9.33,
        9.331, 9.332, 9.333, 9.334, 9.335, 9.336, 9.337, 9.338, 9.339, 9.34,
        9.341, 9.342, 9.343, 9.344, 9.345, 9.346, 9.347, 9.348, 9.349, 9.35,
        9.351, 9.352, 9.353, 9.354, 9.355, 9.356, 9.357, 9.358, 9.359, 9.36,
        9.361, 9.362, 9.363, 9.364, 9.365, 9.366, 9.367, 9.368, 9.369, 9.37,
        9.371, 9.372, 9.373, 9.374, 9.375, 9.376, 9.377, 9.378, 9.379, 9.38,
        9.381, 9.382, 9.383, 9.384, 9.385, 9.386, 9.387, 9.388, 9.389, 9.39,
        9.391, 9.392, 9.393, 9.394, 9.395, 9.396, 9.397, 9.398, 9.399, 9.4,
        9.401, 9.402, 9.403, 9.404, 9.405, 9.406, 9.407, 9.408, 9.409, 9.41,
        9.411, 9.412, 9.413, 9.414, 9.415, 9.416, 9.417, 9.418, 9.419, 9.42,
        9.421, 9.422, 9.423, 9.424, 9.425, 9.426, 9.427, 9.428, 9.429, 9.43,
        9.431, 9.432, 9.433, 9.434, 9.435, 9.436, 9.437, 9.438, 9.439, 9.44,
        9.441, 9.442, 9.443, 9.4439999999999991, 9.445, 9.446, 9.447, 9.448,
        9.449, 9.45, 9.451, 9.452, 9.453, 9.454, 9.455, 9.456, 9.457, 9.458,
        9.459, 9.46, 9.461, 9.462, 9.463, 9.464, 9.465, 9.466, 9.467, 9.468,
        9.469, 9.47, 9.471, 9.472, 9.473, 9.474, 9.475, 9.476, 9.477, 9.478,
        9.479, 9.48, 9.481, 9.482, 9.483, 9.484, 9.485, 9.486, 9.487, 9.488,
        9.489, 9.49, 9.491, 9.492, 9.493, 9.494, 9.495, 9.496, 9.497, 9.498,
        9.499, 9.5, 9.501, 9.502, 9.503, 9.504, 9.505, 9.506, 9.507, 9.508,
        9.509, 9.51, 9.511, 9.512, 9.513, 9.514, 9.515, 9.516, 9.517, 9.518,
        9.519, 9.52, 9.521, 9.522, 9.523, 9.524, 9.525, 9.526, 9.527, 9.528,
        9.529, 9.53, 9.531, 9.532, 9.533, 9.534, 9.535, 9.536, 9.537, 9.538,
        9.539, 9.54, 9.541, 9.542, 9.543, 9.544, 9.545, 9.546, 9.547, 9.548,
        9.549, 9.55, 9.551, 9.552, 9.553, 9.554, 9.555, 9.556, 9.557, 9.558,
        9.559, 9.56, 9.561, 9.562, 9.563, 9.564, 9.565, 9.566, 9.567, 9.568,
        9.569, 9.57, 9.571, 9.572, 9.573, 9.574, 9.575, 9.576, 9.577, 9.578,
        9.579, 9.58, 9.581, 9.582, 9.583, 9.584, 9.585, 9.586, 9.587, 9.588,
        9.589, 9.59, 9.591, 9.592, 9.593, 9.594, 9.595, 9.596, 9.597, 9.598,
        9.599, 9.6, 9.601, 9.602, 9.603, 9.604, 9.605, 9.606, 9.607, 9.608,
        9.609, 9.61, 9.611, 9.612, 9.613, 9.614, 9.615, 9.616, 9.617, 9.618,
        9.619, 9.62, 9.621, 9.622, 9.623, 9.624, 9.625, 9.626, 9.627, 9.628,
        9.629, 9.63, 9.631, 9.632, 9.633, 9.634, 9.635, 9.636, 9.637, 9.638,
        9.639, 9.64, 9.641, 9.642, 9.643, 9.644, 9.645, 9.646, 9.647, 9.648,
        9.649, 9.65, 9.651, 9.652, 9.653, 9.654, 9.655, 9.656, 9.657, 9.658,
        9.659, 9.66, 9.661, 9.662, 9.663, 9.664, 9.665, 9.666, 9.667, 9.668,
        9.669, 9.67, 9.671, 9.672, 9.673, 9.674, 9.675, 9.676, 9.677, 9.678,
        9.679, 9.68, 9.681, 9.682, 9.683, 9.684, 9.685, 9.686, 9.687, 9.688,
        9.689, 9.69, 9.691, 9.692, 9.693, 9.694, 9.695, 9.696, 9.697, 9.698,
        9.699, 9.7, 9.701, 9.702, 9.703, 9.704, 9.705, 9.706, 9.707, 9.708,
        9.709, 9.71, 9.711, 9.712, 9.713, 9.714, 9.715, 9.716, 9.717, 9.718,
        9.719, 9.72, 9.721, 9.722, 9.723, 9.724, 9.725, 9.726, 9.727, 9.728,
        9.729, 9.73, 9.731, 9.732, 9.733, 9.734, 9.735, 9.736, 9.737, 9.738,
        9.739, 9.74, 9.741, 9.742, 9.743, 9.744, 9.745, 9.746, 9.747, 9.748,
        9.749, 9.75, 9.751, 9.752, 9.753, 9.754, 9.755, 9.756, 9.757, 9.758,
        9.759, 9.76, 9.761, 9.762, 9.763, 9.764, 9.765, 9.766, 9.767, 9.768,
        9.769, 9.77, 9.771, 9.772, 9.773, 9.774, 9.775, 9.776, 9.777, 9.778,
        9.779, 9.78, 9.781, 9.782, 9.783, 9.784, 9.785, 9.786, 9.787, 9.788,
        9.789, 9.79, 9.791, 9.792, 9.793, 9.794, 9.795, 9.796, 9.797, 9.798,
        9.799, 9.8, 9.801, 9.802, 9.803, 9.804, 9.805, 9.806, 9.807, 9.808,
        9.809, 9.81, 9.811, 9.812, 9.813, 9.814, 9.815, 9.816, 9.817, 9.818,
        9.819, 9.82, 9.821, 9.822, 9.823, 9.824, 9.825, 9.826, 9.827, 9.828,
        9.829, 9.83, 9.831, 9.832, 9.833, 9.834, 9.835, 9.836, 9.837, 9.838,
        9.839, 9.84, 9.841, 9.842, 9.843, 9.844, 9.845, 9.846, 9.847, 9.848,
        9.849, 9.85, 9.851, 9.852, 9.853, 9.854, 9.855, 9.856, 9.857, 9.858,
        9.859, 9.86, 9.861, 9.862, 9.863, 9.864, 9.865, 9.866, 9.867, 9.868,
        9.869, 9.87, 9.871, 9.872, 9.873, 9.874, 9.875, 9.876, 9.877, 9.878,
        9.879, 9.88, 9.881, 9.882, 9.883, 9.884, 9.885, 9.886, 9.887, 9.888,
        9.889, 9.89, 9.891, 9.892, 9.893, 9.894, 9.895, 9.896, 9.897, 9.898,
        9.899, 9.9, 9.901, 9.902, 9.903, 9.904, 9.905, 9.906, 9.907, 9.908,
        9.909, 9.91, 9.911, 9.912, 9.913, 9.914, 9.915, 9.916, 9.917, 9.918,
        9.919, 9.92, 9.921, 9.922, 9.923, 9.924, 9.925, 9.926, 9.927, 9.928,
        9.929, 9.93, 9.931, 9.932, 9.933, 9.934, 9.935, 9.936, 9.937, 9.938,
        9.939, 9.94, 9.941, 9.942, 9.943, 9.944, 9.945, 9.946, 9.947, 9.948,
        9.949, 9.95, 9.951, 9.952, 9.953, 9.954, 9.955, 9.956, 9.957, 9.958,
        9.959, 9.96, 9.961, 9.962, 9.963, 9.964, 9.965, 9.966, 9.967, 9.968,
        9.969, 9.97, 9.971, 9.972, 9.973, 9.974, 9.975, 9.976, 9.977, 9.978,
        9.979, 9.98, 9.981, 9.982, 9.983, 9.984, 9.985, 9.986, 9.987, 9.988,
        9.989, 9.99, 9.991, 9.992, 9.993, 9.994, 9.995, 9.996, 9.997, 9.998,
        9.999, 10.0 } ;

      static real_T pDataValues0[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } ;

      final23_vcontrol_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
      final23_vcontrol_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
      final23_vcontrol_DW.FromWorkspace_IWORK.PrevIndex = 0;
    }

    /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Start_wrapper(&final23_vcontrol_DW.QuadEncoder2axis_DSTATE,
      &final23_vcontrol_P.QuadEncoder2axis_P1, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P2, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P3, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P4, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P5, 1,
      &final23_vcontrol_P.QuadEncoder2axis_P6, 1);
    final23_vco_MovingAverage_Start(&final23_vcontrol_DW.MovingAverage);

    /* Start for MATLABSystem: '<Root>/PWM' */
    final23_vcontrol_DW.obj_g.matlabCodegenIsDeleted = false;
    final23_vcontrol_DW.objisempty_l = true;
    final23_vcontrol_DW.obj_g.isInitialized = 1;
    final23_vcontrol_DW.obj_g.PinNumber = 19U;
    ret = EXT_PWMBlock_init(final23_vcontrol_DW.obj_g.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_B.b[0], final23_vcontrol_DW.obj_g.PinNumber);
    }

    final23_vcontrol_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */

    /* Start for MATLABSystem: '<Root>/PWM1' */
    final23_vcontrol_DW.obj_e.matlabCodegenIsDeleted = false;
    final23_vcontrol_DW.objisempty_p = true;
    final23_vcontrol_DW.obj_e.isInitialized = 1;
    final23_vcontrol_DW.obj_e.PinNumber = 26U;
    ret = EXT_PWMBlock_init(final23_vcontrol_DW.obj_e.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_B.b[0], final23_vcontrol_DW.obj_e.PinNumber);
    }

    final23_vcontrol_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM1' */
    final23_vco_MovingAverage_Start(&final23_vcontrol_DW.MovingAverage1);

    /* Start for MATLABSystem: '<Root>/PWM2' */
    final23_vcontrol_DW.obj_p.matlabCodegenIsDeleted = false;
    final23_vcontrol_DW.objisempty_d = true;
    final23_vcontrol_DW.obj_p.isInitialized = 1;
    final23_vcontrol_DW.obj_p.PinNumber = 20U;
    ret = EXT_PWMBlock_init(final23_vcontrol_DW.obj_p.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_B.b[0], final23_vcontrol_DW.obj_p.PinNumber);
    }

    final23_vcontrol_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM2' */

    /* Start for MATLABSystem: '<Root>/PWM3' */
    final23_vcontrol_DW.obj.matlabCodegenIsDeleted = false;
    final23_vcontrol_DW.objisempty = true;
    final23_vcontrol_DW.obj.isInitialized = 1;
    final23_vcontrol_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(final23_vcontrol_DW.obj.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        final23_vcontrol_B.b[ret] = tmp[ret];
      }

      printf(&final23_vcontrol_B.b[0], final23_vcontrol_DW.obj.PinNumber);
    }

    final23_vcontrol_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM3' */
  }

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        final23_vcontrol_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for Delay: '<S3>/Delay' */
  final23_vcontrol_DW.Delay_DSTATE = final23_vcontrol_P.Delay_InitialCondition;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  final23_vcontrol_X.Integrator_CSTATE = final23_vcontrol_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  final23_vcontrol_DW.TimeStampA = (rtInf);
  final23_vcontrol_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Delay: '<S4>/Delay1' */
  final23_vcontrol_DW.Delay1_DSTATE = final23_vcontrol_P.Delay1_InitialCondition;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  final23_vcontrol_X.Integrator_CSTATE_l = final23_vcontrol_P.Integrator_IC_m;

  /* InitializeConditions for Derivative: '<S6>/Derivative' */
  final23_vcontrol_DW.TimeStampA_a = (rtInf);
  final23_vcontrol_DW.TimeStampB_o = (rtInf);
  final23_vcon_MovingAverage_Init(&final23_vcontrol_DW.MovingAverage);
  final23_vcon_MovingAverage_Init(&final23_vcontrol_DW.MovingAverage1);
}

/* Model terminate function */
void final23_vcontrol_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper
    (&final23_vcontrol_DW.QuadEncoder2axis_DSTATE,
     &final23_vcontrol_P.QuadEncoder2axis_P1, 1,
     &final23_vcontrol_P.QuadEncoder2axis_P2, 1,
     &final23_vcontrol_P.QuadEncoder2axis_P3, 1,
     &final23_vcontrol_P.QuadEncoder2axis_P4, 1,
     &final23_vcontrol_P.QuadEncoder2axis_P5, 1,
     &final23_vcontrol_P.QuadEncoder2axis_P6, 1);
  final23_vcon_MovingAverage_Term(&final23_vcontrol_DW.MovingAverage);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!final23_vcontrol_DW.obj_g.matlabCodegenIsDeleted) {
    final23_vcontrol_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_DW.obj_g.isInitialized == 1) &&
        final23_vcontrol_DW.obj_g.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_DW.obj_g.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */

  /* Terminate for MATLABSystem: '<Root>/PWM1' */
  if (!final23_vcontrol_DW.obj_e.matlabCodegenIsDeleted) {
    final23_vcontrol_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_DW.obj_e.isInitialized == 1) &&
        final23_vcontrol_DW.obj_e.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_DW.obj_e.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM1' */
  final23_vcon_MovingAverage_Term(&final23_vcontrol_DW.MovingAverage1);

  /* Terminate for MATLABSystem: '<Root>/PWM2' */
  if (!final23_vcontrol_DW.obj_p.matlabCodegenIsDeleted) {
    final23_vcontrol_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_DW.obj_p.isInitialized == 1) &&
        final23_vcontrol_DW.obj_p.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_DW.obj_p.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM2' */

  /* Terminate for MATLABSystem: '<Root>/PWM3' */
  if (!final23_vcontrol_DW.obj.matlabCodegenIsDeleted) {
    final23_vcontrol_DW.obj.matlabCodegenIsDeleted = true;
    if ((final23_vcontrol_DW.obj.isInitialized == 1) &&
        final23_vcontrol_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(final23_vcontrol_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM3' */
}
