/**
 * @file test_heap.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

static void* get_max(struct _heap* heap, void *array, int start, int end)
{
    void* max = array;
    for (int i = start; i < end; i++)
    {
        if (heap->compare((char*)array + heap->_obj_size * i, max) > 0)
        {
            max = (char*)array + heap->_obj_size * i;
        }
    }
    return max;
}

static void* get_min(struct _heap* heap, void *array, int start, int end)
{
    void* min = array;
    for (int i = start; i < end; i++)
    {
        if (heap->compare((char*)array + heap->_obj_size * i, min) < 0)
        {
            min = (char*)array + heap->_obj_size * i;
        }
    }
    return min;
}

static void test_heap_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_new2(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    // default: maxheap
    // maxheap or minheap
    heap->setmin(heap, true);

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));
    }
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));
    TEST_ASSERT_EQUAL_INT(*(int *)get_min(heap, data, 0, heap->size(heap)), temp);

    TEST_ASSERT_TRUE(heap->clear(heap));
    TEST_ASSERT_TRUE(heap->empty(heap));
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
    }

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->pop(heap, &temp));
    }
    TEST_ASSERT_TRUE(heap->empty(heap));

    heap_free(&heap);
    TEST_ASSERT_NULL(heap);
}

static void test_heap_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_new2(sizeof(struct _student), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));
    }

    TEST_ASSERT_TRUE(heap->peek(heap, &temp));
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));
    TEST_ASSERT_EQUAL_INT(((struct _student*)get_min(heap, data, 0, heap->size(heap)))->id, temp.id);
    TEST_ASSERT_EQUAL_STRING(((struct _student*)get_min(heap, data, 0, heap->size(heap)))->name, temp.name);

    TEST_ASSERT_TRUE(heap->clear(heap));
    TEST_ASSERT_TRUE(heap->empty(heap));
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
    }

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->pop(heap, &temp));
    }
    TEST_ASSERT_TRUE(heap->empty(heap));

    heap_free(&heap);
    TEST_ASSERT_NULL(heap);
}

void test_heap(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_heap_num);
    RUN_TEST(test_heap_struct);
}
