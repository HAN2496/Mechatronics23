/*
 * problem1_2s_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "problem1_2s".
 *
 * Model version              : 1.45
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec 11 18:39:46 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "problem1_2s.h"
#include "problem1_2s_private.h"

/* Block parameters (default storage) */
P_problem1_2s_T problem1_2s_P = {
  /* Expression: 64
   * Referenced by: '<Root>/Constant'
   */
  64.0,

  /* Expression: 2
   * Referenced by: '<Root>/Constant2'
   */
  2.0,

  /* Expression: 500
   * Referenced by: '<S3>/P Gain'
   */
  500.0,

  /* Expression: 0
   * Referenced by: '<S3>/Integrator'
   */
  0.0,

  /* Expression: 0.2
   * Referenced by: '<S3>/I Gain'
   */
  0.2,

  /* Expression: 20
   * Referenced by: '<S3>/D Gain'
   */
  20.0,

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

  /* Expression: 48
   * Referenced by: '<Root>/Constant1'
   */
  48.0,

  /* Expression: 500
   * Referenced by: '<S4>/P Gain'
   */
  500.0,

  /* Expression: 0
   * Referenced by: '<S4>/Integrator'
   */
  0.0,

  /* Expression: 0.2
   * Referenced by: '<S4>/I Gain'
   */
  0.2,

  /* Expression: 20
   * Referenced by: '<S4>/D Gain'
   */
  20.0,

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
  1174691910,

  /* Computed Parameter: EncoderGain2_Gain
   * Referenced by: '<Root>/Encoder Gain2'
   */
  1215198528,

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
