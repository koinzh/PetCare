#include "UltrasonicSensor.h"
#include <iostream>
#include <signal.h>
#include <atomic>
#include <csignal>

std::atomic<bool> terminateProgram{false};

void signalHandler(int signum) {
    terminateProgram = true;
}

int main() {
    gpioInitialise();
    signal(SIGINT, signalHandler);

    UltrasonicSensor sensor(20, 21);
    sensor.setDistanceCallback([](float distance) {
        std::cout << "Distance: " << distance << " cm" << std::endl;
    });

    sensor.startMeasurement();

    // 用于持续检查终止信号的循环
    while (!terminateProgram) {
        // 主线程在此空转，无sleep调用
    }

    sensor.stop();
    gpioTerminate();

    std::cout << "Program terminated gracefully." << std::endl;
    return 0;
}
