#ifndef WEIGHTSENSOR_H
#define WEIGHTSENSOR_H

#include <atomic>
#include <iostream>
#include "pigpio.h"

/**
 * @class WeightSensor
 * @brief Class to handle weight measurements using a digital scale sensor.
 *
 * This singleton class provides an interface for reading weight measurements from a digital scale.
 * It initializes the necessary GPIO pins for communication with the sensor and provides methods to start
 * and stop the measurement process, as well as to read the weight values.
 */
class WeightSensor {
private:
    static WeightSensor* instance; ///< Singleton instance of the WeightSensor.
    int SCK; ///< Clock pin for the sensor.
    int SDA; ///< Data pin for the sensor.
    int calibration; ///< Calibration offset for the sensor.
    float coefficient; ///< Calibration coefficient for the sensor.
    std::atomic<bool> running; ///< Flag indicating if the sensor is actively measuring.
    std::atomic<int> latestWeight; ///< Stores the latest weight measurement.

    /**
     * @brief Private constructor to enforce singleton pattern.
     * @param SCK Clock pin for the sensor.
     * @param SDA Data pin for the sensor.
     * @param calibration Calibration offset for the sensor.
     * @param coefficient Calibration coefficient for the sensor.
     */
    WeightSensor(int SCK, int SDA, int calibration, float coefficient);

    /**
     * @brief Read raw weight data from the sensor.
     * @return The raw weight as an integer.
     */
    int readRawWeight();

    /**
     * @brief Calculate and update the latest weight based on raw sensor data.
     */
    void triggerRead();

public:
    /**
     * @brief Destructor for WeightSensor.
     */
    ~WeightSensor();

    /**
     * @brief Retrieves the singleton instance of the WeightSensor.
     * @return Pointer to the singleton instance.
     */
    static WeightSensor* getInstance() {
        if (!instance) {
            // Parameters would ideally be set more flexibly rather than hardcoded
            instance = new WeightSensor(5, 6, 1000, 0.5);
        }
        return instance;
    }

    /**
     * @brief Start the weight measurement process.
     */
    void start();

    /**
     * @brief Stop the weight measurement process.
     */
    void stop();

    /**
     * @brief Get the latest measured weight.
     * @return The latest weight in units after calibration and adjustment.
     */
    int getLatestWeight() const;

    /**
     * @brief Read and calculate the current weight from the sensor.
     * @return The calculated weight.
     */
    int readWeight();
};

#endif // WEIGHTSENSOR_H
