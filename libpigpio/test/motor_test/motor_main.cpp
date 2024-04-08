
#include "motor.h"
#include <pigpio.h>
#include <iostream>

int main() {
    if (gpioInitialise() < 0) {
        std::cout << "Setup pigpio failed" << std::endl;
        return 1;
    }

    // Replace the pin numbers with the actual GPIO pins you are using
    Motor motor(17, 18, 27, 22);

    // The interval and steps are just examples, replace them with the desired values
    int interval = 2; // Interval in milliseconds
    int steps = 400;  // Number of steps to move

    while (1) {
        std::cout << "Forward" << std::endl;
        motor.forward(interval, steps);

        // Here, we wait until the motor completes the forward movement
        // This can be implemented using a condition variable, or in this simple example, just a sleep
        gpioDelay(steps * interval * 1000); // Convert interval to microseconds for gpioDelay

        std::cout << "Stop" << std::endl;
        motor.stop();

        // Delay to see the stop effect
        gpioDelay(2000000); // 2 seconds delay

        std::cout << "Rollback" << std::endl;
        motor.rollback(interval, steps);

        // Wait until the motor completes the rollback movement
        gpioDelay(steps * interval * 1000); // Convert interval to microseconds for gpioDelay

        std::cout << "Stop" << std::endl;
        motor.stop();

        // Delay between each loop iteration
        gpioDelay(2000000); // 2 seconds delay
    }

    gpioTerminate(); // Cleanup and terminate library
    return 0;
}

