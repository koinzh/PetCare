#include "sonic.h"
#include <wiringPi.h>
#include <sys/time.h>
#include <thread>
#include <chrono>

UltrasonicSensor::UltrasonicSensor(int trigger, int echo) : trig(trigger), echo(echo) {
    wiringPiSetup(); 
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}



long UltrasonicSensor::timeMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, nullptr); 
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void UltrasonicSensor::measureDistanceAsync(const std::function<void(float)>& callback) {
    std::thread([this, callback]() {
        while (true) { // 持续测量距离
            digitalWrite(trig, LOW);
            std::this_thread::sleep_for(std::chrono::microseconds(2));
            digitalWrite(trig, HIGH);
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            digitalWrite(trig, LOW);

            while (digitalRead(echo) == LOW);
            long startTime = timeMicroseconds();
            while (digitalRead(echo) == HIGH);
            long travelTime = timeMicroseconds() - startTime;

            float speedOfSound = 340.29 / 10000; 
            float distance = (travelTime * speedOfSound) / 2;

            if (callback) {
                callback(distance);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 在连续测量之间稍作延时
        }
    }).detach(); // 在后台线程中运行，不阻塞主线程
}
