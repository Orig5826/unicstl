/**
 * @file rbtree.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-22
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "unicstl_internal.h"

#include "darray.h"
#include "stack.h"
#include "queue.h"

typedef enum {
    RBT_RED,
    RBT_BLACK,
}rbt_color_t;

typedef struct _rbt_node
{
    size_t idx;
    size_t left;
    size_t right;
    size_t parent;
    rbt_color_t color;
}rbt_node_t;

struct _rbtree
{
    // -------------------- private -------------------- 
    darray_t _keys;
    darray_t _nodes;
    stack_t _free;

    size_t _root;

    size_t _size;
    size_t _obj_size;
    size_t _capacity;

    // temporary for iter
    stack_t _stack;
    queue_t _queue;

    struct _iterator _iter;

    bool (*_rebalance)(struct _rbtree* self, struct _rbt_node* root);
    void (*_destory)(struct _rbtree* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*insert)(struct _rbtree* self, void* obj);
    bool (*remove)(struct _rbtree* self, void* obj);
    size_t (*height)(struct _rbtree* self);

    // base
    bool (*reserve)(struct _rbtree* self, size_t capacity);
    bool (*resize)(struct _rbtree* self, size_t size);
    size_t (*size)(struct _rbtree* self);
    size_t (*capacity)(struct _rbtree* self);
    bool (*empty)(struct _rbtree* self);
    bool (*full)(struct _rbtree* self);
    bool (*clear)(struct _rbtree* self);

    // iter
    iterator_t (*iter)(struct _rbtree* self, tree_order_t order);

    // others
    bool (*min)(struct _rbtree* self, void* obj);
    bool (*max)(struct _rbtree* self, void* obj);

    // config 
    compare_fun_t compare;  // !!! you have to implement this function

    // -------------------- debug -------------------- 
    void (*print_obj)(const void* obj);
    void (*print)(struct _rbtree* self);
};
typedef struct _rbtree* rbtree_t;

// create and free tree
rbtree_t rbtree_new(size_t obj_size, size_t capacity, compare_fun_t compare);
void rbtree_free(rbtree_t* tree);

#endif // _TREE_H_
