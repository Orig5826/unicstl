
#include "stack.h"

static uint32_t stack_capacity(struct _stack* s)
{
	assert(s != NULL);
	return s->_capacity;
}

static uint32_t stack_size(struct _stack* s)
{
	assert(s != NULL);
	return s->_size;
}

static bool stack_empty(struct _stack* s)
{
	assert(s != NULL);
	// assert(s->_head != NULL);
	// return s->_head->next == NULL ? true : false;
	return !stack_size(s);
}

static bool stack_peek(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node * node = s->_head->next;
	memmove(obj, node->obj, s->_obj_size);
	return true;
}

static bool stack_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	void* new_obj = (void*)calloc(1, s->_obj_size);
	if (new_obj == NULL)
	{
		return false;
	}
	memmove(new_obj, obj, s->_obj_size);

	struct _stack_node* new_node = (struct _stack_node*)malloc(sizeof(struct _stack_node));
	if (new_node == NULL)
	{
		return false;
	}
	new_node->obj = new_obj;
	new_node->next = s->_head->next;
	s->_head->next = new_node;

	s->_size += 1;
	return true;
}

static bool stack_pop(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	// assert(obj != NULL);
	
	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;

	if (obj != NULL)
	{
		// 将弹出的数据输出
		memmove(obj, node->obj, s->_obj_size);
	}

	// 更新指针
	s->_head->next = node->next;

	// 释放数据和节点
	free(node->obj);
	free(node);

	s->_size -= 1;
	return true;
}

static bool stack_clear(struct _stack* s)
{
	assert(s != NULL);

	if (s->empty(s))
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		// 更新指针
		s->_head->next = node->next;

		// 释放数据和节点
		free(node->obj);
		free(node);

		node = s->_head->next;
	}
	s->_size = 0;
	return true;
}

static void stack_destory(struct _stack* s)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	
	s->clear(s);
	free(s->_head);
	s->_head = NULL;
}

static void stack_print(struct _stack* s)
{
	uint32_t i = 0;
	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		s->print_obj(node->obj);
		node = node->next;
	}
}

bool stack_init(struct _stack* s, uint32_t obj_size)
{
	assert(s != NULL);

	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	// s->_capacity = 64;		// 无效
	// s->_ratio = 2;			// 无效
	
	// 2. set function
	// kernel
	s->peek = stack_peek;
	s->pop = stack_pop;
	s->push = stack_push;

	// others
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->size = stack_size;
	s->destory = stack_destory;
	s->print = stack_print;

	// 3. set node
	s->_head = (struct _stack_node *)malloc(sizeof(struct _stack_node));
	if (s->_head == NULL)
	{
		return false;
	}
	s->_head->obj = NULL;
	s->_head->next = NULL;

	return true;
}


static bool stack2_peek(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	if (s->empty(s))
	{
		return false;
	}

	uint32_t top = s->size(s) - 1;
	uint32_t offset = top * s->_obj_size;
	memmove(obj, (char *)s->_head->obj + offset, s->_obj_size);
	return true;
}

static bool stack2_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	assert(obj != NULL);

	if (s->size(s) == s->_capacity)
	{
		void* obj_new = (void*)realloc(s->_head->obj, s->_capacity * s->_obj_size * s->_ratio);
		if (obj_new == NULL)
		{
			return false;
		}
		s->_head->obj = obj_new;
	}

	uint32_t top = s->size(s);
	uint32_t offset = top * s->_obj_size;
	memmove((char*)s->_head->obj + offset, obj, s->_obj_size);

	s->_size += 1;
	return true;
}

static bool stack2_pop(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	// assert(obj != NULL);

	if (s->empty(s))
	{
		return false;
	}

	if (obj != NULL)
	{
		uint32_t top = s->size(s) - 1;
		uint32_t offset = top * s->_obj_size;
		memmove(obj, (char*)s->_head->obj + offset, s->_obj_size);
	}

	s->_size -= 1;
	return true;
}

static void stack2_print(struct _stack* s)
{
	assert(s != NULL);
	assert(s->_head != NULL);

	void* obj = NULL;
	uint32_t offset = 0;

	for (int i = s->size(s) - 1; i >= 0; i--)
	{
		offset = s->_obj_size * i;
		obj = (char*)s->_head->obj + offset;
		s->print_obj(obj);
	}
}

bool stack2_init(struct _stack* s, uint32_t obj_size)
{
	assert(s != NULL);

	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	s->_capacity = 64;
	s->_ratio = 2;

	// 2. set function
	// kernel
	s->peek = stack2_peek;
	s->pop = stack2_pop;
	s->push = stack2_push;

	// others
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->size = stack_size;
	s->destory = stack_destory;
	s->print = stack2_print;

	// 3. set node
	s->_head = (struct _stack_node*)malloc(sizeof(struct _stack_node));
	if (s->_head == NULL)
	{
		return false;
	}
	// s->_head->obj = NULL;
	s->_head->next = NULL;		// 无效参数

	// 4. set array
	s->_head->obj = (void *)calloc(s->_capacity, s->_obj_size);
	if (s->_head->obj == NULL)
	{
		return false;
	}
	return true;
}

