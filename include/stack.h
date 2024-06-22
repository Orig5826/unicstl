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
	uint32_t _size;				// ջ��С
	uint32_t _obj_size;			// Ԫ�ش�С
	// only for array mode
	uint32_t _capacity;			// ������
	uint32_t _ratio;			// ��չ����

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
typedef struct _stack* stack_t;

bool stack_init(struct _stack* self, uint32_t obj_size);
bool stack_init2(struct _stack* self, uint32_t obj_size, uint32_t capacity);

stack_t stack_new(void);
void stack_free(stack_t stack);

#endif // _STACK_H_
