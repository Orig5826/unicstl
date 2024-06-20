
#include "deque.h"

static void print_num(void* obj)
{
	printf("(%2d )", *(int*)obj);
}

static void deque_test_num(void)
{
	uint32_t i = 0;
	int data[] = { 0, 1,2,3,4,5,6,7,8,9,10 };
	int temp = 0;
	uint32_t len = sizeof(data) / sizeof(data[0]);

	struct _deque dq;
	deque_init(&dq, sizeof(int));
	dq.print_obj = print_num;

	printf("\n\n----- deque_test_num -----\n");

	printf("----- push_back -----\n");
	for (i = 0; i < len; i++)
	{
		dq.push_back(&dq, &data[i]);

		dq.back(&dq, &temp);

		printf("push_back = ");
		dq.print_obj(&temp);
		printf("\tsize after push_back = %2d\n", dq.size(&dq));
	}
	printf("----- print -----\n");
	dq.print(&dq);
	printf("\n");

#if 0
	printf("----- pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == s.pop(&s, &temp))
		{
			printf("top = ");
			s.print_obj(&temp);
			printf("\tsize after push = %2d\n", s.size(&s));
		}
		else
		{
			printf("pop failed! because stack is empty\n");
		}

		if (s.empty(&s))
		{
			printf("----- empty -----\n");
		}
	}
#endif
	dq.destory(&dq);
}

void deque_test(void)
{
	deque_test_num();
}
