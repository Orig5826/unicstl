/**
 * @file test_unicstal.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

void test_unicstl_capacity(void)
{
    TEST_ASSERT_EQUAL_UINT32(8, unicstl_new_capacity(0));
    TEST_ASSERT_EQUAL_UINT32(8, unicstl_new_capacity(1));
    TEST_ASSERT_EQUAL_UINT32(8, unicstl_new_capacity(3));

    TEST_ASSERT_EQUAL_UINT32(8, unicstl_new_capacity(4));
    TEST_ASSERT_EQUAL_UINT32(16, unicstl_new_capacity(8));
    TEST_ASSERT_EQUAL_UINT32(1024, unicstl_new_capacity(512));

    TEST_ASSERT_EQUAL_UINT32(1152, unicstl_new_capacity(1024));
    TEST_ASSERT_EQUAL_UINT32(1296, unicstl_new_capacity(1152));

    TEST_ASSERT_EQUAL_UINT32(1125000, unicstl_new_capacity(1000000));
}

void test_unicstl(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_unicstl_capacity);
}
