#include "motor.h"
#include <pigpio.h>
#include <iostream>

// Timer callback for motor stepping
void stepTimerCallback(void* user) {
    Motor* motor = reinterpret_cast<Motor*>(user);
    motor->nextStep();
}

Motor::Motor(int in1, int in2, int in3, int in4) : IN1(in1), IN2(in2), IN3(in3), IN4(in4), currentStep(0) {
    // Initialize motor GPIO pins as output
    gpioSetMode(IN1, PI_OUTPUT);
    gpioSetMode(IN2, PI_OUTPUT);
    gpioSetMode(IN3, PI_OUTPUT);
    gpioSetMode(IN4, PI_OUTPUT);
    stop(); // Ensure motor is stopped initially
}

Motor::~Motor() {
    stop(); // Ensure motor stops when object is destroyed
}

void Motor::initialize() {
    // Additional initialization if necessary
}

void Motor::setStep(int step) {
    // Step sequence for a 4-step motor
    const int sequence[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    gpioWrite(IN1, sequence[step][0]);
    gpioWrite(IN2, sequence[step][1]);
    gpioWrite(IN3, sequence[step][2]);
    gpioWrite(IN4, sequence[step][3]);
}

void Motor::forward(int interval, int steps) {
    totalSteps = steps;
    stepCount = 0;
    direction = 1; // Set direction for forward movement
    // Register timer callback for stepping
    gpioSetTimerFuncEx(0, interval, stepTimerCallback, this);
}

void Motor::rollback(int interval, int steps) {
    totalSteps = steps;
    stepCount = 0;
    direction = -1; // Set direction for backward movement
    // Register timer callback for stepping
    gpioSetTimerFuncEx(0, interval, stepTimerCallback, this);
}

void Motor::stop() {
    // Cancel the timer callback to stop the motor
    gpioSetTimerFunc(0, 0, NULL);
    setStep(0); // Optionally reset to a known state
}

void Motor::nextStep() {
    if (stepCount < totalSteps) {
        currentStep = (currentStep + direction + 4) % 4; // Ensure currentStep wraps correctly
        setStep(currentStep);
        stepCount++;
    } else {
        stop(); // Stop the motor after completing the steps
    }
}





/*
In this revised version of the Motor class, forward and rollback methods now use gpioSetTimerFuncEx to control the motor steps. The stepTimerCallback is called at the specified interval, calling Motor::nextStep to advance the motor's steps in the specified direction. The motor stops automatically after completing the desired number of steps, thanks to the check in nextStep.
*/