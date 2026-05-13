/**
 * @file test_darray.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"


static void test_darray_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(darray_new(0, 0));
    // TEST_ASSERT_NULL(darray_new(0, 1));

    darray_t darray = darray_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(darray);
    darray_free(&darray);
    TEST_ASSERT_NULL(darray);
}

static void test_darray_new_lazy(void)
{
    darray_t darray = darray_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(darray);
    TEST_ASSERT_EQUAL_size_t(0, darray->capacity(darray));

    int temp = 0;
    TEST_ASSERT_TRUE(darray->insert(darray, 0, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, darray->capacity(darray));
    darray_free(&darray);
}

static void test_darray_insert(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->print_obj = print_num;

    TEST_ASSERT_TRUE(darray->empty(darray));
    TEST_ASSERT_FALSE(darray->full(darray));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->insert(darray, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(darray->empty(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));

    darray_free(&darray);
}
    
static void test_darray_insert_invalid(void)
{
    int temp = 0;

    darray_t darray = darray_new(sizeof(int), 0);
    darray->print_obj = print_num;

    TEST_ASSERT_FALSE(darray->insert(darray, 1, &temp));
    TEST_ASSERT_FALSE(darray->insert(darray, -1, &temp));
    TEST_ASSERT_FALSE(darray->insert(darray, 999, &temp));

    TEST_ASSERT_FALSE(darray->insert(darray, 0, NULL));

    TEST_ASSERT_TRUE(darray->insert(darray, 0, &temp));
    darray_free(&darray);
}

static void test_darray_append(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    TEST_ASSERT_TRUE(darray->empty(darray));
    TEST_ASSERT_FALSE(darray->full(darray));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        size_t index = darray->size(darray) - 1;
        TEST_ASSERT_TRUE(darray->get(darray, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(darray->empty(darray));
    }
    TEST_ASSERT_TRUE(darray->full(darray));
    darray_free(&darray);
}

static void test_darray_append_invalid(void)
{
    int temp = 0;

    darray_t darray = darray_new(sizeof(int), 0);
    darray->compare = compare_num;

    TEST_ASSERT_FALSE(darray->append(darray, NULL));

    darray_free(&darray);
}

static void test_darray_remove(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_TRUE(darray->remove(darray, len - 1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
    TEST_ASSERT_FALSE(darray->full(darray));

    for (i = 0; i < len - 2; i++)
    {
        TEST_ASSERT_TRUE(darray->remove(darray, 1, &temp));
        TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

        TEST_ASSERT_FALSE(darray->full(darray));
    }

    TEST_ASSERT_TRUE(darray->remove(darray, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(darray->empty(darray));

    // ---------- no return ----------
    for(i = 0; i < 2; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_FALSE(darray->remove(darray, 2, NULL));
    TEST_ASSERT_TRUE(darray->remove(darray, 1, NULL));
    TEST_ASSERT_TRUE(darray->remove(darray, 0, NULL));

    darray_free(&darray);
}

static void test_darray_remove_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_FALSE(darray->remove(darray, len, &temp));
    TEST_ASSERT_FALSE(darray->remove(darray, -1, &temp));
    TEST_ASSERT_FALSE(darray->remove(darray, 999, &temp));

    darray_free(&darray);
}

static void test_darray_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->pop(darray, &temp));
        TEST_ASSERT_EQUAL_INT(data[len -1 - i], temp);

        TEST_ASSERT_FALSE(darray->full(darray));
    }
    TEST_ASSERT_TRUE(darray->empty(darray));

    // ---------- no return ----------
    for(i = 0; i < 2; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_TRUE(darray->pop(darray, NULL));
    TEST_ASSERT_TRUE(darray->pop(darray, NULL));
    TEST_ASSERT_FALSE(darray->pop(darray, NULL));

    darray_free(&darray);
}

static void test_darray_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));

        size_t index = darray->size(darray) - 1;
        TEST_ASSERT_TRUE(darray->get(darray, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(darray->set(darray, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(darray->set(darray, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(darray->set(darray, 9, &temp));

    TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(darray->get(darray, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(darray->get(darray, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    darray_free(&darray);
}

static void test_darray_set_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(darray->set(darray, -1, &temp));
    TEST_ASSERT_FALSE(darray->set(darray, len, &temp));
    TEST_ASSERT_FALSE(darray->set(darray, 999, &temp));

    TEST_ASSERT_FALSE(darray->set(darray, 0, NULL));

    darray_free(&darray);
}

static void test_darray_resize(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), 1);
    darray->compare = compare_num;

    TEST_ASSERT_EQUAL_INT(1, darray->capacity(darray));
    darray->resize(darray, 16);
    TEST_ASSERT_EQUAL_INT(16, darray->capacity(darray));

    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, darray->capacity(darray));
    TEST_ASSERT_EQUAL_INT(10, darray->size(darray));

    TEST_ASSERT_TRUE(darray->resize(darray, 8));
    TEST_ASSERT_EQUAL_INT(8, darray->capacity(darray));
    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(darray->get(darray, i, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(darray->get(darray, i, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, darray->capacity(darray));
    TEST_ASSERT_EQUAL_INT(8, darray->size(darray));

    darray_free(&darray);
}

static void test_darray_resize_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    
    TEST_ASSERT_EQUAL_INT(len, darray->capacity(darray));
    TEST_ASSERT_FALSE(darray->resize(darray, 0));
    TEST_ASSERT_FALSE(darray->resize(darray, -1));

    darray_free(&darray);
}

static void test_darray_index(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    temp = 1;
    TEST_ASSERT_EQUAL_INT(0, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 5;
    TEST_ASSERT_EQUAL_INT(4, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 10;
    TEST_ASSERT_EQUAL_INT(9, darray->index(darray, &temp));
    TEST_ASSERT_TRUE(darray->contains(darray, &temp));

    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, darray->index(darray, &temp));
    TEST_ASSERT_FALSE(darray->contains(darray, &temp));

    TEST_ASSERT_EQUAL_INT(-1, darray->index(darray, NULL));

    darray_free(&darray);
}

static void test_darray_index_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, darray->index(darray, &temp));
    TEST_ASSERT_FALSE(darray->contains(darray, &temp));

    TEST_ASSERT_EQUAL_INT(-1, darray->index(darray, NULL));
    TEST_ASSERT_FALSE(darray->contains(darray, NULL));

    darray_free(&darray);
}


static void test_darray_at(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }

    const int *p_int = NULL;
    p_int = darray->at(darray, 0);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = darray->at(darray, 4);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = darray->at(darray, 9);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    TEST_ASSERT_NULL(darray->at(darray, 10));
    TEST_ASSERT_NULL(darray->at(darray, -1));


    //  warning: initialization discards 'const' qualifier from pointer target type
    // int *p_int_warring = darray->at(darray, 0);

    // !!! you should not do this.
    int *p_int_warring = (int *)darray->at(darray, 0);
    *p_int_warring = 100;

    darray->get(darray, 0, &temp);
    TEST_ASSERT_EQUAL_INT(100, temp);

    darray_free(&darray);
}

static void test_darray_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    darray_t darray = darray_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->insert(darray, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, darray->capacity(darray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(darray->full(darray));
        }
        else
        {
            TEST_ASSERT_TRUE(darray->full(darray));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->insert(darray, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, darray->capacity(darray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(darray->full(darray));
        }
        else
        {
            TEST_ASSERT_TRUE(darray->full(darray));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->insert(darray, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
        
        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, darray->capacity(darray));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(darray->full(darray));
        }
        else
        {
            TEST_ASSERT_TRUE(darray->full(darray));
        }
    }

    darray_free(&darray);
}

static void test_darray_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    darray_t darray = darray_new(sizeof(int), len);
    darray->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        darray->append(darray, &data[i]);
    }
    TEST_ASSERT_TRUE(darray->full(darray));

    TEST_ASSERT_TRUE(darray->clear(darray));
    TEST_ASSERT_TRUE(darray->empty(darray));

    darray_free(&darray);
}

static void test_darray_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    darray_t darray = darray_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(darray);
    darray->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));

        TEST_ASSERT_TRUE(darray->get(darray, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(darray->get(darray, darray->size(darray) - 1, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, darray->size(darray));
    }
    TEST_ASSERT_FALSE(darray->empty(darray));
    TEST_ASSERT_TRUE(darray->clear(darray));
    TEST_ASSERT_TRUE(darray->empty(darray));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(darray->append(darray, &data[i]));
    }

    darray_free(&darray);
    TEST_ASSERT_NULL(darray);
}


void test_darray(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_darray_new);
    RUN_TEST(test_darray_new_lazy);

    RUN_TEST(test_darray_insert);
    RUN_TEST(test_darray_insert_invalid);

    RUN_TEST(test_darray_append);
    RUN_TEST(test_darray_append_invalid);

    RUN_TEST(test_darray_remove);
    RUN_TEST(test_darray_remove_invalid);

    RUN_TEST(test_darray_pop);

    RUN_TEST(test_darray_set);
    RUN_TEST(test_darray_set_invalid);

    RUN_TEST(test_darray_resize);
    RUN_TEST(test_darray_resize_invalid);

    RUN_TEST(test_darray_index);
    RUN_TEST(test_darray_index_invalid);

    RUN_TEST(test_darray_at);

    RUN_TEST(test_darray_dynamic);

    // ---------- base ----------
    RUN_TEST(test_darray_clear);
    
    // ---------- ext ----------
    RUN_TEST(test_darray_struct);
}
