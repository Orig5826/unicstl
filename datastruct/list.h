#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"

#ifdef LIST

struct _list
{
	void * obj;

	uint32_t _obj_size;			// 元素大小
	uint32_t _size;				// 栈大小
	uint32_t _capacity;			// 总容量
	uint32_t _ratio;			// 扩展比率

	// kernel
	bool (*append)(struct _list* self, void* obj);						// Append object to the end of the list.
	bool (*insert)(struct _list* self, int index, void* obj);			// Insert object before index.
	bool (*pop)(struct _list* self, int index, void* obj);				// Remove and return item at index.
	
	int (*index)(struct _list* self, void* obj);						// Return first index of obj. Return -1 if the obj is not present.
	bool (*remove)(struct _list* self, void *obj);						// Remove first occurrence of obj.

	bool (*clear)(struct _list* self);									// Remove all items from list.

	bool (*get)(struct _list* self, int index, void* obj);				// 根据索引，获取对象
	bool (*set)(struct _list* self, int index, void* obj);				// 根据索引，修改对象

	// base
	uint32_t(*size)(struct _list* self);
	bool (*empty)(struct _list* self);

	// sort
	bool (*reverse)(struct _list* self);		// Reverse *IN PLACE*.

	/**
		Sort the list in ascending order and return false.
		The sort is in-place (i.e. the list itself is modified) and stable (i.e. the
		order of two equal elements is maintained).
		The reverse flag can be set to sort in descending order.
	*/
	bool (*sort)(struct _list* self, uint8_t reserve, int (*compare)(void* obj, void* obj2));

	// free
	void (*destory)(struct _list* self);

	// print
	void (*print)(struct _list* self);
	void (*print_obj)(void* obj);
};

bool list_init(struct _list* list, uint32_t obj_size);

#endif

#endif // _LIST_H_
