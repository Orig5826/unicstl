/**
 * @file test_segarray.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

static void test_segarray_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(segarray_new(0, 0));
    // TEST_ASSERT_NULL(segarray_new(0, 1));

    segarray_t segarray = segarray_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(segarray);
    segarray_free(&segarray);
    TEST_ASSERT_NULL(segarray);
}

static void test_segarray_new_lazy(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(segarray);
    TEST_ASSERT_EQUAL_size_t(0, segarray->capacity(segarray));

    int temp = 0;
    TEST_ASSERT_TRUE(segarray->push_back(segarray, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, segarray->capacity(segarray));
    segarray_free(&segarray);
}

static void test_segarray_push_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);
    log_info("test_segarray_push_back");

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        log_debug("i:%d", i);
        TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));
        log_debug("push_back ok. size:%d, capacity:%d", segarray->size(segarray), segarray->capacity(segarray));

        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
    }
    TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[0]));
    TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 2, segarray->size(segarray));

    segarray_free(&segarray);
    log_info("test_segarray_push_back ok");
}

static void test_segarray_push_back_invalid(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(segarray->push_back(segarray, NULL));
    segarray_free(&segarray);
    log_info("test_segarray_push_back_invalid ok");
}

static void test_segarray_push_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));

        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1], temp);

        TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
    }
    TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[0]));
    TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[0]));
    TEST_ASSERT_EQUAL_INT(len + 2, segarray->size(segarray));

    segarray_free(&segarray);
}

static void test_segarray_push_front_invalid(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(segarray->push_front(segarray, NULL));
    segarray_free(&segarray);
}

static void test_segarray_pop_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
    TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
    for (i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->pop_back(segarray, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_back(segarray, &temp));
        }

        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);

            TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
            TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
        }
    }
    TEST_ASSERT_TRUE(segarray->empty(segarray));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    TEST_ASSERT_TRUE(segarray->pop_back(segarray, NULL));
    TEST_ASSERT_TRUE(segarray->pop_back(segarray, NULL));
    TEST_ASSERT_FALSE(segarray->pop_back(segarray, NULL));

    segarray_free(&segarray);
    log_info("test_segarray_pop_back pass");
}

static void test_segarray_pop_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);
    log_info("test_segarray_pop_front start");

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
    TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
    for (i = 0; i < len; i++)
    {
        segarray->push_front(segarray, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->pop_front(segarray, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_front(segarray, &temp));
        }

        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1], temp);

            TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
            TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
        }
    }
    TEST_ASSERT_TRUE(segarray->empty(segarray));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    TEST_ASSERT_TRUE(segarray->pop_front(segarray, NULL));
    TEST_ASSERT_TRUE(segarray->pop_front(segarray, NULL));
    TEST_ASSERT_FALSE(segarray->pop_front(segarray, NULL));

    segarray_free(&segarray);
}

static void test_segarray_back(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);

    TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
    for (i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        segarray->pop_back(segarray, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
        }
    }

    TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
    for (i = 0; i < len; i++)
    {
        segarray->push_front(segarray, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        segarray->pop_front(segarray, &temp);

        if (i != len - 1)
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 2 - i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
        }
    }

    segarray_free(&segarray);
}

static void test_segarray_back_invalid(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(segarray->back(segarray, NULL));
    segarray_free(&segarray);
}

static void test_segarray_front(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
    for (i = 0; i < len; i++)
    {
        segarray->push_front(segarray, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->pop_front(segarray, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_front(segarray, &temp));
        }

        if (!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1], temp);

            TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
            TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
        }
    }
    TEST_ASSERT_TRUE(segarray->empty(segarray));

    // ---------- no return ----------
    for (i = 0; i < 2; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    TEST_ASSERT_TRUE(segarray->pop_front(segarray, NULL));
    TEST_ASSERT_TRUE(segarray->pop_front(segarray, NULL));
    TEST_ASSERT_FALSE(segarray->pop_front(segarray, NULL));

    segarray_free(&segarray);
}

static void test_segarray_front_invalid(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 1);
    TEST_ASSERT_FALSE(segarray->front(segarray, NULL));
    segarray_free(&segarray);
}

static void test_segarray_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    segarray_t segarray = segarray_new(sizeof(int), len);
    // segarray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));

        size_t index = segarray->size(segarray) - 1;
        TEST_ASSERT_TRUE(segarray->get(segarray, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(segarray->set(segarray, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(segarray->set(segarray, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(segarray->set(segarray, 9, &temp));

    TEST_ASSERT_TRUE(segarray->get(segarray, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(segarray->get(segarray, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(segarray->get(segarray, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    segarray_free(&segarray);
}

static void test_segarray_set_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    segarray_t segarray = segarray_new(sizeof(int), len);
    // segarray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(segarray->set(segarray, -1, &temp));
    TEST_ASSERT_FALSE(segarray->set(segarray, len, &temp));
    TEST_ASSERT_FALSE(segarray->set(segarray, 999, &temp));

    TEST_ASSERT_FALSE(segarray->set(segarray, 0, NULL));

    segarray_free(&segarray);
}

static void test_segarray_at(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    segarray_t segarray = segarray_new(sizeof(int), len);
    // segarray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }

    const int *p_int = NULL;
    p_int = segarray->at(segarray, 0);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = segarray->at(segarray, 4);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = segarray->at(segarray, 9);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    TEST_ASSERT_NULL(segarray->at(segarray, 10));
    TEST_ASSERT_NULL(segarray->at(segarray, -1));

    //  warning: initialization discards 'const' qualifier from pointer target type
    // int *p_int_warring = segarray->at(segarray, 0);

    // !!! you should not do this.
    int *p_int_warring = (int *)segarray->at(segarray, 0);
    *p_int_warring = 100;

    segarray->get(segarray, 0, &temp);
    TEST_ASSERT_EQUAL_INT(100, temp);

    segarray_free(&segarray);
    log_info("segarray_at cuccess!");
}

static void test_segarray_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(len, segarray->size(segarray));

    iterator_t iter = segarray->iter(segarray, LINEAR_FORWARD);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        log_debug("iter-test: i=%d", i);
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);
    log_info("iter-forward cuccess!");

    iter = segarray->iter(segarray, LINEAR_REVERSE);
    i = len - 1;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        log_debug("iter-test: i=%d", i);
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }
    TEST_ASSERT_EQUAL_INT(0, i);
    log_info("iter-reverse cuccess!");

    segarray_free(&segarray);
}

static void test_segarray_reserve(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    segarray_t segarray = segarray_new(sizeof(int), len);

    TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
    TEST_ASSERT_TRUE(segarray->reserve(segarray, 16));
    TEST_ASSERT_EQUAL_INT(16, segarray->capacity(segarray));

    for(i = 0; i < len; i++)
    {
        segarray->push_back(segarray, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, segarray->capacity(segarray));
    TEST_ASSERT_EQUAL_INT(len, segarray->size(segarray));

    TEST_ASSERT_TRUE(segarray->reserve(segarray, 8));
    TEST_ASSERT_EQUAL_INT(8, segarray->capacity(segarray));
    TEST_ASSERT_EQUAL_INT(8, segarray->size(segarray));

    TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
    TEST_ASSERT_EQUAL_INT(data[7], temp);

    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(segarray->pop_front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_front(segarray, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, segarray->capacity(segarray));
    TEST_ASSERT_EQUAL_INT(0, segarray->size(segarray));

    segarray_free(&segarray);
}

static void test_segarray_reserve_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    segarray_t segarray = segarray_new(sizeof(int), len);
    
    TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
    TEST_ASSERT_FALSE(segarray->reserve(segarray, 0));
    TEST_ASSERT_FALSE(segarray->reserve(segarray, -1));

    segarray_free(&segarray);
}

static void test_segarray_reserve_edge(void)
{
    segarray_t segarray = segarray_new(sizeof(int), 10);

    TEST_ASSERT_EQUAL_INT(10, segarray->capacity(segarray));
    TEST_ASSERT_TRUE(segarray->reserve(segarray, 10));
    TEST_ASSERT_EQUAL_INT(10, segarray->capacity(segarray));

    segarray_free(&segarray);
}

static void test_segarray_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    segarray_t segarray = segarray_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
        
        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(segarray->full(segarray));
        }
        else
        {
            TEST_ASSERT_TRUE(segarray->full(segarray));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
        
        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(segarray->full(segarray));
        }
        else
        {
            TEST_ASSERT_TRUE(segarray->full(segarray));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
        
        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(segarray->full(segarray));
        }
        else
        {
            TEST_ASSERT_TRUE(segarray->full(segarray));
        }
    }

    segarray_free(&segarray);
}

static void test_segarray_dynamic2(void)
{
    int temp = 0;
    size_t i = 0;
    size_t len = 10;
    segarray_t segarray = segarray_new(sizeof(int), 2);
    TEST_ASSERT_EQUAL_INT(0, segarray->size(segarray));

    for(i = 0; i < len; i++)
    {
        segarray->push_front(segarray, &temp);
    }
    TEST_ASSERT_EQUAL_INT(10, segarray->size(segarray));

    len *= 2;
    for(; i < len; i++)
    {
        segarray->push_front(segarray, &temp);
    }
    TEST_ASSERT_EQUAL_INT(32, segarray->size(segarray));

    len *= 2;
    for(; i < len; i++)
    {
        segarray->push_front(segarray, &temp);
    }
    TEST_ASSERT_EQUAL_INT(64, segarray->size(segarray));

    segarray_free(&segarray);
}


static void test_segarray_status(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(int), len);
    segarray->print_obj = print_num;

    TEST_ASSERT_EQUAL_INT(len, segarray->capacity(segarray));
    TEST_ASSERT_EQUAL_INT(0, segarray->size(segarray));

    TEST_ASSERT_TRUE(segarray->empty(segarray));
    TEST_ASSERT_FALSE(segarray->full(segarray));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));

        TEST_ASSERT_FALSE(segarray->empty(segarray));
        TEST_ASSERT_FALSE(segarray->full(segarray));
    }
    TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));
    TEST_ASSERT_TRUE(segarray->full(segarray));
    TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));

    TEST_ASSERT_TRUE(segarray->clear(segarray));
    TEST_ASSERT_TRUE(segarray->empty(segarray));
    TEST_ASSERT_FALSE(segarray->full(segarray));

    segarray_free(&segarray);   
}

static void test_segarray_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    segarray_t segarray = segarray_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(segarray);
    segarray->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));

        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
    }
    TEST_ASSERT_FALSE(segarray->empty(segarray));
    TEST_ASSERT_TRUE(segarray->clear(segarray));
    TEST_ASSERT_TRUE(segarray->empty(segarray));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_back(segarray, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->pop_back(segarray, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_back(segarray, &temp));
        }
        
        if(!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

            TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[segarray->size(segarray) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
            TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
        }
    }
    TEST_ASSERT_TRUE(segarray->empty(segarray));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
        
        TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, segarray->size(segarray));
    }
    TEST_ASSERT_TRUE(segarray->clear(segarray));
    TEST_ASSERT_TRUE(segarray->empty(segarray));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->pop_front(segarray, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->pop_front(segarray, &temp));
        }
        
        if(!segarray->empty(segarray))
        {
            TEST_ASSERT_TRUE(segarray->front(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[segarray->size(segarray) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[segarray->size(segarray) - 1].name, temp.name);

            TEST_ASSERT_TRUE(segarray->back(segarray, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(segarray->front(segarray, &temp));
            TEST_ASSERT_FALSE(segarray->back(segarray, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(segarray->push_front(segarray, &data[i]));
    }

    segarray_free(&segarray);
    TEST_ASSERT_NULL(segarray);
}


void test_segarray(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_segarray_new);
    RUN_TEST(test_segarray_new_lazy);

    RUN_TEST(test_segarray_push_back);
    RUN_TEST(test_segarray_push_back_invalid);

    RUN_TEST(test_segarray_push_front);
    RUN_TEST(test_segarray_push_front_invalid);

    RUN_TEST(test_segarray_pop_back);
    RUN_TEST(test_segarray_pop_front);

    RUN_TEST(test_segarray_back);
    RUN_TEST(test_segarray_back_invalid);

    RUN_TEST(test_segarray_front);
    RUN_TEST(test_segarray_front_invalid);

    // ---------- random access ----------
    RUN_TEST(test_segarray_set);
    RUN_TEST(test_segarray_set_invalid);

    RUN_TEST(test_segarray_at);

    // ---------- base ----------
    RUN_TEST(test_segarray_iter);

    RUN_TEST(test_segarray_reserve);
    RUN_TEST(test_segarray_reserve_invalid);
    RUN_TEST(test_segarray_reserve_edge);

    RUN_TEST(test_segarray_dynamic);
    // RUN_TEST(test_segarray_dynamic2);    // todo: fix it

    RUN_TEST(test_segarray_status);
    
    // ---------- ext ----------
    RUN_TEST(test_segarray_struct);
}
