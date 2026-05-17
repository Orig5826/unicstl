/**
 * @file arraylist.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#include "unicstl_internal.h"
#include "iterator.h"
#include "darray.h"

#ifdef UNICSTL_ARRAYLIST
#ifndef _SSIZE_T_DECLARED
typedef ptrdiff_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

struct _arraylist
{
    // -------------------- private --------------------
    darray_t _darray;
    iterator_t _iter_darray;

    struct _iterator _iter;
    void (*_destory)(struct _arraylist *self);

    // -------------------- public --------------------
    // kernel
    bool (*append)(struct _arraylist *self, const void *obj);                  // O(1)
    bool (*pop)(struct _arraylist *self, void *obj);                           // O(1)
    
    bool (*insert)(struct _arraylist *self, ssize_t index, const void *obj);    // O(n)
    bool (*remove)(struct _arraylist *self, ssize_t index, void *obj);          // O(n)

    // -------------------- random access -------------------- 
    bool (*set)(struct _arraylist *self, ssize_t index, const void *obj);       // O(1)
    bool (*get)(struct _arraylist *self, ssize_t index, void *obj);             // O(1)
    const void* (*at)(struct _arraylist *self, ssize_t index);                  // O(1)

    // base
    bool (*resize)(struct _arraylist *self, size_t capacity);
    size_t (*size)(struct _arraylist *self);
    size_t (*capacity)(struct _arraylist *self);
    bool (*empty)(struct _arraylist *self);
    bool (*full)(struct _arraylist *self);
    bool (*clear)(struct _arraylist *self);

    // sort and search
    ssize_t (*index)(struct _arraylist *self, const void *obj);         // O(n) return (size_t)-1 if not found
    bool (*contains)(struct _arraylist *self, const void *obj);         // O(n)

    bool (*sort)(struct _arraylist *self);                              // O(nlogn)
    ssize_t (*search)(struct _arraylist *self, const void *obj);        // O(n) if not sorted; O(logn) if sorted
                                                                        // return leftmost matched index; return (size_t)-1 if not found
    
    size_t (*count)(struct _arraylist *self, const void *obj);          // O(nlogn) if sorted; O(n) if not sorted

    // slice
    bool (*slice)(struct _arraylist *self, ssize_t start, ssize_t end, ssize_t step);    // O(n)

    // iter
    iterator_t (*iter)(struct _arraylist *self, linear_order_t order);

    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _arraylist *self);
    void (*print_obj)(const void *obj);
};
typedef struct _arraylist *arraylist_t;

arraylist_t arraylist_new(size_t obj_size, size_t capacity);
void arraylist_free(arraylist_t *arraylist);

#endif // UNICSTL_ARRAYLIST

#endif // _ARRAYLIST_H_
