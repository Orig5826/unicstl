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


static void test_stack_new(void)
{
    stack_t stack = NULL;
    // ------------------------------
    stack = stack_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(stack);
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);

    // ------------------------------
    stack = stack_new2(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(stack);
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);

    // ------------------------------
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

static void test_stack_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    stack_t stack = NULL;

    // ------------------------------
    stack = stack_new(sizeof(int));
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
    stack = stack_new2(sizeof(int), len);
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
    stack = stack_new2(sizeof(int), len - 2);
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
    stack = stack_new(sizeof(int));
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
    stack = stack_new2(sizeof(int), len);
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
    stack = stack_new2(sizeof(int), len - 2);
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
    stack = stack_new(sizeof(int));
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
    stack = stack_new2(sizeof(int), len);
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
    stack = stack_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_num;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    TEST_ASSERT_TRUE(stack->clear(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
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
    }
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->pop(stack, &temp));

    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

static void test_stack_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    stack_t stack = stack_new(sizeof(struct _student));
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_struct;
 
    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    TEST_ASSERT_TRUE(stack->clear(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);
    }

    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
    }

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[stack->size(stack) - 1].name, temp.name);

        TEST_ASSERT_TRUE(stack->pop(stack, &temp));

        if (!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[stack->size(stack) - 1].name, temp.name);
        }
    }
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->pop(stack, &temp));
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}


static void test_stack2_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len;

    stack_t stack = NULL;
    stack = stack_new2(sizeof(int), capacity);
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_num;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    TEST_ASSERT_TRUE(stack->clear(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
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
    }
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->pop(stack, &temp));

    stack_free(&stack);
    TEST_ASSERT_NULL(stack);    
}

static void test_stack2_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;
    uint32_t capacity = len - 2;

    stack_t stack = NULL;
    stack = stack_new2(sizeof(struct _student), capacity);
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_struct;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[stack->size(stack) - 1].name, temp.name);
    }

    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }

    for(i = 0; i < len; i++)
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
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[stack->size(stack) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

static void test_stack2_iter(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len;

    stack_t stack = NULL;
    stack = stack_new2(sizeof(int), capacity);
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_num;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    TEST_ASSERT_TRUE(stack->clear(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    iterator_t iter = stack->iter(stack);
    TEST_ASSERT_NOT_NULL(iter);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        printf("%d ", temp);
        TEST_ASSERT_EQUAL_INT(data[len - 1 - i], temp);
        i++;
    }
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

void test_stack(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_stack_new);
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_clear);

    RUN_TEST(test_stack_num);
    RUN_TEST(test_stack_struct);

    RUN_TEST(test_stack2_num);
    RUN_TEST(test_stack2_struct);

    RUN_TEST(test_stack2_iter);
}
