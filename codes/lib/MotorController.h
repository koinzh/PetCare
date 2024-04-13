#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <atomic>
#include "pigpio.h"

class MotorController {
public:
    MotorController(int pin1, int pin2, int pin3, int pin4);
    ~MotorController();
    void rotateForward(int steps);
    void rotateBackward(int steps);
    void stop();
    void reset();
    bool hasRotatedForward() const;
    bool hasRotatedBackward() const;

private:
    int pins[4];
    std::atomic<bool> rotatedForward; 
    std::atomic<bool> rotatedBackward;
    void setStep(int w1, int w2, int w3, int w4);
    void step(int totalSteps, int direction);
    //Timer* timer;
};

#endif // MOTORCONTROLLER_H
