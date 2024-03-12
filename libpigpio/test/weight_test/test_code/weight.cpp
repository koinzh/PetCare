#include "weight.h"
#include <stdio.h>
#include <cmath> 

#define SCK 4
#define SDA 5

void weight::set_pin(struct hx711_args *value) {
    value->EN = 1;
    value->coefficient = 1010.27f; // use float //data 1010.27 from weight_calibration
}

void weight::init_pin() {
    pinMode(SCK, OUTPUT);
    pinMode(SDA, INPUT);
    pullUpDnControl(SDA, PUD_UP);
}


void weight::start(struct hx711_args *value) {
    int i;
    digitalWrite(SCK, LOW);
    while (digitalRead(SCK));
    value->value = 0;
    while (digitalRead(SDA));
    delay(100);

    for (i = 0; i < 24; i++) {
        digitalWrite(SCK, HIGH);
        delayMicroseconds(1); 
        value->value = value->value * 2;
        
        digitalWrite(SCK, LOW);
        delayMicroseconds(1); 
        
        if (digitalRead(SDA))
            value->value = value->value + 1;
    }
    digitalWrite(SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCK, LOW);

    if ((value->EN == 1) && (value->value < 25000)) {
        value->EN = 0;
        value->calibration = value->value;
    } else {
      
        float raw_weight = (float)(value->value - value->calibration + 50) / value->coefficient;
        i = (int)round((raw_weight - 289) * 2); //manual
    }
    if (i < 5000) value->weight = i;
    printf("Weight: %d g\n", value->weight);
}

/*void weight::start(struct hx711_args *value) {
    int i;
    digitalWrite(SCK, LOW);
    while (digitalRead(SCK));
    value->value = 0;
    while (digitalRead(SDA));
    delay(100);

    for (i = 0; i < 24; i++) {
        digitalWrite(SCK, HIGH);
        delayMicroseconds(1); 
        value->value = value->value * 2;
        
        
        digitalWrite(SCK, LOW);
       delayMicroseconds(1); 
        
        if (digitalRead(SDA))
            value->value = value->value + 1;
    }
    digitalWrite(SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCK, LOW);

    if ((value->EN == 1) && (value->value < 25000)) {
        value->EN = 0;
        value->calibration = value->value;
    } else {
        float weight_float = (float)(value->value - value->calibration + 50) / value->coefficient;
        i = ((int)round(weight_float)-289)*2; // 4- 5+   manual caculate: hardware have some flaws
    }
    if (i < 5000) value->weight = i;
    printf("Weight: %d g\n", value->weight);
}
*/


int weight::setup(struct hx711_args *value) {
    if (wiringPiSetup() == -1) return 1;
    set_pin(value);
    init_pin();
    return 0;
}

void weight::loop(struct hx711_args *value) {
    while(1)
        weight::start(value);
}
