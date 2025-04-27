/**
 * @file tree.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "tree.h"
#include "queue.h"
#include "stack.h"

#define TREE_RECURSIVE_ENABLED 

static struct _tree_node* tree_node_new(struct _tree* self, void* obj)
{
    assert(self != NULL);

    void* obj_new = malloc(self->_obj_size);
    if (obj_new == NULL)
    {
        return NULL;
    }
    memmove(obj_new, obj, self->_obj_size);

    struct _tree_node* node_new = (struct _tree_node*)malloc(sizeof(struct _tree_node));
    if (node_new == NULL)
    {
        free(obj_new);
        return NULL;
    }
    node_new->obj = obj_new;
    node_new->parent = NULL;
    node_new->left = NULL;
    node_new->right = NULL;
    node_new->balance = 0;

    return node_new;
}

static void tree_node_free(struct _tree_node** node)
{
    if (node != NULL && (*node) != NULL)
    {
        if ((*node)->obj != NULL)
        {
            free((*node)->obj);
        }
        free(*node);
        *node = NULL;
    }
    else
    {
        printf("+++\n");
    }
}

static uint32_t tree_height_node(struct _tree* self, struct _tree_node* root)
{
#ifdef TREE_RECURSIVE_ENABLED
    assert(self != NULL);
    if (root == NULL)
    {
        return 0;
    }
    uint32_t left_height = tree_height_node(self, root->left);
    uint32_t right_height = tree_height_node(self, root->right);
    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
#else
    assert(self != NULL);
    if (root == NULL)
    {
        return 0;
    }
    uint32_t height = 0;
    uint32_t count_cur_level = 0;
    uint32_t count_next_level = 0;

    struct _tree_node* node = root;
    queue_t queue = queue_new(sizeof(struct _tree_node*));

    queue->push(queue, &node);
    while (!queue->empty(queue))
    {
        queue->pop(queue, &node);
        if (node->left != NULL)
        {
            queue->push(queue, &node->left);
        }
        if (node->right != NULL)
        {
            queue->push(queue, &node->right);
        }

        if (count_cur_level == count_next_level)
        {
            count_next_level = queue->size(queue);
            height++;
            count_cur_level = 1;
        }
        else
        {
            count_cur_level++;
        }
    }
    queue_free(&queue);
    return height;
#endif
}

static void tree_set_balance(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    if (node == NULL)
    {
        return;
    }
    node->balance = (int32_t)(tree_height_node(self, node->right) - tree_height_node(self, node->left));
}

static struct _tree_node* tree_turn_left(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->right;
    if (node == NULL)
    {
        return root;
    }

    if (root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if (root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->right = node->left;           // step4
    if (node->left != NULL)
    {
        node->left->parent = root;      // step5
    }
    node->left = root;                  // step6

    tree_set_balance(self, root);
    tree_set_balance(self, node);
    return node;
}

static struct _tree_node* tree_turn_right(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->left;
    if (node == NULL)
    {
        return root;
    }

    if (root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if (root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->left = node->right;           // step4
    if (node->right != NULL)
    {
        node->right->parent = root;     // step5
    }
    node->right = root;                 // step6

    tree_set_balance(self, root);
    tree_set_balance(self, node);
    return node;
}

static struct _tree_node* tree_turn_left_then_right(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->left;
    if (node != NULL)
    {
        tree_turn_left(self, node);
    }
    node = tree_turn_right(self, root);
    return node;
}

static struct _tree_node* tree_turn_right_then_left(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->right;
    if (node != NULL)
    {
        tree_turn_right(self, node);
    }
    node = tree_turn_left(self, root);
    return node;
}

/**
 * @brief
 *
 * if balance = rigth - left，so
 *
 * | case | root->balance | node->balance | function |
 * | ---- | ------------ | -------------- | -------- |
 * | 1    |  2           | >= 0           | left rotation
 * | 2    |  2           | < 0            | first right rotation, then left rotation
 * | 3    | -2           | <= 0           | right rotation
 * | 4    | -2           | > 0            | forth left rotation, then right rotation
 *
 * @param self
 * @return true
 * @return false
 */
static bool tree_avl_rebalance(struct _tree* self, struct _tree_node* root)
{
#ifdef TREE_RECURSIVE_ENABLED
    assert(self != NULL);
    if (root == NULL)
    {
        return false;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return false;
    }

    tree_set_balance(self, root);
    int balance = root->balance;
    if (balance == 2)
    {
        if (root->right->balance >= 0)
        {
            root = tree_turn_left(self, root);
        }
        else
        {
            root = tree_turn_right_then_left(self, root);
        }
    }
    else if (balance == -2)
    {
        if (root->left->balance <= 0)
        {
            root = tree_turn_right(self, root);
        }
        else
        {
            root = tree_turn_left_then_right(self, root);
        }
    }

    if (root->parent != NULL)
    {
        tree_avl_rebalance(self, root->parent);
    }
    else
    {
        self->_root = root;
    }
    return true;

#else
    assert(self != NULL);
    if (root == NULL)
    {
        return false;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return false;
    }
    int balance = 0;

    do
    {
        tree_set_balance(self, root);
        balance = root->balance;
        if (balance == 2)
        {
            if (root->right->balance >= 0)
            {
                root = tree_turn_left(self, root);
            }
            else
            {
                root = tree_turn_right_then_left(self, root);
            }
        }
        else if (balance == -2)
        {
            if (root->left->balance <= 0)
            {
                root = tree_turn_right(self, root);
            }
            else
            {
                root = tree_turn_left_then_right(self, root);
            }
        }

        // if node become the new root
        if (root->parent == NULL)
        {
            break;
        }
        root = root->parent;
    } while (root != NULL);

    self->_root = root;
    return true;
#endif
}

static struct _tree_node* tree_find(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* root = self->_root;
    while (root != NULL)
    {
        if (self->compare(obj, root->obj) == 0)
        {
            return root;
        }
        else if (self->compare(obj, root->obj) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return NULL;
}

static struct _tree_node* tree_find_min(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    while (root != NULL)
    {
        if (root->left == NULL)
        {
            break;
        }
        root = root->left;
    }
    return root;
}

static struct _tree_node* tree_find_max(struct _tree* self, struct _tree_node* root)
{
    while (root != NULL)
    {
        if (root->right == NULL)
        {
            break;
        }
        root = root->right;
    }
    return root;
}

/**
 * @brief find the position to insert or find object
 *
 * @param self
 * @param obj
 */
struct _tree_node* tree_find_pos(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(self->compare != NULL);

    struct _tree_node* root = self->_root;
    while (root != NULL)
    {
        if (self->compare(obj, root->obj) < 0)
        {
            if (root->left == NULL)
            {
                break;
            }
            root = root->left;
        }
        else if(self->compare(obj, root->obj) > 0)
        {
            if (root->right == NULL)
            {
                break;
            }
            root = root->right;
        }
        else
        {
            // if obj exist
            break;
        }
    }
    return root;
}


static bool tree_avl_insert(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    if (self->_root == NULL)
    {
        // if tree is empty
        struct _tree_node* new_node = tree_node_new(self, obj);
        if (new_node == NULL)
        {
            return false;
        }

        self->_root = new_node;
    }
    else
    {
        struct _tree_node* root = tree_find_pos(self, obj);
        if (self->compare(obj, root->obj) == 0)
        {
            // if obj is exist in tree, return false
            return false;
        }

        struct _tree_node* new_node = tree_node_new(self, obj);
        if (new_node == NULL)
        {
            return false;
        }

        if (self->compare(obj, root->obj) < 0)
        {
            root->left = new_node;
            new_node->parent = root;
        }
        else /*if (self->compare(obj, root->obj) > 0)*/
        {
            root->right = new_node;
            new_node->parent = root;
        }

        self->_rebalance(self, root);
    }

    self->_size++;
    return true;
}

static bool tree_avl_delete_single_child(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    assert(node != NULL);

    if (node->parent == NULL)
    {
        if (node->left != NULL)
        {
            node->left->parent = node->parent;      // step1 : NULL for root
            self->_root = node->left;               // step2
        }
        else if (node->right != NULL)
        {
            node->right->parent = node->parent;     // step1 : NULL for root
            self->_root = node->right;              // step2
        }
        else
        {
            self->_root = NULL;
        }
    }
    else
    {
        if (node->parent->left == node)
        {
            if (node->left != NULL)
            {
                node->left->parent = node->parent;      // step1
                node->parent->left = node->left;        // step2
            }
            else if (node->right != NULL)
            {
                node->right->parent = node->parent;     // step1
                node->parent->left = node->right;       // step2
            }
            else
            {
                node->parent->left = NULL;
            }
        }
        else if (node->parent->right == node)
        {
            if (node->left != NULL)
            {
                node->left->parent = node->parent;      // step1
                node->parent->right = node->left;       // step2
            }
            else if (node->right != NULL)
            {
                node->right->parent = node->parent;     // step1
                node->parent->right = node->right;      // step2
            }
            else
            {
                node->parent->right = NULL;
            }
        }

        self->_rebalance(self, node->parent);
    }
    tree_node_free(&node);
    return true;
}

static bool tree_avl_delete_double_child(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    assert(node != NULL);
    struct _tree_node* tmp = tree_find_min(self, node->right);
    if (tmp != NULL)
    {
        memmove(node->obj, tmp->obj, self->_obj_size);
        tree_avl_delete_single_child(self, tmp);
    }
    return true;
}

static bool tree_avl_delete(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    if (self->empty(self))
    {
        return false;
    }

    struct _tree_node* node = tree_find(self, obj);
    if (node == NULL)
    {
        return false;
    }

    if ((node->left != NULL) && (node->right != NULL))
    {
        // have two child
        tree_avl_delete_double_child(self, node);
    }
    else
    {
        // have singule child or no child
        tree_avl_delete_single_child(self, node);
    }

    self->_size--;
    return true;
}

static bool tree_clear(struct _tree* self)
{
    assert(self != NULL);
    if (self->_root == NULL)
    {
        // return false;
        return true;
    }

    struct _tree_node* node = self->_root;
    queue_t queue = queue_new(sizeof(struct _tree_node*));

    queue->push(queue, &node);
    while (!queue->empty(queue))
    {
        queue->pop(queue, &node);
        if (node->left != NULL)
        {
            queue->push(queue, &node->left);
        }
        if (node->right != NULL)
        {
            queue->push(queue, &node->right);
        }
        tree_node_free(&node);
    }
    queue_free(&queue);
    self->_root = NULL;
    self->_size = 0;
    return true;
}

static bool tree_empty(struct _tree* self)
{
    assert(self != NULL);
    return !self->size(self);
}

static uint32_t tree_size(struct _tree* self)
{
    assert(self != NULL);
    return self->_size;
}

// free
static void tree_destory(struct _tree* self)
{
    assert(self != NULL);
    self->clear(self);
    self->_root = NULL;

    if (self->stack != NULL)
    {
        stack_free(&self->stack);
    }
    if (self->queue != NULL)
    {
        queue_free(&self->queue);
    }
}

static bool tree_min(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* node = tree_find_min(self, self->_root);
    if (node == NULL)
    {
        return false;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}

static bool tree_max(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* node = tree_find_max(self, self->_root);
    if (node == NULL)
    {
        return false;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}



static rbt_color tree_color(struct _tree_node* node)
{
    assert(node != NULL);
    return node->color;
}

static bool tree_set_color(struct _tree_node* node, rbt_color color)
{
    assert(node != NULL);
    node->color = color;
    return true;
}


static struct _tree_node* tree_rb_turn_left(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->right;
    if (node == NULL)
    {
        return root;
    }

    if (root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if (root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->right = node->left;           // step4
    if (node->left != NULL)
    {
        node->left->parent = root;      // step5
    }
    node->left = root;                  // step6
    return node;
}

static struct _tree_node* tree_rb_turn_right(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->left;
    if (node == NULL)
    {
        return root;
    }

    if (root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if (root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->left = node->right;           // step4
    if (node->right != NULL)
    {
        node->right->parent = root;     // step5
    }
    node->right = root;                 // step6
    return node;
}

static bool tree_rb_insert(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    struct _tree_node* new_node = NULL;
    if (self->_root == NULL)
    {
        // if tree is empty
        new_node = tree_node_new(self, obj);
        if (new_node == NULL)
        {
            return false;
        }

        self->_root = new_node;
    }
    else
    {
        struct _tree_node* root = tree_find_pos(self, obj);
        if (self->compare(obj, root->obj) == 0)
        {
            // if obj is exist in tree, return false
            return false;
        }

        new_node = tree_node_new(self, obj);
        if (new_node == NULL)
        {
            return false;
        }

        if (self->compare(obj, root->obj) < 0)
        {
            root->left = new_node;
            new_node->parent = root;
        }
        else /*if (self->compare(obj, root->obj) > 0)*/
        {
            root->right = new_node;
            new_node->parent = root;
        }
    }

    self->_rebalance(self, new_node);

    self->_size++;
    return true;
}

/**
 * @brief
 *
 * 以 balance = rigth - left 为标准，调整平衡因子
 *
 * | 情况 | root->balance | node->balance | 调整方式 |
 * | ---- | ------------ | -------------- | -------- |
 * | 1    |  2           | >= 0           | 左旋
 * | 2    |  2           | < 0            | 先右旋后左旋
 * | 3    | -2           | <= 0           | 右旋
 * | 4    | -2           | > 0            | 先左旋后右旋
 *
 * @param self
 * @return true
 * @return false
 */
static bool tree_rb_rebalance(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    if (node == NULL)
    {
        return false;
    }
    struct _tree_node* father = NULL;
    struct _tree_node* grandfather = NULL;
    struct _tree_node* uncle = NULL;

    /**
     * @brief 新插入节点为红色，且父节点为红色的情况下，需要调整。
     *
     * 主要考虑前三种情况[1-3]，其余三种[4-6]对称操作即可
     *
     * 原则只有一个，那就是想办法维持红黑树性质不变
     *
     * | 情况 | 说明 | 调整方式 |
     * | ---- | --- | -------- |
     * | 0 | 父节点为黑色 | 不用处理
     * | 1 | 父红，爷黑，叔红 | 仅变色即可：父黑，爷红，叔黑
     * | 2 | 父红，爷黑，叔黑 | （若爷孙在同一边）父黑，爷红，爷左/右旋
     * | 3 | 父红，爷黑，叔黑 | （若爷孙在不同边）先父左右旋，将新父变黑，随后爷红，爷左/右旋
     */
    while (node->parent != NULL && node->parent->color == RBT_RED)
    {
        father = node->parent;
        grandfather = father->parent;
        if (father == grandfather->left)
        {
            uncle = grandfather->right;
            if (uncle != NULL && uncle->color == RBT_RED)        // uncle is red
            {
                father->color = RBT_BLACK;
                uncle->color = RBT_BLACK;
                grandfather->color = RBT_RED;
                node = grandfather;
            }
            else                                                // uncle is black
            {
                if (node == father->right)
                {
                    node = tree_rb_turn_left(self, father);
                    node->color = RBT_BLACK;
                }
                else
                {
                    father->color = RBT_BLACK;
                }
                grandfather->color = RBT_RED;
                node = tree_rb_turn_right(self, grandfather);
                break;
            }
        }
        else
        {
            uncle = grandfather->left;
            if (uncle != NULL && uncle->color == RBT_RED)        // uncle is red
            {
                father->color = RBT_BLACK;
                uncle->color = RBT_BLACK;
                grandfather->color = RBT_RED;
                node = grandfather;
            }
            else                                                // uncle is black
            {
                if (node == father->left)
                {
                    node = tree_rb_turn_right(self, father);
                    node->color = RBT_BLACK;
                }
                else
                {
                    father->color = RBT_BLACK;
                }
                grandfather->color = RBT_RED;
                node = tree_rb_turn_left(self, grandfather);
                break;
            }
        }
    }

    if (node->parent == NULL)
    {
        self->_root = node;
        node->color = RBT_BLACK;
    }
    return true;
}

static bool tree_rb_delete_fix(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    struct _tree_node* father = NULL;
    struct _tree_node* brother = NULL;
    struct _tree_node* tmp = NULL;
    if (node == NULL)
    {
        return false;
    }

    // the color of node is black
    while (node->parent != NULL && node->color == RBT_BLACK)
    {
        father = node->parent;
        if (father->left == node)
        {
            brother = father->right;
            if (brother->color == RBT_RED)
            {
                // case 1
                // father is black, brother is red
                // brother has two black children
                // so ...
                brother->color = RBT_BLACK;
                father->color = RBT_RED;
                tmp = tree_rb_turn_left(self, father);
                // After deleting the node, it became unbalanced
                // so convert to case5
            }
            else if (brother->right != NULL && brother->right->color == RBT_RED)
            {
                // case 2
                brother->color = father->color;
                father->color = RBT_BLACK;
                brother->right->color = RBT_BLACK;
                node = tree_rb_turn_left(self, father);
                // After deleting the node, it remains balanced
                break;
            }
            else if (brother->left != NULL && brother->left->color == RBT_RED)
            {
                // case 3
                brother->color = RBT_RED;
                brother->left->color = RBT_BLACK;
                tmp = tree_rb_turn_right(self, brother);
                // Convert to case2
            }
            else
            {
                if (father->color == RBT_BLACK)
                {
                    // case 4
                    // father is black, brother has no children
                    brother->color = RBT_RED;
                    node = father;
                    // After deleting the node, it became unbalanced
                }
                else
                {
                    // case 5
                    // father is red, brother has no children
                    // if delete the node, it remains balanced
                    brother->color = RBT_RED;
                    father->color = RBT_BLACK;
                    break;
                }
            }
        }
        else
        {
            // symmetric
            brother = father->left;
            if (brother->color == RBT_RED)
            {
                // case1
                brother->color = RBT_BLACK;
                father->color = RBT_RED;
                tmp = tree_rb_turn_right(self, father);
            }
            else if (brother->left != NULL && brother->left->color == RBT_RED)
            {
                // case2
                brother->color = father->color;
                father->color = RBT_BLACK;
                brother->left->color = RBT_BLACK;
                node = tree_rb_turn_right(self, father);
                break;
            }
            else if (brother->right != NULL && brother->right->color == RBT_RED)
            {
                // case3
                brother->color = RBT_RED;
                brother->right->color = RBT_BLACK;
                tmp = tree_rb_turn_left(self, brother);
                // convert to case2
            }
            else
            {
                if (father->color == RBT_BLACK)
                {
                    // case4
                    brother->color = RBT_RED;
                    node = father;
                }
                else
                {
                    // case5
                    brother->color = RBT_RED;
                    father->color = RBT_BLACK;
                    break;
                }
            }
        }

        if (tmp != NULL && tmp->parent == NULL)
        {
            self->_root = tmp;
        }
    }

    if (node->parent == NULL)
    {
        self->_root = node;
    }
    self->_root->color = RBT_BLACK;
    return true;
}

static bool tree_rb_delete(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    if (self->empty(self))
    {
        return false;
    }

    struct _tree_node* node = tree_find(self, obj);
    if (node == NULL)
    {
        return false;
    }

    struct _tree_node* tmp = NULL;
    if (node->left == NULL && node->right == NULL)
    {
        tmp = node;
    }
    else if (node->left != NULL && node->right == NULL)
    {
        // node->left must be red
        tmp = node->left;
        memmove(node->obj, tmp->obj, self->_obj_size);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        // node->right must be red
        tmp = node->right;
        memmove(node->obj, tmp->obj, self->_obj_size);
    }
    else
    {
        // 1. find the min node in right subtree
        // 2. replace the node with min node
        // 3. delete the min node
        tmp = tree_find_min(self, node->right);
        memmove(node->obj, tmp->obj, self->_obj_size);
        if (tmp->right != NULL)
        {
            // tmp->right must be red
            memmove(tmp->obj, tmp->right->obj, self->_obj_size);
            tmp = tmp->right;
        }
    }

    if (tmp->color == RBT_BLACK)
    {
        tree_rb_delete_fix(self, tmp);
    }

    if (tmp->parent != NULL)
    {
        if (tmp->parent->left == tmp)
        {
            tmp->parent->left = NULL;
        }
        else
        {
            tmp->parent->right = NULL;
        }
    }
    else
    {
        self->_root = NULL;
    }

    tree_node_free(&tmp);
    self->_size--;
    return true;
}

static uint32_t tree_height(struct _tree* self)
{
    return tree_height_node(self, self->_root);
}

static bool tree_iter_hasnext(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    tree_t self = (tree_t)iter->_container;
    if(iter->_index < self->size(self))
    {
        return true;
    }
    return false;
}

static const void* tree_iter_next(struct _iterator* iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    tree_t self = (tree_t)iter->_container;
    void *obj = NULL;

    struct _tree_node* cur_node = iter->_node;
    struct _tree_node* target_node = NULL;
    switch (iter->_order)
    {
    case ORDER_PRE:
    case ORDER_PRE_R:
    {
        struct _tree_node* node = NULL;
        if (iter->_order == ORDER_PRE)
        {
            while (!self->stack->empty(self->stack) || cur_node != NULL)
            {
                if (cur_node != NULL)
                {
                    target_node = cur_node;

                    self->stack->push(self->stack, &cur_node);
                    cur_node = cur_node->left;
                    break;
                }
                else
                {
                    self->stack->pop(self->stack, &cur_node);
                    cur_node = cur_node->right;
                }
            }
        }
        else
        {
            while (!self->stack->empty(self->stack) || cur_node != NULL)
            {
                if (cur_node != NULL)
                {
                    target_node = cur_node;

                    self->stack->push(self->stack, &cur_node);
                    cur_node = cur_node->right;
                    break;
                }
                else
                {
                    self->stack->pop(self->stack, &cur_node);
                    cur_node = cur_node->left;
                }
            }
        }
    }break;
    case ORDER_IN:
    case ORDER_IN_R:
    {
        if (iter->_order == ORDER_IN)
        {
            while (!self->stack->empty(self->stack) || cur_node != NULL)
            {
                if (cur_node != NULL)
                {
                    self->stack->push(self->stack, &cur_node);
                    cur_node = cur_node->left;
                }
                else
                {
                    self->stack->pop(self->stack, &cur_node);
                    target_node = cur_node;

                    cur_node = cur_node->right;
                    break;
                }
            }
        }
        else
        {
            while (!self->stack->empty(self->stack) || cur_node != NULL)
            {
                if (cur_node != NULL)
                {
                    self->stack->push(self->stack, &cur_node);
                    cur_node = cur_node->right;
                }
                else
                {
                    self->stack->pop(self->stack, &cur_node);
                    target_node = cur_node;

                    cur_node = cur_node->left;
                    break;
                }
            }
        }
    }break;
    case ORDER_POST:
    case ORDER_POST_R:
    {
        if (!self->stack->empty(self->stack))
        {
            self->stack->pop(self->stack, &cur_node);
            target_node = cur_node;
        }
    }break;
    case ORDER_BREADTH:
    case ORDER_BREADTH_R:
    {
        queue_t queue = self->queue;
        if (!queue->empty(queue) && cur_node != NULL)
        {
            queue->pop(queue, &cur_node);
            target_node = cur_node;

            if (iter->_order == ORDER_BREADTH)
            {
                if (cur_node->left != NULL)
                {
                    queue->push(queue, &cur_node->left);
                }
                if (cur_node->right != NULL)
                {
                    queue->push(queue, &cur_node->right);
                }
            }
            else
            {
                if (cur_node->right != NULL)
                {
                    queue->push(queue, &cur_node->right);
                }
                if (cur_node->left != NULL)
                {
                    queue->push(queue, &cur_node->left);
                }
            }
        }
    }break;
    default:
    {
    }break;
    }

    iter->_node = cur_node;
    obj = target_node->obj;
    iter->_index += 1;
    return obj;
}


static iterator_t tree_iter(struct _tree* self, enum _tree_order order)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_container = self;
    iter->_index = 0;
    iter->_node = self->_root;
    iter->_order = order;
    iter->hasnext = tree_iter_hasnext;
    iter->next = tree_iter_next;
    
    self->stack->clear(self->stack);
    self->queue->clear(self->queue);

    switch (iter->_order)
    {
    case ORDER_PRE:
    case ORDER_PRE_R:
    {
        // pass
    }break;
    case ORDER_IN:
    case ORDER_IN_R:
    {
        // pass
    }break;
    case ORDER_POST:
    case ORDER_POST_R:
    {
        struct _tree_node* node = self->_root;
        self->stack->clear(self->stack);

        stack_t stack = stack_new(sizeof(struct _tree_node*));
        if (iter->_order == ORDER_POST)
        {
            while (!stack->empty(stack) || node != NULL)
            {
                if (node != NULL)
                {
                    self->stack->push(self->stack, &node);

                    stack->push(stack, &node);
                    node = node->right;
                }
                else
                {
                    stack->pop(stack, &node);
                    node = node->left;
                }
            }
        }
        else
        {
            while (!stack->empty(stack) || node != NULL)
            {
                if (node != NULL)
                {
                    self->stack->push(self->stack, &node);

                    stack->push(stack, &node);
                    node = node->left;
                }
                else
                {
                    stack->pop(stack, &node);
                    node = node->right;
                }
            }
        }
        stack_free(&stack);
    }break;
    case ORDER_BREADTH:
    case ORDER_BREADTH_R:
    {
        // pass
        self->queue->push(self->queue, &self->_root);
    }break;
    default:
    {
    }break;
    }

    return iter;
}

static bool tree_avl_init(struct _tree* self, uint32_t obj_size)
{
    assert(self != NULL);

    // -------------------- private -------------------- 
    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_root = NULL;

    self->stack = stack_new(sizeof(struct _tree_node*));
    if (self->stack == NULL)
    {
        return false;
    }
    self->queue = queue_new(sizeof(struct _tree_node*));
    if (self->queue == NULL)
    {
        stack_free(&self->stack);
        return false;
    }

    self->_rebalance = tree_avl_rebalance;
    self->_destory = tree_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = tree_avl_insert;
    self->delete = tree_avl_delete;
    self->height = tree_height;

    // base
    self->clear = tree_clear;
    self->empty = tree_empty;
    self->size = tree_size;
    
    // iter
    self->iter = tree_iter;

    // others
    self->max = tree_max;
    self->min = tree_min;

    return true;
}

static bool tree_rb_init(struct _tree* self, uint32_t obj_size)
{
    assert(self != NULL);

    // -------------------- private -------------------- 
    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_root = NULL;

    self->stack = stack_new(sizeof(struct _tree_node*));
    if (self->stack == NULL)
    {
        return false;
    }
    self->queue = queue_new(sizeof(struct _tree_node*));
    if (self->queue == NULL)
    {
        stack_free(&self->stack);
        return false;
    }

    self->_rebalance = tree_rb_rebalance;
    self->_destory = tree_destory;

    // -------------------- public --------------------
    // kernel
    self->insert = tree_rb_insert;
    self->delete = tree_rb_delete;
    self->height = tree_height;

    // base
    self->clear = tree_clear;
    self->empty = tree_empty;
    self->size = tree_size;

    // iter
    self->iter = tree_iter;

    // others
    self->max = tree_max;
    self->min = tree_min;

    return true;
}

tree_t tree_avl_new(uint32_t obj_size)
{
    tree_t tree = NULL;
    tree = (struct _tree*)malloc(sizeof(struct _tree));
    if(tree == NULL)
    {
        return NULL;
    }

    if(tree_avl_init(tree, obj_size) != true)
    {
        free(tree);
        return NULL;
    }
    return tree;
}

tree_t tree_rb_new(uint32_t obj_size)
{
    tree_t tree = NULL;
    tree = (struct _tree*)malloc(sizeof(struct _tree));
    if(tree == NULL)
    {
        return NULL;
    }

    if(tree_rb_init(tree, obj_size) != true)
    {
        free(tree);
        return NULL;
    }
    return tree;
}

void tree_free(tree_t* tree)
{
    if (*tree != NULL)
    {
        (*tree)->_destory(*tree);
        free(*tree);
    }
    *tree = NULL;
}
