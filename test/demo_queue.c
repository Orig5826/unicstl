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

static void test_queue_destory(void)
{
    queue_t queue = NULL;
    queue = queue_new();
    TEST_ASSERT_TRUE(queue_init(queue, sizeof(int)));
    TEST_ASSERT_NOT_NULL(queue);

    queue_free(&queue);
    TEST_ASSERT_NULL(queue);
}

void test_queue(void)
{
    RUN_TEST(test_queue_destory);
}
