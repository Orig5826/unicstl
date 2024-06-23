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

#if QUEUE == 1
// typedef int queue_data_t;

// node of queue
typedef struct _queue_node_t
{
    queue_data_t data;
    struct _queue_node_t * next;
} queue_node_t, *pqueue_node_t;

// queue
typedef struct _queue_t
{
    struct _queue_node_t * front;
    struct _queue_node_t * rear;
    uint32_t size;
}queue_t,*pqueue_t;


bool queue_init(pqueue_t * head);
void queue_destroy(pqueue_t * head);
bool queue_empty(pqueue_t head);
void queue_clear(pqueue_t head);
uint32_t queue_get_size(pqueue_t head);

bool queue_in(pqueue_t head, queue_data_t data);
void queue_out(pqueue_t head, queue_data_t *data);
bool queue_get_front(pqueue_t head, queue_data_t *data);
bool queue_get_rear(pqueue_t head, queue_data_t *data);

#endif

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

    bool (*clear)(struct _queue* self);
    bool (*empty)(struct _queue* self);
    bool (*full)(struct _queue* self);      // only for queue2
    uint32_t (*size)(struct _queue* self);
    uint32_t (*capacity)(struct _queue* self);

    // free
    void (*destory)(struct _queue* self);

    // print
    void (*print)(struct _queue* self);
    void (*print_obj)(void* obj);
};
typedef struct _queue* queue_t;

bool queue_init(struct _queue * queue, uint32_t obj_size);
bool queue_init2(struct _queue * queue, uint32_t obj_size, uint32_t capacity);

queue_t queue_new(void);
void queue_free(queue_t queue);

#endif // _QUEUE_H_
