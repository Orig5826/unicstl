/**
 * @file arraylist.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "arraylist.h"
#include "algo.h"

#ifdef UNICSTL_ARRAYLIST

static inline size_t calc_index(ssize_t index, size_t size)
{
    return (index + size) % size;
}

static size_t arraylist_size(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->size(self->_darray);
}

static size_t arraylist_capacity(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->capacity(self->_darray);
}

static bool arraylist_empty(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == 0;
}

static bool arraylist_full(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == self->capacity(self);
}

static bool arraylist_clear(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    self->_darray->clear(self->_darray);
    return true;
}

static void arraylist_destory(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    if(self->_darray != NULL)
    {
        darray_free(&self->_darray);
    }
}

static void arraylist_print(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    self->_darray->print_obj = self->print_obj;
    self->_darray->print(self->_darray);
}

static bool arraylist_resize(struct _arraylist *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->resize(self->_darray, capacity);
}

static bool arraylist_insert(struct _arraylist *self, ssize_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->insert(self->_darray, index, obj);
}

static bool arraylist_remove(struct _arraylist *self, ssize_t index, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->remove(self->_darray, index, obj);
}

static bool arraylist_append(struct _arraylist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->append(self->_darray, obj);
}

static bool arraylist_pop(struct _arraylist *self, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->pop(self->_darray, obj);
}

static bool arraylist_set(struct _arraylist *self, ssize_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    if (index < -(ssize_t)self->size(self) || index >= (ssize_t)self->size(self))
    {
        log_debug("arraylist_get index:%ld", index);
        return false;
    }
    index = calc_index(index, self->size(self));
    return self->_darray->set(self->_darray, index, obj);
}

static bool arraylist_get(struct _arraylist *self, ssize_t index, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    if (index < -(ssize_t)self->size(self) || index >= (ssize_t)self->size(self))
    {
        log_debug("arraylist_get index:%ld", index);
        return false;
    }
    index = calc_index(index, self->size(self));
    return self->_darray->get(self->_darray, (size_t)index, obj);
}

const void *arraylist_at(struct _arraylist *self, ssize_t index)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    if (index < -(ssize_t)self->size(self) || index >= (ssize_t)self->size(self))
    {
        log_debug("arraylist_get index:%ld", index);
        return false;
    }
    index = calc_index(index, self->size(self));
    return self->_darray->at(self->_darray, index);
}

bool arraylist_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);
    arraylist_t self = (arraylist_t)iter->_container;
    unicstl_assert(self->_iter_darray != NULL);

    return self->_iter_darray->hasnext(self->_iter_darray);
}

const void *arraylist_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);
    arraylist_t self = (arraylist_t)iter->_container;
    unicstl_assert(self->_iter_darray != NULL);

    return self->_iter_darray->next(self->_iter_darray);
}

iterator_t arraylist_iter(struct _arraylist *self, linear_order_t order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;

    self->_iter_darray = self->_darray->iter(self->_darray, order);

    iter->hasnext = arraylist_iter_hasnext;
    iter->next = arraylist_iter_next;
    return iter;
}

static ssize_t arraylist_index(struct _arraylist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj);
}

static bool arraylist_contains(struct _arraylist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->search(self, obj) != (size_t)-1;
}

static bool arraylist_sort(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->_darray->sort(self->_darray);
}

static ssize_t arraylist_search(struct _arraylist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    self->_darray->compare = self->compare;
    return self->_darray->search(self->_darray, obj);
}

static size_t arraylist_count(struct _arraylist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    return self->_darray->count(self->_darray, obj);
}

static bool arraylist_init(struct _arraylist *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_darray = NULL;
    self->_destory = arraylist_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = arraylist_insert;
    self->remove = arraylist_remove;
    self->append = arraylist_append;
    self->pop = arraylist_pop;

    self->set = arraylist_set;
    self->get = arraylist_get;
    self->at = arraylist_at;

    // base
    self->resize = arraylist_resize;
    self->size = arraylist_size;
    self->capacity = arraylist_capacity;
    self->empty = arraylist_empty;
    self->full = arraylist_full;
    self->clear = arraylist_clear;

    // iter
    self->iter = arraylist_iter;

    // sort and search
    self->index = arraylist_index;
    self->contains = arraylist_contains;
    self->sort = arraylist_sort;
    self->search = arraylist_search;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = arraylist_print;

    // -------------------- init --------------------
    self->_darray = darray_new(obj_size, capacity);
    if(self->_darray == NULL)
    {
        log_warn("self->_darray failed!");
        return false;
    }
    return true;
}

arraylist_t arraylist_new(size_t obj_size, size_t capacity)
{
    struct _arraylist *arraylist = NULL;
    arraylist = (struct _arraylist *)unicstl_malloc(sizeof(struct _arraylist));
    if (arraylist == NULL)
    {
        log_warn("arraylist malloc failed!");
        return NULL;
    }

    if (arraylist_init(arraylist, obj_size, capacity) != true)
    {
        log_warn("arraylist init failed!");
        unicstl_free(arraylist);
        return NULL;
    }
    return arraylist;
}

void arraylist_free(arraylist_t *arraylist)
{
    if (arraylist != NULL && *arraylist != NULL)
    {
        if ((*arraylist)->_destory != NULL)
        {
            (*arraylist)->_destory((*arraylist));
        }
        unicstl_free(*arraylist);
        *arraylist = NULL;
    }
}

#endif // UNICSTL_ARRAYLIST
