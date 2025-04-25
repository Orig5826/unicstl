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
    graph_t graph = graph_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(graph);
    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

void test_graph_add_vertex(void)
{
    const int size = 10;
    int data[10] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    int temp = 11;
    uint32_t i = 0;

    graph_t graph = graph_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(graph);
    graph->compare = compare_num;
    graph->print_obj = print_num;

    for(i = 0; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->add_vertex(graph, &data[i]));
    }
    graph->print(graph);

    TEST_ASSERT_TRUE(graph->find_vertex(graph, &data[0]));
    TEST_ASSERT_TRUE(graph->find_vertex(graph, &data[9]));
    TEST_ASSERT_FALSE(graph->find_vertex(graph, &temp));

    

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

#if 0
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
    int vertexs[size] = {0, 1, 2, 3, 4};
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

    // graph->print(graph);
    graph->from_matrix(graph, vertexs, matrix, size);
    // graph->print(graph);

    graph->bfs(graph, 1);

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}
#endif

void test_graph(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_graph_new);
    RUN_TEST(test_graph_add_vertex);

    // RUN_TEST(test_graph_print);
    // RUN_TEST(test_graph_from_matrix);
}
