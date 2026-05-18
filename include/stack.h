/**
 * @file stack.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _STACK_H_
#define _STACK_H_

#include "unicstl_internal.h"
#include "deque.h"

struct _stack
{
    deque_t _deque;
    iterator_t _iter_deque;

    struct _iterator _iter;
    void (*_destory)(struct _stack* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push)(struct _stack* self, void* obj);
    bool (*pop)(struct _stack* self, void* obj);
    bool (*peek)(struct _stack* self, void* obj);
    
    // base
    size_t (*reserve)(struct _stack* self, size_t capacity);
    size_t (*size)(struct _stack* self);
    size_t (*capacity)(struct _stack* self);
    bool (*empty)(struct _stack* self);
    bool (*full)(struct _stack* self);
    bool (*clear)(struct _stack* self);
    
    // iter
    iterator_t (*iter)(struct _stack* self);

    // -------------------- debug -------------------- 
    void (*print)(struct _stack* self);
    void (*print_obj)(const void* obj);
};
typedef struct _stack* stack_t;

// create and free stack
stack_t stack_new(size_t obj_size, size_t capacity);
void stack_free(stack_t* stack);

#endif // _STACK_H_
