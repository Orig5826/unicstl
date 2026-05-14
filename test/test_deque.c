/**
 * @file test_deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"


static void test_deque_new(void)
{
    deque_t deque = deque_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(deque);
    deque_free(&deque);
    TEST_ASSERT_NULL(deque);

    TEST_ASSERT_NULL(deque_new(0, 0));
    TEST_ASSERT_NULL(deque_new(0, 1));
    TEST_ASSERT_NULL(deque_new(sizeof(int), 0));
}

static void test_deque_status(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
    TEST_ASSERT_EQUAL_INT(0, deque->size(deque));

    TEST_ASSERT_TRUE(deque->empty(deque));
    TEST_ASSERT_FALSE(deque->full(deque));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));

        TEST_ASSERT_FALSE(deque->empty(deque));
        TEST_ASSERT_FALSE(deque->full(deque));
    }
    TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));
    TEST_ASSERT_TRUE(deque->full(deque));
    TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));

    TEST_ASSERT_TRUE(deque->clear(deque));
    TEST_ASSERT_TRUE(deque->empty(deque));
    TEST_ASSERT_FALSE(deque->full(deque));

    deque_free(&deque);   
}

static void test_deque_push_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));

        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(deque->back(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
    }
    TEST_ASSERT_TRUE(deque->push_back(deque, &data[0]));
    TEST_ASSERT_TRUE(deque->push_front(deque, &data[0]));

    deque_free(&deque);
}

static void test_deque_push_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));

        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1], temp);

        TEST_ASSERT_TRUE(deque->back(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
    }
    TEST_ASSERT_TRUE(deque->push_front(deque, &data[0]));
    TEST_ASSERT_TRUE(deque->push_back(deque, &data[0]));

    deque_free(&deque);
}

static void test_deque_pop_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    TEST_ASSERT_FALSE(deque->front(deque, &temp));
    TEST_ASSERT_FALSE(deque->back(deque, &temp));
    for (i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->pop_back(deque, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(deque->pop_back(deque, &temp));
        }

        if (!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);

            TEST_ASSERT_TRUE(deque->back(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
            TEST_ASSERT_FALSE(deque->back(deque, &temp));
        }
    }
    TEST_ASSERT_TRUE(deque->empty(deque));
    deque_free(&deque);
}


static void test_deque_pop_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    TEST_ASSERT_FALSE(deque->front(deque, &temp));
    TEST_ASSERT_FALSE(deque->back(deque, &temp));
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->pop_front(deque, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(deque->pop_front(deque, &temp));
        }

        if (!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1], temp);

            TEST_ASSERT_TRUE(deque->back(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
            TEST_ASSERT_FALSE(deque->back(deque, &temp));
        }
    }
    TEST_ASSERT_TRUE(deque->empty(deque));
    deque_free(&deque);
}

static void test_deque_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);
    }

    iterator_t iter = deque->iter(deque, RINGBUF_FORWARD);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    iter = deque->iter(deque, RINGBUF_REVERSE);
    i = len - 1;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }
    TEST_ASSERT_EQUAL_INT(0, i);

    deque_free(&deque);
}


static void test_deque_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(deque);
    deque->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));

        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(deque->back(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
    }
    TEST_ASSERT_FALSE(deque->empty(deque));
    TEST_ASSERT_TRUE(deque->clear(deque));
    TEST_ASSERT_TRUE(deque->empty(deque));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->pop_back(deque, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(deque->pop_back(deque, &temp));
        }
        
        if(!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

            TEST_ASSERT_TRUE(deque->back(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[deque->size(deque) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
            TEST_ASSERT_FALSE(deque->back(deque, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));

        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(deque->back(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
    }
    TEST_ASSERT_TRUE(deque->clear(deque));
    TEST_ASSERT_TRUE(deque->empty(deque));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->pop_front(deque, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(deque->pop_front(deque, &temp));
        }
        
        if(!deque->empty(deque))
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[deque->size(deque) - 1].name, temp.name);

            TEST_ASSERT_TRUE(deque->back(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
            TEST_ASSERT_FALSE(deque->back(deque, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
    }

    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}

void test_deque(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_deque_new);
    RUN_TEST(test_deque_status);
    RUN_TEST(test_deque_push_back);
    RUN_TEST(test_deque_push_front);
    RUN_TEST(test_deque_pop_back);
    RUN_TEST(test_deque_pop_front);
    RUN_TEST(test_deque_iter);

    RUN_TEST(test_deque_struct);
}
