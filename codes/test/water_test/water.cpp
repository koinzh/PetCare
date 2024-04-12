#include <iostream>
#include <wiringPi.h>

using namespace std;

int main() {
    // 初始化WiringPi库
    wiringPiSetup();
    
    // 设置GPIO引脚为输出模式
    // 注意: 这里使用的是WiringPi的引脚编号
    int pin = 21;
 
    pinMode(pina, OUTPUT);
   
    
    
    cout << "enter" << endl;
    cin.ignore(); // 等待用户按下回车键
   
    digitalWrite(pin, LOW);//low opearte high stop
    
    
    cout << "GPIO high" << endl;

    return 0;
}
