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
    // return 0;
    // return capacity - 1;
    return capacity <= 2 ? 0 : (capacity - 1) / 2;
}

static bool segarray_add_first_segment(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    log_debug("segarray_add_first_segment");

    if(self->_map == NULL && self->_mapfree == NULL)
    {
        log_debug("self->_map == NULL");
        self->_map = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_map == NULL)
        {
            log_warn("self->_map new failed!");
            return false;
        }

        log_debug("self->_mapfree == NULL");
        self->_mapfree = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_mapfree == NULL)
        {
            log_warn("self->_mapfree new failed!");
            ringbuf_free(&self->_map);
            return false;
        }

        rawbuf_t seg = rawbuf_new(self->_obj_size, self->_segsize);
        if (seg == NULL)
        {
            log_warn("seg new failed!");
            ringbuf_free(&self->_map);
            ringbuf_free(&self->_mapfree);
            return false;
        }
        // config first obj index in seg array
        self->_seghead = clac_start_index(self->_segsize);
        self->_segtail = self->_seghead;

        // add first seg array to map
        if(!self->_map->push_back(self->_map, &seg))
        {
            log_warn("self->_map push back failed!");
            rawbuf_free(&seg);
            ringbuf_free(&self->_map);
            ringbuf_free(&self->_mapfree);
            return false;
        }

        if(self->_capacity == 0)
        {
            self->_capacity = self->_segsize;
        }
    }

    log_debug("segarray_add_first_segmen: ok");
    return true;
}

static bool segarray_push_back(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL)
    {
        return false;
    }
    segarray_add_first_segment(self);

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;

    if (self->_segtail == self->_segsize)
    {
        if(self->_mapfree->empty(mapfree))
        {
            log_debug("mapfree is empty!");
            if (map->full(map))
            {
                // reserve 
                size_t capacity_new = unicstl_new_capacity(self->_capacity);
                if(self->reserve(self, capacity_new))
                {
                    log_error("next, you need to realize it");
                    return false;
                }
            }
            else
            {
                rawbuf_t seg = rawbuf_new(self->_obj_size, self->_segsize);
                if (seg == NULL)
                {
                    log_error("rawbuf_new failed!");
                    return false;
                }
                if (!map->push_back(map, &seg))
                {
                    log_error("map->push_back failed!");
                    return false;
                }
            }
        }
        else
        {
            log_debug("mapfree is not empty!");
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
        }

        self->_segtail = 0;
    }
    log_debug("segtail=%zu", self->_segtail);

    rawbuf_t seg;
    if (!map->back(map, &seg))
    {
        log_error("map->back failed!");
        return false;
    }
    size_t index = self->_segtail;
    log_debug("segtail=%zu", index);
    if (!seg->set(seg, index, obj))
    {
        log_error("seg->set failed!");
        return false;
    }
    self->_segtail = index + 1;
    
    log_debug("push_back success!");
    self->_size++;
    if(self->_capacity < self->_size)
    {
        self->_capacity = unicstl_new_capacity(self->_capacity);
    }
    return true;
}

static bool segarray_push_front(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL)
    {
        return false;
    }
    segarray_add_first_segment(self);

    ringbuf_t map = self->_map;
    ringbuf_t mapfree = self->_mapfree;
    
    if (self->_seghead == 0)
    {
        if(self->_mapfree->empty(mapfree))
        {
            if (map->full(map))
            {
                // reserve 
                size_t capacity_new = unicstl_new_capacity(self->_capacity);
                if(self->reserve(self, capacity_new))
                {
                    log_error("next, you need to realize it");
                    return false;
                }
            }
            else
            {
                rawbuf_t seg = rawbuf_new(self->_obj_size, self->_segsize);
                if (seg == NULL)
                {
                    log_error("rawbuf_new failed!");
                    return false;
                }
                map->push_front(map, &seg);
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
        }

        self->_seghead = self->_segsize;
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
    
    log_debug("push_front success!");
    self->_size++;
    if(self->_capacity < self->_size)
    {
        self->_capacity = unicstl_new_capacity(self->_capacity);
    }
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

        if(!map->pop_back(map, &seg))
        {
            log_error("mapfree->pop_back failed!");
            return false;
        }

        if (!mapfree->push_back(mapfree, &seg))
        {
            log_error("mapfree->push_back failed!");
            return false;
        }
    }

    log_debug("pop_back success!");
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
        if(!map->pop_front(map, &seg))
        {
            log_error("mapfree->pop_back failed!");
            return false;
        }

        if (!mapfree->push_back(mapfree, &seg))
        {
            log_error("mapfree->push_back failed!");
            return false;
        }
    }

    log_debug("pop_front success!");
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
    log_debug("back");
    return self->get(self, self->size(self) - 1, obj);
}

static bool segarray_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL || self->empty(self))
    {
        return false;
    }
    log_debug("front");
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

/**
 * @brief 
 *      map_size == capacity/self->_segsize + 2;
 * 
 * @param self 
 * @param capacity 
 * @return true 
 * @return false 
 */
static bool segarray_reserve(struct _segarray *self, size_t capacity)
{
    unicstl_assert(self != NULL);
    if (capacity == 0 || capacity > UNICSTL_CAPACITY_MAX - 1)
    {
        return false;
    }
    log_debug("old_capacity: %lu", capacity);

    size_t map_size = capacity/self->_segsize + 2;
    log_debug("map_size: %lu", map_size);
    if(map_size > 8)
    {
        ringbuf_t map = self->_map;
        if(map_size > map->size(map))
        {
            // reserve
            if(map->reserve(map, map_size))
            {
                log_error("reserve map failed!");
                return true;
            }
            if(self->_mapfree->reserve(self->_mapfree, map_size))
            {
                log_error("reserve mapfree failed!");
                return true;
            }
        }
        else
        {
            while(!self->_mapfree->empty(self->_mapfree))
            {
                rawbuf_t seg = NULL;
                if(self->_mapfree->pop_back(self->_mapfree, &seg))
                {
                    log_error("pop mapfree failed!");
                    return true;
                }

                if(self->_map->push_back(self->_map, &seg))
                {
                    log_error("push map failed!");
                    return true;
                }
            }

            size_t map_use = self->_map->size(self->_map);
            for(size_t i = map_use; i < map_size; i++)
            {
                rawbuf_t seg = NULL;
                if(self->_map->pop_back(self->_mapfree, &seg))
                {
                    log_error("pop mapfree failed!");
                    return true;
                }
                rawbuf_free(&seg);
            }
        }
    }

    if(self->size(self) > capacity)
    {
        size_t seg_nouse = self->size(self) - capacity;
        for(size_t i = 0; i < seg_nouse; i++)
        {
            self->pop_back(self, NULL);
        }
        self->_size = capacity;
    }
    self->_capacity = capacity;
    log_debug("new_capacity: %lu", self->_capacity);
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
    return self->size(self) == self->capacity(self);
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
    ringbuf_t map_used[2] = {
        self->_map,
        self->_mapfree
    };

    rawbuf_t seg = NULL;

    ringbuf_t map = self->_map;
    if(map != NULL)
    {
        for(size_t i = 0; i < 2; i++)
        {
            map = map_used[i];
            while(!map->empty(map))
            {
                if (map->pop_back(map, &seg))
                {
                    if(seg == NULL)
                    {
                        log_error("seg is NULL");
                    }
                    rawbuf_free(&seg);
                }
            }
        }
    }
    ringbuf_free(&self->_map);
    ringbuf_free(&self->_mapfree);

    log_debug("segarray destoryed!");
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

    if (iter->_order == LINEAR_FORWARD)
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
    if (iter->_order == LINEAR_FORWARD)
    {
        iter->_index++;
    }
    else
    {
        iter->_index--;
    }
    return obj;
}

iterator_t segarray_iter(struct _segarray *self, linear_order_t order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;

    if (iter->_order == LINEAR_FORWARD)
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
 * @return true
 * @return false
 */
static bool segarray_init(struct _segarray *self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    if(capacity == 0)
    {
        self->_segsize = UNICSTL_CAPACITY_INIT;
    }
    else
    {
        self->_segsize = self->_capacity;
    }

    self->_map = NULL;
    self->_mapfree = NULL;

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
    self->reserve = segarray_reserve;
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

    // -------------------- memory --------------------
    #if 0
    if(capacity != 0)
    {
        self->_map = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_map == NULL)
        {
            log_warn("self->_map new failed!");
            return false;
        }

        self->_mapfree = ringbuf_new(sizeof(rawbuf_t), 8);
        if (self->_mapfree == NULL)
        {
            log_warn("self->_mapfree new failed!");
            ringbuf_free(&self->_map);
            return false;
        }

        rawbuf_t seg = rawbuf_new(obj_size, self->_segsize);
        if (seg == NULL)
        {
            log_warn("seg new failed!");
            ringbuf_free(&self->_map);
            ringbuf_free(&self->_mapfree);
            return false;
        }
        // config first obj index in seg array
        self->_seghead = clac_start_index(self->_segsize);
        self->_segtail = self->_seghead;

        // add first seg array to map
        if(!self->_map->push_back(self->_map, &seg))
        {
            log_warn("self->_map push back failed!");
            rawbuf_free(&seg);
            ringbuf_free(&self->_map);
            ringbuf_free(&self->_mapfree);
            return false;
        }
    }
    #endif
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

    if (segarray_init(segarray, obj_size, capacity) != true)
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
