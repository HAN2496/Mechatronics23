#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define LOOPTIME 5

#define ENC2REDGEAR 216
#define TESTS_PER_GAIN 1

#define MOTOR1 19 // upper at motor driver (close to Board)
#define MOTOR2 26 // lower at motor driver
#define ENCODERA 5 // purple
#define ENCODERB 6 // blue
#define PULSEINPUT 21

float pgain = 50;
float igain = 2;
float dgain = 20;
float t = 0.01;

float g1;
float g2;
float g3;

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

int total_num;
int target_arr[10] = {};
int current_num = 0;

float total_error = 0;
float min_error = 0;
int pulse_time = 0;
float pulseInterval = 5000;

typedef struct {
    float pgain, igain, dgain;
    float total_error;
} PIDResult;

void saveResultsToCSV(PIDResult results[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in Saving Data.\n");
        return;
    }
    fprintf(file, "P Gain, I Gain, D Gain, Total Error\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%.2f, %.2f, %.2f, %.5f\n",
            results[i].pgain, results[i].igain, results[i].dgain,
            results[i].total_error);
    }
    fclose(file);
}

int main(void){
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);

    softPwmCreate(MOTOR1, 0, 100);
    softPwmCreate(MOTOR2, 0, 100);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);

	PIDResult results[3000];
	int resultCount = 0;
    g1 = pgain + igain * t + dgain / t;
    g2 = -1 * (pgain + 2 * dgain / t);
    g3 = dgain / t;

    softPwmWrite(MOTOR1, 0);
    softPwmWrite(MOTOR2, 0);
    delay(1000);
    
    printf("P, I, D = %.2f, %.2f, %.2f\n", pgain, igain, dgain);

    int total_num = rand() % 6 + 5;
    for (int i = 0; i < total_num; i++) {
        target_arr[i] = rand() % 16 - 8;
        printf("%d ", target_arr[i]);
    }
    printf("\n");
    delay(1000);

    for (int i = 0; i < total_num - 1; i++) {
        min_error = min_error + (target_arr[i + 1] - target_arr[i]) * (target_arr[i + 1] - target_arr[i] / 6.25);
    }

    printf("Start\n");

    while(pgain<500){
		printf("NEW PGAIN: %.1f\n", pgain);
		delay(2000);
        while (current_num < total_num){
            pulse_catch();
            while(checkTime - pulse_time <= pulseInterval){
                checkTime = millis();
                if(checkTime - checkTimeBefore > LOOPTIME){
                if (errorPosition > 0){
                    softPwmWrite(MOTOR1, control());
                    softPwmWrite(MOTOR2, 0);
                    } else {
                    softPwmWrite(MOTOR2, -1 * control());
                    softPwmWrite(MOTOR1, 0);
                    }
                    checkTimeBefore = checkTime;
                    total_error += LOOPTIME * fabs(errorPosition) * (checkTime - pulse_time);
                }
                if(current_num == total_num - 1){
                    softPwmWrite(MOTOR1, 0);
                    softPwmWrite(MOTOR2, 0);
                    printf("%.5f", total_error);
                    delay(1000);
                    printf("HEREHEREHERE\n");
                    current_num = 0;
                    break;
                }
            }
        }
        pgain = pgain + 0.5;
		results[resultCount++] = (PIDResult){ pgain, igain, dgain, total_error };
		total_error=0;
    }
	saveResultsToCSV(results, resultCount, "PTest_result.csv");
    return 0;
}

float control(){
    e = errorPosition;
    m = m1 + g1 * e + g2 * e1 + g3 * e2;
    e2 = e1;
    e1 = e;
    m1 = m;
    printf("M: %.2f | E: %.2f\n", m, e);
    return m;
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

void pulse_catch(){

    referencePosition  = -target_arr[current_num];
    printf("******\n");
    printf("PULSE: %.3f\n", referencePosition);
    delay(1000);
    errorPosition = referencePosition - redGearPosition;

    checkTimeBefore = millis();
    checkTime = millis();
    pulse_time = millis();
    current_num++;

}

