/**
 * @file darray.c
 * @author wenjf (orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "darray.h"

static size_t darray_size(struct _darray *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t darray_capacity(struct _darray *self)
{
    unicstl_assert(self != NULL);
    return self->_capacity;
}

static bool darray_empty(struct _darray *self)
{
    unicstl_assert(self != NULL);
    return self->_size == 0;
}

static bool darray_full(struct _darray *self)
{
    unicstl_assert(self != NULL);
    return self->_size == self->_capacity;
}

static bool darray_clear(struct _darray *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;
    return true;
}

static void darray_destory(struct _darray *self)
{
    unicstl_assert(self != NULL);
    if (self->obj != NULL)
    {
        free(self->obj);
    }
}

static void darray_print(struct _darray *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->print_obj != NULL);
    if (self->obj == NULL)
    {
        return;
    }

    void *obj = NULL;
    size_t offset = 0;

    for (size_t i = 0; i < self->size(self); i++)
    {
        offset = self->_obj_size * i;
        obj = (char *)self->obj + offset;
        self->print_obj(obj);
    }
}

static bool darray_resize(struct _darray *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    if(capacity == 0 || capacity > UNICSTL_CAPACITY_MAX)
    {
        return false;
    }

    void *new_obj = unicstl_realloc(self->obj, capacity * self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    self->obj = new_obj;
    self->_capacity = capacity;
    if(self->_size > self->_capacity)
    {
        self->_size = self->_capacity;
    }
    return true;
}

static bool darray_insert(struct _darray *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index > self->size(self) || obj == NULL)
    {
        return false;
    }

    if (self->full(self))
    {
        size_t new_capacity = unicstl_new_capacity(self->capacity(self));
        if (darray_resize(self, new_capacity) == false)
        {
            return false;
        }
    }

    size_t offset = index * self->_obj_size;
    if (index < self->size(self))
    {
        size_t offset1 = (index + 1) * self->_obj_size;
        size_t count = self->size(self) - index;
        // move data to right
        memmove((char *)self->obj + offset1, (char *)self->obj + offset, count * self->_obj_size);
    }
    // copy new data
    memmove((char *)self->obj + offset, obj, self->_obj_size);
    self->_size += 1;
    return true;
}

static bool darray_remove(struct _darray *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self) || index >= self->size(self))
    {
        return false;
    }

    size_t offset = index * self->_obj_size;
    size_t offset1 = (index + 1) * self->_obj_size;
    size_t count = self->size(self) - 1 - index;
    if (obj != NULL)
    {
        memmove(obj, (char *)self->obj + offset, self->_obj_size);
    }
    memmove((char *)self->obj + offset, (char *)self->obj + offset1, count * self->_obj_size);
    self->_size -= 1;
    return true;
}

static bool darray_append(struct _darray *self, const void *obj)
{
    return darray_insert(self, self->size(self), obj);
}

static bool darray_pop(struct _darray *self, void *obj)
{
    return darray_remove(self, self->size(self) - 1, obj);
}

static bool darray_set(struct _darray *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    memmove((char *)self->obj + offset, obj, self->_obj_size);
    return true;
}

static bool darray_get(struct _darray *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    memmove(obj, (char *)self->obj + offset, self->_obj_size);
    return true;
}

const void *darray_at(struct _darray *self, size_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self))
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    return (const char *)self->obj + offset;
}

static size_t darray_index(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (obj == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < self->size(self); ++i)
    {
        if (self->compare((const char *)self->obj + i * self->_obj_size, (const char *)obj) == 0)
        {
            return i;
        }
    }
    return -1;
}

static bool darray_contains(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return darray_index(self, obj) != -1;
}

static bool darray_init(struct _darray *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size != 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;

    self->obj = NULL;
    self->_destory = darray_destory;

    // -------------------- public --------------------
    // kernel
    self->resize = darray_resize;
    self->insert = darray_insert;
    self->remove = darray_remove;
    self->append = darray_append;
    self->pop = darray_pop;

    self->set = darray_set;
    self->get = darray_get;
    self->at = darray_at;
    self->index = darray_index;
    self->contains = darray_contains;

    self->size = darray_size;
    self->capacity = darray_capacity;
    self->empty = darray_empty;
    self->full = darray_full;
    self->clear = darray_clear;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = darray_print;

    // -------------------- malloc --------------------
    if(capacity > 0)
    {
        self->resize(self, capacity);
    }
    return true;
}

darray_t darray_new(size_t obj_size, size_t capacity)
{
    struct _darray *darray = NULL;
    darray = (struct _darray *)unicstl_malloc(sizeof(struct _darray));
    if (darray == NULL)
    {
        return NULL;
    }

    if (darray_init(darray, obj_size, capacity) != true)
    {
        free(darray);
        return NULL;
    }
    return darray;
}

void darray_free(darray_t *darray)
{
    if (darray != NULL && *darray != NULL)
    {
        if ((*darray)->_destory != NULL)
        {
            (*darray)->_destory((*darray));
        }
        free(*darray);
        *darray = NULL;
    }
}
