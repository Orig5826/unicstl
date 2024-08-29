/**
 * @file test.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "unicstl.h"
#include "unity.h"

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
void test_queue(void);
void test_stack(void);
void test_list(void);
void test_deque(void);
void test_tree(void);
void test_heap(void);

#endif // _TEST_H_
