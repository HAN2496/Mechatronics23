/*
 * final23_vcontrol_1_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_vcontrol_1".
 *
 * Model version              : 1.27
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Tue Dec  5 16:21:34 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "final23_vcontrol_1.h"
#include "final23_vcontrol_1_private.h"

/* Block parameters (default storage) */
P_final23_vcontrol_1_T final23_vcontrol_1_P = {
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

  /* Expression: 10
   * Referenced by: '<S3>/D Gain'
   */
  10.0,

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

  /* Expression: 10
   * Referenced by: '<S4>/D Gain'
   */
  10.0,

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

  /* Computed Parameter: Delay_InitialCondition
   * Referenced by: '<S5>/Delay'
   */
  (0LL),

  /* Computed Parameter: Delay_InitialCondition_o
   * Referenced by: '<S6>/Delay'
   */
  (0LL),

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S5>/Gain'
   */
  (9007199254740992000LL),

  /* Computed Parameter: Gain_Gain_a
   * Referenced by: '<S6>/Gain'
   */
  (9007199254740992000LL),

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
