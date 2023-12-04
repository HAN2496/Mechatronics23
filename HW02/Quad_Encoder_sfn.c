/*
 * File: Quad_Encoder_sfn.c
 *
 *
 *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
 *
 *   This file is an S-function produced by the S-Function
 *   Builder which only recognizes certain fields.  Changes made
 *   outside these fields will be lost the next time the block is
 *   used to load, edit, and resave this file. This file will be overwritten
 *   by the S-function Builder block. If you want to edit this file by hand, 
 *   you must change it only in the area defined as:  
 *
 *        %%%-SFUNWIZ_defines_Changes_BEGIN
 *        #define NAME 'replacement text' 
 *        %%% SFUNWIZ_defines_Changes_END
 *
 *   DO NOT change NAME--Change the 'replacement text' only.
 *
 *   For better compatibility with the Simulink Coder, the
 *   "wrapper" S-function technique is used.  This is discussed
 *   in the Simulink Coder's Manual in the Chapter titled,
 *   "Wrapper S-functions".
 *
 *  -------------------------------------------------------------------------
 * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  ------------------------------------------------------------------------- 
 *
 * Created: Mon Dec 04 15:54:06 2023
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME Quad_Encoder_sfn
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS            0

#define NUM_OUTPUTS           2
/* Output Port  0 */
#define OUT_PORT_0_NAME       enc_pos1
#define OUTPUT_0_WIDTH        1
#define OUTPUT_DIMS_0_COL     1
#define OUTPUT_0_DTYPE        int32_T
#define OUTPUT_0_COMPLEX      COMPLEX_NO
#define OUT_0_FRAME_BASED     FRAME_NO
#define OUT_0_BUS_BASED       0
#define OUT_0_BUS_NAME        
#define OUT_0_DIMS            1-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125
/* Output Port  1 */
#define OUT_PORT_1_NAME       enc_pos2
#define OUTPUT_1_WIDTH        1
#define OUTPUT_DIMS_1_COL     1
#define OUTPUT_1_DTYPE        int32_T
#define OUTPUT_1_COMPLEX      COMPLEX_NO
#define OUT_1_FRAME_BASED     FRAME_NO
#define OUT_1_BUS_BASED       0
#define OUT_1_BUS_NAME        
#define OUT_1_DIMS            1-D
#define OUT_1_ISSIGNED        1
#define OUT_1_WORDLENGTH      8
#define OUT_1_FIXPOINTSCALING 1
#define OUT_1_FRACTIONLENGTH  3
#define OUT_1_BIAS            0
#define OUT_1_SLOPE           0.125

#define NPARAMS               6
/* Parameter 0 */
#define PARAMETER_0_NAME      enc1
#define PARAMETER_0_DTYPE     uint8_T
#define PARAMETER_0_COMPLEX   COMPLEX_NO
/* Parameter 1 */
#define PARAMETER_1_NAME      pinA
#define PARAMETER_1_DTYPE     uint8_T
#define PARAMETER_1_COMPLEX   COMPLEX_NO
/* Parameter 2 */
#define PARAMETER_2_NAME      pinB
#define PARAMETER_2_DTYPE     uint8_T
#define PARAMETER_2_COMPLEX   COMPLEX_NO
/* Parameter 3 */
#define PARAMETER_3_NAME      enc2
#define PARAMETER_3_DTYPE     uint8_T
#define PARAMETER_3_COMPLEX   COMPLEX_NO
/* Parameter 4 */
#define PARAMETER_4_NAME      pinA2
#define PARAMETER_4_DTYPE     uint8_T
#define PARAMETER_4_COMPLEX   COMPLEX_NO
/* Parameter 5 */
#define PARAMETER_5_NAME      pinB2
#define PARAMETER_5_DTYPE     uint8_T
#define PARAMETER_5_COMPLEX   COMPLEX_NO

#define SAMPLE_TIME_0         INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES       1
#define DISC_STATES_IC        [0]
#define NUM_CONT_STATES       0
#define CONT_STATES_IC        [0]

#define SFUNWIZ_GENERATE_TLC  1
#define SOURCEFILES           "__SFB__"
#define PANELINDEX            N/A
#define USE_SIMSTRUCT         0
#define SHOW_COMPILE_STEPS    0
#define CREATE_DEBUG_MEXFILE  0
#define SAVE_CODE_ONLY        1
#define SFUNWIZ_REVISION      3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"

#define PARAM_DEF0(S) ssGetSFcnParam(S, 0)
#define PARAM_DEF1(S) ssGetSFcnParam(S, 1)
#define PARAM_DEF2(S) ssGetSFcnParam(S, 2)
#define PARAM_DEF3(S) ssGetSFcnParam(S, 3)
#define PARAM_DEF4(S) ssGetSFcnParam(S, 4)
#define PARAM_DEF5(S) ssGetSFcnParam(S, 5)

#define IS_PARAM_UINT8(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsUint8(pVal))

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
/*====================*
 * S-function methods *
 *====================*/
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlCheckParameters =============================================
 * Abstract:
 *     Verify parameter definitions and types.
 */
static void mdlCheckParameters(SimStruct *S)
{
    int paramIndex  = 0;
    bool invalidParam = false;
    /* All parameters must match the S-function Builder Dialog */

    {
        const mxArray *pVal0 = ssGetSFcnParam(S, 0);
        if (!IS_PARAM_UINT8(pVal0)) {
            invalidParam = true;
            paramIndex = 0;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal1 = ssGetSFcnParam(S, 1);
        if (!IS_PARAM_UINT8(pVal1)) {
            invalidParam = true;
            paramIndex = 1;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal2 = ssGetSFcnParam(S, 2);
        if (!IS_PARAM_UINT8(pVal2)) {
            invalidParam = true;
            paramIndex = 2;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal3 = ssGetSFcnParam(S, 3);
        if (!IS_PARAM_UINT8(pVal3)) {
            invalidParam = true;
            paramIndex = 3;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal4 = ssGetSFcnParam(S, 4);
        if (!IS_PARAM_UINT8(pVal4)) {
            invalidParam = true;
            paramIndex = 4;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal5 = ssGetSFcnParam(S, 5);
        if (!IS_PARAM_UINT8(pVal5)) {
            invalidParam = true;
            paramIndex = 5;
            goto EXIT_POINT;
        }
    }


    EXIT_POINT:
    if (invalidParam) {
        static char parameterErrorMsg[1024];
        sprintf(parameterErrorMsg, "The data type and or complexity of parameter %d does not match the "
                "information specified in the S-function Builder dialog. "
                "For non-double parameters you will need to cast them using int8, int16, "
                "int32, uint8, uint16, uint32 or boolean.", paramIndex + 1);
        ssSetErrorStatus(S, parameterErrorMsg);
    }
    return;
}
#endif /* MDL_CHECK_PARAMETERS */
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS); /* Number of expected parameters */
    #if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) {
            return;
        }
    } else {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    #endif

    ssSetArrayLayoutForCodeGen(S, SS_COLUMN_MAJOR);

    ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);


    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;

    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    /* Output Port 0 */
    ssSetOutputPortWidth(S, 0, OUTPUT_0_WIDTH);
    ssSetOutputPortDataType(S, 0, SS_INT32);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    /* Output Port 1 */
    ssSetOutputPortWidth(S, 1, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 1, SS_INT32);
    ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);
    ssSetNumPWork(S, 0);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetSimulinkVersionGeneratedIn(S, "10.3");

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR |
                     SS_OPTION_WORKS_WITH_CODE_REUSE));
}

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
    ssSetOffsetTime(S, 0, 0.0);
}
#define MDL_INITIALIZE_CONDITIONS
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    Initialize the states
 */
static void mdlInitializeConditions(SimStruct *S)
{
    real_T *xD = ssGetRealDiscStates(S);

    /* Warning: parameters not of type double used as IC will be replaced with 0.0 */

    xD[0] = 0;
}

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)

static void mdlSetWorkWidths(SimStruct *S)
{

    const char_T *rtParamNames[] = {"P1","P2","P3","P4","P5","P6"};
    ssRegAllTunableParamsAsRunTimeParams(S, rtParamNames);

}

#endif

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S)
{
    real_T *xD = ssGetDiscStates(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int_T   p_width4  = mxGetNumberOfElements(PARAM_DEF4(S));
    const int_T   p_width5  = mxGetNumberOfElements(PARAM_DEF5(S));
    const uint8_T *enc1 = (const uint8_T *) mxGetData(PARAM_DEF0(S));
    const uint8_T *pinA = (const uint8_T *) mxGetData(PARAM_DEF1(S));
    const uint8_T *pinB = (const uint8_T *) mxGetData(PARAM_DEF2(S));
    const uint8_T *enc2 = (const uint8_T *) mxGetData(PARAM_DEF3(S));
    const uint8_T *pinA2 = (const uint8_T *) mxGetData(PARAM_DEF4(S));
    const uint8_T *pinB2 = (const uint8_T *) mxGetData(PARAM_DEF5(S));
    
    Quad_Encoder_sfn_Start_wrapper(xD, enc1, p_width0, pinA, p_width1, pinB, p_width2, enc2, p_width3, pinA2, p_width4, pinB2, p_width5);
}
#endif /*  MDL_START */

/* Function: mdlOutputs =======================================================
 *
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    int32_T *enc_pos1 = (int32_T *) ssGetOutputPortRealSignal(S, 0);
    int32_T *enc_pos2 = (int32_T *) ssGetOutputPortRealSignal(S, 1);
    const real_T *xD = ssGetDiscStates(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int_T   p_width4  = mxGetNumberOfElements(PARAM_DEF4(S));
    const int_T   p_width5  = mxGetNumberOfElements(PARAM_DEF5(S));
    const uint8_T *enc1 = (const uint8_T *) mxGetData(PARAM_DEF0(S));
    const uint8_T *pinA = (const uint8_T *) mxGetData(PARAM_DEF1(S));
    const uint8_T *pinB = (const uint8_T *) mxGetData(PARAM_DEF2(S));
    const uint8_T *enc2 = (const uint8_T *) mxGetData(PARAM_DEF3(S));
    const uint8_T *pinA2 = (const uint8_T *) mxGetData(PARAM_DEF4(S));
    const uint8_T *pinB2 = (const uint8_T *) mxGetData(PARAM_DEF5(S));
    
    Quad_Encoder_sfn_Outputs_wrapper(enc_pos1, enc_pos2, xD, enc1, p_width0, pinA, p_width1, pinB, p_width2, enc2, p_width3, pinA2, p_width4, pinB2, p_width5);

}

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is
 *    useful for performing any tasks that should only take place once per
 *    integration step.
 */
static void mdlUpdate(SimStruct *S, int_T tid)
{
    int32_T *enc_pos1 = (int32_T *) ssGetOutputPortRealSignal(S, 0);
    int32_T *enc_pos2 = (int32_T *) ssGetOutputPortRealSignal(S, 1);
    real_T *xD = ssGetDiscStates(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int_T   p_width4  = mxGetNumberOfElements(PARAM_DEF4(S));
    const int_T   p_width5  = mxGetNumberOfElements(PARAM_DEF5(S));
    const uint8_T *enc1 = (const uint8_T *) mxGetData(PARAM_DEF0(S));
    const uint8_T *pinA = (const uint8_T *) mxGetData(PARAM_DEF1(S));
    const uint8_T *pinB = (const uint8_T *) mxGetData(PARAM_DEF2(S));
    const uint8_T *enc2 = (const uint8_T *) mxGetData(PARAM_DEF3(S));
    const uint8_T *pinA2 = (const uint8_T *) mxGetData(PARAM_DEF4(S));
    const uint8_T *pinB2 = (const uint8_T *) mxGetData(PARAM_DEF5(S));
    
    Quad_Encoder_sfn_Update_wrapper(enc_pos1, enc_pos2, xD, enc1, p_width0, pinA, p_width1, pinB, p_width2, enc2, p_width3, pinA2, p_width4, pinB2, p_width5);

}
#endif /* MDL_UPDATE */
/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    real_T *xD = ssGetDiscStates(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int_T   p_width4  = mxGetNumberOfElements(PARAM_DEF4(S));
    const int_T   p_width5  = mxGetNumberOfElements(PARAM_DEF5(S));
    const uint8_T *enc1 = (const uint8_T *) mxGetData(PARAM_DEF0(S));
    const uint8_T *pinA = (const uint8_T *) mxGetData(PARAM_DEF1(S));
    const uint8_T *pinB = (const uint8_T *) mxGetData(PARAM_DEF2(S));
    const uint8_T *enc2 = (const uint8_T *) mxGetData(PARAM_DEF3(S));
    const uint8_T *pinA2 = (const uint8_T *) mxGetData(PARAM_DEF4(S));
    const uint8_T *pinB2 = (const uint8_T *) mxGetData(PARAM_DEF5(S));
    
    Quad_Encoder_sfn_Terminate_wrapper(xD, enc1, p_width0, pinA, p_width1, pinB, p_width2, enc2, p_width3, pinA2, p_width4, pinB2, p_width5);

}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif



