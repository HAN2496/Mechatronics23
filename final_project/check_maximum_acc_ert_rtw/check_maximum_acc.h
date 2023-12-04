/*
 * check_maximum_acc.h
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

#ifndef RTW_HEADER_check_maximum_acc_h_
#define RTW_HEADER_check_maximum_acc_h_
#include <math.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef check_maximum_acc_COMMON_INCLUDES_
#define check_maximum_acc_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_work.h"
#include "MW_pigs.h"
#endif                                 /* check_maximum_acc_COMMON_INCLUDES_ */

#include "check_maximum_acc_types.h"

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
  int64_T EncoderGain1;                /* '<Root>/Encoder Gain1' */
  int64_T EncoderGain2;                /* '<Root>/Encoder Gain2' */
  int32_T QuadEncoder2axis_o1;         /* '<Root>/Quad Encoder 2axis' */
  int32_T QuadEncoder2axis_o2;         /* '<Root>/Quad Encoder 2axis' */
} B_check_maximum_acc_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  raspi_internal_PWMBlock_check_T obj; /* '<Root>/PWM3' */
  raspi_internal_PWMBlock_check_T obj_p;/* '<Root>/PWM2' */
  raspi_internal_PWMBlock_check_T obj_e;/* '<Root>/PWM1' */
  raspi_internal_PWMBlock_check_T obj_g;/* '<Root>/PWM' */
  real_T QuadEncoder2axis_DSTATE;      /* '<Root>/Quad Encoder 2axis' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Encod;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Enc_a;   /* synthesized block */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<Root>/To Workspace' */

  boolean_T objisempty;                /* '<Root>/PWM3' */
  boolean_T objisempty_d;              /* '<Root>/PWM2' */
  boolean_T objisempty_p;              /* '<Root>/PWM1' */
  boolean_T objisempty_l;              /* '<Root>/PWM' */
} DW_check_maximum_acc_T;

/* Parameters (default storage) */
struct P_check_maximum_acc_T_ {
  real_T Constant_Value;               /* Expression: 500
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant_Value_d;             /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S1>/Switch1'
                                        */
  real_T GPIO19Gain_Gain;              /* Expression: 1/100
                                        * Referenced by: '<S1>/GPIO19 Gain'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S1>/Switch'
                                        */
  real_T GPIO26Gain_Gain;              /* Expression: 1/100
                                        * Referenced by: '<S1>/GPIO26 Gain'
                                        */
  real_T Constant_Value_e;             /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Switch1_Threshold_c;          /* Expression: 0
                                        * Referenced by: '<S2>/Switch1'
                                        */
  real_T GPIO20Gain_Gain;              /* Expression: 1/100
                                        * Referenced by: '<S2>/GPIO20 Gain'
                                        */
  real_T Switch_Threshold_m;           /* Expression: 0
                                        * Referenced by: '<S2>/Switch'
                                        */
  real_T GPIO21Gain_Gain;              /* Expression: 1/100
                                        * Referenced by: '<S2>/GPIO21 Gain'
                                        */
  int32_T EncoderGain1_Gain;           /* Computed Parameter: EncoderGain1_Gain
                                        * Referenced by: '<Root>/Encoder Gain1'
                                        */
  int32_T EncoderGain2_Gain;           /* Computed Parameter: EncoderGain2_Gain
                                        * Referenced by: '<Root>/Encoder Gain2'
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
struct tag_RTM_check_maximum_acc_T {
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
extern P_check_maximum_acc_T check_maximum_acc_P;

/* Block signals (default storage) */
extern B_check_maximum_acc_T check_maximum_acc_B;

/* Block states (default storage) */
extern DW_check_maximum_acc_T check_maximum_acc_DW;

/* Model entry point functions */
extern void check_maximum_acc_initialize(void);
extern void check_maximum_acc_step(void);
extern void check_maximum_acc_terminate(void);

/* Real-time Model object */
extern RT_MODEL_check_maximum_acc_T *const check_maximum_acc_M;

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
 * '<Root>' : 'check_maximum_acc'
 * '<S1>'   : 'check_maximum_acc/Motor Subsystem'
 * '<S2>'   : 'check_maximum_acc/Motor Subsystem1'
 */
#endif                                 /* RTW_HEADER_check_maximum_acc_h_ */
