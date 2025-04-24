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

static bool heap_peek(struct _heap* self, void* obj)
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
    assert(self->compare != NULL);
    int p = 0;

    if(self->compare == NULL)
    {
        return ;
    }
    
    if(self->_type == HEAP_MAX)
    {
        while(1)
        {
            p = parent(i);
            // if current node is greater than its parent, swap the position. otherwise break out of loop
            if(p < 0 || self->compare((char *)self->obj + i * self->_obj_size, (char *)self->obj + p * self->_obj_size) <= 0)
            {
                break;
            }
            heap_swap(self, i, p);
            i = p;
        }
    }
    else /* if(self->_type == HEAP_MIN) */
    {
        while(1)
        {
            p = parent(i);
            // if current node is less than its parent, swap the position. otherwise break out of loop
            if(p < 0 || self->compare((char *)self->obj + i * self->_obj_size, (char *)self->obj + p * self->_obj_size) >= 0)
            {
                break;
            }
            heap_swap(self, i, p);
            i = p;
        }
    }
}

static bool heap_push(struct _heap* self, void* obj)
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

    if(self->compare == NULL)
    {
        return;
    }

    if(self->_type == HEAP_MAX)
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
    else /* if(self->_type == HEAP_MIN) */
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

static bool heap_pop(struct _heap* self, void* obj)
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

static uint32_t heap_size(struct _heap* self)
{
    assert(self != NULL);
    return self->_size;
}

static bool heap_empty(struct _heap* self)
{
    assert(self != NULL);
    return self->size(self) == 0;
}

static bool heap_clear(struct _heap* self)
{
    assert(self != NULL);
    self->_size = 0;
    return true;
}

static void heap_destory(struct _heap* self)
{
    assert(self != NULL);
    self->clear(self);
    if(self->obj)
    {
        free(self->obj);
    }
}

static void heap_print(struct _heap* self)
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


iterator_t heap_iter(struct _heap* self)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_parent = self;
    iter->_cur = 0;
    iter->_cur_node = self->obj;
    return iter;
}

bool heap_iter_hasnext(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    heap_t self = (heap_t)iter->_parent;
    if(iter->_cur < self->size(self))
    {
        return true;
    }
    return false;
}

const void* heap_iter_next(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    heap_t self = (heap_t)iter->_parent;
    void *obj = NULL;

    uint32_t index = self->_iter._cur;
    obj = self->obj + self->_obj_size * index;

    self->_iter._cur += 1;
    return obj;
}

static bool heap_init2(struct _heap* self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);

    // -------------------- private -------------------- 
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_ratio = 2;

    self->obj = (void*)malloc(self->_capacity * self->_obj_size);
    if(self->obj == NULL)
    {
        return false;
    }

    self->_iter.hasnext = heap_iter_hasnext;
    self->_iter.next = heap_iter_next;
    
    self->_destory = heap_destory;

    // -------------------- public -------------------- 
    // kernel
    self->peek = heap_peek;
    self->push = heap_push;
    self->pop = heap_pop;
    self->empty = heap_empty;

    // base
    self->size = heap_size;
    self->clear = heap_clear;

    // iter
    self->iter = heap_iter;

    // config
    self->compare = NULL;
    
    // -------------------- debug -------------------- 
    self->print = heap_print;
    return true;
}

heap_t heap_max_new2(uint32_t obj_size, uint32_t capacity)
{
    heap_t heap = NULL;
    heap = (struct _heap*)malloc(sizeof(struct _heap));
    if(heap == NULL)
    {
        return NULL;
    }

    if(heap_init2(heap, obj_size, capacity) != true)
    {
        free(heap);
        return NULL;
    }

    heap->_type = HEAP_MAX;
    return heap;
}

heap_t heap_min_new2(uint32_t obj_size, uint32_t capacity)
{
    heap_t heap = NULL;
    heap = (struct _heap*)malloc(sizeof(struct _heap));
    if(heap == NULL)
    {
        return NULL;
    }

    if(heap_init2(heap, obj_size, capacity) != true)
    {
        free(heap);
        return NULL;
    }

    heap->_type = HEAP_MIN;
    return heap;
}

void heap_free(heap_t* heap)
{
    if(*heap != NULL)
    {
        (*heap)->_destory(*heap);
        free(*heap);
    }
    *heap = NULL;
}
