#include "MotorController.h"
#include "pigpio.h"
#include <iostream>

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "GPIO faield" << std::endl;
        return 1;
    }

    MotorController motor(17, 18, 27, 22);  // 使用正确的GPIO引脚初始化

    // 执行正转90度
    std::cout << "Motor+++90" << std::endl;
    
    motor.rotateForward(256);  // 正转512步约等于180度

    // 执行反转90度
    std::cout << "Motor---90" << std::endl;
    motor.rotateBackward(256);  // 反转512步约等于180度

    gpioTerminate();
    return 0;
}
