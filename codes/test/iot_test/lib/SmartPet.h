#ifndef SMARTPET_H
#define SMARTPET_H

// 引入SDK的头文件
#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "aiot_mqtt_api.h"
#include "aiot_dm_api.h"
#include <cstddef>


// SmartPet类负责整合传感器和电机的操作。
class IOTConnect {
public:
    // 构造函数，初始化传感器和电机的引脚。
    IOTConnect();
    
    // 开始SmartPet的操作。
    void run();
    void *mqtt_handle = NULL;
    void *dm_handle = NULL;

     ~IOTConnect();

    void initializeIotSdk(); // 初始化SDK
    void deinitializeIotSdk(); // 清理SDK资源
    void reportDistance(float distance); // 上报距离信息
/*private:
    WeightSensor::Hx711Args weightArgs; 
    UltrasonicSensor sensor; // 超声波传感器对象
    Motor motor; // 电机对象
    bool motorRunning; // 标记电机是否正在运行
    bool shouldOperateMotor; // 标记是否应操作电机

    // 根据距离操作电机的方法。
    void operateMotorBasedOnDistance(float distance);
     void checkWeightAndOperateMotor(); // 声明一个检查重量并根据重量操作电机的方法*/
};

#endif // SMARTPET_H
