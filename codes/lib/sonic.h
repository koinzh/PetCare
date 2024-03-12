#ifndef SMARTPET_SONIC_H
#define SMARTPET_SONIC_H

#include <functional>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigger, int echo);
    void measureDistanceAsync(const std::function<void(float)>& callback);

private:
    int trig;
    int echo;
    long timeMicroseconds();
};

#endif // SMARTPET_SONIC_H
