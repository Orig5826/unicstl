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

    uint32_t _index_front;
    uint32_t _index_back;

    uint32_t _obj_size;
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _ratio;

    struct _iterator _iter;

    void (*_destory)(struct _linklist *self);

    // -------------------- public --------------------
    // kernel
    bool (*push)(struct _linklist *self, void *obj);
    bool (*pop)(struct _linklist *self, void *obj);
    bool (*back)(struct _linklist *self, void *obj);
    bool (*front)(struct _linklist *self, void *obj);
    bool (*empty)(struct _linklist *self);
    bool (*full)(struct _linklist *self);

    // base
    uint32_t (*size)(struct _linklist *self);
    uint32_t (*capacity)(struct _linklist *self);
    bool (*clear)(struct _linklist *self);

    // iter
    iterator_t (*iter)(struct _linklist *self);

    // -------------------- debug --------------------
    void (*print)(struct _linklist *self);
    void (*print_obj)(void *obj);
};
typedef struct _linklist *linklist_t;

linklist_t linklist_new(uint32_t obj_size);
void linklist_free(linklist_t *linklist);

#endif
