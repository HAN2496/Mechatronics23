/*
 * test1_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "test1".
 *
 * Model version              : 1.17
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Dec  4 22:13:02 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_test1_types_h_
#define RTW_HEADER_test1_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Model Code Variants */
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

#ifndef typedef_raspi_internal_PWMBlock_test1_T
#define typedef_raspi_internal_PWMBlock_test1_T

typedef struct tag_wGQ65XWdfcDT2LQLRRxyjE raspi_internal_PWMBlock_test1_T;

#endif                             /* typedef_raspi_internal_PWMBlock_test1_T */

/* Parameters (default storage) */
typedef struct P_test1_T_ P_test1_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_test1_T RT_MODEL_test1_T;

#endif                                 /* RTW_HEADER_test1_types_h_ */
