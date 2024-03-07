#include "motor.h"

Motor::Motor(int in1, int in2, int in3, int in4) : IN1(in1), IN2(in2), IN3(in3), IN4(in4) {
    this->initialize();
}

void Motor::initialize() {
    wiringPiSetup();
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void Motor::setStep(int a, int b, int c, int d) {
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}

void Motor::forward(int t, int steps) {
    for (int i = 0; i < steps; i++) {
        setStep(1, 0, 0, 0);
        delay(t);
        setStep(0, 1, 0, 0);
        delay(t);
        setStep(0, 0, 1, 0);
        delay(t);
        setStep(0, 0, 0, 1);
        delay(t);
    }
}

void Motor::stop() {
    setStep(0, 0, 0, 0);
}

void Motor::rollback(int t, int steps) {
    for (int i = 0; i < steps; i++) {
        setStep(0, 0, 0, 1);
        delay(t);
        setStep(0, 0, 1, 0);
        delay(t);
        setStep(0, 1, 0, 0);
        delay(t);
        setStep(1, 0, 0, 0);
        delay(t);
    }
}
