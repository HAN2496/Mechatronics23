/*
 * test1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "test1".
 *
 * Model version              : 1.17
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 22:13:02 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test1.h"
#include "test1_private.h"

/* Block signals (default storage) */
B_test1_T test1_B;

/* Continuous states */
X_test1_T test1_X;

/* Block states (default storage) */
DW_test1_T test1_DW;

/* Real-time model */
static RT_MODEL_test1_T test1_M_;
RT_MODEL_test1_T *const test1_M = &test1_M_;

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
  test1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  test1_step();
  test1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  test1_step();
  test1_derivatives();

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
void test1_step(void)
{
  if (rtmIsMajorTimeStep(test1_M)) {
    /* set solver stop time */
    if (!(test1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&test1_M->solverInfo, ((test1_M->Timing.clockTickH0
        + 1) * test1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&test1_M->solverInfo, ((test1_M->Timing.clockTick0 +
        1) * test1_M->Timing.stepSize0 + test1_M->Timing.clockTickH0 *
        test1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(test1_M)) {
    test1_M->Timing.t[0] = rtsiGetT(&test1_M->solverInfo);
  }

  {
    real_T rtb_Sum;
    real_T rtb_Sum_b;
    real_T rtb_Switch;
    real_T *lastU;

    /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
    Quad_Encoder_sfn_Outputs_wrapper(&test1_B.QuadEncoder2axis_o1,
      &test1_B.QuadEncoder2axis_o2, &test1_DW.QuadEncoder2axis_DSTATE,
      &test1_P.QuadEncoder2axis_P1, 1, &test1_P.QuadEncoder2axis_P2, 1,
      &test1_P.QuadEncoder2axis_P3, 1, &test1_P.QuadEncoder2axis_P4, 1,
      &test1_P.QuadEncoder2axis_P5, 1, &test1_P.QuadEncoder2axis_P6, 1);

    /* Gain: '<Root>/Encoder Gain1' */
    test1_B.EncoderGain1 = (int64_T)test1_P.EncoderGain1_Gain *
      test1_B.QuadEncoder2axis_o1;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant'
     *  Gain: '<Root>/Encoder Gain1'
     */
    test1_B.Sum1 = test1_P.Constant_Value - (real_T)test1_B.EncoderGain1 *
      3.637978807091713E-12;

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Derivative: '<S4>/Derivative'
     */
    rtb_Sum_b = test1_M->Timing.t[0];
    if ((test1_DW.TimeStampA >= rtb_Sum_b) && (test1_DW.TimeStampB >= rtb_Sum_b))
    {
      rtb_Switch = 0.0;
    } else {
      rtb_Switch = test1_DW.TimeStampA;
      lastU = &test1_DW.LastUAtTimeA;
      if (test1_DW.TimeStampA < test1_DW.TimeStampB) {
        if (test1_DW.TimeStampB < rtb_Sum_b) {
          rtb_Switch = test1_DW.TimeStampB;
          lastU = &test1_DW.LastUAtTimeB;
        }
      } else if (test1_DW.TimeStampA >= rtb_Sum_b) {
        rtb_Switch = test1_DW.TimeStampB;
        lastU = &test1_DW.LastUAtTimeB;
      }

      rtb_Switch = (test1_B.Sum1 - *lastU) / (rtb_Sum_b - rtb_Switch);
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* Sum: '<S3>/Sum' incorporates:
     *  Gain: '<S3>/D Gain'
     *  Gain: '<S3>/I Gain'
     *  Gain: '<S3>/P Gain'
     *  Integrator: '<S3>/Integrator'
     */
    rtb_Sum = (test1_P.PGain_Gain * test1_B.Sum1 + test1_P.IGain_Gain *
               test1_X.Integrator_CSTATE) + test1_P.DGain_Gain * rtb_Switch;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    if (rtb_Sum > test1_P.Switch1_Threshold) {
      rtb_Switch = rtb_Sum;
    } else {
      rtb_Switch = test1_P.Constant_Value_d;
    }

    /* End of Switch: '<S1>/Switch1' */

    /* Gain: '<S1>/GPIO19 Gain' */
    rtb_Switch *= test1_P.GPIO19Gain_Gain;

    /* MATLABSystem: '<Root>/PWM' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(test1_DW.obj_g.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM' */

    /* Switch: '<S1>/Switch' incorporates:
     *  Abs: '<S1>/Abs'
     *  Constant: '<S1>/Constant'
     */
    if (rtb_Sum > test1_P.Switch_Threshold) {
      rtb_Sum = test1_P.Constant_Value_d;
    } else {
      rtb_Sum = fabs(rtb_Sum);
    }

    /* End of Switch: '<S1>/Switch' */

    /* Gain: '<S1>/GPIO26 Gain' */
    rtb_Switch = test1_P.GPIO26Gain_Gain * rtb_Sum;

    /* MATLABSystem: '<Root>/PWM1' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(test1_DW.obj_e.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM1' */
    if (rtmIsMajorTimeStep(test1_M)) {
    }

    /* Gain: '<Root>/Encoder Gain2' */
    test1_B.EncoderGain2 = (int64_T)test1_P.EncoderGain2_Gain *
      test1_B.QuadEncoder2axis_o2;

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/Constant'
     *  Gain: '<Root>/Encoder Gain2'
     */
    test1_B.Sum2 = test1_P.Constant_Value - (real_T)test1_B.EncoderGain2 *
      3.637978807091713E-12;

    /* Derivative: '<S4>/Derivative' */
    if ((test1_DW.TimeStampA_l >= rtb_Sum_b) && (test1_DW.TimeStampB_j >=
         rtb_Sum_b)) {
      rtb_Switch = 0.0;
    } else {
      rtb_Switch = test1_DW.TimeStampA_l;
      lastU = &test1_DW.LastUAtTimeA_e;
      if (test1_DW.TimeStampA_l < test1_DW.TimeStampB_j) {
        if (test1_DW.TimeStampB_j < rtb_Sum_b) {
          rtb_Switch = test1_DW.TimeStampB_j;
          lastU = &test1_DW.LastUAtTimeB_m;
        }
      } else if (test1_DW.TimeStampA_l >= rtb_Sum_b) {
        rtb_Switch = test1_DW.TimeStampB_j;
        lastU = &test1_DW.LastUAtTimeB_m;
      }

      rtb_Switch = (test1_B.Sum2 - *lastU) / (rtb_Sum_b - rtb_Switch);
    }

    /* Sum: '<S4>/Sum' incorporates:
     *  Gain: '<S4>/D Gain'
     *  Gain: '<S4>/I Gain'
     *  Gain: '<S4>/P Gain'
     *  Integrator: '<S4>/Integrator'
     */
    rtb_Sum_b = (test1_P.PGain_Gain_m * test1_B.Sum2 + test1_P.IGain_Gain_k *
                 test1_X.Integrator_CSTATE_b) + test1_P.DGain_Gain_o *
      rtb_Switch;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Constant: '<S2>/Constant'
     */
    if (rtb_Sum_b > test1_P.Switch1_Threshold_c) {
      rtb_Switch = rtb_Sum_b;
    } else {
      rtb_Switch = test1_P.Constant_Value_e;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Gain: '<S2>/GPIO20 Gain' */
    rtb_Switch *= test1_P.GPIO20Gain_Gain;

    /* MATLABSystem: '<Root>/PWM2' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(test1_DW.obj_p.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM2' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Abs: '<S2>/Abs'
     *  Constant: '<S2>/Constant'
     */
    if (rtb_Sum_b > test1_P.Switch_Threshold_m) {
      rtb_Sum_b = test1_P.Constant_Value_e;
    } else {
      rtb_Sum_b = fabs(rtb_Sum_b);
    }

    /* End of Switch: '<S2>/Switch' */

    /* Gain: '<S2>/GPIO21 Gain' */
    rtb_Switch = test1_P.GPIO21Gain_Gain * rtb_Sum_b;

    /* MATLABSystem: '<Root>/PWM3' */
    if (!(rtb_Switch < 1.0)) {
      rtb_Switch = 1.0;
    }

    if (!(rtb_Switch > 0.0)) {
      rtb_Switch = 0.0;
    }

    EXT_PWMBlock_setDutyCycle(test1_DW.obj.PinNumber, rtb_Switch);

    /* End of MATLABSystem: '<Root>/PWM3' */
    if (rtmIsMajorTimeStep(test1_M)) {
    }
  }

  if (rtmIsMajorTimeStep(test1_M)) {
    real_T *lastU;

    /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Update_wrapper(&test1_B.QuadEncoder2axis_o1,
      &test1_B.QuadEncoder2axis_o2, &test1_DW.QuadEncoder2axis_DSTATE,
      &test1_P.QuadEncoder2axis_P1, 1, &test1_P.QuadEncoder2axis_P2, 1,
      &test1_P.QuadEncoder2axis_P3, 1, &test1_P.QuadEncoder2axis_P4, 1,
      &test1_P.QuadEncoder2axis_P5, 1, &test1_P.QuadEncoder2axis_P6, 1);

    /* Update for Derivative: '<S3>/Derivative' */
    if (test1_DW.TimeStampA == (rtInf)) {
      test1_DW.TimeStampA = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeA;
    } else if (test1_DW.TimeStampB == (rtInf)) {
      test1_DW.TimeStampB = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeB;
    } else if (test1_DW.TimeStampA < test1_DW.TimeStampB) {
      test1_DW.TimeStampA = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeA;
    } else {
      test1_DW.TimeStampB = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeB;
    }

    *lastU = test1_B.Sum1;

    /* End of Update for Derivative: '<S3>/Derivative' */

    /* Update for Derivative: '<S4>/Derivative' */
    if (test1_DW.TimeStampA_l == (rtInf)) {
      test1_DW.TimeStampA_l = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeA_e;
    } else if (test1_DW.TimeStampB_j == (rtInf)) {
      test1_DW.TimeStampB_j = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeB_m;
    } else if (test1_DW.TimeStampA_l < test1_DW.TimeStampB_j) {
      test1_DW.TimeStampA_l = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeA_e;
    } else {
      test1_DW.TimeStampB_j = test1_M->Timing.t[0];
      lastU = &test1_DW.LastUAtTimeB_m;
    }

    *lastU = test1_B.Sum2;

    /* End of Update for Derivative: '<S4>/Derivative' */

    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, (real_T)test1_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(test1_M)) { /* Sample time: [0.001s, 0.0s] */
      rtExtModeUpload(1, (real_T)(((test1_M->Timing.clockTick1+
        test1_M->Timing.clockTickH1* 4294967296.0)) * 0.001));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(test1_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(test1_M)!=-1) &&
          !((rtmGetTFinal(test1_M)-(((test1_M->Timing.clockTick1+
               test1_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((test1_M->Timing.clockTick1+test1_M->Timing.clockTickH1*
               4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(test1_M, "Simulation finished");
      }

      if (rtmGetStopRequested(test1_M)) {
        rtmSetErrorStatus(test1_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&test1_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++test1_M->Timing.clockTick0)) {
      ++test1_M->Timing.clockTickH0;
    }

    test1_M->Timing.t[0] = rtsiGetSolverStopTime(&test1_M->solverInfo);

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
      test1_M->Timing.clockTick1++;
      if (!test1_M->Timing.clockTick1) {
        test1_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void test1_derivatives(void)
{
  XDot_test1_T *_rtXdot;
  _rtXdot = ((XDot_test1_T *) test1_M->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = test1_B.Sum1;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_b = test1_B.Sum2;
}

/* Model initialize function */
void test1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)test1_M, 0,
                sizeof(RT_MODEL_test1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&test1_M->solverInfo, &test1_M->Timing.simTimeStep);
    rtsiSetTPtr(&test1_M->solverInfo, &rtmGetTPtr(test1_M));
    rtsiSetStepSizePtr(&test1_M->solverInfo, &test1_M->Timing.stepSize0);
    rtsiSetdXPtr(&test1_M->solverInfo, &test1_M->derivs);
    rtsiSetContStatesPtr(&test1_M->solverInfo, (real_T **) &test1_M->contStates);
    rtsiSetNumContStatesPtr(&test1_M->solverInfo, &test1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&test1_M->solverInfo,
      &test1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&test1_M->solverInfo,
      &test1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&test1_M->solverInfo,
      &test1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&test1_M->solverInfo, (&rtmGetErrorStatus(test1_M)));
    rtsiSetRTModelPtr(&test1_M->solverInfo, test1_M);
  }

  rtsiSetSimTimeStep(&test1_M->solverInfo, MAJOR_TIME_STEP);
  test1_M->intgData.y = test1_M->odeY;
  test1_M->intgData.f[0] = test1_M->odeF[0];
  test1_M->intgData.f[1] = test1_M->odeF[1];
  test1_M->intgData.f[2] = test1_M->odeF[2];
  test1_M->contStates = ((X_test1_T *) &test1_X);
  rtsiSetSolverData(&test1_M->solverInfo, (void *)&test1_M->intgData);
  rtsiSetSolverName(&test1_M->solverInfo,"ode3");
  rtmSetTPtr(test1_M, &test1_M->Timing.tArray[0]);
  rtmSetTFinal(test1_M, 25.0);
  test1_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  test1_M->Sizes.checksums[0] = (869915286U);
  test1_M->Sizes.checksums[1] = (9175271U);
  test1_M->Sizes.checksums[2] = (1567864034U);
  test1_M->Sizes.checksums[3] = (1599135151U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    test1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test1_M->extModeInfo,
      &test1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test1_M->extModeInfo, test1_M->Sizes.checksums);
    rteiSetTPtr(test1_M->extModeInfo, rtmGetTPtr(test1_M));
  }

  /* block I/O */
  (void) memset(((void *) &test1_B), 0,
                sizeof(B_test1_T));

  {
    test1_B.EncoderGain1 = (0LL);
    test1_B.EncoderGain2 = (0LL);
  }

  /* states (continuous) */
  {
    (void) memset((void *)&test1_X, 0,
                  sizeof(X_test1_T));
  }

  /* states (dwork) */
  (void) memset((void *)&test1_DW, 0,
                sizeof(DW_test1_T));

  {
    int32_T ret;
    char_T b[45];
    static const char_T tmp[45] =
      "Unable to configure pin %u for PWM output.\\n";

    /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Start_wrapper(&test1_DW.QuadEncoder2axis_DSTATE,
      &test1_P.QuadEncoder2axis_P1, 1, &test1_P.QuadEncoder2axis_P2, 1,
      &test1_P.QuadEncoder2axis_P3, 1, &test1_P.QuadEncoder2axis_P4, 1,
      &test1_P.QuadEncoder2axis_P5, 1, &test1_P.QuadEncoder2axis_P6, 1);

    /* Start for MATLABSystem: '<Root>/PWM' */
    test1_DW.obj_g.matlabCodegenIsDeleted = false;
    test1_DW.objisempty_l = true;
    test1_DW.obj_g.isInitialized = 1;
    test1_DW.obj_g.PinNumber = 19U;
    ret = EXT_PWMBlock_init(test1_DW.obj_g.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], test1_DW.obj_g.PinNumber);
    }

    test1_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */

    /* Start for MATLABSystem: '<Root>/PWM1' */
    test1_DW.obj_e.matlabCodegenIsDeleted = false;
    test1_DW.objisempty_p = true;
    test1_DW.obj_e.isInitialized = 1;
    test1_DW.obj_e.PinNumber = 26U;
    ret = EXT_PWMBlock_init(test1_DW.obj_e.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], test1_DW.obj_e.PinNumber);
    }

    test1_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM1' */
    /* Start for MATLABSystem: '<Root>/PWM2' */
    test1_DW.obj_p.matlabCodegenIsDeleted = false;
    test1_DW.objisempty_d = true;
    test1_DW.obj_p.isInitialized = 1;
    test1_DW.obj_p.PinNumber = 20U;
    ret = EXT_PWMBlock_init(test1_DW.obj_p.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], test1_DW.obj_p.PinNumber);
    }

    test1_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM2' */

    /* Start for MATLABSystem: '<Root>/PWM3' */
    test1_DW.obj.matlabCodegenIsDeleted = false;
    test1_DW.objisempty = true;
    test1_DW.obj.isInitialized = 1;
    test1_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(test1_DW.obj.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], test1_DW.obj.PinNumber);
    }

    test1_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM3' */
  }

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        test1_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  test1_X.Integrator_CSTATE = test1_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S3>/Derivative' */
  test1_DW.TimeStampA = (rtInf);
  test1_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  test1_X.Integrator_CSTATE_b = test1_P.Integrator_IC_g;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  test1_DW.TimeStampA_l = (rtInf);
  test1_DW.TimeStampB_j = (rtInf);
}

/* Model terminate function */
void test1_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper(&test1_DW.QuadEncoder2axis_DSTATE,
    &test1_P.QuadEncoder2axis_P1, 1, &test1_P.QuadEncoder2axis_P2, 1,
    &test1_P.QuadEncoder2axis_P3, 1, &test1_P.QuadEncoder2axis_P4, 1,
    &test1_P.QuadEncoder2axis_P5, 1, &test1_P.QuadEncoder2axis_P6, 1);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!test1_DW.obj_g.matlabCodegenIsDeleted) {
    test1_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((test1_DW.obj_g.isInitialized == 1) && test1_DW.obj_g.isSetupComplete) {
      EXT_PWMBlock_terminate(test1_DW.obj_g.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */

  /* Terminate for MATLABSystem: '<Root>/PWM1' */
  if (!test1_DW.obj_e.matlabCodegenIsDeleted) {
    test1_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((test1_DW.obj_e.isInitialized == 1) && test1_DW.obj_e.isSetupComplete) {
      EXT_PWMBlock_terminate(test1_DW.obj_e.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM1' */
  /* Terminate for MATLABSystem: '<Root>/PWM2' */
  if (!test1_DW.obj_p.matlabCodegenIsDeleted) {
    test1_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((test1_DW.obj_p.isInitialized == 1) && test1_DW.obj_p.isSetupComplete) {
      EXT_PWMBlock_terminate(test1_DW.obj_p.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM2' */

  /* Terminate for MATLABSystem: '<Root>/PWM3' */
  if (!test1_DW.obj.matlabCodegenIsDeleted) {
    test1_DW.obj.matlabCodegenIsDeleted = true;
    if ((test1_DW.obj.isInitialized == 1) && test1_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(test1_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM3' */
}
