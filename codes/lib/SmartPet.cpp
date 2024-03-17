#include "SmartPet.h"
#include <iostream>
#include <thread>
#include <chrono>

// 构造函数，初始化成员变量
SmartPet::SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4, int SCK, int SDA)
: sensor(trigPin, echoPin), motor(in1, in2, in3, in4), motorRunning(false), shouldOperateMotor(false) 
{
    weightArgs.SCK = SCK; // 设置SCK引脚
    weightArgs.SDA = SDA; // 设置SDA引脚
    WeightSensor::setup(&weightArgs); // 使用新引脚初始化重量传感器
}


// 主运行循环。
void SmartPet::run() {
    std::cout << "SmartPet operational." << std::endl;
    sensor.measureDistanceAsync([this](float distance) { // 异步测量距离并使用回调函数处理结果
        this->operateMotorBasedOnDistance(distance);
    });

    while (true) {
        checkWeightAndOperateMotor(); // 检查重量并根据重量操作电机
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 根据传感器测量的距离控制电机。
void SmartPet::operateMotorBasedOnDistance(float distance) {
    std::cout << "Distance: " << distance << " cm" << std::endl;
    if (distance < 10 && !motorRunning) {
        std::cout << "Object detected within 10cm. Operating motor..." << std::endl;
        motor.forward(2, 100); // 
        motorRunning = true;
    }
}

// 检查重量并根据重量操作电机。
void SmartPet::checkWeightAndOperateMotor() {
    WeightSensor::start(&weightArgs); // 开始承重传感器的测量
    if (weightArgs.weight >= 150 && motorRunning) { // 如果重量达到150g并且电机正在运行
        std::cout << "Target weight reached. Rolling back motor..." << std::endl;
        motor.rollback(2, 100); // 
        motorRunning = false;
    }
}
