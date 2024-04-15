#include "sonic.h"
#include "motor.h"
#include "weight.h"
#include "water.h"
#include "pigpio.h"
#include <iostream>
#include <csignal>
#include <atomic>
#include <mutex>
#include <thread>

/**
 * @file main.cpp
 * @brief Main control program for an integrated sensor and actuator system.
 *
 * This program integrates motor, ultrasonic sensor, weight sensor, and water level control to perform automated tasks based on sensor inputs. It utilizes multithreading and signal handling for robust operation.
 */

std::atomic<bool> terminateProgram{false}; ///< Global flag to terminate the program.
std::mutex mtx;  ///< Mutex for protecting shared variables.

/**
 * @brief Signal handler to set termination flag.
 * @param signum Signal number.
 */
void signalHandler(int signum) {
    terminateProgram = true;
}

/**
 * @brief Entry point for the main application.
 * @return Execution status code.
 */
int main() {
    float thresholdDistance; // Threshold for distance measurements.
    int weightThreshold; // Threshold for weight measurements.

    // Get user input for thresholds.
    std::cout << "Enter distance threshold (cm, <500): ";
    std::cin >> thresholdDistance;
    std::cout << "Enter weight threshold (g): ";
    std::cin >> weightThreshold;

    if (gpioInitialise() < 0) {
        std::cerr << "GPIO initialization failed." << std::endl;
        return 1;
    }

    // Setup signal handling for graceful shutdown.
    signal(SIGINT, signalHandler);

    // Initialize system components.
    MotorController motor(17, 18, 27, 22);
    UltrasonicSensor sensor(20, 21);
    WaterLevelController* waterLevelController = WaterLevelController::getInstance();
    WeightSensor* weightSensor = WeightSensor::getInstance();

    int countBelowThreshold = 0;
    const int thresholdCount = 3; // Number of consecutive readings below threshold before action.
    const float minValidDistance = 0.1;  // Minimum valid distance to consider.

    weightSensor->start();  // Start weight monitoring.

    // Start a thread to monitor water levels.
    std::thread waterThread([&]() {
        while (!terminateProgram.load()) {
            // Water level monitoring logic can be added here.
        }
    });

    // Set distance callback to handle sensor readings.
    sensor.setDistanceCallback([&](float distance) {
        std::lock_guard<std::mutex> lock(mtx);  // Protect shared data with a mutex.
        std::cout << "Distance: " << distance << " cm, Weight: " << weightSensor->getLatestWeight() << " g" << std::endl;

        if (distance < minValidDistance || distance > 500) {  // Ignore invalid readings.
            return;
        }

        int currentWeight = weightSensor->getLatestWeight();
        if (distance < thresholdDistance && currentWeight < weightThreshold) {
            countBelowThreshold++;
            if (countBelowThreshold >= thresholdCount && !motor.hasRotatedForward()) {
                std::cout << "Triggering Forward rotation." << std::endl;
                motor.rotateForward(128);  // Rotate forward approximately 90 degrees.
            }
        } else {
            countBelowThreshold = 0; // Reset counter.
        }

        // Trigger reverse rotation if conditions are met.
        if (currentWeight >= weightThreshold && motor.hasRotatedForward()) {
            std::cout << "Triggering Reverse rotation." << std::endl;
            motor.rotateBackward(128);  // Reverse approximately 90 degrees.
            motor.reset();  // Reset motor state after rotation.
        }
    });

    // Start distance measurements.
    sensor.startMeasurement();

    // Main loop continues until termination flag is set.
    while (!terminateProgram) {
        // Main loop content.
    }

    // Clean up.
    waterThread.join();
    weightSensor->stop();
    sensor.stop();
    gpioTerminate();
    std::cout << "Program terminated gracefully." << std::endl;
    return 0;
}
