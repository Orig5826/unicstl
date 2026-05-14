/**
 * @file unicstl_embed.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-14
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _UNICSTL_EMBED_H_
#define _UNICSTL_EMBED_H_

#include "unicstl.h"

typedef struct _ringbuf estack_t;
typedef struct _ringbuf equeue_t;


// ------------------------------ embedded stack ------------------------------
static inline bool estack_init(estack_t *self, size_t obj_size, size_t capacity, void *mem_pool)
{
    if(mem_pool == NULL)
    {
        return false;
    }
    return ringbuf_init(self, obj_size, capacity, mem_pool);
}

static inline bool estack_push(estack_t *self, const void *obj)
{
    if(self->full(self))
    {
        return false;
    }
    return self->push_back(self, obj);
}

static inline bool estack_pop(estack_t *self, void *obj)
{
    return self->pop_back(self, obj);
}

static inline bool estack_peek(estack_t *self, void *obj)
{
    return self->back(self, obj);
}

static inline size_t estack_size(estack_t *self)
{
    return self->size(self);
}

static inline size_t estack_capacity(estack_t *self)
{
    return self->capacity(self);
}

static inline bool estack_empty(estack_t *self)
{
    return self->empty(self);
}

static inline bool estack_full(estack_t *self)
{
    return self->full(self);
}

static inline bool estack_clear(estack_t *self)
{
    return self->clear(self);
}



// ------------------------------ embedded queue ------------------------------
static inline bool equeue_init(equeue_t *self, size_t obj_size, size_t capacity, void *mem_pool)
{
    if(mem_pool == NULL)
    {
        return false;
    }
    return ringbuf_init(self, obj_size, capacity, mem_pool);
}

static inline bool equeue_push(equeue_t *self, const void *obj)
{
    return self->push_back(self, obj);
}

static inline bool equeue_push_force(equeue_t *self, const void *obj)
{
    if(self->full(self))
    {
        self->pop_front(self, NULL);
    }
    return self->push_back(self, obj);
}

static inline bool equeue_pop(equeue_t *self, void *obj)
{
    return self->pop_front(self, obj);
}

static inline bool equeue_back(equeue_t *self, void *obj)
{
    return self->back(self, obj);
}

static inline bool equeue_front(equeue_t *self, void *obj)
{
    return self->front(self, obj);
}

static inline size_t equeue_size(equeue_t *self)
{
    return self->size(self);
}

static inline size_t equeue_capacity(equeue_t *self)
{
    return self->capacity(self);
}

static inline bool equeue_empty(equeue_t *self)
{
    return self->empty(self);
}

static inline bool equeue_full(equeue_t *self)
{
    return self->full(self);
}

static inline bool equeue_clear(equeue_t *self)
{
    return self->clear(self);
}


#endif
