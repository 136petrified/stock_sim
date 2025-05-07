#include "stk_sim.h"

int s_bad_event() {
    return rand() % 67 == 0;
}

int s_good_event() {
    return rand() % 103 == 0;
}

double generate_value() {
    srand(time(NULL));
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = (unsigned) ((~ct ^ mask) & mask);

    double a = (1 + (rand() % 14)) * (rand() % 2 ? -1.0 : 1.0);
    double b = ((1 + (rand() % 43)) / 43) * (rand() % 2 ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * (rand() % 2 ? -1.0 : 1.0);
    double x = rand() % 43;

    return a * sin(b * x + c);
}
