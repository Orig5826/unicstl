#ifndef _STACK_H_
#define _STACK_H_

#include "common.h"

#if STACK == 1

struct _stack_node
{
	void * obj;
	struct _stack_node * next;
};

struct _stack
{
	struct _stack_node * _node;
	uint32_t _capacity;			// ������
	uint32_t _size;				// ջ��С
	uint32_t _obj_size;			// Ԫ�ش�С

	bool (*empty)(struct _stack* s);
	bool (*clear)(struct _stack* s);
	uint32_t(*size)(struct _stack* s);

	bool (*peek)(struct _stack* s, void *obj);
	bool (*push)(struct _stack* s, void* obj);
	bool (*pop)(struct _stack* s, void* obj);
};

bool stack_init(struct _stack* s, uint32_t type_size);

#endif

#endif // _STACK_H_

