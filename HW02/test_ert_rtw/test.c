/*
 * test.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "test".
 *
 * Model version              : 1.1
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 14:57:24 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test.h"
#include "test_private.h"

/* Block signals (default storage) */
B_test_T test_B;

/* Block states (default storage) */
DW_test_T test_DW;

/* Real-time model */
static RT_MODEL_test_T test_M_;
RT_MODEL_test_T *const test_M = &test_M_;

/* Model step function */
void test_step(void)
{
  /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
  Quad_Encoder_sfn_Outputs_wrapper(&test_B.QuadEncoder2axis_o1,
    &test_B.QuadEncoder2axis_o2, &test_DW.QuadEncoder2axis_DSTATE,
    &test_P.QuadEncoder2axis_P1, 1, &test_P.QuadEncoder2axis_P2, 1,
    &test_P.QuadEncoder2axis_P3, 1, &test_P.QuadEncoder2axis_P4, 1,
    &test_P.QuadEncoder2axis_P5, 1, &test_P.QuadEncoder2axis_P6, 1);

  /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Update_wrapper(&test_B.QuadEncoder2axis_o1,
    &test_B.QuadEncoder2axis_o2, &test_DW.QuadEncoder2axis_DSTATE,
    &test_P.QuadEncoder2axis_P1, 1, &test_P.QuadEncoder2axis_P2, 1,
    &test_P.QuadEncoder2axis_P3, 1, &test_P.QuadEncoder2axis_P4, 1,
    &test_P.QuadEncoder2axis_P5, 1, &test_P.QuadEncoder2axis_P6, 1);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, (real_T)test_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(test_M)!=-1) &&
        !((rtmGetTFinal(test_M)-test_M->Timing.taskTime0) >
          test_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(test_M, "Simulation finished");
    }

    if (rtmGetStopRequested(test_M)) {
      rtmSetErrorStatus(test_M, "Simulation finished");
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
  if (!(++test_M->Timing.clockTick0)) {
    ++test_M->Timing.clockTickH0;
  }

  test_M->Timing.taskTime0 = test_M->Timing.clockTick0 *
    test_M->Timing.stepSize0 + test_M->Timing.clockTickH0 *
    test_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void test_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)test_M, 0,
                sizeof(RT_MODEL_test_T));
  rtmSetTFinal(test_M, -1);
  test_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  test_M->Sizes.checksums[0] = (3624252459U);
  test_M->Sizes.checksums[1] = (2846792565U);
  test_M->Sizes.checksums[2] = (1139515904U);
  test_M->Sizes.checksums[3] = (2719688194U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_M->extModeInfo,
      &test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_M->extModeInfo, test_M->Sizes.checksums);
    rteiSetTPtr(test_M->extModeInfo, rtmGetTPtr(test_M));
  }

  /* block I/O */
  (void) memset(((void *) &test_B), 0,
                sizeof(B_test_T));

  /* states (dwork) */
  (void) memset((void *)&test_DW, 0,
                sizeof(DW_test_T));

  /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Start_wrapper(&test_DW.QuadEncoder2axis_DSTATE,
    &test_P.QuadEncoder2axis_P1, 1, &test_P.QuadEncoder2axis_P2, 1,
    &test_P.QuadEncoder2axis_P3, 1, &test_P.QuadEncoder2axis_P4, 1,
    &test_P.QuadEncoder2axis_P5, 1, &test_P.QuadEncoder2axis_P6, 1);

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        test_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void test_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper(&test_DW.QuadEncoder2axis_DSTATE,
    &test_P.QuadEncoder2axis_P1, 1, &test_P.QuadEncoder2axis_P2, 1,
    &test_P.QuadEncoder2axis_P3, 1, &test_P.QuadEncoder2axis_P4, 1,
    &test_P.QuadEncoder2axis_P5, 1, &test_P.QuadEncoder2axis_P6, 1);
}
