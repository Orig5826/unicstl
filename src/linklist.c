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


static struct _linklist_node * linklist_new_node(void* obj, size_t obj_size)
{
    void * new_obj = unicstl_malloc(obj_size);
    if (new_obj == NULL)
    {
        goto done;
    }
    memmove(new_obj, obj, obj_size);

    struct _linklist_node* new_node = (struct _linklist_node*)unicstl_malloc(sizeof(struct _linklist_node));
    if(new_node == NULL)
    {
        goto done1;
    }
    new_node->obj = new_obj;
    new_node->next = NULL;

    return new_node;
done1:
    unicstl_free(new_obj);
done:
    return NULL;
}

static void linklist_node_free(struct _linklist_node** node)
{
    if(node != NULL && *node != NULL)
    {
        if((*node)->obj != NULL)
        {
            unicstl_free((*node)->obj);
        }
        unicstl_free(*node);
        *node = NULL;
    }
}

static size_t linklist_size(struct _linklist* self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static size_t linklist_capacity(struct _linklist* self)
{
    unicstl_assert(self != NULL);
    return self->_capacity;
}

static bool linklist_empty(struct _linklist* self)
{
    unicstl_assert(self != NULL);
    unicstl_assert(self->size != NULL);
    return self->size(self) == 0;
}

static bool linklist_clear(struct _linklist* self)
{
    unicstl_assert(self != NULL);
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
    unicstl_assert(self != NULL);
    self->clear(self);
}

static bool linklist_push_front(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj != NULL);

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
        new_node->next = self->_front;
        self->_front = new_node;
    }
    self->_size++;

    return true;
}

static bool linklist_pop_front(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
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

static bool linklist_push_back(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj != NULL);

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

static bool linklist_pop_back(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _linklist_node* node = self->_front;
    struct _linklist_node* back_prev = NULL;
    while(node->next != NULL)
    {
        back_prev = node;
        node = node->next;
    }

    if(obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }
    self->_back = back_prev;
    self->_size--;

    linklist_node_free(&node);
    return true;
}

static bool linklist_back(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_back->obj, self->_obj_size);
    return true;
}

static bool linklist_front(struct _linklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_front->obj, self->_obj_size);
    return true;
}

bool linklist_insert(struct _linklist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    // ...
    return true;
}

bool linklist_remove(struct _linklist *self, void *obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _linklist_node* node = self->_front;
    struct _linklist_node* node_prev = NULL;
    while(node != NULL)
    {
        node_prev = node;
        if(self->compare(node->obj, obj) == 0)
        {
            break;
        }
        node = node->next;
    }
    //...
    return true;
}

bool linklist_contains(struct _linklist *self, const void *obj)
{
    unicstl_assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _linklist_node* node = self->_front;
    while(node != NULL)
    {
        if(self->compare(node->obj, obj) == 0)
        {
            return true;
        }
        node = node->next;
    }
    return false;
}

static void linklist_print(struct _linklist* self)
{
    unicstl_assert(self != NULL);

    struct _linklist_node * node = self->_front;
    while (node)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}


static bool linklist_init(struct _linklist * self, size_t obj_size)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj_size != 0);
    
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
    self->push_front = linklist_push_front;
    self->pop_front = linklist_pop_front;
    self->push_back = linklist_push_back;
    self->pop_back = linklist_pop_back;
    self->back = linklist_back;
    self->front = linklist_front;
    
    self->insert = linklist_insert;
    self->remove = linklist_remove;
    self->contains = linklist_contains;

    // base
    self->size = linklist_size;
    self->capacity = linklist_capacity;
    self->empty = linklist_empty;
    self->clear = linklist_clear;

    // iter
    // self->iter = linklist_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = linklist_print;
    
    return true;
}

linklist_t linklist_new(size_t obj_size)
{
    struct _linklist * linklist = NULL;
    linklist = (struct _linklist *)unicstl_calloc(1, sizeof(struct _linklist));
    if(linklist == NULL)
    {
        log_warn("linklist calloc failed\n");
        return NULL;
    }

    if(linklist_init(linklist, obj_size) != true)
    {
        log_warn("linklist init failed\n");
        unicstl_free(linklist);
        return NULL;
    }
    return linklist;
}

void linklist_free(linklist_t* linklist)
{
    unicstl_assert(linklist != NULL);
    if(linklist != NULL && *linklist != NULL)
    {
        if((*linklist)->_destory != NULL)
        {
            (*linklist)->_destory(*linklist);
        }
        unicstl_free(*linklist);
        *linklist = NULL;
    }
}
