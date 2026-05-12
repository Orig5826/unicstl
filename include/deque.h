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

#include "unicstl_internal.h"

enum _deque_order
{
    DEQUE_FORWARD,
    DEQUE_REVERSE,
};

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

    size_t _obj_size;
    size_t _size;
    // size_t _capacity;
    // size_t _ratio;

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
    
    // base
    size_t(*size)(struct _deque* self);
    bool (*clear)(struct _deque* self);
    bool (*empty)(struct _deque* self);

    // iter
    iterator_t (*iter)(struct _deque* self, enum _deque_order order);

    // -------------------- debug -------------------- 
    void (*print)(struct _deque* self);
    void (*print_obj)(const void* obj);
};
typedef struct _deque* deque_t;

// create and free deque
deque_t deque_new(size_t obj_size);

void deque_free(deque_t* deque);

#endif
