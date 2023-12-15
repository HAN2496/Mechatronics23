/*
 * check_maximum_acc.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "check_maximum_acc".
 *
 * Model version              : 1.18
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 18:04:43 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "check_maximum_acc.h"
#include "check_maximum_acc_private.h"

/* Block signals (default storage) */
B_check_maximum_acc_T check_maximum_acc_B;

/* Block states (default storage) */
DW_check_maximum_acc_T check_maximum_acc_DW;

/* Real-time model */
static RT_MODEL_check_maximum_acc_T check_maximum_acc_M_;
RT_MODEL_check_maximum_acc_T *const check_maximum_acc_M = &check_maximum_acc_M_;

/* Model step function */
void check_maximum_acc_step(void)
{
  real_T u0;

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S1>/Constant'
   */
  if (check_maximum_acc_P.Constant_Value > check_maximum_acc_P.Switch1_Threshold)
  {
    u0 = check_maximum_acc_P.Constant_Value;
  } else {
    u0 = check_maximum_acc_P.Constant_Value_d;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Gain: '<S1>/GPIO19 Gain' */
  u0 *= check_maximum_acc_P.GPIO19Gain_Gain;

  /* MATLABSystem: '<Root>/PWM' */
  if (!(u0 < 1.0)) {
    u0 = 1.0;
  }

  if (!(u0 > 0.0)) {
    u0 = 0.0;
  }

  EXT_PWMBlock_setDutyCycle(check_maximum_acc_DW.obj_g.PinNumber, u0);

  /* End of MATLABSystem: '<Root>/PWM' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Abs: '<S1>/Abs'
   *  Constant: '<Root>/Constant'
   *  Constant: '<S1>/Constant'
   */
  if (check_maximum_acc_P.Constant_Value > check_maximum_acc_P.Switch_Threshold)
  {
    u0 = check_maximum_acc_P.Constant_Value_d;
  } else {
    u0 = fabs(check_maximum_acc_P.Constant_Value);
  }

  /* End of Switch: '<S1>/Switch' */

  /* Gain: '<S1>/GPIO26 Gain' */
  u0 *= check_maximum_acc_P.GPIO26Gain_Gain;

  /* MATLABSystem: '<Root>/PWM1' */
  if (!(u0 < 1.0)) {
    u0 = 1.0;
  }

  if (!(u0 > 0.0)) {
    u0 = 0.0;
  }

  EXT_PWMBlock_setDutyCycle(check_maximum_acc_DW.obj_e.PinNumber, u0);

  /* End of MATLABSystem: '<Root>/PWM1' */

  /* Switch: '<S2>/Switch1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S2>/Constant'
   */
  if (check_maximum_acc_P.Constant_Value >
      check_maximum_acc_P.Switch1_Threshold_c) {
    u0 = check_maximum_acc_P.Constant_Value;
  } else {
    u0 = check_maximum_acc_P.Constant_Value_e;
  }

  /* End of Switch: '<S2>/Switch1' */

  /* Gain: '<S2>/GPIO20 Gain' */
  u0 *= check_maximum_acc_P.GPIO20Gain_Gain;

  /* MATLABSystem: '<Root>/PWM2' */
  if (!(u0 < 1.0)) {
    u0 = 1.0;
  }

  if (!(u0 > 0.0)) {
    u0 = 0.0;
  }

  EXT_PWMBlock_setDutyCycle(check_maximum_acc_DW.obj_p.PinNumber, u0);

  /* End of MATLABSystem: '<Root>/PWM2' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<Root>/Constant'
   *  Constant: '<S2>/Constant'
   */
  if (check_maximum_acc_P.Constant_Value >
      check_maximum_acc_P.Switch_Threshold_m) {
    u0 = check_maximum_acc_P.Constant_Value_e;
  } else {
    u0 = fabs(check_maximum_acc_P.Constant_Value);
  }

  /* End of Switch: '<S2>/Switch' */

  /* Gain: '<S2>/GPIO21 Gain' */
  u0 *= check_maximum_acc_P.GPIO21Gain_Gain;

  /* MATLABSystem: '<Root>/PWM3' */
  if (!(u0 < 1.0)) {
    u0 = 1.0;
  }

  if (!(u0 > 0.0)) {
    u0 = 0.0;
  }

  EXT_PWMBlock_setDutyCycle(check_maximum_acc_DW.obj.PinNumber, u0);

  /* End of MATLABSystem: '<Root>/PWM3' */

  /* S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */
  Quad_Encoder_sfn_Outputs_wrapper(&check_maximum_acc_B.QuadEncoder2axis_o1,
    &check_maximum_acc_B.QuadEncoder2axis_o2,
    &check_maximum_acc_DW.QuadEncoder2axis_DSTATE,
    &check_maximum_acc_P.QuadEncoder2axis_P1, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P2, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P3, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P4, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P5, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P6, 1);

  /* Gain: '<Root>/Encoder Gain1' */
  check_maximum_acc_B.EncoderGain1 = (int64_T)
    check_maximum_acc_P.EncoderGain1_Gain *
    check_maximum_acc_B.QuadEncoder2axis_o1;

  /* Gain: '<Root>/Encoder Gain2' */
  check_maximum_acc_B.EncoderGain2 = (int64_T)
    check_maximum_acc_P.EncoderGain2_Gain *
    check_maximum_acc_B.QuadEncoder2axis_o2;

  /* Update for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function "Quad_Encoder_sfn_wrapper" Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Update_wrapper(&check_maximum_acc_B.QuadEncoder2axis_o1,
    &check_maximum_acc_B.QuadEncoder2axis_o2,
    &check_maximum_acc_DW.QuadEncoder2axis_DSTATE,
    &check_maximum_acc_P.QuadEncoder2axis_P1, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P2, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P3, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P4, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P5, 1,
    &check_maximum_acc_P.QuadEncoder2axis_P6, 1);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, (real_T)check_maximum_acc_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(check_maximum_acc_M)!=-1) &&
        !((rtmGetTFinal(check_maximum_acc_M)-
           check_maximum_acc_M->Timing.taskTime0) >
          check_maximum_acc_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(check_maximum_acc_M, "Simulation finished");
    }

    if (rtmGetStopRequested(check_maximum_acc_M)) {
      rtmSetErrorStatus(check_maximum_acc_M, "Simulation finished");
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
  if (!(++check_maximum_acc_M->Timing.clockTick0)) {
    ++check_maximum_acc_M->Timing.clockTickH0;
  }

  check_maximum_acc_M->Timing.taskTime0 = check_maximum_acc_M->Timing.clockTick0
    * check_maximum_acc_M->Timing.stepSize0 +
    check_maximum_acc_M->Timing.clockTickH0 *
    check_maximum_acc_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void check_maximum_acc_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)check_maximum_acc_M, 0,
                sizeof(RT_MODEL_check_maximum_acc_T));
  rtmSetTFinal(check_maximum_acc_M, -1);
  check_maximum_acc_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  check_maximum_acc_M->Sizes.checksums[0] = (141858439U);
  check_maximum_acc_M->Sizes.checksums[1] = (3147752787U);
  check_maximum_acc_M->Sizes.checksums[2] = (3185815561U);
  check_maximum_acc_M->Sizes.checksums[3] = (1087732351U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    check_maximum_acc_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(check_maximum_acc_M->extModeInfo,
      &check_maximum_acc_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(check_maximum_acc_M->extModeInfo,
                        check_maximum_acc_M->Sizes.checksums);
    rteiSetTPtr(check_maximum_acc_M->extModeInfo, rtmGetTPtr(check_maximum_acc_M));
  }

  /* block I/O */
  (void) memset(((void *) &check_maximum_acc_B), 0,
                sizeof(B_check_maximum_acc_T));

  {
    check_maximum_acc_B.EncoderGain1 = (0LL);
    check_maximum_acc_B.EncoderGain2 = (0LL);
  }

  /* states (dwork) */
  (void) memset((void *)&check_maximum_acc_DW, 0,
                sizeof(DW_check_maximum_acc_T));

  {
    int32_T ret;
    char_T b[45];
    static const char_T tmp[45] =
      "Unable to configure pin %u for PWM output.\\n";

    /* Start for MATLABSystem: '<Root>/PWM' */
    check_maximum_acc_DW.obj_g.matlabCodegenIsDeleted = false;
    check_maximum_acc_DW.objisempty_l = true;
    check_maximum_acc_DW.obj_g.isInitialized = 1;
    check_maximum_acc_DW.obj_g.PinNumber = 19U;
    ret = EXT_PWMBlock_init(check_maximum_acc_DW.obj_g.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], check_maximum_acc_DW.obj_g.PinNumber);
    }

    check_maximum_acc_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */

    /* Start for MATLABSystem: '<Root>/PWM1' */
    check_maximum_acc_DW.obj_e.matlabCodegenIsDeleted = false;
    check_maximum_acc_DW.objisempty_p = true;
    check_maximum_acc_DW.obj_e.isInitialized = 1;
    check_maximum_acc_DW.obj_e.PinNumber = 26U;
    ret = EXT_PWMBlock_init(check_maximum_acc_DW.obj_e.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], check_maximum_acc_DW.obj_e.PinNumber);
    }

    check_maximum_acc_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM1' */

    /* Start for MATLABSystem: '<Root>/PWM2' */
    check_maximum_acc_DW.obj_p.matlabCodegenIsDeleted = false;
    check_maximum_acc_DW.objisempty_d = true;
    check_maximum_acc_DW.obj_p.isInitialized = 1;
    check_maximum_acc_DW.obj_p.PinNumber = 20U;
    ret = EXT_PWMBlock_init(check_maximum_acc_DW.obj_p.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], check_maximum_acc_DW.obj_p.PinNumber);
    }

    check_maximum_acc_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM2' */

    /* Start for MATLABSystem: '<Root>/PWM3' */
    check_maximum_acc_DW.obj.matlabCodegenIsDeleted = false;
    check_maximum_acc_DW.objisempty = true;
    check_maximum_acc_DW.obj.isInitialized = 1;
    check_maximum_acc_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(check_maximum_acc_DW.obj.PinNumber, 1000U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b[ret] = tmp[ret];
      }

      printf(&b[0], check_maximum_acc_DW.obj.PinNumber);
    }

    check_maximum_acc_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM3' */

    /* Start for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

    /* S-Function Block: <Root>/Quad Encoder 2axis */
    Quad_Encoder_sfn_Start_wrapper(&check_maximum_acc_DW.QuadEncoder2axis_DSTATE,
      &check_maximum_acc_P.QuadEncoder2axis_P1, 1,
      &check_maximum_acc_P.QuadEncoder2axis_P2, 1,
      &check_maximum_acc_P.QuadEncoder2axis_P3, 1,
      &check_maximum_acc_P.QuadEncoder2axis_P4, 1,
      &check_maximum_acc_P.QuadEncoder2axis_P5, 1,
      &check_maximum_acc_P.QuadEncoder2axis_P6, 1);
  }

  /* InitializeConditions for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        check_maximum_acc_DW.QuadEncoder2axis_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void check_maximum_acc_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!check_maximum_acc_DW.obj_g.matlabCodegenIsDeleted) {
    check_maximum_acc_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((check_maximum_acc_DW.obj_g.isInitialized == 1) &&
        check_maximum_acc_DW.obj_g.isSetupComplete) {
      EXT_PWMBlock_terminate(check_maximum_acc_DW.obj_g.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */

  /* Terminate for MATLABSystem: '<Root>/PWM1' */
  if (!check_maximum_acc_DW.obj_e.matlabCodegenIsDeleted) {
    check_maximum_acc_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((check_maximum_acc_DW.obj_e.isInitialized == 1) &&
        check_maximum_acc_DW.obj_e.isSetupComplete) {
      EXT_PWMBlock_terminate(check_maximum_acc_DW.obj_e.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM1' */

  /* Terminate for MATLABSystem: '<Root>/PWM2' */
  if (!check_maximum_acc_DW.obj_p.matlabCodegenIsDeleted) {
    check_maximum_acc_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((check_maximum_acc_DW.obj_p.isInitialized == 1) &&
        check_maximum_acc_DW.obj_p.isSetupComplete) {
      EXT_PWMBlock_terminate(check_maximum_acc_DW.obj_p.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM2' */

  /* Terminate for MATLABSystem: '<Root>/PWM3' */
  if (!check_maximum_acc_DW.obj.matlabCodegenIsDeleted) {
    check_maximum_acc_DW.obj.matlabCodegenIsDeleted = true;
    if ((check_maximum_acc_DW.obj.isInitialized == 1) &&
        check_maximum_acc_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(check_maximum_acc_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM3' */

  /* Terminate for S-Function (Quad_Encoder_sfn): '<Root>/Quad Encoder 2axis' */

  /* S-Function Block: <Root>/Quad Encoder 2axis */
  Quad_Encoder_sfn_Terminate_wrapper
    (&check_maximum_acc_DW.QuadEncoder2axis_DSTATE,
     &check_maximum_acc_P.QuadEncoder2axis_P1, 1,
     &check_maximum_acc_P.QuadEncoder2axis_P2, 1,
     &check_maximum_acc_P.QuadEncoder2axis_P3, 1,
     &check_maximum_acc_P.QuadEncoder2axis_P4, 1,
     &check_maximum_acc_P.QuadEncoder2axis_P5, 1,
     &check_maximum_acc_P.QuadEncoder2axis_P6, 1);
}
