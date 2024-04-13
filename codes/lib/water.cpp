#include "water.h"


WaterLevelController* WaterLevelController::instance = nullptr;

WaterLevelController::WaterLevelController(int waterSensorPin, int motorPin)
    : waterSensorPin(waterSensorPin), motorPin(motorPin), motorRunning(false) {
    initialize();
    
    instance = this;  // 在构造函数中设置实例指针

    
}

WaterLevelController::~WaterLevelController() {
    gpioTerminate();
    
     instance = nullptr;  // 在析构函数中清除实例指针
     
}

void WaterLevelController::checkWaterLevel(int gpio, int level, uint32_t tick) {
    if (level == PI_HIGH) {
        startMotor();
    } else if (motorRunning && std::chrono::duration_cast<std::chrono::seconds>(
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
    gpioSetAlertFunc(waterSensorPin, [](int gpio, int level, uint32_t tick) {
        WaterLevelController::instance->checkWaterLevel(gpio, level, tick);
    });
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
