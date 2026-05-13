/**
 * @file main.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "perf.h"
#include "perf_log.h"

test_obj_t test_plans[PERF_TEST_TIEMS] = {
    {.capacity = 1024, .obj_size = 256},  // 1. 小对象 + 少量数据
    {.capacity = 4096, .obj_size = 256},  // 2. 小对象 + 中等数据
    {.capacity = 8192, .obj_size = 256},  // 3. 小对象 + 大量数据
    {.capacity = 1024, .obj_size = 4096}, // 4. 大对象 + 少量数据
    {.capacity = 4096, .obj_size = 4096}, // 5. 大对象 + 中等数据
    {.capacity = 8192, .obj_size = 4096}  // 6. 大对象 + 大量数据
};

test_obj_t g_test_obj;

static double calc_elapsed(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void perf_init(void)
{
    perf_log_new();
}

void perf_deinit(void)
{
    perf_log_free();
}

void perf_begin(struct _perf_args* args)
{
    timespec_get(&args->start, TIME_UTC);
}

void perf_end(struct _perf_args* args)
{
    timespec_get(&args->end, TIME_UTC);
    args->elapsed = calc_elapsed(args->start, args->end);

    perf_log_append(args->name, args->id, args->elapsed * 1000);
}

void perf_run_start(size_t id)
{
    unicstl_assert(id < PERF_TEST_TIEMS);

    g_test_obj.capacity = test_plans[id].capacity;
    g_test_obj.obj_size = test_plans[id].obj_size;

    g_test_obj.obj = malloc(g_test_obj.capacity);
    if(g_test_obj.obj == NULL)
    {
        LOG_DEBUG("malloc failed");
        return;
    }
}

void perf_run_end(size_t id)
{
    free(g_test_obj.obj);
}

void perf_print(void)
{
    for(size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        printf("T%d: capacity = %zu, obj_size = %zu\n", i, test_plans[i].capacity, test_plans[i].obj_size);
    }
    printf("\n");
    perf_log_print();
    perf_log_clear();
}

int main(int argc, char *argv[])
{
    perf_init();

    perf_test_deque();
    perf_test_stack();
    perf_test_queue();

    perf_print();
    perf_deinit();
    return 0;
}
