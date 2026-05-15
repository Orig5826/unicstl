/**
 * @file segarray.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "segarray.h"

static inline size_t clac_start_index(size_t capacity)
{
    return capacity <= 2 ? 0 : (capacity - 1)/ 2;
}

static inline const darray_t get_seg(struct _segarray *self, struct _obj_pos pos)
{
    return (const darray_t)self->_map->at(self->_map, pos.map);
}

static inline void * get_obj(struct _segarray *self, struct _obj_pos pos, void *obj)
{
    darray_t darray = get_seg(self, pos);
    return (void *)darray->at(darray, pos.seg);
}

static inline void print_pos(struct _segarray *self)
{
    printf("head[%d][%d], tail[%d][%d]\n", self->_head.map, self->_head.seg,
           self->_tail.map, self->_tail.seg);
}


static bool segarray_push_back(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL)
    {
        return false;
    }
    ringbuf_t map = self->_map;

    print_pos(self);

    if (self->_tail.seg == self->_capacity - 1)
    {
        if(map->full(map))
        {
            size_t new_capacity = unicstl_new_capacity(self->capacity(self));
            if (!map->resize(map, new_capacity))
            {
                printf("map->resize(map, new_capacity) failed!");
                return false;
            }
        }
        else
        {
            darray_t seg = darray_new(self->_obj_size, self->_capacity);
            if(seg == NULL)
            {
                printf("darray_new failed!");
                return false;
            }
            map->push_back(map, &seg);
        }
    }

    darray_t seg;
    if(!map->back(map, &seg))
    {
        printf("map->back failed!");
        return false;
    }
    size_t index = self->_tail.seg;
    printf("index = %d\n", index);
    if(!seg->set(seg, index, obj))
    {
        printf("seg->set failed!");
        return false;
    }
    self->_tail.seg = ring_index_next(self->_tail.seg, self->_capacity);

    self->_size++;
    return true;
}

static bool segarray_push_front(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL)
    {
        return false;
    }

    if (self->full(self))
    {
        if(self->_dynamic != true)
        {
            return false;
        }
        size_t new_capacity = unicstl_new_capacity(self->capacity(self));
        if (self->resize(self, new_capacity) == false)
        {
            return false;
        }
    }

    // const darray_t seg = (const darray_t)self->_map->at(self->_map, self->_head.map);
    // if(seg == NULL)
    // {
    //     return false;
    // }
    // self->obj = seg->at(seg, self->_head.seg);
    // if(self->obj == NULL)
    // {
    //     return false;
    // }

    // size_t index = ring_index_prev(self->_head.seg, self->_capacity);
    // obj_set(self->obj, index, obj, self->_obj_size);
    // self->_head.seg = index;

    self->_size++;
    return true;
}

static bool segarray_pop_back(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || self->empty(self))
    {
        return false;
    }

    // size_t index = ring_index_prev(self->_tail.seg, self->_capacity);
    // if(obj != NULL)
    // {
    //     obj_get(self->obj, index, obj, self->_obj_size);
    // }
    // self->_tail = index;

    self->_size--;
    return true;
}

static bool segarray_pop_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || self->empty(self))
    {
        return false;
    }

    if (self->empty(self))
    {
        return false;
    }

    self->_size--;
    return true;
}

static bool segarray_back(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL|| self->empty(self))
    {
        return false;
    }


    return true;
}

static bool segarray_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if(self->obj == NULL || obj == NULL|| self->empty(self))
    {
        return false;
    }

    
    return true;
}

static bool segarray_resize(struct _segarray *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (self->_dynamic != true || capacity == 0 || capacity > UNICSTL_CAPACITY_MAX - 1)
    {
        return false;
    }

    return true;
}

static size_t segarray_size(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t segarray_capacity(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    // return self->_capacity;
    return self->_capacity * self->_map->size(self->_map);
}

static bool segarray_empty(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == 0;
}

static bool segarray_full(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    size_t map_cap = self->_map->size(self->_map);

    return (self->_head.map == 0 && self->_head.seg == 0) ||
           ( self->_tail.map == map_cap - 1 && self->_head.seg == self->_capacity - 1);
}

static bool segarray_clear(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;
    
    self->_head.map = clac_start_index(self->_map->capacity(self->_map));
    self->_tail.map = self->_head.map;

    self->_head.seg = clac_start_index(self->capacity(self));
    self->_tail.seg = self->_head.seg;
    return true;
}

static void segarray_destory(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    if (self->obj != NULL && self->_dynamic == true)
    {
        free(self->obj);
        self->obj = NULL;
    }
}

static void segarray_print(struct _segarray *self)
{
    unicstl_assert(self != NULL);

    for (size_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(obj_at(self->obj, self->_obj_size, i));
    }
}

bool segarray_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    segarray_t self = (segarray_t)iter->_container;

    if (iter->_order == SEGARRAY_FORWARD)
    {

    }
    else
    {

    }
    return true;
}

const void *segarray_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    segarray_t self = (segarray_t)iter->_container;

    size_t index = iter->_index;
    if (iter->_order == SEGARRAY_FORWARD)
    {
        //iter->_index = index_next(index, self->_capacity);
    }
    else
    {
        //iter->_index = index_prev(index, self->_capacity);
    }

    return obj_at(self->obj, index, self->_obj_size);
}

iterator_t segarray_iter(struct _segarray *self, enum _segarray_order order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;

    //..

    iter->hasnext = segarray_iter_hasnext;
    iter->next = segarray_iter_next;
    return iter;
}

/**
 * @brief
 *
 * @param self
 * @param obj_size
 * @param capacity
 * @param mem_pool !!! mem_pool_size = capacity * obj_size
 * @return true
 * @return false
 */
bool segarray_init(struct _segarray *self, size_t obj_size, size_t capacity, void *mem_pool)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity + 1;

    if (mem_pool != NULL)
    {
        self->obj = (char *)mem_pool;
        self->_dynamic = false;
    }
    else
    {
        self->_dynamic = true;

        self->_map = ringbuf_new(sizeof(darray_t), 8);
        if(self->_map == NULL)
        {
            return false;
        }

        darray_t seg = darray_new(obj_size, capacity);
        if(seg == NULL)
        {
            ringbuf_free(&self->_map);
            return false;
        }
        // config first obj index in seg array
        self->_head.seg = clac_start_index(self->_capacity);
        self->_tail.seg = self->_head.seg;

        // add first seg array to map
        self->_head.map = 0;
        self->_tail.map = 0;
        self->_map->push_back(self->_map, &seg);
    }

    self->_destory = segarray_destory;

    // -------------------- public --------------------
    // kernel
    self->push_back = segarray_push_back;
    self->push_front = segarray_push_front;
    self->pop_back = segarray_pop_back;
    self->pop_front = segarray_pop_front;
    self->back = segarray_back;
    self->front = segarray_front;

    // base
    self->resize = segarray_resize;
    self->size = segarray_size;
    self->capacity = segarray_capacity;
    self->empty = segarray_empty;
    self->full = segarray_full;
    self->clear = segarray_clear;

    // iter
    self->iter = segarray_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = segarray_print;

    return true;
}

segarray_t segarray_new(size_t obj_size, size_t capacity)
{
    struct _segarray *segarray = NULL;
    segarray = (struct _segarray *)unicstl_malloc(sizeof(struct _segarray));
    if (segarray == NULL)
    {
        return NULL;
    }

    if (segarray_init(segarray, obj_size, capacity, NULL) != true)
    {
        free(segarray);
        return NULL;
    }
    return segarray;
}

void segarray_free(segarray_t *segarray)
{
    if (*segarray != NULL)
    {
        (*segarray)->_destory(*segarray);
        free(*segarray);
    }
    *segarray = NULL;
}
