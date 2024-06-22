
#ifndef _TEST_H_
#define _TEST_H_

#define _CRT_SECURE_NO_WARNINGS 1		// for vs2022

#include "unicstl.h"

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
void test_stack(void);
void deque_test(void);

void queue_test(void);
void tree_test(void);
void rbtree_test(void);

#endif // _TEST_H_

