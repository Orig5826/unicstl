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

struct _graph_node {
    void *obj;
    uint32_t **edge;
};

struct _graph {
    struct _graph_node *_head;
    uint32_t **edges;

    uint32_t _size;
    uint32_t _obj_size;
    uint32_t _capacity;
    uint32_t _ratio;

    // init
    void (*init)(struct _graph *self);

    // kernel
    bool (*add)(struct _graph *self, void *obj);
    bool (*get)(struct _graph *self, uint32_t idx, void *obj);
    bool (*remove)(struct _graph *self, uint32_t idx);
    
    // base
    uint32_t (*size)(struct _graph *self);
    uint32_t (*capacity)(struct _graph *self);

    bool (*empty)(struct _graph *self);
    bool (*full)(struct _graph *self);

    // 
    bool (*clear)(struct _graph *self);
    void (*destory)(struct _graph *self);
};
typedef struct _graph* graph_t;

graph_t graph_new2(uint32_t obj_size, uint32_t capacity);
void graph_free(graph_t *graph);

#endif
