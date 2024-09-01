/**
 * @file test_list->c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

static void test_list_init2(void)
{
    struct _list list;
    // ------------------------------
#ifdef NDEBUG
    TEST_ASSERT_FALSE(list_init2(NULL, sizeof(int), 1));
    TEST_ASSERT_FALSE(list_init2(list, 0, 1));
    TEST_ASSERT_FALSE(list_init2(list, sizeof(int), 0));
#endif
    TEST_ASSERT_TRUE(list_init2(&list, sizeof(int), 1));
    list.destory(&list);
}

static void test_list_new(void)
{
    list_t list = NULL;
    list = list_new();
    list_free(&list);

    // ------------------------------
    list = list_new();
    TEST_ASSERT_NOT_NULL(list);

#ifdef NDEBUG
    TEST_ASSERT_FALSE(list_init2(NULL, sizeof(int), 1));
    TEST_ASSERT_FALSE(list_init2(list, 0, 1));
    TEST_ASSERT_FALSE(list_init2(list, sizeof(int), 0));
#endif
    TEST_ASSERT_TRUE(list_init2(list, sizeof(int), 1));
    list_free(&list);

    TEST_ASSERT_NULL(list);
    list_free(&list); // list_free(NULL);
}


static void test_list_append(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    TEST_ASSERT_TRUE(list->empty(list));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->get(list, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(list->empty(list));
    }
    list_free(&list);

    // ------------------------------
    // if capacity is less than data len
    list = list_new();
    list_init2(list, sizeof(int), len - 2);
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));
    }
    list_free(&list);
}


static void test_list_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    for(i = 0; i < len; i++)
    {
        list->append(list, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->pop(list, 0, &temp));
    }
    TEST_ASSERT_TRUE(list->empty(list));
    // TEST_ASSERT_FALSE(list->pop(list, 1, &temp));
    list_free(&list);
}


static void test_list_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    TEST_ASSERT_TRUE(list->clear(list));
    for(i = 0; i < len; i++)
    {
        list->append(list, &data[i]);
    }
    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    list_free(&list);
}

static void test_list_num(void)
{
    int i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    int index = 0;
    int len = sizeof(data) / sizeof(data[0]);

    list_t list = NULL;
    list = list_new();
    TEST_ASSERT_TRUE(list != NULL);

    list_init2(list, sizeof(int), 64);
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }
    TEST_ASSERT_TRUE(list->pop(list, 9, NULL));
    TEST_ASSERT_TRUE(list->pop(list, 0, NULL));
    TEST_ASSERT_TRUE(list->pop(list, 4, NULL));
    TEST_ASSERT_TRUE(list->clear(list));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }
    index = 0;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 4;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 9;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 0;
    temp = 11;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = 4;
    temp = 22;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = 9;
    temp = 33;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -1;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -6;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -10;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -1;
    temp = 99;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -6;
    temp = 98;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -10;
    temp = 97;
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    for (i = 0; i < len + 1; i++)
    {
        TEST_ASSERT_TRUE(list->pop(list, 0, &temp));

        if (list->empty(list))
        {
            break;
        }
    }

    list_free(&list);
    TEST_ASSERT_NULL(list);
}

static void test_list_struct(void)
{
    int i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008, 
        "feng", 1009, "cheng",1010, 
    };
    struct _student  temp = {0};
    int index = 0;
    int len = sizeof(data) / sizeof(data[0]);

    list_t list = list_new();
    list_init2(list, sizeof(struct _student), 64);
    list->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }
    TEST_ASSERT_TRUE(list->pop(list, 9, NULL));
    TEST_ASSERT_TRUE(list->pop(list, 0, NULL));
    TEST_ASSERT_TRUE(list->pop(list, 4, NULL));

    TEST_ASSERT_TRUE(list->clear(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    index = 0;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 4;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 9;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = 0;
    temp.id = 11;
    sprintf(temp.name, "robot_%02d", temp.id);
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = 4;
    temp.id = 22;
    sprintf(temp.name, "robot_%02d", temp.id);
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = 9;
    temp.id = 33;
    sprintf(temp.name, "robot_%02d", temp.id);
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -1;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -6;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -10;
    TEST_ASSERT_TRUE(list->get(list, index, &temp));

    index = -1;
    temp.id = 99;
    sprintf(temp.name, "robot_%02d", temp.id);
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -6;
    temp.id = 98;
    sprintf(temp.name, "robot_%02d", temp.id);
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    index = -10;
    temp = (struct _student){"robot", 97};
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    for (i = 0; i < len + 1; i++)
    {
        TEST_ASSERT_TRUE(list->pop(list, 0, &temp));

        if (list->empty(list))
        {
            break;
        }
    }

    list_free(&list);
    TEST_ASSERT_NULL(list);
}

static void test_list_iter(void)
{
    int temp = 0;
    int data[32] = { 1,2,3,4,5,6,7,8,9,10 };
    // uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t len = 10;
    uint32_t i = 0;
    int buff[32];
    int count = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    TEST_ASSERT_TRUE(list->clear(list));
    for(i = 0; i < len; i++)
    {
        list->append(list, &data[i]);
    }

    int * iter = NULL;
    
    iter = list->begin(list);
    for(count = 0, i = 0; i < len + 12; i++)
    {
        if(i < len)
        {
            TEST_ASSERT_EQUAL_INT(data[i % len], *iter);
        }
        iter = list->next(list);
    }
    for(count=0, iter = list->begin(list); iter != list->end(list); iter = list->next(list))
    {
        buff[count++] = *iter;
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(data, buff, count);

    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    list_free(&list);
}

void test_list(void)
{
    RUN_TEST(test_list_init2);
    RUN_TEST(test_list_new);
    RUN_TEST(test_list_append);
    RUN_TEST(test_list_pop);
    RUN_TEST(test_list_clear);

    RUN_TEST(test_list_num);
    RUN_TEST(test_list_struct);

    RUN_TEST(test_list_iter);
}
