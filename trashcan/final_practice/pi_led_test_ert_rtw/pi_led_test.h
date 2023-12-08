/*
 * pi_led_test.h
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

#ifndef RTW_HEADER_pi_led_test_h_
#define RTW_HEADER_pi_led_test_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef pi_led_test_COMMON_INCLUDES_
#define pi_led_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "LED.h"
#endif                                 /* pi_led_test_COMMON_INCLUDES_ */

#include "pi_led_test_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  char_T c[69];
} B_pi_led_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_raspi_internal_LE_T obj; /* '<Root>/LED' */
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
  boolean_T objisempty;                /* '<Root>/LED' */
} DW_pi_led_test_T;

/* Parameters (default storage) */
struct P_pi_led_test_T_ {
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;     /* Computed Parameter: PulseGenerator_Period
                                     * Referenced by: '<Root>/Pulse Generator'
                                     */
  real_T PulseGenerator_Duty;         /* Computed Parameter: PulseGenerator_Duty
                                       * Referenced by: '<Root>/Pulse Generator'
                                       */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_pi_led_test_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_pi_led_test_T pi_led_test_P;

/* Block signals (default storage) */
extern B_pi_led_test_T pi_led_test_B;

/* Block states (default storage) */
extern DW_pi_led_test_T pi_led_test_DW;

/* Model entry point functions */
extern void pi_led_test_initialize(void);
extern void pi_led_test_step(void);
extern void pi_led_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pi_led_test_T *const pi_led_test_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pi_led_test'
 */
#endif                                 /* RTW_HEADER_pi_led_test_h_ */
