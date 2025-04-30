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

int default_compare(void* obj1, void* obj2)
{
    printf("compare is not implemented!\n");
    assert(0);
}

void default_print_obj(void* obj)
{
    printf("print_obj is not implemented!\n");
    assert(0);
}
