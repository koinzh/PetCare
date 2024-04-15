#include "water.h"
#include <iostream>

WaterLevelController::WaterLevelController(int waterSensorPin, int motorPin)
    : waterSensorPin(waterSensorPin), motorPin(motorPin), motorRunning(false) {
    initialize();
}

WaterLevelController::~WaterLevelController() {
    gpioTerminate();
}

void WaterLevelController::checkWaterLevel() {
    if (gpioRead(waterSensorPin) == PI_HIGH) {
        startMotor();
    } else {
        stopMotor();
    }
    if (motorRunning && std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - motorStartTime).count() >= 2) {
        stopMotor();
    }
}

void WaterLevelController::initialize() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed." << std::endl;
        exit(1);
    }
    gpioSetMode(waterSensorPin, PI_INPUT);
    gpioSetMode(motorPin, PI_OUTPUT);
    gpioWrite(motorPin, PI_LOW);
}

void WaterLevelController::startMotor() {
    if (!motorRunning) {
        std::cout << "No water, activating motor..." << std::endl;
        gpioWrite(motorPin, PI_HIGH);
        motorStartTime = std::chrono::steady_clock::now();
        motorRunning = true;
    }
}

void WaterLevelController::stopMotor() {
    if (motorRunning) {
        gpioWrite(motorPin, PI_LOW);
        std::cout << "Motor stopped." << std::endl;
        motorRunning = false;
    }
}
/*
int main() {
    WaterLevelController controller(6, 5);
    while (true) {
        controller.checkWaterLevel();
        gpioDelay(1000000); // 真正的每秒延迟
    }
    return 0;
}
*/
