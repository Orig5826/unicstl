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
    RBT_RED = 0x00,
    RBT_BLACK = 0x01,
}rbt_color;

enum _order{
    ORDER_LEFT_PRE = 0x01,
    ORDER_LEFT_IN = 0x02,
    ORDER_LEFT_POST = 0x03,
    ORDER_LEFT_BREADTH = 0x04,

    ORDER_RIGHT_PRE = 0x05,
    ORDER_RIGHT_IN = 0x06,
    ORDER_RIGHT_POST = 0x07,
    ORDER_RIGHT_BREADTH = 0x08,

    ORDER_PRE = ORDER_LEFT_PRE,
    ORDER_IN = ORDER_LEFT_IN,
    ORDER_POST = ORDER_LEFT_POST,
    ORDER_BREADTH = ORDER_LEFT_BREADTH,
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
    struct _tree_node * cur_node;

    struct _iterator _iter;

    // -------------------- public -------------------- 
    // kernel
    bool (*insert)(struct _tree* self, void* obj);
    bool (*delete)(struct _tree* self, void* obj);

    struct _tree_node* (*find)(struct _tree* self, void* obj);
    struct _tree_node* (*find_min)(struct _tree* self, struct _tree_node* root);
    struct _tree_node* (*find_max)(struct _tree* self, struct _tree_node* root);

    bool (*rebalance)(struct _tree* self, struct _tree_node* root);
    int32_t (*height)(struct _tree* self, struct _tree_node* root);

    bool (*min)(struct _tree* self, void* obj);
    bool (*max)(struct _tree* self, void* obj);

    // base
    bool (*clear)(struct _tree* self);
    bool (*empty)(struct _tree* self);
    uint32_t (*size)(struct _tree* self);

    // iter
    iterator_t (*iter)(struct _tree* self);

    /**
     * @brief 
     * 
     */
    void (*set_order)(struct _tree* self, enum _order order);
    void* (*begin)(struct _tree* self);
    void* (*next)(struct _tree* self);
    void* (*end)(struct _tree* self);

    /**
     * @brief obj compare with obj2
     * 
     * @return
     *      obj < obj2 return -1
     *      obj == obj2 return 0
     *      obj > obj2 return 1
     */
    int (*compare)(void* obj, void* obj2);

    // free
    void (*destory)(struct _tree* self);

    // -------------------- debug -------------------- 
    // traversal depth
    void (*order)(struct _tree* self, bool right_priority);

    void (*preorder)(struct _tree* self, struct _tree_node* root);
    void (*inorder)(struct _tree* self, struct _tree_node* root);
    void (*postorder)(struct _tree* self, struct _tree_node* root);
    // traversal breadth
    void (*breadth)(struct _tree* self, struct _tree_node* root);

    void (*print_obj)(void* obj);
};
typedef struct _tree* tree_t;

// create and free tree
tree_t tree_avl_new(uint32_t obj_size);
tree_t tree_rb_new(uint32_t obj_size);

void tree_free(tree_t* tree);

#endif // _TREE_H_

