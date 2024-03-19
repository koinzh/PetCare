#include <iostream>
#include <wiringPi.h>

using namespace std;

int main() {
    // 初始化WiringPi库
    wiringPiSetup();
    
    // 设置GPIO引脚为输出模式
    // 注意: 这里使用的是WiringPi的引脚编号
    int pina = 24;
    int pinb=25; 
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    
    
    cout << "enter" << endl;
    cin.ignore(); // 等待用户按下回车键
    
  
    digitalWrite(pina, HIGH);
    digitalWrite(pinb, LOW);
    
    cout << "GPIO high" << endl;

    return 0;
}
