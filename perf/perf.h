/**
 * @file perf.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _PERF_H_
#define _PERF_H_

#include "unicstl.h"
#include <time.h>

typedef void (*perf_func_t)(void);

struct _perf_args
{
    size_t id;

    const char *name;
    struct timespec start;  // [C11]
    struct timespec end;    // [C11]
    double elapsed;
};

/**
 * @brief initialize the performance test
 *
 */
#define PERF_INIT() perf_init()

/**
 * @brief run the performance test function
 *
 */
#define RUN_PERF(ID, func) do{\
    struct _perf_args args = {\
        .id = ID, \
        .name = #func, \
        .start = {0}, \
        .end = {0}, \
        .elapsed = 0, \
    };\
    perf_begin(&args); \
    (func); \
    perf_end(&args); \
}while(0)

#define RUN_PERF_T1(func) RUN_PERF(1, func)
#define RUN_PERF_T2(func) RUN_PERF(2, func)
#define RUN_PERF_T3(func) RUN_PERF(3, func)

/**
 * @brief print the performance test result
 *
 */
void perf_init(void);
void perf_begin(struct _perf_args* args);
void perf_end(struct _perf_args* args);

/**
 * @brief perf test items
 *
 */
void perf_deque(void);

#endif // !_PERF_H_
