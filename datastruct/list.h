#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"

// #define LINK_LIST		1
#define LIST				1

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

typedef int list_data_t;

struct _list
{
	list_data_t * array;      // 数组（存储列表元素）
	int capacity;    	// 列表容量
	int size;        	// 列表大小
	int extend_ratio; 	// 列表每次扩容的倍数
};
typedef struct _list * list_t;

bool list_init(list_t list);
void list_destory(list_t list);

bool list_empty(list_t list);
int list_size(list_t list);

bool list_insert(list_t list, int index, list_data_t data);
bool list_append(list_t list, list_data_t data);
list_data_t list_delete(list_t list, int index);
bool list_clear(list_t list);
list_data_t list_get(list_t list, int index);
bool list_set(list_t list, int index, list_data_t data);

extern void list_test(void);

#endif

#endif // _LIST_H_
