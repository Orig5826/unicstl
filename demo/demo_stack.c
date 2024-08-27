/**
 * @file demo_stack.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "demo.h"

static void demo_stack_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    struct _stack s;
    stack_init(&s, sizeof(int));
    s.print_obj = print_num;

    printf("\n\n----- demo_stack_num -----\n");
    // get top if stack is empty
    s.peek(&s, &temp);

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        s.push(&s, &data[i]);

        s.peek(&s, &temp);

        printf("top = ");
        s.print_obj(&temp);

        printf("size = %2d\n", s.size(&s));
    }
    printf("----- print -----\n");
    s.print(&s);
    printf("\n");

    printf("----- pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        if (true == s.pop(&s, &temp))
        {
            printf("pop = ");
            s.print_obj(&temp);

            if (s.peek(&s, &temp))
            {
                printf("top = ");
                s.print_obj(&temp);
            }

            printf("size = %2d\n", s.size(&s));
        }
        else
        {
            printf("pop failed! because it is empty\n");
        }

        if (s.empty(&s))
        {
            printf("----- empty -----\n");
        }
    }

    s.destory(&s);
}

static void demo_stack_char(void)
{
    uint32_t i = 0;
    char data[] = "abcdefghijk";
    char temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    struct _stack s;
    stack_init2(&s, sizeof(char), 64);
    s.print_obj = print_char;

    printf("\n\n----- demo_stack_char -----\n");
    // get top if stack is empty
    s.peek(&s, &temp);

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        s.push(&s, &data[i]);

        s.peek(&s, &temp);
        printf("top = ");
        s.print_obj(&temp);

        printf("size = %2d\n", s.size(&s));
    }
    printf("----- print -----\n");
    s.print(&s);
    printf("\n");

    printf("----- pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        if (true == s.pop(&s, &temp))
        {
            printf("pop = ");
            s.print_obj(&temp);

            if (s.peek(&s, &temp))
            {
                printf("top = ");
                s.print_obj(&temp);
            }

            printf("size = %2d\n", s.size(&s));
        }
        else
        {
            printf("pop failed! because it is empty\n");
        }

        if (s.empty(&s))
        {
            printf("----- empty -----\n");
        }
    }

    s.destory(&s);
}

static void demo_stack_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp = { 0 };
    uint32_t len = sizeof(data) / sizeof(data[0]);

    stack_t stack;
    stack = stack_new();
    stack_init(stack, sizeof(struct _student));
    stack->print_obj = print_struct;

    printf("\n\n----- demo_stack_struct -----\n");
    // get top if stack is empty
    stack->peek(stack, &temp);

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);

        stack->peek(stack, &temp);
        printf("top = ");
        stack->print_obj(&temp);

        printf("size = %2d\n", stack->size(stack));
    }
    printf("----- print -----\n");
    stack->print(stack);
    printf("\n");

    printf("----- clear -----\n");
    stack->clear(stack);
    printf("----- print -----\n");
    stack->print(stack);
    printf("\n");

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        stack->push(stack, &data[i]);
    }

    printf("----- pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        if (true == stack->pop(stack, &temp))
        {
            printf("pop = ");
            stack->print_obj(&temp);

            if (stack->peek(stack, &temp))
            {
                printf("top = ");
                stack->print_obj(&temp);
            }

            printf("size = %2d\n", stack->size(stack));
        }
        else
        {
            printf("pop failed! because it is empty\n");
        }

        if (stack->empty(stack))
        {
            printf("----- empty -----\n");
        }
    }

    stack->destory(stack);
    stack_free(stack);
}

void demo_stack(void)
{
    demo_stack_num();
    demo_stack_char();
    demo_stack_struct();
}
