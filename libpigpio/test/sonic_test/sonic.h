#ifndef SMARTPET_SONIC_TEST
#define SMARTPET_SONIC_TEST


#include <wiringPi.h>
#include <cstddef>
#include <sys/time.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigger, int echo);
    void initialize();
    float measureDistance();

private:
    int trig;
    int echo;
    long timeMicroseconds();
};

#endif //SMARTPET_SONIC_TEST

