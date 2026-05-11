/**
 * @file test_darray.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_darray_new(void)
{
    darray_t darray = darray_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(darray);
    darray_free(&darray);

    TEST_ASSERT_NULL(darray_new(0, 0));
    TEST_ASSERT_NULL(darray_new(0, 1));
    TEST_ASSERT_NULL(darray_new(sizeof(int), 0));

    // ------------------------------
    TEST_ASSERT_NULL(darray);
    darray_free(&darray);
}

static void test_darray_insert(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    TEST_ASSERT_TRUE(darray->empty(darray));
    TEST_ASSERT_FALSE(darray->full(darray));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->insert(darray, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(darray->empty(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));
    darray_free(&darray);
}


static void test_darray_append(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    TEST_ASSERT_TRUE(darray->empty(darray));
    TEST_ASSERT_FALSE(darray->full(darray));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        uint32_t index = darray->size(darray) - 1;
        TEST_ASSERT_TRUE(darray->get(darray, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(darray->empty(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));
    darray_free(&darray);
}

void test_darray(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_darray_new);
    RUN_TEST(test_darray_insert);
    RUN_TEST(test_darray_append);
}
