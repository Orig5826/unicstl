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

#define PERF_FORMAT_HEAD        "%-24s %-4s %-6s %-12s\n"
#define PERF_FORMAT_DATA        "%-24s T%-3d %-6d %8.3f ms\n"

void perf_init(void)
{
    printf(PERF_FORMAT_HEAD, "function", " id ",  " loop", "  time(ms)");
    printf(PERF_FORMAT_HEAD, "--------", "----", "------", "------------");
}

void perf_begin(struct _perf_args* args)
{
    timespec_get(&args->start, TIME_UTC);
}

double calc_elapsed(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void perf_end(struct _perf_args* args)
{
    timespec_get(&args->end, TIME_UTC);

    args->elapsed = calc_elapsed(args->start, args->end);
    printf(PERF_FORMAT_DATA, args->name, args->id, 1,  1000 * args->elapsed);
}

void perf_print(struct _perf_args* args)
{

}



#if 0
void perf_run_avg(perf_func_t perf_func, const char *func_name, size_t count)
{
    double time_used = 0;
    double time_total = 0;

    for(size_t i = 0; i < count; i++)
    {
        perf_start();
        perf_func();
        perf_end();

        time_used = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_nsec - time_start.tv_nsec) / 1e9;
        time_total += time_used;
    }
    printf(PERF_FORMAT_DATA, func_name, "AVG", 1, 1000 * time_total/count);
}

void perf_run_loop(perf_func_t perf_func, const char *func_name, size_t loop)
{
    double time_used = 0;

    perf_start();
    for(size_t i = 0; i < loop; i++)
    {
        perf_func();
    }
    perf_end();

    time_used = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_nsec - time_start.tv_nsec) / 1e9;
    printf(PERF_FORMAT_DATA, func_name, "LOOP", loop, 1000 * time_used);
}
#endif
