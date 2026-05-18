/**
 * @file test_ringbuf.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

static void test_ringbuf_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(ringbuf_new(0, 0));
    // TEST_ASSERT_NULL(ringbuf_new(0, 1));

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(ringbuf);
    ringbuf_free(&ringbuf);
    TEST_ASSERT_NULL(ringbuf);
}

static void test_ringbuf_new_lazy(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(ringbuf);
    TEST_ASSERT_EQUAL_size_t(0, ringbuf->capacity(ringbuf));

    int temp = 0;
    TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, ringbuf->capacity(ringbuf));
    ringbuf_free(&ringbuf);
}

#ifdef UNICSTL_STATIC_MEMORY
static void test_ringbuf_init(void)
{
    size_t i = 0;
    const size_t len = 10;

    int data[10];
    int temp = 0;

    struct _ringbuf ringbuf;
    TEST_ASSERT_TRUE(ringbuf_init(&ringbuf, sizeof(int), len, data));

    TEST_ASSERT_TRUE(ringbuf.empty(&ringbuf));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf.push_back(&ringbuf, &data[i]));

        TEST_ASSERT_TRUE(ringbuf.front((ringbuf_t)&ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(ringbuf.back((ringbuf_t)&ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf.size((ringbuf_t)&ringbuf));
    }
    TEST_ASSERT_TRUE(ringbuf.full(&ringbuf));

    TEST_ASSERT_FALSE(ringbuf.push_back(&ringbuf, &data[0]));
    TEST_ASSERT_FALSE(ringbuf.push_front(&ringbuf, &data[0]));
}
#endif


static void test_ringbuf_push_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));

        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
    }
    TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[0]));
    TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 2, ringbuf->size(ringbuf));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_push_back_invalid(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(ringbuf->push_back(ringbuf, NULL));
    ringbuf_free(&ringbuf);
}

static void test_ringbuf_push_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));

        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1], temp);

        TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
    }
    TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[0]));
    TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 2, ringbuf->size(ringbuf));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_push_front_invalid(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(ringbuf->push_front(ringbuf, NULL));
    ringbuf_free(&ringbuf);
}

static void test_ringbuf_pop_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
    TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
    for (i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->pop_back(ringbuf, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_back(ringbuf, &temp));
        }

        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);

            TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
        }
    }
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }
    TEST_ASSERT_TRUE(ringbuf->pop_back(ringbuf, NULL));
    TEST_ASSERT_TRUE(ringbuf->pop_back(ringbuf, NULL));
    TEST_ASSERT_FALSE(ringbuf->pop_back(ringbuf, NULL));

    ringbuf_free(&ringbuf);
}


static void test_ringbuf_pop_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
    TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
    for (i = 0; i < len; i++)
    {
        ringbuf->push_front(ringbuf, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, &temp));
        }

        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1], temp);

            TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
        }
    }
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }
    TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, NULL));
    TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, NULL));
    TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, NULL));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);

    TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
    for (i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        ringbuf->pop_back(ringbuf, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
        }
    }

    TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
    for (i = 0; i < len; i++)
    {
        ringbuf->push_front(ringbuf, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        ringbuf->pop_front(ringbuf, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 2 - i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
        }
    }

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_back_invalid(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(ringbuf->back(ringbuf, NULL));
    ringbuf_free(&ringbuf);
}

static void test_ringbuf_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
    for (i = 0; i < len; i++)
    {
        ringbuf->push_front(ringbuf, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, &temp));
        }

        if (!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1], temp);

            TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
        }
    }
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }
    TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, NULL));
    TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, NULL));
    TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, NULL));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_front_invalid(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(ringbuf->front(ringbuf, NULL));
    ringbuf_free(&ringbuf);
}


static void test_ringbuf_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    // ringbuf->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));

        size_t index = ringbuf->size(ringbuf) - 1;
        TEST_ASSERT_TRUE(ringbuf->get(ringbuf, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(ringbuf->set(ringbuf, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(ringbuf->set(ringbuf, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(ringbuf->set(ringbuf, 9, &temp));

    TEST_ASSERT_TRUE(ringbuf->get(ringbuf, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(ringbuf->get(ringbuf, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(ringbuf->get(ringbuf, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_set_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    // ringbuf->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(ringbuf->set(ringbuf, -1, &temp));
    TEST_ASSERT_FALSE(ringbuf->set(ringbuf, len, &temp));
    TEST_ASSERT_FALSE(ringbuf->set(ringbuf, 999, &temp));

    TEST_ASSERT_FALSE(ringbuf->set(ringbuf, 0, NULL));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_at(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    // ringbuf->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }

    const int *p_int = NULL;
    p_int = ringbuf->at(ringbuf, 0);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = ringbuf->at(ringbuf, 4);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = ringbuf->at(ringbuf, 9);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    TEST_ASSERT_NULL(ringbuf->at(ringbuf, 10));
    TEST_ASSERT_NULL(ringbuf->at(ringbuf, -1));

    //  warning: initialization discards 'const' qualifier from pointer target type
    // int *p_int_warring = ringbuf->at(ringbuf, 0);

    // !!! you should not do this.
    int *p_int_warring = (int *)ringbuf->at(ringbuf, 0);
    *p_int_warring = 100;

    ringbuf->get(ringbuf, 0, &temp);
    TEST_ASSERT_EQUAL_INT(100, temp);

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }

    iterator_t iter = ringbuf->iter(ringbuf, LINEAR_FORWARD);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    iter = ringbuf->iter(ringbuf, LINEAR_REVERSE);
    i = len - 1;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }
    TEST_ASSERT_EQUAL_INT(0, i);

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_reserve(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);

    TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->reserve(ringbuf, 16));
    TEST_ASSERT_EQUAL_INT(16, ringbuf->capacity(ringbuf));

    for(i = 0; i < len; i++)
    {
        ringbuf->push_back(ringbuf, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, ringbuf->capacity(ringbuf));
    TEST_ASSERT_EQUAL_INT(len, ringbuf->size(ringbuf));

    TEST_ASSERT_TRUE(ringbuf->reserve(ringbuf, 8));
    TEST_ASSERT_EQUAL_INT(8, ringbuf->capacity(ringbuf));
    TEST_ASSERT_EQUAL_INT(8, ringbuf->size(ringbuf));

    TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
    TEST_ASSERT_EQUAL_INT(data[7], temp);

    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, ringbuf->capacity(ringbuf));
    TEST_ASSERT_EQUAL_INT(0, ringbuf->size(ringbuf));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_reserve_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    
    TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
    TEST_ASSERT_FALSE(ringbuf->reserve(ringbuf, 0));
    TEST_ASSERT_FALSE(ringbuf->reserve(ringbuf, -1));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_reserve_edge(void)
{
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), 10);

    TEST_ASSERT_EQUAL_INT(10, ringbuf->capacity(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->reserve(ringbuf, 10));
    TEST_ASSERT_EQUAL_INT(10, ringbuf->capacity(ringbuf));

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
        
        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(ringbuf->full(ringbuf));
        }
        else
        {
            TEST_ASSERT_TRUE(ringbuf->full(ringbuf));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
        
        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(ringbuf->full(ringbuf));
        }
        else
        {
            TEST_ASSERT_TRUE(ringbuf->full(ringbuf));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
        
        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(ringbuf->full(ringbuf));
        }
        else
        {
            TEST_ASSERT_TRUE(ringbuf->full(ringbuf));
        }
    }

    ringbuf_free(&ringbuf);
}

static void test_ringbuf_status(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(int), len);
    ringbuf->print_obj = print_num;

    TEST_ASSERT_EQUAL_INT(len, ringbuf->capacity(ringbuf));
    TEST_ASSERT_EQUAL_INT(0, ringbuf->size(ringbuf));

    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));
    TEST_ASSERT_FALSE(ringbuf->full(ringbuf));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));

        TEST_ASSERT_FALSE(ringbuf->empty(ringbuf));
        TEST_ASSERT_FALSE(ringbuf->full(ringbuf));
    }
    TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));
    TEST_ASSERT_TRUE(ringbuf->full(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));

    TEST_ASSERT_TRUE(ringbuf->clear(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));
    TEST_ASSERT_FALSE(ringbuf->full(ringbuf));

    ringbuf_free(&ringbuf);   
}

static void test_ringbuf_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    ringbuf_t ringbuf = ringbuf_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(ringbuf);
    ringbuf->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));

        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
    }
    TEST_ASSERT_FALSE(ringbuf->empty(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->clear(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_back(ringbuf, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->pop_back(ringbuf, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_back(ringbuf, &temp));
        }
        
        if(!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

            TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[ringbuf->size(ringbuf) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));

        TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, ringbuf->size(ringbuf));
    }
    TEST_ASSERT_TRUE(ringbuf->clear(ringbuf));
    TEST_ASSERT_TRUE(ringbuf->empty(ringbuf));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->pop_front(ringbuf, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->pop_front(ringbuf, &temp));
        }
        
        if(!ringbuf->empty(ringbuf))
        {
            TEST_ASSERT_TRUE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[ringbuf->size(ringbuf) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[ringbuf->size(ringbuf) - 1].name, temp.name);

            TEST_ASSERT_TRUE(ringbuf->back(ringbuf, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(ringbuf->front(ringbuf, &temp));
            TEST_ASSERT_FALSE(ringbuf->back(ringbuf, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->push_front(ringbuf, &data[i]));
    }

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(ringbuf->get(ringbuf, i, &temp));
    }
#endif

    ringbuf_free(&ringbuf);
    TEST_ASSERT_NULL(ringbuf);
}


void test_ringbuf(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_ringbuf_new);
    RUN_TEST(test_ringbuf_new_lazy);

#ifdef UNICSTL_STATIC_MEMORY
    RUN_TEST(test_ringbuf_init);
#endif

    RUN_TEST(test_ringbuf_push_back);
    RUN_TEST(test_ringbuf_push_back_invalid);

    RUN_TEST(test_ringbuf_push_front);
    RUN_TEST(test_ringbuf_push_front_invalid);

    RUN_TEST(test_ringbuf_pop_back);
    RUN_TEST(test_ringbuf_pop_front);

    RUN_TEST(test_ringbuf_back);
    RUN_TEST(test_ringbuf_back_invalid);

    RUN_TEST(test_ringbuf_front);
    RUN_TEST(test_ringbuf_front_invalid);

    // ---------- random access ----------
    RUN_TEST(test_ringbuf_set);
    RUN_TEST(test_ringbuf_set_invalid);

    RUN_TEST(test_ringbuf_at);

    // ---------- base ----------
    RUN_TEST(test_ringbuf_iter);

    RUN_TEST(test_ringbuf_reserve);
    RUN_TEST(test_ringbuf_reserve_invalid);
    RUN_TEST(test_ringbuf_reserve_edge);

    RUN_TEST(test_ringbuf_dynamic);

    RUN_TEST(test_ringbuf_status);
    
    // ---------- ext ----------
    RUN_TEST(test_ringbuf_struct);
}
