#include "water.h"
#include <iostream>
#include <chrono>
#include <pigpio.h>

int main() {
    WaterLevelController controller(6, 5);
    while (true) {
        controller.checkWaterLevel();
        gpioDelay(1000000); // 真正的每秒延迟
    }
    return 0;
}
