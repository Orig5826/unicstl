/**
 * @file demo_queue.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

static void test_queue_init(void)
{
    queue_t queue = NULL;

    // queue_init
    queue = queue_new();
    TEST_ASSERT_NOT_NULL(queue);

    TEST_ASSERT_TRUE(queue_init(queue, sizeof(int)));
    // TEST_ASSERT_NULL(queue);

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);

    // queue_init2
    queue = queue_new();
    TEST_ASSERT_TRUE(queue_init2(queue, sizeof(int), 10));
    TEST_ASSERT_NOT_NULL(queue->front);

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

static void test_queue_clear(void)
{
    queue_t queue = NULL;
    queue = queue_new();
    TEST_ASSERT_TRUE(queue_init(queue, sizeof(int)));
    // TEST_ASSERT_NULL(queue);

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);    
}


static void test_queue_init_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    struct _queue queue;
    TEST_ASSERT_TRUE(queue_init(&queue, sizeof(int)));
    queue.print_obj = print_num;

    TEST_ASSERT_TRUE(queue.clear(&queue));

    TEST_ASSERT_FALSE(queue.front(&queue, &temp));
    TEST_ASSERT_FALSE(queue.back(&queue, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue.push(&queue, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, queue.size(&queue));

        TEST_ASSERT_TRUE(queue.front(&queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);
        
        TEST_ASSERT_TRUE(queue.back(&queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_TRUE(queue.clear(&queue));
    TEST_ASSERT_TRUE(queue.empty(&queue));  //?
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue.push(&queue, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(queue.front(&queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(queue.back(&queue, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(queue.pop(&queue, &temp));

        if(!queue.empty(&queue))
        {
            TEST_ASSERT_TRUE(queue.front(&queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(queue.back(&queue, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(queue.empty(&queue));
    TEST_ASSERT_FALSE(queue.pop(&queue, &temp));
    queue.destory(&queue);
}


void test_queue(void)
{
    // TEST_MESSAGE("----- test_queue -----");
    RUN_TEST(test_queue_init);
    RUN_TEST(test_queue_init_num);
}
