/*
 * final23_vcontrol.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_vcontrol".
 *
 * Model version              : 1.17
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 17:46:37 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_final23_vcontrol_h_
#define RTW_HEADER_final23_vcontrol_h_
#include <math.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef final23_vcontrol_COMMON_INCLUDES_
#define final23_vcontrol_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_work.h"
#include "MW_pigs.h"
#endif                                 /* final23_vcontrol_COMMON_INCLUDES_ */

#include "final23_vcontrol_types.h"

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

/* Block signals for system '<S3>/Moving Average' */
typedef struct {
  real_T csumrev[19];
  real_T MovingAverage;                /* '<S3>/Moving Average' */
} B_MovingAverage_final23_vcont_T;

/* Block states (default storage) for system '<S3>/Moving Average' */
typedef struct {
  dsp_simulink_MovingAverage_fi_T obj; /* '<S3>/Moving Average' */
  boolean_T objisempty;                /* '<S3>/Moving Average' */
} DW_MovingAverage_final23_vcon_T;

/* Block signals (default storage) */
typedef struct {
  char_T b[45];
  int128m_T r;
  int128m_T r1;
  real_T Switch;                       /* '<S2>/Switch' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T Sum_d;                        /* '<S6>/Sum' */
  int64_T EncoderGain1;                /* '<S3>/Encoder Gain1' */
  int64_T Delay;                       /* '<S3>/Delay' */
  int64_T EncoderGain2;                /* '<S4>/Encoder Gain2' */
  int64_T Delay1;                      /* '<S4>/Delay1' */
  real_T FromWorkspace;                /* '<Root>/From Workspace' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  uint64_T u;
  uint64_T u1;
  int32_T QuadEncoder2axis_o1;         /* '<Root>/Quad Encoder 2axis' */
  int32_T QuadEncoder2axis_o2;         /* '<Root>/Quad Encoder 2axis' */
  B_MovingAverage_final23_vcont_T MovingAverage1;/* '<S3>/Moving Average' */
  B_MovingAverage_final23_vcont_T MovingAverage;/* '<S3>/Moving Average' */
} B_final23_vcontrol_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  raspi_internal_PWMBlock_final_T obj; /* '<Root>/PWM3' */
  raspi_internal_PWMBlock_final_T obj_p;/* '<Root>/PWM2' */
  raspi_internal_PWMBlock_final_T obj_e;/* '<Root>/PWM1' */
  raspi_internal_PWMBlock_final_T obj_g;/* '<Root>/PWM' */
  real_T QuadEncoder2axis_DSTATE;      /* '<Root>/Quad Encoder 2axis' */
  int64_T Delay_DSTATE;                /* '<S3>/Delay' */
  int64_T Delay1_DSTATE;               /* '<S4>/Delay1' */
  real_T TimeStampA;                   /* '<S5>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S5>/Derivative' */
  real_T TimeStampB;                   /* '<S5>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S5>/Derivative' */
  real_T TimeStampA_a;                 /* '<S6>/Derivative' */
  real_T LastUAtTimeA_i;               /* '<S6>/Derivative' */
  real_T TimeStampB_o;                 /* '<S6>/Derivative' */
  real_T LastUAtTimeB_m;               /* '<S6>/Derivative' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<Root>/From Workspace' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_FromW;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Motor;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Encod;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Mot_e;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Enc_a;   /* synthesized block */

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
  DW_MovingAverage_final23_vcon_T MovingAverage1;/* '<S3>/Moving Average' */
  DW_MovingAverage_final23_vcon_T MovingAverage;/* '<S3>/Moving Average' */
} DW_final23_vcontrol_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S6>/Integrator' */
} X_final23_vcontrol_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S6>/Integrator' */
} XDot_final23_vcontrol_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S5>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<S6>/Integrator' */
} XDis_final23_vcontrol_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_final23_vcontrol_T_ {
  real_T PGain_Gain;                   /* Expression: 50
                                        * Referenced by: '<S5>/P Gain'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  real_T IGain_Gain;                   /* Expression: 0
                                        * Referenced by: '<S5>/I Gain'
                                        */
  real_T DGain_Gain;                   /* Expression: 0
                                        * Referenced by: '<S5>/D Gain'
                                        */
  real_T Constant_Value;               /* Expression: 0
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
                                        * Referenced by: '<S6>/P Gain'
                                        */
  real_T Integrator_IC_m;              /* Expression: 0
                                        * Referenced by: '<S6>/Integrator'
                                        */
  real_T IGain_Gain_j;                 /* Expression: 0
                                        * Referenced by: '<S6>/I Gain'
                                        */
  real_T DGain_Gain_h;                 /* Expression: 0
                                        * Referenced by: '<S6>/D Gain'
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
  int64_T Delay_InitialCondition;  /* Computed Parameter: Delay_InitialCondition
                                    * Referenced by: '<S3>/Delay'
                                    */
  int64_T Delay1_InitialCondition;/* Computed Parameter: Delay1_InitialCondition
                                   * Referenced by: '<S4>/Delay1'
                                   */
  int64_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S3>/Gain'
                                        */
  int64_T Gain1_Gain;                  /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S4>/Gain1'
                                        */
  int32_T EncoderGain1_Gain;           /* Computed Parameter: EncoderGain1_Gain
                                        * Referenced by: '<S3>/Encoder Gain1'
                                        */
  int32_T EncoderGain2_Gain;           /* Computed Parameter: EncoderGain2_Gain
                                        * Referenced by: '<S4>/Encoder Gain2'
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
struct tag_RTM_final23_vcontrol_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_final23_vcontrol_T *contStates;
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
extern P_final23_vcontrol_T final23_vcontrol_P;

/* Block signals (default storage) */
extern B_final23_vcontrol_T final23_vcontrol_B;

/* Continuous states (default storage) */
extern X_final23_vcontrol_T final23_vcontrol_X;

/* Block states (default storage) */
extern DW_final23_vcontrol_T final23_vcontrol_DW;

/* Model entry point functions */
extern void final23_vcontrol_initialize(void);
extern void final23_vcontrol_step(void);
extern void final23_vcontrol_terminate(void);

/* Real-time Model object */
extern RT_MODEL_final23_vcontrol_T *const final23_vcontrol_M;

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
 * '<Root>' : 'final23_vcontrol'
 * '<S1>'   : 'final23_vcontrol/Motor Subsystem'
 * '<S2>'   : 'final23_vcontrol/Motor Subsystem1'
 * '<S3>'   : 'final23_vcontrol/Motor Vel 1'
 * '<S4>'   : 'final23_vcontrol/Motor Vel 2'
 * '<S5>'   : 'final23_vcontrol/PID Subsystem'
 * '<S6>'   : 'final23_vcontrol/PID Subsystem1'
 */
#endif                                 /* RTW_HEADER_final23_vcontrol_h_ */
