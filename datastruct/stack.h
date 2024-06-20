#ifndef _STACK_H_
#define _STACK_H_

#include "common.h"

struct _stack_node
{
	void * obj;
	struct _stack_node * next;
};

struct _stack
{
	struct _stack_node * _head;
	uint32_t _size;				// 栈大小
	uint32_t _obj_size;			// 元素大小
	// only for array mode
	uint32_t _capacity;			// 总容量
	uint32_t _ratio;			// 扩展比率

	// kernel
	bool (*peek)(struct _stack* s, void* obj);
	bool (*push)(struct _stack* s, void* obj);
	bool (*pop)(struct _stack* s, void* obj);

	// base
	uint32_t(*size)(struct _stack* s);
	bool (*empty)(struct _stack* s);

	// others
	bool (*clear)(struct _stack* s);
	void (*destory)(struct _stack* s);
	void (*print_obj)(void* obj);
	void (*print)(struct _stack* s);
};

bool stack_init(struct _stack* s, uint32_t obj_size);	// 链表
bool stack2_init(struct _stack* s, uint32_t obj_size);	// 数组

#endif // _STACK_H_

