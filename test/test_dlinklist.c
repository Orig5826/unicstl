/**
 * @file test_dlinklist.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2024-09-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "test.h"

static void test_dlinklist_num(void)
{
    size_t i = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    dlinklist_t dlinklist = dlinklist_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(dlinklist);
    dlinklist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_back(dlinklist, &data[i]));

        TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, dlinklist->size(dlinklist));
    }

    TEST_ASSERT_FALSE(dlinklist->empty(dlinklist));
    TEST_ASSERT_TRUE(dlinklist->clear(dlinklist));
    TEST_ASSERT_TRUE(dlinklist->empty(dlinklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_back(dlinklist, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if (!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->pop_back(dlinklist, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->pop_back(dlinklist, &temp));
        }

        if (!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);

            TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[dlinklist->size(dlinklist) - 1], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_FALSE(dlinklist->back(dlinklist, &temp));
        }
    }
    TEST_ASSERT_TRUE(dlinklist->empty(dlinklist));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));

        TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[dlinklist->size(dlinklist) - 1], temp);

        TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, dlinklist->size(dlinklist));
    }
    TEST_ASSERT_TRUE(dlinklist->clear(dlinklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if (!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->pop_front(dlinklist, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->pop_front(dlinklist, &temp));
        }

        if (!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[dlinklist->size(dlinklist) - 1], temp);

            TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[0], temp);
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_FALSE(dlinklist->back(dlinklist, &temp));
        }
    }

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));
    }
    temp = 11;
    dlinklist->set(dlinklist, 0, &temp);

    temp = 22;
    dlinklist->set(dlinklist, len / 2, &temp);

    temp = 33;
    dlinklist->set(dlinklist, len - 1, &temp);

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->get(dlinklist, i, &temp));
    }
#endif

    dlinklist_free(&dlinklist);
    TEST_ASSERT_NULL(dlinklist);
}

static void test_dlinklist_struct(void)
{
    size_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    size_t len = sizeof(data) / sizeof(data[0]);

    dlinklist_t dlinklist = dlinklist_new(sizeof(struct _student));
    TEST_ASSERT_NOT_NULL(dlinklist);
    dlinklist->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_back(dlinklist, &data[i]));

        TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, dlinklist->size(dlinklist));
    }
    TEST_ASSERT_FALSE(dlinklist->empty(dlinklist));
    TEST_ASSERT_TRUE(dlinklist->clear(dlinklist));
    TEST_ASSERT_TRUE(dlinklist->empty(dlinklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_back(dlinklist, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->pop_back(dlinklist, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->pop_back(dlinklist, &temp));
        }
        
        if(!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

            TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[dlinklist->size(dlinklist) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[dlinklist->size(dlinklist) - 1].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_FALSE(dlinklist->back(dlinklist, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));

        TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[i].name, temp.name);

        TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
        TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);

        TEST_ASSERT_EQUAL_INT(i + 1, dlinklist->size(dlinklist));
    }
    TEST_ASSERT_TRUE(dlinklist->clear(dlinklist));
    TEST_ASSERT_TRUE(dlinklist->empty(dlinklist));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));
    }

    for (i = 0; i < len + 1; i++)
    {
        if(!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->pop_front(dlinklist, &temp));
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->pop_front(dlinklist, &temp));
        }
        
        if(!dlinklist->empty(dlinklist))
        {
            TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[dlinklist->size(dlinklist) - 1].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[dlinklist->size(dlinklist) - 1].name, temp.name);

            TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
            TEST_ASSERT_EQUAL_INT(data[0].id, temp.id);
            TEST_ASSERT_EQUAL_STRING(data[0].name, temp.name);
        }
        else
        {
            TEST_ASSERT_FALSE(dlinklist->front(dlinklist, &temp));
            TEST_ASSERT_FALSE(dlinklist->back(dlinklist, &temp));
        }
    }

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_front(dlinklist, &data[i]));
    }

#if 0
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->get(dlinklist, i, &temp));
    }
#endif

    dlinklist_free(&dlinklist);
    TEST_ASSERT_NULL(dlinklist);
}


static void test_dlinklist_iter(void)
{
    size_t i = 0;
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    dlinklist_t dlinklist = dlinklist_new(sizeof(int));
    TEST_ASSERT_NOT_NULL(dlinklist);
    dlinklist->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(dlinklist->push_back(dlinklist, &data[i]));

        TEST_ASSERT_TRUE(dlinklist->front(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[0], temp);

        TEST_ASSERT_TRUE(dlinklist->back(dlinklist, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_EQUAL_INT(i + 1, dlinklist->size(dlinklist));
    }

    iterator_t iter = dlinklist->iter(dlinklist, LINEAR_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    iter = dlinklist->iter(dlinklist, LINEAR_FORWARD);
    i = 0;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i++;
    }

    iter = dlinklist->iter(dlinklist, LINEAR_REVERSE);
    i = len - 1;
    while(iter->hasnext(iter))
    {
        temp = *(int *)iter->next(iter);
        TEST_ASSERT_EQUAL_INT(data[i], temp);
        i--;
    }

    dlinklist_free(&dlinklist);
    TEST_ASSERT_NULL(dlinklist);
}

void test_dlinklist(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_dlinklist_num);
    RUN_TEST(test_dlinklist_struct);

    RUN_TEST(test_dlinklist_iter);
}
