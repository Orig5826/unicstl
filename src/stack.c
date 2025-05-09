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

static struct _stack_node* stack_node_new(void *obj, uint32_t obj_size)
{
    void* new_obj = (void*)calloc(1, obj_size);
    if (new_obj == NULL)
    {
        goto done;
    }
    memmove(new_obj, obj, obj_size);

    struct _stack_node* new_node = (struct _stack_node*)malloc(sizeof(struct _stack_node));
    if (new_node == NULL)
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

static void stack_node_free(struct _stack_node** node)
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

static bool stack_push(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
    assert(obj != NULL);

    struct _stack_node* new_node = stack_node_new(obj, self->_obj_size);
    if (new_node == NULL)
    {
        return false;
    }
    new_node->next = self->_head->next;
    self->_head->next = new_node;

    self->_size += 1;
    return true;
}

static bool stack_pop(struct _stack* self, void* obj)
{
    assert(self != NULL);
    assert(self->_head != NULL);
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

    stack_node_free(&node);
    self->_size -= 1;
    return true;
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

static uint32_t stack_size(struct _stack* self)
{
    assert(self != NULL);
    return self->_size;
}

static bool stack_empty(struct _stack* self)
{
    assert(self != NULL);
    assert(self->size != NULL);
    return self->size(self) == 0;
}

static uint32_t stack_capacity(struct _stack* self)
{
    assert(self != NULL);
    return self->_capacity;
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
        stack_node_free(&node);
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

bool stack_iter_hasnext(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->_container != NULL);

    stack_t self = (stack_t)iter->_container;
    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

/**
 * @brief iter next
 *  from top to bottom
 */
const void* stack_iter_next(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->_container != NULL);

    stack_t self = (stack_t)iter->_container;
    void *obj = NULL;

    if(self->_head->obj == NULL)
    {
        // base on linklist
        struct _stack_node* node = (struct _stack_node *)iter->_node;
        if(node != NULL)
        {
            obj = node->obj;
            iter->_node = node->next;
        }
    }
    else
    {
        // base on array
        uint32_t index = self->size(self) - 1 - iter->_index;
        obj = self->_head->obj + self->_obj_size * index;
    }
    
    iter->_index += 1;
    return obj;
}

iterator_t stack_iter(struct _stack* self)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_node = self->_head->next;

    iter->hasnext = stack_iter_hasnext;
    iter->next = stack_iter_next;
    return iter;
}

static bool stack_init(struct _stack* self, uint32_t obj_size)
{
    // assert(self != NULL);
    // assert(obj_size != 0);
    if(self == NULL || obj_size == 0)
    {
        return false;
    }

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = UINT32_MAX;
    self->_ratio = 1;

    self->_head = (struct _stack_node *)malloc(sizeof(struct _stack_node));
    if (self->_head == NULL)
    {
        return false;
    }
    self->_head->obj = NULL;
    self->_head->next = NULL;

    self->_destory = stack_destory;

    // -------------------- public --------------------
    // kernel
    self->push = stack_push;
    self->pop = stack_pop;
    self->peek = stack_peek;
    self->empty = stack_empty;

    // base
    self->size = stack_size;
    self->capacity = stack_capacity;
    self->clear = stack_clear;

    // iter
    self->iter = stack_iter;
    
    // -------------------- default --------------------
    self->print_obj = default_print_obj;
    
    // -------------------- debug --------------------
    self->print = stack_print;

    return true;
}

static bool stack_init2(struct _stack* self, uint32_t obj_size, uint32_t capacity)
{
    // assert(self != NULL);
    if(self == NULL || obj_size == 0 || capacity == 0)
    {
        return false;
    }

    // -------------------- private --------------------
    self->_obj_size = obj_size;
    self->_size = 0;
    self->_capacity = capacity;
    self->_ratio = 2;

    self->_head = (struct _stack_node*)malloc(sizeof(struct _stack_node));
    if (self->_head == NULL)
    {
        return false;
    }
    self->_head->next = NULL;

    self->_head->obj = (void *)calloc(self->_capacity, self->_obj_size);
    if (self->_head->obj == NULL)
    {
        free(self->_head);
        self->_head = NULL;
        return false;
    }

    self->_iter.next = stack_iter_next;
    self->_iter.hasnext = stack_iter_hasnext;

    self->_destory = stack2_destory;

    // -------------------- public --------------------
    // kernel
    self->push = stack2_push;
    self->pop = stack2_pop;
    self->peek = stack2_peek;
    self->empty = stack_empty;

    // base
    self->size = stack_size;
    self->capacity = stack_capacity;
    self->clear = stack_clear;

    // iter
    self->iter = stack_iter;

    // -------------------- default --------------------
    self->print_obj = default_print_obj;

    // -------------------- debug --------------------
    self->print = stack2_print;

    return true;
}

stack_t stack_new(uint32_t obj_size)
{
    stack_t stack = NULL;
    stack = (struct _stack*)calloc(1, sizeof(struct _stack));
    if(stack == NULL)
    {
        return NULL;
    }

    if(stack_init(stack, obj_size) != true)
    {
        free(stack);
        return NULL;
    }
    return stack;
}

stack_t stack_new2(uint32_t obj_size, uint32_t capacity)
{
    stack_t stack = NULL;
    stack = (struct _stack*)calloc(1, sizeof(struct _stack));
    if (stack == NULL)
    {
        return NULL;
    }

    if(stack_init2(stack, obj_size, capacity) != true)
    {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_free(stack_t *stack)
{
    assert(stack != NULL);
    if(stack != NULL && *stack != NULL)
    {
        if((*stack)->_destory != NULL)
        {
            (*stack)->_destory(*stack);
        }
        free(*stack);
        *stack = NULL;
    }
}
