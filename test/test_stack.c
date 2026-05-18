/**
 * @file test_stack.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_stack_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(stack_new(0, 0));
    // TEST_ASSERT_NULL(stack_new(0, 1));

    stack_t stack = stack_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(stack);
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}

static void test_stack_new_lazy(void)
{
    stack_t stack = stack_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_size_t(0, stack->capacity(stack));

    int temp = 0;
    TEST_ASSERT_TRUE(stack->push(stack, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, stack->capacity(stack));
    stack_free(&stack);
}

static void test_stack_push(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(int), len);
    stack->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }
    TEST_ASSERT_TRUE(stack->push(stack, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 1, stack->size(stack));

    stack_free(&stack);
}

static void test_stack_push_invalid(void)
{
    stack_t stack = stack_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(stack->push(stack, NULL));
    stack_free(&stack);
}

static void test_stack_pop(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(int), len);
    stack->print_obj = print_num;

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }

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
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    TEST_ASSERT_TRUE(stack->empty(stack));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        stack->push(stack, &data[i]);
    }
    TEST_ASSERT_TRUE(stack->pop(stack, NULL));
    TEST_ASSERT_TRUE(stack->pop(stack, NULL));
    TEST_ASSERT_FALSE(stack->pop(stack, NULL));

    stack_free(&stack);
}

static void test_stack_peek(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(int), len);

    TEST_ASSERT_FALSE(stack->peek(stack, &temp));
    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        stack->pop(stack, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    stack_free(&stack);
}

static void test_stack_peek_invalid(void)
{
    stack_t stack = stack_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(stack->peek(stack, NULL));
    stack_free(&stack);
}

static void test_stack_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(int), len);
    stack->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }

    iterator_t iter = stack->iter(stack);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    stack_free(&stack);
}

static void test_stack_reserve(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    stack_t stack = stack_new(sizeof(int), len);

    TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
    TEST_ASSERT_TRUE(stack->reserve(stack, 16));
    TEST_ASSERT_EQUAL_INT(16, stack->capacity(stack));

    for(i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, stack->capacity(stack));
    TEST_ASSERT_EQUAL_INT(len, stack->size(stack));

    TEST_ASSERT_TRUE(stack->reserve(stack, 8));
    TEST_ASSERT_EQUAL_INT(8, stack->capacity(stack));
    TEST_ASSERT_EQUAL_INT(8, stack->size(stack));

    TEST_ASSERT_TRUE(stack->peek(stack, &temp));
    TEST_ASSERT_EQUAL_INT(data[7], temp);

    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(stack->pop(stack, &temp));
            TEST_ASSERT_EQUAL_INT(data[7 - i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->pop(stack, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, stack->capacity(stack));
    TEST_ASSERT_EQUAL_INT(0, stack->size(stack));

    stack_free(&stack);
}

static void test_stack_reserve_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    stack_t stack = stack_new(sizeof(int), len);
    
    TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
    TEST_ASSERT_FALSE(stack->reserve(stack, 0));
    TEST_ASSERT_FALSE(stack->reserve(stack, -1));

    stack_free(&stack);
}

static void test_stack_reserve_edge(void)
{
    stack_t stack = stack_new(sizeof(int), 10);

    TEST_ASSERT_EQUAL_INT(10, stack->capacity(stack));
    TEST_ASSERT_TRUE(stack->reserve(stack, 10));
    TEST_ASSERT_EQUAL_INT(10, stack->capacity(stack));

    stack_free(&stack);
}

static void test_stack_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    stack_t stack = stack_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
        
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(stack->full(stack));
        }
        else
        {
            TEST_ASSERT_TRUE(stack->full(stack));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
        
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(stack->full(stack));
        }
        else
        {
            TEST_ASSERT_TRUE(stack->full(stack));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
        
        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(stack->full(stack));
        }
        else
        {
            TEST_ASSERT_TRUE(stack->full(stack));
        }
    }

    stack_free(&stack);
}

static void test_stack_status(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(int), len);
    stack->print_obj = print_num;

    TEST_ASSERT_EQUAL_INT(len, stack->capacity(stack));
    TEST_ASSERT_EQUAL_INT(0, stack->size(stack));

    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->full(stack));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));

        TEST_ASSERT_FALSE(stack->empty(stack));
        TEST_ASSERT_FALSE(stack->full(stack));
    }
    TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
    TEST_ASSERT_TRUE(stack->full(stack));
    TEST_ASSERT_TRUE(stack->push(stack, &data[i]));

    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    TEST_ASSERT_FALSE(stack->full(stack));

    stack_free(&stack);   
}

static void test_stack_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack = stack_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(stack);
    stack->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }
    TEST_ASSERT_FALSE(stack->empty(stack));
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->pop(stack, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(stack->pop(stack, &temp));
        }
        
        if(!stack->empty(stack))
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

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));

        TEST_ASSERT_TRUE(stack->peek(stack, &temp));
        TEST_ASSERT_EQUAL_INT(data[stack->size(stack) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[stack->size(stack) - 1].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, stack->size(stack));
    }
    TEST_ASSERT_TRUE(stack->clear(stack));
    TEST_ASSERT_TRUE(stack->empty(stack));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(stack->push(stack, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->pop(stack, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(stack->pop(stack, &temp));
        }
        
        if(!stack->empty(stack))
        {
            TEST_ASSERT_TRUE(stack->peek(stack, &temp));
            size_t idx = stack->size(stack) - 1;
            TEST_ASSERT_EQUAL_INT(data[idx].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[idx].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(stack->peek(stack, &temp));
        }
    }
    stack_free(&stack);
    TEST_ASSERT_NULL(stack);
}


void test_stack(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_stack_new);
    RUN_TEST(test_stack_new_lazy);

    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_push_invalid);

    RUN_TEST(test_stack_pop);

    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_peek_invalid);

    RUN_TEST(test_stack_iter);

    RUN_TEST(test_stack_reserve);
    RUN_TEST(test_stack_reserve_invalid);
    RUN_TEST(test_stack_reserve_edge);

    RUN_TEST(test_stack_dynamic);

    // ---------- base ----------
    RUN_TEST(test_stack_status);

    // ---------- ext ----------
    RUN_TEST(test_stack_struct);
}
