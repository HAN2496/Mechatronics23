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
void virtual_pulse();

int total_num = 0;
int target_arr[10] = {};
int current_num = 0;

float total_error = 0;
float min_error = 0;
int pulse_time = 0;

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

/*
1.수정할 것
 1) igain test인 경우 main함수의 while(pgain<1000)을 igain으로 변경
 2) 그리고 파일 저장명 변경

2. GAIN_INCREMENT
 - 실험시 gain값 얼마씩 증가시킬지 (위의 define문에 정의 되어 있음)
 - gain별로 아마 그 값을 다르게 설정해야할 것임.
    - i, d는 낮은 값에서 잘 될것이니 수정하면 됨.

3. 주의사항
 - 변수들이 새로운 test 전에 잘 초기화 되고있는지 확인할 것.
   (ex. total_error, checkTime등에 오류가 발생할 수 있음.)

*/

int main(void) {
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);
    pinMode(PULSEINPUT, INPUT);

    softPwmCreate(MOTOR1, 0, 100);
    softPwmCreate(MOTOR2, 0, 100);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);

    PIDResult results[TESTS_PER_GAIN * 3];
    int resultCount = 0;

    float pgain = 1;
    float igain = 1;
    float dgain = 1;

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
    }

    for (int i = 0; i < total_num - 1; i++) {
        min_error = min_error + (target_arr[i + 1] - target_arr[i]) * (target_arr[i + 1] - target_arr[i] / 6.25);
    }

    printf("Start\n");

    while (pgain < 1000) {
        printf("New Gain Start\n");
        current_num = 0;
        while (1) {
            checkTime = millis();
            virtual_pulse();
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
            if (current_num == total_num) {
                softPwmWrite(MOTOR1, 0);
                softPwmWrite(MOTOR2, 0);
                printf("%.5f", total_error);
                break;
            }
        }
        results[resultCount++] = (PIDResult){ pgain, igain, dgain, total_error };
        pgain = pgain + GAIN_INCREMENT;
        total_error = 0;
        checkTime = millis();
        checkTimeBefore = millis();
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
    printf("M: %.3f\n", m);
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

void virtual_pulse() {
    current_num++;

    referencePosition = target_arr[current_num];
    errorPosition = referencePosition - redGearPosition;

    checkTimeBefore = millis();
    pulse_time = millis();

}
//aaaaa
