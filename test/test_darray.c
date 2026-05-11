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

static void test_darray_remove(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
    }

    TEST_ASSERT_TRUE(darray->remove(darray, len - 1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
    TEST_ASSERT_FALSE(darray->full(darray));

    for (i = 0; i < len - 2; i++)
    {
        TEST_ASSERT_TRUE(darray->remove(darray, 1, &temp));
        TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

        TEST_ASSERT_FALSE(darray->full(darray));
    }

    TEST_ASSERT_TRUE(darray->remove(darray, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(darray->empty(darray));
    darray_free(&darray);
}

static void test_darray_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->pop(darray, &temp));
        TEST_ASSERT_EQUAL_INT(data[len -1 - i], temp);

        TEST_ASSERT_FALSE(darray->full(darray));
    }
    TEST_ASSERT_TRUE(darray->empty(darray));
    darray_free(&darray);
}

static void test_darray_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));

        uint32_t index = darray->size(darray) - 1;
        TEST_ASSERT_TRUE(darray->get(darray, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(darray->set(darray, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(darray->set(darray, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(darray->set(darray, 9, &temp));

    TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(darray->get(darray, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(darray->get(darray, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    darray_free(&darray);
}

static void test_darray_resize(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), 1);
    darray->compare = compare_num;
    
    // TEST_ASSERT_EQUAL_INT(8, darray->capacity(darray));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));

        // printf("capacity: %d\n", darray->capacity(darray));
    }
    TEST_ASSERT_EQUAL_INT(16, darray->capacity(darray));
    darray_free(&darray);
}

static void test_darray_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));

    TEST_ASSERT_TRUE(darray->clear(darray));
    TEST_ASSERT_TRUE(darray->empty(darray));

    darray_free(&darray);
}

static void test_darray_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), 8);
    darray->compare = compare_num;
    
    TEST_ASSERT_TRUE(darray->dynamic(darray));
    darray->dynamic_enable(darray, false);
    TEST_ASSERT_FALSE(darray->dynamic(darray));

    TEST_ASSERT_EQUAL_INT(8, darray->capacity(darray));
    for(i = 0; i < 8; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
    }
    TEST_ASSERT_FALSE(darray->append(darray, &data[i]));
    darray_free(&darray);
}

static void test_darray_index(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    temp = 1;
    TEST_ASSERT_EQUAL_INT(0, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 5;
    TEST_ASSERT_EQUAL_INT(4, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 10;
    TEST_ASSERT_EQUAL_INT(9, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, darray->index(darray, &temp));
    TEST_ASSERT_FALSE(darray->contains(darray, &temp));

    darray_free(&darray);
}

void test_darray(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_darray_new);
    RUN_TEST(test_darray_insert);
    RUN_TEST(test_darray_append);
    RUN_TEST(test_darray_remove);
    RUN_TEST(test_darray_pop);

    RUN_TEST(test_darray_set);
    RUN_TEST(test_darray_resize);
    RUN_TEST(test_darray_clear);
    RUN_TEST(test_darray_dynamic);
    RUN_TEST(test_darray_index);
}
