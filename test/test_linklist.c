/**
 * @file test_linklist.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "test.h"

static void test_linklist_new(void)
{
    // TEST_ASSERT_NULL(linklist_new(0));       // nomeaning

    linklist_t linklist = NULL;
    linklist = linklist_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(linklist);
    linklist_free(&linklist);

    // ------------------------------
    TEST_ASSERT_NULL(linklist);
    linklist_free(&linklist);
}

static void test_linklist_push(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    linklist_t linklist = NULL;

    // ------------------------------
    linklist = linklist_new(sizeof(int));

    TEST_ASSERT_TRUE(linklist->empty(linklist));
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push_back(linklist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, linklist->size(linklist));

        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(linklist->empty(linklist));
    }
    linklist_free(&linklist);
}

static void test_linklist_pop(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    linklist_t linklist = NULL;

    // ------------------------------
    linklist = linklist_new(sizeof(int));

    for(i = 0; i < len; i++)
    {
        linklist->push_back(linklist, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(linklist->pop_front(linklist, &temp));

        if (!linklist->empty(linklist))
        {
            TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(linklist->front(linklist, &temp));
            TEST_ASSERT_FALSE(linklist->back(linklist, &temp));
        }
    }
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    TEST_ASSERT_FALSE(linklist->pop_front(linklist, &temp));
    linklist_free(&linklist);
}

static void test_linklist_clear(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    linklist_t linklist = NULL;

    // ------------------------------
    linklist = linklist_new(sizeof(int));

    for(i = 0; i < len; i++)
    {
        linklist->push_back(linklist, &data[i]);
    }
    TEST_ASSERT_TRUE(linklist->clear(linklist));
    for(i = 0; i < len; i++)
    {
        linklist->push_back(linklist, &data[i]);
    }
    TEST_ASSERT_FALSE(linklist->empty(linklist));
    TEST_ASSERT_TRUE(linklist->clear(linklist));
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    TEST_ASSERT_TRUE(linklist->clear(linklist));
    linklist_free(&linklist);
}


static void test_linklist_num(void)
{
    size_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    linklist_t linklist = NULL;
    linklist = linklist_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(linklist);

    linklist->print_obj = print_num;

    TEST_ASSERT_TRUE(linklist->clear(linklist));

    TEST_ASSERT_FALSE(linklist->front(linklist, &temp));
    TEST_ASSERT_FALSE(linklist->back(linklist, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push_back(linklist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, linklist->size(linklist));

        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    TEST_ASSERT_FALSE(linklist->empty(linklist));
    TEST_ASSERT_TRUE(linklist->clear(linklist));
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push_back(linklist, &data[i]));
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

        TEST_ASSERT_TRUE(linklist->pop_front(linklist, &temp));

        if (!linklist->empty(linklist))
        {
            TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1], temp);

            TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
        }
    }
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    TEST_ASSERT_FALSE(linklist->pop_front(linklist, &temp));

    linklist_free(&linklist);
    TEST_ASSERT_NULL(linklist);
}

static void test_linklist_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        {"zhao", 1001}, {"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    size_t len = sizeof(data) / sizeof(data[0]) - 1;

    linklist_t linklist = linklist_new(sizeof(struct _student));
    TEST_ASSERT_NOT_NULL(linklist);

    linklist->print_obj = print_struct;

    TEST_ASSERT_TRUE(linklist->clear(linklist));

    TEST_ASSERT_FALSE(linklist->front(linklist, &temp));
    TEST_ASSERT_FALSE(linklist->back(linklist, &temp));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push_back(linklist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, linklist->size(linklist));

        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);
    }

    TEST_ASSERT_FALSE(linklist->empty(linklist));
    TEST_ASSERT_TRUE(linklist->clear(linklist));
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push_back(linklist, &data[i]));
    }

    // while (!linklist->empty(linklist))
    for(i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 1].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[len - 1].name, temp.name);

        TEST_ASSERT_TRUE(linklist->pop_front(linklist, &temp));

        if (!linklist->empty(linklist))
        {
            TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[i + 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[i + 1].name, temp.name);

            TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[len - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[len - 1].name, temp.name);
        }
    }
    TEST_ASSERT_TRUE(linklist->empty(linklist));
    TEST_ASSERT_FALSE(linklist->pop_front(linklist, &temp));
    linklist_free(&linklist);
    TEST_ASSERT_NULL(linklist);
}

#if 0
static void test_linklist_iter(void)
{
    size_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    linklist_t linklist = NULL;
    linklist = linklist_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(linklist);
    linklist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(linklist->push(linklist, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, linklist->size(linklist));

        TEST_ASSERT_TRUE(linklist->front(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(linklist->back(linklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }

    iterator_t iter = linklist->iter(linklist);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        // printf("%d ", temp);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    linklist_free(&linklist);
    TEST_ASSERT_NULL(linklist);
}
#endif

void test_linklist(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_linklist_new);
    RUN_TEST(test_linklist_push);
    RUN_TEST(test_linklist_pop);
    RUN_TEST(test_linklist_clear);

    RUN_TEST(test_linklist_num);
    RUN_TEST(test_linklist_struct);

    // RUN_TEST(test_linklist_iter);
}
