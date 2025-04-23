/**
 * @file list.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"
#include "iter.h"

struct _list
{
    void * obj;

    uint32_t _obj_size;
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _ratio;
    uint32_t _cur;

    struct _iterator _iter;
    iterator_t (*iter)(struct _list* self);

    // kernel
    bool (*append)(struct _list* self, void* obj);                      // Append object to the end of the list.
    bool (*insert)(struct _list* self, int index, void* obj);           // Insert object before index.
    bool (*pop)(struct _list* self, int index, void* obj);              // Remove and return item at index.
    
    int (*index)(struct _list* self, void* obj);                        // Return first index of obj. Return -1 if the obj is not present.
    bool (*remove)(struct _list* self, void *obj);                      // Remove first occurrence of obj.

    bool (*get)(struct _list* self, int index, void* obj);
    bool (*set)(struct _list* self, int index, void* obj);

    // iter
    void* (*begin)(struct _list* self);
    void* (*next)(struct _list* self);
    void* (*end)(struct _list* self);

    // base
    uint32_t(*size)(struct _list* self);
    bool (*empty)(struct _list* self);

    // clear and free node
    bool (*clear)(struct _list* self);
    void (*destory)(struct _list* self);


    // sort
    bool (*reverse)(struct _list* self);        // Reverse *IN PLACE*.

    /**
        Sort the list in ascending order and return false.
        The sort is in-place (i.e. the list itself is modified) and stable (i.e. the
        order of two equal elements is maintained).
        The reverse flag can be set to sort in descending order.
    */
    bool (*sort)(struct _list* self, uint8_t reserve, int (*compare)(void* obj, void* obj2));

    // print
    void (*print)(struct _list* self);
    void (*print_obj)(void* obj);
};
typedef struct _list* list_t;

// create and free list
list_t list_new2(uint32_t obj_size, uint32_t capacity);

void list_free(list_t* list);

#endif // _LIST_H_
