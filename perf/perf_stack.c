/**
 * @file perf_stack.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "perf.h"

static stack_t stack = NULL;

void perf_stack_new(void)
{
    stack = stack_new(g_test_obj.obj_size, g_test_obj.capacity);
}

void perf_stack_push(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        stack->push(stack, &g_test_obj.obj);
    }
}

void perf_stack_pop(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        stack->pop(stack, &g_test_obj.obj);
    }
}

void perf_stack_free(void)
{
    stack_free(&stack);
}

void perf_stack(size_t id)
{
    RUN_PERF(id, perf_stack_new());
    RUN_PERF(id, perf_stack_push() );
    RUN_PERF(id, perf_stack_pop() );
    RUN_PERF(id, perf_stack_free() );
}

void perf_test_stack(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        PERF_ADD(i, perf_stack);
    }
    // perf_print();
}
