/**
 * @file graph.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _GRAPH_H
#define _GRAPH_H

#include "common.h"

struct _graph_edge
{
    uint32_t weight;
    struct _graph_edge* next;
    void *target;
};

struct _graph_vertex
{
    void* obj;
    struct _graph_vertex* next;
    struct _graph_edge* edges;
    bool visited;
};

struct _graph
{
    // -------------------- private -------------------- 
    struct _graph_vertex* _head;

    uint32_t _size;
    uint32_t _obj_size;
    uint32_t _capacity;
    uint32_t _ratio;

    struct _iterator _iter;
    
    void (*_destory)(struct _graph* self);

    // -------------------- public -------------------- 
    // kernel
    // -> vertex
    bool (*add_vertex)(struct _graph* self, void* obj);
    bool (*del_vertex)(struct _graph* self, void* obj);
    bool (*find_vertex)(struct _graph* self, void* obj);
    // -> edge
    bool (*add_edge)(struct _graph* self, void* from, void* to, uint32_t weight);
    bool (*del_edge)(struct _graph* self, void* from, void* to);
    bool (*find_edge)(struct _graph* self, void* from, void* to);

    // traverse
    bool (*dfs)(struct _graph* self, uint32_t idx);
    bool (*bfs)(struct _graph* self, uint32_t idx);

    bool (*get)(struct _graph* self, uint32_t idx, void* obj);
    bool (*remove)(struct _graph* self, uint32_t idx);

    // base
    uint32_t(*size)(struct _graph* self);
    uint32_t(*capacity)(struct _graph* self);
    bool (*clear)(struct _graph* self);
    bool (*empty)(struct _graph* self);
    bool (*full)(struct _graph* self);

    // iter
    iterator_t (*iter)(struct _graph* self);

    // others
    bool (*from_matrix)(struct _graph* self, void* obj, uint32_t* edges, uint32_t size);

    // -------------------- debug -------------------- 
    void (*print)(struct _graph* self);
    void (*print_obj)(void* obj);
};
typedef struct _graph* graph_t;

graph_t graph_new(uint32_t obj_size);
graph_t graph_new2(uint32_t obj_size, uint32_t capacity);

void graph_free(graph_t* graph);

#endif
