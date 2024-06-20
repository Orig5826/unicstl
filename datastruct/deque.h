
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
    struct _deque_node* _head;  // _head->prev指向头节点、_head->next指向尾节点

    uint32_t _obj_size;			// 元素大小
    uint32_t _size;				// 栈大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率

    // kernel
    bool (*push_back)(struct _deque* self, void* obj);
    bool (*push_front)(struct _deque* self, void* obj);
    bool (*pop_back)(struct _deque* self, void* obj);
    bool (*pop_front)(struct _deque* self, void* obj);
    bool (*back)(struct _deque* self, void* obj);
    bool (*front)(struct _deque* self, void* obj);

    bool (*insert)(struct _deque* self, int index, void* obj);
    bool (*erase)(struct _deque* self, int index, void* obj);

    int (*index)(struct _deque* self, void* obj);
    bool (*remove)(struct _deque* self, void* obj);

    bool (*clear)(struct _deque* self);

    bool (*get)(struct _deque* self, int index, void* obj);
    bool (*set)(struct _deque* self, int index, void* obj);

    // size
    uint32_t(*size)(struct _deque* self);
    bool (*empty)(struct _deque* self);

    // free
    void (*destory)(struct _deque* self);

    // print
    void (*print)(struct _deque* self);
    void (*print_obj)(void* obj);
};

bool deque_init(struct _deque* deque, uint32_t obj_size);

#endif
