/*
 * check_maximum_acc_data.c
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

/* Block parameters (default storage) */
P_check_maximum_acc_T check_maximum_acc_P = {
  /* Expression: 500
   * Referenced by: '<Root>/Constant'
   */
  500.0,

  /* Expression: 0
   * Referenced by: '<S1>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Switch1'
   */
  0.0,

  /* Expression: 1/100
   * Referenced by: '<S1>/GPIO19 Gain'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S1>/Switch'
   */
  0.0,

  /* Expression: 1/100
   * Referenced by: '<S1>/GPIO26 Gain'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch1'
   */
  0.0,

  /* Expression: 1/100
   * Referenced by: '<S2>/GPIO20 Gain'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Switch'
   */
  0.0,

  /* Expression: 1/100
   * Referenced by: '<S2>/GPIO21 Gain'
   */
  0.01,

  /* Computed Parameter: EncoderGain1_Gain
   * Referenced by: '<Root>/Encoder Gain1'
   */
  1272582903,

  /* Computed Parameter: EncoderGain2_Gain
   * Referenced by: '<Root>/Encoder Gain2'
   */
  1272582903,

  /* Expression: uint8(0)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  0U,

  /* Expression: uint8(5)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  5U,

  /* Expression: uint8(6)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  6U,

  /* Expression: uint8(1)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  1U,

  /* Expression: uint8(23)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  23U,

  /* Expression: uint8(24)
   * Referenced by: '<Root>/Quad Encoder 2axis'
   */
  24U
};
