//#include "weight1.h"
//#include <iostream>
/*
WeightSensor::WeightSensor(int SCK, int SDA, int calibration, float coefficient)
    : SCK(SCK), SDA(SDA), calibration(calibration), coefficient(coefficient), running(false), latestWeight(0) {
    gpioInitialise();
    gpioSetMode(SCK, PI_OUTPUT);
    gpioSetMode(SDA, PI_INPUT);
    gpioWrite(SCK, PI_LOW);
}

WeightSensor::~WeightSensor() {
    stop();
    gpioTerminate();
}

void WeightSensor::start() {
    running = true;
    gpioSetAlertFunc(SDA, [](int pin, int level, uint32_t tick, void* userData) {
        if (level == 0) {  // SDA line low, data ready
            WeightSensor* sensor = static_cast<WeightSensor*>(userData);
            sensor->triggerRead();
        }
    }, this);
}

void WeightSensor::stop() {
    running = false;
    if (weightThread.joinable()) {
        weightThread.join();
    }
    gpioSetAlertFunc(SDA, nullptr, nullptr);  // Remove interrupt handler
}

int WeightSensor::getLatestWeight() const {
    return latestWeight.load();
}

void WeightSensor::triggerRead() {
    if (!running) return;
    latestWeight.store(readWeight());  // Atomic update of the latest weight
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
}*/
/*
WeightSensor::WeightSensor(int SCK, int SDA, int calibration, float coefficient)
    : SCK(SCK), SDA(SDA), calibration(calibration), coefficient(coefficient), running(false), latestWeight(0) {
    gpioInitialise();
    gpioSetMode(SCK, PI_OUTPUT);
    gpioSetMode(SDA, PI_INPUT);
    gpioWrite(SCK, PI_LOW);
}

WeightSensor::~WeightSensor() {
    stop();
    gpioTerminate();
}

void WeightSensor::start() {
    running = true;
    // 设置回调函数，使用 lambda 需要匹配正确的签名
    gpioSetAlertFunc(SDA, [](int gpio, int level, uint32_t tick) {
        if (level == 0) {  // SDA line low, data ready
            // 取得 WeightSensor 实例的指针，以便调用成员函数
            WeightSensor* sensor = static_cast<WeightSensor*>(gpioGetSamplesFuncUserData());
            if (sensor) {
                sensor->triggerRead();
            }
        }
    });
    gpioSetSamplesFuncUserData(this);  // 设置回调函数用户数据
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
}*/
#include "weight1.h"
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
