/**
 * @file perf_queue.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "perf.h"

static queue_t queue = NULL;

void perf_queue_new(void)
{
    // queue = queue_new2(g_test_obj.obj_size, g_test_obj.capacity);
    queue = queue_new(g_test_obj.obj_size);
}

void perf_queue_push(void)
{
    for (size_t i = 0; i < g_test_obj.capacity; i++)
    {
        queue->push(queue, &g_test_obj.obj);
    }
}

void perf_queue_pop(void)
{
    for (size_t i = 0; i < g_test_obj.capacity; i++)
    {
        queue->pop(queue, &g_test_obj.obj);
    }
}

void perf_queue_free(void)
{
    queue_free(&queue);
}

void perf_queue(size_t id)
{
    RUN_PERF(id, perf_queue_new());
    RUN_PERF(id, perf_queue_push() );
    RUN_PERF(id, perf_queue_pop() );
    RUN_PERF(id, perf_queue_free() );
}

void perf_test_queue(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        PERF_ADD(i, perf_queue);
    }
}
