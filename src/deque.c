/**
 * @file deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "deque.h"

static bool deque_push_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    struct _deque_node* front = NULL;
    struct _deque_node* back = NULL;

    // create a new object
    void* new_obj = (void*)malloc(self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    memmove(new_obj, obj, self->_obj_size);

    // create a new node
    struct _deque_node* new_node = (struct _deque_node*)malloc(sizeof(struct _deque_node));
    if (new_node == NULL)
    {
        return false;
    }
    new_node->obj = new_obj;

    // link node
    if(self->empty(self))
    {
        // if this is first node
        self->_tail = new_node;
        self->_head = new_node;
    }
    new_node->prev = self->_tail;       // step 1
    new_node->next = self->_head;       // step 2

    back = self->_tail;
    back->next = new_node;              // step 3

    front = self->_head;
    front->prev = new_node;             // step 4

    self->_tail = new_node;             // step 5

    self->_size += 1;
    return true;
}

static bool deque_push_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    struct _deque_node* front = NULL;
    struct _deque_node* back = NULL;

    // create a new object
    void* new_obj = (void*)malloc(self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    memmove(new_obj, obj, self->_obj_size);

    // create a new node
    struct _deque_node* new_node = (struct _deque_node*)malloc(sizeof(struct _deque_node));
    if (new_node == NULL)
    {
        return false;
    }
    new_node->obj = new_obj;

    // link node
    if (self->empty(self))
    {
        // if this is first node
        self->_tail = new_node;
        self->_head = new_node;
    }
    new_node->prev = self->_tail;       // step 1
    new_node->next = self->_head;       // step 2

    back = self->_tail;
    back->next = new_node;              // step 3

    front = self->_head;
    front->prev = new_node;             // step 4

    self->_head = new_node;             // step 5

    self->_size += 1;
    return true;
}

static bool deque_pop_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    struct _deque_node* node = NULL;
    struct _deque_node* front = NULL;

    if (self->empty(self))
    {
        return false;
    }

    node = self->_tail;
    if (obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }

    if (self->size(self) == 1)
    {
        self->_tail = NULL;
        self->_head = NULL;
    }
    else
    {
        self->_tail = node->prev;       // step 1

        front = self->_head;
        front->prev = node->prev;       // step 2
    }

    free(node->obj);
    free(node);

    self->_size -= 1;
    return true;
}

static bool deque_pop_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    struct _deque_node* node = NULL;
    struct _deque_node* back = NULL;
    
    if (self->empty(self))
    {
        return false;
    }

    node = self->_head;
    if (obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }

    if (self->size(self) == 1)
    {
        self->_tail = NULL;
        self->_head = NULL;
    }
    else
    {
        self->_head = node->next;       // step 1

        back = self->_tail;
        back->next = node->next;        // step 2
    }

    free(node->obj);
    free(node);

    self->_size -= 1;
    return true;
}

static bool deque_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_tail->obj, self->_obj_size);
    return true;
}

static bool deque_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_head->obj, self->_obj_size);
    return true;
}

static bool deque_insert(struct _deque* self, int index, void* obj)
{
    return true;
}

static bool deque_erase(struct _deque* self, int index, void* obj)
{
    return true;
}

static int deque_index(struct _deque* self, void* obj)
{
    return -1;
}

static bool deque_remove(struct _deque* self, void* obj)
{
    return true;
}

static bool deque_clear(struct _deque* self)
{
    while (!self->empty(self))
    {
        deque_pop_back(self, NULL);
    }
    return true;
}

static bool deque_get(struct _deque* self, int index, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(index >= 0 && index < self->size(self));

    struct _deque_node* node = self->_head;   // front

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}

static bool deque_set(struct _deque* self, int index, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(index >= 0 && index < self->size(self));

    struct _deque_node* node = self->_head;   // front

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    memmove(node->obj, obj, self->_obj_size);
    return true;
}

static uint32_t deque_size(struct _deque* self)
{
    assert(self != NULL);
    return self->_size;
}

static bool deque_empty(struct _deque* self)
{
    assert(self != NULL);
    return !self->size(self);
}

static void deque_destory(struct _deque* self)
{
    assert(self != NULL);
    self->clear(self);
    if (self->_head != NULL)
    {
        free(self->_head);
        self->_head = NULL;
    }
}

static void deque_print(struct _deque* self)
{
    assert(self != NULL);

    uint32_t i = 0;
    struct _deque_node * node = self->_head;
    for (uint32_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

bool deque_iter_hasnext(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

const void* deque_iter_next(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->_container != NULL);

    deque_t self = (deque_t)iter->_container;
    void *obj = NULL;
    
    struct _deque_node * cur_node = (struct _deque_node *)iter->_node;
    if(cur_node == NULL)
    {
        return NULL;
    }

    obj = cur_node->obj;
    if(iter->_order == DEQUE_FORWARD)
    {
        iter->_node = cur_node->next;
    }
    else
    {
        iter->_node = cur_node->prev;
    }

    iter->_index += 1;
    return obj;
}

iterator_t deque_iter(struct _deque* self, enum _deque_order order)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    if(iter->_order == DEQUE_FORWARD)
    {
        iter->_node = self->_head;
    }
    else
    {
        iter->_node = self->_tail;
    }

    iter->hasnext = deque_iter_hasnext;
    iter->next = deque_iter_next;
    return iter;
}

static bool deque_init(struct _deque* self, uint32_t obj_size)
{
    assert(self != NULL);
    if(obj_size == 0)
    {
        return false;
    }
    // -------------------- private -------------------- 
    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_head = NULL;
    self->_tail = NULL;

    self->_destory = deque_destory;

    // -------------------- public -------------------- 
    // kernel
    self->push_back = deque_push_back;
    self->push_front = deque_push_front;
    self->pop_back = deque_pop_back;
    self->pop_front = deque_pop_front;
    self->back = deque_back;
    self->front = deque_front;
    self->empty = deque_empty;

    // base
    self->clear = deque_clear;
    self->size = deque_size;

    // iter
    self->iter = deque_iter;

    // others
    self->insert = deque_insert;
    self->erase = deque_erase;
    
    self->index = deque_index;
    self->remove = deque_remove;

    self->set = deque_set;
    self->get = deque_get;

    // -------------------- debug -------------------- 
    self->print = deque_print;
    
    return true;
}

deque_t deque_new(uint32_t obj_size)
{
    struct _deque* deque = NULL;
    deque = (struct _deque*)malloc(sizeof(struct _deque));
    if(deque == NULL)
    {
        return NULL;
    }

    if(deque_init(deque, obj_size) != true)
    {
        free(deque);
        return NULL;
    }
    return deque;
}

void deque_free(deque_t *deque)
{
    if(*deque != NULL)
    {
        (*deque)->_destory(*deque);
        free(*deque);
    }
    *deque = NULL;
}
