
#include "test.h"

/**
 * @brief 
 * int data[] = { 5,2,3,1,7,8,6 };
 *           5
 *      |         |
 *      2         7
 *   |    |     |   |
 *   1    3     6   8
 */
void test_avltree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    tree_t tree = tree_new();
    tree_avl_init(tree, sizeof(int));
    tree->print_obj = print_num;
    tree->compare = compare_num;

    printf("\n\n----- test_avltree_num -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);

        printf("insert = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");
    }

    printf("----- max -----\n");
    tree->max(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- min -----\n");
    tree->min(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- tree -----\n");
    tree->clear(tree);
    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);
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

    printf("----- preorder(right) -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder(right) -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder(right) -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth(right) -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");


    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        // delete
        tree->delete(tree, &temp);

        printf("delete = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }

    tree_free(tree);
}



/**
 * @brief 
 */
void test_rbtree_num(void)
{
    uint32_t i = 0;
    // int data[] = { 2,1,3,4};
    // int data[] = { 1,2,3,4,5,6};
    // int data[] = { 5,2,3,1,7,8,6 };
    int data[] = { 5,2,3,1,7,8,6,4,9,10,12,11,15,14,13 };
    int temp = 0;
    uint32_t len = sizeof(data) / sizeof(data[0]);

    tree_t tree = tree_new();
    tree_rb_init(tree, sizeof(int));
    tree->print_obj = print_num;
    tree->compare = compare_num;

    printf("\n\n----- test_rbtree_num -----\n");

    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);

        printf("insert = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");
    }

    printf("----- max -----\n");
    tree->max(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- min -----\n");
    tree->min(tree, &temp);
    tree->print_obj(&temp);
    printf("\n");

    printf("----- tree -----\n");
    tree->clear(tree);
    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
    printf("----- insert -----\n");
    for (i = 0; i < len; i++)
    {
        temp = data[i];
        tree->insert(tree, &temp);
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

    printf("----- preorder(right) -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    printf("----- inorder(right) -----\n");
    tree->inorder(tree, tree->_root);
    printf("\n");

    printf("----- postorder(right) -----\n");
    tree->postorder(tree, tree->_root);
    printf("\n");

    printf("----- breadth(right) -----\n");
    tree->breadth(tree, tree->_root);
    printf("\n");

#if 1
    printf("----- left priority -----\n");
    tree->order(tree, false);
    printf("----- preorder -----\n");
    tree->preorder(tree, tree->_root);
    printf("\n");

    for (i = 0; i < len; i++)
    {
        temp = data[i];
        // delete
        tree->delete(tree, &temp);

        printf("delete = ");
        tree->print_obj(&temp);
        printf("size = %2d : ", tree->size(tree));
        tree->preorder(tree, tree->_root);
        printf("\n");
    }

    if(tree->empty(tree))
    {
        printf("----- empty -----\n");
    }
#endif
    tree_free(tree);
}

void test_tree(void)
{
    // test_avltree_num();
    test_rbtree_num();
}
