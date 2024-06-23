/**
 * @file unicstl.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _DEMO_H_
#define _DEMO_H_

#include "list.h"
#include "stack.h"
#include "queue.h"
#include "deque.h"
#include "tree.h"

#if RBTREE == 1
#include "rbtree.h"
    typedef prbtree_node_t stack_data_t;
    typedef prbtree_node_t queue_data_t;

    typedef int list_data_t;
#elif AVLTREE == 1
#include "tree.h"
    typedef ptree_node_t stack_data_t;
    typedef ptree_node_t queue_data_t;
#else
    typedef int stack_data_t;
    typedef int queue_data_t;
    typedef int list_data_t;
#endif

#endif // _DEMO_H_

