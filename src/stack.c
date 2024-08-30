/**
 * @file stack.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "stack.h"

static uint32_t stack_capacity(struct _stack* self)
{
    assert(self != NULL);
    return self->_capacity;
}

static uint32_t stack_size(struct _stack* self)
{
    assert(self != NULL);
    return self->_size;
}

static bool stack_empty(struct _stack* self)
{
    assert(self != NULL);
    return stack_size(self) == 0;
}

static bool stack_peek(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }

    struct _stack_node * node = self->_head->next;
    memmove(obj, node->obj, self->_obj_size);
    return true;
}

static bool stack_push(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    void* new_obj = (void*)calloc(1, self->_obj_size);
    if (new_obj == NULL)
    {
        return false;
    }
    memmove(new_obj, obj, self->_obj_size);

    struct _stack_node* new_node = (struct _stack_node*)malloc(sizeof(struct _stack_node));
    if (new_node == NULL)
    {
        return false;
    }
    new_node->obj = new_obj;
    new_node->next = self->_head->next;
    self->_head->next = new_node;

    self->_size += 1;
    return true;
}

static bool stack_pop(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    // assert(obj != NULL);
    
    if (self->empty(self))
    {
        return false;
    }

    struct _stack_node* node = self->_head->next;

    if (obj != NULL)
    {
        memmove(obj, node->obj, self->_obj_size);
    }
    self->_head->next = node->next;

    free(node->obj);
    free(node);

    self->_size -= 1;
    return true;
}

static bool stack_clear(struct _stack* self)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return true;
    }

    struct _stack_node* node = self->_head->next;
    while (node != NULL)
    {
        self->_head->next = node->next;

        free(node->obj);
        free(node);

        node = self->_head->next;
    }
    self->_size = 0;
    return true;
}

static void stack_destory(struct _stack* self)
{
    assert(self != NULL);
    self->clear(self);
    if(self->_head != NULL)
    {
        free(self->_head);
        self->_head = NULL;
    }
}

static void stack_print(struct _stack* self)
{
    uint32_t i = 0;
    struct _stack_node* node = self->_head->next;
    while (node != NULL)
    {
        self->print_obj(node->obj);
        node = node->next;
    }
}

static bool stack2_peek(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }

    uint32_t top = self->size(self) - 1;
    uint32_t offset = top * self->_obj_size;
    memmove(obj, (char *)self->_head->obj + offset, self->_obj_size);
    return true;
}

static bool stack2_push(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    if (self->size(self) == self->capacity(self))
    {
        void* obj_new = (void*)realloc(self->_head->obj, self->capacity(self) * self->_obj_size * self->_ratio);
        if (obj_new == NULL)
        {
            return false;
        }
        self->_head->obj = obj_new;
    }

    uint32_t top = self->size(self);
    uint32_t offset = top * self->_obj_size;
    memmove((char*)self->_head->obj + offset, obj, self->_obj_size);

    self->_size += 1;
    return true;
}

static bool stack2_pop(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    // assert(obj != NULL);

    if (self->empty(self))
    {
        return false;
    }

    if (obj != NULL)
    {
        uint32_t top = self->size(self) - 1;
        uint32_t offset = top * self->_obj_size;
        memmove(obj, (char*)self->_head->obj + offset, self->_obj_size);
    }

    self->_size -= 1;
    return true;
}


static void stack2_destory(struct _stack* self)
{
    assert(self != NULL);
    self->clear(self);
    if(self->_head != NULL)
    {
        if(self->_head->obj != NULL)
        {
            free(self->_head->obj);
            self->_head->obj = NULL;
        }
        free(self->_head);
        self->_head = NULL;
    }
}

static void stack2_print(struct _stack* self)
{
    assert(self != NULL);
    assert(self->_head != NULL);

    void* obj = NULL;
    uint32_t offset = 0;

    for (int i = self->size(self) - 1; i >= 0; i--)
    {
        offset = self->_obj_size * i;
        obj = (char*)self->_head->obj + offset;
        self->print_obj(obj);
    }
}


bool stack_init(struct _stack* self, uint32_t obj_size)
{
    assert(self != NULL);
    assert(obj_size != 0);
    if(self == NULL || obj_size == 0)
    {
        return false;
    }

    // 1. set attr
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = UINT32_MAX;
    self->_ratio = 1;
    
    // 2. set function
    // kernel
    self->peek = stack_peek;
    self->pop = stack_pop;
    self->push = stack_push;

    // base
    self->empty = stack_empty;
    self->size = stack_size;
    self->capacity = stack_capacity;

    // clear and free node
    self->clear = stack_clear;
    self->destory = stack_destory;
    // print
    self->print = stack_print;

    // 3. set node
    self->_head = (struct _stack_node *)malloc(sizeof(struct _stack_node));
    if (self->_head == NULL)
    {
        return false;
    }
    self->_head->obj = NULL;
    self->_head->next = NULL;

    return true;
}

bool stack_init2(struct _stack* self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);

    // 1. set attr
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_ratio = 2;

    // 2. set function
    // kernel
    self->peek = stack2_peek;
    self->pop = stack2_pop;
    self->push = stack2_push;

    // others
    self->empty = stack_empty;
    self->size = stack_size;
    self->capacity = stack_capacity;

    // clear and free node
    self->clear = stack_clear;
    self->destory = stack2_destory;
    // print
    self->print = stack2_print;

    // 3. set node
    self->_head = (struct _stack_node*)malloc(sizeof(struct _stack_node));
    if (self->_head == NULL)
    {
        return false;
    }
    // self->_head->obj = NULL;
    self->_head->next = NULL;

    // 4. set array
    self->_head->obj = (void *)calloc(self->_capacity, self->_obj_size);
    if (self->_head->obj == NULL)
    {
        return false;
    }
    return true;
}

stack_t stack_new(void)
{
    return (struct _stack*)calloc(1, sizeof(struct _stack));
}

void stack_free(stack_t *stack)
{
    assert(stack != NULL);
    if(stack != NULL && *stack != NULL)
    {
        if((*stack)->destory != NULL)
        {
            (*stack)->destory(*stack);
        }
        free(*stack);
        *stack = NULL;
    }
}
