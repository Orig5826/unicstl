/**
 * @file demo.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _DEMO_H_
#define _DEMO_H_

#define _CRT_SECURE_NO_WARNINGS         1   // for vs2022

#include "unicstl.h"

/**
 * @brief demo objects
 * 
 */
struct _student
{
    char name[16];
    int id;
};

void print_num(void* obj);
int compare_num(void *obj, void *obj2);

void print_struct(void* obj);
int compare_struct(void *obj, void *obj2);

void print_char(void* obj);
void print_str(void* obj);


/**
 * @brief test function
 * 
 */
void demo_list(void);
void demo_stack(void);
void demo_deque(void);
void demo_queue(void);
void demo_tree(void);
void demo_heap(void);
void demo_graph(void);

#endif // _DEMO_H_

