/**
 * @file test_list.c
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
    TEST_ASSERT_FALSE(list_init2(&list, 0, 1));
    TEST_ASSERT_FALSE(list_init2(&list, sizeof(int), 0));
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

#if 0

static void test_list_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int));
    TEST_ASSERT_TRUE(list->empty(list));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(list->empty(list));
    }
    list_free(&list);

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    TEST_ASSERT_TRUE(list->empty(list));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
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
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
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
    list_init2(list, sizeof(int));
    for(i = 0; i < len; i++)
    {
        list->push(list, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);

        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(list->peek(list, &temp));
        }
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));
    list_free(&list);

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    for(i = 0; i < len; i++)
    {
        list->push(list, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);

        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(list->peek(list, &temp));
        }
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));
    list_free(&list);

    // ------------------------------
    // if capacity is less than data len
    list = list_new();
    list_init2(list, sizeof(int), len - 2);
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));
    }
    uint32_t capacity = list->capacity(list);
    for (i = 0; i < len; i++)
    {
        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->pop(list, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(list->pop(list, &temp));
        }

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(list->pop(list, &temp));
            TEST_ASSERT_FALSE(list->peek(list, &temp));
        }
    }
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
    list_init2(list, sizeof(int));
    for(i = 0; i < len; i++)
    {
        list->push(list, &data[i]);
    }
    TEST_ASSERT_TRUE(list->clear(list));
    for(i = 0; i < len; i++)
    {
        list->push(list, &data[i]);
    }
    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    list_free(&list);

    // ------------------------------
    list = list_new();
    list_init2(list, sizeof(int), len);
    TEST_ASSERT_TRUE(list->clear(list));
    for(i = 0; i < len; i++)
    {
        list->push(list, &data[i]);
    }
    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    list_free(&list);
}

static void test_list_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    list_t list = NULL;
    list = list_new();
    TEST_ASSERT_NOT_NULL(list);

    TEST_ASSERT_TRUE(list_init2(list, sizeof(int)));
    list->print_obj = print_num;

    TEST_ASSERT_FALSE(list->peek(list, &temp));
    TEST_ASSERT_TRUE(list->clear(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);

        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));

    list_free(&list);
    TEST_ASSERT_NULL(list);
}

static void test_list_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    list_t list = list_new();
    TEST_ASSERT_NOT_NULL(list);

    list_init2(list, sizeof(struct _student));
    list->print_obj = print_struct;

    TEST_ASSERT_FALSE(list->peek(list, &temp));
    TEST_ASSERT_TRUE(list->clear(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);
    }

    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
    }

    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[list->size(list) - 1].name, temp.name);

        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[list->size(list) - 1].name, temp.name);
        }
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));
    list_free(&list);
    TEST_ASSERT_NULL(list);
}


static void test_list2_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t capacity = len;

    list_t list = NULL;
    list = list_new();
    TEST_ASSERT_NOT_NULL(list);
    
    TEST_ASSERT_TRUE(list_init2(list, sizeof(int), capacity));
    list->print_obj = print_num;

    TEST_ASSERT_FALSE(list->peek(list, &temp));
    TEST_ASSERT_TRUE(list->clear(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);

        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));

    list_free(&list);
    TEST_ASSERT_NULL(list);    
}

static void test_list2_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;
    uint32_t capacity = len - 2;

    list_t list = NULL;
    list = list_new();
    TEST_ASSERT_NOT_NULL(list);

    TEST_ASSERT_TRUE(list_init2(list, sizeof(struct _student), capacity));
    list->print_obj = print_struct;

    TEST_ASSERT_FALSE(list->peek(list, &temp));
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->peek(list, &temp));
        TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[list->size(list) - 1].name, temp.name);
    }

    TEST_ASSERT_FALSE(list->empty(list));
    TEST_ASSERT_TRUE(list->clear(list));
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->push(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));
    }

    for(i = 0; i < len; i++)
    {
        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->pop(list, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(list->pop(list, &temp));
        }

        if (!list->empty(list))
        {
            TEST_ASSERT_TRUE(list->peek(list, &temp));
            TEST_ASSERT_EQUAL_INT(data[list->size(list) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[list->size(list) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(list->peek(list, &temp));
        }
    }
    list_free(&list);
    TEST_ASSERT_NULL(list);
}

#endif

void test_list(void)
{
    RUN_TEST(test_list_init2);
    RUN_TEST(test_list_new);
    // RUN_TEST(test_list_push);
    // RUN_TEST(test_list_pop);
    // RUN_TEST(test_list_clear);

    // RUN_TEST(test_list_num);
    // RUN_TEST(test_list_struct);

    // RUN_TEST(test_list2_num);
    // RUN_TEST(test_list2_struct);
}
