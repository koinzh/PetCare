#include <iostream>
#include <wiringPi.h>
#include <unistd.h> // For usleep()


const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 4;



long readHX711() {
    long count = 0;
    while (digitalRead(LOADCELL_DOUT_PIN)) {
        // Wait for the chip to be ready
        usleep(1);
    }

    for (int i = 0; i < 24; i++) {
        digitalWrite(LOADCELL_SCK_PIN, HIGH);
        count = count << 1;
        digitalWrite(LOADCELL_SCK_PIN, LOW);
        if (digitalRead(LOADCELL_DOUT_PIN)) {
            count++;
        }
    }

    // Set the channel and the gain factor for the next reading
    digitalWrite(LOADCELL_SCK_PIN, HIGH);
    usleep(1);
    digitalWrite(LOADCELL_SCK_PIN, LOW);

    return count;
}

void setup() {
    wiringPiSetup();
    pinMode(LOADCELL_SCK_PIN, OUTPUT);
    pinMode(LOADCELL_DOUT_PIN, INPUT);
}

int main() {
    std::cout << "HX711 Calibration" << std::endl;
    setup();

    long zero_factor = readHX711(); // Get a baseline reading
    std::cout << "Zero factor: " << zero_factor << std::endl;

    // Put a known weight(187g)
    std::cout << "Put a known weight(187g) and press Enter" << std::endl;
    std::cin.get();

    long weight_reading = readHX711() - zero_factor;
    std::cout << "Reading: " << weight_reading << std::endl;

    // Assuming you've placed a 187g weight, calculate the calibration factor
    double calibration_factor = weight_reading / 187.0;
    std::cout << "Calibration factor: " << calibration_factor << std::endl;

    return 0;
}
