#include "UltrasonicSensor.h"
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
/*
void UltrasonicSensor::triggerPulse() {
    gpioWrite(trigPin, PI_LOW);
    gpioDelay(2);
    gpioWrite(trigPin, PI_HIGH);
    gpioDelay(10);
    gpioWrite(trigPin, PI_LOW);
}*/

void UltrasonicSensor::triggerPulse() {
    // 使用 gpioTrigger 来生成一个10微秒的高电平脈衝，無需手動處理低电平和高电平的轉換
    gpioTrigger(trigPin, 10, 1); // 第一个参数是GPIO pin，第二个参数是脉冲长度（微秒），第三个参数是脉冲电平（1表示高电平）
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
