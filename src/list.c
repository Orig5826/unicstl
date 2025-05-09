/**
 * @file list.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "list.h"


static bool list_insert(struct _list* self, int index, void* obj)
{
    // assert(index >= 0 && index < (int)self->size(self));
    // assert(index >= 0 && index <= (int)self->size(self));
    if (index < 0 || index >(int)self->size(self))
    {
        return false;
    }

    if (self->size(self) == self->_capacity)
    {
        int capacity = self->_capacity * self->_ratio;
        void* obj_new = (void*)realloc(self->obj, capacity * self->_obj_size);
        if (obj_new == NULL)
        {
            return false;
        }
        self->obj = obj_new;
        self->_capacity = capacity;
    }
    uint32_t offset = index * self->_obj_size;
    uint32_t offset1 = (index + 1) * self->_obj_size;
    uint32_t count = self->size(self) - index;

    // move data to right
    memmove((char*)self->obj + offset1, (char*)self->obj + offset, count * self->_obj_size);
    // copy new data
    memmove((char*)self->obj + offset, obj, self->_obj_size);
    self->_size += 1;
    return true;
}

static bool list_delete(struct _list* self, int index, void* obj)
{
    assert(self != NULL);
    // assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));
    if (index < (int)(0 - self->size(self)) || index >= (int)self->size(self))
    {
        return false;
    }

    if (self->empty(self))
    {
        return false;
    }

    if (index < 0)
    {
        index += self->size(self);
    }

    uint32_t offset = index * self->_obj_size;
    uint32_t offset1 = (index + 1) * self->_obj_size;
    uint32_t count = self->size(self) - 1 - index;
    if (obj != NULL)
    {
        memmove(obj, (char*)self->obj + offset, self->_obj_size);
    }
    memmove((char*)self->obj + offset, (char*)self->obj + offset1, count * self->_obj_size);
    self->_size -= 1;
    return true;
}

static bool list_append(struct _list* self, void* obj)
{
    return self->insert(self, (int)self->size(self), obj);
}

static bool list_pop(struct _list* self, void* obj)
{
    if (self->empty(self))
    {
        return false;
    }
    return self->delete(self, (int)self->size(self) - 1, obj);
}

static int list_index(struct _list* self, void* obj)
{
    assert(self != NULL);
    int index = 0;
    if (obj == NULL)
    {
        return -1;
    }

    while (index < (int)self->size(self))
    {
        if (self->compare(self->obj + index * self->_obj_size, obj) == 0)
        {
            return index;
        }
        index++;
    }

    return -1;
}

static bool list_clear(struct _list* self)
{
    assert(self != NULL);
    self->_size = 0;
    return true;
}

static bool list_get(struct _list* self, int index, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));

    if (index < 0)
    {
        index += self->size(self);
    }
    uint32_t offset = index * self->_obj_size;
    memmove(obj, (char*)self->obj + offset, self->_obj_size);
    return true;
}

static bool list_set(struct _list* self, int index, void* obj)
{
    assert(self != NULL);
    assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));
    if (index < 0)
    {
        index += self->size(self);
    }
    uint32_t offset = index * self->_obj_size;
    memmove((char*)self->obj + offset, obj, self->_obj_size);
    return true;
}

static uint32_t list_size(struct _list* self)
{
    assert(self != NULL);
    return self->_size;
}

static uint32_t list_capacity(struct _list* self)
{
    assert(self != NULL);
    return self->_capacity;
}

static bool list_empty(struct _list* self)
{
    assert(self != NULL);
    return !self->size(self);
}

// free
static void list_destory(struct _list* self)
{
    assert(self != NULL);
    if (self->obj != NULL)
    {
        free(self->obj);
    }
}

// print
static void list_print(struct _list* self)
{
    assert(self != NULL);

    if (!self->empty(self))
    {
        void* obj = NULL;

        for (uint32_t i = 0; i < self->size(self); i++)
        {
            obj = (char*)self->obj + i * self->_obj_size;
            self->print_obj(obj);
        }
    }
}

static int list_index_exchange(struct _list* self, int index)
{
    assert(self != NULL);
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
struct _list* list_slice(struct _list* self, int start, int end, int step)
{
    assert(self != NULL);
    int i = 0;
    bool contains_last_obj = false;
    int size = (int)self->size(self);
    int capicity = 1;
    list_t list = NULL;

    if (step == 0)
    {
        return NULL;
    }

    if (step > 0)
    {
        if (start == LIST_UNLIMITED)
        {
            start = 0;
        }

        if (end == LIST_UNLIMITED)
        {
            end = size;
        }
    }
    else
    {
        if (start == LIST_UNLIMITED)
        {
            start = size - 1;
        }

        if (end == LIST_UNLIMITED)
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
    list = list_new2(self->_obj_size, capicity);
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
                list->append(list, (char*)self->obj + i * self->_obj_size);
            }
        }
        else
        {
            for (i = start; i <= end; i += step)
            {
                list->append(list, (char*)self->obj + i * self->_obj_size);
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
                list->append(list, (char*)self->obj + i * self->_obj_size);
            }
        }
        else
        {
            for (i = start; i >= end; i += step)
            {
                list->append(list, (char*)self->obj + i * self->_obj_size);
            }
        }
    }

done:
    return list;
}

static bool list_iter_hasnext(struct _iterator* iter)
{
    list_t self = (list_t)iter->_container;

    if (iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

static const void* list_iter_next(struct _iterator* iter)
{
    list_t self = (list_t)iter->_container;
    void* obj = self->obj + iter->_index * self->_obj_size;
    iter->_index += 1;
    return obj;
}

iterator_t list_iter(struct _list* self)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;

    iter->hasnext = list_iter_hasnext;
    iter->next = list_iter_next;
    return iter;
}

static bool list_init2(struct _list* self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);
    if (self == NULL || obj_size == 0 || capacity == 0)
    {
        return false;
    }

    // -------------------- private -------------------- 
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_ratio = 2;
    self->_cur = 0;

    self->obj = (void*)malloc(self->_capacity * self->_obj_size);
    if (self->obj == NULL)
    {
        return false;
    }

    self->_iter.next = list_iter_next;
    self->_iter.hasnext = list_iter_hasnext;

    self->_destory = list_destory;

    // -------------------- public -------------------- 
    // kernel
    self->append = list_append;
    self->pop = list_pop;

    self->insert = list_insert;
    self->delete = list_delete;

    self->get = list_get;
    self->set = list_set;

    self->index = list_index;
    // self->contains = list_contains;

    // base
    self->clear = list_clear;
    self->size = list_size;
    self->empty = list_empty;
    self->capacity = list_capacity;

    // iter
    self->iter = list_iter;

    // others
    self->slice = list_slice;

    // -------------------- default --------------------
    self->compare = default_compare;
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = list_print;

    return true;
}

list_t list_new2(uint32_t obj_size, uint32_t capacity)
{
    struct _list* list = NULL;
    list = (struct _list*)calloc(1, sizeof(struct _list));
    if (list == NULL)
    {
        return NULL;
    }

    if (list_init2(list, obj_size, capacity) != true)
    {
        free(list);
        return NULL;
    }
    return list;
}

void list_free(list_t* list)
{
    assert(list != NULL);
    if (list != NULL && *list != NULL)
    {
        if ((*list)->_destory != NULL)
        {
            (*list)->_destory(*list);
        }
        free(*list);
        *list = NULL;
    }
}
