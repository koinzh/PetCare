#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H

#include <atomic>
#include <thread>
#include <pigpio.h>
#include <queue>
#include <numeric>  // 包括这个头文件以使用 std::accumulate


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
    //std::queue<int> weightHistory;
  //  const size_t weightHistorySize = 10;  
    std::deque<int> weightHistory;
    const size_t weightHistorySize = 10;  // 维持10个数据点进行平均

    void triggerRead();
    int readWeight();
    int readRawWeight();
    void updateWeightHistory(int newWeight);
    int getSmoothedWeight();
};

#endif // WEIGHTSENSOR_H
