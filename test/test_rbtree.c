
#include "test.h"

#if RBTREE_TEST == 1

#define TREE_DISP_DEPTH_PRE(tree)	{rbtree_traversal_depth_preorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_DEPTH_IN(tree)	{rbtree_traversal_depth_inorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_DEPTH_POST(tree)	{rbtree_traversal_depth_postorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_BREADTH(tree)		{rbtree_traversal_breadth(tree,tree_data_display);printf("\n");}

// tree display
#define TREE_DISP(tree)		TREE_DISP_DEPTH_IN(tree)

static void tree_data_display(rbtree_data_t data)
{
    printf("%4d ", data);
}

void rbtree_base(void)
{
    int32_t i = 0;
    rbtree_data_t dat[10] = { 5,0,2,4,3,1,8,7,9,6 };		// debug data
    rbtree_data_t tmp;
    prbtree_t tree = NULL;

    rbtree_init(&tree);

    for (i = 0; i < 10; i++)
    {
        rbtree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);

    rbtree_get_min(tree, &tmp);
    if (tmp == 0)
    {
        printf("success -> tree_get_min is %d\n", tmp);
    }
    else
    {
        printf("failure -> tree_get_min is %d ?\n", tmp);
    }

    rbtree_get_max(tree, &tmp);
    if (tmp == 9)
    {
        printf("success -> tree_get_max is %d\n", tmp);
    }
    else
    {
        printf("failure -> tree_get_max is %d ?\n", tmp);
    }

    // delete the leaf
    rbtree_delete(tree, 6);
    printf("del %d: ", 6);
    TREE_DISP(tree);

    // delete the node which one child
    rbtree_delete(tree, 0);
    printf("del %d: ", 0);
    TREE_DISP(tree);

    // delete the node which has two nodes
    rbtree_delete(tree, 2);
    printf("del %d: ", 2);
    TREE_DISP(tree);

    // delete the root
    rbtree_delete(tree, 4);
    printf("del %d: ", 4);
    TREE_DISP(tree);

    rbtree_clear(tree);
    printf("success -> tree_clear success!\n");
    if (rbtree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    if (!rbtree_delete(tree, 8))
    {
        printf("success -> tree is empty, so delete failureed!\n");
    }
    else
    {
        printf("failure -> tree is empty, but delete succeed!\n");
    }


    // ------------------------------------
    // insert again
    for (i = 0; i < 10; i++)
    {
        rbtree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);

    for (i = 0; i < 10; i++)
    {
        if (rbtree_delete(tree, i))
        {
            printf("del %d: ", i);
            TREE_DISP(tree);
        }
    }

    if (rbtree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    rbtree_destroy(&tree);
    if (!rbtree_insert(tree, dat[0]))
    {
        printf("success -> after tree destroyed, tree_insert failureed!\n");
    }

    if (!rbtree_get_min(tree, &tmp))
    {
        printf("success -> after tree destroyed, tree_get_min failured!\n");
    }

    if (!rbtree_get_max(tree, &tmp))
    {
        printf("success -> after tree destroyed, tree_get_max failured!\n");
    }

    printf("----------------------------------------\n");
}

void rbtree_random_insert_test(void)
{
#define INSERT_NUM_MAX		128
    uint32_t i = 0;
    const uint32_t len = INSERT_NUM_MAX;
    rbtree_data_t dat[INSERT_NUM_MAX];
    rbtree_data_t dd[] = { 5,0,2,4,3,1,8,7,9,6 };

    prbtree_t tree = NULL;
    rbtree_init(&tree);

    printf("orig_data:\n");
    srand((uint32_t)time(0));
    for (i = 0; i < len; i++)
    {
        dat[i] = rand() % len;
        // dat[i] = dd[i];
        printf("%d,", dat[i]);
    }
    printf("\n----------------------------------------\n");

    for (i = 0; i < len; i++)
    {
        // printf("insert %-04d\n", dat[i]);
        rbtree_insert(tree, dat[i]);
        // TREE_DISP(tree);

        if (true != rbtree_check(tree))
        {
            printf("failure -> insert\n");
            SYSTEM_PAUSE();
        }
    }

    TREE_DISP_DEPTH_PRE(tree);
    TREE_DISP_DEPTH_IN(tree);
    TREE_DISP_DEPTH_POST(tree);
    TREE_DISP_BREADTH(tree);

    rbtree_destroy(&tree);
}


void rbtree_random_delete_test(void)
{
#define MAX_NUMBER		128
    uint32_t i = 0;
    const uint32_t len = MAX_NUMBER;
    rbtree_data_t dat[MAX_NUMBER];
    rbtree_data_t dd[] = { 22,12,5,2,0,21,5,22,30,11,6,18,22,5,7,17,13,13,24,13,14,1,20,12,22,24,19,14,17,13,24 };

    prbtree_t tree = NULL;
    rbtree_init(&tree);
    static uint8_t srand_flag = 0;

    if (srand_flag == 0)
    {
        srand((uint32_t)time(0));
        srand_flag = 1;
    }
    printf("orig_data:\n");
    for (i = 0; i < len; i++)
    {
        dat[i] = rand() % len;
        // dat[i] = dd[i];
        printf("%d,", dat[i]);
    }
    printf("\n----------------------------------------\n");

    for (i = 0; i < len; i++)
    {
        rbtree_insert(tree, dat[i]);

        if (true != rbtree_check(tree))
        {
            printf("failure -> insert\n");
            SYSTEM_PAUSE();
        }
    }
    // TREE_DISP(tree);
    printf("----------------------------------------\n");

    for (i = 0; i < len; i++)
    {
        // printf("delete %-04d\n", dat[i]);
        rbtree_delete(tree, dat[i]);
        // TREE_DISP(tree);
        if (true != rbtree_check(tree))
        {
            printf("failure -> delete\n");
            SYSTEM_PAUSE();
        }
    }
    printf("----------------------------------------\n");

    if (rbtree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }

    rbtree_destroy(&tree);
}


void rbtree_test(void)
{
    // rbtree_base();
    // rbtree_random_insert_test();
    rbtree_random_delete_test();
}

#endif

