/**
 * @file graph.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "graph.h"

static uint32_t graph_size(struct _graph* self)
{
    if(self == NULL)
    {
        return 0;
    }
    return self->_size;
}

static uint32_t graph_capacity(struct _graph* self)
{
    if(self == NULL)
    {
        return 0;
    }
    return self->_capacity;
}

static bool graph_clear(struct _graph *self)
{
    if(self == NULL && self->_head == NULL)
    {
        return 0;
    }
    self->_head->obj = NULL;
    return self->_size = 0;
}

static void graph_destory(struct _graph *self)
{
    if(self == NULL)
    {
        return;
    }
    self->clear(self);
    if(self->_head != NULL)
    {
        free(self->_head);
        self->_head = NULL;
    }
}

graph_t graph_new2(uint32_t obj_size, uint32_t capacity)
{
    if(obj_size == 0 || capacity == 0)
    {
        return NULL;
    }

    graph_t graph = malloc(sizeof(struct _graph));
    if(graph == NULL)
    {
        goto done;
    }

    graph->_size = 0;
    graph->_obj_size = obj_size;
    graph->_capacity = capacity;
    graph->_ratio = 1;

    graph->size = graph_size;
    graph->capacity = graph_capacity;

    graph->_head = (struct _graph_node *)malloc(sizeof(struct _graph_node));
    if(graph->_head == NULL)
    {
        goto done1;
    }
    graph->_head->next = NULL;

    graph->_head->obj = (void *)malloc(graph->_obj_size * graph->_capacity * graph->_capacity);
    if(graph->_head->obj == NULL)
    {
        goto done2;
    }

    // init graph
    graph->init(graph);

    return graph;

    // free(graph->_head->obj)
done2:
    free(graph->_head);
done1:
    free(graph);
done:
    return NULL;
}

void graph_free(graph_t *graph)
{
    if(graph == NULL || *graph == NULL)
    {
        return;
    }

    (*graph)->destory(*graph);
    free(*graph);
    *graph = NULL;
}
