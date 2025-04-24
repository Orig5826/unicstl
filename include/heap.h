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

typedef enum
{
    MIN_HEAP = 0, 
    MAX_HEAP = 1,
}heap_type;

struct _heap
{
    // -------------------- private -------------------- 
    void* obj;

    uint32_t _size;
    uint32_t _obj_size;
    uint32_t _capacity;
    uint32_t _ratio;

    heap_type _type;
    bool _min_flag;

    void (*destory)(struct _heap* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*peek)(struct _heap* self, void* obj);
    bool (*push)(struct _heap* self, void* obj);
    bool (*pop)(struct _heap* self, void* obj);
    bool (*empty)(struct _heap* self);

    // default: max heap
    void (*setmin)(struct _heap* self, bool min_flag);

    // base
    uint32_t(*size)(struct _heap* self);
    bool (*clear)(struct _heap* self);
    
    /**
     * @brief obj compare with obj2
     *
     * @return
     *      obj < obj2 return -1
     *      obj == obj2 return 0
     *      obj > obj2 return 1
     */
    int (*compare)(void* obj, void* obj2);
    
    // -------------------- debug -------------------- 
    void (*print)(struct _heap* self);
    void (*print_obj)(void* obj);
};
typedef struct _heap* heap_t;

// create and free heap
heap_t heap_max_new2(uint32_t obj_size, uint32_t capacity);
heap_t heap_min_new2(uint32_t obj_size, uint32_t capacity);

void heap_free(heap_t* heap);

#endif  // _HEAP_H_
