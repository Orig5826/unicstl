
#include "test.h"

void print_num(void* obj)
{
	printf("(%2d ) ", *(int*)obj);
}

void print_struct(void* obj)
{
	struct _student* student = (struct _student*)obj;
	printf("(%4d:%-8s) ", student->id, student->name);
}

void print_char(void* obj)
{
	printf("(%2c ) ", *(char*)obj);
}

void print_str(void* obj)
{
	printf("(%s ) ", (char*)obj);
}

int main()
{
	printf("----- unicstl test -----\n");
	// while (1)
	{	
		// list_test();
		// test_stack();
		deque_test();
		// queue_test();
		
		// tree_test();
		// rbtree_test();
	}
	return 0;
}
