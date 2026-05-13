/**
 * @file perf_log.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _PERF_LOG_H_
#define _PERF_LOG_H_

#include "unicstl.h"

typedef struct _log_args{
    char name[32];
    // const char *name;   // function name is const char *
    double elapsed;
    size_t id;
}log_args_t;


bool perf_log_new(void);
void perf_log_free(void);

bool perf_log_append(const char *name, size_t id, double time_ms);
bool perf_log_clear(void);

bool perf_log_print(void);

#endif
