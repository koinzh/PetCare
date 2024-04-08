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
    gpioSetAlertFuncEx(echo, echoCallback, this);
}

UltrasonicSensor::~UltrasonicSensor() {
    // Clean up if needed
}

void UltrasonicSensor::initialize() {
    // Additional initialization if necessary
}

void UltrasonicSensor::sendTriggerPulse() {
    gpioWrite(trig, 1);
    gpioDelay(10); // Delay for 10 microseconds
    gpioWrite(trig, 0);
}

void UltrasonicSensor::echoResponse(int gpio, int level, uint32_t tick) {
    if (level == 1) {
        startTime = tick;
    } else if (level == 0) {
        endTime = tick;
        distance = (endTime - startTime) / 58.0;
    }
}

float UltrasonicSensor::measureDistance() {
    return distance;
}
