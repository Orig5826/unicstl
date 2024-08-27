/**
 * @brief 
 * 
 * @param self 
 * @param obj_size 
 * @return true 
 * @return false 
 */
#include "heap.h"

static int left(int i)
{
    return 2 * i + 1;
}

static int right(int i)
{
    return (i << 1) + 2;
}

static int parent(int i)
{
    if(i == 0)
    {
        return -1;
    }
    return (i-1) >> 1;
}

bool heap_peek(struct _heap* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
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

static void heap_swap(struct _heap* self, int i, int j)
{
    assert(self != NULL);
    assert(self->_obj_size != 0);
// #define C99_VLA
#ifdef C99_VLA
    char tmp[self->_obj_size];
#else
    char* tmp = malloc(self->_obj_size);
    if (tmp == NULL)
    {
        return;
    }
#endif

    memmove(tmp, (char *)self->obj + i * self->_obj_size, self->_obj_size);
    memmove((char*)self->obj + i * self->_obj_size, (char*)self->obj + j * self->_obj_size, self->_obj_size);
    memmove((char*)self->obj + j * self->_obj_size, tmp, self->_obj_size);

#ifndef C99_VLA
    free(tmp);
#endif
}

static void heap_fixed_up(struct _heap* self, int i)
{
    assert(self != NULL);
    int p = 0;
    if(self->_min_flag != true)
    {
        while(1)
        {
            p = parent(i);
            // 若当前节点大于其父节点，则交换位置，否则退出循环
            if(p < 0 || self->compare((char *)self->obj + i * self->_obj_size, (char *)self->obj + p * self->_obj_size) <= 0)
            {
                break;
            }
            heap_swap(self, i, p);
            i = p;
        }
    }
    else
    {
        while(1)
        {
            p = parent(i);
            // 若当前节点大于其父节点，则交换位置，否则退出循环
            if(p < 0 || self->compare((char *)self->obj + i * self->_obj_size, (char *)self->obj + p * self->_obj_size) >= 0)
            {
                break;
            }
            heap_swap(self, i, p);
            i = p;
        }
    }
}

bool heap_push(struct _heap* self, void* obj)
{
    assert(self != NULL);
    if(self->size(self) > self->_capacity)
    {
        return false;
    }
    uint32_t index = self->size(self);
    memmove((char *)self->obj + index * self->_obj_size, obj, self->_obj_size);
    self->_size++;

    heap_fixed_up(self, index);
    return true;
}

static void heap_fixed_down(struct _heap* self, int i)
{
    assert(self != NULL);
    int l = 0,r = 0;
    int max = 0, min = 0;

    if(self->_min_flag != true)
    {
        while(1)
        {
            l = left(i);
            r = right(i);
            max = i;

            if(l < self->size(self) && self->compare((char *)self->obj + l * self->_obj_size, (char *)self->obj + max * self->_obj_size) > 0)
            {
                max = l;
            }

            if(r < self->size(self) && self->compare((char *)self->obj + r * self->_obj_size, (char *)self->obj + max * self->_obj_size) > 0)
            {
                max = r;
            }
            if(max == i)
            {
                break;
            }
            heap_swap(self, i, max);
            i = max;
        }
    }
    else
    {
        while(1)
        {
            l = left(i);
            r = right(i);
            min = i;

            if(l < self->size(self) && self->compare((char *)self->obj + l * self->_obj_size, (char *)self->obj + min * self->_obj_size) < 0)
            {
                min = l;
            }

            if(r < self->size(self) && self->compare((char *)self->obj + r * self->_obj_size, (char *)self->obj + min * self->_obj_size) < 0)
            {
                min = r;
            }
            if(min == i)
            {
                break;
            }
            heap_swap(self, i, min);
            i = min;
        }
    }
}

bool heap_pop(struct _heap* self, void* obj)
{
    assert(self != NULL);
    if(self->empty(self))
    {
        return false;
    }
    int index = self->size(self) - 1;
    heap_swap(self, 0, index);
    if(obj != NULL)
    {
        memmove(obj, (char *)self->obj + index * self->_obj_size, self->_obj_size);
    }
    self->_size--;
    heap_fixed_down(self, 0);
    return true;
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
    self->_size = 0;
    return true;
}

void heap_destory(struct _heap* self)
{
    assert(self != NULL);
    self->clear(self);
    if(self->obj)
    {
        free(self->obj);
    }
}

void heap_print(struct _heap* self)
{
    assert(self != NULL);
    assert(self->obj != NULL);

    void* obj = NULL;
    uint32_t offset = 0;

    for (int i = 0; i < self->size(self); i++)
    {
        offset = self->_obj_size * i;
        obj = (char *)self->obj + offset;
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

void heap_free(heap_t* heap)
{
    if(*heap != NULL)
    {
        (*heap)->destory(*heap);
        free(*heap);
    }
    heap = NULL;
}
