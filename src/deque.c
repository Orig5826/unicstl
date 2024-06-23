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

bool deque_push_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
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
        self->_head->next = new_node;
        self->_head->prev = new_node;
    }
    new_node->prev = self->_head->next;         // step 1
    new_node->next = self->_head->prev;         // step 2

    back = self->_head->next;
    back->next = new_node;                      // step 3

    front = self->_head->prev;
    front->prev = new_node;                     // step 4

    self->_head->next = new_node;               // step 5

    self->_size += 1;
    return true;
}

bool deque_push_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
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
        self->_head->next = new_node;
        self->_head->prev = new_node;
    }
    new_node->prev = self->_head->next;         // step 1
    new_node->next = self->_head->prev;         // step 2

    back = self->_head->next;
    back->next = new_node;                      // step 3

    front = self->_head->prev;
    front->prev = new_node;                     // step 4

    self->_head->prev = new_node;               // step 5

    self->_size += 1;
    return true;
}

bool deque_pop_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    struct _deque_node* node = NULL;
    struct _deque_node* front = NULL;

    if (self->empty(self))
    {
        return false;
    }

    node = self->_head->next;
    if (obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }

    if (self->size(self) == 1)
    {
        self->_head->next = NULL;
        self->_head->prev = NULL;
    }
    else
    {
        self->_head->next = node->prev;         // step 1

        front = self->_head->prev;
        front->prev = node->prev;               // step 2
    }

    free(node->obj);
    free(node);

    self->_size -= 1;
    return true;
}

bool deque_pop_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    struct _deque_node* node = NULL;
    struct _deque_node* back = NULL;
    
    if (self->empty(self))
    {
        return false;
    }

    node = self->_head->prev;
    if (obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }

    if (self->size(self) == 1)
    {
        self->_head->next = NULL;
        self->_head->prev = NULL;
    }
    else
    {
        self->_head->prev = node->next;         // step 1

        back = self->_head->next;
        back->next = node->next;               // step 2
    }

    free(node->obj);
    free(node);

    self->_size -= 1;
    return true;
}

bool deque_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_head->next->obj, self->_obj_size);
    return true;
}

bool deque_front(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_head->prev->obj, self->_obj_size);
    return true;
}

bool deque_insert(struct _deque* self, int index, void* obj)
{
    return true;
}
bool deque_erase(struct _deque* self, int index, void* obj)
{
    return true;
}

int deque_index(struct _deque* self, void* obj)
{
    return -1;
}

bool deque_remove(struct _deque* self, void* obj)
{
    return true;
}

bool deque_clear(struct _deque* self)
{
    while (!self->empty(self))
    {
        deque_pop_back(self, NULL);
    }
    return true;
}

bool deque_get(struct _deque* self, int index, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);
    assert(index >= 0 && index < self->size(self));

    struct _deque_node* node = self->_head->prev;   // front

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}

bool deque_set(struct _deque* self, int index, void* obj) 
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);
    assert(index >= 0 && index < self->size(self));

    struct _deque_node* node = self->_head->prev;   // front

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    memmove(node->obj, obj, self->_obj_size);
    return true;
}

uint32_t deque_size(struct _deque* self)
{
    assert(self != NULL);
    return self->_size;
}

bool deque_empty(struct _deque* self)
{
    assert(self != NULL);
    return !self->size(self);
}

void deque_destory(struct _deque* self)
{
    assert(self != NULL);
    self->clear(self);
    if (self->_head != NULL)
    {
        free(self->_head);
        self->_head = NULL;
    }
}

void deque_print(struct _deque* self)
{
    assert(self != NULL);
    assert(self->_head != NULL);

    uint32_t i = 0;
    struct _deque_node * node = self->_head->prev;
    for (uint32_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

bool deque_init(struct _deque* self, uint32_t obj_size)
{
    // attribute
    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    // function
    self->back = deque_back;
    self->clear = deque_clear;
    self->destory = deque_destory;
    self->empty = deque_empty;
    self->erase = deque_erase;
    self->front = deque_front;
    self->get = deque_get;
    self->index = deque_index;
    self->insert = deque_insert;
    self->pop_back = deque_pop_back;
    self->pop_front = deque_pop_front;
    self->push_back = deque_push_back;
    self->push_front = deque_push_front;
    self->print = deque_print;
    self->remove = deque_remove;
    self->set = deque_set;
    self->size = deque_size;

    self->_head = (struct _deque_node*)malloc(sizeof(struct _deque_node));
    if (self->_head == NULL)
    {
        return false;
    }
    self->_head->obj = NULL;
    self->_head->prev = NULL;
    self->_head->next = NULL;
    
    return true;
}

deque_t deque_new(void)
{
    return (struct _deque*)malloc(sizeof(struct _deque));
}

void deque_free(deque_t deque)
{
    if(deque != NULL)
    {
        deque->destory(deque);
        free(deque);
    }
}
