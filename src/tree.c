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

#if RAVLTREE == 1
// function declare
static bool tree_rebalance(ptree_node_t tree);

bool tree_init(ptree_node_t *tree)
{
    *tree = (ptree_node_t)malloc(sizeof(tree_node_t));
    if(*tree == NULL)
    {
        return false;
    }
    // (*tree)->data = (tree_data_t)0;		// the data of header is invalid
    (*tree)->left = *tree;			// The left subtree of the header node of the tree points to itself
    (*tree)->right = NULL;			// The right subtree of the header node of the tree points to the root
    (*tree)->parent = NULL;			// Invalid, because this is the pointer of tree header
    (*tree)->balance = 0;			// balance of avl tree
    return true;
}

void tree_destroy(ptree_node_t *tree)
{
    if(*tree != NULL)
    {
        tree_clear(*tree);
        free(*tree);
        *tree = NULL;
    }
}

bool tree_empty(ptree_node_t tree)
{
    return ((tree == NULL) || (tree->left == tree) && (tree->right == NULL)) ? true : false;
}

void tree_clear(ptree_node_t tree)
{
    // the header of tree pointer
    if(tree != NULL && tree->left == tree)
    {
        tree_clear(tree->right);
        free(tree->right);
        tree->right = NULL;
        return;
    }

    if(!tree_empty(tree))
    {
        if(tree->left != NULL)
        {
            tree_clear(tree->left);
            free(tree->left);
            tree->left = NULL;
        }

        if(tree->right != NULL)
        {
            tree_clear(tree->right);
            free(tree->right);
            tree->right = NULL;
        }
    }
}

static ptree_node_t tree_find(ptree_node_t tree, tree_data_t data)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_find(tree->right,data);
    }

    if(tree == NULL)
    {
        return NULL;
    }

    if(tree->data == data)
    {
        return tree;
    }

    if(data < tree->data)
    {
        if(tree->left != NULL)
        {
            return tree_find(tree->left,data);
        }
        else
        {
            return tree;
        }
    }

    if(data > tree->data)
    {
        if(tree->right != NULL)
        {
            return tree_find(tree->right,data);
        }
        else
        {
            return tree;
        }
    }
    
    // invalid
    return NULL;
}

bool tree_insert(ptree_node_t tree, tree_data_t data)
{
    ptree_node_t tree_node;
    if (tree == NULL)
    {
        return false;
    }

    // the header of tree pointer
    if(tree != NULL && tree->left == tree)
    {
        if (tree->right == NULL)
        {
            ptree_node_t new_item = (ptree_node_t)malloc(sizeof(tree_node_t));
            if (new_item == NULL)
            {
                return false;
            }
            new_item->data = data;
            new_item->left = NULL;
            new_item->right = NULL;
            // new_item->parent = NULL;	// root no parent
            new_item->parent = tree;	// the parent of root is header of tree
            new_item->balance = 0;		// balance of avl tree

            tree->right = new_item;
            return true;
        }
        else
        {
            return tree_insert(tree->right, data);
        }
    }

    tree_node = tree_find(tree,data);
    if(data < tree_node->data)
    {
        ptree_node_t new_item = (ptree_node_t)malloc(sizeof(tree_node_t));
        if(new_item == NULL)
        {
            return false;
        }
        new_item->data = data;
        new_item->left = NULL;
        new_item->right = NULL;
        new_item->parent = tree_node;
        new_item->balance = 0;	// balance of avl tree
        
        tree_node->left = new_item;
        // avl tree rebalance
        tree_rebalance(tree_node);
    }
    else
    {
        ptree_node_t new_item = (ptree_node_t)malloc(sizeof(tree_node_t));
        if(new_item == NULL)
        {
            return false;
        }
        new_item->data = data;
        new_item->left = NULL;
        new_item->right = NULL;
        new_item->parent = tree_node;
        new_item->balance = 0;	// balance of avl tree
        
        tree_node->right = new_item;

        // avl tree rebalance
        tree_rebalance(tree_node);
    }
    return true;
}

static ptree_node_t tree_get_node_min(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_get_node_min(tree->right);
    }

    if(tree != NULL)
    {
        if(tree->left != NULL)
        {
            return tree_get_node_min(tree->left);
        }
        else
        {
            return tree;
        }
    }
    else
    {
        return NULL;
    }
}

static void tree_delete_single_child(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        tree_delete_single_child(tree->right);
        return ;
    }

    if(tree != NULL)
    {
        // becaue the parent of root is header of tree
        // if(tree->parent == NULL)
        if(tree->parent->parent == NULL)
        {
            // delete the root of tree
            if(tree->left == NULL)
            {
                tree->parent->right = tree->right;
                if(tree->right != NULL)
                {
                    tree->right->parent = tree->parent;
                }
            }
            else
            {
                tree->parent->right = tree->left;
                tree->left->parent = tree->parent;
            }
        }
        else
        {
            // delete other node of tree
            if(tree->parent->left == tree)
            {
                // left subtree
                if(tree->left == NULL)
                {
                    tree->parent->left = tree->right;
                    if(tree->right != NULL)
                    {
                        tree->right->parent = tree->parent;
                    }
                }
                else
                {
                    tree->parent->left = tree->left;
                    tree->left->parent = tree->parent;
                }
            }
            else
            {
                // rigth subtree
                if(tree->left == NULL)
                {
                    tree->parent->right = tree->right;
                    if(tree->right != NULL)
                    {
                        tree->right->parent = tree->parent;
                    }
                }
                else
                {
                    tree->parent->right = tree->left;
                    tree->left->parent = tree->parent;
                }
            }

            // avl tree rebalance
            tree_rebalance(tree->parent);
        }
        free(tree);
    }
}

static void tree_delete_double_child(ptree_node_t tree)
{
    // I think this idea is great!
    ptree_node_t t = tree_get_node_min(tree->right);
    if(t != NULL)
    {
        tree->data = t->data;
        tree_delete_single_child(t);
    }
}

bool tree_delete(ptree_node_t tree, tree_data_t data)
{
    ptree_node_t tree_node;
    if (tree == NULL)
    {
        return false;
    }

    if (tree != NULL && tree->left == tree)
    {
        return tree_delete(tree->right, data);
    }

    tree_node = tree_find(tree,data);
    if(tree_node->data == data)
    {
        if((tree_node->left != NULL) && (tree_node->right != NULL))
        {
            tree_delete_double_child(tree_node);
        }
        else
        {
            tree_delete_single_child(tree_node);
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool tree_get_min(ptree_node_t tree, tree_data_t *data)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_get_min(tree->right, data);
    }

    if(tree != NULL)
    {
        if(tree->left != NULL)
        {
            return tree_get_min(tree->left, data);
        }
        else
        {
            *data = tree->data;
            return true;
        }
    }
    else
    {
        return false;
    }
    
    // invalid but compile prevention warning
    return true;
}

bool tree_get_max(ptree_node_t tree, tree_data_t *data)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_get_max(tree->right, data);
    }

    if(tree != NULL)
    {
        if(tree->right != NULL)
        {
            return tree_get_max(tree->right, data);
        }
        else
        {
            *data = tree->data;
            return true;
        }
    }
    else
    {
        return false;
    }

    // invalid but compile prevention warning
    return true;
}

void tree_traversal_depth_preorder(ptree_node_t tree, tree_data_disp_t tree_data_disp)
{
    if (tree != NULL && tree->left == tree)
    {
        tree_traversal_depth_preorder(tree->right, tree_data_disp);
        return;
    }

    if (tree != NULL)
    {
        tree_data_disp(tree->data);
        tree_traversal_depth_preorder(tree->left, tree_data_disp);
        tree_traversal_depth_preorder(tree->right, tree_data_disp);
    }
}

void tree_traversal_depth_inorder(ptree_node_t tree, tree_data_disp_t tree_data_disp)
{
    if (tree != NULL && tree->left == tree)
    {
        tree_traversal_depth_inorder(tree->right, tree_data_disp);
        return;
    }

    if (tree != NULL)
    {
        tree_traversal_depth_inorder(tree->left, tree_data_disp);
        tree_data_disp(tree->data);
        tree_traversal_depth_inorder(tree->right, tree_data_disp);
    }
}

void tree_traversal_depth_postorder(ptree_node_t tree, tree_data_disp_t tree_data_disp)
{
    
}

void tree_traversal_breadth(ptree_node_t tree, tree_data_disp_t tree_data_disp)
{
    
}


// --------------- AVL ----------------------
static int32_t tree_get_height(ptree_node_t tree)
{
    int32_t left_height;
    int32_t right_height;
    if (tree != NULL && tree->left == tree)
    {
        return tree_get_height(tree->right);
    }
    if(tree == NULL)
    {
        return 0;
    }
    left_height = tree_get_height(tree->left);
    right_height = tree_get_height(tree->right);
    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
}

static void tree_set_balance(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        tree_get_height(tree->right);
        return;
    }
    
    if(tree != NULL)
    {
        tree->balance = tree_get_height(tree->right) - tree_get_height(tree->left);
    }
}

static ptree_node_t tree_turn_left(ptree_node_t tree)
{
    ptree_node_t tree_node;
    if (tree != NULL && tree->left == tree)
    {
        return tree_turn_left(tree->right);
    }

    if(tree == NULL)
    {
        return NULL;
    }

    // tree -> original node[a]
    // tree_node -> original right subnode[b] of [a]
    tree_node = tree->right;

    // 1. replace the children of the parent node
    if(tree->parent->parent != NULL)
    {
        // not root
        if(tree->parent->left == tree)
        {
            tree->parent->left = tree_node;
        }
        else
        {
            tree->parent->right = tree_node;
        }
    }
    tree_node->parent = tree->parent;
    
    // 2. turn left
    tree->parent = tree_node;
    tree->right = tree_node->left;
    tree_node->left = tree;
    if(tree->right != NULL)
    {
        tree->right->parent = tree;
    }
    tree_set_balance(tree);
    tree_set_balance(tree_node);
    return tree_node;
}


static ptree_node_t tree_turn_right(ptree_node_t tree)
{
    ptree_node_t tree_node;
    if (tree != NULL && tree->left == tree)
    {
        return tree_turn_left(tree->right);
    }

    if(tree == NULL)
    {
        return NULL;
    }

    // tree -> original node[a]
    // tree_node -> original left subnode[b] of [a]
    tree_node = tree->left;
    
    // 1. replace the children of the parent node
    if(tree->parent->parent != NULL)
    {
        // not root
        if(tree->parent->left == tree)
        {
            tree->parent->left = tree_node;
        }
        else
        {
            tree->parent->right = tree_node;
        }
    }
    tree_node->parent = tree->parent;
    
    // 2. turn left
    tree->parent = tree_node;
    tree->left = tree_node->right;
    tree_node->right = tree;
    if(tree->left != NULL)
    {
        tree->left->parent = tree;
    }
    tree_set_balance(tree);
    tree_set_balance(tree_node);
    return tree_node;
}


static ptree_node_t tree_turn_left_then_right(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_turn_left(tree->right);
    }

    if(tree == NULL)
    {
        return NULL;
    }

    // first left then right
    tree->left = tree_turn_left(tree->left);
    return tree_turn_right(tree);
}


static ptree_node_t tree_turn_right_then_left(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_turn_left(tree->right);
    }

    if(tree == NULL)
    {
        return NULL;
    }

    // first left then right
    tree->right = tree_turn_right(tree->right);
    return tree_turn_left(tree);
}


bool tree_rebalance(ptree_node_t tree)
{
    if (tree != NULL && tree->left == tree)
    {
        return tree_rebalance(tree->right);
    }

    if(tree == NULL)
    {
        return false;
    }

    tree_set_balance(tree);
    // left is greater than right
    if(tree->balance == -2)
    {
        if(tree->left->balance <= 0)
        {
            // node-left-left
            tree = tree_turn_right(tree);
        }
        else
        {
            // node-left-rigt
            tree = tree_turn_left_then_right(tree);
        }
    }
    // right is greater than left
    else if(tree->balance == 2)
    {
        if(tree->right->balance >= 0)
        {
            // node-right-right
            tree = tree_turn_left(tree);
        }
        else
        {
            // node-right-left
            tree = tree_turn_right_then_left(tree);
        }
    }

    if(tree->parent->parent != NULL)
    {
        tree_rebalance(tree->parent);
    }
    else
    {
        tree->parent->right = tree;
    }
    
    return true;
}
#endif


#if AVLTREE == 1
#include "stack.h"
#include "queue.h"

// function declare
static bool tree_rebalance(ptree_t head, ptree_node_t tree);


bool tree_init(ptree_t *head)
{
    *head = (ptree_t)malloc(sizeof(tree_t));
    if(*head == NULL)
    {
        return false;
    }
    (*head)->tree = NULL;
    (*head)->size = 0;
    return true;
}

void tree_destroy(ptree_t * head)
{
    if(*head != NULL)
    {
        tree_clear(*head);
        free(*head);
        *head = NULL;
    }
}

bool tree_empty(ptree_t head)
{
    return ((head == NULL) || (head->tree == NULL)) ? true : false;
}

void tree_clear(ptree_t head)
{
    pqueue_t queue;
    ptree_node_t root;
    ptree_node_t tree_node;

    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }
    root = head->tree;
    
    queue_init(&queue);
    queue_in(queue,root);

    while(!queue_empty(queue))
    {
        queue_out(queue, &tree_node);
        if(tree_node->left != NULL)
        {
            queue_in(queue,tree_node->left);
        }
        if(tree_node->right != NULL)
        {
            queue_in(queue,tree_node->right);
        }
        
        free(tree_node);
        tree_node = NULL;
    }

    queue_destroy(&queue);

    head->tree = NULL;
    head->size = 0;
}

uint32_t tree_get_size(ptree_t head)
{
    return head->size;
}

static ptree_node_t tree_find(ptree_t head, tree_data_t data)
{
    ptree_node_t root;
    
    if((head == NULL) || head->tree == NULL)
    {
        return NULL;
    }
    root = head->tree;
    
    while(root != NULL)
    {
        if(data < root->data)
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
        else if(data > root->data)
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
        else
        {
            // ==
            return root;
        }
    }

    return root;
}

bool tree_insert(ptree_t head, tree_data_t data)
{
    ptree_node_t tree_node;
    ptree_node_t new_node;
    
    if(head == NULL)
    {
        return false;
    }
    
    // no root of tree
    if(head->tree == NULL)
    {
        new_node = (ptree_node_t)malloc(sizeof(tree_node_t));
        if (new_node == NULL)
        {
            return false;
        }
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;	// the parent of root is NULL
        new_node->balance = 0;		// balance of avl tree

        head->tree = new_node;
    }
    else
    {
        tree_node = tree_find(head,data);
        if(data < tree_node->data)
        {
            new_node = (ptree_node_t)malloc(sizeof(tree_node_t));
            if(new_node == NULL)
            {
                return false;
            }
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = tree_node;
            new_node->balance = 0;		// balance of avl tree
            
            tree_node->left = new_node;
            // avl tree rebalance
            tree_rebalance(head, tree_node);
        }
        else
        {
            new_node = (ptree_node_t)malloc(sizeof(tree_node_t));
            if(new_node == NULL)
            {
                return false;
            }
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = tree_node;
            new_node->balance = 0;		// balance of avl tree
            
            tree_node->right = new_node;

            // avl tree rebalance
            tree_rebalance(head, tree_node);
        }
    }

    if (head->size < _UI32_MAX)
    {
        head->size++;
    }
    return true;
}

static ptree_node_t tree_get_node_min(ptree_node_t tree)
{
    while(tree != NULL)
    {
        if(tree->left != NULL)
        {
            tree = tree->left;
        }
        else
        {
            return tree;
        }
    }
    return tree;
}

static void tree_delete_single_child(ptree_t head, ptree_node_t tree)
{
    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }

    if(tree == NULL)
    {
        return ;
    }

    if(tree->parent == NULL)
    {
        // delete the root of tree
        if(tree->left == NULL)
        {
            head->tree = tree->right;
            if(tree->right != NULL)
            {
                tree->right->parent = tree->parent;
            }
        }
        else
        {
            head->tree = tree->left;
            tree->left->parent = tree->parent;
        }
    }
    else
    {
        // delete other node of tree
        if(tree->parent->left == tree)
        {
            // left subtree
            if(tree->left == NULL)
            {
                tree->parent->left = tree->right;
                if(tree->right != NULL)
                {
                    tree->right->parent = tree->parent;
                }
            }
            else
            {
                tree->parent->left = tree->left;
                tree->left->parent = tree->parent;
            }
        }
        else
        {
            // rigth subtree
            if(tree->left == NULL)
            {
                tree->parent->right = tree->right;
                if(tree->right != NULL)
                {
                    tree->right->parent = tree->parent;
                }
            }
            else
            {
                tree->parent->right = tree->left;
                tree->left->parent = tree->parent;
            }
        }

        // avl tree rebalance
        tree_rebalance(head, tree->parent);
    }
    free(tree);
}

static void tree_delete_double_child(ptree_t head, ptree_node_t tree)
{
    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }

    // I think this idea is great!
    ptree_node_t tree_node = tree_get_node_min(tree->right);
    if(tree_node != NULL)
    {
        tree->data = tree_node->data;
        tree_delete_single_child(head, tree_node);
    }
}

bool tree_delete(ptree_t head, tree_data_t data)
{
    ptree_node_t tree_node;
    
    if((head == NULL) || head->tree == NULL)
    {
        return false;
    }

    tree_node = tree_find(head,data);
    if(tree_node == NULL)
    {
        return false;
    }
    
    if((tree_node->left != NULL) && (tree_node->right != NULL))
    {
        tree_delete_double_child(head, tree_node);
    }
    else
    {
        tree_delete_single_child(head, tree_node);
    }

    if(head->size > 0)
    {
        head->size--;
    }
    return true;
}

bool tree_get_min(ptree_t head, tree_data_t *data)
{
    ptree_node_t root;

    if((head == NULL) || head->tree == NULL)
    {
        return false;
    }
    root = head->tree;
    
    while(root != NULL)
    {
        if(root->left != NULL)
        {
            root = root->left;
        }
        else
        {
            *data = root->data;
            return true;
        }
    }
    return false;
}

bool tree_get_max(ptree_t head, tree_data_t *data)
{
    ptree_node_t root;
    if((head == NULL) || head->tree == NULL)
    {
        return false;
    }
    root = head->tree;

    while(root != NULL)
    {
        if(root->right != NULL)
        {
            root = root->right;
        }
        else
        {
            *data = root->data;
            return true;
        }
    }
    return false;
}

void tree_traversal_depth_preorder(ptree_t head, tree_data_disp_t tree_data_disp)
{
    pstack_t stack;
    ptree_node_t root;
    ptree_node_t tree_node;
    
    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }
    root = head->tree;

    stack_init(&stack);
    tree_node = root;
    while(!stack_empty(stack) || tree_node != NULL)
    {
        if (tree_node != NULL)
        {
            tree_data_disp(tree_node->data);

            stack_push(stack, tree_node);
            tree_node = tree_node->left;
        }
        else
        {
            stack_pop(stack, &tree_node);
            tree_node = tree_node->right;
        }
    }
    
    stack_destroy(&stack);
}

void tree_traversal_depth_inorder(ptree_t head, tree_data_disp_t tree_data_disp)
{
    pstack_t stack;
    ptree_node_t root;
    ptree_node_t tree_node;
    
    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }
    root = head->tree;
    
    stack_init(&stack);
    tree_node = root;
    while(!stack_empty(stack) || tree_node != NULL)
    {
        if (tree_node != NULL)
        {
            stack_push(stack, tree_node);
            tree_node = tree_node->left;
        }
        else
        {
            stack_pop(stack, &tree_node);
            tree_data_disp(tree_node->data);
            tree_node = tree_node->right;
        }
    }
    
    stack_destroy(&stack);
}

void tree_traversal_depth_postorder(ptree_t head, tree_data_disp_t tree_data_disp)
{
    pstack_t stack;
    pstack_t stack_disp;
    ptree_node_t root;
    ptree_node_t tree_node;

    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }
    root = head->tree;
    
    stack_init(&stack);
    stack_init(&stack_disp);
    tree_node = root;
    while(!stack_empty(stack) || tree_node != NULL)
    {
        if (tree_node != NULL)
        {
            stack_push(stack_disp,tree_node);
            
            stack_push(stack, tree_node);
            tree_node = tree_node->right;
        }
        else
        {
            stack_pop(stack, &tree_node);
            tree_node = tree_node->left;
        }
    }
    
    while(!stack_empty(stack_disp))
    {
        stack_pop(stack_disp, &tree_node);
        tree_data_disp(tree_node->data);
    }
    
    stack_destroy(&stack);
    stack_destroy(&stack_disp);
}

void tree_traversal_breadth(ptree_t head, tree_data_disp_t tree_data_disp)
{
    pqueue_t queue;
    ptree_node_t root;
    ptree_node_t tree_node;

    if((head == NULL) || head->tree == NULL)
    {
        return ;
    }
    root = head->tree;
    
    queue_init(&queue);
    queue_in(queue,root);
    if(root != NULL)
    {
        while(!queue_empty(queue))
        {
            queue_out(queue,&tree_node);
            if(tree_node->left != NULL)
            {
                queue_in(queue,tree_node->left);
            }
            if(tree_node->right != NULL)
            {
                queue_in(queue,tree_node->right);
            }

            tree_data_disp(tree_node->data);
        }
    }

    queue_destroy(&queue);
}

// --------------- AVL ----------------------
static int32_t tree_get_height(ptree_node_t tree)
{
    pqueue_t queue;
    ptree_node_t root;
    ptree_node_t tree_node;
    
    int32_t height = 0;
    uint32_t count = 0;
    uint32_t next_level_node_cnt = 0;
    
    if(tree == NULL)
    {
        return false;
    }
    root = tree;
    
    queue_init(&queue);
    queue_in(queue,root);
    if(root != NULL)
    {
        while(!queue_empty(queue))
        {
            queue_out(queue,&tree_node);
            if(tree_node->left != NULL)
            {
                queue_in(queue,tree_node->left);
            }
            if(tree_node->right != NULL)
            {
                queue_in(queue,tree_node->right);
            }

            if(count == next_level_node_cnt)
            {
                next_level_node_cnt = queue_get_size(queue);
                count = 1;
                height ++;
            }
            else
            {
                count++;
            }
        }
    }

    queue_destroy(&queue);
    return height;
}

static void tree_set_balance(ptree_node_t tree)
{
    if (tree != NULL)
    {
        tree->balance = tree_get_height(tree->right) - tree_get_height(tree->left);
    }
}

static ptree_node_t tree_turn_left(ptree_node_t tree)
{
    ptree_node_t tree_node;
    ptree_node_t root;
    
    if(tree == NULL)
    {
        return NULL;
    }
    root = tree;
    
    // tree -> original node[a]
    // tree_node -> original right subnode[b] of [a]
    tree_node = root->right;

    // 1. replace the children of the parent node
    if(root->parent != NULL)
    {
        // not root
        if(root->parent->left == root)
        {
            root->parent->left = tree_node;
        }
        else
        {
            root->parent->right = tree_node;
        }
    }
    tree_node->parent = root->parent;
    
    // 2. turn left
    root->parent = tree_node;
    root->right = tree_node->left;
    tree_node->left = root;
    if(root->right != NULL)
    {
        root->right->parent = root;
    }

    // 3. set balance
    tree_set_balance(root);
    tree_set_balance(tree_node);
    return tree_node;
}


static ptree_node_t tree_turn_right(ptree_node_t tree)
{
    ptree_node_t tree_node;
    ptree_node_t root;
    
    if(tree == NULL)
    {
        return NULL;
    }
    root = tree;

    // tree -> original node[a]
    // tree_node -> original left subnode[b] of [a]
    tree_node = root->left;
    
    // 1. replace the children of the parent node
    if(root->parent != NULL)
    {
        // not root
        if(root->parent->left == root)
        {
            root->parent->left = tree_node;
        }
        else
        {
            root->parent->right = tree_node;
        }
    }
    tree_node->parent = root->parent;
    
    // 2. turn left
    root->parent = tree_node;
    root->left = tree_node->right;
    tree_node->right = root;
    if(root->left != NULL)
    {
        root->left->parent = root;
    }
    tree_set_balance(root);
    tree_set_balance(tree_node);
    return tree_node;
}


static ptree_node_t tree_turn_left_then_right(ptree_node_t tree)
{
    ptree_node_t root;
    if(tree == NULL)
    {
        return NULL;
    }
    root = tree;
    
    // first left then right
    root->left = tree_turn_left(root->left);
    return tree_turn_right(root);
}


static ptree_node_t tree_turn_right_then_left(ptree_node_t tree)
{
    ptree_node_t root;
    if(tree == NULL)
    {
        return NULL;
    }
    root = tree;

    // first left then right
    root->right = tree_turn_right(root->right);
    return tree_turn_left(root);
}


static bool tree_rebalance(ptree_t head, ptree_node_t tree)
{
    ptree_node_t root;
    
    if((head == NULL) || head->tree == NULL)
    {
        return false;
    }
    if(tree == NULL)
    {
        return false;
    }
    
    do
    {
        tree_set_balance(tree);
        // left is greater than right
        if(tree->balance == -2)
        {
            if(tree->left->balance <= 0)
            {
                // node-left-left
                tree = tree_turn_right(tree);
            }
            else
            {
                // node-left-rigt
                tree = tree_turn_left_then_right(tree);
            }
        }
        // right is greater than left
        else if(tree->balance == 2)
        {
            if(tree->right->balance >= 0)
            {
                // node-right-right
                tree = tree_turn_left(tree);
            }
            else
            {
                // node-right-left
                tree = tree_turn_right_then_left(tree);
            }
        }

        root = tree;
        tree = tree->parent;
    }while(tree != NULL);
    
    head->tree = root;
    return true;
}

#endif

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

    if(root->parent != NULL)
    {
        if(root->parent->left == root)          // step1
        {
            root->parent->left = node;
        }
        else if(root->parent->right == root)
        {
            root->parent->right = node;         // setp1
        }
    }
    node->parent = root->parent;        // step2
    root->parent = node;                // step3

    root->right = node->left;           // step4
    node->left = root;                  // step5
    
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

    if(root->parent != NULL)
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
    node->right = root;                 // step5
    
    tree_set_balance(self, root);
    tree_set_balance(self, node);
    return node;
}

static struct _tree_node* tree_trun_left_then_right(struct _tree* self, struct _tree_node* root)
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

static struct _tree_node* tree_trun_right_then_left(struct _tree* self, struct _tree_node* root)
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
    assert(self != NULL);
    if(root == NULL)
    {
        return 0;
    }
    uint32_t left_height = tree_height(self, root->left);
    uint32_t right_height = tree_height(self, root->right);
    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
}

/**
 * @brief 
 * 
 * 以 balance = rigth - left 为标准，调整平衡因子
 * 
 * | 情况 | root->balance | node->balance | 调整方式 |
 * | ---- | ------------ | -------------- | -------- |
 * | 1    |  2           |  1             | 左旋
 * | 2    |  2           | -1             | 先右旋后左旋
 * | 3    | -2           | -1             | 右旋
 * | 4    | -2           |  1             | 先左旋后右旋
 * 
 * @param self 
 * @return true 
 * @return false 
 */
static bool tree_avl_rebalance(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return true;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return true;
    }

    // self->print_obj(root->obj);
    tree_set_balance(self, root);
    int balance = root->balance;
    if(balance == 2)
    {
        if(root->right->balance == 1)
        {
            root = tree_turn_left(self, root);
        }
        else if(root->right->balance == -1)
        {
            root = tree_trun_right_then_left(self, root);
        }
    }
    else if(balance == -2)
    {
        if(root->left->balance == -1)
        {
            root = tree_turn_right(self, root);
        }
        else if(root->left->balance == 1)
        {
            root = tree_trun_left_then_right(self, root);
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
 * @brief 在树中查找插入位置
 * 
 * @param self 树的指针
 * @param obj 要查找或插入的对象
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

        // printf("--------------------\n");
        // printf("insert     : \n");
        // self->print_obj(node->obj);
        // printf("\n");

        // printf("all data   : \n");
        // self->preorder(self, self->_root);
        // printf("\n");

        self->rebalance(self, root);

        // printf("parent_path: \n");
        // struct _tree_node * tmp = node;
        // do
        // {
        //     self->print_obj(tmp->obj);
        //     tmp = tmp->parent;
        // }while(tmp != NULL);
        // printf("\n");
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
            node->left->parent = NULL;
            self->_root = node->left;
        }
        else if(node->right != NULL)
        {
            node->right->parent = NULL;
            self->_root = node->right;
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
                node->left->parent = node->parent;
                node->parent->left = node->left;
            }
            else if(node->right != NULL)
            {
                node->right->parent = node->parent;
                node->parent->left = node->right;
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
                node->left->parent = node->parent;
                node->parent->right = node->left;
            }
            else if(node->right != NULL)
            {
                node->right->parent = node->parent;
                node->parent->right = node->right;
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
        if(tmp->right != NULL)
        {
            node->right = tmp->right;
            tmp->right->parent = node;
        }
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
    // debug
    self->print_obj(obj);

    if(node->left != NULL && node->right != NULL)
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

struct _tree_node * tree_avl_find(struct _tree* self, void* obj)
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
}

void tree_order(struct _tree* self, bool right_priority)
{
    assert(self != NULL);
    self->_right_priority = right_priority;
}

void tree_avl_preorder(struct _tree* self, struct _tree_node* root)
{
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
            tree_avl_preorder(self, root->left);
        }
        if(root->right != NULL)
        {
            tree_avl_preorder(self, root->right);
        }
    }
    else
    {
        self->print_obj(root->obj);
        if(root->right != NULL)
        {
            tree_avl_preorder(self, root->right);
        }
        if(root->left != NULL)
        {
            tree_avl_preorder(self, root->left);
        }
    }
}

void tree_avl_inorder(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    if(!self->_right_priority)
    {
        if(root->left != NULL)
        {
            tree_avl_inorder(self, root->left);
        }
        self->print_obj(root->obj);
        if(root->right != NULL)
        {
            tree_avl_inorder(self, root->right);
        }
    }
    else
    {
        if(root->right != NULL)
        {
            tree_avl_inorder(self, root->right);
        }
        self->print_obj(root->obj);
        if(root->left != NULL)
        {
            tree_avl_inorder(self, root->left);
        }
    }
}

void tree_avl_postorder(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    if(!self->_right_priority)
    {
        if(root->left != NULL)
        {
            tree_avl_postorder(self, root->left);
        }
        if(root->right != NULL)
        {
            tree_avl_postorder(self, root->right);
        }
        self->print_obj(root->obj);
    }
    else
    {
        if(root->right != NULL)
        {
            tree_avl_postorder(self, root->right);
        }
        if(root->left != NULL)
        {
            tree_avl_postorder(self, root->left);
        }
        self->print_obj(root->obj);
    }
}

// traversal breadth
void tree_avl_breadth(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return;
    }

    struct _tree_node* node = self->_root;
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
    queue_free(queue);
}

static struct _tree_node* tree_find_min(struct _tree* self, struct _tree_node* root)
{
    assert(self != NULL);
    if(root == NULL)
    {
        return NULL;
    }
    if(root->left == NULL)
    {
        return root;
    }
    return tree_find_min(self, root->left);
}

static struct _tree_node* tree_find_max(struct _tree* self, struct _tree_node* root)
{
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
}

bool tree_avl_init(struct _tree *self, uint32_t obj_size)
{
    assert(self != NULL);

    self->_obj_size = obj_size;
    self->_size = 0;
    // self->_capacity = 64;
    // self->_ratio = 2;

    self->_right_priority = false;

    self->insert = tree_avl_insert;
    self->delete = tree_avl_delete;
    self->clear = tree_clear;
    self->empty = tree_empty;
    self->size = tree_size;
    self->destory = tree_destory;
    self->preorder = tree_avl_preorder;
    self->inorder = tree_avl_inorder;
    self->postorder = tree_avl_postorder;
    self->breadth = tree_avl_breadth;
    self->order = tree_order;
    self->find = tree_avl_find;
    self->height = tree_height;
    self->rebalance = tree_avl_rebalance;
    self->find_max = tree_find_max;
    self->find_min = tree_find_min;

    self->_root = NULL;

    return true;
}

bool tree_rb_init(struct _tree *self, uint32_t obj_size)
{

}

tree_t tree_new(void)
{
    return (struct _tree*)malloc(sizeof(struct _tree));
}

void tree_free(tree_t tree)
{
    if(tree != NULL)
    {
        tree->destory(tree);
        free(tree);
    }
}
