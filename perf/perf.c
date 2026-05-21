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

// clang-format off
test_obj_t test_plans[PERF_TEST_TIEMS] = {
    {.obj_size = 256,  .capacity = 1024, .run_count = 1024, },      // 1. 小对象 + 少量数据
    {.obj_size = 256,  .capacity = 8192, .run_count = 8192, },      // 2. 小对象 + 大量数据
    {.obj_size = 4096, .capacity = 1024, .run_count = 1024, },      // 3. 大对象 + 少量数据
    {.obj_size = 4096, .capacity = 8192, .run_count = 8192, },      // 4. 大对象 + 大量数据

    {.obj_size = 256,  .capacity = 1024, .run_count = 100000, },    // 1. 小对象 + 少量数据 + 扩容
    {.obj_size = 256,  .capacity = 8192, .run_count = 100000, },    // 2. 小对象 + 大量数据 + 扩容
    {.obj_size = 4096, .capacity = 1024, .run_count = 100000, },    // 3. 大对象 + 少量数据 + 扩容
    {.obj_size = 4096, .capacity = 8192, .run_count = 100000, },    // 4. 大对象 + 大量数据 + 扩容
};
// clang-format on

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

void perf_begin(struct _perf_args *args)
{
    timespec_get(&args->start, TIME_UTC);
}

void perf_end(struct _perf_args *args)
{
    timespec_get(&args->end, TIME_UTC);
    args->elapsed = calc_elapsed(args->start, args->end);

    // printf("run_count = %zu, elapsed = %.3f ms\n", args->run_count, args->elapsed * 1000);
    // perf_log_append(args->name, args->id, args->elapsed * 1000);
    perf_log_append(args->name, args->id, args->elapsed * 1000*1000 / args->run_count);
}

void perf_run_start(size_t id)
{
    unicstl_assert(id < PERF_TEST_TIEMS);

    g_test_obj.capacity = test_plans[id].capacity;
    g_test_obj.obj_size = test_plans[id].obj_size;
    g_test_obj.run_count = test_plans[id].run_count;

    g_test_obj.obj = unicstl_malloc(g_test_obj.capacity);
    if (g_test_obj.obj == NULL)
    {
        log_debug("unicstl_malloc failed");
        return;
    }
}

void perf_run_end(size_t id)
{
    unicstl_free(g_test_obj.obj);
}

void perf_print(void)
{
    for (size_t i = 0; i < PERF_TEST_TIEMS; i++)
    {
        printf("T%d: obj_size=%zu, capacity=%zu, run_count=%zu\n", i,
               test_plans[i].obj_size, test_plans[i].capacity, test_plans[i].run_count);
    }
    printf("\n");
    perf_log_print();
    perf_log_clear();
}

int main(int argc, char *argv[])
{
    perf_init();

    perf_test_segarray();
    perf_test_ringbuf();

    // perf_test_deque();
    // perf_test_stack();
    // perf_test_queue();

    perf_print();
    perf_deinit();
    return 0;
}
