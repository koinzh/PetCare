#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H

#include <atomic>
#include <thread>
#include <pigpio.h>
#include <queue>
#include <numeric>  


class WeightSensor {
public:
    WeightSensor(int SCK, int SDA, int calibration, float coefficient);
    ~WeightSensor();
    void start();
    void stop();
    int getLatestWeight() const;

    static WeightSensor* instance;  

private:
    int SCK, SDA;
    int calibration;
    float coefficient;
    std::atomic<bool> running;
    std::atomic<int> latestWeight;
    std::thread weightThread;
   
    std::deque<int> weightHistory;
    const size_t weightHistorySize = 10;  

    void triggerRead();
    int readWeight();
    int readRawWeight();
    void updateWeightHistory(int newWeight);
    int getSmoothedWeight();
};

#endif // WEIGHTSENSOR_H
