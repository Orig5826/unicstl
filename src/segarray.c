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
    return capacity <= 2 ? 0 : (capacity - 1) / 2;
}

static inline size_t segarray_map_full(struct _segarray *self, size_t capacity)
{
    return 0;
}

static bool segarray_push_back(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL)
    {
        return false;
    }

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;

    if (self->_segtail == self->_segsize)
    {
        if(self->_mapfree->empty(mapfree))
        {
            if (map->full(map))
            {
                // need resize 
                log_error("next, you need to realize it");
                return false;
            }
            else
            {
                rawbuf_t seg = rawbuf_new(self->_obj_size, self->_capacity);
                if (seg == NULL)
                {
                    log_error("rawbuf_new failed!");
                    return false;
                }
                map->push_back(map, &seg);
                self->_segtail = 0;
            }
        }
        else
        {
            rawbuf_t seg;
            if (!mapfree->pop_back(mapfree, &seg))
            {
                log_error("mapfree->pop_back failed!");
                return false;
            }
            if (!map->push_back(map, &seg))
            {
                log_error("map->push_back failed!");
                return false;
            }
            self->_seghead = 0;
        }
    }

    rawbuf_t seg;
    if (!map->back(map, &seg))
    {
        log_error("map->back failed!");
        return false;
    }
    size_t index = self->_segtail;
    if (!seg->set(seg, index, obj))
    {
        log_error("seg->set failed!");
        return false;
    }
    self->_segtail = index + 1;
    
    log_info("push_back success!");
    self->_size++;
    return true;
}

static bool segarray_push_front(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL)
    {
        return false;
    }

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;

    if (self->_seghead == 0)
    {
        if(self->_mapfree->empty(mapfree))
        {
            if (map->full(map))
            {
                // need resize 
                log_error("next, you need to realize it");
                return false;
            }
            else
            {
                rawbuf_t seg = rawbuf_new(self->_obj_size, self->_capacity);
                if (seg == NULL)
                {
                    log_error("rawbuf_new failed!");
                    return false;
                }
                map->push_front(map, &seg);
                self->_seghead = self->_segsize;
            }
        }
        else
        {
            rawbuf_t seg;
            if (!mapfree->pop_back(mapfree, &seg))
            {
                log_error("mapfree->pop_back failed!");
                return false;
            }
            if (!map->push_front(map, &seg))
            {
                log_error("map->push_back failed!");
                return false;
            }
            self->_seghead = self->_segsize;
        }
    }

    rawbuf_t seg;
    if (!map->front(map, &seg))
    {
        log_error("map->back failed!");
        return false;
    }
    size_t index = self->_seghead - 1;
    if (!seg->set(seg, index, obj))
    {
        log_error("seg->set failed!");
        return false;
    }
    self->_seghead = index;
    
    log_info("push_front success!");
    self->_size++;
    return true;
}

static bool segarray_pop_back(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || self->empty(self))
    {
        return false;
    }

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;
    rawbuf_t seg;

    size_t index = self->_segtail - 1;
    if(obj != NULL)
    {
        if (!map->back(map, &seg))
        {
            log_error("map->back failed!");
            return false;
        }
        if (!seg->get(seg, index, obj))
        {
            log_error("seg->set failed!");
            return false;
        }
    }
    self->_segtail = index;
    if(self->_segtail == 0)
    {
        self->_segtail = self->_segsize;

        map->pop_back(map, &seg);
        if (!mapfree->push_back(mapfree, &seg))
        {
            log_error("mapfree->push_back failed!");
            return false;
        }
    }

    log_info("pop_back success!");
    self->_size--;
    return true;
}

static bool segarray_pop_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || self->empty(self))
    {
        return false;
    }

    if (self->empty(self))
    {
        return false;
    }

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;

    size_t index = self->_seghead;
    if(obj != NULL)
    {
        rawbuf_t seg;
        if (!map->front(map, &seg))
        {
            log_error("map->back failed!");
            return false;
        }
        if (!seg->get(seg, index, obj))
        {
            log_error("seg->set failed!");
            return false;
        }
    }
    self->_seghead = index + 1;
    if(self->_seghead == self->_segsize)
    {
        self->_seghead = 0;

        rawbuf_t seg;
        map->pop_front(map, &seg);

        if (!mapfree->push_back(mapfree, &seg))
        {
            log_error("mapfree->push_back failed!");
            return false;
        }
    }

    log_info("pop_front success!");
    self->_size--;
    return true;
}

static bool segarray_back(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL || self->empty(self))
    {
        return false;
    }
    return self->get(self, self->size(self) - 1, obj);
}

static bool segarray_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL || self->empty(self))
    {
        return false;
    }
    return self->get(self, 0, obj);
}

static bool segarray_calc_index(struct _segarray *self, size_t index, size_t *map_index, size_t *seg_index)
{
    ringbuf_t map = self->_map;
    rawbuf_t seg = NULL;
    size_t map_idx;
    size_t seg_idx;

    size_t seg1_left = self->_segsize - self->_seghead;
    if(index < seg1_left)
    {
        map_idx = 0;
        seg_idx = self->_seghead + index;
    }
    else
    {
        size_t index_left = index - seg1_left;
        map_idx = index_left / self->_segsize + 1;
        seg_idx = index_left % self->_segsize;
    }
    *map_index = map_idx;
    *seg_index = seg_idx;
    return true;
}

static bool segarray_set(struct _segarray *self, size_t index, const void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }

    ringbuf_t map = self->_map;
    rawbuf_t seg = NULL;
    size_t map_index;
    size_t seg_index;

    segarray_calc_index(self, index, &map_index, &seg_index);
    
    if (!map->get(map, map_index, &seg))
    {
        return false;
    }
    return seg->set(seg, seg_index, obj);
}

static bool segarray_get(struct _segarray *self, size_t index, void *obj)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self) || obj == NULL)
    {
        return false;
    }
    ringbuf_t map = self->_map;
    rawbuf_t seg = NULL;
    size_t map_index;
    size_t seg_index;

    segarray_calc_index(self, index, &map_index, &seg_index);
    
    if (!map->get(map, map_index, &seg))
    {
        return false;
    }
    return seg->get(seg, seg_index, obj);
}

static const void* segarray_at(struct _segarray *self, size_t index)
{
    unicstl_assert(self != NULL);
    if (index >= self->size(self))
    {
        return false;
    }
    ringbuf_t map = self->_map;
    rawbuf_t seg = NULL;
    size_t map_index;
    size_t seg_index;

    segarray_calc_index(self, index, &map_index, &seg_index);
    
    if (!map->get(map, map_index, &seg))
    {
        return false;
    }
    return seg->at(seg, seg_index);
}

static bool segarray_resize(struct _segarray *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (self->_dynamic != true || capacity == 0 || capacity > UNICSTL_CAPACITY_MAX - 1)
    {
        return false;
    }

    if(capacity < self->_capacity)
    {
        return false;
    }

    log_error("you need to implement this function!");
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
    return self->size(self) == 0;
}

static bool segarray_full(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    size_t map_size = self->_map->size(self->_map);
    if(self->_map->full(self->_map))
    {
        if(self->_seghead == 0 || self->_segtail == self->_segsize - 1)
        {
            return true;
        }
    }
    return false;
}

static bool segarray_clear(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;

    self->_seghead = clac_start_index(self->_segsize);
    self->_segtail = self->_seghead;
    return true;
}

static void segarray_destory(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    ringbuf_t map = self->_map;
    if (self->_dynamic)
    {
        rawbuf_t seg = NULL;
        while(map->empty(map))
        {
            if (map->pop_back(map, &seg))
            {
                rawbuf_free(&seg);
            }
        }
        ringbuf_free(&map);
    }
}

static void segarray_print(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    const void *obj = NULL;

    for (size_t i = 0; i < self->size(self); i++)
    {
        obj = self->at(self, i);
        if(obj == NULL)
        {
            log_error("objs[%ld] is NULL", i);
            return;
        }
        self->print_obj(obj);
    }
}

bool segarray_iter_hasnext(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);
    segarray_t self = (segarray_t)iter->_container;

    if (iter->_order == SEGARRAY_FORWARD)
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

const void *segarray_iter_next(struct _iterator *iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);
    segarray_t self = (segarray_t)iter->_container;
    const void *obj = NULL;

    obj = self->at(self, iter->_index);
    if (iter->_order == SEGARRAY_FORWARD)
    {
        iter->_index++;
    }
    else
    {
        iter->_index--;
    }
    return obj;
}

iterator_t segarray_iter(struct _segarray *self, enum _segarray_order order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;

    if (iter->_order == SEGARRAY_FORWARD)
    {
        iter->_index = 0;
    }
    else
    {
        iter->_index = self->size(self) - 1;
    }

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
    self->_capacity = capacity;
    self->_segsize = capacity;

    if (mem_pool != NULL)
    {
        self->obj = (char *)mem_pool;
        self->_dynamic = false;
    }
    else
    {
        self->_dynamic = true;

        self->_map = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_map == NULL)
        {
            return false;
        }

        self->_mapfree = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_mapfree == NULL)
        {
            ringbuf_free(&self->_map);
            return false;
        }

        rawbuf_t seg = rawbuf_new(obj_size, self->_segsize);
        if (seg == NULL)
        {
            ringbuf_free(&self->_map);
            ringbuf_free(&self->_mapfree);
            return false;
        }
        // config first obj index in seg array
        self->_seghead = clac_start_index(self->_segsize);
        self->_segtail = self->_seghead;

        // add first seg array to map
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

    // -------------------- random access -------------------- 
    self->set = segarray_set;
    self->get = segarray_get;
    self->at = segarray_at;

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
        log_warn("segarray malloc failed");
        return NULL;
    }

    if (segarray_init(segarray, obj_size, capacity, NULL) != true)
    {
        log_warn("segarray init failed");
        unicstl_free(segarray);
        return NULL;
    }
    return segarray;
}

void segarray_free(segarray_t *segarray)
{
    if (*segarray != NULL)
    {
        (*segarray)->_destory(*segarray);
        unicstl_free(*segarray);
    }
    *segarray = NULL;
}
