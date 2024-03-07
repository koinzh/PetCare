#ifndef SMARTPET_SONIC_H
#define SMARTPET_SONIC_H

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

#endif //SMARTPET_SONIC_H
