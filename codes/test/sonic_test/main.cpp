#include "sonic.h"
#include <iostream>
using namespace std;

int main() {
    int trig= 28;
    int echo = 29;
    UltrasonicSensor sensor(trig, echo);

    sensor.initialize();

    while (true) {
        float distance = sensor.measureDistance();
        cout << "Distance: " << distance << " cm" << endl;
        delay(1000);  // mesure in every 1s
    }

    return 0;
}
