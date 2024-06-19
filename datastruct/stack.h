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
	struct _stack_node * _head;
	uint32_t _capacity;			// 总容量
	uint32_t _size;				// 栈大小
	uint32_t _obj_size;			// 元素大小

	// base
	uint32_t(*size)(struct _stack* s);
	bool (*empty)(struct _stack* s);

	// kernel
	bool (*peek)(struct _stack* s, void *obj);
	bool (*push)(struct _stack* s, void* obj);
	bool (*pop)(struct _stack* s, void* obj);

	// others
	bool (*clear)(struct _stack* s);
	void (*destory)(struct _stack* s);
	void (*print)(struct _stack* s);
};

bool stack_init(struct _stack* s, uint32_t type_size);

#endif

#endif // _STACK_H_

