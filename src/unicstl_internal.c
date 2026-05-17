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

const char *unicstl_version(void)
{
    return UNICSTL_VERSION_STRING;
}

int default_compare(const void *obj1, const void *obj2)
{
    printf("compare is not implemented!\n");
    unicstl_assert(0);
}

void default_print_obj(const void *obj)
{
    printf("print_obj is not implemented!\n");
    unicstl_assert(0);
}

size_t unicstl_new_capacity(size_t capacity)
{
    size_t new_capacity = 0;
    if (capacity == 0)
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

#define UNICSTL_COMPARE_FUNC(type)                         \
    int compare_##type(const void *obj1, const void *obj2) \
    {                                                      \
        const type num1 = *(const type *)obj1;             \
        const type num2 = *(const type *)obj2;             \
        if (num1 < num2) return -1;                        \
        if (num1 > num2) return 1;                         \
        return 0;                                          \
    }

UNICSTL_COMPARE_FUNC(char)
UNICSTL_COMPARE_FUNC(short)
UNICSTL_COMPARE_FUNC(int)
UNICSTL_COMPARE_FUNC(long)
UNICSTL_COMPARE_FUNC(int8_t)
UNICSTL_COMPARE_FUNC(int16_t)
UNICSTL_COMPARE_FUNC(int32_t)
UNICSTL_COMPARE_FUNC(int64_t)
UNICSTL_COMPARE_FUNC(uint8_t)
UNICSTL_COMPARE_FUNC(uint16_t)
UNICSTL_COMPARE_FUNC(uint32_t)
UNICSTL_COMPARE_FUNC(uint64_t)
UNICSTL_COMPARE_FUNC(size_t)
UNICSTL_COMPARE_FUNC(ssize_t)

int compare_double(const void *obj, const void *obj2)
{
    double num1 = *(double *)obj;
    double num2 = *(double *)obj2;
    if (num1 - num2 < 1e-9 || num2 - num1 < 1e-9)
    {
        return 0;
    }
    return num1 > num2 ? 1 : -1;
}

int compare_float(const void *obj, const void *obj2)
{
    float num1 = *(float *)obj;
    float num2 = *(float *)obj2;
    if (num1 - num2 < 1e-9 || num2 - num1 < 1e-9)
    {
        return 0;
    }
    return num1 > num2 ? 1 : -1;
}

int compare_string(const void *obj1, const void *obj2)
{
    return strcmp(*(const char **)obj1, *(const char **)obj2);
}
