
#include "test.h"

#if LIST_TEST == 1

static void list_data_display(list_data_t data)
{
	printf("%d ", data);
}

void list_test(void)
{
	int32_t i = 0;
	list_data_t dat[10] = { 0,1,2,3,4,5,6,7,8,9 };
	plist_t list;
	if (!list_init(&list))
	{
		printf("list_init failureed!\n");
	}
	printf("list_init success!\n");
	if (!list_empty(list))
	{
		printf("list is empty!\n");
	}
	for (i = 0; i < 10; i++)
	{
		list_insert_tail(list, dat[i]);
	}
	list_traversal_sequence(list, list_data_display);
	printf("\nlist_traversal_sequence success!\n");
	list_traversal_reversed(list, list_data_display);
	printf("\nlist_traversal_reversed success!\n");
	if (list_empty(list))
	{
		printf("list is not empty!\n");
	}

	list_clear(list);
	printf("list_clear success\n");
	for (i = 0; i < 10; i++)
	{
		list_insert_head(list, dat[i]);
	}
	if (!list_delete(list, 5))
	{
		printf("list_delete failureed!\n");
	}
	printf("list_delete success! Data5 has been deleted\n");
	printf("list_count = %d\n", list_count(list));

	list_traversal_sequence(list, list_data_display);
	printf("\nlist_traversal_sequence success!\n");
	list_traversal_reversed(list, list_data_display);
	printf("\nlist_traversal_reversed success!\n");

	list_destroy(&list);
	printf("list_destroy success\n");

	if (!list_insert_tail(list, dat[0]))
	{
		printf("list_insert_tail success\n");
	}
	if (!list_insert_head(list, dat[0]))
	{
		printf("list_insert_head success\n");
	}

	printf("----------------------------------------\n");
}

#endif

