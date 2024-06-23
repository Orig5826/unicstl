
#include "test.h"

static void test_list_num(void)
{
    int i = 0;
    int data[] = { 1,2,3,4,5,6,7,8,9,10 };
    int temp = 0;
    int index = 0;
    int len = sizeof(data) / sizeof(data[0]);

    struct _list list;
    list_init2(&list, sizeof(int), 64);
    list.print_obj = print_num;

    printf("\n\n----- list_test_num -----\n");
    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        list.append(&list, &data[i]);
    }
    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- pop -----\n");
    list.pop(&list, 9, NULL);
    list.print(&list);
    printf("\n");

    list.pop(&list, 0, NULL);
    list.print(&list);
    printf("\n");

    list.pop(&list, 4, NULL);
    list.print(&list);
    printf("\n");

    printf("----- clear -----\n");
    list.clear(&list);
    list.print(&list);
    printf("\n");

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        list.append(&list, &data[i]);
    }
    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- get -----\n");
    index = 0;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = 4;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = 9;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);


    printf("----- set -----\n");
    index = 0;
    temp = 11;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = 4;
    temp = 22;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = 9;
    temp = 33;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    printf("----- print -----\n");
    list.print(&list);
    printf("\n");


    printf("----- at like python -----\n");
    index = -1;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = -6;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = -10;
    list.get(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    printf("----- set like python -----\n");
    index = -1;
    temp = 99;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = -6;
    temp = 98;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    index = -10;
    temp = 97;
    list.set(&list, index, &temp);
    printf("list[%4d] = %2d\n", index, temp);

    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        list.pop(&list, 0, &temp);

        if (list.empty(&list))
        {
            printf("----- empty -----\n");
            break;
        }
    }

    list.destory(&list);
}

static void test_list_struct(void)
{
    int i = 0;
    struct _student data[] = {
        "zhao", 1001, "qian", 1002, "sun",   1003, "li",   1004,
        "zhou", 1005, "wu",   1006, "zheng", 1007, "wang", 1008, 
        "feng", 1009, "cheng",1010, 
    };
    struct _student  temp = {0};
    int index = 0;
    int len = sizeof(data) / sizeof(data[0]);

    struct _list list;
    list_init2(&list, sizeof(struct _student), 64);
    list.print_obj = print_struct;

    printf("\n\n----- list_test_num -----\n");
    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        list.append(&list, &data[i]);
    }
    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- pop -----\n");
    list.pop(&list, 9, NULL);
    list.print(&list);
    printf("\n");

    list.pop(&list, 0, NULL);
    list.print(&list);
    printf("\n");

    list.pop(&list, 4, NULL);
    list.print(&list);
    printf("\n");

    printf("----- clear -----\n");
    list.clear(&list);
    list.print(&list);
    printf("\n");

    printf("----- push -----\n");
    for (i = 0; i < len; i++)
    {
        list.append(&list, &data[i]);
    }
    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- at -----\n");
    index = 0;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = 4;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = 9;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");


    printf("----- set -----\n");
    index = 0;
    temp.id = 11;
    sprintf(temp.name, "robot_%02d", temp.id);
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = 4;
    temp.id = 22;
    sprintf(temp.name, "robot_%02d", temp.id);
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = 9;
    temp.id = 33;
    sprintf(temp.name, "robot_%02d", temp.id);
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    printf("----- print -----\n");
    list.print(&list);
    printf("\n");


    printf("----- at like python -----\n");
    index = -1;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = -6;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = -10;
    list.get(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    printf("----- set like python -----\n");
    index = -1;
    temp.id = 99;
    sprintf(temp.name, "robot_%02d", temp.id);
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = -6;
    temp.id = 98;
    sprintf(temp.name, "robot_%02d", temp.id);
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    index = -10;
    //temp.id = 97;
    //sprintf(temp.name, "robot_%02d", temp.id);
    // temp = data[0];
    // struct _student robot = {"robot", 97};
    // temp = robot;
    temp = (struct _student){"robot", 97};
    list.set(&list, index, &temp);
    printf("list[%4d] = ", index);
    list.print_obj(&temp); printf("\n");

    printf("----- print -----\n");
    list.print(&list);
    printf("\n");

    printf("----- pop -----\n");
    for (i = 0; i < len + 1; i++)
    {
        list.pop(&list, 0, &temp);

        if (list.empty(&list))
        {
            printf("----- empty -----\n");
            break;
        }
    }

    list.destory(&list);
}

void list_test(void)
{
    test_list_num();
    test_list_struct();
}
