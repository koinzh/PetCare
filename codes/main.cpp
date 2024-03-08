#include "SmartPet.h"
#include <wiringPi.h>

int main() {
    wiringPiSetup(); // 程序开始时调用一次

    // 指定传感器和电机的引脚编号
    int trigPin = 28;
    int echoPin = 29;
    int in1 = 0;
    int in2 = 1;
    int in3 = 2;
    int in4 = 3;

    SmartPet pet(trigPin, echoPin, in1, in2, in3, in4);
    pet.run();

    return 0;
}
