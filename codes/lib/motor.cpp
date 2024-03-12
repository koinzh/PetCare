#include "motor.h"
#include <wiringPi.h>
#include <iostream>
#include <thread>
#include <chrono>

Motor::Motor(int in1, int in2, int in3, int in4) : IN1(in1), IN2(in2), IN3(in3), IN4(in4) {
    wiringPiSetup(); // Make sure to call this in main() or setup
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    stop(); // Ensure motor starts in a stopped state
}

void Motor::setStep(int a, int b, int c, int d) {
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}

void Motor::forward(int t, int steps) {
    state = FORWARD; // Update state to FORWARD
    printState(); // Print current state
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
        stop(); // Stop the motor after completing the steps
    }).detach(); // Run the thread without blocking
}

void Motor::stop() {
    state = STOPPED; // Update state to STOPPED
    printState(); // Print current state
    setStep(0, 0, 0, 0); // Stop the motor by setting all outputs to low
}

void Motor::rollback(int t, int steps) {
    state = BACKWARD; // Update state to BACKWARD
    printState(); // Print current state
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
        stop(); // Stop the motor after completing the steps
    }).detach(); // Run the thread without blocking
}

void Motor::printState() {
    std::string stateStr;
    switch (state) {
        case FORWARD:
            stateStr = "FORWARD";
            break;
        case STOPPED:
            stateStr = "STOPPED";
            break;
        case BACKWARD:
            stateStr = "BACKWARD";
            break;
    }
    std::cout << "Motor state: " << stateStr << std::endl;
}
