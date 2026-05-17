/**
 * @file mempool.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#include "unicstl_internal.h"

#ifdef UNICSTL_MALLOC_CUSTOM
extern void *unicstl_malloc(size_t size);
extern void *unicstl_calloc(size_t num, size_t size);
extern void *unicstl_realloc(void *ptr, size_t size);
extern void unicstl_free(void *ptr);
#endif

void mempool_init(void);
void mempool_deinit(void);

#endif // _MEMPOOL_H_
