/**
 * @file demo.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "demo.h"

void print_num(const void* obj)
{
    printf("(%2d ) ", *(int*)obj);
}

int compare_num(const void *obj, const void *obj2)
{
    int num1 = *(int*)obj;
    int num2 = *(int*)obj2;
    if(num1 == num2)
    {
        return 0;
    }
    return num1 > num2 ? 1 : -1;
}

void print_struct(const void* obj)
{
    struct _student* student = (struct _student*)obj;
    printf("(%4d:%-8s) ", student->id, student->name);
}

int compare_struct(const void *obj, const void *obj2)
{
    struct _student num1 = *(struct _student*)obj;
    struct _student num2 = *(struct _student*)obj2;
    if(num1.id == num2.id)
    {
        return 0;
    }
    return num1.id > num2.id ? 1 : -1;
}

void print_char(const void* obj)
{
    printf("(%2c ) ", *(char*)obj);
}

void print_str(const void* obj)
{
    printf("(%s ) ", (char*)obj);
}

int main()
{
    printf("----- unicstl demo -----\n");
    // while (1)
    {
        demo_queue();
        demo_stack();
        demo_arraylist();
        demo_deque();
        demo_tree();
        demo_heap();
        demo_graph();
    }

    printf("----- unicstl ok -----\n");
    return 0;
}
