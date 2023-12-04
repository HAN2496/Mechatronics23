/*
 * test.h
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

#ifndef RTW_HEADER_test_h_
#define RTW_HEADER_test_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef test_COMMON_INCLUDES_
#define test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_work.h"
#endif                                 /* test_COMMON_INCLUDES_ */

#include "test_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  int32_T QuadEncoder2axis_o1;         /* '<Root>/Quad Encoder 2axis' */
  int32_T QuadEncoder2axis_o2;         /* '<Root>/Quad Encoder 2axis' */
} B_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T QuadEncoder2axis_DSTATE;      /* '<Root>/Quad Encoder 2axis' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_QuadE;   /* synthesized block */
} DW_test_T;

/* Parameters (default storage) */
struct P_test_T_ {
  uint8_T QuadEncoder2axis_P1;         /* Expression: uint8(0)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
  uint8_T QuadEncoder2axis_P2;         /* Expression: uint8(5)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
  uint8_T QuadEncoder2axis_P3;         /* Expression: uint8(6)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
  uint8_T QuadEncoder2axis_P4;         /* Expression: uint8(1)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
  uint8_T QuadEncoder2axis_P5;         /* Expression: uint8(23)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
  uint8_T QuadEncoder2axis_P6;         /* Expression: uint8(24)
                                        * Referenced by: '<Root>/Quad Encoder 2axis'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_test_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_test_T test_P;

/* Block signals (default storage) */
extern B_test_T test_B;

/* Block states (default storage) */
extern DW_test_T test_DW;

/* Model entry point functions */
extern void test_initialize(void);
extern void test_step(void);
extern void test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_test_T *const test_M;

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
 * '<Root>' : 'test'
 */
#endif                                 /* RTW_HEADER_test_h_ */
