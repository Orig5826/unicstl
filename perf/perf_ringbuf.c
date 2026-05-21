/**
 * @file perf_ringbuf.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "perf.h"

static ringbuf_t ringbuf = NULL;

void perf_ringbuf_new(void)
{
    ringbuf = ringbuf_new(g_test_obj.obj_size, g_test_obj.capacity);
}

void perf_ringbuf_push_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        ringbuf->push_back(ringbuf, &g_test_obj.obj);
    }
}

void perf_ringbuf_pop_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        ringbuf->pop_back(ringbuf, &g_test_obj.obj);
    }
}

void perf_ringbuf_push_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        ringbuf->push_front(ringbuf, &g_test_obj.obj);
    }
}

void perf_ringbuf_pop_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        ringbuf->pop_front(ringbuf, &g_test_obj.obj);
    }
}

void perf_ringbuf_free(void)
{
    ringbuf_free(&ringbuf);
}

void perf_ringbuf(size_t id)
{
    RUN_PERF(id, perf_ringbuf_new());
    RUN_PERF(id, perf_ringbuf_push_back() );
    RUN_PERF(id, perf_ringbuf_pop_back() );
    RUN_PERF(id, perf_ringbuf_free() );

    RUN_PERF(id, perf_ringbuf_new());
    RUN_PERF(id, perf_ringbuf_push_front() );
    RUN_PERF(id, perf_ringbuf_pop_front() );
    RUN_PERF(id, perf_ringbuf_free() );
}

void perf_test_ringbuf(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        PERF_ADD(i, perf_ringbuf);
    }
}
