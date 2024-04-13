#ifndef WATER_LEVEL_CONTROLLER_H
#define WATER_LEVEL_CONTROLLER_H

#include <chrono>
#include <pigpio.h>

class WaterLevelController {
public:
    WaterLevelController(int waterSensorPin, int motorPin);
    ~WaterLevelController();

    void checkWaterLevel();

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
