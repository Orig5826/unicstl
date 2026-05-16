/**
 * @file rawbuf.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "rawbuf.h"

static size_t rawbuf_capacity(struct _rawbuf *self)
{
    unicstl_assert(self != NULL);
    return self->_capacity;
}

static bool rawbuf_set(struct _rawbuf *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->capacity(self) || obj == NULL)
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    memmove((char *)self->obj + offset, obj, self->_obj_size);
    return true;
}

static bool rawbuf_get(struct _rawbuf *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->capacity(self) || obj == NULL)
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    memmove(obj, (char *)self->obj + offset, self->_obj_size);
    return true;
}

const void *rawbuf_at(struct _rawbuf *self, size_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->capacity(self))
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    return (const char *)self->obj + offset;
}

static void rawbuf_destory(struct _rawbuf *self)
{
    unicstl_assert(self != NULL);
    if (self->obj != NULL && self->_dynamic == true)
    {
        unicstl_free(self->obj);
    }
}

bool rawbuf_init(struct _rawbuf *self, size_t obj_size, size_t capacity, void *mem_base)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);
    if(capacity == 0)
    {
        return false;
    }

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_capacity = capacity;

    self->obj = mem_base;
    self->_dynamic = false;

    self->_destory = rawbuf_destory;
    // -------------------- public --------------------
    // kernel
    self->set = rawbuf_set;
    self->get = rawbuf_get;
    self->at = rawbuf_at;

    self->capacity = rawbuf_capacity;

    // -------------------- malloc --------------------
    if(self->obj == NULL)
    {
        self->obj = unicstl_malloc(capacity * obj_size);
        if (self->obj == NULL)
        {
            return false;
        }
        self->_dynamic = true;
    }
    return true;
}

rawbuf_t rawbuf_new(size_t obj_size, size_t capacity)
{
    struct _rawbuf *rawbuf = NULL;
    rawbuf = (struct _rawbuf *)unicstl_malloc(sizeof(struct _rawbuf));
    if (rawbuf == NULL)
    {
        log_warn("rawbuf malloc failed!");
        return NULL;
    }

    if (rawbuf_init(rawbuf, obj_size, capacity, NULL) != true)
    {
        log_warn("rawbuf init failed!");
        unicstl_free(rawbuf);
        return NULL;
    }
    return rawbuf;
}

void rawbuf_free(rawbuf_t *rawbuf)
{
    if (rawbuf != NULL && *rawbuf != NULL)
    {
        if ((*rawbuf)->_destory != NULL)
        {
            (*rawbuf)->_destory((*rawbuf));
        }
        unicstl_free(*rawbuf);
        *rawbuf = NULL;
    }
}
