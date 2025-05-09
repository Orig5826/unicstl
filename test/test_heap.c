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

static void test_heap_min_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_min_new2(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(*(int *)get_min(heap, data, 0, heap->size(heap)), temp);
    }
    
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

static void test_heap_min_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"sun", 1003}, 
        {"zhou", 1005}, 
        {"wu", 1006}, 
        {"zhao", 1001}, 
        {"qian", 1002}, 
        {"li", 1004},
        {"zheng", 1007}, 
        {"wang", 1008},
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_min_new2(sizeof(struct _student), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(((struct _student*)get_min(heap, data, 0, heap->size(heap)))->id, temp.id);
        TEST_ASSERT_EQUAL_STRING(((struct _student*)get_min(heap, data, 0, heap->size(heap)))->name, temp.name);
    }
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));

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

static void test_heap_max_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_max_new2(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(*(int *)get_max(heap, data, 0, heap->size(heap)), temp);
    }

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

static void test_heap_max_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"sun", 1003}, 
        {"zhou", 1005}, 
        {"wu", 1006}, 
        {"zhao", 1001}, 
        {"qian", 1002}, 
        {"li", 1004},
        {"zheng", 1007}, 
        {"wang", 1008},
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_max_new2(sizeof(struct _student), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(((struct _student*)get_max(heap, data, 0, heap->size(heap)))->id, temp.id);
        TEST_ASSERT_EQUAL_STRING(((struct _student*)get_max(heap, data, 0, heap->size(heap)))->name, temp.name);

        // heap->print_obj(&temp);
        // printf("\n");
    }
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));
    TEST_ASSERT_TRUE(heap->peek(heap, &temp));

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

const int heap_max_iter_expect[15][15] = {
    {5},
    {5, 2},
    {5, 2, 3},
    {5, 2, 3, 1},
    {7, 5, 3, 1, 2},
    {8, 5, 7, 1, 2, 3},
    {8, 5, 7, 1, 2, 3, 6},
    {8, 5, 7, 4, 2, 3, 6, 1},
    {9, 8, 7, 5, 2, 3, 6, 1, 4},
    {10, 9, 7, 5, 8, 3, 6, 1, 4, 2},
    {12, 10, 7, 5, 9, 3, 6, 1, 4, 2, 8},
    {12, 10, 11, 5, 9, 7, 6, 1, 4, 2, 8, 3},
    {15, 10, 12, 5, 9, 11, 6, 1, 4, 2, 8, 3, 7},
    {15, 10, 14, 5, 9, 11, 12, 1, 4, 2, 8, 3, 7, 6},
    {15, 10, 14, 5, 9, 11, 13, 1, 4, 2, 8, 3, 7, 6, 12}
};

static void test_heap_max_iter(void)
{
    uint32_t i = 0;
    int data[15] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    int out[15] = { 0 };
    int outlen = 0;

    heap_t heap = heap_max_new2(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(*(int *)get_max(heap, data, 0, heap->size(heap)), temp);

        iterator_t iter = heap->iter(heap);

        memset(out, 0, sizeof(out));
        outlen = 0;
        while(iter->hasnext(iter))
        {
            temp = *(int*)iter->next(iter);
            out[outlen] = temp;
            outlen++;
        }
        TEST_ASSERT_EQUAL_INT_ARRAY(&heap_max_iter_expect[i], out, outlen);
    }

    heap_free(&heap);
    TEST_ASSERT_NULL(heap);
}

void test_heap(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_heap_min_num);
    RUN_TEST(test_heap_min_struct);

    RUN_TEST(test_heap_max_num);
    RUN_TEST(test_heap_max_struct);

    RUN_TEST(test_heap_max_iter);
}
