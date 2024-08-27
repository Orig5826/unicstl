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
    struct _stack_node * _head;
    
    uint32_t _size;				// 栈大小
    uint32_t _obj_size;			// 元素大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率

    // kernel
    bool (*peek)(struct _stack* self, void* obj);
    bool (*push)(struct _stack* self, void* obj);
    bool (*pop)(struct _stack* self, void* obj);

    // base
    uint32_t(*size)(struct _stack* self);
    bool (*empty)(struct _stack* self);

    // others
    bool (*clear)(struct _stack* self);
    void (*destory)(struct _stack* self);

    // print
    void (*print)(struct _stack* self);
    void (*print_obj)(void* obj);
};
typedef struct _stack* stack_t;

bool stack_init(struct _stack* self, uint32_t obj_size);
bool stack_init2(struct _stack* self, uint32_t obj_size, uint32_t capacity);

stack_t stack_new(void);
void stack_free(stack_t* stack);

#endif // _STACK_H_
