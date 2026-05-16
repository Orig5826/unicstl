/**
 * @file logger.c
 * @author wenjf (Orig5826@163.com)
 * @brief
 * @version 0.1
 * @date 2026-05-16
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct log_string
{
    loglevel_t level;
    const char *str;
};


static FILE* log_file = NULL;
struct log_string log_str[] = {
    LOG_DEBUG, "DEBUG",
    LOG_INFO, " INFO",
    LOG_WARN, " WARN",
    LOG_ERROR, "ERROR",
    LOG_NONE, NULL
};


void logger_init(const char *file_name)
{
    log_file = fopen(file_name, "w");
    if (log_file == NULL)
    {
        perror("Failed to open log file");
        exit(-1);
    }
    fprintf(log_file, "\n\n ============================== log start ============================== \n\n");
    fflush(log_file);
}

void logger_deinit()
{
    if (log_file != NULL)
    {
        fprintf(log_file, "\n\n ============================== log end ============================== \n\n");
        fflush(log_file);

        fclose(log_file);
        log_file = NULL;
    }
}

// -------------------- logger function --------------------
void logger(loglevel_t level, const char *file_name, int line, const char *func_name, const char *format, ...)
{
    if ((int)level >= (int)LOG_LEVEL) {
        FILE *file = log_file;
        if (file == NULL) {
            file = stderr;
        }

        fprintf(file, "[%5s] ", log_str[level].str);
        fprintf(file, "%s:%d %s()\t", file_name, line, func_name);

        va_list args;
        va_start(args, format);
        vfprintf(file, format, args);
        va_end(args);

        fprintf(file, "\n");
        fflush(file);
    }
}

void logger_hex(loglevel_t level, const void *data, size_t size)
{
    if ((int)level >= (int)LOG_LEVEL) {
        FILE *file = log_file;
        if (file == NULL) {
            file = stderr;
        }

        const uint8_t *bytes = (const uint8_t *)data;

        for (size_t i_temp = 0; i_temp < size; i_temp++) {
            if (i_temp != 0 && (i_temp % 4 == 0)) {
                fprintf(file, " ");
            }
            if (i_temp != 0 && (i_temp % 16 == 0)) {
                fprintf(file, "\n");
            }
            fprintf(file, "%02x", bytes[i_temp]);
        }
        fprintf(file, "\n");
        fflush(file);
    }
}
