
#include "motor.h"
#include <chrono>
#include <thread>
#include <functional>


MotorController::MotorController(int pin1, int pin2, int pin3, int pin4)
: rotatedForward(false), rotatedBackward(false) {
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;
    for (int i = 0; i < 4; ++i) {
        gpioSetMode(pins[i], PI_OUTPUT);
    }
   
    
}



void MotorController::rotateForward(int steps) {
    if (!rotatedForward.exchange(true)) {
        step(steps, 1);
    }
    stop();
}

void MotorController::rotateBackward(int steps) {
    if (!rotatedBackward.exchange(true)) {
        step(steps, -1);
    }
    stop();
}

void MotorController::stop() {
    setStep(0, 0, 0, 0);
}

void MotorController::reset() {
    rotatedForward = false;
    rotatedBackward = false;
}

bool MotorController::hasRotatedForward() const {
    return rotatedForward.load();
}

bool MotorController::hasRotatedBackward() const {
    return rotatedBackward.load();
}

void MotorController::setStep(int w1, int w2, int w3, int w4) {
    gpioWrite(pins[0], w1);
    gpioWrite(pins[1], w2);
    gpioWrite(pins[2], w3);
    gpioWrite(pins[3], w4);
    gpioDelay(1000); 
  
  
}

void MotorController::step(int totalSteps, int direction) {
    int stepCount = 8;
    int stepSequence[8][4] = {
        {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
        {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
    };
    for (int i = 0; i < totalSteps; ++i) {
        for (int s = 0; s < stepCount; ++s) {
            int idx = (direction > 0) ? s : (stepCount - 1 - s);
            setStep(stepSequence[idx][0], stepSequence[idx][1], stepSequence[idx][2], stepSequence[idx][3]);
        }
    }
}

MotorController::~MotorController() {
    stop();
}


/*
#include "motor.h"
#include <chrono>
#include <thread>
#include <functional>

MotorController::MotorController(int pin1, int pin2, int pin3, int pin4)
: rotatedForward(false), rotatedBackward(false) {
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;
    for (int i = 0; i < 4; ++i) {
        gpioSetMode(pins[i], PI_OUTPUT);
    }
}

void MotorController::rotateForward(int steps) {
    if (!rotatedForward.exchange(true)) {
        step(steps, 1);
        completeCycle = false;  // Starting a new cycle
    }
    stop();
}

void MotorController::rotateBackward(int steps) {
    if (!rotatedBackward.exchange(true)) {
        step(steps, -1);
        completeCycle = true;  // Completing the cycle
    }
    stop();
}

void MotorController::stop() {
    setStep(0, 0, 0, 0);
}

void MotorController::reset() {
    rotatedForward = false;
    rotatedBackward = false;
}

void MotorController::resetAfterCompleteCycle() {
    if (completeCycle) {  // Only reset if the complete cycle has finished
        reset();
    }
}

bool MotorController::hasRotatedForward() const {
    return rotatedForward.load();
}

bool MotorController::hasRotatedBackward() const {
    return rotatedBackward.load();
}

void MotorController::setStep(int w1, int w2, int w3, int w4) {
    gpioWrite(pins[0], w1);
    gpioWrite(pins[1], w2);
    gpioWrite(pins[2], w3);
    gpioWrite(pins[3], w4);
    gpioDelay(1000);
}

void MotorController::step(int totalSteps, int direction) {
    int stepCount = 8;
    int stepSequence[8][4] = {
        {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
        {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
    };
    for (int i = 0; i < totalSteps; ++i) {
        for (int s = 0; s < stepCount; ++s) {
            int idx = (direction > 0) ? s : (stepCount - 1 - s);
            setStep(stepSequence[idx][0], stepSequence[idx][1], stepSequence[idx][2], stepSequence[idx][3]);
        }
    }
}

MotorController::~MotorController() {
    stop();
}
*/
