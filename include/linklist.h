/**
 * @file linklist.h
 * @author wenjf (orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "unicstl_internal.h"
#include "iterator.h"

struct _linklist_node
{
    void *obj;
    struct _linklist_node *next;
};

struct _linklist
{
    // -------------------- private --------------------
    struct _linklist_node *_front;
    struct _linklist_node *_back;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;
    size_t _ratio;

    struct _iterator _iter;

    void (*_destory)(struct _linklist *self);

    // -------------------- public --------------------
    // kernel
    bool (*push_front)(struct _linklist *self, void *obj);      // O(1)
    bool (*pop_front)(struct _linklist *self, void *obj);       // O(1)
    bool (*push_back)(struct _linklist *self, void *obj);       // O(1)
    bool (*pop_back)(struct _linklist *self, void *obj);        // O(n)
    bool (*front)(struct _linklist* self, void* obj);           // O(1)
    bool (*back)(struct _linklist* self, void* obj);            // O(1)

    bool (*insert)(struct _linklist *self, const void *obj);    // O(n) = O(n) search + O(1) insert
    bool (*remove)(struct _linklist *self, void *obj);          // O(n) = O(n) search + O(1) remove

    bool (*contains)(struct _linklist *self, const void *obj);  // O(n)

    // base
    size_t (*size)(struct _linklist *self);
    size_t (*capacity)(struct _linklist *self);
    bool (*empty)(struct _linklist *self);
    bool (*clear)(struct _linklist *self);

    // iter
    iterator_t (*iter)(struct _linklist *self);

    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _linklist *self);
    void (*print_obj)(const void *obj);
};
typedef struct _linklist *linklist_t;

linklist_t linklist_new(size_t obj_size);
void linklist_free(linklist_t *linklist);

#endif
