
#include "deque.h"

bool deque_push_back(struct _list* self, void* obj)
{

}
bool deque_push_front(struct _list* self, void* obj)
{

}
bool deque_pop_back(struct _list* self, void* obj)
{

}
bool deque_pop_front(struct _list* self, void* obj)
{

}
bool deque_back(struct _list* self, void* obj)
{

}
bool deque_front(struct _list* self, void* obj)
{

}

bool deque_insert(struct _list* self, int index, void* obj)
{

}
bool deque_erase(struct _list* self, int index, void* obj)
{

}

int deque_index(struct _list* self, void* obj)
{

}
bool deque_remove(struct _list* self, void* obj)
{

}

bool deque_clear(struct _list* self)
{

}

bool deque_get(struct _list* self, int index, void* obj)
{

}
bool deque_set(struct _list* self, int index, void* obj) 
{

}

uint32_t deque_size(struct _list* self)
{

}
bool deque_empty(struct _list* self)
{

}
void deque_destory(struct _list* self)
{

}

void deque_print(struct _list* self)
{

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
    deque->remove = deque_remove;
    deque->set = deque_set;
    deque->size = deque_size;


    deque->_head = (struct _deque_node*)malloc(sizeof(struct _deque_node));
    if (deque->_head == NULL)
    {
        return false;
    }
    deque->_head->prev = deque->_head;
    deque->_head->next = deque->_head;
    
    return true;
}
