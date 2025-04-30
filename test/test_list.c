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

static void test_list_new(void)
{
    list_t list = NULL;
    list = list_new2(sizeof(int), 1);
    TEST_ASSERT_NOT_NULL(list);
    list_free(&list);
    TEST_ASSERT_NULL(list);

    list_free(&list); // list_free(NULL);
    TEST_ASSERT_NULL(list);

    // 
    TEST_ASSERT_NULL(list_new2(0, 1));
    TEST_ASSERT_NULL(list_new2(sizeof(int), 0));
}

static void test_list_append(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
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
    list = list_new2(sizeof(int), len - 2);
    for (i = 0; i < len; i++)
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
    list = list_new2(sizeof(int), len);
    for (i = 0; i < len; i++)
    {
        list->append(list, &data[i]);
    }
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->pop(list, &temp));
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));
    list_free(&list);
}

static void test_list_insert(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->print_obj = print_num;

    TEST_ASSERT_TRUE(list->empty(list));
    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->insert(list, i, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->get(list, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        // list->print(list);
        // printf("\n");
    }
    list->clear(list);
    TEST_ASSERT_TRUE(list->empty(list));

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->insert(list, 0, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->get(list, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        // list->print(list);
        // printf("\n");
    }

    TEST_ASSERT_FALSE(list->empty(list));
    list_free(&list);
}

static void test_list_delete(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    for (i = 0; i < len; i++)
    {
        list->append(list, &data[i]);
    }

    TEST_ASSERT_TRUE(list->delete(list, len - 1, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);

    for (i = 0; i < len - 1; i++)
    {
        TEST_ASSERT_TRUE(list->delete(list, 0, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    TEST_ASSERT_TRUE(list->empty(list));
    TEST_ASSERT_FALSE(list->pop(list, &temp));
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
    list = list_new2(sizeof(int), len);
    TEST_ASSERT_TRUE(list->clear(list));
    for (i = 0; i < len; i++)
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
    list = list_new2(sizeof(int), 64);
    TEST_ASSERT_TRUE(list != NULL);

    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }
    TEST_ASSERT_TRUE(list->delete(list, 9, NULL));
    TEST_ASSERT_TRUE(list->delete(list, 0, NULL));
    TEST_ASSERT_TRUE(list->delete(list, 4, NULL));
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
        TEST_ASSERT_TRUE(list->pop(list, &temp));

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
    struct _student  temp = { 0 };
    int index = 0;
    int len = sizeof(data) / sizeof(data[0]);

    list_t list = list_new2(sizeof(struct _student), 64);
    list->print_obj = print_struct;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }
    TEST_ASSERT_TRUE(list->delete(list, 9, NULL));
    TEST_ASSERT_TRUE(list->delete(list, 0, NULL));
    TEST_ASSERT_TRUE(list->delete(list, 4, NULL));

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
    temp = (struct _student){ "robot", 97 };
    TEST_ASSERT_TRUE(list->set(list, index, &temp));

    for (i = 0; i < len + 1; i++)
    {
        TEST_ASSERT_TRUE(list->pop(list, &temp));

        if (list->empty(list))
        {
            break;
        }
    }

    list_free(&list);
    TEST_ASSERT_NULL(list);
}

void test_list_iter(void)
{
    int temp = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    TEST_ASSERT_TRUE(list->empty(list));
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, list->size(list));

        TEST_ASSERT_TRUE(list->get(list, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);

        TEST_ASSERT_FALSE(list->empty(list));
    }

    iterator_t iter = list->iter(list);
    int iter_data = 0;
    int idx = 0;
    while (iter->hasnext(iter))
    {
        iter_data = *(int*)iter->next(iter);
        // printf("%d ", iter_data);
        TEST_ASSERT_EQUAL_INT(data[idx], iter_data);
        idx++;
    }
    list_free(&list);
}

static void test_list_index(void)
{
    int temp = 0;
    int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->compare = compare_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    TEST_ASSERT_EQUAL_INT(0, list->index(list, &data[0]));
    TEST_ASSERT_EQUAL_INT(5, list->index(list, &data[5]));
    TEST_ASSERT_EQUAL_INT(9, list->index(list, &data[9]));
    temp = 11;
    TEST_ASSERT_EQUAL_INT(-1, list->index(list, &temp));

    list_free(&list);
}

static void test_list_slice_empty(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;
    list_t list2 = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->compare = compare_num;
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    // -------------------- NULL --------------------
    // python: list[0:] -> []
    list2 = list->slice(list, 1, 5, 0); // if step == 0
    TEST_ASSERT_NULL(list2);
    // list_free(&list2);

    // -------------------- empty --------------------
    list2 = list->slice(list, 0, 0, 1); // if start == end
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list2 = list->slice(list, 1, 5, -1); // if start < end && step < 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list2 = list->slice(list, 5, 1, 1); // if start > end && step > 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list2 = list->slice(list, -1, -5, 1); // if start < end && step < 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list2 = list->slice(list, -5, -1, -1); // if start > end && step > 0
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    // -------------------- empty --------------------
    list2 = list->slice(list, len, len + 1, 1); // if start > start_max
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list2 = list->slice(list, -len - 1, -len, 1); // if end < end_min
    TEST_ASSERT_NOT_NULL(list2);
    TEST_ASSERT_TRUE(list2->empty(list2));
    list_free(&list2);

    list_free(&list);
}

static void test_list_slice_positive(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;
    list_t list2 = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->compare = compare_num;
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    // -------------------- elements --------------------
    // python: list[0:]
    list2 = list->slice(list, 0, len, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);

    // python: list[0:11] if len(list) == 10
    list2 = list->slice(list, 0, len + 1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);

    // python: list[-6:8] or list[-6:-2] or list[4:8]
    list2 = list->slice(list, 4, 8, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 6 + i], temp);
    }
    list_free(&list2);

    // python: list[4:0:-1]
    list2 = list->slice(list, 4, 0, -1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - i], temp);
    }
    list_free(&list2);

    // python: list[::2]
    list2 = list->slice(list, 0, len, 2);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i * 2], temp);
    }
    list_free(&list2);

    list_free(&list);
}

static void test_list_slice_negative(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;
    list_t list2 = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->compare = compare_num;
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    // -------------------- elements --------------------
    // python: list[:-1]
    list2 = list->slice(list, 0, -1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len - 1, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);

    // python: list[:-1]
    list2 = list->slice(list, -1, len, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(1, list2->size(list2));
    TEST_ASSERT_TRUE(list2->get(list2, 0, &temp));
    TEST_ASSERT_EQUAL_INT(data[len - 1], temp);
    list_free(&list2);

    // python: list[-6:8] or list[-6:-2]
    // list2 = list->slice(list, -6, 8, 1);   // It can be executed, but it's not intuitive
    list2 = list->slice(list, -6, -2, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(4, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[len - 6 + i], temp);
    }
    list_free(&list2);

    // -------------------- step == 2 --------------------
    // python: list[::-2]
    list2 = list->slice(list, len-1, 0, -2);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[9 - i * 2], temp);
    }
    list_free(&list2);

    // -------------------- start_limit --------------------
    // list[-len-1:-1]
    list2 = list->slice(list, -len-1, -1, 1);
    TEST_ASSERT_NOT_NULL(list2);
    // list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len - 1, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);

    list_free(&list);
}


static void test_list_slice_unlimited(void)
{
    int temp = 0;
    int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint32_t len = sizeof(data) / sizeof(data[0]);
    uint32_t i = 0;

    list_t list = NULL;
    list_t list2 = NULL;

    // ------------------------------
    list = list_new2(sizeof(int), len);
    list->compare = compare_num;
    list->print_obj = print_num;

    for (i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list->append(list, &data[i]));
    }

    // -------------------- umlimited --------------------
    // python: list[0:]
    list2 = list->slice(list, 0, LIST_UNLIMITED, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);
    
    // python: list[4::-1]
    list2 = list->slice(list, 4, LIST_UNLIMITED, -1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - 1 - i], temp);
    }
    list_free(&list2);

    list2 = list->slice(list, LIST_UNLIMITED, LIST_UNLIMITED, 1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i], temp);
    }
    list_free(&list2);

    list2 = list->slice(list, LIST_UNLIMITED, LIST_UNLIMITED, -1);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(len, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[list2->size(list2) - 1 - i], temp);
    }
    list_free(&list2);

    // -------------------- step == 2 --------------------
    list2 = list->slice(list, LIST_UNLIMITED, LIST_UNLIMITED, 2);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[i * 2], temp);
    }
    list_free(&list2);

    list2 = list->slice(list, LIST_UNLIMITED, LIST_UNLIMITED, -2);
    TEST_ASSERT_NOT_NULL(list2);
    //list2->print(list2); printf("\n");
    TEST_ASSERT_EQUAL_INT(5, list2->size(list2));
    for(i = 0; i < list2->size(list2); i++)
    {
        TEST_ASSERT_TRUE(list2->get(list2, i, &temp));
        TEST_ASSERT_EQUAL_INT(data[9 - i*2], temp);
    }
    list_free(&list2);

    list_free(&list);
}

void test_list(void)
{
    UnitySetTestFile(__FILE__);

    RUN_TEST(test_list_new);

    RUN_TEST(test_list_append);
    RUN_TEST(test_list_pop);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_delete);

    RUN_TEST(test_list_clear);

    RUN_TEST(test_list_num);
    RUN_TEST(test_list_struct);

    RUN_TEST(test_list_iter);

    RUN_TEST(test_list_index);

    RUN_TEST(test_list_slice_empty);
    RUN_TEST(test_list_slice_positive);
    RUN_TEST(test_list_slice_negative);
    RUN_TEST(test_list_slice_unlimited);
}
