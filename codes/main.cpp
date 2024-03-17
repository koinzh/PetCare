#include "SmartPet.h"
#include <wiringPi.h>

int main() {
    wiringPiSetup(); // 初始化wiringPi并设置GPIO引脚
    int trigPin = 28; 
    int echoPin = 29;
    int in1 = 0;
    int in2 = 1;
    int in3 = 2;
    int in4 = 3;
    int SCK = 4;
    int SDA = 5;


    SmartPet pet(trigPin, echoPin, in1, in2, in3, in4, SCK, SDA);
    pet.run();

    return 0;
}
