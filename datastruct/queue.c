
#include "queue.h"
#if QUEUE == 1

bool queue_init(pqueue_t * head)
{
	*head = (pqueue_t)malloc(sizeof(queue_t));
	if(*head == NULL)
	{
		return false;
	}
	(*head)->front = NULL;
	(*head)->rear = NULL;
	(*head)->size = 0;
	return true;
}

void queue_destroy(pqueue_t * head)
{
	if(*head != NULL)
	{
		queue_clear(*head);
		free(*head);
		*head = NULL;
	}
}

bool queue_empty(pqueue_t head)
{
	return (head == NULL || head->front == NULL || head->rear == NULL) ? true : false;
}

void queue_clear(pqueue_t head)
{
	pqueue_node_t front_item;
	if(head != NULL)
	{
		front_item = head->front;
		while(head->front != NULL)
		{
			head->front = front_item->next;
			free(front_item);
			front_item = head->front;
		}
		head->rear = head->front;
		head->size = 0;
	}
}

uint32_t queue_get_size(pqueue_t head)
{
	return head->size;
}

bool queue_in(pqueue_t head, queue_data_t data)
{
	pqueue_node_t new_item;
	if(head == NULL)
	{
		return false;
	}
	new_item = (pqueue_node_t)malloc(sizeof(queue_node_t));
	if(new_item == NULL)
	{
		return false;
	}
	new_item->data = data;
	new_item->next = NULL;
	if(head->front == NULL)
	{
		head->front = new_item;
	}
	// insert from tail
	if(head->rear != NULL)
	{
		head->rear->next = new_item;
	}
	head->rear = new_item;

	if (head->size < _UI32_MAX)
	{
		head->size++;
	}
	
	return true;
}

void queue_out(pqueue_t head, queue_data_t *data)
{
	pqueue_node_t front_item;
	if(!queue_empty(head))
	{
		front_item = head->front;
		*data = front_item->data;

		// free the front item
		head->front = front_item->next;
		free(front_item);
		front_item = NULL;
		if (queue_get_size(head) == 1)
		{
			head->rear = NULL;
		}

		if (head > 0)
		{
			head->size--;
		}
	}
}

bool queue_get_front(pqueue_t head, queue_data_t *data)
{
	if(!queue_empty(head))
	{
		*data = head->front->data;
		return true;
	}
	else
	{
		return false;
	}
}

bool queue_get_rear(pqueue_t head, queue_data_t *data)
{
	if(!queue_empty(head))
	{
		*data = head->rear->data;
		return true;
	}
	else
	{
		return false;
	}
}

#endif
