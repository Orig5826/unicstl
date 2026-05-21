/**
 * @file perf_deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "perf.h"

static deque_t deque = NULL;

void perf_deque_new(void)
{
    deque = deque_new(g_test_obj.obj_size, g_test_obj.capacity);
}

void perf_deque_push_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        deque->push_back(deque, &g_test_obj.obj);
    }
}

void perf_deque_pop_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        deque->pop_back(deque, &g_test_obj.obj);
    }
}

void perf_deque_push_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        deque->push_front(deque, &g_test_obj.obj);
    }
}

void perf_deque_pop_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        deque->pop_front(deque, &g_test_obj.obj);
    }
}

void perf_deque_free(void)
{
    deque_free(&deque);
}

void perf_deque(size_t id)
{
    RUN_PERF(id, perf_deque_new());
    RUN_PERF(id, perf_deque_push_back() );
    RUN_PERF(id, perf_deque_pop_back() );
    RUN_PERF(id, perf_deque_free() );

    RUN_PERF(id, perf_deque_new());
    RUN_PERF(id, perf_deque_push_front() );
    RUN_PERF(id, perf_deque_pop_front() );
    RUN_PERF(id, perf_deque_free() );
}

void perf_test_deque(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        PERF_ADD(i, perf_deque);
    }

    // perf_print();
}
