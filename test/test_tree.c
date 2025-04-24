/**
 * @file test_tree.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

 // if vs2022 has error: 'max': macro redefinition
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#if 0
/**
 * @brief
 * int data[] = { 5,2,3,1,7,8,6 };
 *           5
 *      |         |
 *      2         7
 *   |    |     |   |
 *   1    3     6   8
 */
void test_avltree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

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
        tree->preorder(tree, tree->_root);
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
    if (tree->empty(tree))
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
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

    printf("----- right priority -----\n");
    tree->order(tree, true);

    printf("----- preorder(right) -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder(right) -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder(right) -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth(right) -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");


    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        // delete
        tree->delete(tree, &temp);

        printf("delete = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");
    }

    if (tree->empty(tree))
    {
        printf("----- empty -----\n");
    }

    tree_free(&tree);
}

static bool tree_rb_check_color(struct _tree* self, struct _tree_node* root, int black_num, int black_num_expected)
{
    if (root == NULL)
    {
        if (black_num != black_num_expected)
        {
            printf("black_num != black_num_expected\n");
            return false;
        }
        return true;
    }

    if (root->color == RBT_BLACK)
    {
        black_num++;
    }

    if (root->color == RBT_RED && root->parent && root->parent->color == RBT_RED)
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
    if (self->_root == NULL)
    {
        return true;
    }

    if (self->_root->color != RBT_BLACK)
    {
        printf("self->_root->color != RBT_BLACK\n");
        return false;
    }

    int black_num_expected = 0;
    struct _tree_node* root = self->_root;
    while (root)
    {
        if (root->color == RBT_BLACK)
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
void test_rbtree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

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
        tree->preorder(tree, tree->_root);
        printf("\n");

        if (true != tree_rb_check(tree))
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
    if (tree->empty(tree))
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
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

    printf("----- right priority -----\n");
    tree->order(tree, true);

    printf("----- preorder(right) -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder(right) -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder(right) -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth(right) -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

#if 1
    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        printf("delete = ");
        tree->print_obj(&temp);

        // delete
        tree->delete(tree, &temp);

        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");

        if (true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    if (tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
#endif
    tree_free(&tree);
}

/**
 * @brief
 */
void test_rbtree_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp = { 0 };
    uint32_t len = sizeof(data) / sizeof(data[0]);

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
        tree->preorder(tree, tree->_root);
        printf("\n");

        if (true != tree_rb_check(tree))
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
    if (tree->empty(tree))
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
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

    printf("----- right priority -----\n");
    tree->order(tree, true);

    printf("----- preorder(right) -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder(right) -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder(right) -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth(right) -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

#if 1
    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        printf("delete = ");
        tree->print_obj(&temp);

        // delete
        tree->delete(tree, &temp);

        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");

        if (true != tree_rb_check(tree))
        {
            printf("----- rb_check_error -----\n");
            return;
        }
    }

    if (tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
#endif
    tree_free(&tree);
}
#endif

static const int expected_int_array[9][15] = {
    { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13},       // original data
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15},       // order_left_pre
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},       // order_left_in
    { 1, 2, 4, 6, 5, 3, 8, 10, 9, 13, 12, 15, 14, 11, 7},       // order_left_post
    { 7, 3, 11, 2, 5, 9, 14, 1, 4, 6, 8, 10, 12, 15, 13},       // order_left_breadth
    { 7, 11, 14, 15, 12, 13, 9, 10, 8, 3, 5, 6, 4, 2, 1},       // order_right_pre
    { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},       // order_right_in
    { 15, 13, 12, 14, 10, 8, 9, 11, 6, 4, 5, 1, 2, 3, 7},       // order_right_post
    { 7, 11, 3, 14, 9, 5, 2, 15, 12, 10, 8, 6, 4, 1, 13},       // order_right_breadth
};

static const int expected_int_array_orderpre_insert[15][15] = {
    { 5, },
    { 5, 2, },
    { 3, 2, 5, },
    { 3, 2, 1, 5, },
    { 3, 2, 1, 5, 7, },
    { 3, 2, 1, 7, 5, 8, },
    { 3, 2, 1, 7, 5, 6, 8, },
    { 3, 2, 1, 7, 5, 4, 6, 8, },
    { 3, 2, 1, 7, 5, 4, 6, 8, 9, },
    { 3, 2, 1, 7, 5, 4, 6, 9, 8, 10, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 10, 12, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 11, 10, 12, },
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 12, 15, },
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 15, },
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
};

static const int expected_int_array_orderpre_delete[15][15] = {
    {  7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 3, 2, 1, 6, 4, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 3, 1, 6, 4, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 4, 1, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
    { 11, 7, 4, 6, 9, 8, 10, 14, 12, 13, 15, },
    { 11, 8, 4, 6, 9, 10, 14, 12, 13, 15, },
    { 11, 9, 4, 6, 10, 14, 12, 13, 15, },
    { 11, 9, 4, 10, 14, 12, 13, 15, },
    { 11, 9, 10, 14, 12, 13, 15, },
    { 12, 11, 10, 14, 13, 15, },
    { 12, 11, 14, 13, 15, },
    { 13, 11, 14, 15, },
    { 14, 13, 15, },
    { 14, 13, },
    { 13, },
};

static void test_avltree_iter(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    // int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
        
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
        }
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 1; i < 9; i++)
    {
        tree->set_order(tree, i);  //ORDER_LEFT_IN
        // printf("\n ----- iter test -----\n");
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            // printf("(%2d ) ", *iter);
            buff[count++] = *iter;
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[i], buff, count);
    }

#if 0
    tree->order(tree, true);
    printf("\n\nactual data = \n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    // set order
    // tree->set_order(tree, ORDER_LEFT_PRE);
    // tree->set_order(tree, ORDER_LEFT_IN);
    // tree->set_order(tree, ORDER_LEFT_POST);
    // tree->set_order(tree, ORDER_LEFT_BREADTH);
    // tree->set_order(tree, ORDER_RIGHT_PRE);
    // tree->set_order(tree, ORDER_RIGHT_IN);
    tree->set_order(tree, ORDER_RIGHT_POST);
    // tree->set_order(tree, ORDER_RIGHT_BREADTH);
    printf("\n ----- iter data -----\n");
    for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
    {
        printf("(%2d ) ", *iter);
        buff[count++] = *iter;
    }
    printf("\n");
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[tree->_order], buff, count);
#endif

    TEST_ASSERT_FALSE(tree->empty(tree));
    TEST_ASSERT_TRUE(tree->clear(tree));
    TEST_ASSERT_TRUE(tree->empty(tree));
    TEST_ASSERT_TRUE(tree->clear(tree));
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_avltree_insert(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);

    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));

        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
        }
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 1; i < 9; i++)
    {
        tree->set_order(tree, i);  //ORDER_LEFT_IN
        // printf("\n ----- iter test -----\n");
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            // printf("(%2d ) ", *iter);
            buff[count++] = *iter;
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[i], buff, count);
    }
    
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_avltree_delete(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);

    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
    }

    for (i = 0; i < len; i++)
    {
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
            // printf("(%2d ) ", *iter);
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_delete[i], buff, count);

        temp = data[i];
        // delete
        TEST_ASSERT_TRUE(tree->delete(tree, &temp));
    }
    // 
    TEST_ASSERT_FALSE(tree->delete(tree, &temp));

    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}




static const int rbt_expected_int_array[9][15] = {
    { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13},       // original data
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15},       // order_left_pre
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},       // order_left_in
    { 1, 2, 4, 6, 5, 3, 8, 10, 9, 13, 12, 15, 14, 11, 7},       // order_left_post
    { 7, 3, 11, 2, 5, 9, 14, 1, 4, 6, 8, 10, 12, 15, 13},       // order_left_breadth
    { 7, 11, 14, 15, 12, 13, 9, 10, 8, 3, 5, 6, 4, 2, 1},       // order_right_pre
    { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},       // order_right_in
    { 15, 13, 12, 14, 10, 8, 9, 11, 6, 4, 5, 1, 2, 3, 7},       // order_right_post
    { 7, 11, 3, 14, 9, 5, 2, 15, 12, 10, 8, 6, 4, 1, 13},       // order_right_breadth
};

static const int rbt_expected_int_array_orderpre_insert[15][15] = {
    { 5, },
    { 5, 2, },
    { 3, 2, 5, },
    { 3, 2, 1, 5, },
    { 3, 2, 1, 5, 7, },
    { 3, 2, 1, 7, 5, 8, },
    { 3, 2, 1, 7, 5, 6, 8, },
    { 3, 2, 1, 7, 5, 4, 6, 8, },
    { 3, 2, 1, 7, 5, 4, 6, 8, 9, },
    { 3, 2, 1, 7, 5, 4, 6, 9, 8, 10, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 10, 12, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 11, 10, 12, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 11, 10, 12, 15, },
    { 7, 3, 2, 1, 5, 4, 6, 9, 8, 11, 10, 14, 12, 15, },
    { 7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
};

static const int rbt_expected_int_array_orderpre_delete[15][15] = {
    {  7, 3, 2, 1, 5, 4, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 3, 2, 1, 6, 4, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 3, 1, 6, 4, 11, 9, 8, 10, 14, 12, 13, 15, },
    {  7, 4, 1, 6, 11, 9, 8, 10, 14, 12, 13, 15, },
    { 11, 7, 4, 6, 9, 8, 10, 14, 12, 13, 15, },
    { 11, 8, 4, 6, 9, 10, 14, 12, 13, 15, },
    { 11, 9, 4, 6, 10, 14, 12, 13, 15, },
    { 11, 9, 4, 10, 14, 12, 13, 15, },
    { 11, 9, 10, 14, 12, 13, 15, },
    { 11, 10, 14, 12, 13, 15, },
    { 14, 12, 11, 13, 15, },
    { 14, 13, 11, 15, },
    { 14, 13, 15, },
    { 14, 13, },
    { 13, },
};


static void test_rbtree_iter(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    // int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_rb_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);

    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
        
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
        }
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 1; i < 9; i++)
    {
        tree->set_order(tree, i);  //ORDER_LEFT_IN
        // printf("\n ----- iter test -----\n");
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            // printf("(%2d ) ", *iter);
            buff[count++] = *iter;
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array[i], buff, count);
    }

#if 0
    tree->order(tree, true);
    printf("\n\nactual data = \n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    // set order
    // tree->set_order(tree, ORDER_LEFT_PRE);
    // tree->set_order(tree, ORDER_LEFT_IN);
    // tree->set_order(tree, ORDER_LEFT_POST);
    // tree->set_order(tree, ORDER_LEFT_BREADTH);
    // tree->set_order(tree, ORDER_RIGHT_PRE);
    // tree->set_order(tree, ORDER_RIGHT_IN);
    tree->set_order(tree, ORDER_RIGHT_POST);
    // tree->set_order(tree, ORDER_RIGHT_BREADTH);
    printf("\n ----- iter data -----\n");
    for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
    {
        printf("(%2d ) ", *iter);
        buff[count++] = *iter;
    }
    printf("\n");
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[tree->_order], buff, count);
#endif

    TEST_ASSERT_FALSE(tree->empty(tree));
    TEST_ASSERT_TRUE(tree->clear(tree));
    TEST_ASSERT_TRUE(tree->empty(tree));
    TEST_ASSERT_TRUE(tree->clear(tree));
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_rbtree_insert(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_rb_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);

    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));

        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
        }
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 1; i < 9; i++)
    {
        tree->set_order(tree, i);  //ORDER_LEFT_IN
        // printf("\n ----- iter test -----\n");
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            // printf("(%2d ) ", *iter);
            buff[count++] = *iter;
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array[i], buff, count);
    }
    
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_rbtree_delete(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    int * iter = NULL;
    int count = 0;

    tree_t tree = tree_rb_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);

    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
    }

    for (i = 0; i < len; i++)
    {
        for (count = 0, iter = tree->begin(tree); iter != tree->end(tree); iter = tree->next(tree))
        {
            buff[count++] = *iter;
            // printf("(%2d ) ", *iter);
        }
        // printf("\n");
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_delete[i], buff, count);

        temp = data[i];
        // delete
        TEST_ASSERT_TRUE(tree->delete(tree, &temp));
    }
    // 
    TEST_ASSERT_FALSE(tree->delete(tree, &temp));

    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}


static void test_avltree_iter_2(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[32];
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    // int * iter = NULL;
    int count = 0;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
    }

    printf("\n");

    iterator_t iter = tree->iter(tree, ORDER_LEFT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_LEFT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_LEFT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_LEFT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_RIGHT_PRE);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_RIGHT_IN);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_RIGHT_POST);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    iter = tree->iter(tree, ORDER_RIGHT_BREADTH);
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        tree->print_obj(&temp);
    }
    printf("\n");

    TEST_ASSERT_TRUE(tree->clear(tree));
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

void test_tree(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_avltree_iter);
    RUN_TEST(test_avltree_insert);
    RUN_TEST(test_avltree_delete);

    RUN_TEST(test_rbtree_iter);
    RUN_TEST(test_rbtree_insert);
    RUN_TEST(test_rbtree_delete);

    // RUN_TEST(test_avltree_num);
    // RUN_TEST(test_rbtree_num);
    // RUN_TEST(test_rbtree_struct);

    RUN_TEST(test_avltree_iter_2);
}
