
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
    struct _deque_node* _head;

    uint32_t _obj_size;			// 元素大小
    uint32_t _size;				// 栈大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率

    // kernel
    bool (*push_back)(struct _list* self, void* obj);
    bool (*push_front)(struct _list* self, void* obj);
    bool (*pop_back)(struct _list* self, void* obj);
    bool (*pop_front)(struct _list* self, void* obj);
    bool (*back)(struct _list* self, void* obj);
    bool (*front)(struct _list* self, void* obj);

    bool (*insert)(struct _list* self, int index, void* obj);
    bool (*erase)(struct _list* self, int index, void* obj);

    int (*index)(struct _list* self, void* obj);
    bool (*remove)(struct _list* self, void* obj);

    bool (*clear)(struct _list* self);

    bool (*get)(struct _list* self, int index, void* obj);
    bool (*set)(struct _list* self, int index, void* obj);

    // size
    uint32_t(*size)(struct _list* self);
    bool (*empty)(struct _list* self);

    // free
    void (*destory)(struct _list* self);

    // print
    void (*print)(struct _list* self);
    void (*print_obj)(void* obj);
};

bool deque_init(struct _deque* deque, uint32_t obj_size);

#endif
