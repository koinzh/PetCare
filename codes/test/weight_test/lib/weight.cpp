#include "weight.h"
#include <iostream>

WeightSensor* WeightSensor::instance = nullptr;

WeightSensor::WeightSensor(int SCK, int SDA, int calibration, float coefficient)
    : SCK(SCK), SDA(SDA), calibration(calibration), coefficient(coefficient), running(false), latestWeight(0) {
    gpioInitialise();
    gpioSetMode(SCK, PI_OUTPUT);
    gpioSetMode(SDA, PI_INPUT);
    gpioWrite(SCK, PI_LOW);
    instance = this;  // 在构造函数中设置实例指针
}

WeightSensor::~WeightSensor() {
    stop();
    gpioTerminate();
    instance = nullptr;  // 清除实例指针
}

void WeightSensor::start() {
    running = true;
    gpioSetAlertFunc(SDA, [](int gpio, int level, uint32_t tick) {
        if (level == 0 && WeightSensor::instance) {  // 确保实例有效
            WeightSensor::instance->triggerRead();
        }
    });
}

void WeightSensor::stop() {
    running = false;
    gpioSetAlertFunc(SDA, nullptr);  // 移除中断处理函数
}

int WeightSensor::getLatestWeight() const {
    return latestWeight.load();
}

void WeightSensor::triggerRead() {
    if (!running) return;
    latestWeight.store(readWeight());  // 原子更新最新重量
}

int WeightSensor::readWeight() {
    int rawWeight = readRawWeight();
    return static_cast<int>(1.52 * (static_cast<float>(rawWeight - calibration) / coefficient) - 76);
}

int WeightSensor::readRawWeight() {
    long value = 0;
    for (int i = 0; i < 24; ++i) {
        gpioWrite(SCK, PI_HIGH);
        gpioWrite(SCK, PI_LOW);
        if (gpioRead(SDA)) {
            value = (value << 1) + 1;
        } else {
            value <<= 1;
        }
    }
    gpioWrite(SCK, PI_HIGH); // Additional pulse to end the read
    gpioWrite(SCK, PI_LOW);

    if (value & 0x800000) {
        value |= ~0xFFFFFF;
    }
    return static_cast<int>(value);
}
