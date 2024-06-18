
#include "list.h"

bool list_init(plist_t *list)
{
	*list = (plist_t)malloc(sizeof(list_t));
	if(*list == NULL)
	{
		return false;
	}
	(*list)->data = (list_data_t)0;
	(*list)->prev = *list;
	(*list)->next = *list;
	return true;
}

void list_destroy(plist_t *list)
{
	if (*list != NULL)
	{
		list_clear(*list);
		free(*list);
		(*list)->prev = NULL;
		(*list)->next = NULL;
		*list = NULL;
	}
}

bool list_empty(plist_t list)
{
	return (list == NULL || (list->prev == list && list->next == list)) ? true : false;
}

void list_clear(plist_t list)
{
	if(!list_empty(list))
	{
		plist_t p = list->next;
		plist_t ptmp = p;
		while(p != list)
		{
			ptmp = p;
			p->prev->next = p->next;
			p->next->prev = p->prev;
			p = p->next;

			// finally free memory
			free(ptmp);
			ptmp->prev = NULL;
			ptmp->next = NULL;
		}
	}
}

bool list_insert_head(plist_t list, list_data_t data)
{
	plist_t new_item;
	if(list == NULL)
	{
		return false;
	}

	new_item = (plist_t)malloc(sizeof(list_t));
	if(new_item == NULL)
	{
		return false;
	}
	new_item->data = data;

	// insert from head
	new_item->next = list->next;
	new_item->prev = list->next->prev;
	list->next->prev = new_item;
	list->next = new_item;

	return true;
}

bool list_insert_tail(plist_t list, list_data_t data)
{
	plist_t new_item;
	if(list == NULL)
	{
		return false;
	}

	new_item = (plist_t)malloc(sizeof(list_t));
	if(new_item == NULL)
	{
		return false;
	}
	new_item->data = data;

	// insert from tail
	new_item->prev = list->prev;
	new_item->next = list->prev->next;
	list->prev->next = new_item;
	list->prev = new_item;

	return true;
}

bool list_delete(plist_t list, list_data_t data)
{
	if(!list_empty(list))
	{
		plist_t p = list;
		while(p->next != list)
		{
			p = p->next;
			if(p->data == data)
			{
				// delete the item
				p->prev->next = p->next;
				p->next->prev = p->prev;
				free(p);
				p->prev = NULL;
				p->next = NULL;
				return true;
			}
		}
	}
	return false;
}

uint32_t list_count(plist_t list)
{
	uint32_t count = 0;
	if(!list_empty(list))
	{
		plist_t p = list;
		while(p->next != list)
		{
			p = p->next;
			count++;
		}
	}
	return count;
}

void list_traversal_sequence(plist_t list, list_data_disp_t disp)
{
	if(!list_empty(list))
	{
		plist_t p = list->next;
		while(p != list)
		{
			disp(p->data);
			p = p->next;
		}
	}
}

void list_traversal_reversed(plist_t list, list_data_disp_t disp)
{
	if(!list_empty(list))
	{
		plist_t p = list->prev;
		while(p != list)
		{
			disp(p->data);
			p = p->prev;
		}
	}
}

