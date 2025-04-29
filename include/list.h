/**
 * @file list.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * 
 * @details dynamic array list.
 *      similar to python list/ java ArrayList / C++ std::vector
 * 
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"
#include "iterator.h"

#define LIST_UNLIMITED  INT32_MAX

struct _list
{
    // -------------------- private --------------------
    void *obj;

    uint32_t _obj_size;
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _ratio;
    uint32_t _cur;

    struct _iterator _iter;

    void (*_destory)(struct _list *self);

    // -------------------- public --------------------
    // kernel
    bool (*append)(struct _list *self, void *obj);
    bool (*pop)(struct _list *self, void *obj);
    
    bool (*insert)(struct _list *self, int index, void *obj);
    bool (*delete)(struct _list *self, int index, void *obj);

    bool (*get)(struct _list *self, int index, void *obj);
    bool (*set)(struct _list *self, int index, void *obj);

    int (*index)(struct _list *self, void *obj);        // retval -1 if not found
    // bool (*contains)(struct _list *self, void *obj);

    // base
    uint32_t (*size)(struct _list *self);
    uint32_t (*capacity)(struct _list *self);
    bool (*empty)(struct _list *self);
    bool (*clear)(struct _list *self);

    // iter
    iterator_t (*iter)(struct _list *self);

    // others
    struct _list* (*slice)(struct _list *self, int start, int end, int step);
    // struct _list* (*copy)(struct _list *self);
    
    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _list *self);
    void (*print_obj)(void *obj);
};
typedef struct _list *list_t;

// create and free list
list_t list_new2(uint32_t obj_size, uint32_t capacity);

void list_free(list_t *list);

#endif // _LIST_H_
