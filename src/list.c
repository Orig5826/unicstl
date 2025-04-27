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

static bool list_append(struct _list* self, void* obj)
{
    assert(self != NULL);
    assert(self->obj != NULL);
    assert(obj != NULL);

    if (self->size(self) == self->_capacity)
    {
        int capacity = self->_capacity * self->_ratio;
        void * obj_new = (void *)realloc(self->obj, capacity * self->_obj_size);
        if (obj_new == NULL)
        {
            return false;
        }
        self->obj = obj_new;
        self->_capacity = capacity;
    }
    uint32_t index = self->size(self);
    uint32_t offset = index * self->_obj_size;
    memmove((char*)self->obj + offset, obj, self->_obj_size);

    self->_size += 1;
    return true;
}

static bool list_insert(struct _list* self, int index, void* obj)
{
    assert(index >= 0 && index < (int)self->size(self));

    if (self->size(self) == self->_capacity)
    {
        int capacity = self->_capacity * self->_ratio;
        void* obj_new = (void *)realloc(self->obj, capacity * self->_obj_size);
        if (obj_new == NULL)
        {
            return false;
        }
        self->obj = obj_new;
        self->_capacity = capacity;
    }
    uint32_t offset = index * self->_obj_size;
    uint32_t offset1 = (index + 1) * self->_obj_size;

    memmove((char*)self->obj + offset, (char*)self->obj + offset, self->size(self) * self->_obj_size);
    self->_size += 1;
    return true;
}

static bool list_pop(struct _list* self, int index, void* obj)
{
    assert(self != NULL);
    assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));

    if (self->empty(self))
    {
        return false;
    }

    if (index < 0)
    {
        index += self->size(self);
    }

    uint32_t count = self->size(self) - 1 - index;
    uint32_t offset = index * self->_obj_size;
    uint32_t offset1 = (index + 1) * self->_obj_size;
    if (obj != NULL)
    {
        memmove(obj, (char*)self->obj + offset, self->_obj_size);
    }
    memmove((char*)self->obj + offset, (char*)self->obj + offset1, count * self->_obj_size);
    self->_size -= 1;
    return true;
}

static int list_index(struct _list* self, void* obj)
{
    return 0;
}

static bool list_remove(struct _list* self, void* obj)
{
    assert(self != NULL);
    return true;
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
    return self->_size;
}

static bool list_empty(struct _list* self)
{
    assert(self != NULL);
    return !self->size(self);
}

static bool list_reverse(struct _list* self)
{
    return true;
}

static bool list_sort(struct _list* self, uint8_t reserve, int (*compare)(void* obj, void* obj2))
{
    return true;
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

static const void* list_iter_next(struct _iterator* iter)
{
    list_t self = (list_t)iter->_container;
    void *obj = self->obj + iter->_index * self->_obj_size;
    iter->_index += 1;
    return obj;
}

static bool list_iter_hasnext(struct _iterator* iter)
{
    list_t self = (list_t)iter->_container;

    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

iterator_t list_iter(struct _list* self)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    return iter;
}

static bool list_init2(struct _list* list, uint32_t obj_size, uint32_t capacity)
{
    assert(list != NULL);
    assert(obj_size > 0);
    assert(capacity > 0);
    if(list == NULL || obj_size == 0 || capacity == 0)
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
    list->insert = list_insert;
    list->pop = list_pop;

    list->empty = list_empty;

    // base
    list->clear = list_clear;
    list->size = list_size;

    // iter
    list->iter = list_iter;

    // others
    list->index = list_index;
    list->remove = list_remove;
    list->get = list_get;
    list->set = list_set;

    // list->reverse = list_reverse;
    // list->sort = list_sort;

    // -------------------- debug -------------------- 
    list->print = list_print;
    
    return true;
}

list_t list_new2(uint32_t obj_size, uint32_t capacity)
{
    struct _list* list = NULL;
    list = (struct _list*)calloc(1, sizeof(struct _list));
    if(list == NULL)
    {
        return NULL;
    }
    
    if(list_init2(list, obj_size, capacity) != true)
    {
        free(list);
        return NULL;
    }
    return list;
}

void list_free(list_t* list)
{
    assert(list != NULL);
    if(list != NULL && *list != NULL)
    {
        if((*list)->_destory != NULL)
        {
            (*list)->_destory(*list);
        }
        free(*list);
        *list = NULL;
    }
}
