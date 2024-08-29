/**
 * @file queue.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "common.h"

struct _queue_node
{
    void  *obj;
    struct _queue_node * next;
};

struct _queue
{
    struct _queue_node * _front;
    struct _queue_node * _back;

    uint32_t _index_front;
    uint32_t _index_back;

    uint32_t _obj_size;			// 元素大小
    uint32_t _size;				// 栈大小
    uint32_t _capacity;			// 总容量
    uint32_t _ratio;			// 扩展比率

    // kernel
    bool (*push)(struct _queue* self, void* obj);
    bool (*pop)(struct _queue* self, void* obj);

    bool (*back)(struct _queue* self, void* obj);
    bool (*front)(struct _queue* self, void* obj);

    // base
    bool (*empty)(struct _queue* self);
    bool (*full)(struct _queue* self);
    uint32_t (*size)(struct _queue* self);
    uint32_t (*capacity)(struct _queue* self);
    
    // clear and free node
    bool (*clear)(struct _queue* self);
    void (*destory)(struct _queue* self);

    // print
    void (*print)(struct _queue* self);
    void (*print_obj)(void* obj);
};
typedef struct _queue* queue_t;

bool queue_init(struct _queue* self, uint32_t obj_size);
bool queue_init2(struct _queue* self, uint32_t obj_size, uint32_t capacity);

queue_t queue_new(void);
void queue_free(queue_t* queue);

#endif // _QUEUE_H_
