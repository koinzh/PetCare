#include "sonic.h"
#include "motor.h"
#include "weight.h"
#include "water.h"
#include "pigpio.h"
#include <iostream>
#include <csignal>
#include <atomic>
#include <mutex>
#include <thread>

std::atomic<bool> terminateProgram{false};
std::mutex mtx;  // 互斥锁用于保护共享变量

void signalHandler(int signum) {
    terminateProgram = true;
}

int main() {
    float thresholdDistance; // 距离阈值变量
    int weightThreshold; // 重量阈值变量

    // 获取用户输入的阈值
    std::cout << "Enter distance threshold (cm<500): ";
    std::cin >> thresholdDistance;
    std::cout << "Enter weight threshold (g): ";
    std::cin >> weightThreshold;

    if (gpioInitialise() < 0) {
        std::cerr << "GPIO initialization failed." << std::endl;
        return 1;
    }

    signal(SIGINT, signalHandler);
    MotorController motor(17, 18, 27, 22);
    UltrasonicSensor sensor(20, 21);
    WaterLevelController waterLevelController(6, 5); // new for water
    WeightSensor weightSensor(23, 24, 233084, 1010.27f);  // 初始化

    int countBelowThreshold = 0;
    const int thresholdCount = 3; // 连续3次距离小于设定阈值且重量小于设定阈值
    const float minValidDistance = 0.1;  // 最小有效距离

    weightSensor.start();  // 开始重量监测
    
    // water
    std::thread waterThread([&]() {
        while (!terminateProgram.load()) {
            // 可以在这里添加水位检测的相关处理代码
        }
    }); // water 

    sensor.setDistanceCallback([&](float distance) {
        std::lock_guard<std::mutex> lock(mtx);  // 使用互斥锁保护共享数据
        std::cout << "Distance: " << distance << " cm, Weight: " << weightSensor.getLatestWeight() << " g" << std::endl;

        if (distance < minValidDistance || distance > 500) {  // 忽略无效读数
            return;
        }

        int currentWeight = weightSensor.getLatestWeight();
        if (distance < thresholdDistance && currentWeight < weightThreshold) {
            countBelowThreshold++;
            if (countBelowThreshold >= thresholdCount && !motor.hasRotatedForward()) {
                std::cout << "Triggering Forward rotation." << std::endl;
                motor.rotateForward(128);  // 正转128步约等于90度
            }
        } else {
            countBelowThreshold = 0; // 重置计数器
        }

        // 当重量达到或超过设定的重量阈值，且电机之前已经正转过
        if (currentWeight >= weightThreshold && motor.hasRotatedForward()) {
            std::cout << "Triggering Reverse rotation." << std::endl;
            motor.rotateBackward(128);  // 反转128步约等于90度
            motor.reset();  // 在电机反转后重置状态，允许再次正转
        }
    });

    sensor.startMeasurement();

    while (!terminateProgram) {
        // 主循环内容
    }

    waterThread.join(); // water
    weightSensor.stop();
    sensor.stop();
    gpioTerminate();
    std::cout << "程序优雅地终止了。" << std::endl;
    return 0;
}
