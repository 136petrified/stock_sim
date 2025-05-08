#include "unity.h"
#include "unity_internals.h"

#include "stk_sim.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_gen_print_err(void) {
    print_err("./err_test.txt", "Error occurred! Test message.");
}

void test_gen_strdup(void) {
    char str1[] = "hexagonal";
    char *str2 = strdup(str1);

    TEST_ASSERT_EQUAL(0, strcmp(str1, str2));

    free(str2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_gen_print_err);
    RUN_TEST(test_gen_strdup);
    return UNITY_END();
}