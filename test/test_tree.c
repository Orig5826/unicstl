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

static const enum _order order[8] = { 
    ORDER_LEFT_PRE, ORDER_LEFT_IN, ORDER_LEFT_POST, ORDER_LEFT_BREADTH,
    ORDER_RIGHT_PRE, ORDER_RIGHT_IN, ORDER_RIGHT_POST, ORDER_RIGHT_BREADTH
};

static uint32_t iter2array_num(iterator_t iter, int *data)
{
    uint32_t count = 0;
    while(iter->hasnext(iter))
    {
        data[count] = *(int *)iter->next(iter);
        count++;
    }
    return count;
}

static void test_avltree_iter(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(int);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    memcpy(data, expected_int_array[0], len);
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
        
        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 0; i < 8; i++)
    {
        iter = tree->iter(tree, order[i]);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[i + 1], buff, count);
    }

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
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(int);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    memcpy(data, expected_int_array[0], len);
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 0; i < 8; i++)
    {
        iter = tree->iter(tree, order[i]);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array[i + 1], buff, count);
    }
    
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_avltree_delete(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(int);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_avl_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    memcpy(data, expected_int_array[0], len);
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
    }

    for (i = 0; i < len; i++)
    {
        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_int_array_orderpre_delete[i], buff, count);

        temp = data[i];
        TEST_ASSERT_TRUE(tree->delete(tree, &temp));
    }
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
    int data[15] = { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(int);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;
    
    tree_t tree = tree_rb_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));
        
        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 0; i < 8; i++)
    {
        iter = tree->iter(tree, order[i]);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array[i + 1], buff, count);
    }

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
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(int);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;

    tree_t tree = tree_rb_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(tree);
    tree->print_obj = print_num;
    tree->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(tree->insert(tree, &temp));

        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_insert[i], buff, count);
    }

    for(i = 0; i < 8; i++)
    {
        iter = tree->iter(tree, order[i]);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array[i + 1], buff, count);
    }
    
    tree_free(&tree);
    TEST_ASSERT_NULL(tree);
}

static void test_rbtree_delete(void)
{
    uint32_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6,  4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    uint32_t len = sizeof(data) / sizeof(data[0]);
    int temp = 0;
    int count = 0;
    iterator_t iter = NULL;
    enum _order order[8] = { 
        ORDER_LEFT_PRE, ORDER_LEFT_IN, ORDER_LEFT_POST, ORDER_LEFT_BREADTH,
        ORDER_RIGHT_PRE, ORDER_RIGHT_IN, ORDER_RIGHT_POST, ORDER_RIGHT_BREADTH
    };

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
        iter = tree->iter(tree, ORDER_LEFT_PRE);
        count = iter2array_num(iter, buff);
        TEST_ASSERT_EQUAL_INT_ARRAY(rbt_expected_int_array_orderpre_delete[i], buff, count);

        temp = data[i];
        TEST_ASSERT_TRUE(tree->delete(tree, &temp));
    }
    TEST_ASSERT_FALSE(tree->delete(tree, &temp));

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
}
