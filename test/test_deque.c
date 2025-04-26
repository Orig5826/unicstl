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

static void test_deque_num(void)
{
    uint32_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(deque);
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

    TEST_ASSERT_FALSE(deque->empty(deque));
    TEST_ASSERT_TRUE(deque->clear(deque));
    TEST_ASSERT_TRUE(deque->empty(deque));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_back(deque, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
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

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));

        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[deque->size(deque) - 1], temp);

        TEST_ASSERT_TRUE(deque->back(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
    }
    TEST_ASSERT_TRUE(deque->clear(deque));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
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

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
    }
    temp = 11;
    deque->set(deque, 0, &temp);

    temp = 22;
    deque->set(deque, len / 2, &temp);

    temp = 33;
    deque->set(deque, len - 1, &temp);

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->get(deque, i, &temp));
    }

    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}

static void test_deque_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(struct _student));
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

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->get(deque, i, &temp));
    }

    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}


static void test_deque_iter(void)
{
    uint32_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(deque);
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

    iterator_t iter = deque->iter(deque, DEQUE_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    iter = deque->iter(deque, DEQUE_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    iter = deque->iter(deque, DEQUE_REVERSE);
    i = len - 1;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }

    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}

void test_deque(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_deque_num);
    RUN_TEST(test_deque_struct);

    RUN_TEST(test_deque_iter);
}
