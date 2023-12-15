/*
 * test2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "test2".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 22:03:55 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test2.h"
#include "test2_private.h"

/* Block signals (default storage) */
B_test2_T test2_B;

/* Block states (default storage) */
DW_test2_T test2_DW;

/* Real-time model */
static RT_MODEL_test2_T test2_M_;
RT_MODEL_test2_T *const test2_M = &test2_M_;

/* Model step function */
void test2_step(void)
{
  /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
  Quad_Encoder_sfn_Outputs_wrapper(&test2_B.QuadEncoder2axis_o1,
    &test2_B.QuadEncoder2axis_o2, &test2_DW.QuadEncoder2axis_DSTATE,
    &test2_P.QuadEncoder2axis_P1, 1, &test2_P.QuadEncoder2axis_P2, 1,
    &test2_P.QuadEncoder2axis_P3, 1, &test2_P.QuadEncoder2axis_P4, 1,
    &test2_P.QuadEncoder2axis_P5, 1, &test2_P.QuadEncoder2axis_P6, 1);

  /* Gain: '<Root>/Encoder Gain1' */
  test2_B.EncoderGain1 = (int64_T)test2_P.EncoderGain1_Gain *
    test2_B.QuadEncoder2axis_o1;

  /* Gain: '<Root>/Encoder Gain2' */
  test2_B.EncoderGain2 = (int64_T)test2_P.EncoderGain2_Gain *
    test2_B.QuadEncoder2axis_o2;

  /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Update_wrapper(&test2_B.QuadEncoder2axis_o1,
    &test2_B.QuadEncoder2axis_o2, &test2_DW.QuadEncoder2axis_DSTATE,
    &test2_P.QuadEncoder2axis_P1, 1, &test2_P.QuadEncoder2axis_P2, 1,
    &test2_P.QuadEncoder2axis_P3, 1, &test2_P.QuadEncoder2axis_P4, 1,
    &test2_P.QuadEncoder2axis_P5, 1, &test2_P.QuadEncoder2axis_P6, 1);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.2s, 0.0s] */
    rtExtModeUpload(0, (real_T)test2_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(test2_M)!=-1) &&
        !((rtmGetTFinal(test2_M)-test2_M->Timing.taskTime0) >
          test2_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(test2_M, "Simulation finished");
    }

    if (rtmGetStopRequested(test2_M)) {
      rtmSetErrorStatus(test2_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++test2_M->Timing.clockTick0)) {
    ++test2_M->Timing.clockTickH0;
  }

  test2_M->Timing.taskTime0 = test2_M->Timing.clockTick0 *
    test2_M->Timing.stepSize0 + test2_M->Timing.clockTickH0 *
    test2_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void test2_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)test2_M, 0,
                sizeof(RT_MODEL_test2_T));
  rtmSetTFinal(test2_M, -1);
  test2_M->Timing.stepSize0 = 0.2;

  /* External mode info */
  test2_M->Sizes.checksums[0] = (2600811023U);
  test2_M->Sizes.checksums[1] = (2711967023U);
  test2_M->Sizes.checksums[2] = (291707564U);
  test2_M->Sizes.checksums[3] = (3571977616U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    test2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test2_M->extModeInfo,
      &test2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test2_M->extModeInfo, test2_M->Sizes.checksums);
    rteiSetTPtr(test2_M->extModeInfo, rtmGetTPtr(test2_M));
  }

  /* block I/O */
  (void) memset(((void *) &test2_B), 0,
                sizeof(B_test2_T));

  {
    test2_B.EncoderGain1 = (0LL);
    test2_B.EncoderGain2 = (0LL);
  }

  /* states (dwork) */
  (void) memset((void *)&test2_DW, 0,
                sizeof(DW_test2_T));

  /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Start_wrapper(&test2_DW.QuadEncoder2axis_DSTATE,
    &test2_P.QuadEncoder2axis_P1, 1, &test2_P.QuadEncoder2axis_P2, 1,
    &test2_P.QuadEncoder2axis_P3, 1, &test2_P.QuadEncoder2axis_P4, 1,
    &test2_P.QuadEncoder2axis_P5, 1, &test2_P.QuadEncoder2axis_P6, 1);

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        test2_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void test2_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper(&test2_DW.QuadEncoder2axis_DSTATE,
    &test2_P.QuadEncoder2axis_P1, 1, &test2_P.QuadEncoder2axis_P2, 1,
    &test2_P.QuadEncoder2axis_P3, 1, &test2_P.QuadEncoder2axis_P4, 1,
    &test2_P.QuadEncoder2axis_P5, 1, &test2_P.QuadEncoder2axis_P6, 1);
}
