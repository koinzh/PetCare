#ifndef PETCARE_WEIGHT_TEST
#define PETCARE_WEIGHT_TEST

#include <wiringPi.h>

class weight {
public:
    struct hx711_args {
        int EN;
        int calibration;
        float coefficient; 
        int weight;
        unsigned long value;
    };

    static void set_pin(struct hx711_args *value);
    static void init_pin();
    static void start(struct hx711_args *value);
    static int setup(struct hx711_args *value);
    static void loop(struct hx711_args *value);
};

#endif // PETCARE_WEIGHT_TEST
