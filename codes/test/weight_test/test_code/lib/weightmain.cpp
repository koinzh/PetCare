#include "weight1.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    WeightSensor sensor(23, 24, 233084, 1010.27f); // 使用适当的参数初始化传感器
    sensor.start();  // 开始传感器数据读取

    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒钟，查看输出
        std::cout << "Latest Weight: " << sensor.getLatestWeight() << " grams" << std::endl;
    }

    sensor.stop();  // 停止传感器数据读取
    return 0;
}
