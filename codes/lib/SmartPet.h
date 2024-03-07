#ifndef SMARTPET_H
#define SMARTPET_H

#include "sonic.h"
#include "motor.h"

class SmartPet {
public:
    SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4);
    void run();

private:
    UltrasonicSensor sensor;
    Motor motor;
    bool motorRunning;

    void operateMotorBasedOnDistance();
};

#endif // SMARTPET_H
