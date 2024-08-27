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

#include "common.h"

struct _heap
{
    void * obj;

    uint32_t _size;             // 栈大小
    uint32_t _obj_size;         // 元素大小
    uint32_t _capacity;         // 总容量
    uint32_t _ratio;            // 扩展比率

    bool _min_flag;             // 最大/小堆标志

    // kernel
    bool (*peek)(struct _heap* self, void* obj);
    bool (*push)(struct _heap* self, void* obj);
    bool (*pop)(struct _heap* self, void* obj);

    // default: max heap
    void (*setmin)(struct _heap* self, bool min_flag);

    // base
    uint32_t(*size)(struct _heap* self);
    bool (*empty)(struct _heap* self);

    /**
     * @brief obj compare with obj2
     * 
     * @return
     *      obj < obj2 return -1
     *      obj == obj2 return 0
     *      obj > obj2 return 1
     */
    int (*compare)(void* obj, void* obj2);

    // others
    bool (*clear)(struct _heap* self);
    void (*destory)(struct _heap* self);

    // print
    void (*print)(struct _heap* self);
    void (*print_obj)(void* obj);
};
typedef struct _heap* heap_t;

bool heap_init2(struct _heap* self, uint32_t obj_size, uint32_t capacity);

heap_t heap_new(void);
void heap_free(heap_t* heap);
 
#endif  // _HEAP_H_
