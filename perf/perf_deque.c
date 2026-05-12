/**
 * @file perf_deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "perf.h"

#if 0
static void demo_deque_num(void)
{
    size_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    size_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int), len);
    deque->print_obj = print_num;

    printf("\n\n----- demo_deque_num -----\n");

    printf("----- after push_back -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);

        deque->front(deque, &temp);
        printf("front = ");
        deque->print_obj(&temp);

        deque->back(deque, &temp);
        printf("\tback = ");
        deque->print_obj(&temp);

        printf("\tsize = %2d\n", deque->size(deque));
    }
    printf("----- print -----\n");
    deque->print(deque);
    printf("\n");

    deque->clear(deque);
    if (deque->empty(deque))
    {
        printf("----- empty -----\n");
    }

    printf("----- push_back -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_back(deque, &data[i]);
    }

    printf("----- after pop_back -----\n");
    for (i = 0; i < len + 1; i++)
    {
        if (true == deque->pop_back(deque, &temp))
        {
            printf("pop = ");
            deque->print_obj(&temp);

            if (true == deque->front(deque, &temp))
            {
                printf("front = ");
                deque->print_obj(&temp);
            }

            if (deque->back(deque, &temp))
            {
                printf("back = ");
                deque->print_obj(&temp);
            }

            printf("size = %2d\n", deque->size(deque));
        }
        else
        {
            printf("pop failed! because it is empty\n");
        }

        if (deque->empty(deque))
        {
            printf("----- empty -----\n");
        }
    }

    printf("----- after push_front -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);

        deque->front(deque, &temp);
        printf("front = ");
        deque->print_obj(&temp);

        deque->back(deque, &temp);
        printf("\tback = ");
        deque->print_obj(&temp);

        printf("\tsize = %2d\n", deque->size(deque));
    }
    printf("----- print -----\n");
    deque->print(deque);
    printf("\n");

    deque->clear(deque);
    if (deque->empty(deque))
    {
        printf("----- empty -----\n");
    }

    printf("----- push_front -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);
    }

    for (i = 0; i < len + 1; i++)
    {
        if (true == deque->pop_front(deque, &temp))
        {
            printf("pop = ");
            deque->print_obj(&temp);

            if (true == deque->front(deque, &temp))
            {
                printf("front = ");
                deque->print_obj(&temp);
            }

            if (deque->back(deque, &temp))
            {
                printf("back = ");
                deque->print_obj(&temp);
            }

            printf("size = %2d\n", deque->size(deque));
        }
    }

#if 0
    printf("----- push_front -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);
    }
    printf("----- print -----\n");
    deque->print(deque);
    printf("\n");

    printf("----- set -----\n");
    temp = 11;
    deque->set(deque, 0, &temp);

    temp = 22;
    deque->set(deque, len/2, &temp);

    temp = 33;
    deque->set(deque, len - 1, &temp);

    printf("----- print -----\n");
    deque->print(deque);
    printf("\n");

    printf("----- get -----\n");
    for (i = 0; i < len; i++)
    {
        if (true == deque->get(deque, i, &temp))
        {
            printf("deque[%2d] = ", i);
            deque->print_obj(&temp);
            printf("\n");
        }
    }
#endif

    deque_free(&deque);
}
#endif

#define CAPACITY_T1 1024
#define OBJ_SIZE_T1 256

#define CAPACITY_T2 1024
#define OBJ_SIZE_T2 4096

#define CAPACITY_T3 8192
#define OBJ_SIZE_T3 4096

struct _test_obj
{
    void *obj;
    size_t obj_size;
    size_t capacity;
}test_obj;

static deque_t deque = NULL;

void perf_deque_new(void)
{
    deque = deque_new(test_obj.obj_size, test_obj.capacity);
}

void perf_deque_push_back(void)
{
    for (size_t i = 0; i < test_obj.capacity; i++)
    {
        deque->push_back(deque, &test_obj.obj);
    }
}

void perf_deque_pop_back(void)
{
    for (size_t i = 0; i < test_obj.capacity; i++)
    {
        deque->pop_back(deque, &test_obj.obj);
    }
}

void perf_deque_push_front(void)
{
    for (size_t i = 0; i < test_obj.capacity; i++)
    {
        deque->push_front(deque, &test_obj.obj);
    }
}

void perf_deque_pop_front(void)
{
    for (size_t i = 0; i < test_obj.capacity; i++)
    {
        deque->pop_front(deque, &test_obj.obj);
    }
}

void perf_deque_free(void)
{
    deque_free(&deque);
}


void perf_deque_t1(void)
{
    test_obj.capacity = CAPACITY_T1;
    test_obj.obj_size = OBJ_SIZE_T1;
    test_obj.obj = malloc(test_obj.capacity);
    if(test_obj.obj == NULL)
    {
        printf( __FUNCTION__, "malloc failed");
        return;
    }

    RUN_PERF_T1( perf_deque_new() );
    RUN_PERF_T1( perf_deque_push_back() );
    RUN_PERF_T1( perf_deque_pop_back() );
    RUN_PERF_T1( perf_deque_push_front() );
    RUN_PERF_T1( perf_deque_pop_front() );
    RUN_PERF_T1( perf_deque_free() );

    free(test_obj.obj);
}

void perf_deque_t2(void)
{
    test_obj.capacity = CAPACITY_T2;
    test_obj.obj_size = OBJ_SIZE_T2;
    test_obj.obj = malloc(test_obj.capacity);
    if(test_obj.obj == NULL)
    {
        printf( __FUNCTION__, "malloc failed");
        return;
    }

    RUN_PERF_T2( perf_deque_new() );
    RUN_PERF_T2( perf_deque_push_back() );
    RUN_PERF_T2( perf_deque_pop_back() );
    RUN_PERF_T2( perf_deque_push_front() );
    RUN_PERF_T2( perf_deque_pop_front() );
    RUN_PERF_T2( perf_deque_free() );

    free(test_obj.obj);
}

void perf_deque_t3(void)
{
    test_obj.capacity = CAPACITY_T3;
    test_obj.obj_size = OBJ_SIZE_T3;
    test_obj.obj = malloc(test_obj.capacity);
    if(test_obj.obj == NULL)
    {
        printf( __FUNCTION__, "malloc failed");
        return;
    }

    RUN_PERF_T3( perf_deque_new() );
    RUN_PERF_T3( perf_deque_push_back() );
    RUN_PERF_T3( perf_deque_pop_back() );
    RUN_PERF_T3( perf_deque_push_front() );
    RUN_PERF_T3( perf_deque_pop_front() );
    RUN_PERF_T3( perf_deque_free() );

    free(test_obj.obj);
}

void perf_deque(void)
{
    perf_deque_t1();
    perf_deque_t2();
    perf_deque_t3();
}
