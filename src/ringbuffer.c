/**
 * @file ringbuffer.c
 * @author wenjf (orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "ringbuffer.h"

static bool ringbuffer_push_back(struct _ringbuffer *self, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);
    
    if(self->full(self))
    {
        return false;
    }

    size_t index = self->_tail;
    obj_set(self->obj, index, obj, self->_obj_size);
    self->_tail = index_next(index, self->_capacity);

    self->_size++;
    return true;
}

static bool ringbuffer_push_front(struct _ringbuffer *self, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);

    if(self->full(self))
    {
        return false;
    }

    size_t index = index_prev(self->_head, self->_capacity);
    obj_set(self->obj, index, obj, self->_obj_size);
    self->_head = index;

    self->_size++;
    return true;
}

static bool ringbuffer_pop_back(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);

    if(self->empty(self))
    {
        return false;
    }

    size_t index = index_prev(self->_tail, self->_capacity);
    obj_get(self->obj, index, obj, self->_obj_size);
    self->_tail = index;

    self->_size--;
    return true;
}

static bool ringbuffer_pop_front(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);

    if(self->empty(self))
    {
        return false;
    }

    obj_get(self->obj, self->_head, obj, self->_obj_size);
    self->_head = index_next(self->_head, self->_capacity);

    self->_size--;
    return true;
}

static bool ringbuffer_back(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);

    if(self->empty(self))
    {
        return false;
    }

    size_t index = index_prev(self->_tail, self->_capacity);
    obj_get(self->obj, index, obj, self->_obj_size);

    return true;
}

static bool ringbuffer_front(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->obj != NULL);
    unicstl_assert(obj != NULL);

    if(self->empty(self))
    {
        return false;
    }

    obj_get(self->obj, self->_head, obj, self->_obj_size);

    return true;
}

static bool ringbuffer_clear(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;
    self->_head = 0;
    self->_tail = 0;
    return true;
}

static size_t ringbuffer_size(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t ringbuffer_capacity(struct _ringbuffer* self)
{
    unicstl_assert(self != NULL);
    return self->_capacity - 1;
}

static bool ringbuffer_empty(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    return self->_head == self->_tail;
}

static bool ringbuffer_full(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    return self->_head == index_next(self->_tail, self->_capacity);
}

static void ringbuffer_destory(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    if(self->obj != NULL)
    {
        free(self->obj);
        self->obj = NULL;
    }
}

static void ringbuffer_print(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);

    for(size_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(obj_at(self->obj, self->_obj_size, i));
    }
}

bool ringbuffer_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ringbuffer_t self = (ringbuffer_t)iter->_container;

    if(iter->_order == RINGBUF_FORWARD)
    {
        if(iter->_index == self->_tail)
        {
            return false;
        }
    }
    else
    {
        if(iter->_index == self->_head)
        {
            return false;
        }
    }
    return true;
}

const void *ringbuffer_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ringbuffer_t self = (ringbuffer_t)iter->_container;

    size_t index = iter->_index;
    if(iter->_order == RINGBUF_FORWARD)
    {
        iter->_index = index_next(index, self->_capacity);
    }
    else
    {
        iter->_index = index_prev(index, self->_capacity);
    }

    return obj_at(self->obj, index, self->_obj_size);
}

iterator_t ringbuffer_iter(struct _ringbuffer *self, enum _ringbuffer_order order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    if (iter->_order == RINGBUF_FORWARD)
    {
        iter->_index = self->_head;
    }
    else
    {
        iter->_index = index_prev(self->_tail, self->_capacity);
    }

    iter->hasnext = ringbuffer_iter_hasnext;
    iter->next = ringbuffer_iter_next;
    return iter;
}

bool ringbuffer_init(struct _ringbuffer *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (obj_size == 0 || capacity == 0)
    {
        return false;
    }
    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity + 1;

    self->obj = (char *)malloc(self->_obj_size * self->_capacity);
    if(self->obj == NULL)
    {
        return false;
    }

    self->_head = 0;
    self->_tail = 0;

    self->_destory = ringbuffer_destory;

    // -------------------- public --------------------
    // kernel
    self->push_back = ringbuffer_push_back;
    self->push_front = ringbuffer_push_front;
    self->pop_back = ringbuffer_pop_back;
    self->pop_front = ringbuffer_pop_front;
    self->back = ringbuffer_back;
    self->front = ringbuffer_front;

    // base
    self->clear = ringbuffer_clear;
    self->size = ringbuffer_size;
    self->capacity = ringbuffer_capacity;
    self->empty = ringbuffer_empty;
    self->full = ringbuffer_full;

    // iter
    self->iter = ringbuffer_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;
    
    // -------------------- debug --------------------
    self->print = ringbuffer_print;

    return true;
}

ringbuffer_t ringbuffer_new(size_t obj_size, size_t capacity)
{
    struct _ringbuffer *ringbuffer = NULL;
    ringbuffer = (struct _ringbuffer *)malloc(sizeof(struct _ringbuffer));
    if (ringbuffer == NULL)
    {
        return NULL;
    }

    if (ringbuffer_init(ringbuffer, obj_size, capacity) != true)
    {
        free(ringbuffer);
        return NULL;
    }
    return ringbuffer;
}

void ringbuffer_free(ringbuffer_t *ringbuffer)
{
    if (*ringbuffer != NULL)
    {
        (*ringbuffer)->_destory(*ringbuffer);
        free(*ringbuffer);
    }
    *ringbuffer = NULL;
}
