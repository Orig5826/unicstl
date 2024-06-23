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

bool list_append(struct _list* self, void* obj)
{
    assert(self != NULL);
    assert(self->obj != NULL);
    assert(obj != NULL);

    if (self->size(self) == self->_capacity)
    {
        int capacity = self->_capacity * self->_ratio;
        void * obj_new = (list_data_t*)realloc(self->obj, capacity * self->_obj_size);
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

bool list_insert(struct _list* self, int index, void* obj)
{
    assert(index >= 0 && index < (int)self->size(self));

    if (self->size(self) == self->_capacity)
    {
        int capacity = self->_capacity * self->_ratio;
        void* obj_new = (list_data_t*)realloc(self->obj, capacity * self->_obj_size);
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

bool list_pop(struct _list* self, int index, void* obj)
{
    assert(self != NULL);
    assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));		// list空的时候也会报错，太严格了有点

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

int list_index(struct _list* self, void* obj)
{
    return 0;
}

bool list_remove(struct _list* self, void* obj)
{
    assert(self != NULL);
    return true;
}

bool list_clear(struct _list* self)
{
    assert(self != NULL);
    self->_size = 0;
    return true;
}

bool list_get(struct _list* self, int index, void* obj)
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

bool list_set(struct _list* self, int index, void* obj)
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

uint32_t list_size(struct _list* self)
{
    return self->_size;
}

bool list_empty(struct _list* self)
{
    assert(self != NULL);
    return !self->size(self);
}

bool list_reverse(struct _list* self)
{
    return true;
}

bool list_sort(struct _list* self, uint8_t reserve, int (*compare)(void* obj, void* obj2))
{
    return true;
}

// free
void list_destory(struct _list* self)
{
    assert(self != NULL);
    if (self->obj != NULL)
    {
        free(self->obj);
    }
}

// print
void list_print(struct _list* self)
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

bool list_init2(struct _list* list, uint32_t obj_size, uint32_t capacity)
{
    assert(list != NULL);

    // 1. set attr
    list->_obj_size = obj_size;
    list->_size = 0;
    list->_capacity = capacity;
    list->_ratio = 2;

    // 2. set function
    // kernel
    list->append = list_append;
    list->get = list_get;
    list->clear = list_clear;
    list->destory = list_destory;
    list->empty = list_empty;
    list->index = list_index;
    list->insert = list_insert;
    list->pop = list_pop;
    list->print = list_print;
    list->remove = list_remove;
    list->reverse = list_reverse;
    list->set = list_set;
    list->size = list_size;
    list->sort = list_sort;

    // 3. set array
    list->obj = (void*)calloc(list->_capacity, list->_obj_size);
    if (list->obj == NULL)
    {
        return false;
    }
    return true;
}

list_t list_new(void)
{
    return (struct _list*)malloc(sizeof(struct _list));
}

void list_free(list_t list)
{
    if(list != NULL)
    {
        list->destory(list);
        free(list);
    }
}
