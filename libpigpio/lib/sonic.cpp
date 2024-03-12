#include "sonic.h"
#include <pigpio.h>
#include <iostream>

// Callback function to handle echo pin changes
void echoCallback(int gpio, int level, uint32_t tick, void *user) {
    UltrasonicSensor* sensor = reinterpret_cast<UltrasonicSensor*>(user);
    sensor->echoResponse(gpio, level, tick);
}

UltrasonicSensor::UltrasonicSensor(int trigger, int echo) : trig(trigger), echo(echo), distance(0.0), startTime(0), endTime(0) {
    gpioSetMode(trig, PI_OUTPUT);
    gpioSetMode(echo, PI_INPUT);
    gpioWrite(trig, PI_LOW); // Ensure trigger is low
    // Register callback for echo pin
    gpioSetAlertFuncEx(echo, echoCallback, this);
}

void UltrasonicSensor::initialize() {
    // Initialization code if necessary, already handled in constructor
}

void UltrasonicSensor::triggerPulse() {
    gpioWrite(trig, PI_LOW);
    gpioDelay(2); // Settle time
    gpioWrite(trig, PI_HIGH);
    gpioDelay(10); // Pulse length
    gpioWrite(trig, PI_LOW);
}

void UltrasonicSensor::echoResponse(int gpio, int level, uint32_t tick) {
    if(level == 1) { // Echo pulse starts
        startTime = tick;
    } else if(level == 0) { // Echo pulse ends
        endTime = tick;
        uint32_t duration = endTime - startTime;
        distance = duration * 0.0343 / 2.0; // Calculate distance in cm
        std::cout << "Distance: " << distance << " cm" << std::endl;
    }
}

float UltrasonicSensor::measureDistance() {
    triggerPulse();
    return distance; // Return the most recently measured distance
}


/*
In this update, echoCallback is a static callback function that pigpio calls whenever the echo pin changes state. This callback then calls UltrasonicSensor::echoResponse, a member function to process the echo signal, measuring the time between the signal's high and low transitions to calculate the distance.

The measureDistance method now primarily triggers a pulse, and the actual distance measurement is asynchronously handled by the callback. The distance value is stored in a member variable, distance, which measureDistance returns. Note that due to this asynchronous nature, measureDistance might initially return 0 or a stale value until the echo callback updates distance.
*/