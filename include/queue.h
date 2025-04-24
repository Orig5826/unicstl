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

#include "common.h"

struct _queue_node
{
    void  *obj;
    struct _queue_node * next;
};

struct _queue
{
    // -------------------- private -------------------- 
    struct _queue_node * _front;
    struct _queue_node * _back;

    uint32_t _index_front;
    uint32_t _index_back;

    uint32_t _obj_size;
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _ratio;

    void (*_destory)(struct _queue* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push)(struct _queue* self, void* obj);
    bool (*pop)(struct _queue* self, void* obj);
    bool (*back)(struct _queue* self, void* obj);
    bool (*front)(struct _queue* self, void* obj);
    bool (*empty)(struct _queue* self);
    bool (*full)(struct _queue* self);

    // base
    uint32_t (*size)(struct _queue* self);
    uint32_t (*capacity)(struct _queue* self);
    bool (*clear)(struct _queue* self);

    // -------------------- debug -------------------- 
    void (*print)(struct _queue* self);
    void (*print_obj)(void* obj);
};
typedef struct _queue* queue_t;

// create and free queue
queue_t queue_new(uint32_t obj_size);
queue_t queue_new2( uint32_t obj_size, uint32_t capacity);

void queue_free(queue_t* queue);

#endif // _QUEUE_H_
