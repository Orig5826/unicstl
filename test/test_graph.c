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

    // test add_vertex
    for(i = 0; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->add_vertex(graph, &data[i]));
    }
    // graph->print(graph);

    // test find_vertex
    TEST_ASSERT_TRUE(graph->find_vertex(graph, &data[0]));
    TEST_ASSERT_TRUE(graph->find_vertex(graph, &data[9]));
    TEST_ASSERT_FALSE(graph->find_vertex(graph, &temp));

    // test del_vertex
    TEST_ASSERT_TRUE(graph->del_vertex(graph, &data[0]));
    TEST_ASSERT_FALSE(graph->find_vertex(graph, &data[0]));
    // graph->print(graph);

    for(i = 1; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->del_vertex(graph, &data[i]));
    }
    TEST_ASSERT_TRUE(graph->empty(graph));

    // test clear
    for(i = 0; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->add_vertex(graph, &data[i]));
    }
    // graph->print(graph);

    graph->clear(graph);
    // graph->print(graph);
    TEST_ASSERT_TRUE(graph->empty(graph));

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}


void test_graph_add_edge(void)
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

    // test add_vertex
    for(i = 0; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->add_vertex(graph, &data[i]));
    }
    //graph->print(graph);

    // test add_edge
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[0], &data[1], 12));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[0], &data[2], 13));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[1], &data[3], 24));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[5], &data[6], 67));
    TEST_ASSERT_FALSE(graph->add_edge(graph, &temp, &data[1], 0));
    //graph->print(graph);

    // test find_edge
    TEST_ASSERT_TRUE(graph->find_edge(graph, &data[0], &data[1]));
    TEST_ASSERT_TRUE(graph->find_edge(graph, &data[1], &data[3]));
    TEST_ASSERT_TRUE(graph->find_edge(graph, &data[6], &data[5]));  // undirected graph
    TEST_ASSERT_FALSE(graph->find_edge(graph, &data[4], &data[3]));
    TEST_ASSERT_FALSE(graph->find_edge(graph, &data[0], &temp));

    // test del_edge
    TEST_ASSERT_TRUE(graph->del_edge(graph, &data[0], &data[1]));
    //graph->print(graph);

    TEST_ASSERT_FALSE(graph->find_edge(graph, &data[0], &data[1]));
    TEST_ASSERT_TRUE(graph->del_edge(graph, &data[5], &data[6]));
    //graph->print(graph);

    graph_free(&graph);
    TEST_ASSERT_NULL(graph);
}

void test_graph_iter(void)
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

    // test add_vertex
    for(i = 0; i < size; i++)
    {
        TEST_ASSERT_TRUE(graph->add_vertex(graph, &data[i]));
    }
    // graph->print(graph);

    // test add_edge
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[0], &data[1], 12));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[0], &data[2], 13));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[1], &data[3], 24));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[5], &data[6], 67));

    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[7], &data[6], 87));
    TEST_ASSERT_TRUE(graph->add_edge(graph, &data[8], &data[2], 92));
    TEST_ASSERT_FALSE(graph->add_edge(graph, &temp, &data[1], 0));
    // graph->print(graph);

    iterator_t iter_vertex = NULL;

    iter_vertex = graph->iter(graph, GRAPH_BFS, &data[0]);
    TEST_ASSERT_NOT_NULL(iter_vertex);
    while(iter_vertex->hasnext(iter_vertex))
    {
        temp = *(int *)iter_vertex->next(iter_vertex);
        graph->print_obj(&temp);
    }
    printf("\n");

    iter_vertex = graph->iter(graph, GRAPH_DFS, &data[0]);
    TEST_ASSERT_NOT_NULL(iter_vertex);
    while(iter_vertex->hasnext(iter_vertex))
    {
        temp = *(int *)iter_vertex->next(iter_vertex);
        graph->print_obj(&temp);
    }
    printf("\n");

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
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_iter);

    // RUN_TEST(test_graph_print);
    // RUN_TEST(test_graph_from_matrix);
}
