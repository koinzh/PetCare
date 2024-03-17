#ifndef SMARTPET_WEIGHT_H
#define SMARTPET_WEIGHT_H

#include <wiringPi.h>

class WeightSensor {
public:
    struct Hx711Args {
        int SCK;
        int SDA;
        int EN;
        int calibration;
        float coefficient; // 标定系数
        int weight;
        unsigned long value;

        
    };

    static void setPin(Hx711Args *value);
    static void initPin(Hx711Args *value);
    static void start(Hx711Args *value);
    static int setup(Hx711Args *value);
    static void loop(Hx711Args *value);
};

#endif // SMARTPET_WEIGHT_H
