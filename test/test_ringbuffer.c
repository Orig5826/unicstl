/**
 * @file test_ringbuffer.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

static void test_ringbuffer_new(void)
{
    darray_t ringbuffer = darray_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(ringbuffer);
    darray_free(&ringbuffer);

    TEST_ASSERT_NULL(darray_new(0, 0));
    TEST_ASSERT_NULL(darray_new(0, 1));
    TEST_ASSERT_NULL(darray_new(sizeof(int), 0));

    // ------------------------------
    TEST_ASSERT_NULL(ringbuffer);
    darray_free(&ringbuffer);
}

static void test_ringbuffer_push(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuffer_t ringbuffer = ringbuffer_new(sizeof(int), len);

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_back(ringbuffer, &data[i]));
    }
    TEST_ASSERT_FALSE(ringbuffer->push_back(ringbuffer, &data[0]));

    TEST_ASSERT_TRUE(ringbuffer->clear(ringbuffer));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));
    }
    TEST_ASSERT_FALSE(ringbuffer->push_front(ringbuffer, &data[0]));

    ringbuffer_free(&ringbuffer);
}

static void test_ringbuffer_num(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuffer_t ringbuffer = ringbuffer_new(sizeof(int), len);
    ringbuffer->print_obj = print_num;

    TEST_ASSERT_TRUE(ringbuffer->empty(ringbuffer));
    TEST_ASSERT_FALSE(ringbuffer->full(ringbuffer));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_back(ringbuffer, &data[i]));

        TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuffer->size(ringbuffer));
    }
    TEST_ASSERT_TRUE(ringbuffer->full(ringbuffer));
    TEST_ASSERT_FALSE(ringbuffer->empty(ringbuffer));

    TEST_ASSERT_TRUE(ringbuffer->clear(ringbuffer));
    TEST_ASSERT_TRUE(ringbuffer->empty(ringbuffer));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_back(ringbuffer, &data[i]));
    }
    // ringbuffer->print(ringbuffer);

    for (i = 0; i < len + 1; i++)
    {
        if (!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->pop_back(ringbuffer, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->pop_back(ringbuffer, &temp));
        }

        if (!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);

            TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuffer->size(ringbuffer) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_FALSE(ringbuffer->back(ringbuffer, &temp));
        }
    }
    TEST_ASSERT_TRUE(ringbuffer->empty(ringbuffer));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));

        TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[ringbuffer->size(ringbuffer) - 1], temp);

        TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuffer->size(ringbuffer));
    }
    TEST_ASSERT_TRUE(ringbuffer->clear(ringbuffer));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if (!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->pop_front(ringbuffer, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->pop_front(ringbuffer, &temp));
        }

        if (!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuffer->size(ringbuffer) - 1], temp);

            TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_FALSE(ringbuffer->back(ringbuffer, &temp));
        }
    }

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));
    }
    temp = 11;
    ringbuffer->set(ringbuffer, 0, &temp);

    temp = 22;
    ringbuffer->set(ringbuffer, len / 2, &temp);

    temp = 33;
    ringbuffer->set(ringbuffer, len - 1, &temp);

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->get(ringbuffer, i, &temp));
    }
#endif

    ringbuffer_free(&ringbuffer);
    TEST_ASSERT_NULL(ringbuffer);
}

static void test_ringbuffer_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuffer_t ringbuffer = ringbuffer_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(ringbuffer);
    ringbuffer->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_back(ringbuffer, &data[i]));

        TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuffer->size(ringbuffer));
    }
    TEST_ASSERT_FALSE(ringbuffer->empty(ringbuffer));
    TEST_ASSERT_TRUE(ringbuffer->clear(ringbuffer));
    TEST_ASSERT_TRUE(ringbuffer->empty(ringbuffer));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_back(ringbuffer, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->pop_back(ringbuffer, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->pop_back(ringbuffer, &temp));
        }
        
        if(!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

            TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuffer->size(ringbuffer) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[ringbuffer->size(ringbuffer) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_FALSE(ringbuffer->back(ringbuffer, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));

        TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuffer->size(ringbuffer));
    }
    TEST_ASSERT_TRUE(ringbuffer->clear(ringbuffer));
    TEST_ASSERT_TRUE(ringbuffer->empty(ringbuffer));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->pop_front(ringbuffer, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->pop_front(ringbuffer, &temp));
        }
        
        if(!ringbuffer->empty(ringbuffer))
        {
            TEST_ASSERT_TRUE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuffer->size(ringbuffer) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[ringbuffer->size(ringbuffer) - 1].name, temp.name);

            TEST_ASSERT_TRUE(ringbuffer->back(ringbuffer, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuffer->front(ringbuffer, &temp));
            TEST_ASSERT_FALSE(ringbuffer->back(ringbuffer, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->push_front(ringbuffer, &data[i]));
    }

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuffer->get(ringbuffer, i, &temp));
    }
#endif

    ringbuffer_free(&ringbuffer);
    TEST_ASSERT_NULL(ringbuffer);
}


static void test_ringbuffer_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuffer_t ringbuffer = ringbuffer_new(sizeof(int), len);
    ringbuffer->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        ringbuffer->push_back(ringbuffer, &data[i]);
    }

    iterator_t iter = ringbuffer->iter(ringbuffer, RINGBUF_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    iter = ringbuffer->iter(ringbuffer, RINGBUF_REVERSE);
    i = len - 1;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }

    ringbuffer_free(&ringbuffer);
}

void test_ringbuffer(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_ringbuffer_new);
    RUN_TEST(test_ringbuffer_push);

    RUN_TEST(test_ringbuffer_num);
    RUN_TEST(test_ringbuffer_struct);

    RUN_TEST(test_ringbuffer_iter);
}
