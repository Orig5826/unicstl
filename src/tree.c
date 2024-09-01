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

static void tree_set_balance(struct _tree* self, struct _tree_node * node)
{
    assert(self != NULL);
    if(node == NULL)
    {
        return;
    }
    node->balance = self->height(self, node->right) - self->height(self, node->left);
}

static struct _tree_node* tree_turn_left(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    assert(root != NULL);
    struct _tree_node* node = root->right;
    if(node == NULL)
    {
        return root;
    }

    if(root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if(root->parent->left == root) 
        {
            root->parent->left = node;          // step1
        }
        else if(root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->right = node->left;           // step4
    if(node->left != NULL)
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
    if(node == NULL)
    {
        return root;
    }

    if(root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if(root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if(root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->left = node->right;           // step4
    if(node->right != NULL)
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
    if(node != NULL)
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
    if(node != NULL)
    {
        tree_turn_right(self, node);
    }
    node = tree_turn_left(self, root);
    return node;
}

int32_t tree_height(struct _tree* self, struct _tree_node* root)
{
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return 0;
    }
    int32_t left_height = tree_height(self, root->left);
    int32_t right_height = tree_height(self, root->right);
    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
#else
    assert(self != NULL);
    if(root == NULL)
    {
        return 0;
    }
    int32_t height = 0;
    int32_t count_cur_level = 0;
    int32_t count_next_level = 0;

    struct _tree_node* node = root;
    queue_t queue = queue_new();
    queue_init(queue, sizeof(struct _tree_node*));

    queue->push(queue, &node);
    while(!queue->empty(queue))
    {
        queue->pop(queue, &node);
        if(node->left != NULL)
        {
            queue->push(queue, &node->left);
        }
        if(node->right != NULL)
        {
            queue->push(queue, &node->right);
        }

        if(count_cur_level == count_next_level)
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
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return false;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return false;
    }

    // self->print_obj(root->obj);
    tree_set_balance(self, root);
    int balance = root->balance;
    if(balance == 2)
    {
        if(root->right->balance >= 0)
        {
            root = tree_turn_left(self, root);
        }
        else
        {
            root = tree_turn_right_then_left(self, root);
        }
    }
    else if(balance == -2)
    {
        if(root->left->balance <= 0)
        {
            root = tree_turn_right(self, root);
        }
        else
        {
            root = tree_turn_left_then_right(self, root);
        }
    }
    
    if(root->parent != NULL)
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
    if(root == NULL)
    {
        return false;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return false;
    }
    int balance = 0;

    do
    {
        tree_set_balance(self, root);
        balance = root->balance;
        if(balance == 2)
        {
            if(root->right->balance >= 0)
            {
                root = tree_turn_left(self, root);
            }
            else
            {
                root = tree_turn_right_then_left(self, root);
            }
        }
        else if(balance == -2)
        {
            if(root->left->balance <= 0)
            {
                root = tree_turn_right(self, root);
            }
            else
            {
                root = tree_turn_left_then_right(self, root);
            }
        }

        // if node become the new root
        if(root->parent == NULL)
        {
            break;
        }
        root = root->parent;
    }while(root != NULL);
    
    self->_root = root;
    return true;
#endif
}

static struct _tree_node * tree_node_new(struct _tree* self, void* obj)
{
    assert(self != NULL);

    void * obj_new = malloc(self->_obj_size);
    if (obj_new == NULL)
    {
        goto done;
    }
    memmove(obj_new, obj, self->_obj_size);

    struct _tree_node* node_new = (struct _tree_node*)malloc(sizeof(struct _tree_node));
    if(node_new == NULL)
    {
        goto done;
    }
    node_new->obj = obj_new;
    node_new->parent = NULL;
    node_new->left = NULL;
    node_new->right = NULL;
    node_new->balance = 0;

    return node_new;
done:
    if(obj_new != NULL)
    {
        free(obj_new);
    }
    if(node_new != NULL)
    {
        free(node_new);
    }
    return NULL;
}

static bool tree_node_free(struct _tree_node* node)
{
    if(node != NULL)
    {
        if(node->obj != NULL)
        {
            free(node->obj);
        }
        free(node);
    }
    return true;
}

/**
 * @brief find the position to insert or find object
 * 
 * @param self 
 * @param obj
 */
struct _tree_node * tree_find_pos(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(self->compare != NULL);

    struct _tree_node* root = self->_root;
    while(root != NULL)
    {
        if(self->compare(obj, root->obj) == 0)
        {
            break;
        }
        else if(self->compare(obj, root->obj) < 0)
        {
            if(root->left == NULL)
            {
                break;
            }
            root = root->left;
        }
        else
        {
            if(root->right == NULL)
            {
                break;
            }
            root = root->right;
        }
    }
    return root;
}


bool tree_avl_insert(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    struct _tree_node* node = tree_node_new(self, obj);
    if(node == NULL)
    {
        return false;
    }

    // if no root
    if(self->_root == NULL)
    {
        self->_root = node;
    }
    else
    {
        // insert the node
        struct _tree_node* root = tree_find_pos(self, obj);
        if(self->compare(obj, root->obj) < 0)
        {
            root->left = node;
            node->parent = root;
        }
        else if(self->compare(obj, root->obj) > 0)
        {
            root->right = node;
            node->parent = root;
        }
        else
        {
            // if obj exist, just return false
            tree_node_free(node);
            return false;
        }

        self->rebalance(self, root);
    }
    self->_size++;
    return true;
}

static bool tree_avl_delete_single_child(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    assert(node != NULL);

    if(node->parent == NULL)
    {
        if(node->left != NULL)
        {
            node->left->parent = node->parent;      // step1 : NULL for root
            self->_root = node->left;               // step2
        }
        else if(node->right != NULL)
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
        if(node->parent->left == node)
        {
            if(node->left != NULL)
            {
                node->left->parent = node->parent;      // step1
                node->parent->left = node->left;        // step2
            }
            else if(node->right != NULL)
            {
                node->right->parent = node->parent;     // step1
                node->parent->left = node->right;       // step2
            }
            else
            {
                node->parent->left = NULL;
            }
        }
        else if(node->parent->right == node)
        {
            if(node->left != NULL)
            {
                node->left->parent = node->parent;      // step1
                node->parent->right = node->left;       // step2
            }
            else if(node->right != NULL)
            {
                node->right->parent = node->parent;     // step1
                node->parent->right = node->right;      // step2
            }
            else
            {
                node->parent->right = NULL;
            }
        }

        self->rebalance(self, node->parent);
    }
    tree_node_free(node);
    return true;
}

static bool tree_avl_delete_double_child(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    assert(node != NULL);
    struct _tree_node* tmp = self->find_min(self, node->right);
    if(tmp != NULL)
    {
        memmove(node->obj, tmp->obj, self->_obj_size);
        tree_avl_delete_single_child(self, tmp);
    }
    return true;
}

bool tree_avl_delete(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    if(self->empty(self))
    {
        return false;
    }

    struct _tree_node* node = self->find(self, obj);
    if(node == NULL)
    {
        return false;
    }

    if((node->left != NULL) && (node->right != NULL))
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

struct _tree_node * tree_find(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* root = self->_root;
    while(root != NULL)
    {
        if(self->compare(obj, root->obj) == 0)
        {
            return root;
        }
        else if(self->compare(obj, root->obj) < 0)
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

bool tree_clear(struct _tree* self)
{
    assert(self != NULL);
    if(self->_root == NULL)
    {
        return false;
    }

    struct _tree_node* node = self->_root;
    queue_t queue = queue_new();
    queue_init(queue, sizeof(struct _tree_node*));

    queue->push(queue, &node);
    while(!queue->empty(queue))
    {
        queue->pop(queue, &node);
        if(node->left != NULL)
        {
            queue->push(queue, &node->left);
        }
        if(node->right != NULL)
        {
            queue->push(queue, &node->right);
        }
        tree_node_free(node);
    }
    queue_free(&queue);
    self->_root = NULL;
    self->_size = 0;
    return true;
}

bool tree_empty(struct _tree* self)
{
    assert(self != NULL);
    return !self->size(self);
}

uint32_t tree_size(struct _tree* self)
{
    assert(self != NULL);
    return self->_size;
}

// free
void tree_destory(struct _tree* self)
{
    assert(self != NULL);
    self->clear(self);
    self->_root = NULL;

    if(self->stack != NULL)
    {
        stack_free(&self->stack);
    }
    if(self->queue != NULL)
    {
        queue_free(&self->queue);
    }
}

void tree_order(struct _tree* self, bool right_priority)
{
    assert(self != NULL);
    self->_right_priority = right_priority;
}

void tree_preorder(struct _tree* self, struct _tree_node* root)
{
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    if(!self->_right_priority)
    {
        self->print_obj(root->obj);
        if(root->left != NULL)
        {
            tree_preorder(self, root->left);
        }
        if(root->right != NULL)
        {
            tree_preorder(self, root->right);
        }
    }
    else
    {
        self->print_obj(root->obj);
        if(root->right != NULL)
        {
            tree_preorder(self, root->right);
        }
        if(root->left != NULL)
        {
            tree_preorder(self, root->left);
        }
    }
#else
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }
    struct _tree_node* node = root;

    stack_t stack = stack_new();
    stack_init(stack, sizeof(struct _tree_node*));

    if(!self->_right_priority)          // left priority
    {
        while(!stack->empty(stack) || node != NULL)
        {
            if(node != NULL)
            {
                self->print_obj(node->obj);

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
    else
    {
        while(!stack->empty(stack) || node != NULL)
        {
            if(node != NULL)
            {
                self->print_obj(node->obj);

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
    stack_free(&stack);
#endif
}

void tree_inorder(struct _tree* self, struct _tree_node* root)
{
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    if(!self->_right_priority)
    {
        if(root->left != NULL)
        {
            tree_inorder(self, root->left);
        }
        self->print_obj(root->obj);
        if(root->right != NULL)
        {
            tree_inorder(self, root->right);  
        }
    }
    else
    {
        if(root->right != NULL)
        {
            tree_inorder(self, root->right);
        }
        self->print_obj(root->obj);
        if(root->left != NULL)
        {
            tree_inorder(self, root->left);
        }
    }
#else
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    struct _tree_node *node = root;

    stack_t stack = stack_new();
    stack_init(stack, sizeof(struct _tree_node*));

    if(!self->_right_priority)         // left priority
    {
        while(!stack->empty(stack) || node != NULL)
        {
            if(node != NULL)
            {
                stack->push(stack, &node);
                node = node->left;
            }
            else
            {
                stack->pop(stack, &node);
                self->print_obj(node->obj);

                node = node->right;
            }
        }
    }
    else
    {
        while(node != NULL || !stack->empty(stack))
        {
            if(node != NULL)
            {
                stack->push(stack, &node);
                node = node->right;
            }
            else
            {
                stack->pop(stack, &node);
                self->print_obj(node->obj);

                node = node->left;
            }
        }
    }
    stack_free(&stack);
#endif
}

void tree_postorder(struct _tree* self, struct _tree_node* root)
{
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    if(!self->_right_priority)
    {
        if(root->left != NULL)
        {
            tree_postorder(self, root->left);
        }
        if(root->right != NULL)
        {
            tree_postorder(self, root->right);
        }
        self->print_obj(root->obj);
    }
    else
    {
        if(root->right != NULL)
        {
            tree_postorder(self, root->right);
        }
        if(root->left != NULL)
        {
            tree_postorder(self, root->left);
        }
        self->print_obj(root->obj);
    }
#else
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }
    struct _tree_node* node = root;

    stack_t stack2 = stack_new();
    stack_init(stack2, sizeof(struct _tree_node*));

    // because: left:postorder == right:the reverse of preorder 
    stack_t stack = stack_new();
    stack_init(stack, sizeof(struct _tree_node*));

    if(!self->_right_priority)          // left priority
    {
        while(!stack->empty(stack) || node != NULL)
        {
            if(node != NULL)
            {
                stack2->push(stack2, &node);

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
        while(!stack->empty(stack) || node != NULL)
        {
            if(node != NULL)
            {
                stack2->push(stack2, &node);

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

    while(!stack2->empty(stack2))
    {
        stack2->pop(stack2, &node);
        self->print_obj(node->obj);
    }

    stack_free(&stack);
    stack_free(&stack2);
#endif
}

// traversal breadth
void tree_breadth(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    struct _tree_node* node = root;
    queue_t queue = queue_new();
    queue_init(queue, sizeof(struct _tree_node*));

    if(node != NULL)
    {
        queue->push(queue, &node);
        while(!queue->empty(queue))
        {
            queue->pop(queue, &node);
            if(!self->_right_priority)
            {
                if(node->left != NULL)
                {
                    queue->push(queue, &node->left);
                }
                if(node->right != NULL)
                {
                    queue->push(queue, &node->right);
                }
            }
            else
            {
                if(node->right != NULL)
                {
                    queue->push(queue, &node->right);
                }
                if(node->left != NULL)
                {
                    queue->push(queue, &node->left);
                }
            }
            self->print_obj(node->obj);
        }
    }
    queue_free(&queue);
}

static struct _tree_node* tree_find_min(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
#if 0
    if(root == NULL)
    {
        return NULL;
    }
    if(root->left == NULL)
    {
        return root;
    }
    return tree_find_min(self, root->left);
#else
    while(root != NULL)
    {
        if(root->left != NULL)
        {
            root = root->left;
        }
        else
        {
            return root;
        }
    }
    return root;
#endif
}

static struct _tree_node* tree_find_max(struct _tree* self, struct _tree_node* root)
{
#if 0
    assert(self != NULL);
    if(root == NULL)
    {
        return NULL;
    }
    if(root->right == NULL)
    {
        return root;
    }
    return tree_find_max(self, root->right);
#else
    while(root != NULL)
    {
        if(root->right != NULL)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return root;
#endif
}

bool tree_min(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* node = tree_find_min(self, self->_root);
    if(node == NULL)
    {
        return false;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}

bool tree_max(struct _tree* self, void* obj)
{
    assert(self != NULL);
    struct _tree_node* node = tree_find_max(self, self->_root);
    if(node == NULL)
    {
        return false;
    }
    memmove(obj, node->obj, self->_obj_size);
    return true;
}



rbt_color tree_color(struct _tree_node* node)
{
    assert(node != NULL);
    return node->color;
}

bool tree_set_color(struct _tree_node* node, rbt_color color)
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
    if(node == NULL)
    {
        return root;
    }

    if(root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if(root->parent->left == root) 
        {
            root->parent->left = node;          // step1
        }
        else if(root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->right = node->left;           // step4
    if(node->left != NULL)
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
    if(node == NULL)
    {
        return root;
    }

    if(root->parent == NULL)
    {
        self->_root = node;                     // step1
    }
    else
    {
        if(root->parent->left == root)
        {
            root->parent->left = node;          // step1
        }
        else if(root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->left = node->right;           // step4
    if(node->right != NULL)
    {
        node->right->parent = root;     // step5
    }
    node->right = root;                 // step6
    return node;
}

bool tree_rb_insert(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    struct _tree_node* node = tree_node_new(self, obj);
    if(node == NULL)
    {
        return false;
    }

    // if no root
    if(self->_root == NULL)
    {
        self->_root = node;
    }
    else
    {
        // insert the node
        struct _tree_node* root = tree_find_pos(self, obj);
        if(self->compare(obj, root->obj) < 0)
        {
            root->left = node;
            node->parent = root;
        }
        else if(self->compare(obj, root->obj) > 0)
        {
            root->right = node;
            node->parent = root;
        }
        else
        {
            // if obj exist, just return false
            tree_node_free(node);
            return false;
        }

    }

    self->rebalance(self, node);
    
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
    if(node == NULL)
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
    while(node->parent != NULL && node->parent->color == RBT_RED)
    {
        father = node->parent;
        grandfather = father->parent;
        if(father == grandfather->left)
        {
            uncle = grandfather->right;
            if(uncle != NULL && uncle->color == RBT_RED)        // uncle is red
            {
                father->color = RBT_BLACK;
                uncle->color = RBT_BLACK;
                grandfather->color = RBT_RED;
                node = grandfather;
            }
            else                                                // uncle is black
            {
                if(node == father->right)
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
            if(uncle != NULL && uncle->color == RBT_RED)        // uncle is red
            {
                father->color = RBT_BLACK;
                uncle->color = RBT_BLACK;
                grandfather->color = RBT_RED;
                node = grandfather;
            }
            else                                                // uncle is black
            {
                if(node == father->left)
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

    if(node->parent == NULL)
    {
        self->_root = node;
        node->color = RBT_BLACK;
    }
    return true;
}

bool tree_rb_delete_fix(struct _tree* self, struct _tree_node* node)
{
    assert(self != NULL);
    struct _tree_node* father = NULL;
    struct _tree_node* brother = NULL;
    struct _tree_node* tmp = NULL;
    if(node == NULL)
    {
        return false;
    }

    // the color of node is black
    while(node->parent != NULL && node->color == RBT_BLACK)
    {
        father = node->parent;
        if(father->left == node)
        {
            brother = father->right;
            if(brother->color == RBT_RED)
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
            else if(brother->right != NULL && brother->right->color == RBT_RED)
            {
                // case 2
                brother->color = father->color;
                father->color = RBT_BLACK;
                brother->right->color = RBT_BLACK;
                node = tree_rb_turn_left(self, father);
                // After deleting the node, it remains balanced
                break;
            }
            else if(brother->left != NULL && brother->left->color == RBT_RED)
            {
                // case 3
                brother->color = RBT_RED;
                brother->left->color = RBT_BLACK;
                tmp = tree_rb_turn_right(self, brother);
                // Convert to case2
            }
            else
            {
                if(father->color == RBT_BLACK)
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
            if(brother->color == RBT_RED)
            {
                // case1
                brother->color = RBT_BLACK;
                father->color = RBT_RED;
                tmp = tree_rb_turn_right(self, father);
            }
            else if(brother->left != NULL && brother->left->color == RBT_RED)
            {
                // case2
                brother->color = father->color;
                father->color = RBT_BLACK;
                brother->left->color = RBT_BLACK;
                node = tree_rb_turn_right(self, father);
                break;
            }
            else if(brother->right != NULL && brother->right->color == RBT_RED)
            {
                // case3
                brother->color = RBT_RED;
                brother->right->color = RBT_BLACK;
                tmp = tree_rb_turn_left(self, brother);
                // convert to case2
            }
            else
            {
                if(father->color == RBT_BLACK)
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

        if(tmp != NULL && tmp->parent == NULL)
        {
            self->_root = tmp;
        }
    }
    
    if(node->parent == NULL)
    {
        self->_root = node;
    }
    self->_root->color = RBT_BLACK;
    return true;
}

bool tree_rb_delete(struct _tree* self, void* obj)
{
    assert(self != NULL);
    assert(obj != NULL);
    assert(self->compare != NULL);

    if(self->empty(self))
    {
        return false;
    }

    struct _tree_node* node = self->find(self, obj);
    if(node == NULL)
    {
        return false;
    }

    struct _tree_node* tmp = NULL;
    if(node->left == NULL && node->right == NULL)
    {
        tmp = node;
    }
    else if(node->left != NULL && node->right == NULL)
    {
        // node->left must be red
        tmp = node->left;
        memmove(node->obj,tmp->obj, self->_obj_size);
    }
    else if(node->left == NULL && node->right != NULL)
    {
        // node->right must be red
        tmp = node->right;
        memmove(node->obj,tmp->obj, self->_obj_size);
    }
    else
    {
        // 1. find the min node in right subtree
        // 2. replace the node with min node
        // 3. delete the min node
        tmp = self->find_min(self, node->right);
        memmove(node->obj, tmp->obj, self->_obj_size);
        if(tmp->right != NULL)
        {
            // tmp->right must be red
            memmove(tmp->obj, tmp->right->obj, self->_obj_size);
            tmp = tmp->right;
        }
    }

    if(tmp->color == RBT_BLACK)
    {
        tree_rb_delete_fix(self, tmp);
    }

    if(tmp->parent != NULL)
    {
        if(tmp->parent->left == tmp)
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

    tree_node_free(tmp);
    self->_size--;
    return true;
}

void tree_set_order(struct _tree* self, enum _order order)
{
    assert(self != NULL);
    self->_order = order;
}

void* tree_begin(struct _tree* self)
{
    assert(self != NULL);
    switch (self->_order)
    {
    case ORDER_LEFT_PRE:
    {
        struct _tree_node* node = NULL;
        self->cur_node = self->_root;

        self->stack->clear(self->stack);
        node = self->cur_node;
        self->stack->push(self->stack, &self->cur_node);
        return node->obj;
    }break;
    case ORDER_LEFT_IN:
    {

    }break;
    case ORDER_LEFT_POST:
    {

    }break;
    case ORDER_LEFT_BREADTH:
    {

    }break;
    case ORDER_RIGHT_PRE:
    {

    }break;
    case ORDER_RIGHT_IN:
    {

    }break;
    case ORDER_RIGHT_POST:
    {

    }break;
    case ORDER_RIGHT_BREADTH:
    {

    }break;
    default:
    {
    }break;
    }
}

void* tree_next(struct _tree* self)
{
    assert(self != NULL);
    switch (self->_order)
    {
    case ORDER_LEFT_PRE:
    {
        struct _tree_node* node = NULL;
        while(!self->stack->empty(self->stack) || self->cur_node != NULL)
        {
            if(self->cur_node != NULL)
            {
                node = self->cur_node;
                self->stack->push(self->stack, &self->cur_node);
            }
            else
            {
                self->stack->pop(self->stack, &self->cur_node);
                self->cur_node = self->cur_node->right;
            }
        }
        return node->obj;
    }break;
    case ORDER_LEFT_IN:
    {

    }break;
    case ORDER_LEFT_POST:
    {

    }break;
    case ORDER_LEFT_BREADTH:
    {

    }break;
    case ORDER_RIGHT_PRE:
    {

    }break;
    case ORDER_RIGHT_IN:
    {

    }break;
    case ORDER_RIGHT_POST:
    {

    }break;
    case ORDER_RIGHT_BREADTH:
    {

    }break;
    default:
    {
    }break;
    }
}

void* tree_end(struct _tree* self)
{
    assert(self != NULL);
    switch (self->_order)
    {
    case ORDER_LEFT_PRE:
    {
        return NULL;
    }break;
    case ORDER_LEFT_IN:
    {

    }break;
    case ORDER_LEFT_POST:
    {

    }break;
    case ORDER_LEFT_BREADTH:
    {

    }break;
    case ORDER_RIGHT_PRE:
    {

    }break;
    case ORDER_RIGHT_IN:
    {

    }break;
    case ORDER_RIGHT_POST:
    {

    }break;
    case ORDER_RIGHT_BREADTH:
    {

    }break;
    default:
    {
    }break;
    }
}



bool tree_avl_init(struct _tree *self, uint32_t obj_size)
{
    assert(self != NULL);

    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_right_priority = false;
    self->_order = ORDER_PRE;

    self->insert = tree_avl_insert;
    self->delete = tree_avl_delete;
    self->clear = tree_clear;
    self->empty = tree_empty;
    self->size = tree_size;
    self->destory = tree_destory;
    self->preorder = tree_preorder;
    self->inorder = tree_inorder;
    self->postorder = tree_postorder;
    self->breadth = tree_breadth;
    self->order = tree_order;
    self->find = tree_find;
    self->height = tree_height;
    self->rebalance = tree_avl_rebalance;
    self->find_max = tree_find_max;
    self->find_min = tree_find_min;
    self->max = tree_max;
    self->min = tree_min;

    self->set_order = tree_set_order;
    self->begin = tree_begin;
    self->next = tree_next;
    self->end = tree_end;

    self->_root = NULL;

    self->stack = stack_new();
    if(self->stack == NULL)
    {
        goto done;
    }
    stack_init(self->stack, sizeof(struct _tree_node*));
    self->queue = queue_new();
    if(self->queue == NULL)
    {
        goto done1;
    }
    queue_init(self->queue, sizeof(struct _tree_node*));
    self->cur_node = NULL;

    return true;
done1:
    stack_free(&self->stack);
done:
    return false;

    return true;
}

bool tree_rb_init(struct _tree *self, uint32_t obj_size)
{
    assert(self != NULL);
    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_right_priority = false;
    self->_order = ORDER_PRE;

    self->insert = tree_rb_insert;
    self->delete = tree_rb_delete;
    self->rebalance = tree_rb_rebalance;
    
    self->clear = tree_clear;
    self->empty = tree_empty;
    self->size = tree_size;
    self->destory = tree_destory;
    self->preorder = tree_preorder;
    self->inorder = tree_inorder;
    self->postorder = tree_postorder;
    self->breadth = tree_breadth;
    self->order = tree_order;
    self->find = tree_find;
    self->height = tree_height;
    self->find_max = tree_find_max;
    self->find_min = tree_find_min;
    self->max = tree_max;
    self->min = tree_min;

    self->set_order = tree_set_order;
    self->begin = tree_begin;
    self->next = tree_next;
    self->end = tree_end;

    self->_root = NULL;

    self->stack = stack_new();
    if(self->stack == NULL)
    {
        goto done;
    }
    stack_init(self->stack, sizeof(struct _tree_node*));
    self->queue = queue_new();
    if(self->queue == NULL)
    {
        goto done1;
    }
    queue_init(self->queue, sizeof(struct _tree_node*));
    self->cur_node = NULL;

    return true;
done1:
    stack_free(&self->stack);
done:
    return false;
}

tree_t tree_new(void)
{
    return (struct _tree*)malloc(sizeof(struct _tree));
}

void tree_free(tree_t* tree)
{
    if(*tree != NULL)
    {
        (*tree)->destory(*tree);
        free(*tree);
    }
    *tree = NULL;
}
