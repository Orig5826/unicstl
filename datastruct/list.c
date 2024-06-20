
#include "list.h"


#ifdef LINK_LIST
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
#endif

#if 0
bool list_init(list_t list)
{
	// list->capacity = 64;
	list->capacity = 8;

	list->size = 0;
	list->extend_ratio = 2;
	list->array = (list_data_t *)malloc(list->capacity * sizeof(list_data_t));
	if (list->array == NULL)
	{
		return false;
	}
	return true;
}

void list_destory(list_t list)
{
	if (list->array != NULL)
	{
		free(list->array);
	}
}

int list_capacity(list_t list)
{
	return list->capacity;
}

int list_size(list_t list)
{
	return list->size;
}

bool list_empty(list_t list)
{
	return list_size(list) == 0 ? true : false;
}

bool list_insert(list_t list, int index, list_data_t data)
{
	assert(index >= 0 && index <= list_size(list));
	if (list_size(list) == list_capacity(list))
	{
		int capacity = list->capacity * list->extend_ratio;
		list_data_t * array = (list_data_t*)realloc(list->array, capacity * sizeof(list_data_t));
		if (array == NULL)
		{
			return false;
		}
		list->array = array;
		list->capacity = capacity;
	}
	memmove(&list->array[index + 1], &list->array[index], list_size(list) * sizeof(list_data_t));
	list->array[index] = data;
	list->size += 1;
	return true;
}

bool list_append(list_t list, list_data_t data)
{
	if (list_size(list) == list_capacity(list))
	{
		int capacity = list->capacity * list->extend_ratio;
		list_data_t * array = (list_data_t*)realloc(list->array, capacity * sizeof(list_data_t));
		if (array == NULL)
		{
			return false;
		}
		list->array = array;
		list->capacity = capacity;
	}
	list->array[list->size] = data;
	list->size += 1;
	return true;
}

int list_delete(list_t list, int index)
{
	assert(index >= 0 && index < list_size(list));
	int temp = 0;
	temp = list->array[index];
	if (index != list_size(list))
	{
		memmove(&list->array[index], &list->array[index + 1], (list_size(list) - 1 - index) * sizeof(list_data_t));
		//for (int i = index; i < list_size(list) - 1; i++)
		//{
		//	list->array[i] = list->array[i + 1];
		//}
	}
	list->size -= 1;
	return temp;
}

bool list_clear(list_t list)
{
	memset(list->array, 0, list->size);
	list->size = 0;
	return true;
}

list_data_t list_get(list_t list, int index)
{
	assert(index >= -list_size(list) && index < list_size(list));
	return index >= 0 ? list->array[index] : list->array[list_size(list) + index];
}

bool list_set(list_t list, int index, list_data_t data)
{
	assert(index >= 0 && index < list_size(list));
	list->array[index] = data;
	return true;
}

void list_print(list_t list)
{
	if (!list_empty(list))
	{
		for (int i = 0; i < list_size(list); i++)
		{
			printf("%2d ", list->array[i]);
		}
		printf("\n");
	}
}

void list_test(void)
{
	int i = 0;
	
	list_data_t data = 0;
	struct _list list;
	list_init(&list);

	printf("----- append -----\n");
	for (i = 0; i < 18; i++)
	{
		list_append(&list, i);
		list_print(&list);
	}

	printf("----- delete -----\n");
	list_delete(&list, 17);
	list_print(&list);

	list_delete(&list, 0);
	list_print(&list);

	list_delete(&list, 9);
	list_print(&list);

	printf("----- clear -----\n");
	list_clear(&list);
	printf("----- insert -----\n");
	for (i = 0; i < 18; i++)
	{
		list_insert(&list, 0, i);
		list_print(&list);
	}

	printf("----- get -----\n");
	data = list_get(&list, 0);
	printf("list[0] = %2d\n", data);

	data = list_get(&list, 17);
	printf("list[17] = %2d\n", data);

	data = list_get(&list, 5);
	printf("list[5] = %2d\n", data);

	printf("----- like python -----\n");
	data = list_get(&list, -1);
	printf("list[-1] = %2d\n", data);

	data = list_get(&list, -5);
	printf("list[-5] = %2d\n", data);

	data = list_get(&list, -18);
	printf("list[-18] = %2d\n", data);

	printf("----- set -----\n");
	for (i = 0; i < 18; i++)
	{
		list_set(&list, i, i);
		list_print(&list);
	}

	list_print(&list);
	list_destory(&list);
}

#endif

bool list_append(struct _list* self, void* obj)
{
	assert(self != NULL);
	assert(self->obj != NULL);
	assert(obj != NULL);

	if (self->size(self) == self->_capacity)
	{
		int capacity = self->_capacity * self->_ratio;
		void * obj_new = (list_data_t*)realloc(self->obj, capacity * self->_obj_size);
		if (obj_new == NULL)
		{
			return false;
		}
		self->obj = obj_new;
		self->_capacity = capacity;
	}
	uint32_t index = self->size(self);
	uint32_t offset = index * self->_obj_size;
	memmove((char*)self->obj + offset, obj, self->_obj_size);

	self->_size += 1;
	return true;
}

bool list_clear(struct _list* self)
{
	assert(self != NULL);
	self->_size = 0;
	return true;
}

bool list_empty(struct _list* self)
{
	assert(self != NULL);
	return !self->size(self);
}

uint32_t list_index(struct _list* self, void* obj)
{
	return 0;
}

bool list_insert(struct _list* self, uint32_t index, void* obj)
{
	assert(index >= 0 && index < self->size(self));

	if (self->size(self) == self->_capacity)
	{
		int capacity = self->_capacity * self->_ratio;
		void* obj_new = (list_data_t*)realloc(self->obj, capacity * self->_obj_size);
		if (obj_new == NULL)
		{
			return false;
		}
		self->obj = obj_new;
		self->_capacity = capacity;
	}
	uint32_t offset = index * self->_obj_size;
	uint32_t offset1 = (index + 1) * self->_obj_size;

	memmove((char*)self->obj + offset, (char *)self->obj + offset, self->size(self) * self->_obj_size);
	self->_size += 1;
	return true;
}

bool list_pop(struct _list* self, int index, void* obj)
{
	assert(self != NULL);
	assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));		// list空的时候也会报错，太严格了有点

	if (self->empty(self))
	{
		return false;
	}

	if (index < 0)
	{
		index += self->size(self);
	}

	uint32_t count = self->size(self) - 1 - index;
	uint32_t offset = index * self->_obj_size;
	uint32_t offset1 = (index + 1) * self->_obj_size;
	if (obj != NULL)
	{
		memmove(obj, (char*)self->obj + offset, self->_obj_size);
	}
	memmove((char*)self->obj + offset, (char*)self->obj + offset1, count * self->_obj_size);
	self->_size -= 1;
	return true;
}

bool list_at(struct _list* self, int index, void *obj)
{
	assert(self != NULL);
	assert(obj != NULL);
	assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));

	if (index < 0)
	{
		index += self->size(self);
	}
	uint32_t offset = index * self->_obj_size;
	memmove(obj, (char*)self->obj + offset, self->_obj_size);
	return true;
}

bool list_set(struct _list* self, int index, void* obj)
{
	assert(self != NULL);
	assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));
	if (index < 0)
	{
		index += self->size(self);
	}
	uint32_t offset = index * self->_obj_size;
	memmove((char*)self->obj + offset, obj, self->_obj_size);
	return true;
}

uint32_t list_size(struct _list* self)
{
	return self->_size;
}

bool list_remove(struct _list* self, int index)
{
	assert(self != NULL);
	assert(index >= (int)(0 - self->size(self)) && index < (int)self->size(self));

	if (self->empty(self))
	{
		return false;
	}

	if (index < 0)
	{
		index += self->size(self);
	}

	uint32_t count = self->size(self) - 1 - index;
	uint32_t offset = index * self->_obj_size;
	uint32_t offset1 = (index + 1) * self->_obj_size;
	memmove((char*)self->obj + offset, (char*)self->obj + offset1, count * self->_obj_size);
	self->_size -= 1;
	return true;
}

bool list_reverse(struct _list* self)
{
	return true;
}

bool list_sort(struct _list* self, uint8_t reserve, int (*compare)(void* obj, void* obj2))
{
	return true;
}

// free
void list_destory(struct _list* self)
{
	assert(self != NULL);
	if (self->obj != NULL)
	{
		free(self->obj);
	}
}

// print
void list_print(struct _list* self)
{
	assert(self != NULL);

	if (!self->empty(self))
	{
		void* obj = NULL;

		for (uint32_t i = 0; i < self->size(self); i++)
		{
			obj = (char*)self->obj + i * self->_obj_size;
			self->print_obj(obj);
		}
	}
}

bool list_init(struct _list* list, uint32_t obj_size)
{
	assert(list != NULL);

	// 1. set attr
	list->_obj_size = obj_size;
	list->_size = 0;
	list->_capacity = 64;
	list->_ratio = 2;

	// 2. set function
	// kernel
	list->append = list_append;
	list->at = list_at;
	list->clear = list_clear;
	list->destory = list_destory;
	list->empty = list_empty;
	list->index = list_index;
	list->insert = list_insert;
	list->pop = list_pop;
	list->print = list_print;
	list->remove = list_remove;
	list->reverse = list_reverse;
	list->set = list_set;
	list->size = list_size;
	list->sort = list_sort;

	// 3. set array
	list->obj = (void*)calloc(list->_capacity, list->_obj_size);
	if (list->obj == NULL)
	{
		return false;
	}
	return true;
}
