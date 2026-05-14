/**
 * @file test_deque.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_deque_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(deque_new(0, 0));
    // TEST_ASSERT_NULL(deque_new(0, 1));

    deque_t deque = deque_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(deque);
    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}

static void test_deque_new_lazy(void)
{
    deque_t deque = deque_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(deque);
    TEST_ASSERT_EQUAL_size_t(0, deque->capacity(deque));

    int temp = 0;
    TEST_ASSERT_TRUE(deque->push_back(deque, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, deque->capacity(deque));
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
    TEST_ASSERT_EQUAL_INT(len + 2, deque->size(deque));

    deque_free(&deque);
}

static void test_deque_push_back_invalid(void)
{
    deque_t deque = deque_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(deque->push_back(deque, NULL));
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
    TEST_ASSERT_EQUAL_INT(len + 2, deque->size(deque));

    deque_free(&deque);
}

static void test_deque_push_front_invalid(void)
{
    deque_t deque = deque_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(deque->push_front(deque, NULL));
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

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        deque->push_back(deque, &data[i]);
    }
    TEST_ASSERT_TRUE(deque->pop_back(deque, NULL));
    TEST_ASSERT_TRUE(deque->pop_back(deque, NULL));
    TEST_ASSERT_FALSE(deque->pop_back(deque, NULL));

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

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        deque->push_back(deque, &data[i]);
    }
    TEST_ASSERT_TRUE(deque->pop_front(deque, NULL));
    TEST_ASSERT_TRUE(deque->pop_front(deque, NULL));
    TEST_ASSERT_FALSE(deque->pop_front(deque, NULL));

    deque_free(&deque);
}

static void test_deque_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);

    TEST_ASSERT_FALSE(deque->back(deque, &temp));
    for (i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        deque->pop_back(deque, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
        }
    }

    TEST_ASSERT_FALSE(deque->back(deque, &temp));
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        deque->pop_front(deque, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(deque->front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 2 - i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->front(deque, &temp));
        }
    }

    deque_free(&deque);
}

static void test_deque_back_invalid(void)
{
    deque_t deque = deque_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(deque->back(deque, NULL));
    deque_free(&deque);
}

static void test_deque_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    TEST_ASSERT_FALSE(deque->front(deque, &temp));
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

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        deque->push_back(deque, &data[i]);
    }
    TEST_ASSERT_TRUE(deque->pop_front(deque, NULL));
    TEST_ASSERT_TRUE(deque->pop_front(deque, NULL));
    TEST_ASSERT_FALSE(deque->pop_front(deque, NULL));

    deque_free(&deque);
}

static void test_deque_front_invalid(void)
{
    deque_t deque = deque_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(deque->front(deque, NULL));
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

static void test_deque_resize(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    deque_t deque = deque_new(sizeof(int), len);

    TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
    TEST_ASSERT_TRUE(deque->resize(deque, 16));
    TEST_ASSERT_EQUAL_INT(16, deque->capacity(deque));

    for(i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, deque->capacity(deque));
    TEST_ASSERT_EQUAL_INT(len, deque->size(deque));

    TEST_ASSERT_TRUE(deque->resize(deque, 8));
    TEST_ASSERT_EQUAL_INT(8, deque->capacity(deque));
    TEST_ASSERT_EQUAL_INT(8, deque->size(deque));

    TEST_ASSERT_TRUE(deque->front(deque, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(deque->back(deque, &temp));
    TEST_ASSERT_EQUAL_INT(data[7], temp);

    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(deque->pop_front(deque, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(deque->pop_front(deque, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, deque->capacity(deque));
    TEST_ASSERT_EQUAL_INT(0, deque->size(deque));

    deque_free(&deque);
}

static void test_deque_resize_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    deque_t deque = deque_new(sizeof(int), len);
    
    TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
    TEST_ASSERT_FALSE(deque->resize(deque, 0));
    TEST_ASSERT_FALSE(deque->resize(deque, -1));

    deque_free(&deque);
}

static void test_deque_resize_edge(void)
{
    deque_t deque = deque_new(sizeof(int), 10);

    TEST_ASSERT_EQUAL_INT(10, deque->capacity(deque));
    TEST_ASSERT_TRUE(deque->resize(deque, 10));
    TEST_ASSERT_EQUAL_INT(10, deque->capacity(deque));

    deque_free(&deque);
}

static void test_deque_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    deque_t deque = deque_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
        
        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(deque->full(deque));
        }
        else
        {
            TEST_ASSERT_TRUE(deque->full(deque));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
        
        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(deque->full(deque));
        }
        else
        {
            TEST_ASSERT_TRUE(deque->full(deque));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->push_front(deque, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, deque->size(deque));
        
        TEST_ASSERT_TRUE(deque->front(deque, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, deque->capacity(deque));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(deque->full(deque));
        }
        else
        {
            TEST_ASSERT_TRUE(deque->full(deque));
        }
    }

    deque_free(&deque);
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

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(deque->get(deque, i, &temp));
    }
#endif

    deque_free(&deque);
    TEST_ASSERT_NULL(deque);
}


void test_deque(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_deque_new);
    RUN_TEST(test_deque_new_lazy);

    RUN_TEST(test_deque_push_back);
    RUN_TEST(test_deque_push_back_invalid);

    RUN_TEST(test_deque_push_front);
    RUN_TEST(test_deque_push_front_invalid);

    RUN_TEST(test_deque_pop_back);
    RUN_TEST(test_deque_pop_front);

    RUN_TEST(test_deque_back);
    RUN_TEST(test_deque_back_invalid);

    RUN_TEST(test_deque_front);
    RUN_TEST(test_deque_front_invalid);

    RUN_TEST(test_deque_iter);

    RUN_TEST(test_deque_resize);
    RUN_TEST(test_deque_resize_invalid);
    RUN_TEST(test_deque_resize_edge);

    RUN_TEST(test_deque_dynamic);

    // ---------- base ----------
    RUN_TEST(test_deque_status);

    // ---------- ext ----------
    RUN_TEST(test_deque_struct);
}
