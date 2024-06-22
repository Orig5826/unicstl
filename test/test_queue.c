
#include "queue.h"
#include "test.h"

#if QUEUE_TEST == 1

void queue_test(void)
{
	int32_t i = 0;
	uint32_t size;
	queue_data_t dat[10] = {0,1,2,3,4,5,6,7,8,9};
	queue_data_t tmp;
	pqueue_t que;

	if(!queue_init(&que))
	{
		printf("failure -> queue_init\n");
	}
	printf("success -> queue_init\n");

	for(i = 0; i < 10; i++)
	{
		if(!queue_in(que,dat[i]))
		{
			printf("failure -> queue_in\n");
		}
		if(!queue_get_front(que,&tmp))
		{
			printf("failure -> queue_get_front\t");
		}
		else
		{
			printf("    front = %d",tmp);
		}

		if(!queue_get_rear(que,&tmp))
		{
			printf("failure -> queue_get_rear\n");
		}
		else
		{
			printf("    rear = %d\n",tmp);
		}
	}
	printf("success -> queue_in\n");
	if(!queue_empty(que))
	{
		printf("success -> queue is not empty!\n");
	}
	else
	{
		printf("failure -> queue is not empty!\n");
	}

	size = queue_get_size(que);
	if (size != 10)
	{
		printf("failure -> the size of queue is : %d\n", size);
	}
	else
	{
		printf("success -> the size of queue is : %d\n", size);
	}

	printf("success -> queue_empty\n");
	for(i = 0; i < 10; i++)
	{
		if(!queue_get_front(que,&tmp))
		{
			printf("failure -> queue_get_front\t");
		}
		else
		{
			printf("    front = %d\t",tmp);
		}
		if(!queue_get_rear(que,&tmp))
		{
			printf("failure -> queue_get_rear\n");
		}
		else
		{
			printf("    rear = %d\n",tmp);
		}
		queue_out(que,&tmp);
	}
	printf("success -> queue_out\n");
	if(queue_empty(que))
	{
		printf("success -> queue is empty!\n");
	}

	size = queue_get_size(que);
	if (size != 0)
	{
		printf("failure -> the size of queue is : %d\n", size);
	}
	else
	{
		printf("success -> the size of queue is : %d\n", size);
	}

	for(i = 0; i < 5; i++)
	{
		if(!queue_in(que,dat[i]))
		{
			printf("failure -> queue_in\n");
		}
	}

	if(!queue_empty(que))
	{
		printf("success -> queue is not empty!\n");
		queue_clear(que);
		printf("success -> queue_clear\n");

		if(queue_empty(que))
		{
			printf("success -> queue is empty!\n");
		}
		else
		{
			printf("failure -> queue is not empty!\n");
		}
	}

	queue_destroy(&que);
	printf("success -> queue_destroy\n");

	if(!queue_in(que,dat[0]))
	{
		printf("success -> If que if NULL, queue_in return failure\n");
	}

	queue_out(que,&tmp);
	printf("success -> queue_out invalid!\n");

	if(queue_empty(que))
	{
		printf("success -> If que is NULL, queue_empty alse return true!\n");
	}
	else
	{
		printf("failure -> Que is NULL, but queue_empty return true!\n");
	}

	printf("----------------------------------------\n");
}

#else


static void queue_test_num(void)
{
	uint32_t i = 0;
	int data[] = { 1,2,3,4,5,6,7,8,9,10 };
	int temp = 0;
	uint32_t len = sizeof(data) / sizeof(data[0]);

	struct _queue queue;
	queue_init(&queue, sizeof(int));
	queue.print_obj = print_num;

	printf("\n\n----- queue_test_num -----\n");

	printf("----- after push-----\n");
	for (i = 0; i < len; i++)
	{
		queue.push(&queue, &data[i]);

		queue.front(&queue, &temp);
		printf("front = ");
		queue.print_obj(&temp);

		queue.back(&queue, &temp);
		printf("\tback = ");
		queue.print_obj(&temp);

		printf("\tsize = %2d\n", queue.size(&queue));
	}
	printf("----- print -----\n");
	queue.print(&queue);
	printf("\n");

	queue.clear(&queue);
	if (queue.empty(&queue))
	{
		printf("----- empty -----\n");
	}

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		queue.push(&queue, &data[i]);
	}

	printf("----- after pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == queue.pop(&queue, &temp))
		{
			printf("pop = ");
			queue.print_obj(&temp);

			if (true == queue.front(&queue, &temp))
			{
				printf("front = ");
				queue.print_obj(&temp);
			}

			if (queue.back(&queue, &temp))
			{
				printf("back = ");
				queue.print_obj(&temp);
			}

			printf("size = %2d\n", queue.size(&queue));
		}
		else
		{
			printf("pop failed! because it is empty\n");
		}

		if (queue.empty(&queue))
		{
			printf("----- empty -----\n");
		}
	}

	printf("----- print -----\n");
	queue.print(&queue);
	printf("\n");

	queue.destory(&queue);
}


static void queue_test_char(void)
{
	uint32_t i = 0;
	char data[] = "abcdefghijk";
	char temp = 0;
	uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

	struct _queue queue;
	queue2_init(&queue, sizeof(char), 64);
	queue.print_obj = print_char;

	printf("\n\n----- queue_test_char -----\n");

	printf("----- after push-----\n");
	for (i = 0; i < len; i++)
	{
		queue.push(&queue, &data[i]);

		queue.front(&queue, &temp);
		printf("front = ");
		queue.print_obj(&temp);

		queue.back(&queue, &temp);
		printf("\tback = ");
		queue.print_obj(&temp);

		printf("\tsize = %2d\n", queue.size(&queue));
	}
	printf("----- print -----\n");
	queue.print(&queue);
	printf("\n");

	queue.clear(&queue);
	if (queue.empty(&queue))
	{
		printf("----- empty -----\n");
	}

	printf("----- push -----\n");
	for (i = 0; i < len; i++)
	{
		queue.push(&queue, &data[i]);
	}

	printf("----- after pop -----\n");
	for (i = 0; i < len + 1; i++)
	{
		if (true == queue.pop(&queue, &temp))
		{
			printf("pop = ");
			queue.print_obj(&temp);

			if (true == queue.front(&queue, &temp))
			{
				printf("front = ");
				queue.print_obj(&temp);
			}

			if (queue.back(&queue, &temp))
			{
				printf("back = ");
				queue.print_obj(&temp);
			}

			printf("size = %2d\n", queue.size(&queue));
		}
		else
		{
			printf("pop failed! because it is empty\n");
		}

		if (queue.empty(&queue))
		{
			printf("----- empty -----\n");
		}
	}

	printf("----- print -----\n");
	queue.print(&queue);
	printf("\n");

	queue.destory(&queue);
}

void queue_test(void)
{
	// queue_test_num();
	queue_test_char();
}

#endif

