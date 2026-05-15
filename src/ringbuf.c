/**
 * @file ringbuf.c
 * @author wenjf (orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "ringbuf.h"

static inline size_t index_next(size_t index, size_t capacity)
{
    return (index + 1) % capacity;
}

static inline size_t index_prev(size_t index, size_t capacity)
{
    return index == 0 ? (capacity - 1) : index - 1;
}

static inline size_t ring_index(size_t head, size_t index, size_t capacity)
{
    return (head + index) % capacity;
}

static bool ringbuf_push_back(struct _ringbuf *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL)
    {
        return false;
    }

    if (self->full(self))
    {
        if(self->_dynamic != true)
        {
            return false;
        }
        size_t new_capacity = unicstl_new_capacity(self->capacity(self));
        if (self->resize(self, new_capacity) == false)
        {
            return false;
        }
    }

    size_t index = self->_tail;
    obj_set(self->obj, index, obj, self->_obj_size);
    self->_tail = index_next(index, self->_capacity);

    self->_size++;
    return true;
}

static bool ringbuf_push_front(struct _ringbuf *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL)
    {
        return false;
    }

    if (self->full(self))
    {
        if(self->_dynamic != true)
        {
            return false;
        }
        size_t new_capacity = unicstl_new_capacity(self->capacity(self));
        if (self->resize(self, new_capacity) == false)
        {
            return false;
        }
    }

    size_t index = index_prev(self->_head, self->_capacity);
    obj_set(self->obj, index, obj, self->_obj_size);
    self->_head = index;

    self->_size++;
    return true;
}

static bool ringbuf_pop_back(struct _ringbuf *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || self->empty(self))
    {
        return false;
    }

    size_t index = index_prev(self->_tail, self->_capacity);
    if(obj != NULL)
    {
        obj_get(self->obj, index, obj, self->_obj_size);
    }
    self->_tail = index;

    self->_size--;
    return true;
}

static bool ringbuf_pop_front(struct _ringbuf *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || self->empty(self))
    {
        return false;
    }

    if (self->empty(self))
    {
        return false;
    }

    if(obj != NULL)
    {
        obj_get(self->obj, self->_head, obj, self->_obj_size);
    }
    self->_head = index_next(self->_head, self->_capacity);

    self->_size--;
    return true;
}

static bool ringbuf_back(struct _ringbuf *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL|| self->empty(self))
    {
        return false;
    }
    size_t index = index_prev(self->_tail, self->_capacity);
    obj_get(self->obj, index, obj, self->_obj_size);
    return true;
}

static bool ringbuf_front(struct _ringbuf *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL|| self->empty(self))
    {
        return false;
    }
    obj_get(self->obj, self->_head, obj, self->_obj_size);
    return true;
}

static bool ringbuf_set(struct _ringbuf *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    index = ring_index(self->_head, index, self->_capacity);

    size_t offset = index * self->_obj_size;
    memmove((char *)self->obj + offset, obj, self->_obj_size);
    return true;
}

static bool ringbuf_get(struct _ringbuf *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    index = ring_index(self->_head, index, self->_capacity);

    size_t offset = index * self->_obj_size;
    memmove(obj, (char *)self->obj + offset, self->_obj_size);
    return true;
}

static const void* ringbuf_at(struct _ringbuf *self, size_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self))
    {
        return false;
    }
    index = ring_index(self->_head, index, self->_capacity);
    
    size_t offset = index * self->_obj_size;
    return (const char *)self->obj + offset;
}

static bool ringbuf_resize(struct _ringbuf *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (self->_dynamic != true || capacity == 0 || capacity > UNICSTL_CAPACITY_MAX - 1)
    {
        return false;
    }
    // make sure there is always one empty slot to distinguish between full and empty
    size_t real_capacity = capacity + 1;

    void *new_obj = unicstl_malloc(real_capacity * self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }

    size_t first_size = 0;
    size_t second_size = 0;
    if(self->_tail >= self->_head)
    {
        first_size = self->_tail - self->_head;
        second_size = 0;
    }
    else
    {
        first_size = self->_capacity - self->_head;
        second_size = self->_tail;
    }

    // resize to smaller capacity
    if(self->_size > capacity)
    {
        if(first_size >= capacity)
        {
            first_size = capacity;
            second_size = 0;
        }
        else
        {
            second_size = capacity - first_size;
        }
    }

    if(first_size > 0)
    {
        obj_copy(new_obj, self->obj + self->_head * self->_obj_size, first_size, self->_obj_size);
    }

    if (second_size > 0)
    {
        obj_copy(new_obj + first_size * self->_obj_size, self->obj, second_size, self->_obj_size);
    }

    free(self->obj);
    self->obj = new_obj;
    self->_capacity = real_capacity;
    self->_head = 0;
    self->_tail = first_size + second_size;
    self->_size = self->_tail;

    return true;
}

static size_t ringbuf_size(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t ringbuf_capacity(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    return self->_capacity - 1;
}

static bool ringbuf_empty(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    return self->_head == self->_tail;
}

static bool ringbuf_full(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    return self->_head == index_next(self->_tail, self->_capacity);
}

static bool ringbuf_clear(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;
    self->_head = 0;
    self->_tail = 0;
    return true;
}

static void ringbuf_destory(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);
    if (self->obj != NULL && self->_dynamic == true)
    {
        free(self->obj);
        self->obj = NULL;
    }
}

static void ringbuf_print(struct _ringbuf *self)
{
    unicstl_assert(self != NULL);

    for (size_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(obj_at(self->obj, self->_obj_size, i));
    }
}

bool ringbuf_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ringbuf_t self = (ringbuf_t)iter->_container;

    if (iter->_order == RINGBUF_FORWARD)
    {
        if (iter->_index == self->_tail)
        {
            return false;
        }
    }
    else
    {
        if (iter->_index == self->_head)
        {
            return false;
        }
    }
    return true;
}

const void *ringbuf_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    ringbuf_t self = (ringbuf_t)iter->_container;

    size_t index = iter->_index;
    if (iter->_order == RINGBUF_FORWARD)
    {
        iter->_index = index_next(index, self->_capacity);
    }
    else
    {
        iter->_index = index_prev(index, self->_capacity);
    }

    return obj_at(self->obj, index, self->_obj_size);
}

iterator_t ringbuf_iter(struct _ringbuf *self, enum _ringbuf_order order)
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

    iter->hasnext = ringbuf_iter_hasnext;
    iter->next = ringbuf_iter_next;
    return iter;
}

/**
 * @brief
 *
 * @param self
 * @param obj_size
 * @param capacity
 * @param mem_pool !!! mem_pool_size = capacity * obj_size
 * @return true
 * @return false
 */
bool ringbuf_init(struct _ringbuf *self, size_t obj_size, size_t capacity, void *mem_pool)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity + 1;

    if (mem_pool != NULL)
    {
        self->obj = (char *)mem_pool;
        self->_dynamic = false;
    }
    else
    {
        self->obj = (char *)unicstl_malloc(self->_obj_size * self->_capacity);
        if (self->obj == NULL)
        {
            return false;
        }
        self->_dynamic = true;
    }

    self->_head = 0;
    self->_tail = 0;

    self->_destory = ringbuf_destory;

    // -------------------- public --------------------
    // kernel
    self->push_back = ringbuf_push_back;
    self->push_front = ringbuf_push_front;
    self->pop_back = ringbuf_pop_back;
    self->pop_front = ringbuf_pop_front;
    self->back = ringbuf_back;
    self->front = ringbuf_front;

    // random access
    self->get = ringbuf_get;
    self->set = ringbuf_set;
    self->at = ringbuf_at;

    // base
    self->resize = ringbuf_resize;
    self->size = ringbuf_size;
    self->capacity = ringbuf_capacity;
    self->empty = ringbuf_empty;
    self->full = ringbuf_full;
    self->clear = ringbuf_clear;

    // iter
    self->iter = ringbuf_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = ringbuf_print;

    return true;
}

ringbuf_t ringbuf_new(size_t obj_size, size_t capacity)
{
    struct _ringbuf *ringbuf = NULL;
    ringbuf = (struct _ringbuf *)unicstl_malloc(sizeof(struct _ringbuf));
    if (ringbuf == NULL)
    {
        return NULL;
    }

    if (ringbuf_init(ringbuf, obj_size, capacity, NULL) != true)
    {
        free(ringbuf);
        return NULL;
    }
    return ringbuf;
}

void ringbuf_free(ringbuf_t *ringbuf)
{
    if (*ringbuf != NULL)
    {
        (*ringbuf)->_destory(*ringbuf);
        free(*ringbuf);
    }
    *ringbuf = NULL;
}
