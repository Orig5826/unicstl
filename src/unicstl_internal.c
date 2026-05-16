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

const char* unicstl_version(void)
{
    return UNICSTL_VERSION_STRING;
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

size_t unicstl_new_capacity(size_t capacity)
{
    size_t new_capacity = 0;
    if(capacity == 0)
    {
        new_capacity = UNICSTL_CAPACITY_INIT;
    }
    else if (capacity < 1024)
    {
        // capacity * 2;
        new_capacity = capacity << 1;
    }
    else
    {
        // capacity + capacity / 8 = capacity * 1.125;
        new_capacity = capacity + (capacity >> 3);
    }
    return new_capacity;
}
