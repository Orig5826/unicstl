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
#include "algo.h"

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
        unicstl_free(self->obj);
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

    const void *obj = NULL;
    for (size_t i = 0; i < self->size(self); i++)
    {
        obj = obj_at(self, i, self->_obj_size);
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
        if (self->resize(self, new_capacity) == false)
        {
            return false;
        }
    }

    if (index < self->size(self))
    {
        obj_shift(self->obj, index + 1, index, self->size(self) - index, self->_obj_size);
    }
    // copy new data
    obj_copy((char *)self->obj + index * self->_obj_size, obj, 1, self->_obj_size);

    self->_size += 1;
    self->_sorted = false;
    return true;
}

static bool darray_remove(struct _darray *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self) || index >= self->size(self))
    {
        return false;
    }

    size_t count = self->size(self) - 1 - index;
    if (obj != NULL)
    {
        size_t offset = index * self->_obj_size;
        obj_copy(obj, self->obj + offset, 1, self->_obj_size);
    }
    obj_shift(self->obj, index, index + 1, count, self->_obj_size);

    self->_size -= 1;
    return true;
}

static bool darray_append(struct _darray *self, const void *obj)
{
    return self->insert(self, self->size(self), obj);
}

static bool darray_pop(struct _darray *self, void *obj)
{
    return self->remove(self, self->size(self) - 1, obj);
}

static bool darray_set(struct _darray *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    obj_set(self->obj, index, obj, self->_obj_size);
    return true;
}

static bool darray_get(struct _darray *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    obj_get(self->obj, index, obj, self->_obj_size);
    return true;
}

const void *darray_at(struct _darray *self, size_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self))
    {
        return false;
    }
    return obj_at(self->obj, index, self->_obj_size);
}

bool darray_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    darray_t self = (darray_t)iter->_container;

    if (iter->_order == LINEAR_FORWARD)
    {
        if (iter->_index >= self->size(self))
        {
            return false;
        }
    }
    else
    {
        if (iter->_index == 0)
        {
            return false;
        }
    }
    return true;
}

const void *darray_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    darray_t self = (darray_t)iter->_container;

    size_t index = iter->_index;
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index++;
    }
    else
    {
        iter->_index = iter->_index - 1;
    }
    return self->at(self, index);
}

iterator_t darray_iter(struct _darray *self, linear_order_t order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index = 0;
    }
    else
    {
        iter->_index = self->size(self) - 1;
    }

    iter->hasnext = darray_iter_hasnext;
    iter->next = darray_iter_next;
    return iter;
}

static size_t darray_index(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj);
}

static bool darray_contains(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj) != (size_t) - 1;
}

static bool darry_sort(struct _darray *self)
{
    unicstl_assert(self != NULL);
    if(self->_sorted)
    {
        return true;
    }
#ifdef UNICSTL_SORT
    bubble_sort(self->obj, self->size(self), self->_obj_size, self->compare);
#else
    qsort(self->obj, self->size(self), self->_obj_size, self->compare);
#endif
    self->_sorted = true;
    return true;
}

static size_t darry_search(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(obj == NULL)
    {
        return -1;
    }
#ifdef UNICSTL_BSEARCH
    if(self->_sorted)
    {
        return unicstl_search(obj, self->obj, self->size(self), self->_obj_size, self->compare);
    }
#else
    if(self->_sorted)
    {
        log_debug("bsearch of standard library");
        const void *addr = bsearch(obj, self->obj, self->size(self), self->_obj_size, self->compare);
        if(addr != NULL)
        {
            return (addr - self->obj) / self->_obj_size;
        }
    }
#endif
    return linear_search(obj, self->obj, self->size(self), self->_obj_size, self->compare);
}

static size_t darry_count(struct _darray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(obj == NULL)
    {
        return 0;
    }
    size_t count = 0;
    size_t index = 0;

    if(self->_sorted)
    {
        size_t index = self->search(self, obj);
        if(index == (size_t)-1)
        {
            return 0;
        }
    }
    for(size_t i = index; i < self->size(self); i++)
    {
        if (self->compare((const char *)self->obj + i * self->_obj_size, (const char *)obj) != 0)
        {
            break;
            
        }
        count++;
    }
    return count;
}

static bool darray_init(struct _darray *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;

    self->_sorted = false;

    self->obj = NULL;
    self->_destory = darray_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = darray_insert;
    self->remove = darray_remove;
    self->append = darray_append;
    self->pop = darray_pop;
    
    self->set = darray_set;
    self->get = darray_get;
    self->at = darray_at;

    // base
    self->resize = darray_resize;
    self->size = darray_size;
    self->capacity = darray_capacity;
    self->empty = darray_empty;
    self->full = darray_full;
    self->clear = darray_clear;

    // iter
    self->iter = darray_iter;

    // sort and search
    self->index = darray_index;
    self->contains = darray_contains;
    self->sort = darry_sort;
    self->search = darry_search;

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
        log_warn("darray malloc failed!");
        return NULL;
    }

    if (darray_init(darray, obj_size, capacity) != true)
    {
        log_warn("darray init failed!");
        unicstl_free(darray);
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
        unicstl_free(*darray);
        *darray = NULL;
    }
}
