/**
 * @file test_stack.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

static void test_stack_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = NULL;
    stack = stack_new();
    TEST_ASSERT_TRUE(stack_init(stack, sizeof(int)));
    stack->print_obj = print_num;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));

    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
        stack->peek(stack, &temp);
    }

    for (i = 0; i < len + 1; i++)
    {
        if (true == stack->pop(stack, &temp))
        {
            if(false != stack->peek(stack, &temp))
            {
                TEST_ASSERT_EQUAL(data[len - 2 - i], temp);
            }
        }
    }
    TEST_ASSERT_TRUE(stack->empty(stack));

    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

void test_stack(void)
{
    RUN_TEST(test_stack_num);
}
