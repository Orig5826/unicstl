/**
 * @file demo_graph.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "demo.h"
 
void demo_graph_add_vertex(void)
{
    const int size = 10;
    int data[10] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    int temp = 11;
    uint32_t i = 0;

    graph_t graph = graph_new(sizeof(int));
    graph->compare = compare_num;
    graph->print_obj = print_num;

    // test add_vertex
    for(i = 0; i < size; i++)
    {
        graph->add_vertex(graph, &data[i]);
    }
    // graph->print(graph);

    // test add_edge
    graph->add_edge(graph, &data[0], &data[1], 12);
    graph->add_edge(graph, &data[0], &data[2], 13);
    graph->add_edge(graph, &data[1], &data[3], 24);
    graph->add_edge(graph, &data[5], &data[6], 67);
    graph->add_edge(graph, &data[7], &data[6], 87);
    graph->add_edge(graph, &data[8], &data[2], 92);

    graph->add_edge(graph, &temp, &data[1], 0);
    graph->print(graph);

    iterator_t iter_vertex = NULL;
    iter_vertex = graph->iter(graph, GRAPH_BFS, &data[0]);
    while(iter_vertex->hasnext(iter_vertex))
    {
        temp = *(int *)iter_vertex->next(iter_vertex);
        graph->print_obj(&temp);
    }
    printf("\n");

    iter_vertex = graph->iter(graph, GRAPH_DFS, &data[0]);
    while(iter_vertex->hasnext(iter_vertex))
    {
        temp = *(int *)iter_vertex->next(iter_vertex);
        graph->print_obj(&temp);
    }
    printf("\n");

    graph_free(&graph);
}

void demo_graph(void)
{
    demo_graph_add_vertex();
}