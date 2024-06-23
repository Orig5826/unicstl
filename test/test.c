
#include "test.h"

void print_num(void* obj)
{
    printf("(%2d ) ", *(int*)obj);
}

int compare_num(void *obj, void *obj2)
{
    int num1 = *(int*)obj;
    int num2 = *(int*)obj2;
    return num1 - num2 > 0 ? 1 : -1;
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
        // test_list();
        // test_stack();
        // test_deque();
        // test_queue();
        test_tree();

        // rbtree_test();
    }
    return 0;
}
