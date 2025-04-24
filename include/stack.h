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

#include "common.h"

struct _stack_node
{
    void * obj;
    struct _stack_node * next;
};

struct _stack
{
    // ---------- private ---------- 
    struct _stack_node * _head;
    
    uint32_t _size;
    uint32_t _obj_size;
    uint32_t _capacity;
    uint32_t _ratio;

    struct _iterator _iter;

    void (*_destory)(struct _stack* self);

    // ---------- public ---------- 
    // kernel
    bool (*push)(struct _stack* self, void* obj);
    bool (*pop)(struct _stack* self, void* obj);
    bool (*peek)(struct _stack* self, void* obj);
    bool (*empty)(struct _stack* self);

    // base
    uint32_t (*size)(struct _stack* self);
    uint32_t (*capacity)(struct _stack* self);
    bool (*clear)(struct _stack* self);
    
    // iter
    iterator_t (*iter)(struct _stack* self);

    // ---------- debug ---------- 
    void (*print)(struct _stack* self);
    void (*print_obj)(void* obj);
};
typedef struct _stack* stack_t;

// create and free stack
stack_t stack_new(uint32_t obj_size);
stack_t stack_new2(uint32_t obj_size, uint32_t capacity);

void stack_free(stack_t* stack);

#endif // _STACK_H_
