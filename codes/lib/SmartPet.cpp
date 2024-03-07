#include "SmartPet.h"
#include <iostream>
#include <unistd.h> 

SmartPet::SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4) 
: sensor(trigPin, echoPin), motor(in1, in2, in3, in4), motorRunning(false) {
    sensor.initialize();
}

void SmartPet::run() {
    std::cout << "SmartPet operational." << std::endl;
    while (true) {
        operateMotorBasedOnDistance();
        sleep(1); // Reduce output frequency
    }
}

void SmartPet::operateMotorBasedOnDistance() {
    float distance = sensor.measureDistance();
    std::cout << "Distance: " << distance << " cm" << std::endl;

    if (distance < 10 && !motorRunning) {
        std::cout << "Object detected within 10cm. Operating motor..." << std::endl;
        motor.forward(2, 100); // randonm
        motorRunning = true;
    } else if (distance >= 10 && motorRunning) {
        std::cout << "Object no longer within 10cm. Stopping motor..." << std::endl;
        motor.stop();
        motorRunning = false;
    } else if (motorRunning) {
        std::cout << "Motor continues running..." << std::endl;
    }
}
