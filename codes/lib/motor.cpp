#include "motor.h"
#include <wiringPi.h>
#include <thread>

Motor::Motor(int in1, int in2, int in3, int in4) : IN1(in1), IN2(in2), IN3(in3), IN4(in4) {
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
    std::thread([=]() {
        for (int i = 0; i < steps; i++) {
            setStep(1, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(0, 1, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(0, 0, 1, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(0, 0, 0, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
        }
    }).detach(); // 启动线程并立即返回
}

void Motor::stop() {
    setStep(0, 0, 0, 0);
}

void Motor::rollback(int t, int steps) {
    std::thread([=]() {
        for (int i = 0; i < steps; i++) {
            setStep(0, 0, 0, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(0, 0, 1, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(0, 1, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            setStep(1, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
        }
    }).detach(); // 启动线程并立即返回
}
