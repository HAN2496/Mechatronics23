/*
 * test_private.h
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

#ifndef RTW_HEADER_test_private_h_
#define RTW_HEADER_test_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Quad_Encoder_sfn_Start_wrapper(real_T *xD,
    const uint8_T *enc1, const int_T p_width0,
    const uint8_T *pinA, const int_T p_width1,
    const uint8_T *pinB, const int_T p_width2,
    const uint8_T *enc2, const int_T p_width3,
    const uint8_T *pinA2, const int_T p_width4,
    const uint8_T *pinB2, const int_T p_width5);
  extern void Quad_Encoder_sfn_Outputs_wrapper(int32_T *enc_pos1,
    int32_T *enc_pos2,
    const real_T *xD,
    const uint8_T *enc1, const int_T p_width0,
    const uint8_T *pinA, const int_T p_width1,
    const uint8_T *pinB, const int_T p_width2,
    const uint8_T *enc2, const int_T p_width3,
    const uint8_T *pinA2, const int_T p_width4,
    const uint8_T *pinB2, const int_T p_width5);
  extern void Quad_Encoder_sfn_Update_wrapper(int32_T *enc_pos1,
    int32_T *enc_pos2,
    real_T *xD,
    const uint8_T *enc1, const int_T p_width0,
    const uint8_T *pinA, const int_T p_width1,
    const uint8_T *pinB, const int_T p_width2,
    const uint8_T *enc2, const int_T p_width3,
    const uint8_T *pinA2, const int_T p_width4,
    const uint8_T *pinB2, const int_T p_width5);
  extern void Quad_Encoder_sfn_Terminate_wrapper(real_T *xD,
    const uint8_T *enc1, const int_T p_width0,
    const uint8_T *pinA, const int_T p_width1,
    const uint8_T *pinB, const int_T p_width2,
    const uint8_T *enc2, const int_T p_width3,
    const uint8_T *pinA2, const int_T p_width4,
    const uint8_T *pinB2, const int_T p_width5);

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_test_private_h_ */
