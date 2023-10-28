#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR1 19			// Motor DI 1
#define MOTOR2 26			// Motor DI 2

int main(void)
{
    wiringPiSetupGpio();
    softPwmCreate(MOTOR1, 0, 100);	// Create soft Pwm
    softPwmCreate(MOTOR2, 0, 100); 	// Create soft Pwm 	
    while (1)
    {
        float cnt = 0;
        while(cnt<5){
            softPwmWrite(MOTOR1, cnt);
            softPwmWrite(MOTOR2, 0);
            delayMicroseconds(1000);
            cnt += 0.5
        }
        cnt = 0;
    }
    return 0;
}