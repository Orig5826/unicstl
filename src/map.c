/**
 * @file map.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-05-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "map.h"

struct _map_node* map_node_new(struct _map *self, const char* key, void* value)
{
    struct _map_node* node = (struct _map_node*)malloc(sizeof(struct _map_node));
    if (!node)
    {
        return NULL;
    }
    uint32_t keylen = strlen(key) + 1;
    node->key = (char*)malloc(sizeof(char) * keylen);
    if (!node->key)
    {
        free(node);
        return NULL;
    }

    node->value = malloc(self->_obj_size);
    if (!node->value)
    {
        free(node->key);
        free(node);
        return NULL;
    }
    
    memcpy(node->key, key, keylen);
    memcpy(node->value, value, self->_obj_size);
    return node;
}

static void map_node_free(struct _map_node** node)
{
    if (node != NULL && (*node) != NULL)
    {
        if ((*node)->key != NULL)
        {
            free((*node)->key);
        }
        if ((*node)->value != NULL)
        {
            free((*node)->value);
        }
        free(*node);
        *node = NULL;
    }
}

bool map_clear(struct _map* self)
{
    struct _map_node* node = NULL;
    iterator_t iter = self->_tree->iter(self->_tree, ORDER_IN);
    while(iter->hasnext(&iter))
    {
        // tree & map malloc memory independently, so free them one by one.
        node = (struct _map_node*)iter->next(&iter);
        map_node_free(&node);
    }

    return self->_tree->clear(self->_tree);
}

bool map_empty(struct _map* self)
{
    return self->_tree->empty(self->_tree);
}

uint32_t map_size(struct _map* self)
{
    return self->_tree->size(self->_tree);
}

bool map_insert(struct _map* self, const char* key, void* value)
{
    struct _map_node* node = NULL;
    node = map_node_new(self, key, value);
    if(node == NULL)
    {
        return false;
    }
    return self->_tree->insert(self->_tree, &node);
}

bool map_delete(struct _map* self, const char* key, void* value)
{
    struct _map_node node = {.key = key, .value = value};
    return self->_tree->delete(self->_tree, &node);
}

void map_contains(struct _map* self, const char* key)
{
    // struct _map_node node = {.key = key, .value = NULL};
    // return self->_tree->find(self->_tree, &node);
}

bool map_get(struct _map* self, const char* key, void* value)
{
    // struct _map_node node = {.key = key, .value = NULL};
    // return self->_tree->find(self->_tree, &node);
}

bool map_set(struct _map* self, const char* key, void* value)
{
    return false;
}

bool map_init(struct _map* self, uint32_t obj_size)
{
    assert(self != NULL);
    if(obj_size == 0)
    {
        return false;
    }

    // -------------------- private -------------------- 
    self->_obj_size = obj_size;

    self->_tree = tree_rb_new(sizeof(struct _map_node));
    if(self->_tree == NULL)
    {
        return false;
    }

    // -------------------- public --------------------
    // kernel
    self->insert = map_insert;
    self->delete = map_delete;
    self->contains = map_contains;

    self->get = map_get;
    // self->set = map_set;

    // base
    self->clear = map_clear;
    self->empty = map_empty;
    self->size = map_size;

    // -------------------- default --------------------
    self->compare = default_compare;
    self->print_obj = default_print_obj;
    self->_tree->compare = self->compare;

    return true;
}

bool map_destory(struct _map* self)
{
    self->clear(self);
    if(self->_tree != NULL)
    {
        tree_rb_free(self->_tree);
        self->_tree = NULL;
    }
    return true;
}

map_t map_new(uint32_t obj_size)
{
    map_t map = NULL;
    map = (map_t)malloc(sizeof(struct _map));
    if(map == NULL)
    {
        return NULL;
    }
    if(map_init(map, obj_size) != true)
    {
        free(map);
        return NULL;
    }
    return map;
}

map_t unordered_map_new(uint32_t obj_size)
{
    return NULL;
}

void map_free(map_t self)
{
    map_destory(self);
    free(self);
}