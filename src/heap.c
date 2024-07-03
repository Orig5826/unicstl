/**
 * @brief 
 * 
 * @param self 
 * @param obj_size 
 * @return true 
 * @return false 
 */
#include "heap.h"

bool heap_peek(struct _heap* self, void* obj)
{
    assert(self != NULL);
    if(obj == NULL)
    {
        return false;
    }
    if(self->empty(self))
    {
        return false;
    }
    memmove(obj, self->obj, self->_obj_size);
    return true;
}

bool heap_push(struct _heap* self, void* obj)
{

}

bool heap_pop(struct _heap* self, void* obj)
{

}

void heap_setmin(struct _heap* self, bool min_flag)
{
    assert(self != NULL);
    self->_min_flag = min_flag;
}

uint32_t heap_size(struct _heap* self)
{
    assert(self != NULL);
    return self->_size;
}

bool heap_empty(struct _heap* self)
{
    assert(self != NULL);
    return self->size(self) == 0;
}

bool heap_clear(struct _heap* self)
{
    assert(self != NULL);
}

void heap_destory(struct _heap* self)
{
    assert(self != NULL);
}

void heap_print(struct _heap* self)
{
    assert(self != NULL);
    assert(self->obj != NULL);

    void* obj = NULL;
    uint32_t offset = 0;

    for (int i = self->size(self) - 1; i >= 0; i--)
    {
        offset = self->_obj_size * i;
        obj = (char*)self->obj + offset;
        self->print_obj(obj);
    }
}

bool heap_init2(struct _heap* self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);

    // 1. set attr
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_ratio = 2;

    self->peek = heap_peek;
    self->push = heap_push;
    self->pop = heap_pop;
    self->size = heap_size;
    self->empty = heap_empty;
    self->clear = heap_clear;
    self->destory = heap_destory;
    self->setmin = heap_setmin;
    self->print = heap_print;

    self->obj = (void*)malloc(self->_capacity * self->_obj_size);
    if(self->obj == NULL)
    {
        return false;
    }
    return true;
}

heap_t heap_new(void)
{
    return (struct _heap*)malloc(sizeof(struct _heap));
}

void heap_free(heap_t heap)
{
    if(heap)
    {
        heap->destory(heap);
        free(heap);
    }
}
