#include "stk_sim.h"

int s_bad_event() {
    return rand() % 67 == 0;
}

int s_good_event() {
    return rand() % 103 == 0;
}

void print_err(const char *file, const char *msg) {
    FILE *fp = fopen(file, "a");
    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

void stk_sim_loop() {
    // TODO: Implement this
    seed_random();

    while (1) {
        // here...
    }
}

double generate_value() {
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = (unsigned) ((~ct ^ mask) & mask);

    double a = (1 + (rand() % 14)) * (rand() % 2 ? -1.0 : 1.0);
    double b = ((1 + (rand() % 43)) / 43) * (rand() % 2 ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * (rand() % 2 ? -1.0 : 1.0);
    double x = rand() % 43;

    return a * sin(b * x + c);
}

char * strdup(const char *str) {
    int buflen = strlen(str) + 1;
    char *new_str = (char *) malloc(buflen);

    if (new_str == NULL) {
        print_err(ERR_FILE, "strdup(): malloc() failed\n");
        return NULL;
    }

    strcpy(new_str, str);
    return new_str;
}