#ifndef SMARTPET_H
#define SMARTPET_H

#include "sonic.h"
#include "motor.h"
#include  "weight.h"
// SmartPet类负责整合传感器和电机的操作。
class SmartPet {
public:
    // 构造函数，初始化传感器和电机的引脚。
    SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4, int SCK, int SDA);
    
    // 开始SmartPet的操作。
    void run();

private:
    WeightSensor::Hx711Args weightArgs; 
    UltrasonicSensor sensor; // 超声波传感器对象
    Motor motor; // 电机对象
    bool motorRunning; // 标记电机是否正在运行
    bool shouldOperateMotor; // 标记是否应操作电机

    // 根据距离操作电机的方法。
    void operateMotorBasedOnDistance(float distance);
     void checkWeightAndOperateMotor(); // 声明一个检查重量并根据重量操作电机的方法
};

#endif // SMARTPET_H
