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

bool queue_init(struct _queue * queue, uint32_t obj_size)
{
    assert(queue != NULL);
    assert(obj_size > 0);
    if(queue == NULL || obj_size == 0)
    {
        return false;
    }

    // attribute init
    queue->_size = 0;
    queue->_obj_size = obj_size;
    queue->_capacity = UINT32_MAX;
    queue->_ratio = 1;

    // function init
    queue->push = queue_push;
    queue->pop = queue_pop;

    queue->back = queue_back;
    queue->front = queue_front;

    queue->clear = queue_clear;
    queue->empty = queue_empty;
    queue->full = queue_full;
    queue->size = queue_size;
    queue->capacity = queue_capacity;

    queue->destory = queue_destory;
    queue->print = queue_print;
    
    // init front & back
    queue->_front = NULL;
    queue->_back = NULL;

    return true;
}

bool queue_init2(struct _queue * queue, uint32_t obj_size, uint32_t capacity)
{
    assert(queue != NULL);
    assert(obj_size > 0);
    assert(capacity > 0);
    if(queue == NULL || obj_size == 0 || capacity == 0)
    {
        return false;
    }

    // attribute init
    queue->_size = 0;
    queue->_obj_size = obj_size;
    queue->_capacity = capacity;
    queue->_ratio = 2;

    // function init
    queue->push = queue2_push;
    queue->pop = queue2_pop;

    queue->back = queue2_back;
    queue->front = queue2_front;

    queue->clear = queue2_clear;
    queue->empty = queue_empty;
    queue->full = queue_full;
    queue->size = queue_size;
    queue->capacity = queue_capacity;

    queue->destory = queue2_destory;
    queue->print = queue2_print;

    // init front & back
    queue->_front = (struct _queue_node *)malloc(sizeof(struct _queue_node));
    if(queue->_front == NULL)
    {
        goto done;
    }
    queue->_back = queue->_front;

    // use queue->_front->obj as obj_array
    // queue->_front->obj = calloc(queue->_capacity, queue->_obj_size);
    queue->_front->obj = malloc(queue->_capacity * queue->_obj_size);
    if(queue->_front->obj == NULL)
    {
        goto done1;
    }
    queue->_index_front = 0;
    queue->_index_back = 0;

    return true;
done1:
    free(queue->_front);
done:
    return false;
}

queue_t queue_new(void)
{
    return (struct _queue *)calloc(1, sizeof(struct _queue));
}

void queue_free(queue_t* queue)
{
    // assert(queue != NULL);
    // assert(*queue != NULL);
    // assert((*queue)->destory != NULL);

    if(queue != NULL && *queue != NULL)
    {
        if((*queue)->destory != NULL)
        {
            (*queue)->destory(*queue);
        }
        free(*queue);
        *queue = NULL;
    }
}
