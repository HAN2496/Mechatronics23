/*
 * HW02_1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "HW02_1".
 *
 * Model version              : 1.3
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 14:08:31 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "HW02_1.h"
#include "HW02_1_private.h"

/* Block signals (default storage) */
B_HW02_1_T HW02_1_B;

/* Block states (default storage) */
DW_HW02_1_T HW02_1_DW;

/* Real-time model */
static RT_MODEL_HW02_1_T HW02_1_M_;
RT_MODEL_HW02_1_T *const HW02_1_M = &HW02_1_M_;

/* Callback for Hardware Interrupt Block: '<Root>/External Interrupt' */
void MW_ISR_4(void)
{
  /* Call the system: <Root>/Function-Call Subsystem */
  {
    /* Reset subsysRan breadcrumbs */
    srClearBC(HW02_1_DW.FunctionCallSubsystem_SubsysRan);

    /* RateTransition: '<Root>/Rate Transition1' */
    switch (HW02_1_DW.RateTransition1_write_buf) {
     case 0:
      HW02_1_DW.RateTransition1_read_buf = 1;
      break;

     case 1:
      HW02_1_DW.RateTransition1_read_buf = 0;
      break;

     default:
      HW02_1_DW.RateTransition1_read_buf = HW02_1_DW.RateTransition1_last_buf_wr;
      break;
    }

    if (HW02_1_DW.RateTransition1_read_buf != 0) {
      HW02_1_B.RateTransition1 = HW02_1_DW.RateTransition1_Buffer1;
    } else {
      HW02_1_B.RateTransition1 = HW02_1_DW.RateTransition1_Buffer0;
    }

    HW02_1_DW.RateTransition1_read_buf = -1;

    /* End of RateTransition: '<Root>/Rate Transition1' */

    /* S-Function (raspiextint_sfcn): '<Root>/External Interrupt' */

    /* Output and update for function-call system: '<Root>/Function-Call Subsystem' */

    /* Asynchronous task (with no priority assigned)
     * reads absolute time */
    switch (HW02_1_M->Timing.rtmDbBufWriteBuf1) {
     case 0:
      HW02_1_M->Timing.rtmDbBufReadBuf1 = 1;
      break;

     case 1:
      HW02_1_M->Timing.rtmDbBufReadBuf1 = 0;
      break;

     default:
      HW02_1_M->Timing.rtmDbBufReadBuf1 = HW02_1_M->Timing.rtmDbBufLastBufWr1;
      break;
    }

    HW02_1_M->Timing.clockTick1 = HW02_1_M->Timing.rtmDbBufClockTick1
      [HW02_1_M->Timing.rtmDbBufReadBuf1];
    HW02_1_M->Timing.clockTickH1 = HW02_1_M->Timing.rtmDbBufClockTickH1
      [HW02_1_M->Timing.rtmDbBufReadBuf1];
    HW02_1_M->Timing.rtmDbBufReadBuf1 = 0xFF;

    /* Sum: '<S1>/Sum' incorporates:
     *  RateTransition: '<Root>/Rate Transition1'
     *  UnitDelay: '<S1>/Unit Delay'
     */
    HW02_1_B.Sum += HW02_1_B.RateTransition1;
    HW02_1_DW.FunctionCallSubsystem_SubsysRan = 4;

    /* End of Outputs for S-Function (raspiextint_sfcn): '<Root>/External Interrupt' */

    /* RateTransition: '<Root>/Rate Transition' incorporates:
     *  Sum: '<S1>/Sum'
     */
    switch (HW02_1_DW.RateTransition_read_buf) {
     case 0:
      HW02_1_DW.RateTransition_write_buf = 1;
      break;

     case 1:
      HW02_1_DW.RateTransition_write_buf = 0;
      break;

     default:
      HW02_1_DW.RateTransition_write_buf = (int8_T)
        (HW02_1_DW.RateTransition_last_buf_wr == 0);
      break;
    }

    if (HW02_1_DW.RateTransition_write_buf != 0) {
      HW02_1_DW.RateTransition_Buffer1 = HW02_1_B.Sum;
    } else {
      HW02_1_DW.RateTransition_Buffer0 = HW02_1_B.Sum;
    }

    HW02_1_DW.RateTransition_last_buf_wr = HW02_1_DW.RateTransition_write_buf;
    HW02_1_DW.RateTransition_write_buf = -1;

    /* End of RateTransition: '<Root>/Rate Transition' */
  }
}

/* Model step function */
void HW02_1_step(void)
{
  int64_T rtb_Gain;

  /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
  Quad_Encoder_sfn_Outputs_wrapper(&HW02_1_B.QuadEncoder2axis_o1,
    &HW02_1_B.QuadEncoder2axis_o2, &HW02_1_DW.QuadEncoder2axis_DSTATE,
    &HW02_1_P.QuadEncoder2axis_P1, 1, &HW02_1_P.QuadEncoder2axis_P2, 1,
    &HW02_1_P.QuadEncoder2axis_P3, 1, &HW02_1_P.QuadEncoder2axis_P4, 1,
    &HW02_1_P.QuadEncoder2axis_P5, 1, &HW02_1_P.QuadEncoder2axis_P6, 1);

  /* Gain: '<Root>/Gain' */
  rtb_Gain = (int64_T)HW02_1_P.Gain_Gain * HW02_1_B.QuadEncoder2axis_o1;

  /* RateTransition: '<Root>/Rate Transition1' incorporates:
   *  Gain: '<Root>/Gain'
   */
  switch (HW02_1_DW.RateTransition1_read_buf) {
   case 0:
    HW02_1_DW.RateTransition1_write_buf = 1;
    break;

   case 1:
    HW02_1_DW.RateTransition1_write_buf = 0;
    break;

   default:
    HW02_1_DW.RateTransition1_write_buf = (int8_T)
      (HW02_1_DW.RateTransition1_last_buf_wr == 0);
    break;
  }

  if (HW02_1_DW.RateTransition1_write_buf != 0) {
    HW02_1_DW.RateTransition1_Buffer1 = rtb_Gain;
  } else {
    HW02_1_DW.RateTransition1_Buffer0 = rtb_Gain;
  }

  HW02_1_DW.RateTransition1_last_buf_wr = HW02_1_DW.RateTransition1_write_buf;
  HW02_1_DW.RateTransition1_write_buf = -1;

  /* End of RateTransition: '<Root>/Rate Transition1' */

  /* RateTransition: '<Root>/Rate Transition' */
  switch (HW02_1_DW.RateTransition_write_buf) {
   case 0:
    HW02_1_DW.RateTransition_read_buf = 1;
    break;

   case 1:
    HW02_1_DW.RateTransition_read_buf = 0;
    break;

   default:
    HW02_1_DW.RateTransition_read_buf = HW02_1_DW.RateTransition_last_buf_wr;
    break;
  }

  if (HW02_1_DW.RateTransition_read_buf != 0) {
    /* RateTransition: '<Root>/Rate Transition' */
    HW02_1_B.RateTransition = HW02_1_DW.RateTransition_Buffer1;
  } else {
    /* RateTransition: '<Root>/Rate Transition' */
    HW02_1_B.RateTransition = HW02_1_DW.RateTransition_Buffer0;
  }

  HW02_1_DW.RateTransition_read_buf = -1;

  /* End of RateTransition: '<Root>/Rate Transition' */
  /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Update_wrapper(&HW02_1_B.QuadEncoder2axis_o1,
    &HW02_1_B.QuadEncoder2axis_o2, &HW02_1_DW.QuadEncoder2axis_DSTATE,
    &HW02_1_P.QuadEncoder2axis_P1, 1, &HW02_1_P.QuadEncoder2axis_P2, 1,
    &HW02_1_P.QuadEncoder2axis_P3, 1, &HW02_1_P.QuadEncoder2axis_P4, 1,
    &HW02_1_P.QuadEncoder2axis_P5, 1, &HW02_1_P.QuadEncoder2axis_P6, 1);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, (real_T)HW02_1_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(HW02_1_M)!=-1) &&
        !((rtmGetTFinal(HW02_1_M)-HW02_1_M->Timing.taskTime0) >
          HW02_1_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(HW02_1_M, "Simulation finished");
    }

    if (rtmGetStopRequested(HW02_1_M)) {
      rtmSetErrorStatus(HW02_1_M, "Simulation finished");
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
  if (!(++HW02_1_M->Timing.clockTick0)) {
    ++HW02_1_M->Timing.clockTickH0;
  }

  HW02_1_M->Timing.taskTime0 = HW02_1_M->Timing.clockTick0 *
    HW02_1_M->Timing.stepSize0 + HW02_1_M->Timing.clockTickH0 *
    HW02_1_M->Timing.stepSize0 * 4294967296.0;
  switch (HW02_1_M->Timing.rtmDbBufReadBuf1) {
   case 0:
    HW02_1_M->Timing.rtmDbBufWriteBuf1 = 1;
    break;

   case 1:
    HW02_1_M->Timing.rtmDbBufWriteBuf1 = 0;
    break;

   default:
    HW02_1_M->Timing.rtmDbBufWriteBuf1 = !HW02_1_M->Timing.rtmDbBufLastBufWr1;
    break;
  }

  HW02_1_M->Timing.rtmDbBufClockTick1[HW02_1_M->Timing.rtmDbBufWriteBuf1] =
    HW02_1_M->Timing.clockTick0;
  HW02_1_M->Timing.rtmDbBufClockTickH1[HW02_1_M->Timing.rtmDbBufWriteBuf1] =
    HW02_1_M->Timing.clockTickH0;
  HW02_1_M->Timing.rtmDbBufLastBufWr1 = HW02_1_M->Timing.rtmDbBufWriteBuf1;
  HW02_1_M->Timing.rtmDbBufWriteBuf1 = 0xFF;
}

/* Model initialize function */
void HW02_1_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)HW02_1_M, 0,
                sizeof(RT_MODEL_HW02_1_T));
  rtmSetTFinal(HW02_1_M, -1);
  HW02_1_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  HW02_1_M->Sizes.checksums[0] = (1048974977U);
  HW02_1_M->Sizes.checksums[1] = (1427217874U);
  HW02_1_M->Sizes.checksums[2] = (2262141880U);
  HW02_1_M->Sizes.checksums[3] = (2567518460U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    HW02_1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&HW02_1_DW.FunctionCallSubsystem_SubsysRan;
    rteiSetModelMappingInfoPtr(HW02_1_M->extModeInfo,
      &HW02_1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(HW02_1_M->extModeInfo, HW02_1_M->Sizes.checksums);
    rteiSetTPtr(HW02_1_M->extModeInfo, rtmGetTPtr(HW02_1_M));
  }

  /* block I/O */
  (void) memset(((void *) &HW02_1_B), 0,
                sizeof(B_HW02_1_T));

  {
    HW02_1_B.RateTransition = (0LL);
    HW02_1_B.RateTransition1 = (0LL);
    HW02_1_B.Sum = (0LL);
  }

  /* states (dwork) */
  (void) memset((void *)&HW02_1_DW, 0,
                sizeof(DW_HW02_1_T));

  /* Start for S-Function (raspiextint_sfcn): '<Root>/External Interrupt' */

  /* Attach callback function */
  /* Changes made wrt g2141701, this change was needed to make the
   * architecture simpler for adding new boards.
   */
  int retStatusInt_4;
  const int cMode_4[] = {
    RISING_EDGE,
    FALLING_EDGE,
    EITHER_EDGE };

  retStatusInt_4 = gpioSetMode(4U, PI_INPUT);
  if (retStatusInt_4 != 0) {
    fprintf(stderr,"ERR_EXTINT_PIGPIOMODE\n");
    exit(-1);
  } else {
    retStatusInt_4 = gpioSetPullUpDown(4U, PI_PUD_DOWN);
    if (retStatusInt_4 != 0) {
      fprintf(stderr,"ERR_EXTINT_PIGPIOPUD\n");
      exit(-1);
    } else {
      retStatusInt_4 = gpioSetISRFunc(4U, cMode_4[1-1], 0, (gpioISRFunc_t)
        MW_ISR_4);
      if (retStatusInt_4 != 0) {
        fprintf(stderr,"ERR_EXTINT_PIGPIOISR\n");
        exit(-1);
      }
    }
  }

  /* End of Start for S-Function (raspiextint_sfcn): '<Root>/External Interrupt' */

  /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Start_wrapper(&HW02_1_DW.QuadEncoder2axis_DSTATE,
    &HW02_1_P.QuadEncoder2axis_P1, 1, &HW02_1_P.QuadEncoder2axis_P2, 1,
    &HW02_1_P.QuadEncoder2axis_P3, 1, &HW02_1_P.QuadEncoder2axis_P4, 1,
    &HW02_1_P.QuadEncoder2axis_P5, 1, &HW02_1_P.QuadEncoder2axis_P6, 1);
  HW02_1_M->Timing.rtmDbBufReadBuf1 = 0xFF;
  HW02_1_M->Timing.rtmDbBufWriteBuf1 = 0xFF;
  HW02_1_M->Timing.rtmDbBufLastBufWr1 = 0;

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        HW02_1_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition1' */
  HW02_1_DW.RateTransition1_Buffer0 = HW02_1_P.RateTransition1_InitialConditio;
  HW02_1_DW.RateTransition1_write_buf = -1;
  HW02_1_DW.RateTransition1_read_buf = -1;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition' */
  HW02_1_DW.RateTransition_Buffer0 = HW02_1_P.RateTransition_InitialCondition;
  HW02_1_DW.RateTransition_write_buf = -1;
  HW02_1_DW.RateTransition_read_buf = -1;

  /* SystemInitialize for S-Function (raspiextint_sfcn): '<Root>/External Interrupt' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem'
   */

  /* System initialize for function-call system: '<Root>/Function-Call Subsystem' */

  /* Asynchronous task (with no priority assigned)
   * reads absolute time */
  switch (HW02_1_M->Timing.rtmDbBufWriteBuf1) {
   case 0:
    HW02_1_M->Timing.rtmDbBufReadBuf1 = 1;
    break;

   case 1:
    HW02_1_M->Timing.rtmDbBufReadBuf1 = 0;
    break;

   default:
    HW02_1_M->Timing.rtmDbBufReadBuf1 = HW02_1_M->Timing.rtmDbBufLastBufWr1;
    break;
  }

  HW02_1_M->Timing.clockTick1 = HW02_1_M->Timing.rtmDbBufClockTick1
    [HW02_1_M->Timing.rtmDbBufReadBuf1];
  HW02_1_M->Timing.clockTickH1 = HW02_1_M->Timing.rtmDbBufClockTickH1
    [HW02_1_M->Timing.rtmDbBufReadBuf1];
  HW02_1_M->Timing.rtmDbBufReadBuf1 = 0xFF;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  HW02_1_B.Sum = HW02_1_P.UnitDelay_InitialCondition;

  /* SystemInitialize for Sum: '<S1>/Sum' incorporates:
   *  Outport: '<S1>/Out1'
   */
  HW02_1_B.Sum = HW02_1_P.Out1_Y0;

  /* End of SystemInitialize for S-Function (raspiextint_sfcn): '<Root>/External Interrupt' */
}

/* Model terminate function */
void HW02_1_terminate(void)
{
  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper(&HW02_1_DW.QuadEncoder2axis_DSTATE,
    &HW02_1_P.QuadEncoder2axis_P1, 1, &HW02_1_P.QuadEncoder2axis_P2, 1,
    &HW02_1_P.QuadEncoder2axis_P3, 1, &HW02_1_P.QuadEncoder2axis_P4, 1,
    &HW02_1_P.QuadEncoder2axis_P5, 1, &HW02_1_P.QuadEncoder2axis_P6, 1);
}
