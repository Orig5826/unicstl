/**
 * @brief 
 * 
 * @param self 
 * @param obj_size 
 * @return true 
 * @return false 
 */
#include "heap.h"

static size_t left(size_t i)
{
    return 2 * i + 1;
}

static size_t right(size_t i)
{
    return (i << 1) + 2;
}

static size_t parent(size_t i)
{
    if(i == 0)
    {
        return -1;
    }
    return (i - 1) >> 1;
}

static bool heap_peek(struct _heap* self, void* obj)
{
    unicstl_assert(self != NULL);
    size_t index = self->size(self) - 1;
    if(!self->_darray->get(self->_darray, 0, obj))
    {
        return false;
    }
    return true;
}

static void heap_fixed_up(struct _heap* self, size_t i)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    unicstl_assert(self->compare != NULL);

    const void *base = self->_darray->at(self->_darray, 0);
    size_t obj_size = self->_darray->_obj_size;
    size_t p = 0;

    if(self->_type == HEAP_MAX)
    {
        while(1)
        {
            p = parent(i);
            // if current node is greater than its parent, swap the position. otherwise break out of loop
            if(p == (size_t)-1 || compare_obj(base, i, p, obj_size, self->compare) <= 0)
            {
                break;
            }
            obj_swap(base, i, p, obj_size);
            i = p;
        }
    }
    else /* if(self->_type == HEAP_MIN) */
    {
        while(1)
        {
            p = parent(i);
            log_debug("heap_fixed_up: p = %d, i = %zu\n", (ssize_t)p, i);

            // if current node is less than its parent, swap the position. otherwise break out of loop
            if(p == (size_t)-1 || compare_obj(base, i, p, obj_size, self->compare) >= 0)
            {
                break;
            }
            obj_swap(base, i, p, obj_size);
            i = p;
        }
    }
}

static bool heap_push(struct _heap* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    if(!self->_darray->append(self->_darray, obj))
    {
        return false;
    }
    heap_fixed_up(self, self->size(self) - 1);
    return true;
}

static void heap_fixed_down(struct _heap* self, size_t i)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    size_t l = 0,r = 0;
    size_t max = 0, min = 0;

    const void *base = self->_darray->at(self->_darray, 0);
    size_t obj_size = self->_darray->_obj_size;

    if(self->_type == HEAP_MAX)
    {
        while(1)
        {
            l = left(i);
            r = right(i);
            max = i;

            if(l < self->size(self) && compare_obj(base, l, max, obj_size, self->compare) > 0)
            {
                max = l;
            }
            if(r < self->size(self) && compare_obj(base, r, max, obj_size, self->compare) > 0)
            {
                max = r;
            }

            if(max == i)
            {
                break;
            }
            obj_swap(base, i, max, obj_size);
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

            if(l < self->size(self) && compare_obj(base, l, min, obj_size, self->compare) < 0)
            {
                min = l;
            }

            if(r < self->size(self) && compare_obj(base, r, min, obj_size, self->compare) < 0)
            {
                min = r;
            }
            if(min == i)
            {
                break;
            }
            obj_swap(self, i, min, obj_size);
            i = min;
        }
    }
}

static bool heap_pop(struct _heap* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    if(!self->_darray->pop(self->_darray, obj))
    {
        return false;
    }
    heap_fixed_down(self, 0);
    return true;
}

static bool heap_reserve(struct _heap* self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->reserve(self->_darray, capacity);
}

static size_t heap_size(struct _heap* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->size(self->_darray);
}

static size_t heap_capacity(struct _heap* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->capacity(self->_darray);
}

static bool heap_empty(struct _heap* self)
{
    unicstl_assert(self != NULL);
    return self->size(self) == 0;
}

static bool heap_clear(struct _heap* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    return self->_darray->clear(self->_darray);
}

static void heap_destory(struct _heap* self)
{
    unicstl_assert(self != NULL);
    self->clear(self);
    if(self->_darray != NULL)
    {
        darray_free(&self->_darray);
    }
}

static void heap_print(struct _heap* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_darray != NULL);
    self->_darray->print_obj = self->print_obj;
    self->_darray->print(self->_darray);
}

bool heap_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    heap_t self = (heap_t)iter->_container;
    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

const void* heap_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);
    heap_t self = (heap_t)iter->_container;
    unicstl_assert(self->_darray != NULL);

    size_t index = iter->_index;
    iter->_index += 1;
    return self->_darray->at(self->_darray, index);
}

iterator_t heap_iter(struct _heap* self)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;

    iter->hasnext = heap_iter_hasnext;
    iter->next = heap_iter_next;
    return iter;
}

static bool heap_init(struct _heap* self, size_t obj_size, size_t capacity, heap_type type)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size > 0);

    // -------------------- private -------------------- 
    self->_darray = NULL;
    self->_type = type;

    self->_destory = heap_destory;

    // -------------------- public -------------------- 
    // kernel
    self->peek = heap_peek;
    self->push = heap_push;
    self->pop = heap_pop;
    self->empty = heap_empty;

    // base
    self->reserve = heap_reserve;
    self->capacity = heap_capacity;
    self->size = heap_size;
    self->clear = heap_clear;

    // iter
    self->iter = heap_iter;

    // -------------------- default --------------------
    self->compare = default_compare;
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = heap_print;

    // -------------------- init -------------------- 
    self->_darray = darray_new(obj_size, capacity);
    if(self->_darray == NULL)
    {
        return false;
    }
    return true;
}

heap_t heap_max_new(size_t obj_size, size_t capacity)
{
    heap_t heap = NULL;
    heap = (struct _heap*)unicstl_malloc(sizeof(struct _heap));
    if(heap == NULL)
    {
        return NULL;
    }

    if(heap_init(heap, obj_size, capacity, HEAP_MAX) != true)
    {
        unicstl_free(heap);
        return NULL;
    }
    return heap;
}

heap_t heap_min_new(size_t obj_size, size_t capacity)
{
    heap_t heap = NULL;
    heap = (struct _heap*)unicstl_malloc(sizeof(struct _heap));
    if(heap == NULL)
    {
        log_warn("heap malloc failed\n");
        return NULL;
    }

    if(heap_init(heap, obj_size, capacity, HEAP_MIN) != true)
    {
        log_warn("heap init failed\n");
        unicstl_free(heap);
        return NULL;
    }
    return heap;
}

void heap_free(heap_t* heap)
{
    if(*heap != NULL)
    {
        (*heap)->_destory(*heap);
        unicstl_free(*heap);
    }
    *heap = NULL;
}
