/*
 * pi_led_test.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "pi_led_test".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Nov  9 16:16:13 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pi_led_test.h"
#include "pi_led_test_private.h"

/* Block signals (default storage) */
B_pi_led_test_T pi_led_test_B;

/* Block states (default storage) */
DW_pi_led_test_T pi_led_test_DW;

/* Real-time model */
static RT_MODEL_pi_led_test_T pi_led_test_M_;
RT_MODEL_pi_led_test_T *const pi_led_test_M = &pi_led_test_M_;
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void pi_led_test_step(void)
{
  real_T rtb_PulseGenerator;
  int32_T i;
  char_T d[5];
  uint8_T tmp;
  static const char_T tmp_0[69] = { 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ', 'L',
    'E', 'D', ' ', 'v', 'a', 'l', 'u', 'e', '.', ' ', 'L', 'E', 'D', ' ', 'v',
    'a', 'l', 'u', 'e', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 'a', ' ',
    'l', 'o', 'g', 'i', 'c', 'a', 'l', ' ', 'v', 'a', 'l', 'u', 'e', ' ', '(',
    't', 'r', 'u', 'e', ' ', 'o', 'r', ' ', 'f', 'a', 'l', 's', 'e', ')', '.' };

  static const char_T tmp_1[5] = "none";

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (pi_led_test_DW.clockTickCounter <
                        pi_led_test_P.PulseGenerator_Duty) &&
    (pi_led_test_DW.clockTickCounter >= 0) ? pi_led_test_P.PulseGenerator_Amp :
    0.0;
  if (pi_led_test_DW.clockTickCounter >= pi_led_test_P.PulseGenerator_Period -
      1.0) {
    pi_led_test_DW.clockTickCounter = 0;
  } else {
    pi_led_test_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* MATLABSystem: '<Root>/LED' */
  if ((rtb_PulseGenerator == 0.0) || (rtb_PulseGenerator == 1.0)) {
  } else {
    memcpy(&pi_led_test_B.c[0], &tmp_0[0], 69U * sizeof(char_T));
    perror(&pi_led_test_B.c[0]);
  }

  for (i = 0; i < 5; i++) {
    d[i] = tmp_1[i];
  }

  EXT_LED_setTrigger(0U, &d[0]);
  rtb_PulseGenerator = rt_roundd_snf(rtb_PulseGenerator);
  if (rtb_PulseGenerator < 256.0) {
    if (rtb_PulseGenerator >= 0.0) {
      tmp = (uint8_T)rtb_PulseGenerator;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  EXT_LED_write(0U, tmp);

  /* End of MATLABSystem: '<Root>/LED' */
}

/* Model initialize function */
void pi_led_test_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(pi_led_test_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&pi_led_test_DW, 0,
                sizeof(DW_pi_led_test_T));

  {
    int32_T i;
    char_T b[5];
    static const char_T tmp[5] = "none";

    /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
    pi_led_test_DW.clockTickCounter = 0;

    /* Start for MATLABSystem: '<Root>/LED' */
    pi_led_test_DW.obj.matlabCodegenIsDeleted = false;
    pi_led_test_DW.objisempty = true;
    pi_led_test_DW.obj.isInitialized = 1;
    for (i = 0; i < 5; i++) {
      b[i] = tmp[i];
    }

    EXT_LED_setTrigger(0U, &b[0]);
    pi_led_test_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/LED' */
  }
}

/* Model terminate function */
void pi_led_test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/LED' */
  if (!pi_led_test_DW.obj.matlabCodegenIsDeleted) {
    pi_led_test_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/LED' */
}
