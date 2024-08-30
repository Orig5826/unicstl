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

struct _list
{
    void * obj;

    uint32_t _obj_size;			// 元素大小
    uint32_t _size;				// 栈大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率
    uint32_t _cur;              // 当前索引

    // kernel
    bool (*append)(struct _list* self, void* obj);						// Append object to the end of the list.
    bool (*insert)(struct _list* self, int index, void* obj);			// Insert object before index.
    bool (*pop)(struct _list* self, int index, void* obj);				// Remove and return item at index.
    
    int (*index)(struct _list* self, void* obj);						// Return first index of obj. Return -1 if the obj is not present.
    bool (*remove)(struct _list* self, void *obj);						// Remove first occurrence of obj.

    bool (*get)(struct _list* self, int index, void* obj);				// 根据索引，获取对象
    bool (*set)(struct _list* self, int index, void* obj);				// 根据索引，修改对象

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
    bool (*reverse)(struct _list* self);		// Reverse *IN PLACE*.

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

bool list_init2(struct _list* self, uint32_t obj_size, uint32_t capacity);

list_t list_new(void);
void list_free(list_t* list);

#endif // _LIST_H_
