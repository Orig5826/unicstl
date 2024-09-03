/**
 * @file test.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test.h"

void print_num(void* obj)
{
    printf("(%2d ) ", *(int*)obj);
}

int compare_num(void *obj, void *obj2)
{
    int num1 = *(int*)obj;
    int num2 = *(int*)obj2;
    if(num1 == num2)
    {
        return 0;
    }
    return num1 > num2 ? 1 : -1;
}

void print_struct(void* obj)
{
    struct _student* student = (struct _student*)obj;
    printf("(%4d:%-8s) ", student->id, student->name);
}

int compare_struct(void *obj, void *obj2)
{
    struct _student num1 = *(struct _student*)obj;
    struct _student num2 = *(struct _student*)obj2;
    if(num1.id == num2.id)
    {
        return 0;
    }
    return num1.id > num2.id ? 1 : -1;
}

void print_char(void* obj)
{
    printf("(%2c ) ", *(char*)obj);
}

void print_str(void* obj)
{
    printf("(%s ) ", (char*)obj);
}



// --------------------------------------------------
//                     测试用例
// --------------------------------------------------
void setUp(void)
{
    // before each test
    static uint32_t item_cnt = 1;
    printf("# %d. ", item_cnt);
    item_cnt+=1;
}

void tearDown(void)
{
    // after each test
}

#define TEST_ADD(name)  printf("\n----- " #name " -----\n"); name();

int main(int argc, char const *argv[])
{
    printf("----- Unicstl Unit Test -----\n");
    UNITY_BEGIN();

    TEST_ADD(test_queue);
    TEST_ADD(test_stack);
    TEST_ADD(test_list);
    TEST_ADD(test_deque);
    TEST_ADD(test_heap);
    TEST_ADD(test_tree);
    TEST_ADD(test_graph);
    
    return UNITY_END();
}
