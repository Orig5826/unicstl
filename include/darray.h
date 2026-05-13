/**
 * @file darray.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _DARRAY_H_
#define _DARRAY_H_

#include "unicstl_internal.h"
#include "iterator.h"

struct _darray
{
    // -------------------- private --------------------
    void *obj;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;

    struct _iterator _iter;
    void (*_destory)(struct _darray *self);

    // -------------------- public --------------------
    // kernel
    bool (*append)(struct _darray *self, const void *obj);              // O(1)
    bool (*pop)(struct _darray *self, void *obj);                       // O(1)
    
    bool (*insert)(struct _darray *self, size_t index, const void *obj);   // O(n)
    bool (*remove)(struct _darray *self, size_t index, void *obj);         // O(n)

    bool (*set)(struct _darray *self, size_t index, const void *obj);      // O(1)
    bool (*get)(struct _darray *self, size_t index, void *obj);            // O(1)

    const void* (*at)(struct _darray *self, size_t index);                // O(1)

    size_t (*index)(struct _darray *self, const void *obj);        // O(n) retval -1 if not found
    bool (*contains)(struct _darray *self, const void *obj);    // O(n)

    // base
    bool (*resize)(struct _darray *self, size_t capacity);
    size_t (*size)(struct _darray *self);
    size_t (*capacity)(struct _darray *self);
    bool (*empty)(struct _darray *self);
    bool (*full)(struct _darray *self);
    bool (*clear)(struct _darray *self);

    // iter
    iterator_t (*iter)(struct _darray *self);

    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _darray *self);
    void (*print_obj)(const void *obj);
};
typedef struct _darray *darray_t;

darray_t darray_new(size_t obj_size, size_t capacity);
void darray_free(darray_t *darray);

#endif
