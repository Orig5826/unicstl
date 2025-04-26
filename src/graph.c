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

#if 0
static uint32_t graph_size(struct _graph* self)
{
    if (self == NULL)
    {
        return 0;
    }
    return self->_size;
}

static uint32_t graph_capacity(struct _graph* self)
{
    if (self == NULL)
    {
        return 0;
    }
    return self->_capacity;
}

static bool graph_clear(struct _graph* self)
{
    if (self == NULL && self->_head == NULL)
    {
        return 0;
    }
    for (uint32_t i = 0; i < self->_capacity; i++)
    {
        for (uint32_t j = 0; j < self->_capacity; j++)
        {
            self->_head->edge[i][j] = 0;
        }
    }
    self->_size = 0;
    return self->_size = 0;
}

static void graph_destory(struct _graph* self)
{
    if (self == NULL)
    {
        return;
    }
    self->clear(self);
    if (self->_head != NULL)
    {
        if (self->_head->visited != NULL)
        {
            free(self->_head->visited);
        }

        if (self->_head->obj != NULL)
        {
            free(self->_head->obj);
        }

        if (self->_head->edge != NULL)
        {
            for (uint32_t i = 0; i < self->_capacity; i++)
            {
                if (self->_head->edge[i] != NULL)
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

static void graph_print(struct _graph* self)
{
    if (self == NULL || self->_head == NULL || self->print_obj == NULL)
    {
        return;
    }

    printf("\n     ");
    for (uint32_t i = 0; i < self->_capacity; i++)
    {
        self->print_obj((char*)self->_head->obj + i * self->_obj_size);
    }
    printf("\n");
    for (uint32_t i = 0; i < self->_capacity; i++)
    {
        self->print_obj((char*)self->_head->obj + i * self->_obj_size);
        for (uint32_t j = 0; j < self->_capacity; j++)
        {
            printf(" %2d   ", self->_head->edge[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("print done.\n");
}

static bool graph_from_matrix(struct _graph* self, void* obj, uint32_t* edges, uint32_t size)
{
    if (self == NULL || self->_head == NULL)
    {
        return false;
    }

    if (size > self->_capacity || obj == NULL || edges == NULL)
    {
        return false;
    }

    for (uint32_t i = 0; i < size; i++)
    {
        memmove((char*)self->_head->obj + i * self->_obj_size, (char*)obj + i * self->_obj_size, self->_obj_size);
    }
    for (uint32_t i = 0; i < size; i++)
    {
        for (uint32_t j = 0; j < size; j++)
        {
            self->_head->edge[i][j] = edges[i * size + j];
        }
    }

    self->_size = size;
    return true;
}

static bool graph_bfs(struct _graph* self, uint32_t idx)
{
    if (self == NULL || self->_head == NULL)
    {
        return false;
    }

    if (idx >= self->_size || idx >= self->_capacity)
    {
        return false;
    }

    for (uint32_t i = 0; i < self->_size; i++)
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
        for (uint32_t i = 0; i < self->_size; i++)
        {
            if (self->_head->edge[idx][i] == 1)
            {
                if (self->_head->visited[i] == 0)
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

static bool graph_dfs(struct _graph* self, uint32_t idx)
{

}

static bool graph_init2(struct _graph* self, uint32_t obj_size, uint32_t capacity)
{
    assert(self != NULL);
    if (self == NULL)
    {
        return false;
    }
    uint32_t edges = 0;

    // -------------------- private -------------------- 
    self->_size = 0;
    self->_obj_size = obj_size;
    self->_capacity = capacity;
    self->_ratio = 1;

    self->_head = (struct _graph_node*)malloc(sizeof(struct _graph_node));
    if (self->_head == NULL)
    {
        goto done;
    }

    self->_head->obj = (void*)malloc(self->_obj_size);
    if (self->_head->obj == NULL)
    {
        goto done1;
    }

    self->_head->edge = (uint32_t**)malloc(self->_capacity * sizeof(uint32_t*));
    if (self->_head->edge == NULL)
    {
        goto done2;
    }

    uint32_t i = 0;
    for (i = 0; i < self->_capacity; i++)
    {
        self->_head->edge[i] = (uint32_t*)malloc(self->_capacity * sizeof(uint32_t));
        if (self->_head->edge[i] == NULL)
        {
            edges += 1;
            goto done3;
        }
    }

    self->_head->visited = (uint8_t*)calloc(1, self->_capacity * sizeof(uint8_t));
    if (self->_head->visited == NULL)
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

    for (uint32_t i = 0; i < self->_capacity; i++)
    {
        *((int*)self->_head->obj + i) = i;
        for (uint32_t j = 0; j < self->_capacity; j++)
        {
            self->_head->edge[i][j] = 0;
        }
    }

    return true;
done4:
done3:
    for (uint32_t j = 0; j < edges; j++)
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
    if (graph == NULL)
    {
        return NULL;
    }

    // if(graph_init2(graph, obj_size, capacity) != true)
    // {
    //     free(graph);
    //     return NULL;
    // }
    return graph;
}

void graph_free(graph_t* graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }

    (*graph)->_destory(*graph);
    free(*graph);
    *graph = NULL;
}

#endif

static struct _graph_node *graph_node_new(void *obj, uint32_t obj_size)
{
    void *new_obj = (void *)calloc(1, obj_size);
    if (new_obj == NULL)
    {
        return NULL;
    }
    memmove(new_obj, obj, obj_size);

    struct _graph_node *new_node = (struct _graph_node *)malloc(sizeof(struct _graph_node));
    if (new_node == NULL)
    {
        free(new_obj);
        return NULL;
    }
    new_node->obj = new_obj;
    new_node->next = NULL;
    new_node->edgehead = NULL;
    new_node->visited = false;

    return new_node;
}

static void greph_node_free(struct _graph_node **node)
{
    if (node != NULL && *node != NULL)
    {
        if ((*node)->obj != NULL)
        {
            free((*node)->obj);
            (*node)->obj = NULL;
        }

        if ((*node)->edgehead != NULL)
        {
            free((*node)->edgehead);
            (*node)->edgehead = NULL;
        }

        free(*node);

        *node = NULL;
    }
}

static struct _graph_edge *graph_edge_new(void *target, uint32_t weight)
{
    struct _graph_edge *new_edge = (struct _graph_edge *)malloc(sizeof(struct _graph_edge));
    if (new_edge == NULL)
    {
        return NULL;
    }
    new_edge->next = NULL;
    new_edge->weight = weight;
    new_edge->target = target;
    return new_edge;
}

static void graph_edge_free(struct _graph_edge **edge)
{
    if (edge != NULL && *edge != NULL)
    {
        free(*edge);
        *edge = NULL;
    }
}

static uint32_t graph_size(struct _graph *self)
{
    if (self == NULL)
    {
        return 0;
    }
    return self->_size;
}

static bool graph_empty(struct _graph *self)
{
    if (self == NULL)
    {
        return 0;
    }
    return self->size(self) == 0;
}

static uint32_t graph_capacity(struct _graph *self)
{
    if (self == NULL)
    {
        return 0;
    }
    return self->_capacity;
}

static bool graph_clear(struct _graph *self)
{
    if (self == NULL && self->_head == NULL)
    {
        return 0;
    }

    struct _graph_node *cur = self->_head->next;
    struct _graph_node *next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        greph_node_free(&cur);
        cur = next;
    }

    self->_head->next = NULL;
    self->_size = 0;
    return true;
}

static void graph_destory(struct _graph *self)
{
    if (self == NULL)
    {
        return;
    }
    self->clear(self);
    if (self->_head != NULL)
    {
        free(self->_head);
        self->_head = NULL;
    }

    if (self->stack != NULL)
    {
        stack_free(&self->stack);
    }
    if (self->queue != NULL)
    {
        queue_free(&self->queue);
    }
}

static void graph_print(struct _graph *self)
{
    if (self == NULL || self->_head == NULL || self->print_obj == NULL)
    {
        return;
    }

    printf("\nvertex : \n");
    struct _graph_node *cur = self->_head->next;
    while (cur != NULL)
    {
        self->print_obj(cur->obj);
        cur = cur->next;
    }
    printf("\n");

    printf("edge : \n");
    cur = self->_head->next;
    while (cur != NULL)
    {
        if (cur->edgehead != NULL)
        {
            struct _graph_edge *edge = cur->edgehead;
            while (edge != NULL)
            {
                struct _graph_node *target = (struct _graph_node *)edge->target;

                // printf("from ");
                self->print_obj(cur->obj);
                // printf(" to ");
                printf("--> ");
                self->print_obj(target->obj);
                printf(": %d \n", edge->weight);

                edge = edge->next;
            }
        }
        cur = cur->next;
    }
    printf("\n");
    printf("print done.\n");
}

static bool graph_add_vertex(struct _graph *self, void *obj)
{
    assert(self != NULL);
    if (self->_head->next == NULL)
    {
        // no vertex
        struct _graph_node *new_node = graph_node_new(obj, self->_obj_size);
        if (new_node == NULL)
        {
            return false;
        }
        self->_head->next = new_node;
    }
    else
    {
        struct _graph_node *cur = self->_head->next;

        // find if exist
        while (cur != NULL)
        {
            if (self->compare(cur->obj, obj) == 0)
            {
                return true;
            }
            cur = cur->next;
        }

        struct _graph_node *new_node = graph_node_new(obj, self->_obj_size);
        if (new_node == NULL)
        {
            return false;
        }

        // add to tail
        cur = self->_head->next;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_node;
    }

    self->_size++;
    return true;
}

static bool graph_del_vertex(struct _graph *self, void *obj)
{
    assert(self != NULL);
    if (obj == NULL)
    {
        return false;
    }
    if (self->empty(self))
    {
        return false;
    }

    struct _graph_node *cur = self->_head->next;
    struct _graph_node *pre = self->_head;
    while (cur != NULL)
    {
        if (self->compare(cur->obj, obj) == 0)
        {
            pre->next = cur->next;
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    if (cur == NULL)
    {
        return false;
    }

    greph_node_free(&cur);
    self->_size--;
    return true;
}

static bool graph_find_vertex(struct _graph *self, void *obj)
{
    assert(self != NULL);
    if (obj == NULL)
    {
        return false;
    }
    if (self->empty(self))
    {
        return false;
    }
    struct _graph_node *cur = self->_head->next;
    while (cur != NULL)
    {
        if (self->compare(cur->obj, obj) == 0)
        {
            // obj is found
            break;
        }
        cur = cur->next;
    }

    return cur == NULL ? false : true;
}

static struct _graph_node *find_node(struct _graph *self, void *obj)
{
    struct _graph_node *cur = self->_head->next;
    while (cur != NULL)
    {
        if (self->compare(cur->obj, obj) == 0)
        {
            // obj is found
            break;
        }
        cur = cur->next;
    }
    return cur;
}

static bool graph_add_edge(struct _graph *self, void *from, void *to, uint32_t weight)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }

    struct _graph_node *from_node = self->_head->next;
    struct _graph_node *to_node = self->_head->next;
    from_node = find_node(self, from);
    if (from_node == NULL)
    {
        return false;
    }

    to_node = find_node(self, to);
    if (to_node == NULL)
    {
        return false;
    }

    // from_node add edge
    struct _graph_edge *new_edge = graph_edge_new(to_node, weight);
    if (new_edge == NULL)
    {
        return false;
    }
    if (from_node->edgehead == NULL)
    {
        from_node->edgehead = new_edge;
    }
    else
    {
        new_edge->next = from_node->edgehead->next;
        from_node->edgehead->next = new_edge;
    }

    if (self->_type == GRAPH_UNDIRECTED)
    {
        // if graph is undirected
        // to_node add edge
        struct _graph_edge *new_edge2 = graph_edge_new(from_node, weight);
        if (new_edge2 == NULL)
        {
            return false;
        }

        if (to_node->edgehead == NULL)
        {
            to_node->edgehead = new_edge2;
        }
        else
        {
            new_edge2->next = to_node->edgehead->next;
            to_node->edgehead->next = new_edge2;
        }
    }

    return true;
}

static bool graph_del_edge(struct _graph *self, void *from, void *to)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }

    struct _graph_node *from_node = self->_head->next;
    struct _graph_node *to_node = self->_head->next;
    from_node = find_node(self, from);
    if (from_node == NULL)
    {
        return false;
    }

    to_node = find_node(self, to);
    if (to_node == NULL)
    {
        return false;
    }

    struct _graph_edge *cur = from_node->edgehead;
    struct _graph_edge *pre = from_node->edgehead;
    while (cur != NULL)
    {
        if (cur->target == to_node)
        {
            pre->next = cur->next;
            if (pre == cur)
            {
                from_node->edgehead = cur->next;
            }
            graph_edge_free(&cur);
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if (self->_type == GRAPH_UNDIRECTED)
    {
        struct _graph_edge *cur2 = to_node->edgehead;
        struct _graph_edge *pre2 = to_node->edgehead;
        while (cur2 != NULL)
        {
            if (cur2->target == from_node)
            {
                pre2->next = cur2->next;
                if (pre2 == cur2)
                {
                    to_node->edgehead = cur2->next;
                }
                graph_edge_free(&cur2);
                break;
            }
            pre2 = cur2;
            cur2 = cur2->next;
        }
    }
    return true;
}

static bool graph_find_edge(struct _graph *self, void *from, void *to)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }
    struct _graph_node *from_node = self->_head->next;
    struct _graph_node *to_node = self->_head->next;
    from_node = find_node(self, from);
    if (from_node == NULL)
    {
        return false;
    }

    to_node = find_node(self, to);
    if (to_node == NULL)
    {
        return false;
    }

    struct _graph_edge *cur = from_node->edgehead;
    while (cur != NULL)
    {
        if (cur->target == to_node)
        {
            // found edge
            break;
        }
        cur = cur->next;
    }
    if (cur == NULL)
    {
        return false;
    }
    return true;
}

static struct _graph_node * graph_find_unvisited_vertex(struct _graph *self)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return false;
    }

    struct _graph_node *node = self->_head->next;
    while(node != NULL)
    {
        if(node->visited == false)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

static struct _graph_node * graph_find_next_unvisited_target(struct _graph *self, struct _graph_node *node)
{
    assert(self != NULL);
    if (self->empty(self))
    {
        return NULL;
    }

    if(node == NULL)
    {
        return NULL;
    }

    struct _graph_edge *edge = node->edgehead;
    struct _graph_node *target = NULL;
    while(edge != NULL)
    {
        target = edge->target;
        if(target != NULL && target->visited != true)
        {
            return target;
        }
        edge = edge->next;
    }

    return NULL;
}

iterator_t graph_iter(struct _graph *self, enum _graph_search search_type, void *start)
{
    assert(self != NULL);
    iterator_t iter = &self->_iter;

    iter->_parent = self;
    iter->_cur = 0;
    iter->_cur_node = self->_head->next;

    struct _graph_node *start_node = find_node(self, start);
    if (start_node == NULL)
    {
        goto done;
    }
    iter->_cur_node = start_node;

    struct _graph_node *node = self->_head->next;
    while (node != NULL)
    {
        node->visited = false;
        node = node->next;
    }

    self->_search = search_type;
    switch (self->_search)
    {
    case GRAPH_BFS:
    {
        self->queue->push(self->queue, &iter->_cur_node);
    }
    break;
    case GRAPH_DFS:
    {
        // pass
    }
    break;
    default:
    {
    }
    break;
    }

done:
    return iter;
}

bool graph_iter_hasnext(struct _iterator *iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    graph_t self = (graph_t)iter->_parent;
    if (iter->_cur < self->size(self))
    {
        return true;
    }
    return false;
}

const void *graph_iter_next(struct _iterator *iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);

    graph_t self = (graph_t)iter->_parent;
    void *obj = NULL;

    iter->_cur += 1;
    switch (self->_search)
    {
    case GRAPH_BFS:
    {
        struct _graph_node *cur_node = iter->_cur_node;
        struct _graph_edge *cur_edge = cur_node->edgehead;
        struct _graph_node *target = NULL;
        struct _graph_node *node = cur_node;

        queue_t queue = self->queue;

        // 3. [graph special] if queue is empty, find a new root node
        if (queue->empty(queue))
        {
            cur_node = graph_find_unvisited_vertex(self);
            if(cur_node != NULL)
            {
                queue->push(queue, &cur_node);
            }
        }

        // graph->BFS : similar to breadth-first traversal of a tree
        if (!queue->empty(queue) && node != NULL)
        {
            // 1. pop the root vertex from queue
            queue->pop(queue, &node);
            node->visited = true;

            // 2. find all unvisited target node and push them to queue
            cur_edge = node->edgehead;
            while (cur_edge != NULL)
            {
                target = cur_edge->target;
                if (target != NULL && target->visited != true)
                {
                    queue->push(queue, &target);
                }
                cur_edge = cur_edge->next;
            }

            cur_node = node;
        }

        iter->_cur_node = cur_node;
        obj = cur_node->obj;
    }
    break;
    case GRAPH_DFS:
    {
        // self->stack->push(self->stack, iter->_cur_node);
        struct _graph_node *cur_node = self->_iter._cur_node;
        struct _graph_node *node = NULL;

        stack_t stack = self->stack;

        // graph->DFS : similar to the preorder traversal of a tree
        while (!self->stack->empty(self->stack) || cur_node != NULL)
        {
            if (cur_node != NULL)
            {
                // 1. get current node
                node = cur_node;

                // 2. push current node to stack
                self->stack->push(self->stack, &cur_node);
                cur_node->visited = true;

                // 3. find unvisited target node
                cur_node = graph_find_next_unvisited_target(self, cur_node);
                break;
            }
            else
            {
                // 4. if cur_node is NULL, pop from stack and find unvisited target node
                self->stack->pop(self->stack, &cur_node);

                // 5. find unvisited target node
                cur_node = graph_find_next_unvisited_target(self, cur_node);

                // 6. [graph special] If the graph contains isolated vertices
                if(cur_node == NULL)
                {
                    cur_node = graph_find_unvisited_vertex(self);
                }
            }
        }
        iter->_cur_node = cur_node;
        obj = node->obj;
    }
    break;
    default:
    {
    }
    break;
    }

    return obj;
}

static bool graph_init(struct _graph *self, uint32_t obj_size)
{
    assert(self != NULL);
    if (self == NULL)
    {
        return false;
    }

    // -------------------- private --------------------
    self->_size = 0;
    self->_obj_size = obj_size;
    self->_capacity = UINT32_MAX;
    self->_ratio = 1;

    self->stack = stack_new(sizeof(struct _graph_node *));
    if (self->stack == NULL)
    {
        return false;
    }
    self->queue = queue_new(sizeof(struct _graph_node *));
    if (self->queue == NULL)
    {
        stack_free(&self->stack);
        return false;
    }

    self->_head = (struct _graph_node *)malloc(sizeof(struct _graph_node));
    if (self->_head == NULL)
    {
        stack_free(&self->stack);
        queue_free(&self->queue);
        return false;
    }
    self->_head->visited = false;
    self->_head->obj = NULL;
    self->_head->edgehead = NULL;
    self->_head->next = NULL;

    self->_type = GRAPH_UNDIRECTED;
    // self->_type = GRAPH_DIRECTED;

    self->_iter.hasnext = graph_iter_hasnext;
    self->_iter.next = graph_iter_next;

    self->_destory = graph_destory;

    // -------------------- public --------------------
    // kernel
    // -> vertex
    self->add_vertex = graph_add_vertex;
    self->del_vertex = graph_del_vertex;
    self->find_vertex = graph_find_vertex;
    // -> edge
    self->add_edge = graph_add_edge;
    self->del_edge = graph_del_edge;
    self->find_edge = graph_find_edge;

    // base
    self->size = graph_size;
    self->clear = graph_clear;
    self->empty = graph_empty;
    self->capacity = graph_capacity;

    // iter
    self->iter = graph_iter;

    // others
    self->from_matrix = NULL;


    self->compare = NULL;
    // -------------------- debug --------------------
    self->print_obj = NULL;
    self->print = graph_print;

    return true;
}

graph_t graph_new(uint32_t obj_size)
{
    graph_t graph = NULL;
    graph = malloc(sizeof(struct _graph));
    if (graph == NULL)
    {
        return NULL;
    }

    if (graph_init(graph, obj_size) != true)
    {
        free(graph);
        return NULL;
    }
    return graph;
}

void graph_free(graph_t *graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }

    (*graph)->_destory(*graph);
    free(*graph);
    *graph = NULL;
}
