#include "sonic.h"
#include <wiringPi.h>
#include <sys/time.h>
// #include <cstddef> // Not needed if using nullptr instead of NULL

UltrasonicSensor::UltrasonicSensor(int trig, int echo) : trig(trig), echo(echo) {
    wiringPiSetup();
}

void UltrasonicSensor::initialize() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

long UltrasonicSensor::timeMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, nullptr); // Using nullptr
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

float UltrasonicSensor::measureDistance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    while(digitalRead(echo) == LOW);
    long startTime = timeMicroseconds();
    while(digitalRead(echo) == HIGH);
    long travelTime = timeMicroseconds() - startTime;

    // Speed of sound in air (in cm/microsecond)
    float speedOfSound = 340.0 / 10000;
    return (travelTime * speedOfSound) / 2;
}
