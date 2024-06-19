
#include "stack.h"


#if STACK == 1
#if 0
bool stack_init(pstack_t *head)
{
	*head = (pstack_t)malloc(sizeof(stack_t));
	if(*head == NULL)
	{
		return false;
	}
	(*head)->top = NULL;
	(*head)->size = 0;
	return true;
}

void stack_destroy(pstack_t *head)
{
	if(*head != NULL)
	{
		stack_clear(*head);
		free(*head);
		*head = NULL;
	}
}

bool stack_empty(pstack_t head)
{
	return (head == NULL || head->top == NULL) ? true : false;
}

void stack_clear(pstack_t head)
{
	pstack_node_t top_item;
	if(head != NULL)
	{
		top_item = head->top;
		while(top_item != NULL)
		{
			head->top = top_item->next;
			free(top_item);
			top_item = head->top;
		}
	}
	head->size = 0;
}

bool stack_push(pstack_t head, stack_data_t data)
{
	pstack_node_t new_item;
	if(head == NULL)
	{
		return false;
	}

	new_item = (pstack_node_t)malloc(sizeof(stack_node_t));
	if(new_item == NULL)
	{
		return false;
	}
	new_item->data = data;

	// insert from head
	new_item->next = head->top;
	head->top = new_item;

	// increase
	if(head->size < _UI32_MAX)
	{
		head->size ++;
	}
	return true;
}

void stack_pop(pstack_t head, stack_data_t *data)
{
	pstack_node_t top_item;
	if(!stack_empty(head))
	{
		top_item = head->top;
		*data = top_item->data;

		// free the top item
		head->top = top_item->next;
		free(top_item);
		top_item = NULL;

		// decrease
		if(head->size > 0)
		{
			head->size--;
		}
	}
}

bool stack_get_top(pstack_t head, stack_data_t *data)
{
	if(!stack_empty(head))
	{
		*data = head->top->data;
		return true;
	}
	else
	{
		return false;
	}
}

uint32_t stack_get_size(pstack_t head)
{
	return head->size;
}
#endif

uint32_t stack_capacity(struct _stack* s)
{
	assert(s != NULL);
	return s->_capacity;
}

uint32_t stack_size(struct _stack* s)
{
	assert(s != NULL);
	return s->_size;
}

bool stack_empty(struct _stack* s)
{
	assert(s != NULL);
	return !stack_size(s);
}

bool stack_peek(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(s->_head != NULL);
	struct _stack_node * node = s->_head->next;
	memmove(obj, node->obj, s->_obj_size);
	return true;
}

bool stack_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(obj != NULL);

	void* new_obj = (void*)malloc(s->_obj_size);
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

bool stack_pop(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(obj != NULL);
	assert(s->_head != NULL);
	
	if (s->_head->next == NULL)
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;
	// 将弹出的数据输出
	memmove(obj, node->obj, s->_obj_size);

	// 更新指针
	s->_head->next = node->next;

	// 释放数据和节点
	free(node->obj);
	free(node);

	s->_size -= 1;
	return true;
}

bool stack_clear(struct _stack* s)
{
	assert(s != NULL);

	if (s->_head == NULL)
	{
		return false;
	}

	struct _stack_node* node = s->_head->next;
	while (node != NULL)
	{
		node = node->next;
	}
	return true;
}

void stack_destory(struct _stack* s)
{
	assert(s != NULL);
	
	s->clear(s);
	free(s->_head);
	s->_head = NULL;
}

bool stack_init(struct _stack* s, uint32_t obj_size)
{
	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	// s->_capacity = 64;
	
	// 2. set function
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->peek = stack_peek;
	s->pop = stack_pop;
	s->push = stack_push;
	s->size = stack_size;
	s->destory = stack_destory;
	s->print = NULL;

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

void stack_print_num(struct _stack* s)
{
	uint32_t i = 0;
	struct _stack_node * node = s->_head->next;
	while (node != NULL)
	{
		printf("%2d ", *(int*)node->obj);
		node = node->next;
	}
	printf("\n");
}

void stack_test(void)
{
	uint32_t i = 0;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	int temp = 0;
	uint32_t len = sizeof(data)/sizeof(data[0]);

	struct _stack s;
	stack_init(&s, sizeof(int));
	s.print = stack_print_num;

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		s.push(&s, &data[i]);

		s.peek(&s, &temp);
		printf("top = %2d, size after push = %2d\n", temp, s.size(&s));
	}
	printf("----- print -----\n");
	s.print(&s);

	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == s.pop(&s, &temp))
		{
			printf("top = %2d, size after pop = %2d\n", temp, s.size(&s));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (s.empty(&s))
		{
			printf("----- empty -----\n");
		}
	}

	s.destory(&s);
}

#endif
