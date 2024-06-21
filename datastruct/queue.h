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




#endif // _QUEUE_H_
