/**
 * @file test_graph.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

void test_graph_new(void)
{
    graph_t g = graph_new2(sizeof(int), 10);
    TEST_ASSERT(g != NULL);
    graph_free(&g);
    TEST_ASSERT(g == NULL);
}

void test_graph(void)
{
    RUN_TEST(test_graph_new);
}
