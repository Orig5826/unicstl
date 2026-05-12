/**
 * @file ringbuffer.h
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
#include "darray.h"

enum _ringbuffer_order
{
    RINGBUF_FORWARD,
    RINGBUF_REVERSE,
};

struct _ringbuffer
{
    // -------------------- private -------------------- 
    void *obj;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;
    
    size_t _head;
    size_t _tail;
    
    struct _iterator _iter;
    void (*_destory)(struct _ringbuffer* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push_back)(struct _ringbuffer* self, const void* obj);
    bool (*push_front)(struct _ringbuffer* self, const void* obj);
    bool (*pop_back)(struct _ringbuffer* self, void* obj);
    bool (*pop_front)(struct _ringbuffer* self, void* obj);
    bool (*back)(struct _ringbuffer* self, void* obj);
    bool (*front)(struct _ringbuffer* self, void* obj);
    
    // base
    size_t (*size)(struct _ringbuffer* self);
    size_t (*capacity)(struct _ringbuffer* self);
    bool (*clear)(struct _ringbuffer* self);
    bool (*empty)(struct _ringbuffer* self);
    bool (*full)(struct _ringbuffer* self);

    // iter
    iterator_t (*iter)(struct _ringbuffer* self, enum _ringbuffer_order order);

    // -------------------- debug -------------------- 
    void (*print)(struct _ringbuffer* self);
    void (*print_obj)(const void* obj);
};
typedef struct _ringbuffer* ringbuffer_t;

ringbuffer_t ringbuffer_new(size_t obj_size, size_t capacity);
void ringbuffer_free(ringbuffer_t* ringbuffer);

#endif
