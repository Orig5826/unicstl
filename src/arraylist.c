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
#ifdef UNICSTL_ARRAYLIST

#include "arraylist.h"
#include "algo.h"

static size_t arraylist_size(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t arraylist_capacity(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->_capacity;
}

static bool arraylist_empty(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->_size == 0;
}

static bool arraylist_full(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    return self->_size == self->_capacity;
}

static bool arraylist_clear(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;
    return true;
}

static void arraylist_destory(struct _arraylist *self)
{
    unicstl_assert(self != NULL);
    if (self->obj != NULL)
    {
        unicstl_free(self->obj);
    }
}

static void arraylist_print(struct _arraylist *self)
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

static bool arraylist_resize(struct _arraylist *self, size_t capacity)
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

static bool arraylist_insert(struct _arraylist *self, ssize_t index, const void *obj)
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

    self->_sorted = false;
    return true;
}

static bool arraylist_remove(struct _arraylist *self, ssize_t index, void *obj)
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

static bool arraylist_append(struct _arraylist *self, const void *obj)
{
    return arraylist_insert(self, self->size(self), obj);
}

static bool arraylist_pop(struct _arraylist *self, void *obj)
{
    return arraylist_remove(self, self->size(self) - 1, obj);
}

static bool arraylist_set(struct _arraylist *self, ssize_t index, const void *obj)
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

static bool arraylist_get(struct _arraylist *self, ssize_t index, void *obj)
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

const void *arraylist_at(struct _arraylist *self, ssize_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self))
    {
        return false;
    }
    size_t offset = index * self->_obj_size;
    return (const char *)self->obj + offset;
}

bool arraylist_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    arraylist_t self = (arraylist_t)iter->_container;

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

const void *arraylist_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    arraylist_t self = (arraylist_t)iter->_container;

    size_t index = iter->_index;
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index++;
    }
    else
    {
        iter->_index = iter->_index - 1;
    }
    return obj_at(self->obj, index, self->_obj_size);
}

iterator_t arraylist_iter(struct _arraylist *self, enum _arraylist_order order)
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

static ssize_t arraylist_search(struct _arraylist *self, const void *obj)
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
        const void *addr = bsearch(obj, self->obj, self->size(self), self->_obj_size, self->compare);
        if(addr != NULL)
        {
            return (addr - self->obj) / self->_obj_size;
        }
    }
#endif
    return linear_search(obj, self->obj, self->size(self), self->_obj_size, self->compare);
}

static size_t arraylist_count(struct _arraylist *self, const void *obj)
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

static bool arraylist_init(struct _arraylist *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;

    self->_sorted = false;

    self->obj = NULL;
    self->_destory = arraylist_destory;


    // -------------------- public --------------------
    // kernel
    self->resize = arraylist_resize;
    self->insert = arraylist_insert;
    self->remove = arraylist_remove;
    self->append = arraylist_append;
    self->pop = arraylist_pop;

    self->set = arraylist_set;
    self->get = arraylist_get;
    self->at = arraylist_at;
    self->index = arraylist_index;
    self->contains = arraylist_contains;

    self->size = arraylist_size;
    self->capacity = arraylist_capacity;
    self->empty = arraylist_empty;
    self->full = arraylist_full;
    self->clear = arraylist_clear;

    // iter
    self->iter = arraylist_iter;

    // sort and search
    self->sort = arraylist_sort;
    self->search = arraylist_search;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = arraylist_print;

    // -------------------- malloc --------------------
    if(capacity > 0)
    {
        self->resize(self, capacity);
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
