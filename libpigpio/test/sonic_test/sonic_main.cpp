#include "sonic.h"
#include <iostream>
#include <pigpio.h>

using namespace std;

int main() {
    if (gpioInitialise() < 0) {
        cerr << "Failed to initialize pigpio." << endl;
        return -1;
    }

    UltrasonicSensor sensor(20, 21); // Use appropriate GPIO pins

    while (true) {
        sensor.sendTriggerPulse();
        usleep(60000); // Wait for echo to return
        float distance = sensor.measureDistance();
        cout << "Distance: " << distance << " cm" << endl;
    }

    gpioTerminate();
    return 0;
}
