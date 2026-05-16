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

#include "iterator.h"
#include "logger.h"

#define UNICSTL_VERSION_MAJOR 0
#define UNICSTL_VERSION_MINOR 0
#define UNICSTL_VERSION_MICRO 10
#define UNICSTL_VERSION ((UNICSTL_VERSION_MAJOR << 16) | (UNICSTL_VERSION_MINOR << 8) | UNICSTL_VERSION_MICRO)

#define UNICSTL_TOSTRING_(x) #x
#define UNICSTL_TOSTRING(x) UNICSTL_TOSTRING_(x)
#define UNICSTL_VERSION_STRING UNICSTL_TOSTRING(UNICSTL_VERSION_MAJOR) "." UNICSTL_TOSTRING(UNICSTL_VERSION_MINOR) "." UNICSTL_TOSTRING(UNICSTL_VERSION_MICRO)

#define UNICSTL_UNUSED(x) (void)(x)

/**
 * @brief default capacity and ratio
 *
 */
#ifndef UNICSTL_CAPACITY_INIT
#define UNICSTL_CAPACITY_INIT 8 // 若capacity参数为0时，自动分配默认初始容量
#endif

#ifndef UNICSTL_CAPACITY_MAX
#define UNICSTL_CAPACITY_MAX 8192 // 最大容量
#endif

#ifndef UNICSTL_OBJSIZE_MAX
#define UNICSTL_OBJSIZE_MAX 8192 // 最大对象大小
#endif

#ifndef UNICSTL_STATIC_MEMORY
#define UNICSTL_STATIC_MEMORY
#endif

/**
 * @brief assert function
 *
 */
#ifdef UNICSTL_ASSERT_ENABLE
#define unicstl_assert(expr) (void)((!!(expr)) || (_unicstl_assert(#expr, __FILE__, __LINE__), 0))

#ifndef ASSERT_CUSTOM
static inline void _unicstl_assert(const char *expr, const char *file, int line)
{
    printf("Assertion failed: %s, file:%s line:%d\n", expr, file, line);
    exit(1);
}
#else
extern void _unicstl_assert(const char *expr, const char *file, int line);
#endif // ASSERT_CUSTOM

#else
#define unicstl_assert(expr) // assert(expr)
#endif                       // UNICSTL_ASSERT_ENABLE

/**
 * @brief malloc and free function
 *
 */
#ifdef UNICSTL_MALLOC_ENABLE
#ifndef UNICSTL_MALLOC_CUSTOM
static inline void *unicstl_malloc(size_t size)
{
    return malloc(size);
}

static inline void *unicstl_calloc(size_t num, size_t size)
{
    return calloc(num, size);
}

static inline void *unicstl_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

static inline void unicstl_free(void *ptr)
{
    free(ptr);
}
#else
extern void *unicstl_malloc(size_t size);
extern void *unicstl_calloc(size_t num, size_t size);
extern void *unicstl_realloc(void *ptr, size_t size);
extern void unicstl_free(void *ptr);
#endif
#else
static inline void *unicstl_malloc(size_t size) { return NULL; }
static inline void *unicstl_calloc(size_t num, size_t size) { return NULL; }
static inline void *unicstl_realloc(void *ptr, size_t size) { return NULL; }
static inline void unicstl_free(void *ptr) { }
#endif // UNICSTL_MALLOC_ENABLE

static inline const void *obj_at(const void *objs, size_t index, size_t obj_size)
{
#ifdef UNICSTL_DEBUG
    unicstl_assert(objs != NULL);
#endif
    return (const char *)objs + obj_size * index;
}

static inline void obj_set(void *objs, size_t index, const void *obj, size_t obj_size)
{
#ifdef UNICSTL_DEBUG
    unicstl_assert(objs != NULL);
    unicstl_assert(obj != NULL);
#endif
    memmove((char *)objs + obj_size * index, obj, obj_size);
}

static inline void obj_get(const void *objs, size_t index, void *obj, size_t obj_size)
{
#ifdef UNICSTL_DEBUG
    unicstl_assert(objs != NULL);
    unicstl_assert(obj != NULL);
#endif
    memmove(obj, (const char *)objs + obj_size * index, obj_size);
}

static inline void obj_copy(void *dst, const void *src, size_t count, size_t obj_size)
{
#ifdef UNICSTL_DEBUG
    unicstl_assert(dst != NULL);
    unicstl_assert(src != NULL);
#endif
    memmove(dst, src, obj_size * count);
}

static inline size_t ring_index(size_t head, size_t index, size_t capacity)
{
    return (head + index) % capacity;
}

static inline size_t ring_index_next(size_t index, size_t capacity)
{
    return (index + 1) % capacity;
}

static inline size_t ring_index_prev(size_t index, size_t capacity)
{
    return index == 0 ? (capacity - 1) : index - 1;
}

/**
 * @brief obj compare with obj2
 *
 * @return
 *      obj < obj2 return -1
 *      obj == obj2 return 0
 *      obj > obj2 return 1
 */
typedef int (*compare_fun_t)(const void *obj, const void *obj2);

// default function
int default_compare(const void *obj1, const void *obj2);
void default_print_obj(const void *obj);

/**
 * @brief new capacity
 *
 * @param capacity
 * @return size_t
 */
const char *unicstl_version(void);
size_t unicstl_new_capacity(size_t capacity);

#endif // _COMMON_H_
