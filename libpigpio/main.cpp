#include "SmartPet.h"
#include <pigpio.h>
#include <iostream>

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed." << std::endl;
        return 1; // Return an error code if pigpio fails to initialize
    }

    // Specify sensor and motor pin numbers
    int trigPin = 28;
    int echoPin = 29;
    int in1 = 0;
    int in2 = 1;
    int in3 = 2;
    int in4 = 3;

    SmartPet pet(trigPin, echoPin, in1, in2, in3, in4);
    pet.run();

    gpioTerminate(); // Properly terminate pigpio before exiting the program
    return 0;
}
