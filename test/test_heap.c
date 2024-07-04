/**
 * @file test_heap.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

void test_heap_num(void)
{
    uint32_t i = 0;
    int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    // int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_new();
    heap_init2(heap, sizeof(int), 64);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    printf("\n\n----- test_heap_num -----\n");

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

    printf("----- max -----\n");
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
}

void test_heap(void)
{
    test_heap_num();
}
