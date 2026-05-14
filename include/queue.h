/**
 * @file queue.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "unicstl_internal.h"
#include "deque.h"

struct _queue
{
    // -------------------- private -------------------- 
    deque_t _deque;
    iterator_t _iter_deque;

    struct _iterator _iter;
    void (*_destory)(struct _queue* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push)(struct _queue* self, void* obj);
    bool (*pop)(struct _queue* self, void* obj);
    bool (*back)(struct _queue* self, void* obj);
    bool (*front)(struct _queue* self, void* obj);

    // base
    size_t (*resize)(struct _queue* self, size_t capacity);
    size_t (*size)(struct _queue* self);
    size_t (*capacity)(struct _queue* self);
    bool (*empty)(struct _queue* self);
    bool (*full)(struct _queue* self);
    bool (*clear)(struct _queue* self);

    // iter
    iterator_t (*iter)(struct _queue* self);
    
    // -------------------- debug -------------------- 
    void (*print)(struct _queue* self);
    void (*print_obj)(const void* obj);
};
typedef struct _queue* queue_t;

// create and free queue
queue_t queue_new(size_t obj_size, size_t capacity);
void queue_free(queue_t* queue);

#endif // _QUEUE_H_
