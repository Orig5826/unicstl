
#include "queue.h"
#if QUEUE == 1

bool queue_init(pqueue_t * head)
{
    *head = (pqueue_t)malloc(sizeof(queue_t));
    ifqueue_head == NULL)
    {
        return false;
    }
    queue_head)->front = NULL;
    queue_head)->rear = NULL;
    queue_head)->size = 0;
    return true;
}

void queue_destroy(pqueue_t * head)
{
    ifqueue_head != NULL)
    {
        queue_clearqueue_head);
        freequeue_head);
        *head = NULL;
    }
}

bool queue_empty(pqueue_t head)
{
    return (head == NULL || head->front == NULL || head->rear == NULL) ? true : false;
}

void queue_clear(pqueue_t head)
{
    pqueue_node_t front_item;
    if(head != NULL)
    {
        front_item = head->front;
        while(head->front != NULL)
        {
            head->front = front_item->next;
            free(front_item);
            front_item = head->front;
        }
        head->rear = head->front;
        head->size = 0;
    }
}

uint32_t queue_get_size(pqueue_t head)
{
    return head->size;
}

bool queue_in(pqueue_t head, queue_data_t data)
{
    pqueue_node_t new_item;
    if(head == NULL)
    {
        return false;
    }
    new_item = (pqueue_node_t)malloc(sizeof(queue_node_t));
    if(new_item == NULL)
    {
        return false;
    }
    new_item->data = data;
    new_item->next = NULL;
    if(head->front == NULL)
    {
        head->front = new_item;
    }
    // insert from tail
    if(head->rear != NULL)
    {
        head->rear->next = new_item;
    }
    head->rear = new_item;

    if (head->size < _UI32_MAX)
    {
        head->size++;
    }

    return true;
}

void queue_out(pqueue_t head, queue_data_t *data)
{
    pqueue_node_t front_item;
    if(!queue_empty(head))
    {
        front_item = head->front;
        *data = front_item->data;

        // free the front item
        head->front = front_item->next;
        free(front_item);
        front_item = NULL;
        if (queue_get_size(head) == 1)
        {
            head->rear = NULL;
        }

        if (head > 0)
        {
            head->size--;
        }
    }
}

bool queue_get_front(pqueue_t head, queue_data_t *data)
{
    if(!queue_empty(head))
    {
        *data = head->front->data;
        return true;
    }
    else
    {
        return false;
    }
}

bool queue_get_rear(pqueue_t head, queue_data_t *data)
{
    if(!queue_empty(head))
    {
        *data = head->rear->data;
        return true;
    }
    else
    {
        return false;
    }
}

#endif


bool queue_push(struct _queue* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    void * obj_new = malloc(self->_obj_size);
    if (obj_new == NULL)
    {
        return false;
    }
    memmove(obj_new, obj, self->_obj_size);

    struct _queue_node* node_new = (struct _queue_node*)malloc(sizeof(struct _queue_node));
    if(node_new == NULL)
    {
        return false;
    }
    node_new->obj = obj_new;
    node_new->next = NULL;

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

bool queue_pop(struct _queue* self, void* obj)
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
    free(node->obj);
    free(node);
    return true;
}

bool queue_back(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_back->obj, self->_obj_size);
    return true;
}

bool queue_front(struct _queue* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_front->obj, self->_obj_size);
    return true;
}

bool queue_clear(struct _queue* self)
{
    assert(self != NULL);
    struct _queue_node* node = self->_front;
    struct _queue_node* next = NULL;
    while (node)
    {
        next = node->next;
        free(node->obj);
        free(node);
        node = next;
    }
    self->_front = NULL;
    self->_back = NULL;
    self->_size = 0;
    return true;
}

bool queue_empty(struct _queue* self)
{
    assert(self != NULL);
    return !self->size(self);
}

uint32_t queue_size(struct _queue* self)
{
    assert(self != NULL);
    return self->_size;
}

void queue_destory(struct _queue* self)
{
    assert(self != NULL);
    self->clear(self);
}

void queue_print(struct _queue* self)
{
    assert(self != NULL);

    struct _queue_node * node = self->_front;
    while (node)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

bool queue_init(struct _queue * queue, uint32_t obj_size)
{
    assert(queue != NULL);
    assert(obj_size > 0);

    // attribute init
    queue->_size = 0;
    queue->_obj_size = obj_size;
    // queue->_capacity = 0;
    // queue->_ratio = 0;

    // function init
    queue->push = queue_push;
    queue->pop = queue_pop;
    queue->back = queue_back;
    queue->front = queue_front;
    queue->clear = queue_clear;
    queue->empty = queue_empty;
    queue->size = queue_size;
    queue->destory = queue_destory;
    queue->print = queue_print;

    // init front & back
    queue->_front = NULL;
    queue->_back = NULL;
}



bool queue2_push(struct _queue* self, void* obj)
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

bool queue2_pop(struct _queue* self, void* obj)
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

bool queue2_back(struct _queue* self, void* obj)
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

bool queue2_front(struct _queue* self, void* obj)
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

bool queue2_clear(struct _queue* self)
{
    assert(self != NULL);
    self->_index_front = 0;
    self->_index_back = 0;
    self->_size = 0;
    return true;
}

bool queue2_full(struct _queue* self)
{
    assert(self != NULL);
    return self->size(self) == self->capacity(self);
}

uint32_t queue2_capacity(struct _queue* self)
{
    assert(self != NULL);
    return self->_capacity;
}

void queue2_destory(struct _queue* self)
{
    assert(self != NULL);
    self->clear(self);
}

void queue2_print(struct _queue* self)
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

bool queue_init2(struct _queue * queue, uint32_t obj_size, uint32_t capacity)
{
    assert(queue != NULL);
    assert(obj_size > 0);

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
    queue->full = queue2_full;
    queue->size = queue_size;
    queue->capacity = queue2_capacity;
    queue->destory = queue2_destory;
    queue->print = queue2_print;

    // init front & back
    queue->_front = (struct _queue_node *)malloc(sizeof(struct _queue_node));
    if(queue->_front == NULL)
    {
        return false;
    }
    queue->_back = queue->_front;

    // queue->_front->obj = calloc(queue->_capacity + 1, queue->_obj_size);
    queue->_front->obj = calloc(queue->_capacity, queue->_obj_size);
    if(queue->_front->obj == NULL)
    {
        return false;
    }
    queue->_index_front = 0;
    queue->_index_back = 0;
}

queue_t queue_new(void)
{
    return (struct _queue *)malloc(sizeof(struct _queue));
}

void queue_free(queue_t queue)
{
    if(queue != NULL)
    {
        queue->destory(queue);
        free(queue);
    }
}
