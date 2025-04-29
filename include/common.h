/**
 * @file common.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#define UNICSTL_CONFIG

#ifdef UNICSTL_CONFIG
#include "unicstl_config.h"
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#ifdef UNICSTL_ITERATOR
#include "iterator.h"
#endif

/**
 * @brief obj compare with obj2
 *
 * @return
 *      obj < obj2 return -1
 *      obj == obj2 return 0
 *      obj > obj2 return 1
 */
typedef int (*compare_fun_t)(void* obj, void* obj2);


// default function
int default_compare(void* obj1, void* obj2);
void default_print_obj(void* obj);

#endif // _COMMON_H_
