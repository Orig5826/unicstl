/**
 * @file ringbuf.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include "unicstl_internal.h"

enum _ringbuf_order
{
    RINGBUF_FORWARD,
    RINGBUF_REVERSE,
};

struct _ringbuf
{
    // -------------------- private -------------------- 
    void *obj;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;
    bool _dynamic;
    
    size_t _head;
    size_t _tail;
    
    struct _iterator _iter;
    void (*_destory)(struct _ringbuf* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push_back)(struct _ringbuf* self, const void* obj);
    bool (*push_front)(struct _ringbuf* self, const void* obj);
    bool (*pop_back)(struct _ringbuf* self, void* obj);
    bool (*pop_front)(struct _ringbuf* self, void* obj);
    bool (*back)(struct _ringbuf* self, void* obj);
    bool (*front)(struct _ringbuf* self, void* obj);

    // -------------------- random access -------------------- 
    bool (*set)(struct _ringbuf *self, size_t index, const void *obj);      // O(1)
    bool (*get)(struct _ringbuf *self, size_t index, void *obj);            // O(1)
    const void* (*at)(struct _ringbuf *self, size_t index);                 // O(1)
    
    // base
    bool (*resize)(struct _ringbuf *self, size_t capacity);
    size_t (*size)(struct _ringbuf* self);
    size_t (*capacity)(struct _ringbuf* self);
    bool (*empty)(struct _ringbuf* self);
    bool (*full)(struct _ringbuf* self);
    bool (*clear)(struct _ringbuf* self);

    // iter
    iterator_t (*iter)(struct _ringbuf* self, enum _ringbuf_order order);

    // -------------------- debug -------------------- 
    void (*print)(struct _ringbuf* self);
    void (*print_obj)(const void* obj);
};
typedef struct _ringbuf* ringbuf_t;

ringbuf_t ringbuf_new(size_t obj_size, size_t capacity);
void ringbuf_free(ringbuf_t* ringbuf);

#ifdef UNICSTL_STATIC_MEMORY
bool ringbuf_init(struct _ringbuf *self, size_t obj_size, size_t capacity, void *mem_base);
#endif

#endif
