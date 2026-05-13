/**
 * @file deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "deque.h"

static bool deque_push_back(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->push_back(self->ringbuf, obj);
}

static bool deque_push_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->push_front(self->ringbuf, obj);
}

static bool deque_pop_back(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->pop_back(self->ringbuf, obj);
}

static bool deque_pop_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->pop_front(self->ringbuf, obj);
}

static bool deque_back(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->back(self->ringbuf, obj);
}

static bool deque_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->front(self->ringbuf, obj);
}

static bool deque_clear(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->clear(self->ringbuf);
}

static size_t deque_size(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->size(self->ringbuf);
}

static size_t deque_capacity(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->capacity(self->ringbuf);
}

static bool deque_empty(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
    return self->ringbuf->empty(self->ringbuf);
}

static void deque_destory(struct _deque* self)
{
    unicstl_assert(self != NULL);
    self->clear(self);
    ringbuffer_free(&self->ringbuf);
}

static void deque_print(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);

    self->ringbuf->print_obj = self->print_obj;
    self->ringbuf->print(self->ringbuf);
}

bool deque_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    return self->_iter_ringbuf->hasnext(self->_iter_ringbuf);
}

const void* deque_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    return self->_iter_ringbuf->next(self->_iter_ringbuf);
}

iterator_t deque_iter(struct _deque* self, enum _deque_order order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    self->_iter_ringbuf = self->ringbuf->iter(self->ringbuf, order);

    iter->hasnext = deque_iter_hasnext;
    iter->next = deque_iter_next;
    return iter;
}

static bool deque_init(struct _deque* self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    if(obj_size == 0 || capacity == 0)
    {
        return false;
    }
    // -------------------- private -------------------- 
    self->ringbuf = ringbuffer_new(obj_size, capacity);
    if(self->ringbuf == NULL)
    {
        return false;
    }
    self->_destory = deque_destory;

    // -------------------- public -------------------- 
    // kernel
    self->push_back = deque_push_back;
    self->push_front = deque_push_front;
    self->pop_back = deque_pop_back;
    self->pop_front = deque_pop_front;
    self->back = deque_back;
    self->front = deque_front;
    
    // base
    self->clear = deque_clear;
    self->size = deque_size;
    self->empty = deque_empty;

    // iter
    self->iter = deque_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = deque_print;
    
    return true;
}

deque_t deque_new(size_t obj_size, size_t capacity)
{
    struct _deque* deque = NULL;
    deque = (struct _deque*)malloc(sizeof(struct _deque));
    if(deque == NULL)
    {
        return NULL;
    }

    if(deque_init(deque, obj_size, capacity) != true)
    {
        free(deque);
        return NULL;
    }
    return deque;
}

void deque_free(deque_t *deque)
{
    if(*deque != NULL)
    {
        (*deque)->_destory(*deque);
        free(*deque);
    }
    *deque = NULL;
}
