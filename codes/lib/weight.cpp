#include "weight.h"
#include <iostream>
#include <queue>


WeightSensor* WeightSensor::instance = nullptr;

WeightSensor::WeightSensor(int SCK, int SDA, int calibration, float coefficient)
    : SCK(SCK), SDA(SDA), calibration(calibration), coefficient(coefficient), running(false), latestWeight(0) {
    gpioInitialise();
    gpioSetMode(SCK, PI_OUTPUT);
    gpioSetMode(SDA, PI_INPUT);
    gpioWrite(SCK, PI_LOW);
    instance = this;  // Set the instance pointer in the constructor.
}

WeightSensor::~WeightSensor() {
    stop();
    gpioTerminate();
    instance = nullptr;  // Clear the instance pointer.
}

void WeightSensor::start() {
    running = true;
    gpioSetAlertFunc(SDA, [](int gpio, int level, uint32_t tick) {
        if (level == 0 && WeightSensor::instance) {  // make sure the instance is useful
            WeightSensor::instance->triggerRead();
        }
    });
}

void WeightSensor::stop() {
    running = false;
    gpioSetAlertFunc(SDA, nullptr);  // Remove the interrupt handler function
}

int WeightSensor::getLatestWeight() const {
    return latestWeight.load();
}

void WeightSensor::triggerRead() {
    if (!running) return;
   // int rawWeight = readWeight();
    //updateWeightHistory(rawWeight);
    latestWeight.store(readWeight());  // Update the latest weight
}

int WeightSensor::readWeight() {
    int rawWeight = readRawWeight();
    //return static_cast<int>(1.52 * (static_cast<float>(rawWeight - calibration) / coefficient) - 76);
    return static_cast<int>(static_cast<float>(rawWeight - calibration) / coefficient);
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
/*
void WeightSensor::updateWeightHistory(int newWeight) {
    if (weightHistory.size() >= weightHistorySize) {
        weightHistory.pop();  // 如果队列已满，移除最老的数据
    }
    weightHistory.push(newWeight);  // 添加新的重量读数
}

int WeightSensor::getSmoothedWeight() {
    if (weightHistory.empty()) return 0;
    int sum = std::accumulate(weightHistory.begin(), weightHistory.end(), 0);
    return sum / weightHistory.size();  // 计算并返回平均重量
}
*/
void WeightSensor::updateWeightHistory(int newWeight) {
    if (weightHistory.size() >= weightHistorySize) {
        weightHistory.pop_front();  // 如果deque已满，移除最老的数据
    }
    weightHistory.push_back(newWeight);  // 添加新的重量记录
}

int WeightSensor::getSmoothedWeight() {
    if (weightHistory.empty()) return 0;
    int sum = std::accumulate(weightHistory.begin(), weightHistory.end(), 0);
    return sum / weightHistory.size();  // 计算并返回平均重量
}
