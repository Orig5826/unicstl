/**
 * @file demo_deque.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "demo.h"

static void demo_deque_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(int));
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

static void demo_deque_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008,
        "feng", 1009, "cheng",1010,
    };
    struct _student temp = {0};
    uint32_t len = sizeof(data) / sizeof(data[0]);

    deque_t deque = deque_new(sizeof(struct _student));
    deque->print_obj = print_struct;

    printf("\n\n----- demo_deque_struct -----\n");

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

    printf("----- push_front -----\n");
    for (i = 0; i < len; i++)
    {
        deque->push_front(deque, &data[i]);
    }
    printf("----- print -----\n");
    deque->print(deque);
    printf("\n");

#if 0
    printf("----- set -----\n");
    temp = 11;
    deque->set(deque, 0, &temp);

    temp = 22;
    deque->set(deque, len / 2, &temp);

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

void demo_deque(void)
{
    demo_deque_num();
    demo_deque_struct();
}
