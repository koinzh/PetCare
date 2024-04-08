#ifndef SMARTPET_SONIC_H
#define SMARTPET_SONIC_H

#include <pigpio.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigger, int echo);
    ~UltrasonicSensor();
    void initialize();
    float measureDistance();
    void sendTriggerPulse();
    void echoResponse(int gpio, int level, uint32_t tick);

private:
    int trig;
    int echo;
    float distance;
    uint32_t startTime, endTime;
};

#endif //SMARTPET_SONIC_H
