/**
 * @file demo_tree.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "demo.h"

// if vs2022 has error: 'max': macro redefinition
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

/**
 * @brief 
 * int data[] = { 5,2,3,1,7,8,6 };
 *           5
 *      |         |
 *      2         7
 *   |    |     |   |
 *   1    3     6   8
 */
void demo_avltree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    int temp = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_avl_new(sizeof(int));
    tree->print_obj = print_num;
    tree->compare = compare_num;

    printf("\n\n----- demo_avltree_num -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);

        printf("insert = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(int *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");
    }

    printf("----- max -----\n");
    tree->max(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- min -----\n");
    tree->min(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- tree -----\n");
    tree->clear(tree);
    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);
    }

    printf("----- preorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth -----\n");
    iter = tree->iter(tree, ORDER_LEFT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- preorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");


    printf("----- preorder(left) -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        // delete
        tree->delete(tree, &temp);

        printf("delete = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(int *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }

    tree_free(&tree);
}

static bool tree_rb_check_color(struct _tree *self, struct _tree_node* root, int black_num, int black_num_expected)
{
    if(root == NULL)
    {
        if(black_num != black_num_expected)
        {
            printf("black_num != black_num_expected\n");
            return false;
        }
        return true;
    }

    if(root->color == RBT_BLACK)
    {
        black_num++;
    }

    if(root->color == RBT_RED && root->parent && root->parent->color == RBT_RED)
    {
        printf("The red node is adjacent to the red node\n");
        return false;
    }
    return tree_rb_check_color(self, root->left, black_num, black_num_expected) && 
        tree_rb_check_color(self, root->right, black_num, black_num_expected);
}

static bool tree_rb_check(struct _tree* self)
{
    assert(self != NULL);
    if(self->_root == NULL)
    {
        return true;
    }

    if(self->_root->color != RBT_BLACK)
    {
        printf("self->_root->color != RBT_BLACK\n");
        return false;
    }

    int black_num_expected = 0;
    struct _tree_node* root = self->_root;
    while(root)
    {
        if(root->color == RBT_BLACK)
        {
            black_num_expected++;
        }
        root = root->left;
    }
    return tree_rb_check_color(self, self->_root, 0, black_num_expected);
}

/**
 * @brief 
 */
void demo_rbtree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    int temp = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_rb_new(sizeof(int));
    tree->print_obj = print_num;
    tree->compare = compare_num;

    printf("\n\n----- demo_rbtree_num -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);

        printf("insert = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(int *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");

        if(true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    printf("----- max -----\n");
    tree->max(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- min -----\n");
    tree->min(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- tree -----\n");
    tree->clear(tree);
    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);
    }

    printf("----- preorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth -----\n");
    iter = tree->iter(tree, ORDER_LEFT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- preorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- preorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        printf("delete = ");
        tree->print_obj(&temp);

        // delete
        tree->delete(tree, &temp);

        printf("size = %2d : ", tree->size(tree));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(int *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");

        if(true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    tree_free(&tree);
}

/**
 * @brief 
 */
void demo_rbtree_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);
    iterator_t iter = NULL;

    tree_t tree = tree_rb_new(sizeof(struct _student));
    tree->print_obj = print_struct;
    tree->compare = compare_struct;

    printf("\n\n----- demo_rbtree_struct -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);

        printf("insert = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        
        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(struct _student *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");

        if(true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    printf("----- max -----\n");
    tree->max(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- min -----\n");
    tree->min(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- tree -----\n");
    tree->clear(tree);
    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);
    }

    printf("----- preorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth -----\n");
    iter = tree->iter(tree, ORDER_LEFT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- preorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- inorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- postorder(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- breadth(right) -----\n");
    iter = tree->iter(tree, ORDER_RIGHT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    printf("----- preorder -----\n");
    iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(struct _student *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        printf("delete = ");
        tree->print_obj(&temp);

        // delete
        tree->delete(tree, &temp);

        printf("size = %2d : ", tree->size(tree));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        while(iter->hasnext(iter))
        {
            temp = *(struct _student *)iter->next(iter);
            tree->print_obj(&temp);
        }
        printf("\n");

        if(true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    tree_free(&tree);
}

void demo_tree(void)
{
    demo_avltree_num();
    demo_rbtree_num();
    demo_rbtree_struct();
}
