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
    size_t run_count;
};

typedef struct _test_obj
{
    void *obj;
    size_t obj_size;
    size_t capacity;
    size_t run_count;
}test_obj_t;

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
        .run_count = g_test_obj.run_count,\
    };\
    perf_begin(&args); \
    (func); \
    perf_end(&args); \
}while(0)

#define PERF_ADD(ID, func) do{\
    perf_run_start(ID); \
    func(ID); \
    perf_run_end(ID); \
}while(0)

#define PERF_TEST_TIEMS            8
extern test_obj_t g_test_obj;

/**
 * @brief print the performance test result
 *
 */
void perf_init(void);
void perf_deinit(void);

void perf_begin(struct _perf_args* args);
void perf_end(struct _perf_args* args);

void perf_run_start(size_t id);
void perf_run_end(size_t id);

void perf_print(void);

/**
 * @brief perf test items
 *
 */
void perf_test_segarray(void);
void perf_test_ringbuf(void);

void perf_test_deque(void);
void perf_test_stack(void);
void perf_test_queue(void);

#endif // !_PERF_H_
