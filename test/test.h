
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
int compare_num(void *obj, void *obj2);

void print_char(void* obj);
void print_struct(void* obj);
void print_str(void* obj);


/**
 * @brief test function
 * 
 */
void test_list(void);
void test_stack(void);
void test_deque(void);
void test_queue(void);
void test_tree(void);

#endif // _TEST_H_

