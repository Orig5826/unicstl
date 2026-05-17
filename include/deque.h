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
#include "ringbuf.h"

struct _deque
{
    // -------------------- private -------------------- 
    union 
    {
        ringbuf_t ringbuf;
    };
    iterator_t _iter_ringbuf;
    
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
    bool (*resize)(struct _deque* self, size_t capacity);
    size_t (*size)(struct _deque* self);
    size_t (*capacity)(struct _deque* self);
    bool (*clear)(struct _deque* self);
    bool (*empty)(struct _deque* self);
    bool (*full)(struct _deque* self);

    // iter
    iterator_t (*iter)(struct _deque* self, linear_order_t order);

    // -------------------- debug -------------------- 
    void (*print)(struct _deque* self);
    void (*print_obj)(const void* obj);
};
typedef struct _deque* deque_t;

deque_t deque_new(size_t obj_size, size_t capacity);
void deque_free(deque_t* deque);

#endif
