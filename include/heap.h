/**
 * @file heap.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _HEAP_H_
#define _HEAP_H_

#include "unicstl_internal.h"
#include "darray.h"

typedef enum
{
    HEAP_MIN = 0, 
    HEAP_MAX = 1,
}heap_type;

struct _heap
{
    // -------------------- private -------------------- 
    darray_t _darray;

    heap_type _type;
    struct _iterator _iter;

    void (*_destory)(struct _heap* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push)(struct _heap* self, void* obj);
    bool (*pop)(struct _heap* self, void* obj);
    bool (*peek)(struct _heap* self, void* obj);

    // base
    bool (*reserve)(struct _heap* self, size_t capacity);
    size_t (*capacity)(struct _heap* self);
    size_t (*size)(struct _heap* self);
    bool (*empty)(struct _heap* self);
    bool (*clear)(struct _heap* self);

    // iter
    iterator_t (*iter)(struct _heap* self);
    
    // config
    compare_fun_t compare;      // !!! you have to implement this function
    
    // -------------------- debug -------------------- 
    void (*print)(struct _heap* self);
    void (*print_obj)(const void* obj);
};
typedef struct _heap* heap_t;

// create and free heap
heap_t heap_max_new(size_t obj_size, size_t capacity);
heap_t heap_min_new(size_t obj_size, size_t capacity);

void heap_free(heap_t* heap);

#endif  // _HEAP_H_
