#ifndef SMARTPET_MOTOR_H
#define SMARTPET_MOTOR_H

class Motor {
public:

enum State {STOPPED, FORWARD, BACKWARD}; // 定义电机的状态

    Motor(int in1, int in2, int in3, int in4); // 构造函数
    void initialize();
    void setStep(int a, int b, int c, int d);
    void forward(int t, int steps);
    void stop();
    void rollback(int t, int steps);
    void printState(); // 打印当前状态的方法


private:
    int IN1; // 存储引脚配置
    int IN2;
    int IN3;
    int IN4;
    State state = STOPPED;
};

#endif // SMARTPET_MOTOR_H
