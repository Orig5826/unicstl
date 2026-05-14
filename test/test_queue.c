/**
 * @file test_queue.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_queue_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(queue_new(0, 0));
    // TEST_ASSERT_NULL(queue_new(0, 1));

    queue_t queue = queue_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(queue);
    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

static void test_queue_new_lazy(void)
{
    queue_t queue = queue_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_EQUAL_size_t(0, queue->capacity(queue));

    int temp = 0;
    TEST_ASSERT_TRUE(queue->push(queue, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, queue->capacity(queue));
    queue_free(&queue);
}

static void test_queue_push(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);
    queue->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
    }
    TEST_ASSERT_TRUE(queue->push(queue, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 1, queue->size(queue));

    queue_free(&queue);
}

static void test_queue_push_invalid(void)
{
    queue_t queue = queue_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(queue->push(queue, NULL));
    queue_free(&queue);
}

static void test_queue_pop(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);
    queue->print_obj = print_num;

    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    TEST_ASSERT_FALSE(queue->back(queue, &temp));
    for (i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(len, queue->size(queue));

    for (i = 0; i < len; i++)
    {
        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->pop(queue, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(queue->pop(queue, &temp));
        }

        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->front(queue, &temp));
            TEST_ASSERT_FALSE(queue->back(queue, &temp));
        }

    }
    TEST_ASSERT_TRUE(queue->empty(queue));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_TRUE(queue->pop(queue, NULL));
    TEST_ASSERT_TRUE(queue->pop(queue, NULL));
    TEST_ASSERT_FALSE(queue->pop(queue, NULL));

    queue_free(&queue);
}

static void test_queue_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);

    TEST_ASSERT_FALSE(queue->back(queue, &temp));
    for (i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        queue->pop(queue, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->front(queue, &temp));
        }
    }

    queue_free(&queue);
}

static void test_queue_back_invalid(void)
{
    queue_t queue = queue_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(queue->back(queue, NULL));
    queue_free(&queue);
}

static void test_queue_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);
    queue->print_obj = print_num;

    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    for (i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->pop(queue, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(queue->pop(queue, &temp));
        }

        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->front(queue, &temp));
            TEST_ASSERT_FALSE(queue->back(queue, &temp));
        }
    }
    TEST_ASSERT_TRUE(queue->empty(queue));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_TRUE(queue->pop(queue, NULL));
    TEST_ASSERT_TRUE(queue->pop(queue, NULL));
    TEST_ASSERT_FALSE(queue->pop(queue, NULL));

    queue_free(&queue);
}

static void test_queue_front_invalid(void)
{
    queue_t queue = queue_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(queue->front(queue, NULL));
    queue_free(&queue);
}

static void test_queue_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);
    queue->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }

    iterator_t iter = queue->iter(queue);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    queue_free(&queue);
}

static void test_queue_resize(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    queue_t queue = queue_new(sizeof(int), len);

    TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
    TEST_ASSERT_TRUE(queue->resize(queue, 16));
    TEST_ASSERT_EQUAL_INT(16, queue->capacity(queue));

    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, queue->capacity(queue));
    TEST_ASSERT_EQUAL_INT(len, queue->size(queue));

    TEST_ASSERT_TRUE(queue->resize(queue, 8));
    TEST_ASSERT_EQUAL_INT(8, queue->capacity(queue));
    TEST_ASSERT_EQUAL_INT(8, queue->size(queue));

    TEST_ASSERT_TRUE(queue->front(queue, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(queue->back(queue, &temp));
    TEST_ASSERT_EQUAL_INT(data[7], temp);

    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(queue->pop(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->pop(queue, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, queue->capacity(queue));
    TEST_ASSERT_EQUAL_INT(0, queue->size(queue));

    queue_free(&queue);
}

static void test_queue_resize_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    queue_t queue = queue_new(sizeof(int), len);
    
    TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
    TEST_ASSERT_FALSE(queue->resize(queue, 0));
    TEST_ASSERT_FALSE(queue->resize(queue, -1));

    queue_free(&queue);
}

static void test_queue_resize_edge(void)
{
    queue_t queue = queue_new(sizeof(int), 10);

    TEST_ASSERT_EQUAL_INT(10, queue->capacity(queue));
    TEST_ASSERT_TRUE(queue->resize(queue, 10));
    TEST_ASSERT_EQUAL_INT(10, queue->capacity(queue));

    queue_free(&queue);
}

static void test_queue_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    queue_t queue = queue_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        
        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(queue->full(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        
        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(queue->full(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        
        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(queue->full(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));
        }
    }

    queue_free(&queue);
}

static void test_queue_status(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(int), len);
    queue->print_obj = print_num;

    TEST_ASSERT_EQUAL_INT(len, queue->capacity(queue));
    TEST_ASSERT_EQUAL_INT(0, queue->size(queue));

    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->full(queue));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));

        TEST_ASSERT_FALSE(queue->empty(queue));
        TEST_ASSERT_FALSE(queue->full(queue));
    }
    TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    TEST_ASSERT_TRUE(queue->full(queue));
    TEST_ASSERT_TRUE(queue->push(queue, &data[i]));

    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->full(queue));

    queue_free(&queue);   
}

static void test_queue_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = queue_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(queue);
    queue->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
    }
    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->pop(queue, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(queue->pop(queue, &temp));
        }
        
        if(!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[i + 1].name, temp.name);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[len - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->front(queue, &temp));
            TEST_ASSERT_FALSE(queue->back(queue, &temp));
        }
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    
    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}


void test_queue(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_queue_new);
    RUN_TEST(test_queue_new_lazy);

    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_push_invalid);

    RUN_TEST(test_queue_pop);

    RUN_TEST(test_queue_back);
    RUN_TEST(test_queue_back_invalid);

    RUN_TEST(test_queue_front);
    RUN_TEST(test_queue_front_invalid);

    RUN_TEST(test_queue_iter);

    RUN_TEST(test_queue_resize);
    RUN_TEST(test_queue_resize_invalid);
    RUN_TEST(test_queue_resize_edge);

    RUN_TEST(test_queue_dynamic);

    // ---------- base ----------
    RUN_TEST(test_queue_status);

    // ---------- ext ----------
    RUN_TEST(test_queue_struct);
}
