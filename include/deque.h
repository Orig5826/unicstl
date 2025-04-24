/**
 * @file deque.h
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "common.h"

struct _deque_node
{
    void* obj;
    struct _deque_node* prev;
    struct _deque_node* next;
};

struct _deque
{
    // -------------------- private -------------------- 
    struct _deque_node* _head;
    struct _deque_node* _tail;

    uint32_t _obj_size;
    uint32_t _size;
    // uint32_t _capacity;
    // uint32_t _ratio;

    struct _iterator _iter;

    void (*_destory)(struct _deque* self);

    // -------------------- public -------------------- 
    // kernel
    bool (*push_back)(struct _deque* self, void* obj);
    bool (*push_front)(struct _deque* self, void* obj);
    bool (*pop_back)(struct _deque* self, void* obj);
    bool (*pop_front)(struct _deque* self, void* obj);
    bool (*back)(struct _deque* self, void* obj);
    bool (*front)(struct _deque* self, void* obj);
    bool (*empty)(struct _deque* self);

    // base
    uint32_t(*size)(struct _deque* self);
    bool (*clear)(struct _deque* self);

    // iter
    iterator_t (*iter)(struct _deque* self);

    // ohters
    bool (*insert)(struct _deque* self, int index, void* obj);
    bool (*erase)(struct _deque* self, int index, void* obj);

    int (*index)(struct _deque* self, void* obj);
    bool (*remove)(struct _deque* self, void* obj);

    bool (*get)(struct _deque* self, int index, void* obj);
    bool (*set)(struct _deque* self, int index, void* obj);

    // compare
    int (*cmp)(void* obj, void* obj2);
    bool (*sort)(struct _deque* self, uint8_t reserve);

    // -------------------- debug -------------------- 
    void (*print)(struct _deque* self);
    void (*print_obj)(void* obj);
};
typedef struct _deque* deque_t;

// create and free deque
deque_t deque_new(uint32_t obj_size);

void deque_free(deque_t* deque);

#endif
