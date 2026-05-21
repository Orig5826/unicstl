/**
 * @file perf_segarray.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "perf.h"

static segarray_t segarray = NULL;

void perf_segarray_new(void)
{
    segarray = segarray_new(g_test_obj.obj_size, g_test_obj.capacity);
}

void perf_segarray_push_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        segarray->push_back(segarray, &g_test_obj.obj);
    }
}

void perf_segarray_pop_back(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        segarray->pop_back(segarray, &g_test_obj.obj);
    }
}

void perf_segarray_push_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        segarray->push_front(segarray, &g_test_obj.obj);
    }
}

void perf_segarray_pop_front(void)
{
    for (size_t i = 0; i < g_test_obj.run_count; i++)
    {
        segarray->pop_front(segarray, &g_test_obj.obj);
    }
}

void perf_segarray_free(void)
{
    segarray_free(&segarray);
}

void perf_segarray(size_t id)
{
    RUN_PERF(id, perf_segarray_new());
    RUN_PERF(id, perf_segarray_push_back() );
    RUN_PERF(id, perf_segarray_pop_back() );
    RUN_PERF(id, perf_segarray_free() );

    RUN_PERF(id, perf_segarray_new());
    RUN_PERF(id, perf_segarray_push_front() );
    RUN_PERF(id, perf_segarray_pop_front() );
    RUN_PERF(id, perf_segarray_free() );
}

void perf_test_segarray(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        PERF_ADD(i, perf_segarray);
    }
}
