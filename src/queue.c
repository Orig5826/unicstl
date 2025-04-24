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

static struct _queue_node * queue_node_new(void* obj, uint32_t obj_size)
{
    void * obj_new = malloc(obj_size);
    if (obj_new == NULL)
    {
        goto done;
    }
    memmove(obj_new, obj, obj_size);

    struct _queue_node* node_new = (struct _queue_node*)malloc(sizeof(struct _queue_node));
    if(node_new == NULL)
    {
        goto done1;
    }
    node_new->obj = obj_new;
    node_new->next = NULL;

    return node_new;
done1:
    free(obj_new);
done:
    return NULL;
}

static void queue_node_free(struct _queue_node** node)
{
    if(node != NULL && *node != NULL)
    {
        if((*node)->obj != NULL)
        {
            free((*node)->obj);
        }
        free(*node);
        *node = NULL;
    }
}

static bool queue_push(struct _queue* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    struct _queue_node* node_new = queue_node_new(obj, self->_obj_size);
    if(node_new == NULL)
    {
        return false;
    }

    if(self->empty(self))
    {
        self->_front = node_new;
        self->_back = node_new;
    }
    else
    {
        self->_back->next = node_new;
        self->_back = node_new;
    }
    self->_size++;

    return true;
}

static bool queue_pop(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _queue_node* node = self->_front;
    if(obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }
    self->_front = node->next;
    self->_size--;

    queue_node_free(&node);
    return true;
}

static bool queue_back(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_back->obj, self->_obj_size);
    return true;
}

static bool queue_front(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_front->obj, self->_obj_size);
    return true;
}

static bool queue_clear(struct _queue* self)
{
    assert(self != NULL);
    if(self->empty(self))
    {
        return true;
    }

    struct _queue_node* node = self->_front;
    struct _queue_node* next = NULL;
    while (node)
    {
        next = node->next;
        queue_node_free(&node);
        node = next;
    }
    self->_front = NULL;
    self->_back = NULL;
    self->_size = 0;
    return true;
}

static bool queue_empty(struct _queue* self)
{
    assert(self != NULL);
    assert(self->size != NULL);
    return self->size(self) == 0;
}

static bool queue_full(struct _queue* self)
{
    assert(self != NULL);
    assert(self->size != NULL);
    assert(self->capacity != NULL);
    return self->size(self) == self->capacity(self);
}

static uint32_t queue_size(struct _queue* self)
{
    assert(self != NULL);
    return self->_size;
}

static uint32_t queue_capacity(struct _queue* self)
{
    assert(self != NULL);
    return self->_capacity;
}

static void queue_destory(struct _queue* self)
{
    assert(self != NULL);
    self->clear(self);
}

static void queue_print(struct _queue* self)
{
    assert(self != NULL);

    struct _queue_node * node = self->_front;
    while (node)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

static bool queue2_push(struct _queue* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    if(self->full(self))
    {
        return false;
    }

    void * obj_array = self->_front->obj;
    uint32_t index = self->_index_back;
    memmove((char*)obj_array + index * self->_obj_size, obj, self->_obj_size);
    if(index >= self->capacity(self))
    {
        index = 0;
    }
    else
    {
        index++;
    }
    self->_index_back = index;
    self->_size++;
    return true;
}

static bool queue2_pop(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    void * obj_array = self->_front->obj;
    uint32_t index = self->_index_front;
    if(obj != NULL)
    {
        memmove(obj, (char*)obj_array + index * self->_obj_size,self->_obj_size);
    }
    if(index >= self->capacity(self))
    {
        index = 0;
    }
    else
    {
        index++;
    }
    self->_index_front = index;
    self->_size--;
    return true;
}

static bool queue2_back(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    void * obj_array = self->_front->obj;
    uint32_t index = self->_index_back;
    if(index == 0)
    {
        index = self->capacity(self) - 1;
    }
    else
    {
        index--;
    }
    memmove(obj, (char *)obj_array + index * self->_obj_size, self->_obj_size);
    return true;
}

static bool queue2_front(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    void * obj_array = self->_front->obj;
    uint32_t index = self->_index_front;
    memmove(obj, (char *)obj_array + index * self->_obj_size, self->_obj_size);
    return true;
}

static bool queue2_clear(struct _queue* self)
{
    assert(self != NULL);
    self->_index_front = 0;
    self->_index_back = 0;
    self->_size = 0;
    return true;
}

static void queue2_destory(struct _queue* self)
{
    assert(self != NULL);
    self->clear(self);
    if(self->_front != NULL)
    {
        free(self->_front->obj);
        free(self->_front);
        self->_front = NULL;
    }
}

static void queue2_print(struct _queue* self)
{
    assert(self != NULL);
    uint32_t index = 0;
    void * obj_array = self->_front->obj;

    for(uint32_t i = 0; i < self->size(self); i++)
    {
        index = self->_index_front + i;
        if(index >= self->capacity(self))
        {
            index -= self->_capacity;
        }

        self->print_obj((char *)obj_array + index * self->_obj_size);
    }
}

static iterator_t queue_iter(struct _queue* self)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_parent = self;
    iter->_cur = 0;
    iter->_cur_node = self->_front;
    return iter;
}

static bool queue_iter_hasnext(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    queue_t self = (queue_t)iter->_parent;
    if(iter->_cur < self->size(self))
    {
        return true;
    }
    return false;
}

static const void* queue_iter_next(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    queue_t self = (queue_t)iter->_parent;
    void *obj = NULL;

    if(self->_front->obj == NULL)
    {
        // base on linklist
        struct _queue_node * node = (struct _queue_node *)iter->_cur_node;
        if(node != NULL)
        {
            obj = node->obj;
            iter->_cur_node = node->next;
        }
    }
    else
    {
        // base on array
        uint32_t index = self->size(self) - 1 - self->_iter._cur;
        obj = self->_front->obj + self->_obj_size * index;
    }
    
    self->_iter._cur += 1;
    return obj;
}

static bool queue_init(struct _queue * self, uint32_t obj_size)
{
    assert(self != NULL);
    assert(obj_size > 0);
    if(self == NULL || obj_size == 0)
    {
        return false;
    }

    // -------------------- private -------------------- 
    self->_size = 0;
    self->_obj_size = obj_size;
    self->_capacity = UINT32_MAX;
    self->_ratio = 1;

    // front & back pointer init
    self->_front = NULL;
    self->_back = NULL;

    // base
    self->_destory = queue_destory;

    // iter
    self->_iter.hasnext = queue_iter_hasnext;
    self->_iter.next = queue_iter_next;

    // -------------------- public -------------------- 
    // kernel
    self->push = queue_push;
    self->pop = queue_pop;
    self->back = queue_back;
    self->front = queue_front;
    self->empty = queue_empty;
    self->full = queue_full;

    // base
    self->size = queue_size;
    self->capacity = queue_capacity;
    self->clear = queue_clear;

    // -------------------- debug -------------------- 
    self->print = queue_print;
    
    return true;
}

static bool queue_init2(struct _queue * self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);
    assert(obj_size > 0);
    assert(capacity > 0);
    if(self == NULL || obj_size == 0 || capacity == 0)
    {
        return false;
    }

     // -------------------- private -------------------- 
    self->_size = 0;
    self->_obj_size = obj_size;
    self->_capacity = capacity;
    self->_ratio = 2;

    self->_front = (struct _queue_node *)malloc(sizeof(struct _queue_node));
    if(self->_front == NULL)
    {
        return false;
    }
    self->_back = self->_front;

    // use self->_front->obj as obj_array
    // 
    // self->_front->obj = calloc(self->_capacity, self->_obj_size);
    self->_front->obj = malloc(self->_capacity * self->_obj_size);
    if(self->_front->obj == NULL)
    {
        free(self->_front);
        return false;
    }
    self->_index_front = 0;
    self->_index_back = 0;

    // 
    self->_destory = queue2_destory;

    // iter
    self->_iter.hasnext = queue_iter_hasnext;
    self->_iter.next = queue_iter_next;

    // -------------------- public -------------------- 
    // kernel
    self->push = queue2_push;
    self->pop = queue2_pop;
    self->back = queue2_back;
    self->front = queue2_front;
    self->empty = queue_empty;
    self->full = queue_full;

    // base
    self->size = queue_size;
    self->capacity = queue_capacity;
    self->clear = queue2_clear;

    // iter
    self->iter = queue_iter;

    // -------------------- debug -------------------- 
    self->print = queue2_print;

    return true;
}

/**
 * @brief 创建队列对象
 *  基于链表
 * 
 * @param obj_size 元素大小
 * 
 * @return queue_t 队列指针
 */
queue_t queue_new(uint32_t obj_size)
{
    struct _queue * queue = NULL;
    queue = (struct _queue *)calloc(1, sizeof(struct _queue));
    if(queue == NULL)
    {
        return NULL;
    }

    if(queue_init(queue, obj_size) != true)
    {
        free(queue);
        return NULL;
    }
    return queue;
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
queue_t queue_new2(uint32_t obj_size, uint32_t capacity)
{
    struct _queue * queue = NULL;
    queue = (struct _queue *)calloc(1, sizeof(struct _queue));
    if(queue == NULL)
    {
        return NULL;
    }

    if(queue_init2(queue, obj_size, capacity) != true)
    {
        free(queue);
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
    assert(queue != NULL);
    if(queue != NULL && *queue != NULL)
    {
        if((*queue)->_destory != NULL)
        {
            (*queue)->_destory(*queue);
        }
        free(*queue);
        *queue = NULL;
    }
}
