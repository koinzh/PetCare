#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H

#include <atomic>
#include <thread>
#include <pigpio.h>

class WeightSensor {
public:
    WeightSensor(int SCK, int SDA, int calibration, float coefficient);
    ~WeightSensor();
    void start();
    void stop();
    int getLatestWeight() const;

    static WeightSensor* instance;  // 添加一个静态实例指针

private:
    int SCK, SDA;
    int calibration;
    float coefficient;
    std::atomic<bool> running;
    std::atomic<int> latestWeight;
    std::thread weightThread;

    void triggerRead();
    int readWeight();
    int readRawWeight();
};

#endif // WEIGHTSENSOR_H
