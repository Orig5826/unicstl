/**
 * @file linklist.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "linklist.h"


static struct _linklist_node * linklist_new_node(void* obj, uint32_t obj_size)
{
    void * new_obj = malloc(obj_size);
    if (new_obj == NULL)
    {
        goto done;
    }
    memmove(new_obj, obj, obj_size);

    struct _linklist_node* new_node = (struct _linklist_node*)malloc(sizeof(struct _linklist_node));
    if(new_node == NULL)
    {
        goto done1;
    }
    new_node->obj = new_obj;
    new_node->next = NULL;

    return new_node;
done1:
    free(new_obj);
done:
    return NULL;
}

static void linklist_node_free(struct _linklist_node** node)
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

static uint32_t linklist_size(struct _linklist* self)
{
    assert(self != NULL);
    return self->_size;
}

static uint32_t linklist_capacity(struct _linklist* self)
{
    assert(self != NULL);
    return self->_capacity;
}

static bool linklist_clear(struct _linklist* self)
{
    assert(self != NULL);
    if(self->empty(self))
    {
        return true;
    }

    struct _linklist_node* node = self->_front;
    struct _linklist_node* next = NULL;
    while (node)
    {
        next = node->next;
        linklist_node_free(&node);
        node = next;
    }
    self->_front = NULL;
    self->_back = NULL;
    self->_size = 0;
    return true;
}

static void linklist_destory(struct _linklist* self)
{
    assert(self != NULL);
    self->clear(self);
}

static bool linklist_push(struct _linklist* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);

    struct _linklist_node* new_node = linklist_new_node(obj, self->_obj_size);
    if(new_node == NULL)
    {
        return false;
    }

    if(self->empty(self))
    {
        self->_front = new_node;
        self->_back = new_node;
    }
    else
    {
        self->_back->next = new_node;
        self->_back = new_node;
    }
    self->_size++;

    return true;
}

static bool linklist_pop(struct _linklist* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _linklist_node* node = self->_front;
    if(obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }
    self->_front = node->next;
    self->_size--;

    linklist_node_free(&node);
    return true;
}

static bool linklist_back(struct _linklist* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_back->obj, self->_obj_size);
    return true;
}

static bool linklist_front(struct _linklist* self, void* obj)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_front->obj, self->_obj_size);
    return true;
}

static bool linklist_empty(struct _linklist* self)
{
    assert(self != NULL);
    assert(self->size != NULL);
    return self->size(self) == 0;
}

static bool linklist_full(struct _linklist* self)
{
    assert(self != NULL);
    assert(self->size != NULL);
    assert(self->capacity != NULL);
    return self->size(self) == self->capacity(self);
}

static void linklist_print(struct _linklist* self)
{
    assert(self != NULL);

    struct _linklist_node * node = self->_front;
    while (node)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}


static bool linklist_init(struct _linklist * self, uint32_t obj_size)
{
    assert(self != NULL);
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
    self->_destory = linklist_destory;

    // -------------------- public -------------------- 
    // kernel
    self->push = linklist_push;
    self->pop = linklist_pop;
    self->back = linklist_back;
    self->front = linklist_front;
    self->empty = linklist_empty;
    self->full = linklist_full;

    // base
    self->size = linklist_size;
    self->capacity = linklist_capacity;
    self->clear = linklist_clear;

    // iter
    // self->iter = linklist_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = linklist_print;
    
    return true;
}

linklist_t linklist_new(uint32_t obj_size)
{
    struct _linklist * linklist = NULL;
    linklist = (struct _linklist *)calloc(1, sizeof(struct _linklist));
    if(linklist == NULL)
    {
        return NULL;
    }

    if(linklist_init(linklist, obj_size) != true)
    {
        free(linklist);
        return NULL;
    }
    return linklist;
}

void linklist_free(linklist_t* linklist)
{
    assert(linklist != NULL);
    if(linklist != NULL && *linklist != NULL)
    {
        if((*linklist)->_destory != NULL)
        {
            (*linklist)->_destory(*linklist);
        }
        free(*linklist);
        *linklist = NULL;
    }
}
