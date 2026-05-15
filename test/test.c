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

void print_num(const void* obj)
{
    printf("(%2d ) ", *(int*)obj);
}

int compare_num(const void *obj, const void *obj2)
{
    int num1 = *(int*)obj;
    int num2 = *(int*)obj2;
    if(num1 == num2)
    {
        return 0;
    }
    return num1 > num2 ? 1 : -1;
}

void print_struct(const void* obj)
{
    struct _student* student = (struct _student*)obj;
    printf("(%4d:%-8s) ", student->id, student->name);
}

int compare_struct(const void *obj, const void *obj2)
{
    struct _student num1 = *(struct _student*)obj;
    struct _student num2 = *(struct _student*)obj2;
    if(num1.id == num2.id)
    {
        return 0;
    }
    return num1.id > num2.id ? 1 : -1;
}

void print_char(const void* obj)
{
    printf("(%2c ) ", *(char*)obj);
}

void print_str(const void* obj)
{
    printf("(%s ) ", (char*)obj);
}



// --------------------------------------------------
//                     测试用例
// --------------------------------------------------
void setUp(void)
{
    // before each test
    static size_t item_cnt = 1;
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

    TEST_ADD(test_unicstl);

    TEST_ADD(test_darray);
    TEST_ADD(test_linklist);
    TEST_ADD(test_dlinklist);
    
    TEST_ADD(test_ringbuf);
    
    TEST_ADD(test_deque);

    TEST_ADD(test_queue);
    TEST_ADD(test_stack);
    TEST_ADD(test_list);
    TEST_ADD(test_heap);
    TEST_ADD(test_tree);
    TEST_ADD(test_graph);

    TEST_ADD(test_rawbuf);
    TEST_ADD(test_segarray);
    
    return UNITY_END();
}
