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

static const void* get_max(const void *base, size_t index, size_t count, size_t obj_size, compare_fun_t compare)
{
    const void* max = base;
    if(count <= 1)
    {
        return base;
    }
    size_t idx = 0;
    for (size_t i = 0; i < count; i++)
    {
        idx = index + i * obj_size;
        if (compare((char*)base + idx, max) > 0)
        {
            max = (char*)base + idx;
        }
    }
    return max;
}

static const void* get_min(const void *base, size_t index, size_t count, size_t obj_size, compare_fun_t compare)
{
    const void* min = base;
    if(count <= 1)
    {
        return base;
    }
    size_t idx = 0;
    for (size_t i = 0; i < count ; i++)
    {
        idx = index + i * obj_size;
        if (compare((char*)base + idx, min) < 0)
        {
            min = (char*)base + idx;
        }
    }
    return min;
}

static void test_heap_min_num(void)
{
    size_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);
    int min = 0;

    heap_t heap = heap_min_new(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        min = *(int *)get_min(data, 0, i + 1, sizeof(int), compare_num);
        log_debug("i = %d, min = %d, heap_peek: %d, ", i, min, temp);
        TEST_ASSERT_EQUAL_INT(min, temp);
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
    size_t i = 0;
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
    size_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_min_new(sizeof(struct _student), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(((struct _student*)get_min(data, 0, i + 1, sizeof(struct _student), compare_struct))->id, temp.id);
        TEST_ASSERT_EQUAL_STRING(((struct _student*)get_min(data, 0, i + 1, sizeof(struct _student), compare_struct))->name, temp.name);
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
    size_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_max_new(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(*(int *)get_max(data, 0, i + 1, sizeof(int), compare_num), temp);
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
    size_t i = 0;
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
    size_t len = sizeof(data) / sizeof(data[0]);

    heap_t heap = heap_max_new(sizeof(struct _student), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_struct;
    heap->compare = compare_struct;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(((struct _student*)get_max(data, 0, i + 1, sizeof(struct _student), compare_struct))->id, temp.id);
        TEST_ASSERT_EQUAL_STRING(((struct _student*)get_max(data, 0, i + 1, sizeof(struct _student), compare_struct))->name, temp.name);

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
    size_t i = 0;
    int data[15] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);
    int out[15] = { 0 };
    int outlen = 0;

    heap_t heap = heap_max_new(sizeof(int), 64);
    TEST_ASSERT_NOT_NULL(heap);
    heap->print_obj = print_num;
    heap->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        TEST_ASSERT_TRUE(heap->push(heap, &temp));
        TEST_ASSERT_EQUAL_INT(i + 1, heap->size(heap));

        TEST_ASSERT_TRUE(heap->peek(heap, &temp));
        TEST_ASSERT_EQUAL_INT(*(int *)get_max(data, 0, i + 1, sizeof(int), compare_num), temp);

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
