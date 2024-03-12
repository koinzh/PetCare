#include "motor.h"

int main()
{
    if (wiringPiSetup() < 0) {
        printf("Setup wiringPi failed!\n");
        return -1;
    }

    /* set pins mode as output */
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    while (1) {
        printf("+++\n");
        motor::Forward(2, 400);

        printf("stop\n");
        motor::Stop();

        printf("---\n");
        motor::Rollback(2, 400);

        printf("stop\n");
        motor::Stop();
        delay(2000);
    }
}
