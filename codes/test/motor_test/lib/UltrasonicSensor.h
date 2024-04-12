#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <functional>
#include <mutex>
#include <condition_variable>
#include "pigpio.h"

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    ~UltrasonicSensor();
    void startMeasurement();
    void stop();
    void setDistanceCallback(std::function<void(float)> callback);

private:
    int trigPin, echoPin;
    bool running;
    std::mutex mtx;
    std::condition_variable cv;
    std::function<void(float)> distanceCallback;
    uint32_t startTime, endTime;
    static void echoInterrupt(int gpio, int level, uint32_t tick, void* user);
    void triggerPulse();
    void waitForEcho();
};

#endif // ULTRASONICSENSOR_H
