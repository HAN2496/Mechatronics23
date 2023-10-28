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
#define PULSEINPUT 21

#define GAIN_INCREMENT 0.5
#define TESTS_PER_GAIN 1


float t = 0.01;

int encA;
int encB;
int encoderPosition = 0;
float redGearPosition = 0;
float referencePosition = 10;
float errorPosition = 0;


float g1;
float g2;
float g3;

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
void virtual_pulse(int i);

int total_num = 0;
int target_arr[10] = {};
int current_num = 0;

float total_error = 0;
float min_error = 0;
int pulse_time = 0;
float pulseInterval = 500;

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

int main(void) {
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);

    softPwmCreate(MOTOR1, 0, 100);
    softPwmCreate(MOTOR2, 0, 100);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);

    PIDResult results[TESTS_PER_GAIN * 3];
    int resultCount = 0;

    float pgain = 1;
    float igain = 1;
    float dgain = 1;
    
    float lastTime = millis();

    float g1 = pgain + igain * t + dgain / t;
    float g2 = -1 * (pgain + 2 * dgain / t);
    float g3 = dgain / t;

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

    for (int i = 0; i < total_num - 1; i++) {
        min_error = min_error + (target_arr[i + 1] - target_arr[i]) * (target_arr[i + 1] - target_arr[i] / 6.25);
    }

    printf("Start\n");

    while (pgain < 1000) {
        printf("New Gain Start\n");
        for (int i=0; i<total_num; i++){
        virtual_pulse(i);
        while (checkTime - lastTime <= pulseInterval) {
            printf("%d, %.3f, %.3f\n", checkTime, lastTime, pulseInterval);
            checkTime = millis();
            if (checkTime - checkTimeBefore > LOOPTIME) {
                if (errorPosition > 0) {
                    softPwmWrite(MOTOR1, -control(g1, g2, g3));
                    softPwmWrite(MOTOR2, 0);
                }
                else {
                    softPwmWrite(MOTOR2, control(g1, g2, g3));
                    softPwmWrite(MOTOR1, 0);
                }
                checkTimeBefore = checkTime;
                total_error += LOOPTIME * fabs(errorPosition) * (checkTime - pulse_time);
            }
            if (i == total_num - 1) {
                softPwmWrite(MOTOR1, 0);
                softPwmWrite(MOTOR2, 0);
                printf("Total Error: %.5f\n", total_error);
                break;
            }
        }
        lastTime = millis();
        results[resultCount++] = (PIDResult){ pgain, igain, dgain, total_error };
        pgain = pgain + GAIN_INCREMENT;
        printf("PGAIN: %.3f\n",pgain);
        total_error = 0;
        checkTime = millis();
        checkTimeBefore = millis();
    }
    }
    saveResultsToCSV(results, resultCount, "PTest_result.csv");
    return 0;
}

float control() {
    e = errorPosition;
    m = m1 + g1 * e + g2 * e1 + g3 * e2;
    e2 = e1;
    e1 = e;
    m1 = m;
    //printf("M: %.3f\n", m);
    return m;
}

void funcEncoderA() {
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    if (encA == HIGH) {
        if (encB == LOW) encoderPosition++;
        else encoderPosition--;
    }
    else {
        if (encB == LOW) encoderPosition--;
        else encoderPosition++;
    }
    redGearPosition = (float)encoderPosition / ENC2REDGEAR;
    errorPosition = referencePosition - redGearPosition;
}

void funcEncoderB() {
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    if (encB == HIGH) {
        if (encA == LOW) encoderPosition--;
        else encoderPosition++;
    }
    else {
        if (encA == LOW) encoderPosition++;
        else encoderPosition--;
    }
    redGearPosition = (float)encoderPosition / ENC2REDGEAR;
    errorPosition = referencePosition - redGearPosition;
}

void virtual_pulse(int i) {
    referencePosition = target_arr[i];
    errorPosition = referencePosition - redGearPosition;

    checkTimeBefore = millis();
    checkTime = millis();
    pulse_time = millis();

}
//aaaaa
