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
    queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);

    queue_free(NULL);
}

static void test_queue_init(void)
{
    queue_t queue = NULL;

    // ------------------------------
    queue = queue_new();
    TEST_ASSERT_TRUE(queue_init(queue, sizeof(int)));
    TEST_ASSERT_FALSE(queue_init(NULL, sizeof(int)));
    TEST_ASSERT_FALSE(queue_init(queue, 0));
    queue_free(&queue);

    // ------------------------------
    queue = queue_new();
    TEST_ASSERT_TRUE(queue_init2(queue, sizeof(int), 1));
    TEST_ASSERT_FALSE(queue_init2(NULL, sizeof(int),1 ));
    TEST_ASSERT_FALSE(queue_init2(queue, 0, 1));
    TEST_ASSERT_FALSE(queue_init2(queue, sizeof(int), 0));
    queue_free(&queue);

    queue_init2(queue, sizeof(int), 1);
}

static void test_queue_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    queue_t queue = NULL;

    // ------------------------------
    queue = queue_new();
    queue_init(queue, sizeof(int));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
    }
    queue_free(&queue);

    // ------------------------------
    queue = queue_new();
    queue_init2(queue, sizeof(int), 10);

    queue_free(&queue);
}



static void test_queue_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    queue_t queue = NULL;
    queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    TEST_ASSERT_TRUE(queue_init(queue, sizeof(int)));
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

    queue_t queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    queue_init(queue, sizeof(struct _student));
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
    queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    TEST_ASSERT_TRUE(queue_init2(queue, sizeof(int), capacity));
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

static void test_queue2_fifo_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len - 1;

    queue_t queue = NULL;
    queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    TEST_ASSERT_TRUE(queue_init2(queue, sizeof(int), capacity));

    for (i = 0; i < len; i++)
    {
        if (queue->size(queue) == capacity)
        {
            TEST_ASSERT_TRUE(queue->full(queue));
            TEST_ASSERT_FALSE(queue->push(queue, &data[i]));
        }
        else
        {
            TEST_ASSERT_FALSE(queue->full(queue));
            TEST_ASSERT_TRUE(queue->push(queue, &data[i]));
        }
    }
    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

void test_queue(void)
{
    // TEST_MESSAGE("----- test_queue -----");
    RUN_TEST(test_queue_new);
    RUN_TEST(test_queue_init);

    RUN_TEST(test_queue_num);
    RUN_TEST(test_queue_struct);

    RUN_TEST(test_queue2_num);
    RUN_TEST(test_queue2_fifo_num);
}
