#include "test.h"

#if STACK_TEST == 1

void stack_test(void)
{
	int32_t i = 0;
	uint32_t size = 0;
	stack_data_t dat[10] = {0,1,2,3,4,5,6,7,8,9};
	stack_data_t tmp;
	pstack_t pst;
	if(!stack_init(&pst))
	{
		printf("failure -> stack_init\n");
	}
	printf("success -> stack_init\n");

	// push
	for(i = 0; i < 10; i++)
	{
		if(!stack_push(pst,dat[i]))
		{
			printf("failure -> stack_push\n");
		}
		printf("    push %d\n",dat[i]);
	}
	printf("success -> stack_push\n");

	// stack size
	size = stack_get_size(pst);
	if(size != 10)
	{
		printf("failure -> the size of stack is %d\n",size);
	}
	else
	{
		printf("success -> the size of stack is %d\n",size);
	}

	if(!stack_empty(pst))
	{
		printf("success -> the stack is not empty!\n");
	}
	else
	{
		printf("failure -> the stack is empty!\n");
	}

	// pop
	for(i = 0; i < 10; i++)
	{
		stack_get_top(pst,&tmp);
		printf("    top = %d",tmp);
		stack_pop(pst,&tmp);
		printf("    pop %d\n",tmp);
	}
	printf("stack_pop success!\n");

	// stack size
	size = stack_get_size(pst);
	if(size != 0)
	{
		printf("failure -> the size of stack is %d\n",size);
	}
	else
	{
		printf("success -> the size of stack is %d\n",size);
	}

	if(stack_empty(pst))
	{
		printf("success -> the stack is empty!\n");
	}
	else
	{
		printf("failure -> the stack is empty!\n");
	}

	for(i = 0; i < 5; i++)
	{
		stack_push(pst,dat[i]);
	}
	if(!stack_empty(pst))
	{
		stack_clear(pst);
		printf("success -> stack_clear\n");
		if(stack_empty(pst))
		{
			printf("success -> the stack is empty!\n");
		}
	}

	stack_destroy(&pst);
	printf("success -> stack_destroy\n");

	if(!stack_push(pst,dat[0]))
	{
		printf("success -> stack_push failed!\n");
	}

	stack_pop(pst,&tmp);
	printf("success -> stack_pop invalid!\n");

	if(stack_empty(pst))
	{
		printf("success -> If pst is NULL, stack_empty alse return true!\n");
	}

	printf("----------------------------------------\n");
}

#endif

