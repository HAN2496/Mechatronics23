/*
 * final23_vcontrol_1_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "final23_vcontrol_1".
 *
 * Model version              : 1.20
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 21:20:35 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_final23_vcontrol_1_types_h_
#define RTW_HEADER_final23_vcontrol_1_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Model Code Variants */
#ifndef struct_tag_rsJ0GE01HUvEHoEeL7l3HC
#define struct_tag_rsJ0GE01HUvEHoEeL7l3HC

struct tag_rsJ0GE01HUvEHoEeL7l3HC
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pCumSum;
  real_T pCumSumRev[19];
  real_T pCumRevIndex;
};

#endif                                 /* struct_tag_rsJ0GE01HUvEHoEeL7l3HC */

#ifndef typedef_g_dsp_private_SlidingWindowAv_T
#define typedef_g_dsp_private_SlidingWindowAv_T

typedef struct tag_rsJ0GE01HUvEHoEeL7l3HC g_dsp_private_SlidingWindowAv_T;

#endif                             /* typedef_g_dsp_private_SlidingWindowAv_T */

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_final23_vcontrol_1_T
#define typedef_cell_wrap_final23_vcontrol_1_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_final23_vcontrol_1_T;

#endif                              /* typedef_cell_wrap_final23_vcontrol_1_T */

#ifndef struct_tag_Q9Q7bpC5hgdHXLdOOoEToG
#define struct_tag_Q9Q7bpC5hgdHXLdOOoEToG

struct tag_Q9Q7bpC5hgdHXLdOOoEToG
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_final23_vcontrol_1_T inputVarSize;
  g_dsp_private_SlidingWindowAv_T *pStatistic;
  int32_T NumChannels;
  g_dsp_private_SlidingWindowAv_T _pobj0;
};

#endif                                 /* struct_tag_Q9Q7bpC5hgdHXLdOOoEToG */

#ifndef typedef_dsp_simulink_MovingAverage_fi_T
#define typedef_dsp_simulink_MovingAverage_fi_T

typedef struct tag_Q9Q7bpC5hgdHXLdOOoEToG dsp_simulink_MovingAverage_fi_T;

#endif                             /* typedef_dsp_simulink_MovingAverage_fi_T */

#ifndef struct_tag_wGQ65XWdfcDT2LQLRRxyjE
#define struct_tag_wGQ65XWdfcDT2LQLRRxyjE

struct tag_wGQ65XWdfcDT2LQLRRxyjE
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  uint32_T PinNumber;
};

#endif                                 /* struct_tag_wGQ65XWdfcDT2LQLRRxyjE */

#ifndef typedef_raspi_internal_PWMBlock_final_T
#define typedef_raspi_internal_PWMBlock_final_T

typedef struct tag_wGQ65XWdfcDT2LQLRRxyjE raspi_internal_PWMBlock_final_T;

#endif                             /* typedef_raspi_internal_PWMBlock_final_T */

/* Parameters (default storage) */
typedef struct P_final23_vcontrol_1_T_ P_final23_vcontrol_1_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_final23_vcontrol_1_T RT_MODEL_final23_vcontrol_1_T;

#endif                              /* RTW_HEADER_final23_vcontrol_1_types_h_ */
