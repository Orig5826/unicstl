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
    return compare_int(obj, obj2);
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

    log_init();
    mempool_init();
    

    TEST_ADD(test_unicstl);

#if UNITTEST_LINKLIST
    TEST_ADD(test_linklist);
#endif
#if UNITTEST_DLINKLIST
    TEST_ADD(test_dlinklist);
#endif
#if UNITTEST_DARRAY
    TEST_ADD(test_darray);
#endif
#if UNITTEST_RINGBUF || UNITTEST_RAWBUF
    TEST_ADD(test_ringbuf);
#endif 
#if UNITTEST_RAWBUF
    TEST_ADD(test_rawbuf);
#endif  
#if UNITTEST_ARRAYLIST
    TEST_ADD(test_arraylist);
#endif
#if UNITTEST_DEQUE
    TEST_ADD(test_deque);
#endif
#if UNITTEST_QUEUE
    TEST_ADD(test_queue);
#endif
#if UNITTEST_STACK
    TEST_ADD(test_stack);
#endif
#if UNITTEST_HEAP
    TEST_ADD(test_heap);
#endif
#if UNITTEST_TREE
    TEST_ADD(test_tree);
#endif
#if UNITTEST_GRAPH
    TEST_ADD(test_graph);
#endif
#if UNITTEST_SEGARRAY
    TEST_ADD(test_segarray);
#endif
#if  UNITTEST_USTRING
    TEST_ADD(test_ustring);
#endif
#if UNITTEST_RBTREE
    TEST_ADD(test_rbtree);
#endif

    mempool_deinit();
    log_deinit();
    return UNITY_END();
}
