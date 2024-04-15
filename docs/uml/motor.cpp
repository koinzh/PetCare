#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <atomic>
#include <functional>
#include <chrono>
#include <thread>

/**
 * @class MotorController
 * @brief Controller for a stepper motor that supports basic directional commands.
 *
 * This class provides functionality to control a stepper motor with forward,
 * backward, and stop commands. It directly interacts with the hardware using GPIO
 * operations.
 */
class MotorController {
private:
    int pins[4]; ///< GPIO pin numbers for motor control.
    std::atomic<bool> rotatedForward; ///< Indicates whether the motor has rotated forward.
    std::atomic<bool> rotatedBackward; ///< Indicates whether the motor has rotated backward.

    /**
     * @brief Set the motor to a specific step in the motor sequence.
     * @param w1 First pin state.
     * @param w2 Second pin state.
     * @param w3 Third pin state.
     * @param w4 Fourth pin state.
     */
    void setStep(int w1, int w2, int w3, int w4);

    /**
     * @brief Perform stepping for a specific number of steps in a given direction.
     * @param totalSteps Number of steps to perform.
     * @param direction Direction to rotate (1 for forward, -1 for backward).
     */
    void step(int totalSteps, int direction);

public:
    /**
     * @brief Constructor for MotorController.
     * @param pin1 GPIO pin number connected to the first motor pin.
     * @param pin2 GPIO pin number connected to the second motor pin.
     * @param pin3 GPIO pin number connected to the third motor pin.
     * @param pin4 GPIO pin number connected to the fourth motor pin.
     */
    MotorController(int pin1, int pin2, int pin3, int pin4);

    /**
     * @brief Destructor for MotorController.
     */
    ~MotorController();

    /**
     * @brief Rotate the motor forward by a specific number of steps.
     * @param steps Number of steps to rotate forward.
     */
    void rotateForward(int steps);

    /**
     * @brief Rotate the motor backward by a specific number of steps.
     * @param steps Number of steps to rotate backward.
     */
    void rotateBackward(int steps);

    /**
     * @brief Stop the motor immediately.
     */
    void stop();

    /**
     * @brief Reset the direction flags of the motor to false.
     */
    void reset();

    /**
     * @brief Check if the motor has rotated forward.
     * @return True if the motor has rotated forward, otherwise false.
     */
    bool hasRotatedForward() const;

    /**
     * @brief Check if the motor has rotated backward.
     * @return True if the motor has rotated backward, otherwise false.
     */
    bool hasRotatedBackward() const;
};

#endif // MOTORCONTROLLER_H
