#include "sonic.h"
#include "motor.h"
#include "weight.h"
#include "water.h"
#include "pigpio.h"
#include <iostream>
#include <csignal>
#include <atomic>
#include <mutex>

std::atomic<bool> terminateProgram{false};
std::mutex mtx;  // 互斥锁用于保护共享变量

void signalHandler(int signum) {
    terminateProgram = true;
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "GPIO初始化失败。" << std::endl;
        return 1;
    }

    signal(SIGINT, signalHandler);
    MotorController motor(17, 18, 27, 22);
    UltrasonicSensor sensor(20, 21);
    WaterLevelController waterLevelController(6, 5);//new for water
    WeightSensor weightSensor(23, 24, 233084, 1010.27f);  // 初始化
    

    int countBelowThreshold = 0;
    const int thresholdCount = 3; // 连续3次距离小于10cm且重量小于300g
    const float thresholdDistance = 10.0;  // 距离阈值
    const float minValidDistance = 0.1;  // 最小有效距离
    const int weightThreshold = 150;  // 重量阈值

    weightSensor.start();  // 开始重量监测
    
    //water
    std::thread waterThread([&](){
       while (!terminateProgram.load()) {
        
        }
    });//water 
    

    sensor.setDistanceCallback([&](float distance) {
        std::lock_guard<std::mutex> lock(mtx);  // 使用互斥锁保护共享数据
        std::cout << "Distance: " << distance << " cm, Weight: " << weightSensor.getLatestWeight() << " g" << std::endl;
    //   std::cout << " Weight: " << weightSensor.getLatestWeight() << " g" << std::endl;
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

        // 当重量达到或超过300g，且电机之前已经正转过
        if (currentWeight >= weightThreshold && motor.hasRotatedForward()) {
            std::cout << "Triggering Reverse rotation." << std::endl;
            motor.rotateBackward(128);  // 反转128步约等于90度
            motor.reset();  // 在电机反转后重置状态，允许再次正转
        }
    });

    sensor.startMeasurement();

    while (!terminateProgram) {
        
       ////test code 
       // std::cout << "Motor hasRotatedForward: " << motor.hasRotatedForward() << std::endl;
      //  std::this_thread::sleep_for(std::chrono::seconds(1)); // 每秒打印一次状态
        //testcode
    }
        
        
        

    waterThread.join();//water
    weightSensor.stop();
    sensor.stop();
    gpioTerminate();
    std::cout << "程序优雅地终止了。" << std::endl;
    return 0;
}
