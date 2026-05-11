/**
 * @file unicstl_internal.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#define UNICSTL_CONFIG

#ifdef UNICSTL_CONFIG
#include "unicstl_config.h"
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#ifdef UNICSTL_ITERATOR
#include "iterator.h"
#endif


/**
 * @brief default capacity and ratio
 * 
 */
#define DEFAULT_CAPACITY        8


/**
 * @brief malloc and free function
 * 
 */
#ifdef UNICSTL_MALLOC
static inline void * unicstl_malloc(size_t size) {
    return malloc(size);
}

static inline void * unicstl_realloc(void * ptr, size_t size) {
    return realloc(ptr, size);
}

static inline void unicstl_free(void * ptr) {
    free(ptr);
}
#else
#error "UNICSTL_MALLOC not defined"
#endif

#ifdef UNICSTL_ASSERT
#define unicstl_assert(expr) (void) ((!!(expr)) || (_unicstl_assert(#expr,__FILE__,__LINE__),0))
void _unicstl_assert(const char *expr, const char *file, int line);
#else
#define unicstl_assert   assert
#endif

/**
 * @brief obj compare with obj2
 *
 * @return
 *      obj < obj2 return -1
 *      obj == obj2 return 0
 *      obj > obj2 return 1
 */
typedef int (*compare_fun_t)(const void* obj, const void* obj2);


// default function
int default_compare(const void* obj1,const void* obj2);
void default_print_obj(const void* obj);


/**
 * @brief new capacity
 * 
 * @param capacity 
 * @return uint32_t 
 */
uint32_t unicstl_new_capacity(uint32_t capacity);

#endif // _COMMON_H_
