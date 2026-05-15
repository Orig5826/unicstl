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

enum _darray_order
{
    DARRAY_FORWARD,
    DARRAY_REVERSE,
};

struct _darray
{
    // -------------------- private --------------------
    void *obj;

    size_t _obj_size;
    size_t _size;
    size_t _capacity;

    bool _sorted;

    struct _iterator _iter;
    void (*_destory)(struct _darray *self);

    // -------------------- public --------------------
    // kernel
    bool (*append)(struct _darray *self, const void *obj);                  // O(1)
    bool (*pop)(struct _darray *self, void *obj);                           // O(1)
    
    bool (*insert)(struct _darray *self, size_t index, const void *obj);    // O(n)
    bool (*remove)(struct _darray *self, size_t index, void *obj);          // O(n)

    // -------------------- random access -------------------- 
    bool (*set)(struct _darray *self, size_t index, const void *obj);       // O(1)
    bool (*get)(struct _darray *self, size_t index, void *obj);             // O(1)
    const void* (*at)(struct _darray *self, size_t index);                  // O(1)

    // base
    bool (*resize)(struct _darray *self, size_t capacity);
    size_t (*size)(struct _darray *self);
    size_t (*capacity)(struct _darray *self);
    bool (*empty)(struct _darray *self);
    bool (*full)(struct _darray *self);
    bool (*clear)(struct _darray *self);

    // sort and search
    size_t (*index)(struct _darray *self, const void *obj);         // O(n) return (size_t)-1 if not found
    bool (*contains)(struct _darray *self, const void *obj);        // O(n)

    bool (*sort)(struct _darray *self);                                 // O(nlogn)
    size_t (*search)(struct _darray *self, const void *obj);            // O(n) if not sorted; O(logn) if sorted
                                                                        // return leftmost matched index; return (size_t)-1 if not found
    
    size_t (*count)(struct _darray *self, const void *obj);         // O(nlogn) if sorted; O(n) if not sorted

    // iter
    iterator_t (*iter)(struct _darray *self, enum _darray_order order);

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
