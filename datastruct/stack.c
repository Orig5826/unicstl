
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

bool stack_clear(struct _stack* s)
{
	assert(s != NULL);
	return true;
}

bool stack_peek(struct _stack* s, void* obj)
{
	return true;
}

bool stack_push(struct _stack* s, void* obj)
{
	assert(s != NULL);
	assert(obj != NULL);
	return true;
}

bool stack_pop(struct _stack* s, void* obj)
{
	return true;
}

bool stack_init(struct _stack* s, uint32_t obj_size)
{
	// 1. set attr
	s->_obj_size = obj_size;
	s->_size = 0;
	// s->capacity = 64;
	
	// 2. set function
	s->clear = stack_clear;
	s->empty = stack_empty;
	s->peek = stack_peek;
	s->pop = stack_pop;
	s->push = stack_push;
	s->size = stack_size;

	// 3. set node
	s->_node->obj = NULL;
	s->_node->next = NULL;

	return true;
}

#endif
