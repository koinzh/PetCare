#ifndef SMARTPET_SONIC_H
#define SMARTPET_SONIC_H

#include <pigpio.h> // Include pigpio to use its functions

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigger, int echo);
    ~UltrasonicSensor(); // Destructor to clean up, if needed
    void initialize();
    float measureDistance();

private:
    int trig;
    int echo;
    //long timeMicroseconds();
};

#endif //SMARTPET_SONIC_H
