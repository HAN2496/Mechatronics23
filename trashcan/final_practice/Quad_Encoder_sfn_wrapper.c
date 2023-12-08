
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE

#include </home/pi/WiringPi/wiringPi/softServo.h>
#include </home/pi/WiringPi/wiringPi/wiringSerial.h>
#include </home/pi/WiringPi/wiringPi/softTone.h>
#include </home/pi/WiringPi/wiringPi/wiringPiI2C.h>
#include </home/pi/WiringPi/wiringPi/wiringShift.h>
#include </home/pi/WiringPi/wiringPi/softPwm.h>
#include </home/pi/WiringPi/wiringPi/wiringPi.h>
#include </home/pi/WiringPi/wiringPi/wiringPiSPI.h>
// for digital out:
#include </home/pi/WiringPi/wiringPi/wiringPi.c>
#include </home/pi/WiringPi/wiringPi/piHiPri.c>
// for pwm:
#include </home/pi/WiringPi/wiringPi/softPwm.c>
#include </home/pi/WiringPi/wiringPi/piThread.c>

typedef struct { int pinA; int pinB; int pos; int del;} Encoder;    
volatile Encoder Enc[3] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

void irsPinAEn0(){                                 
  int drB = digitalRead(Enc[0].pinB);
  int drA = digitalRead(Enc[0].pinA);

  /* this updates the counter                                */
  if (drA == HIGH) {   /* low->high on A? */
    if (drB == LOW) {  /* check pin B */
  	Enc[0].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[0].pos--;  /* going counterclockwise: decrement  */
    }
    
  } else {                       /* must be high to low on A */
  
    if (drB == HIGH) { /* check pin B */
  	Enc[0].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[0].pos--;  /* going counterclockwise: decrement  */
    }
    
  } /* end counter update                                    */
} /* end ISR pin A Encoder 0                                 */

void isrPinBEn0(){ 
  int drA = digitalRead(Enc[0].pinA);
  int drB = digitalRead(Enc[0].pinB);

  /* this updates the counter                                */
  if (drB == HIGH) {   /* low->high on B? */
  
    if (drA == HIGH) { /* check pin A */
  	Enc[0].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[0].pos--;  /* going counterclockwise: decrement  */
    }
  
  } else {                       /* must be high to low on B */
  
    if (drA == LOW) {  /* check pin A */
  	Enc[0].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[0].pos--;  /* going counterclockwise: decrement  */
    }
    
  } /* end counter update */
} /* end ISR pin B Encoder 0  */




void irsPinAEn1(){
  int drB = digitalRead(Enc[1].pinB);
  
  /* possibly wait before reading pin A, then read it        */
  //debounce(Enc[0].del);
  int drA = digitalRead(Enc[1].pinA);

  /* this updates the counter                                */
  if (drA == HIGH) {   /* low->high on A? */
      
    if (drB == LOW) {  /* check pin B */
  	Enc[1].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[1].pos--;  /* going counterclockwise: decrement  */
    }
    
  } else {                       /* must be high to low on A */
  
    if (drB == HIGH) { /* check pin B */
  	Enc[1].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[1].pos--;  /* going counterclockwise: decrement  */
    }
    
  } /* end counter update                                    */
} /* end ISR pin A Encoder 0                                 */


void isrPinBEn1(){ 
  int drA = digitalRead(Enc[1].pinA);
  
  /* possibly wait before reading pin B, then read it        */
  //debounce(Enc[0].del);
  int drB = digitalRead(Enc[1].pinB);

  /* this updates the counter                                */
  if (drB == HIGH) {   /* low->high on B? */
  
    if (drA == HIGH) { /* check pin A */
  	Enc[1].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[1].pos--;  /* going counterclockwise: decrement  */
    }
  
  } else {                       /* must be high to low on B */
  
    if (drA == LOW) {  /* check pin A */
  	Enc[1].pos++;  /* going clockwise: increment         */
    } else {
  	Enc[1].pos--;  /* going counterclockwise: decrement  */
    }
    
  } /* end counter update */
} /* end ISR pin B Encoder 0  */

# endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void Quad_Encoder_sfn_Start_wrapper(real_T *xD,
			const uint8_T *enc1, const int_T p_width0,
			const uint8_T *pinA, const int_T p_width1,
			const uint8_T *pinB, const int_T p_width2,
			const uint8_T *enc2, const int_T p_width3,
			const uint8_T *pinA2, const int_T p_width4,
			const uint8_T *pinB2, const int_T p_width5)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
/*
 *     .
 */
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void Quad_Encoder_sfn_Outputs_wrapper(int32_T *enc_pos1,
			int32_T *enc_pos2,
			const real_T *xD,
			const uint8_T *enc1, const int_T p_width0,
			const uint8_T *pinA, const int_T p_width1,
			const uint8_T *pinB, const int_T p_width2,
			const uint8_T *enc2, const int_T p_width3,
			const uint8_T *pinA2, const int_T p_width4,
			const uint8_T *pinB2, const int_T p_width5)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]==1) {
    /* don't do anything for mex file generation */
    # ifndef MATLAB_MEX_FILE          
        /* get encoder position and set is as output */
       *enc_pos1=Enc[0].pos;
       *enc_pos2=Enc[1].pos;
    # endif
    
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void Quad_Encoder_sfn_Update_wrapper(int32_T *enc_pos1,
			int32_T *enc_pos2,
			real_T *xD,
			const uint8_T *enc1, const int_T p_width0,
			const uint8_T *pinA, const int_T p_width1,
			const uint8_T *pinB, const int_T p_width2,
			const uint8_T *enc2, const int_T p_width3,
			const uint8_T *pinA2, const int_T p_width4,
			const uint8_T *pinB2, const int_T p_width5)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]!=1) {
    # ifndef MATLAB_MEX_FILE
        Enc[enc1[0]].pinA=pinA[0];      /* set pin A              */
        Enc[enc1[0]].pinB=pinB[0];      /* set pin B              */
        Enc[enc2[0]].pinA=pinA2[0];      /* set pin A              */
        Enc[enc2[0]].pinB=pinB2[0];      /* set pin B              */

        /* set up WiringPi                           			 */	
		wiringPiSetupGpio();
        pinMode(pinA[0], INPUT);
        pinMode(pinB[0], INPUT);
        pinMode(pinA2[0], INPUT);
        pinMode(pinB2[0], INPUT);
    	wiringPiISR (pinA[0], INT_EDGE_BOTH, &irsPinAEn0);
    	wiringPiISR (pinB[0], INT_EDGE_BOTH, &isrPinBEn0);
    	wiringPiISR (pinA2[0], INT_EDGE_BOTH, &irsPinAEn1);
    	wiringPiISR (pinB2[0], INT_EDGE_BOTH, &isrPinBEn1);
        # endif
    
    /* initialization done */ 
    xD[0]=1;
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Terminate function
 *
 */
void Quad_Encoder_sfn_Terminate_wrapper(real_T *xD,
			const uint8_T *enc1, const int_T p_width0,
			const uint8_T *pinA, const int_T p_width1,
			const uint8_T *pinB, const int_T p_width2,
			const uint8_T *enc2, const int_T p_width3,
			const uint8_T *pinA2, const int_T p_width4,
			const uint8_T *pinB2, const int_T p_width5)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
/*
 *     .
 *
 /
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

