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


static void test_stack_init(void)
{
    struct _stack stack;

    // ------------------------------
#ifdef NDEBUG
    TEST_ASSERT_FALSE(stack_init(NULL, sizeof(int)));
    TEST_ASSERT_FALSE(stack_init(&stack, 0));
#endif
    TEST_ASSERT_TRUE(stack_init(&stack, sizeof(int)));
    stack.destory(&stack);

    // ------------------------------
#ifdef NDEBUG
    TEST_ASSERT_FALSE(stack_init2(NULL, sizeof(int), 1));
    TEST_ASSERT_FALSE(stack_init2(&stack, 0, 1));
    TEST_ASSERT_FALSE(stack_init2(&stack, sizeof(int), 0));
#endif
    TEST_ASSERT_TRUE(stack_init2(&stack, sizeof(int), 1));
    stack.destory(&stack);
}

static void test_stack_new(void)
{
    stack_t stack = NULL;
    stack = stack_new();
    stack_free(&stack);

    // ------------------------------
    stack = stack_new();
    TEST_ASSERT_NOT_NULL(stack);

#ifdef NDEBUG
    TEST_ASSERT_FALSE(stack_init(NULL, sizeof(int)));
    TEST_ASSERT_FALSE(stack_init(stack, 0));
#endif
    TEST_ASSERT_TRUE(stack_init(stack, sizeof(int)));
    stack_free(&stack);

    // ------------------------------
    stack = stack_new();
    TEST_ASSERT_NOT_NULL(stack);

#ifdef NDEBUG
    TEST_ASSERT_FALSE(stack_init2(NULL, sizeof(int), 1));
    TEST_ASSERT_FALSE(stack_init2(stack, 0, 1));
    TEST_ASSERT_FALSE(stack_init2(stack, sizeof(int), 0));
#endif
    TEST_ASSERT_TRUE(stack_init2(stack, sizeof(int), 1));
    stack_free(&stack);

    TEST_ASSERT_NULL(stack);
    stack_free(&stack); // stack_free(NULL);
}

static void test_stack_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    stack_t stack = NULL;

    // ------------------------------
    stack = stack_new();
    stack_init(stack, sizeof(int));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(stack->empty(stack));
    }
    stack_free(&stack);

    // ------------------------------
    stack = stack_new();
    stack_init2(stack, sizeof(int), len);
    TEST_ASSERT_TRUE(stack->empty(stack));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(stack->empty(stack));
    }
    stack_free(&stack);

    // ------------------------------
    // if capacity is less than data len
    stack = stack_new();
    stack_init2(stack, sizeof(int), len - 2);
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }
    stack_free(&stack);
}

static void test_stack_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    stack_t stack = NULL;

    // ------------------------------
    stack = stack_new();
    stack_init(stack, sizeof(int));
    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);

        TEST_ASSERT_TRUE(stack->pop(stack, &temp));

        if (!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->pop(stack, &temp));
    stack_free(&stack);

    // ------------------------------
    stack = stack_new();
    stack_init2(stack, sizeof(int), len);
    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);

        TEST_ASSERT_TRUE(stack->pop(stack, &temp));

        if (!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->pop(stack, &temp));
    stack_free(&stack);

    // ------------------------------
    // if capacity is less than data len
    stack = stack_new();
    stack_init2(stack, sizeof(int), len - 2);
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }
    uint32_t capacity = stack->capacity(stack);
    for (i = 0; i < len; i++)
    {
        if (!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->pop(stack, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(stack->pop(stack, &temp));
        }

        if (!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->pop(stack, &temp));
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    stack_free(&stack);
}

static void test_stack_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    stack_t stack = NULL;

    // ------------------------------
    stack = stack_new();
    stack_init(stack, sizeof(int));
    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    TEST_ASSERT_TRUE(stack->clear(stack));
    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    stack_free(&stack);

    // ------------------------------
    stack = stack_new();
    stack_init2(stack, sizeof(int), len);
    TEST_ASSERT_TRUE(stack->clear(stack));
    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    stack_free(&stack);
}

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

static void test_stack_struct(void)
{

}


static void test_stack2_num(void)
{
    
}

static void test_stack2_struct(void)
{

}

void test_stack(void)
{
    RUN_TEST(test_stack_num);

    RUN_TEST(test_stack_init);
    RUN_TEST(test_stack_new);
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_clear);

    RUN_TEST(test_stack_num);
    RUN_TEST(test_stack_struct);

    RUN_TEST(test_stack2_num);
    RUN_TEST(test_stack2_struct);
}
