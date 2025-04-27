/**
 * @file tree.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _TREE_H_
#define _TREE_H_

#include "common.h"

#include "stack.h"
#include "queue.h"


typedef enum {
    RBT_RED,
    RBT_BLACK,
}rbt_color;

/**
 * @brief dfs amd bfs traversal order
 * 
 *  pre-order traversal
 *   in-order traversal
 *  post-order traversal
 *  breadth-first search traversal [BFS]
 * 
 *  right-first pre-order traversal
 *  right-first in-order traversal
 *  right-first post-order traversal
 *  breadth-first search traversal [BFS]
 */
enum _order{
    ORDER_PRE,
    ORDER_IN,
    ORDER_POST,
    ORDER_BREADTH,

    ORDER_PRE_R,
    ORDER_IN_R,
    ORDER_POST_R,
    ORDER_BREADTH_R,
};

struct _tree_node
{
    void *obj;
    struct _tree_node * left;
    struct _tree_node * right;
    struct _tree_node * parent;

    union 
    {
        int32_t balance;
        uint32_t color;
    };
};

struct _tree
{
    // -------------------- private -------------------- 
    struct _tree_node * _root;

    uint32_t _size;
    uint32_t _obj_size;
    uint32_t _capacity;
    uint32_t _ratio;

    enum _order _order;
    bool _right_priority;

    stack_t stack;
    queue_t queue;

    struct _iterator _iter;

    bool (*rebalance)(struct _tree* self, struct _tree_node* root);
    void (*_destory)(struct _tree* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*insert)(struct _tree* self, void* obj);
    bool (*delete)(struct _tree* self, void* obj);
    uint32_t (*height)(struct _tree* self);

    // base
    bool (*clear)(struct _tree* self);
    bool (*empty)(struct _tree* self);
    uint32_t (*size)(struct _tree* self);

    // iter
    iterator_t (*iter)(struct _tree* self, enum _order);

    // others
    bool (*min)(struct _tree* self, void* obj);
    bool (*max)(struct _tree* self, void* obj);

    // config 
    compare_fun_t compare;  // !!! you have to implement this function

    // -------------------- debug -------------------- 
    void (*print_obj)(void* obj);
};
typedef struct _tree* tree_t;

// create and free tree
tree_t tree_avl_new(uint32_t obj_size);
tree_t tree_rb_new(uint32_t obj_size);

void tree_free(tree_t* tree);

#endif // _TREE_H_
