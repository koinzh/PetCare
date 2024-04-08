#ifndef SMARTPET_MOTOR_H
#define SMARTPET_MOTOR_H

class Motor {
public:
    Motor(int in1, int in2, int in3, int in4); // 构造函数
    ~Motor(); // Destructor
    void initialize(); // Explicit initialization method
    void setStep(int step); 
    void forward(int t, int steps);
    void stop();
    void rollback(int t, int steps);
    void nextStep(); 

private:
    int IN1; // 存储引脚配置
    int IN2;
    int IN3;
    int IN4;
    int currentStep; // 当前步骤
    int totalSteps; // 总步骤
    int stepCount; // 步骤计数
    int direction; // 方向
};

#endif // SMARTPET_MOTOR_H

