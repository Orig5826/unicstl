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
    graph_t graph = graph_new2(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(graph);
    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

void test_graph_print(void)
{
    graph_t graph = graph_new2(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(graph);
    graph->print_obj = print_num;

    graph->print(graph);

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

void test_graph_from_matrix(void)
{
    // const uint32_t size = 10;
#define size 5
    int vertexs[size] = {1,2,3,4,5};
    int matrix[size * size] = {
        0, 1, 0, 0, 0, 
        1, 0, 1, 0, 0, 
        0, 1, 0, 1, 0, 
        0, 0, 1, 0, 1, 
        0, 0, 0, 1, 0, 
    };

    graph_t graph = graph_new2(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(graph);
    graph->print_obj = print_num;

    graph->print(graph);
    graph->from_matrix(graph, vertexs, matrix, size);
    graph->print(graph);

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

void test_graph(void)
{
    RUN_TEST(test_graph_new);
    // RUN_TEST(test_graph_print);
    RUN_TEST(test_graph_from_matrix);
}
