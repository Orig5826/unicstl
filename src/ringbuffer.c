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

static size_t calc_index_next(size_t capacity, size_t index)
{
    return (index + 1) % capacity;
}

static size_t calc_index_prev(size_t capacity, size_t index)
{
    return index == 0 ? (capacity - 1) : index - 1;
}

static bool ringbuffer_push_back(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

    if(self->full(self))
    {
        return false;
    }
    darray->set(darray, self->_tail, obj);
    self->_tail = calc_index_next(capacity_total, self->_tail);

    LOG_DEBUG("head: %lu, tail: %lu", self->_head, self->_tail);

    self->_size++;
    return true;
}

static bool ringbuffer_push_front(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

    if(self->full(self))
    {
        return false;
    }
    size_t index = calc_index_prev(capacity_total, self->_head);
    darray->set(darray, index, obj);
    self->_head = index;

    self->_size++;
    return true;
}

static bool ringbuffer_pop_back(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

    if(self->empty(self))
    {
        return false;
    }
    size_t index = calc_index_prev(capacity_total, self->_tail);
    darray->get(darray, index, obj);
    self->_tail = index;
    self->_size--;
    return true;
}

static bool ringbuffer_pop_front(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

    if(self->empty(self))
    {
        return false;
    }
    darray->get(darray, self->_head, obj);
    self->_head = calc_index_next(capacity_total, self->_head);
    self->_size--;
    return true;
}

static bool ringbuffer_back(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;

    if(self->empty(self))
    {
        return false;
    }
    size_t capacity_total = darray->capacity(darray);
    size_t index = calc_index_prev(capacity_total, self->_tail);
    darray->get(darray, index, obj);
    return true;
}

static bool ringbuffer_front(struct _ringbuffer *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_t darray = self->darray;

    if(self->empty(self))
    {
        return false;
    }
    darray->get(darray, self->_head, obj);
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
    return self->_capacity;
}

static bool ringbuffer_empty(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    // return self->size(self) == 0;
    return self->_head == self->_tail;
}

static bool ringbuffer_full(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    // return self->size(self) == self->capacity(self) - 1;
    return self->_head == calc_index_next(self->_capacity, self->_tail);
}

static void ringbuffer_destory(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    darray_free(&self->darray);
}


static void print_num(const void* obj)
{
    printf("(%2d ) ", *(int*)obj);
}

static void ringbuffer_print(struct _ringbuffer *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->darray != NULL);
    self->darray->print_obj = self->print_obj;
    self->darray->print(self->darray);
}

bool ringbuffer_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ringbuffer_t self = (ringbuffer_t)iter->_container;
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

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
    darray_t darray = self->darray;
    size_t capacity_total = darray->capacity(darray);

    size_t index = iter->_index;
    if(iter->_order == RINGBUF_FORWARD)
    {
        iter->_index = calc_index_next(capacity_total, index);
    }
    else
    {
        iter->_index = calc_index_prev(capacity_total, index);
    }
    return darray->at(darray, index);
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
        darray_t darray = self->darray;
        size_t capacity_total = darray->capacity(darray);
        iter->_index = calc_index_prev(capacity_total, self->_tail);
    }

    iter->hasnext = ringbuffer_iter_hasnext;
    iter->next = ringbuffer_iter_next;
    return iter;
}

static bool ringbuffer_init(struct _ringbuffer *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (obj_size == 0)
    {
        return false;
    }
    // -------------------- private --------------------
    self->darray = darray_new(obj_size, capacity + 1);
    self->darray->set_dynamic(self->darray, false);
    self->darray->_size = capacity + 1;

    self->_size = 0;
    self->_capacity = capacity + 1;
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
