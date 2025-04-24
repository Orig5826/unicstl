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

#endif // _COMMON_H_
