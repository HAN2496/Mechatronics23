/*
 * problem1_2s.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "problem1_2s".
 *
 * Model version              : 1.46
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Dec 14 22:14:33 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "problem1_2s.h"
#include "problem1_2s_private.h"

/* Block signals (default storage) */
B_problem1_2s_T problem1_2s_B;

/* Continuous states */
X_problem1_2s_T problem1_2s_X;

/* Block states (default storage) */
DW_problem1_2s_T problem1_2s_DW;

/* Real-time model */
static RT_MODEL_problem1_2s_T problem1_2s_M_;
RT_MODEL_problem1_2s_T *const problem1_2s_M = &problem1_2s_M_;

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
  problem1_2s_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  problem1_2s_step();
  problem1_2s_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  problem1_2s_step();
  problem1_2s_derivatives();

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

/* Model step function */
void problem1_2s_step(void)
{
  if (rtmIsMajorTimeStep(problem1_2s_M)) {
    /* set solver stop time */
    if (!(problem1_2s_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&problem1_2s_M->solverInfo,
                            ((problem1_2s_M->Timing.clockTickH0 + 1) *
        problem1_2s_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&problem1_2s_M->solverInfo,
                            ((problem1_2s_M->Timing.clockTick0 + 1) *
        problem1_2s_M->Timing.stepSize0 + problem1_2s_M->Timing.clockTickH0 *
        problem1_2s_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(problem1_2s_M)) {
    problem1_2s_M->Timing.t[0] = rtsiGetT(&problem1_2s_M->solverInfo);
  }

  {
    real_T rtb_Sum;
    real_T rtb_Sum_a;
    real_T rtb_Switch;
    real_T *lastU;

    /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
    Quad_Encoder_sfn_Outputs_wrapper(&problem1_2s_B.QuadEncoder2axis_o1,
      &problem1_2s_B.QuadEncoder2axis_o2,
      &problem1_2s_DW.QuadEncoder2axis_DSTATE,
      &problem1_2s_P.QuadEncoder2axis_P1, 1, &problem1_2s_P.QuadEncoder2axis_P2,
      1, &problem1_2s_P.QuadEncoder2axis_P3, 1,
      &problem1_2s_P.QuadEncoder2axis_P4, 1, &problem1_2s_P.QuadEncoder2axis_P5,
      1, &problem1_2s_P.QuadEncoder2axis_P6, 1);

    /* Gain: '<Root>/Encoder Gain1' */
    problem1_2s_B.EncoderGain1 = (int64_T)problem1_2s_P.EncoderGain1_Gain *
      problem1_2s_B.QuadEncoder2axis_o1;

    /* Product: '<Root>/X position' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Gain: '<Root>/Encoder Gain1'
     */
    problem1_2s_B.Xposition = (real_T)problem1_2s_B.EncoderGain1 *
      3.637978807091713E-12 * problem1_2s_P.Constant2_Value;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant'
     */
    problem1_2s_B.Sum1 = problem1_2s_P.Constant_Value - problem1_2s_B.Xposition;

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Derivative: '<S4>/Derivative'
     */
    rtb_Sum_a = problem1_2s_M->Timing.t[0];
    if ((problem1_2s_DW.TimeStampA >= rtb_Sum_a) && (problem1_2s_DW.TimeStampB >=
         rtb_Sum_a)) {
      rtb_Switch = 0.0;
    } else {
      rtb_Switch = problem1_2s_DW.TimeStampA;
      lastU = &problem1_2s_DW.LastUAtTimeA;
      if (problem1_2s_DW.TimeStampA < problem1_2s_DW.TimeStampB) {
        if (problem1_2s_DW.TimeStampB < rtb_Sum_a) {
          rtb_Switch = problem1_2s_DW.TimeStampB;
          lastU = &problem1_2s_DW.LastUAtTimeB;
        }
      } else if (problem1_2s_DW.TimeStampA >= rtb_Sum_a) {
        rtb_Switch = problem1_2s_DW.TimeStampB;
        lastU = &problem1_2s_DW.LastUAtTimeB;
      }

      rtb_Switch = (problem1_2s_B.Sum1 - *lastU) / (rtb_Sum_a - rtb_Switch);
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* Sum: '<S3>/Sum' incorporates:
     *  Gain: '<S3>/D Gain'
     *  Gain: '<S3>/I Gain'
     *  Gain: '<S3>/P Gain'
     *  Integrator: '<S3>/Integrator'
     */
    rtb_Sum = (problem1_2s_P.PGain_Gain * problem1_2s_B.Sum1 +
               problem1_2s_P.IGain_Gain * problem1_2s_X.Integrator_CSTATE) +
      problem1_2s_P.DGain_Gain * rtb_Switch;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    if (rtb_Sum > problem1_2s_P.Switch1_Threshold) {
      rtb_Switch = rtb_Sum;
    } else {
      rtb_Switch = problem1_2s_P.Constant_Value_d;
    }

    /* End of Switch: '<S1>/Switch1' */

    /* Gain: '<S1>/GPIO19 Gain' */
    rtb_Switch *= problem1_2s_P.GPIO19Gain_Gain;

    /* MATLABSystem: '<Root>/PWM' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(problem1_2s_DW.obj_g.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM' */

    /* Switch: '<S1>/Switch' incorporates:
     *  Abs: '<S1>/Abs'
     *  Constant: '<S1>/Constant'
     */
    if (rtb_Sum > problem1_2s_P.Switch_Threshold) {
      rtb_Sum = problem1_2s_P.Constant_Value_d;
    } else {
      rtb_Sum = fabs(rtb_Sum);
    }

    /* End of Switch: '<S1>/Switch' */

    /* Gain: '<S1>/GPIO26 Gain' */
    rtb_Switch = problem1_2s_P.GPIO26Gain_Gain * rtb_Sum;

    /* MATLABSystem: '<Root>/PWM1' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(problem1_2s_DW.obj_e.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM1' */
    if (rtmIsMajorTimeStep(problem1_2s_M)) {
    }

    /* Gain: '<Root>/Encoder Gain2' */
    problem1_2s_B.EncoderGain2 = (int64_T)problem1_2s_P.EncoderGain2_Gain *
      problem1_2s_B.QuadEncoder2axis_o2;

    /* Product: '<Root>/Y position' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Gain: '<Root>/Encoder Gain2'
     */
    problem1_2s_B.Yposition = (real_T)problem1_2s_B.EncoderGain2 *
      3.637978807091713E-12 * problem1_2s_P.Constant2_Value;
    if (rtmIsMajorTimeStep(problem1_2s_M)) {
    }

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    problem1_2s_B.Sum2 = problem1_2s_P.Constant1_Value - problem1_2s_B.Yposition;

    /* Derivative: '<S4>/Derivative' */
    if ((problem1_2s_DW.TimeStampA_n >= rtb_Sum_a) &&
        (problem1_2s_DW.TimeStampB_a >= rtb_Sum_a)) {
      rtb_Switch = 0.0;
    } else {
      rtb_Switch = problem1_2s_DW.TimeStampA_n;
      lastU = &problem1_2s_DW.LastUAtTimeA_k;
      if (problem1_2s_DW.TimeStampA_n < problem1_2s_DW.TimeStampB_a) {
        if (problem1_2s_DW.TimeStampB_a < rtb_Sum_a) {
          rtb_Switch = problem1_2s_DW.TimeStampB_a;
          lastU = &problem1_2s_DW.LastUAtTimeB_c;
        }
      } else if (problem1_2s_DW.TimeStampA_n >= rtb_Sum_a) {
        rtb_Switch = problem1_2s_DW.TimeStampB_a;
        lastU = &problem1_2s_DW.LastUAtTimeB_c;
      }

      rtb_Switch = (problem1_2s_B.Sum2 - *lastU) / (rtb_Sum_a - rtb_Switch);
    }

    /* Sum: '<S4>/Sum' incorporates:
     *  Gain: '<S4>/D Gain'
     *  Gain: '<S4>/I Gain'
     *  Gain: '<S4>/P Gain'
     *  Integrator: '<S4>/Integrator'
     */
    rtb_Sum_a = (problem1_2s_P.PGain_Gain_c * problem1_2s_B.Sum2 +
                 problem1_2s_P.IGain_Gain_a * problem1_2s_X.Integrator_CSTATE_b)
      + problem1_2s_P.DGain_Gain_c * rtb_Switch;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Constant: '<S2>/Constant'
     */
    if (rtb_Sum_a > problem1_2s_P.Switch1_Threshold_c) {
      rtb_Switch = rtb_Sum_a;
    } else {
      rtb_Switch = problem1_2s_P.Constant_Value_e;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Gain: '<S2>/GPIO20 Gain' */
    rtb_Switch *= problem1_2s_P.GPIO20Gain_Gain;

    /* MATLABSystem: '<Root>/PWM2' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(problem1_2s_DW.obj_p.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM2' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Abs: '<S2>/Abs'
     *  Constant: '<S2>/Constant'
     */
    if (rtb_Sum_a > problem1_2s_P.Switch_Threshold_m) {
      rtb_Sum_a = problem1_2s_P.Constant_Value_e;
    } else {
      rtb_Sum_a = fabs(rtb_Sum_a);
    }

    /* End of Switch: '<S2>/Switch' */

    /* Gain: '<S2>/GPIO21 Gain' */
    rtb_Switch = problem1_2s_P.GPIO21Gain_Gain * rtb_Sum_a;

    /* MATLABSystem: '<Root>/PWM3' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(problem1_2s_DW.obj.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM3' */
    if (rtmIsMajorTimeStep(problem1_2s_M)) {
    }
  }

  if (rtmIsMajorTimeStep(problem1_2s_M)) {
    real_T *lastU;

    /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Update_wrapper(&problem1_2s_B.QuadEncoder2axis_o1,
      &problem1_2s_B.QuadEncoder2axis_o2,
      &problem1_2s_DW.QuadEncoder2axis_DSTATE,
      &problem1_2s_P.QuadEncoder2axis_P1, 1, &problem1_2s_P.QuadEncoder2axis_P2,
      1, &problem1_2s_P.QuadEncoder2axis_P3, 1,
      &problem1_2s_P.QuadEncoder2axis_P4, 1, &problem1_2s_P.QuadEncoder2axis_P5,
      1, &problem1_2s_P.QuadEncoder2axis_P6, 1);

    /* Update for Derivative: '<S3>/Derivative' */
    if (problem1_2s_DW.TimeStampA == (rtInf)) {
      problem1_2s_DW.TimeStampA = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeA;
    } else if (problem1_2s_DW.TimeStampB == (rtInf)) {
      problem1_2s_DW.TimeStampB = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeB;
    } else if (problem1_2s_DW.TimeStampA < problem1_2s_DW.TimeStampB) {
      problem1_2s_DW.TimeStampA = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeA;
    } else {
      problem1_2s_DW.TimeStampB = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeB;
    }

    *lastU = problem1_2s_B.Sum1;

    /* End of Update for Derivative: '<S3>/Derivative' */

    /* Update for Derivative: '<S4>/Derivative' */
    if (problem1_2s_DW.TimeStampA_n == (rtInf)) {
      problem1_2s_DW.TimeStampA_n = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeA_k;
    } else if (problem1_2s_DW.TimeStampB_a == (rtInf)) {
      problem1_2s_DW.TimeStampB_a = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeB_c;
    } else if (problem1_2s_DW.TimeStampA_n < problem1_2s_DW.TimeStampB_a) {
      problem1_2s_DW.TimeStampA_n = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeA_k;
    } else {
      problem1_2s_DW.TimeStampB_a = problem1_2s_M->Timing.t[0];
      lastU = &problem1_2s_DW.LastUAtTimeB_c;
    }

    *lastU = problem1_2s_B.Sum2;

    /* End of Update for Derivative: '<S4>/Derivative' */

    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, (real_T)problem1_2s_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(problem1_2s_M)) {/* Sample time: [0.001s, 0.0s] */
      rtExtModeUpload(1, (real_T)(((problem1_2s_M->Timing.clockTick1+
        problem1_2s_M->Timing.clockTickH1* 4294967296.0)) * 0.001));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(problem1_2s_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(problem1_2s_M)!=-1) &&
          !((rtmGetTFinal(problem1_2s_M)-(((problem1_2s_M->Timing.clockTick1+
               problem1_2s_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((problem1_2s_M->Timing.clockTick1+
               problem1_2s_M->Timing.clockTickH1* 4294967296.0)) * 0.001) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(problem1_2s_M, "Simulation finished");
      }

      if (rtmGetStopRequested(problem1_2s_M)) {
        rtmSetErrorStatus(problem1_2s_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&problem1_2s_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++problem1_2s_M->Timing.clockTick0)) {
      ++problem1_2s_M->Timing.clockTickH0;
    }

    problem1_2s_M->Timing.t[0] = rtsiGetSolverStopTime
      (&problem1_2s_M->solverInfo);

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
      problem1_2s_M->Timing.clockTick1++;
      if (!problem1_2s_M->Timing.clockTick1) {
        problem1_2s_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void problem1_2s_derivatives(void)
{
  XDot_problem1_2s_T *_rtXdot;
  _rtXdot = ((XDot_problem1_2s_T *) problem1_2s_M->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = problem1_2s_B.Sum1;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_b = problem1_2s_B.Sum2;
}

/* Model initialize function */
void problem1_2s_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)problem1_2s_M, 0,
                sizeof(RT_MODEL_problem1_2s_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&problem1_2s_M->solverInfo,
                          &problem1_2s_M->Timing.simTimeStep);
    rtsiSetTPtr(&problem1_2s_M->solverInfo, &rtmGetTPtr(problem1_2s_M));
    rtsiSetStepSizePtr(&problem1_2s_M->solverInfo,
                       &problem1_2s_M->Timing.stepSize0);
    rtsiSetdXPtr(&problem1_2s_M->solverInfo, &problem1_2s_M->derivs);
    rtsiSetContStatesPtr(&problem1_2s_M->solverInfo, (real_T **)
                         &problem1_2s_M->contStates);
    rtsiSetNumContStatesPtr(&problem1_2s_M->solverInfo,
      &problem1_2s_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&problem1_2s_M->solverInfo,
      &problem1_2s_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&problem1_2s_M->solverInfo,
      &problem1_2s_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&problem1_2s_M->solverInfo,
      &problem1_2s_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&problem1_2s_M->solverInfo, (&rtmGetErrorStatus
      (problem1_2s_M)));
    rtsiSetRTModelPtr(&problem1_2s_M->solverInfo, problem1_2s_M);
  }

  rtsiSetSimTimeStep(&problem1_2s_M->solverInfo, MAJOR_TIME_STEP);
  problem1_2s_M->intgData.y = problem1_2s_M->odeY;
  problem1_2s_M->intgData.f[0] = problem1_2s_M->odeF[0];
  problem1_2s_M->intgData.f[1] = problem1_2s_M->odeF[1];
  problem1_2s_M->intgData.f[2] = problem1_2s_M->odeF[2];
  problem1_2s_M->contStates = ((X_problem1_2s_T *) &problem1_2s_X);
  rtsiSetSolverData(&problem1_2s_M->solverInfo, (void *)&problem1_2s_M->intgData);
  rtsiSetSolverName(&problem1_2s_M->solverInfo,"ode3");
  rtmSetTPtr(problem1_2s_M, &problem1_2s_M->Timing.tArray[0]);
  rtmSetTFinal(problem1_2s_M, -1);
  problem1_2s_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  problem1_2s_M->Sizes.checksums[0] = (2983932367U);
  problem1_2s_M->Sizes.checksums[1] = (1250427754U);
  problem1_2s_M->Sizes.checksums[2] = (3704669492U);
  problem1_2s_M->Sizes.checksums[3] = (2701860128U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    problem1_2s_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(problem1_2s_M->extModeInfo,
      &problem1_2s_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(problem1_2s_M->extModeInfo,
                        problem1_2s_M->Sizes.checksums);
    rteiSetTPtr(problem1_2s_M->extModeInfo, rtmGetTPtr(problem1_2s_M));
  }

  /* block I/O */
  (void) memset(((void *) &problem1_2s_B), 0,
                sizeof(B_problem1_2s_T));

  {
    problem1_2s_B.EncoderGain1 = (0LL);
    problem1_2s_B.EncoderGain2 = (0LL);
  }

  /* states (continuous) */
  {
    (void) memset((void *)&problem1_2s_X, 0,
                  sizeof(X_problem1_2s_T));
  }

  /* states (dwork) */
  (void) memset((void *)&problem1_2s_DW, 0,
                sizeof(DW_problem1_2s_T));

  {
    int32_T ret;
    char_T b[45];
    static const char_T tmp[45] =
      "Unable to configure pin %u for PWM output.\\n";

    /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Start_wrapper(&problem1_2s_DW.QuadEncoder2axis_DSTATE,
      &problem1_2s_P.QuadEncoder2axis_P1, 1, &problem1_2s_P.QuadEncoder2axis_P2,
      1, &problem1_2s_P.QuadEncoder2axis_P3, 1,
      &problem1_2s_P.QuadEncoder2axis_P4, 1, &problem1_2s_P.QuadEncoder2axis_P5,
      1, &problem1_2s_P.QuadEncoder2axis_P6, 1);

    /* Start for MATLABSystem: '<Root>/PWM' */
    problem1_2s_DW.obj_g.matlabCodegenIsDeleted = false;
    problem1_2s_DW.objisempty_l = true;
    problem1_2s_DW.obj_g.isInitialized = 1;
    problem1_2s_DW.obj_g.PinNumber = 19U;
    ret = EXT_PWMBlock_init(problem1_2s_DW.obj_g.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], problem1_2s_DW.obj_g.PinNumber);
    }

    problem1_2s_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */

    /* Start for MATLABSystem: '<Root>/PWM1' */
    problem1_2s_DW.obj_e.matlabCodegenIsDeleted = false;
    problem1_2s_DW.objisempty_p = true;
    problem1_2s_DW.obj_e.isInitialized = 1;
    problem1_2s_DW.obj_e.PinNumber = 26U;
    ret = EXT_PWMBlock_init(problem1_2s_DW.obj_e.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], problem1_2s_DW.obj_e.PinNumber);
    }

    problem1_2s_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM1' */
    /* Start for MATLABSystem: '<Root>/PWM2' */
    problem1_2s_DW.obj_p.matlabCodegenIsDeleted = false;
    problem1_2s_DW.objisempty_d = true;
    problem1_2s_DW.obj_p.isInitialized = 1;
    problem1_2s_DW.obj_p.PinNumber = 20U;
    ret = EXT_PWMBlock_init(problem1_2s_DW.obj_p.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], problem1_2s_DW.obj_p.PinNumber);
    }

    problem1_2s_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM2' */

    /* Start for MATLABSystem: '<Root>/PWM3' */
    problem1_2s_DW.obj.matlabCodegenIsDeleted = false;
    problem1_2s_DW.objisempty = true;
    problem1_2s_DW.obj.isInitialized = 1;
    problem1_2s_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(problem1_2s_DW.obj.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], problem1_2s_DW.obj.PinNumber);
    }

    problem1_2s_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM3' */
  }

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        problem1_2s_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  problem1_2s_X.Integrator_CSTATE = problem1_2s_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S3>/Derivative' */
  problem1_2s_DW.TimeStampA = (rtInf);
  problem1_2s_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  problem1_2s_X.Integrator_CSTATE_b = problem1_2s_P.Integrator_IC_h;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  problem1_2s_DW.TimeStampA_n = (rtInf);
  problem1_2s_DW.TimeStampB_a = (rtInf);
}

/* Model terminate function */
void problem1_2s_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper(&problem1_2s_DW.QuadEncoder2axis_DSTATE,
    &problem1_2s_P.QuadEncoder2axis_P1, 1, &problem1_2s_P.QuadEncoder2axis_P2, 1,
    &problem1_2s_P.QuadEncoder2axis_P3, 1, &problem1_2s_P.QuadEncoder2axis_P4, 1,
    &problem1_2s_P.QuadEncoder2axis_P5, 1, &problem1_2s_P.QuadEncoder2axis_P6, 1);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!problem1_2s_DW.obj_g.matlabCodegenIsDeleted) {
    problem1_2s_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((problem1_2s_DW.obj_g.isInitialized == 1) &&
        problem1_2s_DW.obj_g.isSetupComplete) {
      EXT_PWMBlock_terminate(problem1_2s_DW.obj_g.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */

  /* Terminate for MATLABSystem: '<Root>/PWM1' */
  if (!problem1_2s_DW.obj_e.matlabCodegenIsDeleted) {
    problem1_2s_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((problem1_2s_DW.obj_e.isInitialized == 1) &&
        problem1_2s_DW.obj_e.isSetupComplete) {
      EXT_PWMBlock_terminate(problem1_2s_DW.obj_e.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM1' */
  /* Terminate for MATLABSystem: '<Root>/PWM2' */
  if (!problem1_2s_DW.obj_p.matlabCodegenIsDeleted) {
    problem1_2s_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((problem1_2s_DW.obj_p.isInitialized == 1) &&
        problem1_2s_DW.obj_p.isSetupComplete) {
      EXT_PWMBlock_terminate(problem1_2s_DW.obj_p.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM2' */

  /* Terminate for MATLABSystem: '<Root>/PWM3' */
  if (!problem1_2s_DW.obj.matlabCodegenIsDeleted) {
    problem1_2s_DW.obj.matlabCodegenIsDeleted = true;
    if ((problem1_2s_DW.obj.isInitialized == 1) &&
        problem1_2s_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(problem1_2s_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM3' */
}
