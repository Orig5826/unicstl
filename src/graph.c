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
#include "queue.h"
#include "stack.h"

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
    for(uint32_t i = 0; i < self->_capacity; i++)
    {
        for(uint32_t j = 0; j < self->_capacity; j++)
        {
            self->_head->edge[i][j] = 0;
        }
    }
    self->_size = 0;
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
        if(self->_head->visited != NULL)
        {
            free(self->_head->visited);
        }

        if(self->_head->obj != NULL)
        {
            free(self->_head->obj);
        }

        if(self->_head->edge != NULL)
        {
            for(uint32_t i = 0; i < self->_capacity; i++)
            {
                if(self->_head->edge[i] != NULL)
                {
                    free(self->_head->edge[i]);
                }
            }
            free(self->_head->edge);
        }
        free(self->_head);
        self->_head = NULL;
    }
}

static void graph_print(struct _graph *self)
{
    if(self == NULL || self->_head == NULL || self->print_obj == NULL)
    {
        return;
    }

    printf("\n     ");
    for(uint32_t i = 0; i < self->_capacity; i++)
    {
        self->print_obj((char *)self->_head->obj + i * self->_obj_size);
    }
    printf("\n");
    for(uint32_t i = 0; i < self->_capacity; i++)
    {
        self->print_obj((char *)self->_head->obj + i * self->_obj_size);
        for(uint32_t j = 0; j < self->_capacity; j++)
        {
            printf(" %2d   ", self->_head->edge[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("print done.\n");
}

static bool graph_from_matrix(struct _graph *self, void *obj, uint32_t *edges, uint32_t size)
{
    if(self == NULL || self->_head == NULL)
    {
        return false;
    }

    if(size > self->_capacity || obj == NULL || edges == NULL)
    {
        return false;
    }

    for(uint32_t i = 0; i < size; i++)
    {
        memmove((char *)self->_head->obj + i * self->_obj_size, (char *)obj + i * self->_obj_size, self->_obj_size);
    }
    for(uint32_t i = 0; i < size; i++)
    {
        for(uint32_t j = 0; j < size; j++)
        {
            self->_head->edge[i][j] = edges[i * size + j];
        }
    }

    self->_size = size;
    return true;
}

static bool graph_bfs(struct _graph *self, uint32_t idx)
{
    if(self == NULL || self->_head == NULL)
    {
        return false;
    }

    if(idx >= self->_size || idx >= self->_capacity)
    {
        return false;
    }

    for(uint32_t i = 0; i < self->_size; i++)
    {
        self->_head->visited[i] = 0;
    }
    // printf("bfs start.\n");

    queue_t queue = queue_new(sizeof(uint32_t));

    queue->push(queue, &idx);
    while (!queue->empty(queue))
    {
        queue->pop(queue, &idx);
        self->_head->visited[idx] = 1;
        for(uint32_t i = 0; i < self->_size; i++)
        {
            if(self->_head->edge[idx][i] == 1)
            {
                if(self->_head->visited[i] == 0)
                {
                    queue->push(queue, &i);
                }

                // self->print_obj((char *)self->_head->obj + idx * self->_obj_size);
                // printf("->");
                // self->print_obj((char *)self->_head->obj + i * self->_obj_size);
                // printf(", ");
            }
        }
        // printf("\n");
    }
    queue_free(&queue);
    // printf("bfs done.\n");
    return true;
}

static bool graph_dfs(struct _graph *self, uint32_t idx)
{

}

static bool graph_init2(struct _graph *self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);
    if(self == NULL)
    {
        return false;
    }
    uint32_t edges = 0;

    // -------------------- private -------------------- 
    self->_size = 0;
    self->_obj_size = obj_size;
    self->_capacity = capacity;
    self->_ratio = 1;

    self->_head = (struct _graph_node *)malloc(sizeof(struct _graph_node));
    if(self->_head == NULL)
    {
        goto done;
    }

    self->_head->obj = (void *)malloc(self->_obj_size);
    if(self->_head->obj == NULL)
    {
        goto done1;
    }

    self->_head->edge = (uint32_t **)malloc(self->_capacity * sizeof(uint32_t *));
    if(self->_head->edge == NULL)
    {
        goto done2;
    }

    uint32_t i = 0;
    for(i = 0; i < self->_capacity; i++)
    {
        self->_head->edge[i] = (uint32_t *)malloc(self->_capacity * sizeof(uint32_t));
        if(self->_head->edge[i] == NULL)
        {
            edges += 1;
            goto done3;
        }
    }

    self->_head->visited = (uint8_t *)calloc(1, self->_capacity * sizeof(uint8_t));
    if(self->_head->visited == NULL)
    {
        goto done4;
    }

    self->_destory = graph_destory;

    // -------------------- public -------------------- 
    self->size = graph_size;
    self->capacity = graph_capacity;
    self->clear = graph_clear;

    self->from_matrix = graph_from_matrix;
    self->bfs = graph_bfs;
    self->dfs = graph_dfs;

    // -------------------- debug -------------------- 
    self->print_obj = NULL;
    self->print = graph_print;

    for(uint32_t i = 0; i < self->_capacity; i++)
    {
        *((int *)self->_head->obj + i) = i;
        for(uint32_t j = 0; j < self->_capacity; j++)
        {
            self->_head->edge[i][j] = 0;
        }
    }

    return true;
done4:
done3:
    for(uint32_t j = 0; j < edges; j++)
    {
        free(self->_head->edge[j]);
    }
    free(self->_head->edge);
done2:
    free(self->_head->obj);
done1:
    free(self->_head);
done:
    return false;
}

graph_t graph_new2(uint32_t obj_size, uint32_t capacity)
{
    graph_t graph = NULL;
    graph = malloc(sizeof(struct _graph));
    if(graph == NULL)
    {
        return NULL;
    }

    if(graph_init2(graph, obj_size, capacity) != true)
    {
        free(graph);
        return NULL;
    }
    return graph;
}

void graph_free(graph_t *graph)
{
    if(graph == NULL || *graph == NULL)
    {
        return;
    }

    (*graph)->_destory(*graph);
    free(*graph);
    *graph = NULL;
}
