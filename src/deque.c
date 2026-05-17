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
#if DEQUE_RINGBUF == 1
    return self->ringbuf->push_back(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->push_back(self->_segarray, obj);
#endif
}

static bool deque_push_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->push_front(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->push_front(self->_segarray, obj);
#endif
}

static bool deque_pop_back(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->pop_back(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->pop_back(self->_segarray, obj);
#endif
}

static bool deque_pop_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->pop_front(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->pop_front(self->_segarray, obj);
#endif
}

static bool deque_back(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->back(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->back(self->_segarray, obj);
#endif
}

static bool deque_front(struct _deque* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->front(self->ringbuf, obj);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->front(self->_segarray, obj);
#endif
}

static bool deque_resize(struct _deque *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->resize(self->ringbuf, capacity);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->resize(self->_segarray, capacity);
#endif
}

static size_t deque_size(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->size(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->size(self->_segarray);
#endif
}

static size_t deque_capacity(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->capacity(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->capacity(self->_segarray);
#endif
}

static bool deque_empty(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->empty(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->empty(self->_segarray);
#endif
}

static bool deque_full(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->full(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->full(self->_segarray);
#endif
}

static bool deque_clear(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);
#if DEQUE_RINGBUF == 1
    return self->ringbuf->clear(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    return self->_segarray->clear(self->_segarray);
#endif
}

static void deque_destory(struct _deque* self)
{
    unicstl_assert(self != NULL);
    self->clear(self);
#if DEQUE_RINGBUF == 1
    ringbuf_free(&self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    segarray_free(&self->_segarray);
#endif
}

static void deque_print(struct _deque* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->ringbuf != NULL);

#if DEQUE_RINGBUF == 1
    self->ringbuf->print_obj = self->print_obj;
    self->ringbuf->print(self->ringbuf);
#endif
#if DEQUE_SEGARRAY == 1
    self->_segarray->print_obj = self->print_obj;
    self->_segarray->print(self->_segarray);
#endif
}

bool deque_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    return self->_iter_ptr->hasnext(self->_iter_ptr);
}

const void* deque_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    return self->_iter_ptr->next(self->_iter_ptr);
}

iterator_t deque_iter(struct _deque* self, linear_order_t order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;

#if DEQUE_RINGBUF == 1
    self->_iter_ptr = self->ringbuf->iter(self->ringbuf, order);
#endif
#if DEQUE_SEGARRAY == 1
    self->_iter_ptr = self->_segarray->iter(self->_segarray, order);
#endif

    iter->hasnext = deque_iter_hasnext;
    iter->next = deque_iter_next;
    return iter;
}

static bool deque_init(struct _deque* self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);
    
    // -------------------- private -------------------- 
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
    self->resize = deque_resize;
    self->size = deque_size;
    self->capacity = deque_capacity;
    self->empty = deque_empty;
    self->full = deque_full;
    self->clear = deque_clear;

    // iter
    self->iter = deque_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = deque_print;
    
    // -------------------- init -------------------- 
    #if DEQUE_RINGBUF == 1
    self->ringbuf = ringbuf_new(obj_size, capacity);
    if(self->ringbuf == NULL)
    {
        return false;
    }
    self->ringbuf->print_obj = default_print_obj;
    #endif

    #if DEQUE_SEGARRAY == 1
    self->_segarray = segarray_new(obj_size, capacity);
    if(self->_segarray == NULL)
    {
        return false;
    }
    self->_segarray->print_obj = default_print_obj;
    #endif

    return true;
}

deque_t deque_new(size_t obj_size, size_t capacity)
{
    struct _deque* deque = NULL;
    deque = (struct _deque*)unicstl_malloc(sizeof(struct _deque));
    if(deque == NULL)
    {
        log_warn("deque malloc failed\n");
        return NULL;
    }

    if(deque_init(deque, obj_size, capacity) != true)
    {
        log_warn("deque init failed\n");
        unicstl_free(deque);
        return NULL;
    }
    return deque;
}

void deque_free(deque_t *deque)
{
    if(*deque != NULL)
    {
        (*deque)->_destory(*deque);
        unicstl_free(*deque);
        *deque = NULL;
    }
}
