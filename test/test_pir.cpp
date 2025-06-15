// filepath: test/test_basic.cpp
#include <unity.h>

void test_true(void) {
    TEST_ASSERT_TRUE(true);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_true);
    UNITY_END();
}

void loop() {}