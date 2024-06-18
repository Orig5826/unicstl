#ifndef _STACK_H_
#define _STACK_H_

#include "common.h"

#if STACK == 1

// typedef int stack_data_t;

typedef struct _stack_node_t
{
	stack_data_t data;
	struct _stack_node_t * next;
} stack_node_t, *pstack_node_t;

typedef struct _stack_t
{
	struct _stack_node_t * top;
	uint32_t size;
} stack_t, *pstack_t;


bool stack_init(pstack_t *head);
void stack_destroy(pstack_t *head);
bool stack_empty(pstack_t head);
void stack_clear(pstack_t head);
uint32_t stack_get_size(pstack_t head);

bool stack_push(pstack_t head, stack_data_t data);
void stack_pop(pstack_t head, stack_data_t *data);
bool stack_get_top(pstack_t head, stack_data_t *data);

#endif

#endif // _STACK_H_

