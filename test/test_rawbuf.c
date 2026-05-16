/**
 * @file test_rawbuf.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_rawbuf_new(void)
{
    // if obj_size must > 0, illegal. so no test case.

    rawbuf_t rawbuf = rawbuf_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(rawbuf);
    rawbuf_free(&rawbuf);
    TEST_ASSERT_NULL(rawbuf);
}

static void test_rawbuf_new_invalid(void)
{
    // rawbuf_t rawbuf = rawbuf_new(sizeof(int), 0);
    // TEST_ASSERT_NULL(rawbuf);
}

#ifdef UNICSTL_STATIC_MEMORY
static void test_rawbuf_init(void)
{
    size_t i = 0;
    const size_t len = 10;

    int data[10];
    int temp = 0;

    struct _rawbuf rawbuf;
    TEST_ASSERT_TRUE(rawbuf_init(&rawbuf, sizeof(int), len, data));
    for (i = 0; i < len; i++)
    {
        size_t index = len - 1 - i;
        TEST_ASSERT_TRUE(rawbuf.set(&rawbuf, index, &data[i]));

        TEST_ASSERT_TRUE(rawbuf.get((rawbuf_t)&rawbuf, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    TEST_ASSERT_TRUE(rawbuf.set(&rawbuf, 0, &data[0]));
}
#endif

static void test_rawbuf_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    rawbuf_t rawbuf = rawbuf_new(sizeof(int), len);

    // set from start to end
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(rawbuf->set(rawbuf, i, &data[i]));

        TEST_ASSERT_TRUE(rawbuf->get(rawbuf, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(rawbuf->set(rawbuf, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(rawbuf->set(rawbuf, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(rawbuf->set(rawbuf, 9, &temp));

    TEST_ASSERT_TRUE(rawbuf->get(rawbuf, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(rawbuf->get(rawbuf, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(rawbuf->get(rawbuf, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    rawbuf_free(&rawbuf);
}

static void test_rawbuf_set_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    rawbuf_t rawbuf = rawbuf_new(sizeof(int), len);
    for(i = 0; i < len; i++)
    {
        rawbuf->set(rawbuf, i, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(rawbuf->set(rawbuf, -1, &temp));
    TEST_ASSERT_FALSE(rawbuf->set(rawbuf, len, &temp));
    TEST_ASSERT_FALSE(rawbuf->set(rawbuf, 999, &temp));

    TEST_ASSERT_FALSE(rawbuf->set(rawbuf, 0, NULL));

    rawbuf_free(&rawbuf);
}

static void test_rawbuf_at(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    rawbuf_t rawbuf = rawbuf_new(sizeof(int), len);
    for(i = 0; i < len; i++)
    {
        rawbuf->set(rawbuf, i, &data[i]);
    }

    const int *p_int = NULL;
    p_int = rawbuf->at(rawbuf, 0);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = rawbuf->at(rawbuf, 4);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = rawbuf->at(rawbuf, 9);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    TEST_ASSERT_NULL(rawbuf->at(rawbuf, 10));
    TEST_ASSERT_NULL(rawbuf->at(rawbuf, -1));


    //  warning: initialization discards 'const' qualifier from pointer target type
    // int *p_int_warring = rawbuf->at(rawbuf, 0);

    // !!! you should not do this.
    int *p_int_warring = (int *)rawbuf->at(rawbuf, 0);
    *p_int_warring = 100;

    rawbuf->get(rawbuf, 0, &temp);
    TEST_ASSERT_EQUAL_INT(100, temp);

    rawbuf_free(&rawbuf);
}

static void test_rawbuf_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    rawbuf_t rawbuf = rawbuf_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(rawbuf);
    TEST_ASSERT_EQUAL_INT(len, rawbuf->capacity(rawbuf));

    // set from end to start
    for (i = 0; i < len; i++)
    {
        size_t index = len-1-i;
        TEST_ASSERT_TRUE(rawbuf->set(rawbuf, index,  &data[i]));

        TEST_ASSERT_TRUE(rawbuf->get(rawbuf, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);
    }
    for (i = 0; i < len; i++)
    {
        size_t index = len-1-i;
        TEST_ASSERT_TRUE(rawbuf->get(rawbuf, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[index].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[index].name, temp.name);
    }
    rawbuf_free(&rawbuf);
    TEST_ASSERT_NULL(rawbuf);
}

void test_rawbuf(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_rawbuf_new);
    RUN_TEST(test_rawbuf_new_invalid);

    RUN_TEST(test_rawbuf_init);

    RUN_TEST(test_rawbuf_set);
    RUN_TEST(test_rawbuf_set_invalid);

    RUN_TEST(test_rawbuf_at);

    // ---------- ext ----------
    RUN_TEST(test_rawbuf_struct);
}
