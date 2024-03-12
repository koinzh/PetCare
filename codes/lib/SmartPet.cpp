#include "SmartPet.h"
#include <iostream>
#include <thread>
#include <chrono>

// 构造函数，初始化成员变量
SmartPet::SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4)
: sensor(trigPin, echoPin), motor(in1, in2, in3, in4), motorRunning(false), shouldOperateMotor(false) {
   
}

// 主运行循环。
void SmartPet::run() {
    std::cout << "SmartPet operational." << std::endl;
    sensor.measureDistanceAsync([this](float distance) { // 异步测量距离并使用回调函数处理结果
        this->operateMotorBasedOnDistance(distance);
    });

    while (true) {
        // 让主循环空转，真正的工作在回调函数中完成
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 根据传感器测量的距离控制电机。
void SmartPet::operateMotorBasedOnDistance(float distance) {
    std::cout << "Distance: " << distance << " cm" << std::endl;
    if (distance < 10 && !shouldOperateMotor) {
        std::cout << "Object detected within 10cm. Operating motor..." << std::endl;
        motor.forward(2, 100); // 操作电机运行
        shouldOperateMotor = true; // 设置标记，避免重复操作
        motorRunning = true;
    } else if (distance >= 10) {
        shouldOperateMotor = false; // 重置标记，允许电机在下次检测到物体时再次运行
        if (motorRunning) {
            motor.stop(); // 停止电机
            motorRunning = false;
        }
    }
}
