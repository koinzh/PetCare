#ifndef WATERLEVELCONTROLLER_H
#define WATERLEVELCONTROLLER_H

#include <iostream>
#include <chrono>
#include "pigpio.h"

/**
 * @class WaterLevelController
 * @brief Controller for managing water levels using a sensor and motor.
 *
 * This singleton class controls the operation of a motor based on the readings from a water level sensor.
 * It ensures that the motor is activated when the water level is below a certain threshold and
 * stops the motor once the water level is adequate.
 */
class WaterLevelController {
private:
    static WaterLevelController* instance; ///< Singleton instance of the controller.
    int waterSensorPin; ///< GPIO pin number for the water level sensor.
    int motorPin; ///< GPIO pin number for the motor control.
    bool motorRunning; ///< Flag to check if the motor is currently running.
    std::chrono::steady_clock::time_point motorStartTime; ///< Time when the motor was last started.

    /**
     * @brief Private constructor to enforce singleton pattern.
     * @param waterSensorPin GPIO pin number for the water level sensor.
     * @param motorPin GPIO pin number for the motor control.
     */
    WaterLevelController(int waterSensorPin, int motorPin);

    /**
     * @brief Initialize the GPIO settings and the callback function for the water level sensor.
     */
    void initialize();

public:
    /**
     * @brief Destructor for WaterLevelController.
     */
    ~WaterLevelController();

    /**
     * @brief Retrieves the singleton instance of the WaterLevelController.
     * @return Pointer to the singleton instance.
     */
    static WaterLevelController* getInstance() {
        if (!instance) {
            // Ideally, parameters should be dynamically determined, not hard-coded.
            instance = new WaterLevelController(21, 20);
        }
        return instance;
    }

    /**
     * @brief Function called by the GPIO library when the water level changes.
     * @param gpio GPIO pin number that triggered the alert.
     * @param level New level of the GPIO pin (high or low).
     * @param tick Time at which the change occurred.
     */
    void checkWaterLevel(int gpio, int level, uint32_t tick);

    /**
     * @brief Starts the motor if it is not already running.
     */
    void startMotor();

    /**
     * @brief Stops the motor if it is running.
     */
    void stopMotor();
};

#endif // WATERLEVELCONTROLLER_H
