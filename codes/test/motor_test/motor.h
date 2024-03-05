
#ifndef SMARTPET_MOTOR_TEST
#define SMARTPET_MOTOR_TEST


#include <wiringPi.h>
#include <cstdio>

class motor{

public:
#define IN1  0    // GPIO11
#define IN2  1    // GPIO12
#define IN3  2    // GPIO13
#define IN4  3    // GPIO15

    static void SetStep(int a, int b, int c, int d);
    static void Forward(int t, int steps);
    static void Stop();
    static void Rollback(int t, int steps);
};

#endif 
