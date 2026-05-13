/**
 * @file logger.h
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-03-31
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "unicstl_config.h"

// -------------------- DEBUG CONFIG --------------------
#ifdef LOGGER_ON

#ifndef LOG_LEVEL
#define LOG_LEVEL               LOG_NONE
#endif

#ifndef LOG_DEBUG_DETAIL
#define LOG_DEBUG_DETAIL         0
#endif

// -------------------- LOG OUTPUT --------------------
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO  = 1,
    LOG_WARN  = 2,
    LOG_ERROR = 3,
}loglevel_t;

#if LOG_DEBUG_DETAIL == 1
#define LOG_PRINT(level, fmt, ...) do {\
    if ((int)level >= (int)LOG_LEVEL) {\
        printf("[%s] %s:%d %s()", #level, __FILE__, __LINE__, __func__); \
        printf("\n" fmt "\n", ##__VA_ARGS__);\
    }\
} while (0)
#else
#define LOG_PRINT(level, fmt, ...) do {\
    if (level >= (int)LOG_LEVEL) {\
        printf(fmt "\n", ##__VA_ARGS__);\
    }\
} while (0)
#endif

#define LOG_DEBUG(fmt, ...) LOG_PRINT(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG_PRINT(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG_PRINT(LOG_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_PRINT(LOG_ERROR, fmt, ##__VA_ARGS__)



#define LOG_HEX(level, data, len) do {\
    if (level >= LOG_LEVEL) {\
        for(uint32_t i_temp = 0; i_temp < len; i_temp++) { \
            if(i_temp != 0 && (i_temp % 4 == 0)){ printf(" ");}\
            if(i_temp != 0 && (i_temp % 64 == 0)){ printf("\n");}\
            printf("%x", ((uint8_t*)(data))[i_temp]);\
        }\
        printf("\n");\
    }\
} while (0)

#define LOG_HEX_DEBUG(data, len) LOG_HEX(LOG_DEBUG, data, len)
#define LOG_HEX_INFO(data, len)  LOG_HEX(LOG_INFO, data, len)
#define LOG_HEX_WARN(data, len)  LOG_HEX(LOG_WARN, data, len)
#define LOG_HEX_ERROR(data, len) LOG_HEX(LOG_ERROR, data, len)


#else

#define LOG_DEBUG(fmt, ...) do {} while (0)
#define LOG_INFO(fmt, ...)  do {} while (0)
#define LOG_WARN(fmt, ...)  do {} while (0)
#define LOG_ERROR(fmt, ...) do {} while (0)

#define LOG_HEX_DEBUG(data, len) do {} while (0)
#define LOG_HEX_INFO(data, len)  do {} while (0)
#define LOG_HEX_WARN(data, len)  do {} while (0)
#define LOG_HEX_ERROR(data, len) do {} while (0)

#endif  // LOGGER_ON

#endif /* _LOGGER_H_ */
