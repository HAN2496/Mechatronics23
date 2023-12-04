/*
 * HW02_1.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "HW02_1".
 *
 * Model version              : 1.3
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 14:08:31 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_HW02_1_h_
#define RTW_HEADER_HW02_1_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef HW02_1_COMMON_INCLUDES_
#define HW02_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_work.h"
#include "MW_raspiextint.h"
#endif                                 /* HW02_1_COMMON_INCLUDES_ */

#include "HW02_1_types.h"

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
  int64_T RateTransition;              /* '<Root>/Rate Transition' */
  int64_T RateTransition1;             /* '<Root>/Rate Transition1' */
  int64_T Sum;                         /* '<S1>/Sum' */
  int32_T QuadEncoder2axis_o1;         /* '<Root>/Quad Encoder 2axis' */
  int32_T QuadEncoder2axis_o2;         /* '<Root>/Quad Encoder 2axis' */
} B_HW02_1_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T QuadEncoder2axis_DSTATE;      /* '<Root>/Quad Encoder 2axis' */
  volatile int64_T RateTransition1_Buffer0;/* '<Root>/Rate Transition1' */
  volatile int64_T RateTransition1_Buffer1;/* '<Root>/Rate Transition1' */
  volatile int64_T RateTransition_Buffer0;/* '<Root>/Rate Transition' */
  volatile int64_T RateTransition_Buffer1;/* '<Root>/Rate Transition' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_RateT;   /* synthesized block */

  volatile int8_T RateTransition1_write_buf;/* '<Root>/Rate Transition1' */
  volatile int8_T RateTransition1_read_buf;/* '<Root>/Rate Transition1' */
  volatile int8_T RateTransition1_last_buf_wr;/* '<Root>/Rate Transition1' */
  volatile int8_T RateTransition_write_buf;/* '<Root>/Rate Transition' */
  volatile int8_T RateTransition_read_buf;/* '<Root>/Rate Transition' */
  volatile int8_T RateTransition_last_buf_wr;/* '<Root>/Rate Transition' */
  int8_T FunctionCallSubsystem_SubsysRan;/* '<Root>/Function-Call Subsystem' */
} DW_HW02_1_T;

/* Parameters (default storage) */
struct P_HW02_1_T_ {
  int64_T Out1_Y0;                     /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S1>/Out1'
                                        */
  int64_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S1>/Unit Delay'
                                */
  int64_T RateTransition1_InitialConditio;
                          /* Computed Parameter: RateTransition1_InitialConditio
                           * Referenced by: '<Root>/Rate Transition1'
                           */
  int64_T RateTransition_InitialCondition;
                          /* Computed Parameter: RateTransition_InitialCondition
                           * Referenced by: '<Root>/Rate Transition'
                           */
  int32_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<Root>/Gain'
                                        */
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
struct tag_RTM_HW02_1_T {
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
    uint32_T clockTick1;
    uint32_T clockTickH1;
    uint8_T rtmDbBufReadBuf1;
    uint8_T rtmDbBufWriteBuf1;
    boolean_T rtmDbBufLastBufWr1;
    uint32_T rtmDbBufClockTick1[2];
    uint32_T rtmDbBufClockTickH1[2];
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_HW02_1_T HW02_1_P;

/* Block signals (default storage) */
extern B_HW02_1_T HW02_1_B;

/* Block states (default storage) */
extern DW_HW02_1_T HW02_1_DW;

/* Model entry point functions */
extern void HW02_1_initialize(void);
extern void HW02_1_step(void);
extern void HW02_1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_HW02_1_T *const HW02_1_M;

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
 * '<Root>' : 'HW02_1'
 * '<S1>'   : 'HW02_1/Function-Call Subsystem'
 */
#endif                                 /* RTW_HEADER_HW02_1_h_ */
