#include "weight.h"
#include <wiringPi.h>
#include <stdio.h>
#include <cmath>

void WeightSensor::setPin(Hx711Args *value) {
    value->EN = 1;
    value->coefficient = 1010.27f; // 使用浮点数，这是根据称重校准得到的数据
}

void WeightSensor::initPin(Hx711Args *value) {
    pinMode(value->SCK, OUTPUT);
    pinMode(value->SDA, INPUT);
    pullUpDnControl(value->SDA, PUD_UP);
}

void WeightSensor::start(Hx711Args *value) {
    int i;
    digitalWrite(value->SCK, LOW);
    while (digitalRead(value->SCK));
    value->value = 0;
    while (digitalRead(value->SDA));
    delay(100);

    for (i = 0; i < 24; i++) {
        digitalWrite(value->SCK, HIGH);
        delayMicroseconds(1);
        value->value = value->value * 2;

        digitalWrite(value->SCK, LOW);
        delayMicroseconds(1);

        if (digitalRead(value->SDA))
            value->value = value->value + 1;
    }
    digitalWrite(value->SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(value->SCK, LOW);

    float rawWeight = (float)(value->value - value->calibration + 50) / value->coefficient;
    i = (int)round((rawWeight - 289) * 2); // 手动计算
    if (i < 5000) value->weight = i;
    printf("Weight: %d g\n", value->weight);
}

int WeightSensor::setup(Hx711Args *value) {
    if (wiringPiSetup() == -1) return 1;
    setPin(value);
    initPin(value);
    return 0;
}

void WeightSensor::loop(Hx711Args *value) {
    while(1)
        WeightSensor::start(value);
}
