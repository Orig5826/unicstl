/**
 * @file stack.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "stack.h"

static bool stack_push(struct _stack* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->push_back(deque, obj);
}

static bool stack_pop(struct _stack* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->pop_back(deque, obj);
}

static bool stack_peek(struct _stack* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->back(deque, obj);
}

static size_t stack_resize(struct _stack* self, size_t capaticy)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->resize(deque, capaticy);
}

static size_t stack_size(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->size(deque);
}

static size_t stack_capacity(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->capacity(deque);
}

static bool stack_empty(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->empty(deque);
}

static bool stack_full(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->full(deque);
}

static bool stack_clear(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    return deque->clear(deque);
}

static void stack_destory(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_free(&self->_deque);
}

static void stack_print(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;
    deque->print_obj = self->print_obj;

    deque->print(deque);
}

bool stack_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    stack_t self = (stack_t)iter->_container;
    return self->_iter_deque->hasnext(self->_iter_deque);
}

/**
 * @brief iter next
 *  from top to bottom
 */
const void* stack_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    stack_t self = (stack_t)iter->_container;
    return self->_iter_deque->next(self->_iter_deque);
}

iterator_t stack_iter(struct _stack* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;

    self->_iter_deque = deque->iter(deque, DEQUE_FORWARD);
    
    iterator_t iter = &self->_iter;
    iter->_container = self;
    iter->hasnext = stack_iter_hasnext;
    iter->next = stack_iter_next;
    return iter;
}

static bool stack_init(struct _stack* self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size != 0);
    
    // -------------------- private --------------------
    self->_deque = deque_new(obj_size, capacity);
    if(self->_deque == NULL)
    {
        return false;
    }

    self->_destory = stack_destory;

    // -------------------- public --------------------
    // kernel
    self->push = stack_push;
    self->pop = stack_pop;
    self->peek = stack_peek;

    // base
    self->resize = stack_resize;
    self->size = stack_size;
    self->capacity = stack_capacity;
    self->empty = stack_empty;
    self->full = stack_full;
    self->clear = stack_clear;

    // iter
    self->iter = stack_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = stack_print;

    return true;
}

stack_t stack_new(size_t obj_size, size_t capacity)
{
    stack_t stack = NULL;
    stack = (struct _stack*)calloc(1, sizeof(struct _stack));
    if (stack == NULL)
    {
        return NULL;
    }

    if(stack_init(stack, obj_size, capacity) != true)
    {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_free(stack_t *stack)
{
    if(stack != NULL && *stack != NULL)
    {
        if((*stack)->_destory != NULL)
        {
            (*stack)->_destory(*stack);
        }
        free(*stack);
        *stack = NULL;
    }
}
