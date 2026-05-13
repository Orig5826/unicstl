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

// #define NDEBUG      // release

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
 * @brief unicstl use which function
 * 
 */
#define UNICSTL_MALLOC

/**
 * @brief 
 * 
 */
#ifndef NDEBUG
#define UNICSTL_DEBUG
#endif

#ifdef UNICSTL_DEBUG

#define UNICSTL_DEBUG_STACK
#define UNICSTL_DEBUG_QUEUE
#define UNICSTL_DEBUG_DEQUE
#define UNICSTL_DEBUG_TREE
#define UNICSTL_DEBUG_HEAP
#define UNICSTL_DEBUG_GRAPH


#define UNICSTL_ASSERT      // assert
#define LOGGER_ON           // logger on

/**
 * @brief debug level
 *      0. DEBUG  
 *      1. INFO  
 *      2. WARN  
 *      3. ERROR  
 */
#define LOG_LEVEL                    0

/**
 * @brief 
 *      0. simple
 *      1. detail
 */
#define LOG_DEBUG_DETAIL             1
#endif  // UNICSTL_DEBUG

#endif
