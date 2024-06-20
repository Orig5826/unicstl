
#include "deque.h"

bool deque_push_back(struct _deque* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    struct _deque_node* node = NULL;

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
    new_node->prev = self->_head->next; 
    new_node->next = self->_head->prev;

    node = self->_head->next;
    node->next = new_node;

    node = self->_head->prev;
    node->prev = new_node;

    self->_head->next = new_node;

    self->_size += 1;
    return true;
}

bool deque_push_front(struct _deque* self, void* obj)
{

}

bool deque_pop_back(struct _deque* self, void* obj)
{

}

bool deque_pop_front(struct _deque* self, void* obj)
{

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

}

bool deque_insert(struct _deque* self, int index, void* obj)
{

}
bool deque_erase(struct _deque* self, int index, void* obj)
{

}

int deque_index(struct _deque* self, void* obj)
{

}

bool deque_remove(struct _deque* self, void* obj)
{

}

bool deque_clear(struct _deque* self)
{

}

bool deque_get(struct _deque* self, int index, void* obj)
{

}

bool deque_set(struct _deque* self, int index, void* obj) 
{
    
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
    while (node != self->_head->next)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

bool deque_init(struct _deque* deque, uint32_t obj_size)
{
    // attribute
    deque->_obj_size = obj_size;
    deque->_size = 0;
    // deque->_capacity = 64;
    // deque->_ratio = 2;

    // function
    deque->back = deque_back;
    deque->clear = deque_clear;
    deque->destory = deque_destory;
    deque->empty = deque_empty;
    deque->erase = deque_erase;
    deque->front = deque_front;
    deque->get = deque_get;
    deque->index = deque_index;
    deque->insert = deque_insert;
    deque->pop_back = deque_pop_back;
    deque->pop_front = deque_pop_back;
    deque->push_back = deque_push_back;
    deque->push_front = deque_push_front;
    deque->print = deque_print;
    deque->remove = deque_remove;
    deque->set = deque_set;
    deque->size = deque_size;


    deque->_head = (struct _deque_node*)malloc(sizeof(struct _deque_node));
    if (deque->_head == NULL)
    {
        return false;
    }
    deque->_head->obj = NULL;
    deque->_head->prev = NULL;
    deque->_head->next = NULL;
    
    return true;
}
