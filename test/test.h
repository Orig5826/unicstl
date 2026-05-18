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

#define UNITY_INCLUDE_CONFIG_H
#include "unicstl.h"
#include "unity.h"


#define UNITTEST_ALL        0

#define UNITTEST_LINKLIST   (UNITTEST_ALL || 0)
#define UNITTEST_DLINKLIST  (UNITTEST_ALL || 0)
#define UNITTEST_DARRAY     (UNITTEST_ALL || 1)
#define UNITTEST_RINGBUF    (UNITTEST_ALL || 0)
#define UNITTEST_RAWBUF     (UNITTEST_ALL || 0)

#define UNITTEST_ARRAYLIST  (UNITTEST_ALL || 1)
#define UNITTEST_DEQUE      (UNITTEST_ALL || 0)

#define UNITTEST_QUEUE      (UNITTEST_ALL || 0)
#define UNITTEST_STACK      (UNITTEST_ALL || 0)

#define UNITTEST_HEAP       (UNITTEST_ALL || 0)
// #define UNITTEST_TREE       (UNITTEST_ALL || 0)
// #define UNITTEST_GRAPH      (UNITTEST_ALL || 0)

#define UNITTEST_SEGARRAY   (UNITTEST_ALL || 0)
#define UNITTEST_USTRING    (UNITTEST_ALL || 1)


/**
 * @brief demo objects
 * 
 */
struct _student
{
    char name[16];
    int id;
};

void print_num(const void* obj);
int compare_num(const void *obj, const void *obj2);

void print_struct(const void* obj);
int compare_struct(const void *obj, const void *obj2);

void print_char(const void* obj);
void print_str(const void* obj);

/**
 * @brief test function
 * 
 */
void test_unicstl(void);

void test_darray(void);
void test_linklist(void);
void test_dlinklist(void);
void test_ringbuf(void);
void test_rawbuf(void);
void test_segarray(void);

void test_deque(void);
void test_arraylist(void);

void test_queue(void);
void test_stack(void);
void test_list(void);
void test_tree(void);
void test_heap(void);
void test_graph(void);

void test_ustring(void);

#endif // _TEST_H_
