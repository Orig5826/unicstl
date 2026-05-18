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
    if(index < 0)
    {
        return index + size;
    }
    return index;
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

static bool arraylist_reserve(struct _arraylist *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->reserve(self->_darray, capacity);
}

static bool arraylist_insert(struct _arraylist *self, ssize_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    index = calc_index(index, self->size(self));
    if(index < 0)
    {
        index += 1;
        log_debug("index < 0, index = %zd", index);
    }
    return self->_darray->insert(self->_darray, index, obj);
}

static bool arraylist_remove(struct _arraylist *self, ssize_t index, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    index = calc_index(index, self->size(self));
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
    index = calc_index(index, self->size(self));
    return self->_darray->set(self->_darray, index, obj);
}

static bool arraylist_get(struct _arraylist *self, ssize_t index, void *obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    index = calc_index(index, self->size(self));
    return self->_darray->get(self->_darray, (size_t)index, obj);
}

const void *arraylist_at(struct _arraylist *self, ssize_t index)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
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
    self->_darray->compare = self->compare;
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


static int list_index_exchange(struct _arraylist *self, int index)
{
    unicstl_assert(self != NULL);
    int size = (int)self->size(self);

    if (index < 0)
    {
        index += size;
        if (index < 0)
        {
            index = 0;
        }
    }
    else
    {
        if (index > size)
        {
            index = size;
        }
    }
    return index;
}

/**
 * @brief list slice
 *  if index < 0, from the end of list. for example:
 *  list[-1] is the last element in list.
 *
 * @param self
 * @param start start index
 * @param end end index
 * @param step step, if step < 0, return a reverse list.
 * @return struct _list*
 *  a copy of the list, from start to end, step by step.
 *      if step < 0, return a reverse list.
 *      if step > 0, return a forward list.
 *      if step == 0, return NULL.
 */
struct _arraylist * arraylist_slice(struct _arraylist *self, ssize_t start, ssize_t end, ssize_t step)
{
    unicstl_assert(self != NULL);
    int i = 0;
    bool contains_last_obj = false;
    int size = (int)self->size(self);
    int capicity = 1;
    arraylist_t list = NULL;

    if (step == 0)
    {
        return NULL;
    }

    if (step > 0)
    {
        if (start == SLICE_UNLIMITED)
        {
            start = 0;
        }

        if (end == SLICE_UNLIMITED)
        {
            end = size;
        }
    }
    else
    {
        if (start == SLICE_UNLIMITED)
        {
            start = size - 1;
        }

        if (end == SLICE_UNLIMITED)
        {
            end = 0;
            contains_last_obj = true;
        }
    }

    start = list_index_exchange(self, start);
    end = list_index_exchange(self, end);

    if(abs(end - start) != 0)
    {
        capicity = abs(end - start);
    }
    list = arraylist_new(self->_darray->_obj_size, 0);
    if (list == NULL)
    {
        return NULL;
    }
    list->compare = self->compare;
    list->print_obj = self->print_obj;

    if (step > 0)
    {
        if (start >= end)
        {
            goto done;
        }

        if (contains_last_obj != true)
        {
            for (i = start; i < end; i += step)
            {
                list->append(list, self->at(self, i));
            }
        }
        else
        {
            for (i = start; i <= end; i += step)
            {
                list->append(list, self->at(self, i));
            }
        }
    }
    else /*if(step < 0)*/
    {
        if (start <= end)
        {
            goto done;
        }

        if (contains_last_obj != true)
        {
            for (i = start; i > end; i += step)
            {
                list->append(list, self->at(self, i));
            }
        }
        else
        {
            for (i = start; i >= end; i += step)
            {
                list->append(list, self->at(self, i));
            }
        }
    }
done:
    return list;
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
    self->reserve = arraylist_reserve;
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

    // 
    self->slice = arraylist_slice;

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
    self->_darray->compare = self->compare;
    self->_darray->print_obj = self->print_obj;
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
