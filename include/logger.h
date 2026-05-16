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

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO  = 1,
    LOG_WARN  = 2,
    LOG_ERROR = 3,
    LOG_NONE  = 4,
}loglevel_t;

typedef enum {
    LOG_DETAIL_DISABLE = 0,
    LOG_DETAIL_ENABLE = 1,
}logdetail_t;

// -------------------- log config --------------------
#ifdef LOGGER_ENABLE

#ifndef LOG_LEVEL
#define LOG_LEVEL                   LOG_ERROR
#endif

#ifndef LOG_DEBUG_DETAIL
#define LOG_DEBUG_DETAIL            LOG_DETAIL_DISABLE
#endif

#ifdef LOG_FILE_ENABLE
#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME                "unicstl.log"
#endif
#endif

// -------------------- log print --------------------
#define _LOG_STR(x) #x
#define _LOG_STR_IMPL(x) _LOG_STR(x)
#define _LOG_LEVEL_STR(level) (_LOG_STR_IMPL(level) + 4)

#define _LOG_LEVEL_PRINT(level) do{\
    printf("[%5.*s] ", (int)strlen(_LOG_LEVEL_STR(level)),_LOG_LEVEL_STR(level)); \
}while(0)

#if LOG_DEBUG_DETAIL == LOG_DETAIL_ENABLE
#define _LOG_HEADER_PRINT(level, fmt, ...) do {\
    if ((int)level >= (int)LOG_LEVEL) {\
        _LOG_LEVEL_PRINT(level);\
        printf("%s:%d %s()\t", __FILE__, __LINE__, __func__); \
    }\
} while (0)
#else
#define _LOG_HEADER_PRINT(level, fmt, ...) do {
    if ((int)level >= (int)LOG_LEVEL) {\
        _LOG_LEVEL_PRINT(level);\
    }\
} while (0)
#endif

#define _LOG_PRINT(level, fmt, ...) do {\
    if (level >= (int)LOG_LEVEL) {\
        _LOG_HEADER_PRINT(level, fmt, ##__VA_ARGS__);\
        printf("@" fmt "\n", ##__VA_ARGS__);\
    }\
} while (0)

#define _LOG_HEX(level, data, len) do {\
    if (level >= LOG_LEVEL) {\
        for(uint32_t i_temp = 0; i_temp < len; i_temp++) { \
            if(i_temp != 0 && (i_temp % 4 == 0)){ printf(" ");}\
            if(i_temp != 0 && (i_temp % 64 == 0)){ printf("\n");}\
            printf("%02x", ((uint8_t*)(data))[i_temp]);\
        }\
        printf("\n");\
    }\
} while (0)


// -------------------- log api --------------------
#ifndef LOG_FILE_ENABLE

#define log_init()                  do {} while (0)
#define log_deinit()                do {} while (0)

#define log_debug(fmt, ...)         _LOG_PRINT(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)          _LOG_PRINT(LOG_INFO, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)          _LOG_PRINT(LOG_WARN, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)         _LOG_PRINT(LOG_ERROR, fmt, ##__VA_ARGS__)

#define log_debug_hex(data, len)    _LOG_HEX(LOG_DEBUG, data, len)
#define log_info_hex(data, len)     _LOG_HEX(LOG_INFO, data, len)
#define log_warn_hex(data, len)     _LOG_HEX(LOG_WARN, data, len)
#define log_error_hex(data, len)    _LOG_HEX(LOG_ERROR, data, len)

#else

#define log_init()                  logger_init(LOG_FILE_NAME)
#define log_deinit()                logger_deinit()

#define log_debug(fmt, ...)         logger(LOG_DEBUG, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)          logger(LOG_INFO, __FILE__, __LINE__, __func__,fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)          logger(LOG_WARN, __FILE__, __LINE__, __func__,fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)         logger(LOG_ERROR, __FILE__, __LINE__, __func__,fmt, ##__VA_ARGS__)

#define log_debug_hex(data, len)    logger_hex(LOG_DEBUG, data, len)
#define log_info_hex(data, len)     logger_hex(LOG_INFO, data, len)
#define log_warn_hex(data, len)     logger_hex(LOG_WARN, data, len)
#define log_error_hex(data, len)    logger_hex(LOG_ERROR, data, len)

void logger_init(const char *file_name);
void logger_deinit(void);
void logger(loglevel_t level, const char *file_name, int line, const char *func_name, const char *format, ...);
void logger_hex(loglevel_t level, const void *data, size_t len);

#endif


#else // no LOGGER_ENABLE

#define log_debug(fmt, ...) do {} while (0)
#define log_info(fmt, ...)  do {} while (0)
#define log_warn(fmt, ...)  do {} while (0)
#define log_error(fmt, ...) do {} while (0)

#define log_debug_hex(data, len) do {} while (0)
#define log_info_hex(data, len)  do {} while (0)
#define log_warn_hex(data, len)  do {} while (0)
#define log_error_hex(data, len) do {} while (0)

#endif  // LOGGER_ENABLE

#endif /* _LOGGER_H_ */
