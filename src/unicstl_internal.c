/**
 * @file unicstl_internal.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "unicstl_internal.h"

void _unicstl_assert(const char *expr, const char *file, int line)
{
    printf("Assertion failed: %s, file:%s line:%d\n", expr, file, line);
    exit(1);
}

int default_compare(const void* obj1, const void* obj2)
{
    printf("compare is not implemented!\n");
    unicstl_assert(0);
}

void default_print_obj(const void* obj)
{
    printf("print_obj is not implemented!\n");
    unicstl_assert(0);
}

uint32_t unicstl_new_capacity(uint32_t capacity)
{
    uint32_t new_capacity = 0;
    if(capacity < 4)
    {
        new_capacity = 8;
    }
    else if (capacity < 1024)
    {
        new_capacity = capacity * 2;
    }
    else
    {
        new_capacity = capacity + (capacity >> 3);
    }

    return new_capacity;
}

