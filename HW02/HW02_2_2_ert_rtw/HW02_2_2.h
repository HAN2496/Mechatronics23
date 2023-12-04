/*
 * HW02_2_2.h
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

#ifndef RTW_HEADER_HW02_2_2_h_
#define RTW_HEADER_HW02_2_2_h_
#include <math.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef HW02_2_2_COMMON_INCLUDES_
#define HW02_2_2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_work.h"
#include "MW_pigs.h"
#endif                                 /* HW02_2_2_COMMON_INCLUDES_ */

#include "HW02_2_2_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
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
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  int64_T EncoderGain1;                /* '<Root>/Encoder Gain1' */
  int64_T EncoderGain2;                /* '<Root>/Encoder Gain2' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T FromWorkspace;                /* '<Root>/From Workspace' */
  int32_T QuadEncoder2axis_o1;         /* '<Root>/Quad Encoder 2axis' */
  int32_T QuadEncoder2axis_o2;         /* '<Root>/Quad Encoder 2axis' */
} B_HW02_2_2_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  raspi_internal_PWMBlock_HW02__T obj; /* '<Root>/PWM3' */
  raspi_internal_PWMBlock_HW02__T obj_p;/* '<Root>/PWM2' */
  raspi_internal_PWMBlock_HW02__T obj_e;/* '<Root>/PWM1' */
  raspi_internal_PWMBlock_HW02__T obj_g;/* '<Root>/PWM' */
  real_T QuadEncoder2axis_DSTATE;      /* '<Root>/Quad Encoder 2axis' */
  real_T TimeStampA;                   /* '<S3>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S3>/Derivative' */
  real_T TimeStampB;                   /* '<S3>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S3>/Derivative' */
  real_T TimeStampA_a;                 /* '<S4>/Derivative' */
  real_T LastUAtTimeA_i;               /* '<S4>/Derivative' */
  real_T TimeStampB_o;                 /* '<S4>/Derivative' */
  real_T LastUAtTimeB_m;               /* '<S4>/Derivative' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Encod;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Enc_a;   /* synthesized block */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<Root>/From Workspace' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_FromW;   /* synthesized block */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<Root>/To Workspace' */

  struct {
    int_T PrevIndex;
  } FromWorkspace_IWORK;               /* '<Root>/From Workspace' */

  boolean_T objisempty;                /* '<Root>/PWM3' */
  boolean_T objisempty_d;              /* '<Root>/PWM2' */
  boolean_T objisempty_p;              /* '<Root>/PWM1' */
  boolean_T objisempty_l;              /* '<Root>/PWM' */
} DW_HW02_2_2_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S4>/Integrator' */
} X_HW02_2_2_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S4>/Integrator' */
} XDot_HW02_2_2_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<S4>/Integrator' */
} XDis_HW02_2_2_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_HW02_2_2_T_ {
  real_T Constant_Value;               /* Expression: 10
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T PGain_Gain;                   /* Expression: 50
                                        * Referenced by: '<S3>/P Gain'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T IGain_Gain;                   /* Expression: 0
                                        * Referenced by: '<S3>/I Gain'
                                        */
  real_T DGain_Gain;                   /* Expression: 0
                                        * Referenced by: '<S3>/D Gain'
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
  real_T PGain_Gain_i;                 /* Expression: 50
                                        * Referenced by: '<S4>/P Gain'
                                        */
  real_T Integrator_IC_m;              /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T IGain_Gain_j;                 /* Expression: 0
                                        * Referenced by: '<S4>/I Gain'
                                        */
  real_T DGain_Gain_h;                 /* Expression: 0
                                        * Referenced by: '<S4>/D Gain'
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
struct tag_RTM_HW02_2_2_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_HW02_2_2_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
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
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_HW02_2_2_T HW02_2_2_P;

/* Block signals (default storage) */
extern B_HW02_2_2_T HW02_2_2_B;

/* Continuous states (default storage) */
extern X_HW02_2_2_T HW02_2_2_X;

/* Block states (default storage) */
extern DW_HW02_2_2_T HW02_2_2_DW;

/* Model entry point functions */
extern void HW02_2_2_initialize(void);
extern void HW02_2_2_step(void);
extern void HW02_2_2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_HW02_2_2_T *const HW02_2_2_M;

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
 * '<Root>' : 'HW02_2_2'
 * '<S1>'   : 'HW02_2_2/Motor Subsystem'
 * '<S2>'   : 'HW02_2_2/Motor Subsystem1'
 * '<S3>'   : 'HW02_2_2/PID Subsystem'
 * '<S4>'   : 'HW02_2_2/PID Subsystem1'
 */
#endif                                 /* RTW_HEADER_HW02_2_2_h_ */
