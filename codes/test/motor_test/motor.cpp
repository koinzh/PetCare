#include "motor.h"

void motor::SetStep(int a, int b, int c, int d)
{
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}

void motor::Forward(int t, int steps)
{
    const int stepSequence[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    int i, j;
    for (i = 0; i < steps; i++) {
        for (j = 0; j < 4; j++) {
            SetStep(stepSequence[j][0], stepSequence[j][1], stepSequence[j][2], stepSequence[j][3]);
            delay(t);
        }
    }
}

void motor::Stop()
{
    SetStep(0, 0, 0, 0);
}

void motor::Rollback(int t, int steps)
{
    const int stepSequence[4][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {1, 0, 0, 0}
    };

    int i, j;
    for (i = 0; i < steps; i++) {
        for (j = 0; j < 4; j++) {
            SetStep(stepSequence[j][0], stepSequence[j][1], stepSequence[j][2], stepSequence[j][3]);
            delay(t);
        }
    }
}
