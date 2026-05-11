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

    uint32_t _obj_size;
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _ratio;
    uint32_t _cur;

    struct _iterator _iter;

    void (*_destory)(struct _darray *self);

    // -------------------- public --------------------
    // kernel
    bool (*resize)(struct _darray *self, uint32_t capacity);

    bool (*append)(struct _darray *self, const void *obj);
    bool (*pop)(struct _darray *self, void *obj);
    
    bool (*insert)(struct _darray *self, int index, const void *obj);
    bool (*remove)(struct _darray *self, int index, void *obj);

    bool (*set)(struct _darray *self, int index, const void *obj);
    bool (*get)(struct _darray *self, int index, void *obj);

    int (*index)(struct _darray *self, const void *obj);        // retval -1 if not found
    bool (*contains)(struct _darray *self, const void *obj);

    // base
    uint32_t (*size)(struct _darray *self);
    uint32_t (*capacity)(struct _darray *self);
    bool (*empty)(struct _darray *self);
    bool (*full)(struct _darray *self);
    bool (*clear)(struct _darray *self);

    void (*dynamic_enable)(struct _darray *self, bool enable);
    bool (*dynamic)(struct _darray *self);

    // iter
    iterator_t (*iter)(struct _darray *self);

    // config
    compare_fun_t compare;      // !!! you have to implement this function

    // -------------------- debug --------------------
    void (*print)(struct _darray *self);
    void (*print_obj)(void *obj);
};
typedef struct _darray *darray_t;

darray_t darray_new(uint32_t obj_size, uint32_t capacity);
void darray_free(darray_t *darray);

#endif
