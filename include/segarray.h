/**
 * @file segarray.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _SEGARRAY_H_
#define _SEGARRAY_H_

#include "unicstl_internal.h"
#include "ringbuf.h"
#include "rawbuf.h"

struct _segarray
{
    // -------------------- private -------------------- 
    void *obj;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;
    size_t _segsize;

    ringbuf_t _map;
    ringbuf_t _mapfree;
    size_t _seghead;
    size_t _segtail;
    
    struct _iterator _iter;
    void (*_destory)(struct _segarray* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push_back)(struct _segarray* self, const void* obj);
    bool (*push_front)(struct _segarray* self, const void* obj);
    bool (*pop_back)(struct _segarray* self, void* obj);
    bool (*pop_front)(struct _segarray* self, void* obj);
    bool (*back)(struct _segarray* self, void* obj);
    bool (*front)(struct _segarray* self, void* obj);
    
    // -------------------- random access -------------------- 
    bool (*set)(struct _segarray *self, size_t index, const void *obj);      // O(1)
    bool (*get)(struct _segarray *self, size_t index, void *obj);            // O(1)
    const void* (*at)(struct _segarray *self, size_t index);                 // O(1)

    // base
    bool (*resize)(struct _segarray *self, size_t capacity);
    size_t (*size)(struct _segarray* self);
    size_t (*capacity)(struct _segarray* self);
    bool (*empty)(struct _segarray* self);
    bool (*full)(struct _segarray* self);
    bool (*clear)(struct _segarray* self);

    // iter
    iterator_t (*iter)(struct _segarray* self, linear_order_t order);

    // -------------------- debug -------------------- 
    void (*print)(struct _segarray* self);
    void (*print_obj)(const void* obj);
};
typedef struct _segarray* segarray_t;

segarray_t segarray_new(size_t obj_size, size_t capacity);
void segarray_free(segarray_t* segarray);

#endif
