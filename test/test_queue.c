
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

void queue_test(void)
{
	
}

#endif

