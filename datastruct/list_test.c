
#include "list.h"

#if 0
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

static void print_num(void* obj)
{
	printf("(%2d )", *(int*)obj);
}

static void list_test_num(void)
{
	int i = 0;
	int data[] = { 1,2,3,4,5,6,7,8,9,10 };
	int temp = 0;
	int index = 0;
	int len = sizeof(data) / sizeof(data[0]);

	struct _list list;
	list_init(&list, sizeof(int));
	list.print_obj = print_num;

	printf("\n\n----- list_test_num -----\n");
	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		list.append(&list, &data[i]);
	}
	printf("----- print -----\n");
	list.print(&list);
	printf("\n");

	printf("----- remove -----\n");
	list.remove(&list, 9);
	list.print(&list);
	printf("\n");

	list.remove(&list, 0);
	list.print(&list);
	printf("\n");

	list.remove(&list, 4);
	list.print(&list);
	printf("\n");

	printf("----- clear -----\n");
	list.clear(&list);
	list.print(&list);
	printf("\n");

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		list.append(&list, &data[i]);
	}
	printf("----- print -----\n");
	list.print(&list);
	printf("\n");

	printf("----- at -----\n");
	index = 0;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = 4;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = 9;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);


	printf("----- set -----\n");
	index = 0;
	temp = 11;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = 4;
	temp = 22;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = 9;
	temp = 33;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	printf("----- print -----\n");
	list.print(&list);
	printf("\n");


	printf("----- at like python -----\n");
	index = -1;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = -6;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = -10;
	list.at(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	printf("----- set like python -----\n");
	index = -1;
	temp = 99;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = -6;
	temp = 98;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	index = -10;
	temp = 97;
	list.set(&list, index, &temp);
	printf("list[%2d] = %2d\n", index, temp);

	printf("----- print -----\n");
	list.print(&list);
	printf("\n");

	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == list.pop(&list, 0, &temp))
		{
			printf("top = ");
			list.print_obj(&temp);
			printf("\tsize after push = %2d\n", list.size(&list));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (list.empty(&list))
		{
			printf("----- empty -----\n");
			break;
		}
	}

	list.destory(&list);
}


void list_test(void)
{
	list_test_num();
}
