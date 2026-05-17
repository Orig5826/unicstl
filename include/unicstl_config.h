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
#define _UNICSTL_CONFIG_H_
// clang-format off

// #define NDEBUG          // release mode if define
#ifndef NDEBUG
#define UNICSTL_DEBUG
#endif

/**
 * @brief unicstl contains which module
 * 
 */
#define UNICSTL_ARRAYLIST

#define UNICSTL_LIST
#define UNICSTL_STACK
#define UNICSTL_QUEUE
#define UNICSTL_DEQUE
#define UNICSTL_TREE
#define UNICSTL_HEAP
#define UNICSTL_GRAPH
#define UNICSTL_ITERATOR

/**
 * @brief malloc config
 * 
 */
#define UNICSTL_MALLOC_ENABLE           // malloc enable
#define UNICSTL_MALLOC_CUSTOM        // malloc custom support


/**
 * @brief 
 * 
 */
#ifdef UNICSTL_DEBUG

/**
 * @brief assert config
 * 
 */
#define UNICSTL_ASSERT_ENABLE              // assert enable
// #define ASSERT_CUSTOM                   // assert custom support

/**
 * @brief logger config
 * 
 */
#define LOGGER_ENABLE                       // logger enable

/**
 * @brief debug level
 *   LOG_DEBUG
 *   LOG_INFO
 *   LOG_WARN
 *   LOG_ERROR
 *   LOG_NONE
 */
#define LOG_LEVEL                       LOG_DEBUG

/**
 * @brief 
 *      LOG_DETAIL_DISABLE
 *      LOG_DETAIL_ENABLE
 */
#define LOG_DEBUG_DETAIL                LOG_DETAIL_ENABLE

#define LOG_FILE_ENABLE

// #define UNICSTL_DEBUG_STACK
// #define UNICSTL_DEBUG_QUEUE
// #define UNICSTL_DEBUG_DEQUE
// #define UNICSTL_DEBUG_TREE
// #define UNICSTL_DEBUG_HEAP
// #define UNICSTL_DEBUG_GRAPH

#endif  // UNICSTL_DEBUG

// clang-format on
#endif // _UNICSTL_CONFIG_H_
