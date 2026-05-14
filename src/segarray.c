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

static inline struct _obj_pos index_next(struct _segarray *self, const struct _obj_pos* cur_pos)
{
    struct _obj_pos pos;
    pos.map = cur_pos->map;
    pos.seg = cur_pos->seg;

    if(pos.seg + 1 >= self->_capacity)
    {
        pos.map++;
        pos.seg = 0;
    }
    else
    {
        pos.seg++;
    }
    return pos;
}

static inline struct _obj_pos index_prev(struct _segarray *self, const struct _obj_pos* cur_pos)
{
    struct _obj_pos pos;
    pos.map = cur_pos->map;
    pos.seg = cur_pos->seg;

    if (pos.map == 0 && pos.seg == 0) {
        return pos;
    }

    if(pos.seg == 0)
    {
        pos.map--;
        pos.seg = self->_capacity - 1;
    }
    else
    {
        pos.seg--;
    }
    return pos;
}

static bool segarray_push_back(struct _segarray *self, const void *obj)
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
        // size_t new_capacity = unicstl_new_capacity(self->capacity(self));
        // if (self->resize(self, new_capacity) == false)
        // {
        //     return false;
        // }
    }


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
    return self->_capacity;
}

static bool segarray_empty(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    return self->_head.map == self->_tail.map && self->_head.seg == self->_tail.seg;
}

static bool segarray_full(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    size_t map_cap = self->_map->capacity(self->_map);

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

        self->_map = darray_new(sizeof(darray_t), 8);
        if(self->_map == NULL)
        {
            return false;
        }

        darray_t seg = darray_new(obj_size, capacity);
        if(seg == NULL)
        {
            darray_free(&self->_map);
            return false;
        }

        self->_head.map = clac_start_index(self->_map->capacity(self->_map));
        self->_tail.map = self->_head.map;

        self->_head.seg = clac_start_index(self->_capacity);
        self->_tail.seg = self->_head.seg;
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
