#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <condition_variable>

/**
 * @class UltrasonicSensor
 * @brief Class for handling ultrasonic distance measurement using an ultrasonic sensor.
 * 
 * This class provides functionality to measure distance using an ultrasonic sensor
 * by triggering pulses and listening for an echo response.
 */
class UltrasonicSensor {
private:
    int trigPin; ///< GPIO pin used to trigger the ultrasonic pulse.
    int echoPin; ///< GPIO pin used to receive the echo signal.
    std::atomic<bool> running; ///< Flag to control the measurement thread.
    std::thread measurementThread; ///< Thread for handling the measurement loop.
    std::function<void(float)> distanceCallback; ///< Callback function to handle the distance measured.
    std::mutex mtx; ///< Mutex for synchronizing access to shared resources.
    std::condition_variable cv; ///< Condition variable for managing echo response waiting.
    uint32_t startTime; ///< Start time of the echo pulse.
    uint32_t endTime; ///< End time of the echo pulse.

    /**
     * @brief Trigger a short ultrasonic pulse.
     * 
     * This function sends a 10-microsecond pulse on the trigger pin.
     */
    void triggerPulse();

    /**
     * @brief Wait for the echo response and calculate distance.
     * 
     * This function waits for the echo response up to 100 milliseconds and calculates
     * the distance based on the time between the sent pulse and the received echo.
     */
    void waitForEcho();

    /**
     * @brief Handle interrupt generated by echo response.
     * @param gpio GPIO pin number that generated the interrupt.
     * @param level The level of the GPIO pin.
     * @param tick The system tick at which the change occurred.
     * @param user User-defined data (pointer to UltrasonicSensor instance).
     */
    static void echoInterrupt(int gpio, int level, uint32_t tick, void* user);

public:
    /**
     * @brief Constructor for UltrasonicSensor.
     * @param triggerPin GPIO pin number used to trigger the sensor.
     * @param echoPin GPIO pin number used to receive the echo from the sensor.
     */
    UltrasonicSensor(int triggerPin, int echoPin);

    /**
     * @brief Destructor for UltrasonicSensor.
     */
    ~UltrasonicSensor();

    /**
     * @brief Start the distance measurement process.
     * 
     * Starts a new thread that continuously measures distance until stopped.
     */
    void startMeasurement();

    /**
     * @brief Stop the distance measurement process.
     * 
     * Stops the measurement thread and cleans up resources.
     */
    void stop();

    /**
     * @brief Set the callback function to be called when distance is measured.
     * @param callback The function to call with the measured distance.
     */
    void setDistanceCallback(std::function<void(float)> callback);
};

#endif // ULTRASONICSENSOR_H