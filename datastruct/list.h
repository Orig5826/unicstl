#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"

// #define LINK_LIST		1
// #define LIST				1

#ifdef LINK_LIST
#define LIST_TEST

#ifdef LIST_TEST
	typedef int list_data_t;
#else
	typedef int list_data_t;
#endif

typedef struct _list_t
{
	list_data_t data;
	struct _list_t * prev;
	struct _list_t * next;
}list_t,*plist_t;

typedef void (*list_data_disp_t)(list_data_t data);


bool list_init(plist_t *list);
void list_destroy(plist_t *list);
bool list_empty(plist_t list);
void list_clear(plist_t list);
bool list_insert_head(plist_t list, list_data_t data);
bool list_insert_tail(plist_t list, list_data_t data);
bool list_delete(plist_t list, list_data_t data);
uint32_t list_count(plist_t list);
void list_traversal_sequence(plist_t list, list_data_disp_t disp);
void list_traversal_reversed(plist_t list, list_data_disp_t disp);

extern void list_test(void);
#endif

#ifdef LIST

struct _list
{
	void * obj;
	uint32_t _obj_size;			// Ԫ�ش�С
	uint32_t _size;				// ջ��С
	uint32_t _capacity;			// ������
	uint32_t _ratio;			// ��չ����

	// kernel
	bool (*append)(struct _list* self, void* obj);						// ׷�Ӷ���
	bool (*insert)(struct _list* self, uint32_t index, void* obj);		// ���б�ָ��λ�ã��������
	bool (*pop)(struct _list* self, int index, void* obj);				// ����������ɾ�����󲢷��ء�
	bool (*remove)(struct _list* self, int index);						// �����������Ƴ�����

	int (*index)(struct _list* self, void* obj);						// ���б��У����������Ƿ���ڣ��������򷵻������������򷵻�-1
	bool (*at)(struct _list* self, int index, void* obj);				// ������������ȡ����
	bool (*set)(struct _list* self, int index, void* obj);				// �����������޸Ķ���

	// base
	uint32_t(*size)(struct _list* self);
	bool (*clear)(struct _list* self);
	bool (*empty)(struct _list* self);

	// sort
	bool (*reverse)(struct _list* self);
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
