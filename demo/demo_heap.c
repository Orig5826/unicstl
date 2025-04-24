/**
 * @file demo_heap.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "demo.h"

void demo_heap_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_min_new2(sizeof(int), 64);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    printf("\n\n----- demo_heap_num -----\n");

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->push(heap, &temp);

        printf("push = ");
        heap->print_obj(&temp);
        printf("size = %2d : ", heap->size(heap));
        heap->print(heap);
        printf("\n");
    }

    printf("----- max/min -----\n");
    heap->peek(heap, &temp);
    heap->print_obj(&temp);
    printf("\n");

    printf("----- heap -----\n");
    heap->clear(heap);
    if(heap->empty(heap))
    {
        printf("----- empty -----\n");
    }
    printf("----- heap -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->push(heap, &temp);
    }

    printf("----- pop -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->pop(heap, &temp);

        printf("pop = ");
        heap->print_obj(&temp);
        printf("size = %2d : ", heap->size(heap));
        heap->print(heap);
        printf("\n");
    }
    if(heap->empty(heap))
    {
        printf("----- empty -----\n");
    }
    heap_free(&heap);
}

static void demo_heap_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_min_new2(sizeof(struct _student), 64);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    printf("\n\n----- demo_heap_num -----\n");
    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->push(heap, &temp);

        printf("push = ");
        heap->print_obj(&temp);
        printf("size = %2d : ", heap->size(heap));
        heap->print(heap);
        printf("\n");
    }

    printf("----- max/min -----\n");
    heap->peek(heap, &temp);
    heap->print_obj(&temp);
    printf("\n");

    printf("----- heap -----\n");
    heap->clear(heap);
    if(heap->empty(heap))
    {
        printf("----- empty -----\n");
    }
    printf("----- heap -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->push(heap, &temp);
    }

    printf("----- pop -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        heap->pop(heap, &temp);

        printf("pop = ");
        heap->print_obj(&temp);
        printf("size = %2d : ", heap->size(heap));
        heap->print(heap);
        printf("\n");
    }
    if(heap->empty(heap))
    {
        printf("----- empty -----\n");
    }
    heap_free(&heap);
}

void demo_heap(void)
{
    demo_heap_num();
    demo_heap_struct();
}
