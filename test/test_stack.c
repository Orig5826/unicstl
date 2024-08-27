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

    struct _stack s;
    TEST_ASSERT_TRUE(stack_init(&s, sizeof(int)));
    s.print_obj = print_num;

    TEST_ASSERT_FALSE(s.peek(&s, &temp));

    for (i = 0; i < len; i++)
    {
        s.push(&s, &data[i]);
        s.peek(&s, &temp);
    }

    for (i = 0; i < len + 1; i++)
    {
        if (true == s.pop(&s, &temp))
        {
            if(false != s.peek(&s, &temp))
            {
                TEST_ASSERT_EQUAL(data[len - 2 - i], temp);
            }
        }
    }
    TEST_ASSERT_TRUE(s.empty(&s));

    s.destory(&s);
}

void test_stack(void)
{
    RUN_TEST(test_stack_num);
}
