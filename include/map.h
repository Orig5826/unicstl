/**
 * @file map.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _MAP_H_
#define _MAP_H_

#include "unicstl_internal.h"
#include "tree.h"

struct _map_node
{
    char* key;
    void* value;
};

struct _map
{
    // -------------------- private -------------------- 
    tree_t _tree;

    // uint32_t _size;
    uint32_t _obj_size;
    // uint32_t _capacity;
    // uint32_t _ratio;

    // -------------------- public -------------------- 
    // kernel
    bool (*insert)(struct _map* self, const char* key, void* value);
    bool (*delete)(struct _map* self, const char* key, void* value);
    void (*contains)(struct _map* self, const char* key);
    bool (*get)(struct _map* self, const char* key, void* value);
    // bool (*set)(struct _map* self, const char* key, void* value);

    // base
    bool (*clear)(struct _map* self);
    bool (*empty)(struct _map* self);
    uint32_t(*size)(struct _map* self);

    // iter
    iterator_t(*iter)(struct _map* self, enum _tree_order);

    // config 
    compare_fun_t compare;  // !!! you have to implement this function

    // -------------------- debug -------------------- 
    void (*print_obj)(void* obj);
};
typedef struct _map* map_t;

map_t map_new(uint32_t obj_size);           // obj_size is the size of value
map_t unordered_map_new(uint32_t obj_size);

void map_free(map_t self);

#endif
