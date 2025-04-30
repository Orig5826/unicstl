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
#if 0
    assert(self != NULL);
    int i = 0;
    bool unlimited = false;
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
            end = self->size(self);
        }
    }
    else
    {
        if (start == LIST_UNLIMITED)
        {
            start = self->size(self) - 1;
            unlimited = true;
        }

        if (end == LIST_UNLIMITED)
        {
            end = 0;
            unlimited = true;
        }
    }

    if (start < 0)
    {
        if (start < -self->size(self))
        {
            start = -self->size(self);
        }
        start += self->size(self);
    }
    else
    {
        if (start > self->size(self))
        {
            start = self->size(self);
        }
    }

    if (end < 0)
    {
        if (end < -self->size(self))
        {
            end = -self->size(self);
        }
        end += self->size(self);
    }
    else
    {
        if (end > self->size(self))
        {
            end = self->size(self);
        }
    }

    // printf("start = %d\n", start);
    // printf("end = %d\n", end);

    uint32_t capicity = (end - start == 0) ? 1 : abs(end - start);
    list_t list = list_new2(self->_obj_size, capicity);
    if (list == NULL)
    {
        return NULL;
    }
    list->compare = self->compare;
    list->print_obj = self->print_obj;

    if (capicity == 0 || start > self->size(self) || end > self->size(self))
    {
        goto done;
    }

    if (step > 0)
    {
        if (start > end)
        {
            goto done;
        }

        if (unlimited != true)
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
        if (start < end)
        {
            goto done;
        }

        if (unlimited != true)
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
#else
    assert(self != NULL);
    list_t list = NULL;
    bool empty = false;
    uint32_t capacity = 1;
    int i = 0;
    bool contain_last_obj = false;
    int temp = 0;
    bool negative = false;

    int start0 = start;
    int end0 = end;
    if (step == 0)
    {
        return NULL;
    }

    if(start0 == LIST_UNLIMITED)
    {
        start = 0 - (int)LIST_UNLIMITED;
    }

    if(end0 == LIST_UNLIMITED)
    {
        end = (int)LIST_UNLIMITED;
    }

    if(start < 0)
    {
        start += (int)self->size(self);
        if(start < 0)
        {
            start = 0;
        }
    }
    else
    {
        if(start >= (int)self->size(self))
        {
            empty = true;
        }
    }

    if(end < 0)
    {
        end += (int)self->size(self);
        if(end < 0)
        {
            empty = true;
        }
    }
    else
    {
        if (end >= (int)self->size(self))
        {
            end = (int)self->size(self);
        }

        if(step < 0)
        {
            contain_last_obj = true;
        }
    }

    if(step < 0)
    {
        negative = true;
        step = -step;
        
        temp = start;
        if(start >= 0)
        {
            start = end + 1;
        }
        else
        {
            start = end;
        }

        if(end >= 0)
        {
            end = temp + 1;
        }
        else
        {
            end = temp;
        }
        end = temp;
    }

    if(start >= end)
    {
        empty = true;
    }

    if (empty != true)
    {
        capacity = end - start;
    }
    list = list_new2(self->_obj_size, capacity);
    if (list == NULL)
    {
        return NULL;
    }
    list->compare = self->compare;
    list->print_obj = self->print_obj;

    if(empty != true)
    {
        if(negative != true)
        {
            if (contain_last_obj != true)
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
        else
        {
            if (contain_last_obj != true)
            {
                for (i = start; i < end; i += step)
                {
                    list->insert(list, 0, (char*)self->obj + i * self->_obj_size);
                }
            }
            else
            {
                for (i = start; i <= end; i += step)
                {
                    list->insert(list, 0, (char*)self->obj + i * self->_obj_size);
                }
            }
        }
    }

done:
    return list;
#endif
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

static bool list_init2(struct _list* list, uint32_t obj_size, uint32_t capacity)
{
    assert(list != NULL);
    if (list == NULL || obj_size == 0 || capacity == 0)
    {
        return false;
    }

    // -------------------- private -------------------- 
    list->_obj_size = obj_size;
    list->_size = 0;
    list->_capacity = capacity;
    list->_ratio = 2;
    list->_cur = 0;

    list->obj = (void*)malloc(list->_capacity * list->_obj_size);
    if (list->obj == NULL)
    {
        return false;
    }

    list->_iter.next = list_iter_next;
    list->_iter.hasnext = list_iter_hasnext;

    list->_destory = list_destory;

    // -------------------- public -------------------- 
    // kernel
    list->append = list_append;
    list->pop = list_pop;

    list->insert = list_insert;
    list->delete = list_delete;

    list->get = list_get;
    list->set = list_set;

    list->index = list_index;
    // list->contains = list_contains;

    // base
    list->clear = list_clear;
    list->size = list_size;
    list->empty = list_empty;
    list->capacity = list_capacity;

    // iter
    list->iter = list_iter;

    // others
    list->slice = list_slice;

    // config
    list->compare = default_compare;
    // -------------------- debug --------------------
    list->print_obj = default_print_obj;
    list->print = list_print;

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
