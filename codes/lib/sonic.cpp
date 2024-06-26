#include "sonic.h"
#include <iostream>
#include <thread>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : trigPin(triggerPin), echoPin(echoPin), running(false) {
    gpioSetMode(trigPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
    gpioSetAlertFuncEx(echoPin, echoInterrupt, this);
}

UltrasonicSensor::~UltrasonicSensor() {
    stop();
    gpioSetAlertFuncEx(echoPin, nullptr, nullptr);
}

void UltrasonicSensor::startMeasurement() {
    running = true;
    std::thread([&]() {
        while (running) {
            triggerPulse();
            waitForEcho();
        }
    }).detach();
}

void UltrasonicSensor::stop() {
    running = false;
    cv.notify_all();
}

void UltrasonicSensor::setDistanceCallback(std::function<void(float)> callback) {
    distanceCallback = callback;
}

void UltrasonicSensor::triggerPulse() {
    // generate a 10 microsecond high level pulse
    gpioTrigger(trigPin, 10, 1); 
}


void UltrasonicSensor::waitForEcho() {
    std::unique_lock<std::mutex> lock(mtx);
    if (!cv.wait_for(lock, std::chrono::milliseconds(100), [this] { return this->endTime > this->startTime; })) {
        std::cerr << "Timeout waiting for echo response." << std::endl;
    } else {
        if (distanceCallback) {
            float distance = (endTime - startTime) * 0.0343 / 2.0;
            distanceCallback(distance);
        }
    }
}

void UltrasonicSensor::echoInterrupt(int gpio, int level, uint32_t tick, void* user) {
    UltrasonicSensor* sensor = static_cast<UltrasonicSensor*>(user);
    if (level == 1) {
        sensor->startTime = tick;
    } else if (level == 0) {
        sensor->endTime = tick;
        sensor->cv.notify_one();
    }
}
