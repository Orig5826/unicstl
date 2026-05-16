/**
 * @file dlinklist.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "dlinklist.h"

static bool dlinklist_push_back(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    struct _dlinklist_node* front = NULL;
    struct _dlinklist_node* back = NULL;

    // create a new object
    void* new_obj = (void*)unicstl_malloc(self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    memmove(new_obj, obj, self->_obj_size);

    // create a new node
    struct _dlinklist_node* new_node = (struct _dlinklist_node*)unicstl_malloc(sizeof(struct _dlinklist_node));
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

static bool dlinklist_push_front(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    struct _dlinklist_node* front = NULL;
    struct _dlinklist_node* back = NULL;

    // create a new object
    void* new_obj = (void*)unicstl_malloc(self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    memmove(new_obj, obj, self->_obj_size);

    // create a new node
    struct _dlinklist_node* new_node = (struct _dlinklist_node*)unicstl_malloc(sizeof(struct _dlinklist_node));
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

static bool dlinklist_pop_back(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    struct _dlinklist_node* node = NULL;
    struct _dlinklist_node* front = NULL;

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

    unicstl_free(node->obj);
    unicstl_free(node);

    self->_size -= 1;
    return true;
}

static bool dlinklist_pop_front(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    struct _dlinklist_node* node = NULL;
    struct _dlinklist_node* back = NULL;
    
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

    unicstl_free(node->obj);
    unicstl_free(node);

    self->_size -= 1;
    return true;
}

static bool dlinklist_back(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_tail->obj, self->_obj_size);
    return true;
}

static bool dlinklist_front(struct _dlinklist* self, void* obj)
{
    unicstl_assert(self != NULL);
    unicstl_assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }
    memmove(obj, self->_head->obj, self->_obj_size);
    return true;
}

static bool dlinklist_clear(struct _dlinklist* self)
{
    while (!self->empty(self))
    {
        dlinklist_pop_back(self, NULL);
    }
    return true;
}

static size_t dlinklist_size(struct _dlinklist* self)
{
    unicstl_assert(self != NULL);
    return self->_size;
}

static bool dlinklist_empty(struct _dlinklist* self)
{
    unicstl_assert(self != NULL);
    return !self->size(self);
}

static void dlinklist_destory(struct _dlinklist* self)
{
    unicstl_assert(self != NULL);
    self->clear(self);
    if (self->_head != NULL)
    {
        unicstl_free(self->_head);
        self->_head = NULL;
    }
}

static void dlinklist_print(struct _dlinklist* self)
{
    unicstl_assert(self != NULL);

    size_t i = 0;
    struct _dlinklist_node * node = self->_head;
    for (size_t i = 0; i < self->size(self); i++)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

bool dlinklist_iter_hasnext(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    dlinklist_t self = (dlinklist_t)iter->_container;
    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

const void* dlinklist_iter_next(struct _iterator* iter)
{
    unicstl_assert(iter != NULL);
    unicstl_assert(iter->_container != NULL);

    dlinklist_t self = (dlinklist_t)iter->_container;
    void *obj = NULL;
    
    struct _dlinklist_node * cur_node = (struct _dlinklist_node *)iter->_node;
    if(cur_node == NULL)
    {
        return NULL;
    }

    obj = cur_node->obj;
    if(iter->_order == DLLIST_FORWARD)
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

iterator_t dlinklist_iter(struct _dlinklist* self, enum _dlinklist_order order)
{
    unicstl_assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_order = order;
    if(iter->_order == DLLIST_FORWARD)
    {
        iter->_node = self->_head;
    }
    else
    {
        iter->_node = self->_tail;
    }

    iter->hasnext = dlinklist_iter_hasnext;
    iter->next = dlinklist_iter_next;
    return iter;
}

static bool dlinklist_init(struct _dlinklist* self, size_t obj_size)
{
    unicstl_assert(self != NULL);
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

    self->_destory = dlinklist_destory;

    // -------------------- public -------------------- 
    // kernel
    self->push_back = dlinklist_push_back;
    self->push_front = dlinklist_push_front;
    self->pop_back = dlinklist_pop_back;
    self->pop_front = dlinklist_pop_front;
    self->back = dlinklist_back;
    self->front = dlinklist_front;
    
    // base
    self->clear = dlinklist_clear;
    self->size = dlinklist_size;
    self->empty = dlinklist_empty;

    // iter
    self->iter = dlinklist_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug -------------------- 
    self->print = dlinklist_print;
    
    return true;
}

dlinklist_t dlinklist_new(size_t obj_size)
{
    struct _dlinklist* dlinklist = NULL;
    dlinklist = (struct _dlinklist*)unicstl_malloc(sizeof(struct _dlinklist));
    if(dlinklist == NULL)
    {
        log_warn("dlinklist malloc failed\n");
        return NULL;
    }

    if(dlinklist_init(dlinklist, obj_size) != true)
    {
        log_warn("dlinklist init failed\n");
        unicstl_free(dlinklist);
        return NULL;
    }
    return dlinklist;
}

void dlinklist_free(dlinklist_t *dlinklist)
{
    if(*dlinklist != NULL)
    {
        (*dlinklist)->_destory(*dlinklist);
        unicstl_free(*dlinklist);
    }
    *dlinklist = NULL;
}
