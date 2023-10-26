#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define LOOPTIME 5

#define ENC2REDGEAR 216

#define MOTOR1 19 // upper at motor driver (close to Board)
#define MOTOR2 26 // lower at motor driver
#define ENCODERA 5 // purple
#define ENCODERB 6 // blue

#define GAIN_INCREMENT 0.5


float t = 0.01;

int encA;
int encB;
int encoderPosition = 0;
float redGearPosition = 0;
float referencePosition = 10;
float errorPosition = 0;

float e = 0;
float e1 = 0;
float e2 = 0;
float m = 0;
float m1 = 0;

unsigned int checkTime;
unsigned int checkTimeBefore;

float control();
void funcEncoderA();
void funcEncoderB();
void pulse_catch();

int total_num = 0;
int target_arr[10] = {};
int current_num = 0;


int main(void){
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);

    softPwmCreate(MOTOR1, 0, 100);
    softPwmCreate(MOTOR2, 0, 100);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB); 

    PIDResult results[TESTS_PER_GAIN * 3];
    int resultCount = 0;

    float pgain = 0;
    float igain = 1;
    float dgain = 1;

    float g1 = pgain + igain * t + dgain / t;
    float g2 = -1 * (pgain + 2 * dgain / t);
    float g3 = dgain / t;

    softPwmWrite(MOTOR1, 0);
    softPwmWrite(MOTOR2, 0);
    delay(1000);
    while(1){
        checkTime = millis();
        virtual_pulse();
        if(checkTime - checkTimeBefore > LOOPTIME){
            softPwmWrite(MOTOR1, 100);
            softPwmWrite(MOTOR2, 0);
    }
    return 0;
}

void funcEncoderA(){
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    if(encA == HIGH){
        if(encB == LOW) encoderPosition ++;
        else encoderPosition --;
    } else{
        if(encB == LOW) encoderPosition --;
        else encoderPosition ++;
    }
    redGearPosition = (float) encoderPosition / ENC2REDGEAR;
    errorPosition = referencePosition - redGearPosition;
}

void funcEncoderB(){
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    if(encB == HIGH){
        if(encA == LOW) encoderPosition --;
        else encoderPosition ++;
    } else{
        if(encA == LOW) encoderPosition ++;
        else encoderPosition --;
    }
    redGearPosition = (float) encoderPosition / ENC2REDGEAR;
    errorPosition = referencePosition - redGearPosition;
}