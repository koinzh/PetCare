#include "sonic.h"
#include "motor.h"
#include "weight.h"
#include "water.h"
#include "pigpio.h"
#include "IOTConnect.h"
#include <iostream>
#include <csignal>
#include <atomic>
#include <mutex>
#include <chrono>

std::atomic<bool> terminateProgram{false};
std::mutex mtx;  // Mutexes are used to protect shared variables

std::chrono::time_point<std::chrono::steady_clock> lastReverseTime;
std::chrono::time_point<std::chrono::steady_clock> lastReverseTime2;
const std::chrono::seconds reverseCooldown(30);  // cool for 30s
const std::chrono::seconds reverseCooldown2(2);
void signalHandler(int signum) {
    terminateProgram = true;
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "GPIO initialization failed。" << std::endl;
        return 1;
    }

    signal(SIGINT, signalHandler);   // gpio initialization
    MotorController motor(17, 18, 27, 22);//set motor GPIO
    UltrasonicSensor sensor(20, 21);//set sonic GPIO
    WaterLevelController waterLevelController(6, 5);//set water GPIO
    WeightSensor weightSensor(23, 24, -151774, 442.54f); //set weight GPIO
    IOTConnect iotconnect;

    int countBelowThreshold = 0;
    const int thresholdCount = 3; //detect three times distance < thresholdDistance and weight < weightThreshold
    const float thresholdDistance = 10.0;  
    const float minValidDistance = 0.1;  
    int weightThreshold = iotconnect.weight1;

    weightSensor.start();  
    std::thread waterThread([&](){while (!terminateProgram.load()) {}});//water 
    int weight1;

    sensor.setDistanceCallback([&](float distance) {
        std::lock_guard<std::mutex> lock(mtx);  // protect shared variables
        auto now = std::chrono::steady_clock::now();  
        auto now2 = std::chrono::steady_clock::now();  
        weight1 = weightSensor.getLatestWeight();
        if(now2 > lastReverseTime2 + reverseCooldown2 ){
            weightThreshold = iotconnect.weight1;
            std::cout << "Distance: " << distance << " cm, Weight: " << weight1 << " g, weightthreshold:" << weightThreshold << "g"<<std::endl;
            iotconnect.reportDistance(distance,weight1);
           
         
            lastReverseTime2 = std::chrono::steady_clock::now(); 
            }
      
        if (distance < minValidDistance || distance > 500) {  // ignore meanless data
            return;
        }

        int currentWeight = weightSensor.getLatestWeight();
        if (distance < thresholdDistance && currentWeight < weightThreshold && now > lastReverseTime + reverseCooldown) {
            countBelowThreshold++;
            if (countBelowThreshold >= thresholdCount && !motor.hasRotatedForward()) {
                std::cout << "Triggering Forward rotation." << std::endl;
                std::cout << "currentWeight"<< currentWeight<< std::endl;
                std::cout << "Weighthold:"<< weightThreshold << std::endl;
                motor.rotateForward(128);  // ++128==motor 90 angle 
            }
        } else {
            countBelowThreshold = 0; // reset this: detect three times distance < thresholdDistance and weight < weightThreshold
        }

        // if weight> weightThreshold and motor has been Forwarded
        if (currentWeight >= weightThreshold && motor.hasRotatedForward()) {
            std::cout << "Triggering Reverse rotation." << std::endl;
            std::cout << "currentWeight"<< currentWeight<< std::endl;
            std::cout << "Weighthold:"<< weightThreshold << std::endl;
            motor.rotateBackward(128);  //  --128==motor 90 angle
            motor.reset();  // reset motor and allowed motor Forward again
            lastReverseTime = std::chrono::steady_clock::now();  
        }
    });

    sensor.startMeasurement();

    while (!terminateProgram) {
        
    }

    waterThread.join();
    weightSensor.stop();
    sensor.stop();
    gpioTerminate();
    std::cout << "PROGRAM STOPED" << std::endl;
    return 0;
}
