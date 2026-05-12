/**
 * @file dlinklist.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-12
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _DLINKLIST_H_
#define _DLINKLIST_H_

#include "unicstl_internal.h"

enum _dlinklist_order
{
    DLLIST_FORWARD,
    DLLIST_REVERSE,
};

struct _dlinklist_node
{
    void* obj;
    struct _dlinklist_node* prev;
    struct _dlinklist_node* next;
};

struct _dlinklist
{
    // -------------------- private -------------------- 
    struct _dlinklist_node* _head;
    struct _dlinklist_node* _tail;

    size_t _obj_size;
    size_t _size;
    // size_t _capacity;
    // size_t _ratio;

    struct _iterator _iter;

    void (*_destory)(struct _dlinklist* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push_back)(struct _dlinklist* self, void* obj);
    bool (*push_front)(struct _dlinklist* self, void* obj);
    bool (*pop_back)(struct _dlinklist* self, void* obj);
    bool (*pop_front)(struct _dlinklist* self, void* obj);
    bool (*back)(struct _dlinklist* self, void* obj);
    bool (*front)(struct _dlinklist* self, void* obj);
    
    // base
    size_t(*size)(struct _dlinklist* self);
    bool (*clear)(struct _dlinklist* self);
    bool (*empty)(struct _dlinklist* self);

    // iter
    iterator_t (*iter)(struct _dlinklist* self, enum _dlinklist_order order);

    // -------------------- debug -------------------- 
    void (*print)(struct _dlinklist* self);
    void (*print_obj)(const void* obj);
};
typedef struct _dlinklist* dlinklist_t;

dlinklist_t dlinklist_new(size_t obj_size);
void dlinklist_free(dlinklist_t* dlinklist);

#endif
