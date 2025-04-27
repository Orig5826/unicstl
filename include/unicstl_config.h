/**
 * @file unicstl_config.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _UNICSTL_CONFIG_H_

/**
 * @brief unicstl contains which module
 * 
 */
#define UNICSTL_LIST
#define UNICSTL_STACK
#define UNICSTL_QUEUE
#define UNICSTL_DEQUE
#define UNICSTL_TREE
#define UNICSTL_HEAP
#define UNICSTL_GRAPH
#define UNICSTL_ITERATOR

/**
 * @brief debug 
 * 
 */
// #define NDEBUG       // assert disable

#define UNICSTL_DEBUG

#ifdef UNICSTL_DEBUG
    #define UNICSTL_DEBUG_STACK
    #define UNICSTL_DEBUG_QUEUE
    #define UNICSTL_DEBUG_DEQUE
    #define UNICSTL_DEBUG_TREE
    #define UNICSTL_DEBUG_HEAP
    #define UNICSTL_DEBUG_GRAPH
#endif

#endif