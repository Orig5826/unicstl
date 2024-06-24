
#include "test.h"

#ifdef TREE_TEST

static void tree_data_display(tree_data_t data)
{
    printf("%d ", data);
}

#ifdef TREE_RECURSION

#define TREE_DISP_DEPTH_PRE(tree)	{tree_traversal_depth_preorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_DEPTH_IN(tree)	{tree_traversal_depth_inorder(tree,tree_data_display);printf("\n");}

// tree display
#define TREE_DISP(tree)		TREE_DISP_DEPTH_IN(tree)

void tree_test(void)
{
    int32_t i = 0;
    // tree_data_t dat[10] = {5,0,2,4,3,1,8,7,9,6};		// debug data
    tree_data_t dat[10] = { 0,1,2,3,4,5,6,7,8,9 };		// test data1
    // tree_data_t dat[10] = { 3,1,2,5,4,8,6,7,9,0 };	// test data2
    tree_data_t tmp;
    ptree_node_t tree = NULL;

    tree_init(&tree);

    for (i = 0; i < 10; i++)
    {
        tree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);

    tree_get_min(tree, &tmp);
    if (tmp == 0)
    {
        printf("success -> tree_get_min is %d\n", tmp);
    }
    else
    {
        printf("failure -> tree_get_min is %d ?\n", tmp);
    }

    tree_get_max(tree, &tmp);
    if (tmp == 9)
    {
        printf("success -> tree_get_max is %d\n", tmp);
    }
    else
    {
        printf("failure -> tree_get_max is %d ?\n", tmp);
    }

    // delete the root
    tree_delete(tree, 5);
    printf("del %d: ", 5);
    TREE_DISP(tree);

    // delete the leaf
    tree_delete(tree, 3);
    printf("del %d: ", 3);
    TREE_DISP(tree);

    // delete the node which has two nodes
    tree_delete(tree, 8);
    printf("del %d: ", 8);
    TREE_DISP(tree);

    tree_clear(tree);
    printf("success -> tree_clear success!\n");
    if (tree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    if (!tree_delete(tree, 8))
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
        tree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);

    for (i = 0; i < 10; i++)
    {
        if (tree_delete(tree, i))
        {
            printf("del %d: ", i);
            TREE_DISP(tree);
        }
    }

    if (tree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    tree_destroy(&tree);
    if (!tree_insert(tree, dat[0]))
    {
        printf("success -> after tree destroyed, tree_insert failureed!\n");
    }

    if (!tree_get_min(tree, &tmp))
    {
        printf("success -> after tree destroyed, tree_get_min failured!\n");
    }

    if (!tree_get_max(tree, &tmp))
    {
        printf("success -> after tree destroyed, tree_get_max failured!\n");
    }

    printf("----------------------------------------\n");
}


#else

#define TREE_DISP_DEPTH_PRE(tree)	{tree_traversal_depth_preorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_DEPTH_IN(tree)	{tree_traversal_depth_inorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_DEPTH_POST(tree)	{tree_traversal_depth_postorder(tree,tree_data_display);printf("\n");}
#define TREE_DISP_BREADTH(tree)		{tree_traversal_breadth(tree,tree_data_display);printf("\n");}

// tree display
#define TREE_DISP(tree)		TREE_DISP_DEPTH_IN(tree)

void tree_test(void)
{
    int32_t i = 0;
    // tree_data_t dat[10] = {5,0,2,4,3,1,8,7,9,6};		// debug data
    tree_data_t dat[10] = {0,1,2,3,4,5,6,7,8,9};		// test data1
    // tree_data_t dat[10] = { 3,1,2,5,4,8,6,7,9,0 };	// test data2
    tree_data_t tmp;
    ptree_t tree = NULL;

    tree_init(&tree);

    for (i = 0; i < 10; i++)
    {
        tree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);

    tree_get_min(tree, &tmp);
    if(tmp == 0)
    {
        printf("success -> tree_get_min is %d\n",tmp);
    }
    else
    {
        printf("failure -> tree_get_min is %d ?\n", tmp);
    }

    tree_get_max(tree, &tmp);
    if (tmp == 9)
    {
        printf("success -> tree_get_max is %d\n", tmp);
    }
    else
    {
        printf("failure -> tree_get_max is %d ?\n", tmp);
    }

    // delete the root
    tree_delete(tree, 5);
    printf("del %d: ", 5);
    TREE_DISP(tree);

    // delete the leaf
    tree_delete(tree, 3);
    printf("del %d: ", 3);
    TREE_DISP(tree);

    // delete the node which has two nodes
    tree_delete(tree, 8);
    printf("del %d: ", 8);
    TREE_DISP(tree);
    
    tree_clear(tree);
    printf("success -> tree_clear success!\n");
    if (tree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    if (!tree_delete(tree, 8))
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
        tree_insert(tree, dat[i]);
    }
    printf("tree : ");
    TREE_DISP(tree);
    
    for (i = 0; i < 10; i++)
    {
        if (tree_delete(tree, i))
        {
            printf("del %d: ", i);
            TREE_DISP(tree);
        }
    }

    if (tree_empty(tree))
    {
        printf("success -> the tree is empty\n");
    }
    else
    {
        printf("failure -> the tree is not empty\n");
    }

    tree_destroy(&tree);
    if (!tree_insert(tree, dat[0]))
    {
        printf("success -> after tree destroyed, tree_insert failureed!\n");
    }

    if(!tree_get_min(tree,&tmp))
    {
        printf("success -> after tree destroyed, tree_get_min failured!\n");
    }

    if(!tree_get_max(tree,&tmp))
    {
        printf("success -> after tree destroyed, tree_get_max failured!\n");
    }

    printf("----------------------------------------\n");
}
#endif
#endif

/**
 * @brief 
 * int data[] = { 5,2,3,1,7,8,6 };
 *           5
 *      |         |
 *      2         7
 *   |    |     |   |
 *   1    3     6   8
 */
void test_tree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    int data[] = { 5,2,3,1,7,8,6 };
    // int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    tree_t tree = tree_new();
    tree_avl_init(tree, sizeof(int));
    tree->print_obj = print_num;
    tree->compare = compare_num;

    printf("\n\n----- test_queue_num -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        tree->insert(tree, &data[i]);
    }
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

    printf("----- right priority -----\n");
    tree->order(tree, true);

    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");



    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- breadth -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->delete(tree, &temp);

        printf("delete = ");
        tree->print_obj(&temp);

        printf("size = %2d\n", tree->size(tree));

        printf("----- breadth -----\n");
        tree->breadth(tree, tree->_root);
        printf("----- inorder -----\n");
        tree->inorder(tree, tree->_root);
        printf("\n");
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }

    tree_free(tree);
}

void test_tree(void)
{
    test_tree_num();
}
