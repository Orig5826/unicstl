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

#include "unicstl_internal.h"

#include "stack.h"
#include "queue.h"

enum _graph_type
{
    GRAPH_UNDIRECTED,
    GRAPH_DIRECTED,
    // GRAPH_UNDIRECTED_WEIGHT,
    // GRAPH_DIRECTED_WEIGHT,
};

enum _graph_search
{
    GRAPH_DFS,
    GRAPH_BFS,
};


struct _graph_edge
{
    size_t weight;
    struct _graph_edge* next;
    void *target;
};

struct _graph_node
{
    void* obj;
    struct _graph_node* next;

    bool visited;
    struct _graph_edge* edgehead;
};

struct _graph
{
    // -------------------- private -------------------- 
    struct _graph_node* _head;

    size_t _size;
    size_t _obj_size;
    size_t _capacity;
    size_t _ratio;

    enum _graph_type _type;
    enum _graph_search _search;

    stack_t stack;
    queue_t queue;

    struct _iterator _iter;

    void (*_destory)(struct _graph* self);

    // -------------------- public -------------------- 
    // kernel
    // -> vertex
    bool (*add_vertex)(struct _graph* self, void* obj);
    bool (*del_vertex)(struct _graph* self, void* obj);
    bool (*find_vertex)(struct _graph* self, void* obj);
    // -> edge
    bool (*add_edge)(struct _graph* self, void* from, void* to, size_t weight);
    bool (*del_edge)(struct _graph* self, void* from, void* to);
    bool (*find_edge)(struct _graph* self, void* from, void* to);

    // base
    size_t(*size)(struct _graph* self);
    size_t(*capacity)(struct _graph* self);
    bool (*empty)(struct _graph* self);
    bool (*full)(struct _graph* self);
    bool (*clear)(struct _graph* self);

    // iter
    iterator_t (*iter)(struct _graph* self, enum _graph_search search, void *obj);

    // config 
    compare_fun_t compare;  // !!! you have to implement this function

    // others
    bool (*from_matrix)(struct _graph* self, void* obj, size_t* edges, size_t size);

    // -------------------- debug -------------------- 
    void (*print)(struct _graph* self);
    void (*print_obj)(const void* obj);
};
typedef struct _graph* graph_t;

graph_t graph_new(size_t obj_size);
// graph_t graph_new2(size_t obj_size, size_t capacity);

void graph_free(graph_t* graph);

#endif
