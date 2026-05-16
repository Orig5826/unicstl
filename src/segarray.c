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

static inline void print_pos(struct _segarray *self)
{
    log_debug("head[%d][%d], tail[%d][%d]\n",
           self->_maphead,
           self->_seghead,
           self->_maptail - 1,
           self->_segtail);
}

static bool segarray_push_back(struct _segarray *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL)
    {
        return false;
    }

    ringbuf_t map = self->_map;
    if (self->_segtail == self->_segsize)
    {
        if (map->full(map))
        {
            log_warn("map->full");
            return false;
            // size_t new_capacity = unicstl_new_capacity(self->capacity(self));
            // if (!map->resize(map, new_capacity))
            // {
            //     log_error("map->resize(map, new_capacity) failed!");
            //     return false;
            // }
        }

        rawbuf_t seg = rawbuf_new(self->_obj_size, self->_capacity);
        if (seg == NULL)
        {
            log_error("rawbuf_new failed!");
            return false;
        }
        map->push_back(map, &seg);

        self->_maptail = self->_maptail + 1;
        self->_segtail = 0;
    }

    print_pos(self);

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
    if (self->_seghead == 0)
    {
        log_debug("map->size = %d\n", map->size(map));
        if (map->full(map))
        {
            log_warn("map->full");
            return false;
            // size_t new_capacity = unicstl_new_capacity(self->capacity(self));
            // if (!map->resize(map, new_capacity))
            // {
            //     log_error("map->resize(map, new_capacity) failed!");
            //     return false;
            // }
        }

        rawbuf_t seg = rawbuf_new(self->_obj_size, self->_capacity);
        if (seg == NULL)
        {
            log_error("rawbuf_new failed!");
            return false;
        }
        map->push_front(map, &seg);

        self->_maphead = self->_maphead - 1;
        self->_seghead = self->_segsize;
    }

    print_pos(self);

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

    print_pos(self);

    ringbuf_t map = self->_map;
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
        self->_maptail = self->_maptail - 1;

        map->pop_back(map, &seg);
        rawbuf_free(&seg);
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

    print_pos(self);

    ringbuf_t map = self->_map;
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
        self->_maphead = self->_maphead + 1;

        rawbuf_t seg;
        map->pop_front(map, &seg);
        rawbuf_free(&seg);
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

    ringbuf_t map = self->_map;
    rawbuf_t seg;
    if (!map->back(map, &seg))
    {
        return false;
    }
    size_t index = self->_segtail - 1;
    return seg->get(seg, index, obj);
}

static bool segarray_front(struct _segarray *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->obj == NULL || obj == NULL || self->empty(self))
    {
        return false;
    }

    ringbuf_t map = self->_map;
    rawbuf_t seg;
    if (!map->front(map, &seg))
    {
        return false;
    }
    size_t index = self->_seghead;
    return seg->get(seg, index, obj);
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

    return (self->_maphead == 0 && self->_seghead == 0) ||
           (self->_maptail == map_size - 1 && self->_segtail == self->_segsize - 1);
}

static bool segarray_clear(struct _segarray *self)
{
    unicstl_assert(self != NULL);
    self->_size = 0;

    self->_seghead = clac_start_index(self->_segsize);
    self->_segtail = self->_seghead;
    self->_maptail = self->_maphead;
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
    size_t index = iter->_index;
    ringbuf_t map = self->_map;
    rawbuf_t seg = NULL;
    size_t map_index;
    size_t seg_index;

    if (iter->_order == SEGARRAY_REVERSE)
    {
        log_debug("index:%ld", index);
        index = self->size(self) + 1 - index;
        log_debug("reverse-index:%ld", index);
    }

    size_t seg1_left = self->_segsize - self->_seghead;
    if(index < seg1_left)
    {
        map_index = 0;
        seg_index = self->_seghead + index;
    }
    else
    {
        size_t index_left = index - seg1_left;
        map_index = index_left / self->_segsize + 1;
        seg_index = index_left % self->_segsize;
    }
    
    log_debug("index:%ld, sethead:%ld", index, seg_index);
    log_debug("map_index:%ld, seg_index:%ld", map_index, seg_index);

    if (map->get(map, map_index, &seg))
    {
        obj = seg->at(seg, seg_index);
        if(obj == NULL)
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }

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

    //..
    if (iter->_order == SEGARRAY_FORWARD)
    {
        iter->_index = 0;
    }
    else
    {
        iter->_index = self->_map->size(self->_map);
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

        rawbuf_t seg = rawbuf_new(obj_size, self->_segsize);
        if (seg == NULL)
        {
            ringbuf_free(&self->_map);
            return false;
        }
        // config first obj index in seg array
        self->_seghead = clac_start_index(self->_segsize);
        self->_segtail = self->_seghead;

        // add first seg array to map
        self->_maphead = 0;
        self->_maptail = 1;
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
