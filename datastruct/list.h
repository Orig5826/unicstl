#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"

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

#endif // _LIST_H_
