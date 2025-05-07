#include "unity.h"
#include "unity_internals.h"

#include "stk_sim.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_PRINT_ERR(void) {
    print_err("./err_test.txt", "Error occurred! Test message.\n");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_PRINT_ERR);
    return UNITY_END();
}