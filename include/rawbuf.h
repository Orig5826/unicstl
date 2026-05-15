/**
 * @file rawbuf.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _RAWBUF_H_
#define _RAWBUF_H_

#include "unicstl_internal.h"

struct _rawbuf
{
    // -------------------- private --------------------
    void *obj;
    size_t _obj_size;
    size_t _capacity;
    bool _dynamic;
    
    void (*_destory)(struct _rawbuf *self);
    // -------------------- public --------------------
    // kernel -> random access
    bool (*set)(struct _rawbuf *self, size_t index, const void *obj);       // O(1)
    bool (*get)(struct _rawbuf *self, size_t index, void *obj);             // O(1)
    const void* (*at)(struct _rawbuf *self, size_t index);                  // O(1)

    // base
    size_t (*capacity)(struct _rawbuf *self);
};
typedef struct _rawbuf *rawbuf_t;

rawbuf_t rawbuf_new(size_t obj_size, size_t capacity);
void rawbuf_free(rawbuf_t *rawbuf);

#ifdef UNICSTL_STATIC_MEMORY
bool rawbuf_init(struct _rawbuf *self, size_t obj_size, size_t capacity, void *mem_base);
#endif

#endif // _RAWBUF_H_
