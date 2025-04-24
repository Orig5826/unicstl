/**
 * @file demo_queue->c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

static void test_queue_new(void)
{
    queue_t queue = NULL;
    queue = queue_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(queue);
    queue_free(&queue);

    TEST_ASSERT_NULL(queue_new(0));

    // ------------------------------
    queue = queue_new2(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(queue);
    queue_free(&queue);
    
    TEST_ASSERT_NULL(queue_new2(0, 0));
    TEST_ASSERT_NULL(queue_new2(0, 1));
    TEST_ASSERT_NULL(queue_new2(sizeof(int), 0));

    // ------------------------------
    TEST_ASSERT_NULL(queue);
    queue_free(&queue);
}

static void test_queue_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    queue_t queue = NULL;

    // ------------------------------
    queue = queue_new(sizeof(int));

    TEST_ASSERT_TRUE(queue->empty(queue));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(queue->empty(queue));
    }
    queue_free(&queue);

    // ------------------------------
    queue = queue_new2(sizeof(int), len);

    TEST_ASSERT_TRUE(queue->empty(queue));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(queue->empty(queue));
    }
    queue_free(&queue);

    // ------------------------------
    // if capacity is less than data len
    queue = queue_new2(sizeof(int), len - 2);

    for(i = 0; i < len; i++)
    {
        if(i < queue->capacity(queue))
        {
            TEST_ASSERT_FALSE(queue->full(queue));

            TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));

            TEST_ASSERT_FALSE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(queue->capacity(queue), queue->size(queue));
        }
    }
    queue_free(&queue);
}

static void test_queue_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    queue_t queue = NULL;

    // ------------------------------
    queue = queue_new(sizeof(int));

    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(queue->pop(queue, &temp));

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

        TEST_ASSERT_FALSE(queue->full(queue));
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->pop(queue, &temp));
    queue_free(&queue);

    // ------------------------------
    queue = queue_new2(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_TRUE(queue->full(queue));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(queue->pop(queue, &temp));

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

        TEST_ASSERT_FALSE(queue->full(queue));
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->pop(queue, &temp));
    queue_free(&queue);

    // ------------------------------
    // if capacity is less than data len
    queue = queue_new2(sizeof(int), len - 2);

    for(i = 0; i < len; i++)
    {
        if(i < queue->capacity(queue))
        {
            TEST_ASSERT_FALSE(queue->full(queue));

            TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));

            TEST_ASSERT_FALSE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(queue->capacity(queue), queue->size(queue));
        }
    }
    TEST_ASSERT_TRUE(queue->full(queue));
    uint32_t capacity = queue->capacity(queue);
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
            TEST_ASSERT_EQUAL_INT(data[capacity - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->pop(queue, &temp));

            TEST_ASSERT_FALSE(queue->front(queue, &temp));
            TEST_ASSERT_FALSE(queue->back(queue, &temp));
        }

        TEST_ASSERT_FALSE(queue->full(queue));
    }
    queue_free(&queue);
}


static void test_queue_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    queue_t queue = NULL;

    // ------------------------------
    queue = queue_new(sizeof(int));

    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_TRUE(queue->clear(queue));
    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    queue_free(&queue);

    // ------------------------------
    queue = queue_new2(sizeof(int), len);

    TEST_ASSERT_TRUE(queue->clear(queue));
    for(i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }
    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    queue_free(&queue);
}


static void test_queue_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = NULL;
    queue = queue_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(queue);

    queue->print_obj = print_num;

    TEST_ASSERT_TRUE(queue->clear(queue));

    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    TEST_ASSERT_FALSE(queue->back(queue, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(queue->pop(queue, &temp));

        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            // TEST_PRINTF("front = %d", temp);
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->pop(queue, &temp));

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

static void test_queue_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    queue_t queue = queue_new(sizeof(struct _student));
    TEST_ASSERT_NOT_NULL(queue);

    queue->print_obj = print_struct;

    TEST_ASSERT_TRUE(queue->clear(queue));

    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    TEST_ASSERT_FALSE(queue->back(queue, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);
    }

    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    }

    // while (!queue->empty(queue))
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[len - 1].name, temp.name);

        TEST_ASSERT_TRUE(queue->pop(queue, &temp));

        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[i + 1].name, temp.name);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[len - 1].name, temp.name);
        }
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->pop(queue, &temp));
    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

static void test_queue2_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len;

    queue_t queue = NULL;
    queue = queue_new2(sizeof(int), capacity);
    TEST_ASSERT_NOT_NULL(queue);

    queue->print_obj = print_num;

    TEST_ASSERT_TRUE(queue->clear(queue));

    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    TEST_ASSERT_FALSE(queue->back(queue, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(queue->pop(queue, &temp));

        if (!queue->empty(queue))
        {
            TEST_ASSERT_TRUE(queue->front(queue, &temp));
            // TEST_PRINTF("front = %d", temp);
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->pop(queue, &temp));

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

static void test_queue2_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;
    uint32_t capacity = len - 2;

    queue_t queue = NULL;
    queue = queue_new2(sizeof(struct _student), capacity);
    TEST_ASSERT_NOT_NULL(queue);

    queue->print_obj = print_struct;

    TEST_ASSERT_TRUE(queue->empty(queue));
    TEST_ASSERT_FALSE(queue->full(queue));
    TEST_ASSERT_FALSE(queue->front(queue, &temp));
    TEST_ASSERT_FALSE(queue->back(queue, &temp));

    for (i = 0; i < len; i++)
    {
        if(i < queue->capacity(queue))
        {
            TEST_ASSERT_FALSE(queue->full(queue));

            TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        }
        else
        {
            TEST_ASSERT_TRUE(queue->full(queue));

            TEST_ASSERT_FALSE(queue->push(queue, &data[i]));
        }

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[queue->size(queue) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[queue->size(queue) - 1].name, temp.name);
    }

    TEST_ASSERT_FALSE(queue->empty(queue));
    TEST_ASSERT_TRUE(queue->clear(queue));
    TEST_ASSERT_TRUE(queue->empty(queue));
    for (i = 0; i < len; i++)
    {
        if(i < queue->capacity(queue))
        {
            TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
            TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));
        }
        else
        {
            TEST_ASSERT_FALSE(queue->push(queue, &data[i]));
        }
    }

    for(i = 0; i < len; i++)
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
            TEST_ASSERT_EQUAL_INT(data[i + 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[i + 1].name, temp.name);

            TEST_ASSERT_TRUE(queue->back(queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[queue->capacity(queue) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[queue->capacity(queue) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(queue->front(queue, &temp));
            TEST_ASSERT_FALSE(queue->back(queue, &temp));
        }

        TEST_ASSERT_FALSE(queue->full(queue));
    }
    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}


static void test_queue_iter(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = NULL;
    queue = queue_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(queue);
    queue->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    iterator_t iter = queue->iter(queue);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        // printf("%d ", temp);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}


static void test_queue2_iter(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len;

    queue_t queue = NULL;
    queue = queue_new2(sizeof(int), capacity);
    TEST_ASSERT_NOT_NULL(queue);
    queue->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue->size(queue));

        TEST_ASSERT_TRUE(queue->front(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(queue->back(queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    iterator_t iter = queue->iter(queue);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

void test_queue(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_queue_new);
    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_pop);
    RUN_TEST(test_queue_clear);

    RUN_TEST(test_queue_num);
    RUN_TEST(test_queue_struct);

    RUN_TEST(test_queue2_num);
    RUN_TEST(test_queue2_struct);

    RUN_TEST(test_queue_iter);
    RUN_TEST(test_queue2_iter);
}
