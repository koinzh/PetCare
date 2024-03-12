#ifndef SMARTPET_MOTOR_H
#define SMARTPET_MOTOR_H

class Motor {
public:
    Motor(int in1, int in2, int in3, int in4); // 构造函数
    ~Motor();// Destructor to ensure gpioTerminate is called
    void initialize();// Explicit initialization method
    void setStep(int a, int b, int c, int d);
    void forward(int t, int steps);
    void stop();
    void rollback(int t, int steps);

private:
    int IN1; // 存储引脚配置
    int IN2;
    int IN3;
    int IN4;
};

#endif // SMARTPET_MOTOR_H
