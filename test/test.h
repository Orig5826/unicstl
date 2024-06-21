
#ifndef _TEST_H_
#define _TEST_H_

#include "common.h"

// It is recommended to keep one at the same time
#define RBTREE_TEST		0
#define AVLTREE_TEST	0
#define RAVLTRE_TEST	0
#define STACK_TEST		0
#define QUEUE_TEST		0
#define LIST_TEST		0


#if AVLTREE == 1 || RAVLTREE == 1 || RBTREE == 1
	#if QUEUE_TEST == 1 || STACK_TEST == 1
	#error "When use the tree, you can't use the base data type of stack or queue! "
	#endif
#endif


/**
 * @brief test objects
 * 
 */
struct _student
{
	char name[16];
	int id;
};

void print_num(void* obj);
void print_char(void* obj);
void print_struct(void* obj);
void print_str(void* obj);


/**
 * @brief test function
 * 
 */
void list_test(void);
void stack_test(void);
void deque_test(void);

void queue_test(void);
void tree_test(void);
void rbtree_test(void);

#endif // _TEST_H_

