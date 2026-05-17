/**
 * @file test_arraylist.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

#ifdef UNICSTL_ARRAYLIST

static void test_arraylist_new(void)
{
    // [invalid param] if obj_size==0, unit test is not needed. because assert will be triggered.
    // TEST_ASSERT_NULL(arraylist_new(0, 0));
    // TEST_ASSERT_NULL(arraylist_new(0, 1));

    arraylist_t arraylist = arraylist_new(sizeof(int), 10);
    TEST_ASSERT_NOT_NULL(arraylist);
    arraylist_free(&arraylist);
    TEST_ASSERT_NULL(arraylist);
}

static void test_arraylist_new_lazy(void)
{
    arraylist_t arraylist = arraylist_new(sizeof(int), 0);
    TEST_ASSERT_NOT_NULL(arraylist);
    TEST_ASSERT_EQUAL_size_t(0, arraylist->capacity(arraylist));

    int temp = 0;
    TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &temp));
    TEST_ASSERT_EQUAL_size_t(UNICSTL_CAPACITY_INIT, arraylist->capacity(arraylist));
    arraylist_free(&arraylist);
}

static void test_arraylist_insert(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->print_obj = print_num;

    TEST_ASSERT_TRUE(arraylist->empty(arraylist));
    TEST_ASSERT_FALSE(arraylist->full(arraylist));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(arraylist->empty(arraylist));
    }
    TEST_ASSERT_TRUE(arraylist->full(arraylist));

    arraylist_free(&arraylist);
}

static void test_arraylist_insert_negative(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->print_obj = print_num;

    TEST_ASSERT_TRUE(arraylist->empty(arraylist));
    TEST_ASSERT_FALSE(arraylist->full(arraylist));
    for(i = 0; i < len; i++)
    {
        ssize_t first_idx = -(ssize_t)arraylist->size(arraylist);

        TEST_ASSERT_TRUE(arraylist->insert(arraylist, first_idx, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(arraylist->empty(arraylist));
    }
    TEST_ASSERT_TRUE(arraylist->full(arraylist));

    arraylist_free(&arraylist);
}
    
static void test_arraylist_insert_invalid(void)
{
    int temp = 0;
    size_t len = 10;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->print_obj = print_num;

    TEST_ASSERT_FALSE(arraylist->insert(arraylist, len+1, &temp));
    TEST_ASSERT_FALSE(arraylist->insert(arraylist, 999, &temp));

    TEST_ASSERT_FALSE(arraylist->insert(arraylist, -len-1, &temp));
    TEST_ASSERT_FALSE(arraylist->insert(arraylist, -999, &temp));

    TEST_ASSERT_FALSE(arraylist->insert(arraylist, 0, NULL));

    TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &temp));
    arraylist_free(&arraylist);
}

static void test_arraylist_append(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    TEST_ASSERT_TRUE(arraylist->empty(arraylist));
    TEST_ASSERT_FALSE(arraylist->full(arraylist));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        size_t index = arraylist->size(arraylist) - 1;
        TEST_ASSERT_TRUE(arraylist->get(arraylist, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(arraylist->empty(arraylist));
    }
    TEST_ASSERT_TRUE(arraylist->full(arraylist));
    arraylist_free(&arraylist);
}

static void test_arraylist_append_invalid(void)
{
    int temp = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), 0);
    arraylist->compare = compare_num;

    TEST_ASSERT_FALSE(arraylist->append(arraylist, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_remove(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, len - 1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
    TEST_ASSERT_FALSE(arraylist->full(arraylist));

    for (i = 0; i < len - 2; i++)
    {
        TEST_ASSERT_TRUE(arraylist->remove(arraylist, 1, &temp));
        TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

        TEST_ASSERT_FALSE(arraylist->full(arraylist));
    }

    TEST_ASSERT_TRUE(arraylist->remove(arraylist, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_TRUE(arraylist->empty(arraylist));

    // ---------- no return ----------
    for(i = 0; i < 2; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, 2, NULL));
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, 1, NULL));
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, 0, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_remove_negative(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, -len, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);
    TEST_ASSERT_FALSE(arraylist->full(arraylist));

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(arraylist->remove(arraylist, -1, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1 - i], temp);
        TEST_ASSERT_FALSE(arraylist->full(arraylist));
    }
    TEST_ASSERT_TRUE(arraylist->empty(arraylist));

    // ---------- no return ----------
    for(i = 0; i < 2; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, -3, NULL));
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, -2, NULL));
    TEST_ASSERT_TRUE(arraylist->remove(arraylist, -1, NULL));

    arraylist_free(&arraylist);
}


static void test_arraylist_remove_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, -len-1, &temp));
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, -999, &temp));
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, len, &temp));
    TEST_ASSERT_FALSE(arraylist->remove(arraylist, 999, &temp));
    arraylist_free(&arraylist);
}

static void test_arraylist_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->pop(arraylist, &temp));
        TEST_ASSERT_EQUAL_INT(data[len -1 - i], temp);

        TEST_ASSERT_FALSE(arraylist->full(arraylist));
    }
    TEST_ASSERT_TRUE(arraylist->empty(arraylist));

    // ---------- no return ----------
    for(i = 0; i < 2; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->pop(arraylist, NULL));
    TEST_ASSERT_TRUE(arraylist->pop(arraylist, NULL));
    TEST_ASSERT_FALSE(arraylist->pop(arraylist, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_get(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);

    TEST_ASSERT_TRUE(arraylist->get(arraylist, len-1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len-1], temp);

    TEST_ASSERT_TRUE(arraylist->get(arraylist, -len, &temp));
    TEST_ASSERT_EQUAL_INT(data[0], temp);

    TEST_ASSERT_TRUE(arraylist->get(arraylist, -1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len-1], temp);

    arraylist_free(&arraylist);
}

static void test_arraylist_get_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(arraylist->get(arraylist, len, &temp));
    TEST_ASSERT_FALSE(arraylist->get(arraylist, 999, &temp));

    TEST_ASSERT_FALSE(arraylist->get(arraylist, -len-1, &temp));
    TEST_ASSERT_FALSE(arraylist->get(arraylist, -999, &temp));

    TEST_ASSERT_FALSE(arraylist->get(arraylist, 0, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_set(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));

        size_t index = arraylist->size(arraylist) - 1;
        TEST_ASSERT_TRUE(arraylist->get(arraylist, index, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, 0, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, 5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, 9, &temp));

    TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(arraylist->get(arraylist, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(arraylist->get(arraylist, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);

    arraylist_free(&arraylist);
}

static void test_arraylist_set_negative(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    temp = 0x11;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, -len, &temp));
    temp = 0x22;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, -5, &temp));
    temp = 0x33;
    TEST_ASSERT_TRUE(arraylist->set(arraylist, -1, &temp));

    TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
    TEST_ASSERT_EQUAL_INT(0x11, temp);
    TEST_ASSERT_TRUE(arraylist->get(arraylist, 5, &temp));
    TEST_ASSERT_EQUAL_INT(0x22, temp);
    TEST_ASSERT_TRUE(arraylist->get(arraylist, 9, &temp));
    TEST_ASSERT_EQUAL_INT(0x33, temp);
    
    arraylist_free(&arraylist);
}

static void test_arraylist_set_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    // ---------- invalid index ----------
    temp = 0x11;
    TEST_ASSERT_FALSE(arraylist->set(arraylist, len, &temp));
    TEST_ASSERT_FALSE(arraylist->set(arraylist, 999, &temp));

    TEST_ASSERT_FALSE(arraylist->set(arraylist, -len-1, &temp));
    TEST_ASSERT_FALSE(arraylist->set(arraylist, -999, &temp));

    TEST_ASSERT_FALSE(arraylist->set(arraylist, 0, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_at(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    const int *p_int = NULL;
    p_int = arraylist->at(arraylist, 0);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = arraylist->at(arraylist, 4);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = arraylist->at(arraylist, 9);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    arraylist_free(&arraylist);
}

static void test_arraylist_at_negative(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    const int *p_int = NULL;
    p_int = arraylist->at(arraylist, -len);
    TEST_ASSERT_EQUAL_INT(1, *p_int);

    p_int = arraylist->at(arraylist, -6);
    TEST_ASSERT_EQUAL_INT(5, *p_int);

    p_int = arraylist->at(arraylist, -1);
    TEST_ASSERT_EQUAL_INT(10, *p_int);

    arraylist_free(&arraylist);
}

static void test_arraylist_at_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    TEST_ASSERT_NULL(arraylist->at(arraylist, 10));

    //  warning: initialization discards 'const' qualifier from pointer target type
    // int *p_int_warring = arraylist->at(arraylist, 0);

    // !!! you should not do this.
    int *p_int_warring = (int *)arraylist->at(arraylist, 0);
    *p_int_warring = 100;

    arraylist->get(arraylist, 0, &temp);
    TEST_ASSERT_EQUAL_INT(100, temp);

    arraylist_free(&arraylist);
}


static void test_arraylist_resize(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), 1);
    arraylist->compare = compare_num;

    TEST_ASSERT_EQUAL_INT(1, arraylist->capacity(arraylist));
    arraylist->resize(arraylist, 16);
    TEST_ASSERT_EQUAL_INT(16, arraylist->capacity(arraylist));

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_EQUAL_INT(16, arraylist->capacity(arraylist));
    TEST_ASSERT_EQUAL_INT(10, arraylist->size(arraylist));

    TEST_ASSERT_TRUE(arraylist->resize(arraylist, 8));
    TEST_ASSERT_EQUAL_INT(8, arraylist->capacity(arraylist));
    for(i = 0; i < len; i++)
    {
        if(i < 8)
        {
            TEST_ASSERT_TRUE(arraylist->get(arraylist, i, &temp));
            TEST_ASSERT_EQUAL_INT(data[i], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(arraylist->get(arraylist, i, &temp));
        }
    }
    TEST_ASSERT_EQUAL_INT(8, arraylist->capacity(arraylist));
    TEST_ASSERT_EQUAL_INT(8, arraylist->size(arraylist));

    arraylist_free(&arraylist);
}

static void test_arraylist_resize_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    
    TEST_ASSERT_EQUAL_INT(len, arraylist->capacity(arraylist));
    TEST_ASSERT_FALSE(arraylist->resize(arraylist, 0));
    TEST_ASSERT_FALSE(arraylist->resize(arraylist, -1));

    arraylist_free(&arraylist);
}

static void test_arraylist_index(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    log_info("test_arraylist_index: append finished");
    
    temp = 1;
    TEST_ASSERT_EQUAL_INT(0, arraylist->index(arraylist, &temp));
    TEST_ASSERT_TRUE(arraylist->contains(arraylist, &temp));

    temp = 5;
    TEST_ASSERT_EQUAL_INT(4, arraylist->index(arraylist, &temp));
    TEST_ASSERT_TRUE(arraylist->contains(arraylist, &temp));

    temp = 10;
    TEST_ASSERT_EQUAL_INT(9, arraylist->index(arraylist, &temp));
    TEST_ASSERT_TRUE(arraylist->contains(arraylist, &temp));

    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, arraylist->index(arraylist, &temp));
    TEST_ASSERT_FALSE(arraylist->contains(arraylist, &temp));

    TEST_ASSERT_EQUAL_INT(-1, arraylist->index(arraylist, NULL));

    arraylist_free(&arraylist);
    log_info("test_arraylist_index: pass");
}

static void test_arraylist_index_invalid(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, arraylist->index(arraylist, &temp));
    TEST_ASSERT_FALSE(arraylist->contains(arraylist, &temp));

    TEST_ASSERT_EQUAL_INT(-1, arraylist->index(arraylist, NULL));
    TEST_ASSERT_FALSE(arraylist->contains(arraylist, NULL));

    arraylist_free(&arraylist);
}

static void test_arraylist_dynamic(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };

    size_t i = 0;
    size_t len = 2;
    arraylist_t arraylist = arraylist_new(sizeof(int), len);

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, arraylist->capacity(arraylist));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(arraylist->full(arraylist));
        }
        else
        {
            TEST_ASSERT_TRUE(arraylist->full(arraylist));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, arraylist->capacity(arraylist));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(arraylist->full(arraylist));
        }
        else
        {
            TEST_ASSERT_TRUE(arraylist->full(arraylist));
        }
    }

    len *= 2;
    for(; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->insert(arraylist, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
        
        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(len, arraylist->capacity(arraylist));
        if(i < len - 1)
        {
            TEST_ASSERT_FALSE(arraylist->full(arraylist));
        }
        else
        {
            TEST_ASSERT_TRUE(arraylist->full(arraylist));
        }
    }

    arraylist_free(&arraylist);
}

static void test_arraylist_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }

    iterator_t iter = arraylist->iter(arraylist, LINEAR_FORWARD);
    i = 0;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    iter = arraylist->iter(arraylist, LINEAR_REVERSE);
    i = len - 1;
    TEST_ASSERT_TRUE(iter->hasnext(iter));
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }
    TEST_ASSERT_EQUAL_INT(0, i);

    arraylist_free(&arraylist);
}

static void test_arraylist_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->full(arraylist));

    TEST_ASSERT_TRUE(arraylist->clear(arraylist));
    TEST_ASSERT_TRUE(arraylist->empty(arraylist));

    arraylist_free(&arraylist);
}

static void test_arraylist_sort(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;
    int unordered_data[] = { 1, 3, 4, 5, 2, 9, 8, 10, 7, 6};

    arraylist_t arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    arraylist->print_obj = print_num;

    for(i = 0; i < len; i++)
    {
        arraylist->append(arraylist, &unordered_data[i]);
    }
    TEST_ASSERT_TRUE(arraylist->sort(arraylist));
    
    iterator_t iter = arraylist->iter(arraylist, LINEAR_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len, i);

    temp = -55;
    TEST_ASSERT_TRUE(arraylist->append(arraylist, &temp));

    TEST_ASSERT_TRUE(arraylist->sort(arraylist));

    iter = arraylist->iter(arraylist, LINEAR_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        if(i == 0)
        {
            TEST_ASSERT_EQUAL_INT(-55, temp);
        }
        else
        {
            TEST_ASSERT_EQUAL_INT(data[i - 1], temp);
        }
        i++;
    }
    TEST_ASSERT_EQUAL_INT(len + 1, i);

    arraylist_free(&arraylist);
}

static void test_arraylist_slice_empty(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = NULL;
    arraylist_t list2 = NULL;

    // ------------------------------
    arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    arraylist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
    }

    // -------------------- NULL --------------------
    // python: arraylist[0:] -> []
    list2 = arraylist->slice(arraylist, 1, 5, 0); // if step == 0
    TEST_ASSERT_NULL(list2);
    // arraylist_free(&list2);

    // -------------------- empty --------------------
    list2 = arraylist->slice(arraylist, 0, 0, 1); // if start == end
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, len, SLICE_UNLIMITED, 1); // if start == end
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, 1, 5, -1); // if start < end && step < 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, 5, 1, 1); // if start > end && step > 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, -1, -5, 1); // if start < end && step < 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, -5, -1, -1); // if start > end && step > 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    // -------------------- empty --------------------
    list2 = arraylist->slice(arraylist, len, len + 1, 1); // if start > start_max
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, -len - 1, -len, 1); // if end < end_min
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    arraylist_free(&list2);

    arraylist_free(&arraylist);
}

static void test_arraylist_slice_positive(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = NULL;
    arraylist_t list2 = NULL;

    // ------------------------------
    arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    arraylist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
    }

    // -------------------- elements --------------------
    // python: arraylist[0:]
    list2 = arraylist->slice(arraylist, 0, len, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);

    // python: arraylist[0:11] if len(arraylist) == 10
    list2 = arraylist->slice(arraylist, 0, len + 1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);

    // python: arraylist[-6:8] or arraylist[-6:-2] or arraylist[4:8]
    list2 = arraylist->slice(arraylist, 4, 8, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 6 + i], temp);
    }
    arraylist_free(&list2);

    // python: arraylist[4:0:-1]
    list2 = arraylist->slice(arraylist, 4, 0, -1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - i], temp);
    }
    arraylist_free(&list2);

    // python: arraylist[::2]
    list2 = arraylist->slice(arraylist, 0, len, 2);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i * 2], temp);
    }
    arraylist_free(&list2);

    arraylist_free(&arraylist);
}

static void test_arraylist_slice_negative(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = NULL;
    arraylist_t list2 = NULL;

    // ------------------------------
    arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    arraylist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
    }

    // -------------------- elements --------------------
    // python: arraylist[:-1]
    list2 = arraylist->slice(arraylist, 0, -1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len - 1, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);

    // python: arraylist[:-1]
    list2 = arraylist->slice(arraylist, -1, len, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(1, list2->size(list2));
    TEST_ASSERT_TRUE(list2->get(list2, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
    arraylist_free(&list2);

    // python: arraylist[-6:8] or arraylist[-6:-2]
    // list2 = arraylist->slice(arraylist, -6, 8, 1);   // It can be executed, but it's not intuitive
    list2 = arraylist->slice(arraylist, -6, -2, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 6 + i], temp);
    }
    arraylist_free(&list2);

    // -------------------- step == 2 --------------------
    // python: arraylist[::-2]
    list2 = arraylist->slice(arraylist, len-1, 0, -2);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[9 - i * 2], temp);
    }
    arraylist_free(&list2);

    // -------------------- start_limit --------------------
    // arraylist[-len-1:-1]
    list2 = arraylist->slice(arraylist, -len-1, -1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len - 1, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);

    arraylist_free(&arraylist);
}


static void test_arraylist_slice_unlimited(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    arraylist_t arraylist = NULL;
    arraylist_t list2 = NULL;

    // ------------------------------
    arraylist = arraylist_new(sizeof(int), len);
    arraylist->compare = compare_num;
    arraylist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
    }

    // -------------------- umlimited --------------------
    // python: arraylist[0:]
    list2 = arraylist->slice(arraylist, 0, SLICE_UNLIMITED, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);
    
    // python: arraylist[4::-1]
    list2 = arraylist->slice(arraylist, 4, SLICE_UNLIMITED, -1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - 1 - i], temp);
    }
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, SLICE_UNLIMITED, SLICE_UNLIMITED, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, SLICE_UNLIMITED, SLICE_UNLIMITED, -1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - 1 - i], temp);
    }
    arraylist_free(&list2);

    // -------------------- step == 2 --------------------
    list2 = arraylist->slice(arraylist, SLICE_UNLIMITED, SLICE_UNLIMITED, 2);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i * 2], temp);
    }
    arraylist_free(&list2);

    list2 = arraylist->slice(arraylist, SLICE_UNLIMITED, SLICE_UNLIMITED, -2);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[9 - i*2], temp);
    }
    arraylist_free(&list2);

    arraylist_free(&arraylist);
}


static void test_arraylist_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    arraylist_t arraylist = arraylist_new(sizeof(struct _student), len);
    TEST_ASSERT_NOT_NULL(arraylist);
    arraylist->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));

        TEST_ASSERT_TRUE(arraylist->get(arraylist, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(arraylist->get(arraylist, arraylist->size(arraylist) - 1, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, arraylist->size(arraylist));
    }
    TEST_ASSERT_FALSE(arraylist->empty(arraylist));
    TEST_ASSERT_TRUE(arraylist->clear(arraylist));
    TEST_ASSERT_TRUE(arraylist->empty(arraylist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(arraylist->append(arraylist, &data[i]));
    }

    arraylist_free(&arraylist);
    TEST_ASSERT_NULL(arraylist);
}


void test_arraylist(void)
{
    UnitySetTestFile(__FILE__);

    // ---------- kernel ----------
    RUN_TEST(test_arraylist_new);
    RUN_TEST(test_arraylist_new_lazy);

    RUN_TEST(test_arraylist_insert);
    RUN_TEST(test_arraylist_insert_negative);
    RUN_TEST(test_arraylist_insert_invalid);

    RUN_TEST(test_arraylist_append);
    RUN_TEST(test_arraylist_append_invalid);

    RUN_TEST(test_arraylist_remove);
    RUN_TEST(test_arraylist_remove_negative);
    RUN_TEST(test_arraylist_remove_invalid);

    RUN_TEST(test_arraylist_pop);

    RUN_TEST(test_arraylist_get);
    RUN_TEST(test_arraylist_get_invalid);

    RUN_TEST(test_arraylist_set);
    RUN_TEST(test_arraylist_set_negative);
    RUN_TEST(test_arraylist_set_invalid);

    RUN_TEST(test_arraylist_at);
    RUN_TEST(test_arraylist_at_negative);
    RUN_TEST(test_arraylist_at_invalid);

    RUN_TEST(test_arraylist_resize);
    RUN_TEST(test_arraylist_resize_invalid);

    RUN_TEST(test_arraylist_index);    // index, search, contains
    RUN_TEST(test_arraylist_index_invalid);

    RUN_TEST(test_arraylist_dynamic);

    RUN_TEST(test_arraylist_iter);

    RUN_TEST(test_arraylist_sort);

    // RUN_TEST(test_arraylist_slice);
    RUN_TEST(test_arraylist_slice_empty);
    RUN_TEST(test_arraylist_slice_positive);
    RUN_TEST(test_arraylist_slice_negative);
    RUN_TEST(test_arraylist_slice_unlimited);

    // ---------- base ----------
    RUN_TEST(test_arraylist_clear);
    
    // ---------- ext ----------
    RUN_TEST(test_arraylist_struct);
}

#endif
