#include "unity.h"
#include "unity_internals.h"

#include "stk_sim.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_mkt_init(void) {
    TEST_ASSERT_TRUE(0);
}

void test_mpm(void) {
    struct MarketParam *mpm = mpm_init("MyMarket", 100, 0, 0, 10, 1, NULL);
    
    TEST_ASSERT_EQUAL(0, strcmp("MyMarket", mpm->name));
    TEST_ASSERT_EQUAL(100, mpm->max_stocks);
    TEST_ASSERT_EQUAL(true, mpm->is_open);

    mpm = mpm_destroy(mpm);
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
    RUN_TEST(test_mkt_init);
    RUN_TEST(test_mpm);
    RUN_TEST(test_gen_print_err);
    RUN_TEST(test_gen_strdup);
    return UNITY_END();
}