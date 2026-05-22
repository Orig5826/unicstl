/**
 * @file test_rbtree.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-22
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

void test_rbtree_new(void)
{
    rbtree_t rbt = rbtree_new(sizeof(int), 10, compare_int);
    TEST_ASSERT_NOT_NULL(rbt);

    rbtree_free(&rbt);
}

void test_rbtree_insert(void)
{
    size_t i = 0;
    int data[15] = { 5, 2, 3, 1, 7, 8, 6, 4, 9, 10, 12, 11, 15, 14, 13, };
    int buff[15];
    size_t len = sizeof(data) / sizeof(int);
    int temp = 0;

    rbtree_t rbt = rbtree_new(sizeof(int), 10, compare_int);
    rbt->print_obj = print_num;
    TEST_ASSERT_NOT_NULL(rbt);

    for(i = 0; i < len; ++i)
    {
        TEST_ASSERT_TRUE(rbt->insert(rbt, &data[i]));
    }

    rbt->print(rbt);

    rbtree_free(&rbt);
}

void test_rbtree(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_rbtree_new);
    RUN_TEST(test_rbtree_insert);
}
