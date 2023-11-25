#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define LOOPTIME 5

//실험을 통해 정해진 ENC2REDGEAR값
#define ENC2REDGEAR 235.78

#define MOTOR1 19 // upper at motor driver
#define MOTOR2 26 // lower at motor driver
#define ENCODERA 5 // purple
#define ENCODERB 6 // blue
#define PULSEINPUT 21

//PID 제어를 위한 변수들
float pgain = 600;
float igain = 0.2;
float dgain = 50;
float t = 0.01;

float g1;
float g2;
float g3;

float e = 0;
float e1 = 0;
float e2 = 0;
float m = 0;
float m1 = 0;

int encA;
int encB;
int encoderPosition = 0;
float redGearPosition = 0;
float referencePosition = 0;
float errorPosition = 0;

unsigned int checkTime;
unsigned int checkTimeBefore;

float control();
void funcEncoderA();
void funcEncoderB();
void detect_pulse();


int total_num; //총 펄스 횟수
int trial_arr[10] = {}; //목표 위치 저장 배열
int current_trial = -1; //현재 시도 횟수

float itae_error = 0;
int pulse_time = 0;

int main(void){
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);

    softPwmCreate(MOTOR1, 0, 100);
    softPwmCreate(MOTOR2, 0, 100);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);

    //펄스 감지를 위한 코드
    pinMode(PULSEINPUT, INPUT);
    wiringPiISR(PULSEINPUT, INT_EDGE_RISING, detect_pulse);

    //PID 변수. Fine tuning을 할 시에는 gain값이 계속 변하므로 main문 안에서 정의함.
    g1 = pgain + igain * t + dgain / t;
    g2 = -1 * (pgain + 2 * dgain / t);
    g3 = dgain / t;

    softPwmWrite(MOTOR1, 0);
    softPwmWrite(MOTOR2, 0);
    delay(1000);
    
    printf("P, I, D = %.2f, %.2f, %.2f\n", pgain, igain, dgain);

    //총 펄스 횟수 입력 및 저장
    printf("Enter Total Trial Number: ");
    scanf("%d", &total_num);
    printf("\n");

    int target_pos;

    // 목표위치 입력 및 저장
    for(int i = 0; i<total_num; i++){
        printf("%d trial target :", i+1);
        scanf("%d", &target_pos);
        trial_arr[i] = target_pos;
    }

    while(1){
	if(current_trial>-1){ //초기 펄스를 받기 전까지 대기
	    checkTime = millis();
	    if(checkTime - checkTimeBefore > LOOPTIME){ //최소단위만큼 시간이 흘렀을 때 시작하게 함.
            if (errorPosition > 0){ //errorPosition 부호에 따라 회전 방향을 맞추는 조건문
                softPwmWrite(MOTOR1, control());
                softPwmWrite(MOTOR2, 0);
            } else {
                softPwmWrite(MOTOR2, -1 * control());
                softPwmWrite(MOTOR1, 0);
            }
            checkTimeBefore = checkTime;
            //에러메세지 입력. 시간이 ms단위이므로 1000000 만큼 나누어줌.
            itae_error += LOOPTIME * fabs(errorPosition) * (checkTime - pulse_time) / 1000 / 1000;
	    }
	    if(current_trial == total_num){ //완료시 모터 회전 중지.
            softPwmWrite(MOTOR1, 0);
            softPwmWrite(MOTOR2, 0);
            printf("ITAE: %.5f", itae_error);
            break;
	    }
	}
    }
    return 0;
}

//PID 제어 함수
float control(){
    e = errorPosition;
    m = m1 + g1 * e + g2 * e1 + g3 * e2;
    e2 = e1;
    e1 = e;
    m1 = m;
    printf("M: %.3f\n", m);
    return m;
}

//엔코더A함수
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

//엔코더B함수
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

//펄스 감지 함수
void detect_pulse(){
    if(millis() - pulse_time>500){
        printf("******\nPULSE\n");
        current_trial++;

        referencePosition  = -trial_arr[current_trial]; //위치 부호를 반대로 바꾸어줌. 회전 방향을 맞추기 위함.
        errorPosition = referencePosition - redGearPosition;

        checkTimeBefore = millis(); //시간 초기화
        checkTime = millis(); //시간 초기화
        pulse_time = millis(); //시간 초기화
    }

}

