/**
 * @file mempool.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "mempool.h"

#ifdef UNICSTL_MALLOC_CUSTOM

typedef struct _mempool
{
    size_t count_total;
    size_t count_free;

    size_t count_malloc;
    size_t count_calloc;
    size_t count_realloc;
}mempool_t;

static mempool_t mempool;


void mempool_init()
{
    memset(&mempool, 0, sizeof(mempool_t));
}

void mempool_deinit()
{
    printf("\n-------------------- \n");
    printf("count_malloc: %zu\n", mempool.count_malloc);
    printf("count_calloc: %zu\n", mempool.count_calloc);
    printf("count_realloc: %zu\n", mempool.count_realloc);
    printf("\n");
    printf("count_total: %zu\n", mempool.count_total);
    printf("count_free: %zu\n", mempool.count_free);
    printf("-------------------- \n");

    size_t leak = mempool.count_total - mempool.count_free;
    if (mempool.count_total > mempool.count_free)
    {
        printf("ERROR: maybe leak: %zu\n", leak);
    }
    else if (mempool.count_total < mempool.count_free)
    {
        printf("ERROR: maybe free too many\n");
    }
    else
    {
        printf("OK: no leak\n");
    }
    memset(&mempool, 0, sizeof(mempool_t));
}

void *unicstl_malloc(size_t size)
{
    mempool.count_malloc++;
    mempool.count_total++;
    return malloc(size);
}

void *unicstl_calloc(size_t num, size_t size)
{
    mempool.count_calloc++;
    mempool.count_total++;
    return calloc(num, size);
}

void *unicstl_realloc(void *ptr, size_t size)
{
    mempool.count_realloc++;
    if(ptr == NULL)
    {
        mempool.count_total++;
    }
    return realloc(ptr, size);
}

void unicstl_free(void *ptr)
{
    if (ptr != NULL)
    {
        mempool.count_free++;
        free(ptr);
    }
}
#endif
