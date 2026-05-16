/**
 * @file queue.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "queue.h"

static bool queue_push(struct _queue* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->push_back(self->_deque, obj);
}

static bool queue_pop(struct _queue* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->pop_front(self->_deque, obj);
}

static bool queue_back(struct _queue* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->back(self->_deque, obj);
    return true;
}

static bool queue_front(struct _queue* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->front(self->_deque, obj);
}

static size_t queue_resize(struct _queue* self, size_t capacity)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->resize(self->_deque, capacity);
}

static size_t queue_size(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->size(self->_deque);
}

static size_t queue_capacity(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);

    return self->_deque->capacity(self->_deque);
}

static bool queue_empty(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->empty(self->_deque);
}

static bool queue_full(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->full(self->_deque);
}

static bool queue_clear(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    return self->_deque->clear(self->_deque);
}


static void queue_destory(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_free(&self->_deque);
}

static void queue_print(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);

    self->_deque->print_obj = self->print_obj;
    self->_deque->print(self->_deque);
}

static bool queue_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    queue_t self = (queue_t)iter->_container;
    return self->_iter_deque->hasnext(self->_iter_deque);
}

static const void* queue_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    queue_t self = (queue_t)iter->_container;
    return self->_iter_deque->next(self->_iter_deque);
}

static iterator_t queue_iter(struct _queue* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->_deque != NULL);
    deque_t deque = self->_deque;
    self->_iter_deque = deque->iter(deque, DEQUE_FORWARD);

    iterator_t iter = &self->_iter;
    iter->_container = self;

    iter->hasnext = queue_iter_hasnext;
    iter->next = queue_iter_next;
    return iter;
}

static bool queue_init(struct _queue * self, size_t obj_size, size_t capacity)
{
    unicstl_assert(self != NULL);

    // -------------------- private --------------------
    self->_deque = deque_new(obj_size, capacity);
    if(self->_deque == NULL)
    {
        return false;
    }

    // 
    self->_destory = queue_destory;

    // -------------------- public -------------------- 
    // kernel
    self->push = queue_push;
    self->pop = queue_pop;
    self->back = queue_back;
    self->front = queue_front;

    // base
    self->resize = queue_resize;
    self->size = queue_size;
    self->capacity = queue_capacity;
    self->empty = queue_empty;
    self->full = queue_full;
    self->clear = queue_clear;

    // iter
    self->iter = queue_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;
    
    // -------------------- debug -------------------- 
    self->print = queue_print;

    return true;
}

/**
 * @brief 创建队列对象
 *  基于动态数组
 * 
 * @param obj_size 元素大小
 * @param capacity 容量
 * 
 * @return queue_t 队列指针
 */
queue_t queue_new(size_t obj_size, size_t capacity)
{
    struct _queue * queue = NULL;
    queue = (struct _queue *)unicstl_malloc(sizeof(struct _queue));
    if(queue == NULL)
    {
        log_warn("queue malloc failed!\n");
        return NULL;
    }

    if(queue_init(queue, obj_size, capacity) != true)
    {
        log_warn("queue init failed!\n");
        unicstl_free(queue);
        return NULL;
    }
    return queue;
}

/**
 * @brief 释放队列对象
 * 
 * @param queue 队列指针地址
 * 
 */
void queue_free(queue_t* queue)
{
    unicstl_assert(queue != NULL);
    if(queue != NULL && *queue != NULL)
    {
        if((*queue)->_destory != NULL)
        {
            (*queue)->_destory(*queue);
        }
        unicstl_free(*queue);
        *queue = NULL;
    }
}
