#ifndef WATER_LEVEL_CONTROLLER_H
#define WATER_LEVEL_CONTROLLER_H

#include <chrono>
#include <pigpio.h>
#include <iostream>

class WaterLevelController {
public:

 static WaterLevelController* instance;  

    WaterLevelController(int waterSensorPin, int motorPin);
    ~WaterLevelController();

    void checkWaterLevel(int gpio, int level, uint32_t tick);

private:
    int waterSensorPin;
    int motorPin;
    bool motorRunning;
    std::chrono::steady_clock::time_point motorStartTime;

    void initialize();
    void startMotor();
    void stopMotor();
};

#endif // WATER_LEVEL_CONTROLLER_H
