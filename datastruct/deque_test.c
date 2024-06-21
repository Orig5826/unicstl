
#include "deque.h"

static void print_num(void* obj)
{
	printf("(%2d ) ", *(int*)obj);
}

static void deque_test_num(void)
{
	uint32_t i = 0;
	int data[] = { 1,2,3,4,5,6,7,8,9,10 };
	int temp = 0;
	uint32_t len = sizeof(data) / sizeof(data[0]);

	struct _deque dq;
	deque_init(&dq, sizeof(int));
	dq.print_obj = print_num;

	printf("\n\n----- deque_test_num -----\n");

	printf("----- after push_back -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_back(&dq, &data[i]);

		dq.front(&dq, &temp);
		printf("front = ");
		dq.print_obj(&temp);

		dq.back(&dq, &temp);
		printf("\tback = ");
		dq.print_obj(&temp);

		printf("\tsize = %2d\n", dq.size(&dq));
	}
	printf("----- print -----\n");
	dq.print(&dq);
	printf("\n");

	dq.clear(&dq);
	if (dq.empty(&dq))
	{
		printf("----- empty -----\n");
	}

	printf("----- push_back -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_back(&dq, &data[i]);
	}

	printf("----- after pop_back -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == dq.pop_back(&dq, &temp))
		{
			printf("pop = ");
			dq.print_obj(&temp);

			if (true == dq.front(&dq, &temp))
			{
				printf("front = ");
				dq.print_obj(&temp);
			}

			if (dq.back(&dq, &temp))
			{
				printf("back = ");
				dq.print_obj(&temp);
			}

			printf("size = %2d\n", dq.size(&dq));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (dq.empty(&dq))
		{
			printf("----- empty -----\n");
		}
	}

	printf("----- after push_front -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_front(&dq, &data[i]);

		dq.front(&dq, &temp);
		printf("front = ");
		dq.print_obj(&temp);

		dq.back(&dq, &temp);
		printf("\tback = ");
		dq.print_obj(&temp);

		printf("\tsize = %2d\n", dq.size(&dq));
	}
	printf("----- print -----\n");
	dq.print(&dq);
	printf("\n");

	dq.clear(&dq);
	if (dq.empty(&dq))
	{
		printf("----- empty -----\n");
	}

	printf("----- push_front -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_front(&dq, &data[i]);
	}

	for (i = 0; i < len + 1; i++)
	{
		if (true == dq.pop_front(&dq, &temp))
		{
			printf("pop = ");
			dq.print_obj(&temp);

			if (true == dq.front(&dq, &temp))
			{
				printf("front = ");
				dq.print_obj(&temp);
			}

			if (dq.back(&dq, &temp))
			{
				printf("back = ");
				dq.print_obj(&temp);
			}

			printf("size = %2d\n", dq.size(&dq));
		}
	}

	printf("----- push_front -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_front(&dq, &data[i]);
	}
	printf("----- print -----\n");
	dq.print(&dq);
	printf("\n");

	printf("----- set -----\n");
	temp = 11;
	dq.set(&dq, 0, &temp);

	temp = 22;
	dq.set(&dq, len/2, &temp);

	temp = 33;
	dq.set(&dq, len - 1, &temp);

	printf("----- print -----\n");
	dq.print(&dq);
	printf("\n");

	printf("----- get -----\n");
	for (i = 0; i < len; i++)
	{
		if (true == dq.get(&dq, i, &temp))
		{
			printf("deque[%2d] = ", i);
			dq.print_obj(&temp);
			printf("\n");
		}
	}

	dq.destory(&dq);
}

void deque_test(void)
{
	deque_test_num();
}
