#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;

int main() {
    // 初始化WiringPi库
    wiringPiSetup();
    
    // 设置GPIO引脚为输出模式
    // 注意: 这里使用的是WiringPi的引脚编号
    int pin = 21;
 
    pinMode(pin, OUTPUT);
   
    
    
    cout << "enter" << endl;
    cin.ignore(); // 等待用户按下回车键
   
    digitalWrite(pin, HIGH);//low opearte high stop
    
    sleep(5);
    cout << "GPIO high" << endl;
    digitalWrite(pin, LOW);
    return 0;
}
