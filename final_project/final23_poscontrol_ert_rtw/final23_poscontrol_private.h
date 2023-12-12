/*
 * final23_poscontrol_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_poscontrol".
 *
 * Model version              : 1.38
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Tue Dec 12 15:49:32 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_final23_poscontrol_private_h_
#define RTW_HEADER_final23_poscontrol_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Used by FromWorkspace Block: '<Root>/From Workspace' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
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

/* private model entry point functions */
extern void final23_poscontrol_derivatives(void);

#endif                            /* RTW_HEADER_final23_poscontrol_private_h_ */
