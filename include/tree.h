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

#if AVLTREE == 1 || RAVLTREE == 1
// typedef int tree_data_t;

typedef struct _tree_node_t
{
    tree_data_t data;
    struct _tree_node_t * left;
    struct _tree_node_t * right;
    struct _tree_node_t * parent;
    int32_t balance;		// balance of avl tree
}tree_node_t, *ptree_node_t;


typedef struct _tree_t
{
    struct _tree_node_t * tree;
    uint32_t size;
}tree_t, *ptree_t;

typedef void (*tree_data_disp_t)(tree_data_t data);

#endif


#if RAVLTREE == 1
    bool tree_init(ptree_node_t *head);
    void tree_destroy(ptree_node_t *head);
    bool tree_empty(ptree_node_t head);
    void tree_clear(ptree_node_t head);
    uint32_t tree_get_size(ptree_node_t head);

    bool tree_insert(ptree_node_t head, tree_data_t data);
    bool tree_delete(ptree_node_t head, tree_data_t data);
    bool tree_get_min(ptree_node_t head, tree_data_t *data);
    bool tree_get_max(ptree_node_t head, tree_data_t *data);

    void tree_traversal_depth_preorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
    void tree_traversal_depth_inorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
    //void tree_traversal_depth_postorder(ptree_node_t head, tree_data_disp_t tree_data_disp);
    //void tree_traversal_breadth(ptree_node_t head, tree_data_disp_t tree_data_disp);

#endif

#if AVLTREE == 1
    bool tree_init(ptree_t *head);
    void tree_destroy(ptree_t *head);
    bool tree_empty(ptree_t head);
    void tree_clear(ptree_t head);
    uint32_t tree_get_size(ptree_t head);

    bool tree_insert(ptree_t head, tree_data_t data);
    bool tree_delete(ptree_t head, tree_data_t data);
    bool tree_get_min(ptree_t head, tree_data_t *data);
    bool tree_get_max(ptree_t head, tree_data_t *data);

    void tree_traversal_depth_preorder(ptree_t head, tree_data_disp_t tree_data_disp);
    void tree_traversal_depth_inorder(ptree_t head, tree_data_disp_t tree_data_disp);
    void tree_traversal_depth_postorder(ptree_t head, tree_data_disp_t tree_data_disp);
    void tree_traversal_breadth(ptree_t head, tree_data_disp_t tree_data_disp);
#endif

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
    struct _tree_node * _root;

    uint32_t _size;				// 栈大小
    uint32_t _obj_size;			// 元素大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率

    bool _right_priority;		// 右优先

    // kernel
    bool (*insert)(struct _tree* self, void* obj);
    bool (*delete)(struct _tree* self, void* obj);

    struct _tree_node* (*find)(struct _tree* self, void* obj);
    struct _tree_node* (*find_min)(struct _tree* self, struct _tree_node* root);
    struct _tree_node* (*find_max)(struct _tree* self, struct _tree_node* root);

    bool (*rebalance)(struct _tree* self, struct _tree_node* root);
    int32_t (*height)(struct _tree* self, struct _tree_node* root);

    bool (*min)(struct _tree* self, void** obj);
    bool (*max)(struct _tree* self, void** obj);

    bool (*clear)(struct _tree* self);
    bool (*empty)(struct _tree* self);
    uint32_t (*size)(struct _tree* self);

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

    // ----- print -----
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

// bst_tree
bool tree_avl_init(struct _tree *self, uint32_t obj_size);
bool tree_rb_init(struct _tree *self, uint32_t obj_size);

tree_t tree_new(void);
void tree_free(tree_t tree);

#endif // _TREE_H_

