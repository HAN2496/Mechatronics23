/*
 * HW02_2_2_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "HW02_2_2".
 *
 * Model version              : 1.15
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 16:59:44 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "HW02_2_2.h"
#include "HW02_2_2_private.h"

/* Block parameters (default storage) */
P_HW02_2_2_T HW02_2_2_P = {
  /* Expression: 10
   * Referenced by: '<Root>/Constant'
   */
  10.0,

  /* Expression: 50
   * Referenced by: '<S3>/P Gain'
   */
  50.0,

  /* Expression: 0
   * Referenced by: '<S3>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/I Gain'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/D Gain'
   */
  0.0,

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

  /* Expression: 50
   * Referenced by: '<S4>/P Gain'
   */
  50.0,

  /* Expression: 0
   * Referenced by: '<S4>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/I Gain'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/D Gain'
   */
  0.0,

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
