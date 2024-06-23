
#include "test.h"

static void test_queue_num(void)
{
    uint32_t i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    struct _queue queue;
    queue_init(&queue, sizeof(int));
    queue.print_obj = print_num;

    printf("\n\n----- test_queue_num -----\n");

    printf("----- after push-----\n");
    for (i = 0; i < len; i++)
    {
        queue.push(&queue, &data[i]);

        queue.front(&queue, &temp);
        printf("front = ");
        queue.print_obj(&temp);

        queue.back(&queue, &temp);
        printf("\tback = ");
        queue.print_obj(&temp);

        printf("\tsize = %2d\n", queue.size(&queue));
    }
    printf("----- print -----\n");
    queue.print(&queue);
    printf("\n");

    queue.clear(&queue);
    if (queue.empty(&queue))
    {
        printf("----- empty -----\n");
    }

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        queue.push(&queue, &data[i]);
    }

    printf("----- after pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        if (true == queue.pop(&queue, &temp))
        {
            printf("pop = ");
            queue.print_obj(&temp);

            if (true == queue.front(&queue, &temp))
            {
                printf("front = ");
                queue.print_obj(&temp);
            }

            if (queue.back(&queue, &temp))
            {
                printf("back = ");
                queue.print_obj(&temp);
            }

            printf("size = %2d\n", queue.size(&queue));
        }
        else
        {
            printf("pop failed! because it is empty\n");
        }

        if (queue.empty(&queue))
        {
            printf("----- empty -----\n");
        }
    }

    printf("----- print -----\n");
    queue.print(&queue);
    printf("\n");

    queue.destory(&queue);
}


static void test_queue_char(void)
{
    uint32_t i = 0;
    char data[] = "abcdefghijk";
    char temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    struct _queue queue;
    // queue_init2(&queue, sizeof(char), 64);
    queue_init2(&queue, sizeof(char), 10);
    queue.print_obj = print_char;

    printf("\n\n----- test_queue_char -----\n");

    printf("----- after push-----\n");
    for (i = 0; i < len; i++)
    {
        if(queue.push(&queue, &data[i]))
        {
            queue.front(&queue, &temp);
            printf("front = ");
            queue.print_obj(&temp);

            queue.back(&queue, &temp);
            printf("\tback = ");
            queue.print_obj(&temp);

            printf("\tsize = %2d\n", queue.size(&queue));
        }
        else
        {
            printf("push failed! because it is full\n");
        }

        if(queue.full(&queue))
        {
            printf("----- full -----\n");
        }
    }
    printf("----- print -----\n");
    queue.print(&queue);
    printf("\n");

    queue.clear(&queue);
    if (queue.empty(&queue))
    {
        printf("----- empty -----\n");
    }

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        queue.push(&queue, &data[i]);
    }

    printf("----- after pop -----\n");
    while(!queue.empty(&queue))
    {
        if (true == queue.pop(&queue, &temp))
        {
            printf("pop = ");
            queue.print_obj(&temp);

            if (true == queue.front(&queue, &temp))
            {
                printf("front = ");
                queue.print_obj(&temp);
            }

            if (queue.back(&queue, &temp))
            {
                printf("back = ");
                queue.print_obj(&temp);
            }

            printf("size = %2d\n", queue.size(&queue));
        }
    }

    if (true == queue.pop(&queue, &temp))
    {
        printf("pop = ");
        queue.print_obj(&temp);

        if (true == queue.front(&queue, &temp))
        {
            printf("front = ");
            queue.print_obj(&temp);
        }

        if (queue.back(&queue, &temp))
        {
            printf("back = ");
            queue.print_obj(&temp);
        }

        printf("size = %2d\n", queue.size(&queue));
    }

    if (queue.empty(&queue))
    {
        printf("----- empty -----\n");
    }

    printf("----- print -----\n");
    queue.print(&queue);
    printf("\n");

    queue.destory(&queue);
}

static void test_queue_struct(void)
{
    uint32_t i = 0;
    struct _student data[] = {
        {"zhao", 1001},{"qian", 1002}, {"sun", 1003}, {"li", 1004},
        "zhou", 1005, "wu", 1006, "zheng", 1007, "wang", 1008,
    };
    struct _student temp;
    uint32_t len = sizeof(data) / sizeof(data[0]) - 1;

    queue_t queue = queue_new();
    queue_init(queue, sizeof(struct _student));
    queue->print_obj = print_struct;

    printf("\n\n----- test_queue_struct -----\n");

    printf("----- after push-----\n");
    for (i = 0; i < len; i++)
    {
        if(queue->push(queue, &data[i]))
        {
            queue->front(queue, &temp);
            printf("front = ");
            queue->print_obj(&temp);

            queue->back(queue, &temp);
            printf("\tback = ");
            queue->print_obj(&temp);

            printf("\tsize = %2d\n", queue->size(queue));
        }
    }
    printf("----- print -----\n");
    queue->print(queue);
    printf("\n");

    queue->clear(queue);
    if (queue->empty(queue))
    {
        printf("----- empty -----\n");
    }

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        queue->push(queue, &data[i]);
    }

    printf("----- after pop -----\n");
    while(!queue->empty(queue))
    {
        if (true == queue->pop(queue, &temp))
        {
            printf("pop = ");
            queue->print_obj(&temp);

            if (true == queue->front(queue, &temp))
            {
                printf("front = ");
                queue->print_obj(&temp);
            }

            if (queue->back(queue, &temp))
            {
                printf("back = ");
                queue->print_obj(&temp);
            }

            printf("size = %2d\n", queue->size(queue));
        }
    }

    if (!queue->pop(queue, &temp))
    {
        printf("----- pop failed! -----\n");
    }

    if (queue->empty(queue))
    {
        printf("----- empty -----\n");
    }

    printf("----- print -----\n");
    queue->print(queue);
    printf("\n");

    queue_free(queue);
}


void test_queue(void)
{
    test_queue_num();
    test_queue_char();
    test_queue_struct();
}
