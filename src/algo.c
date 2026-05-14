/**
 * @file algo.c
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "algo.h"

// 1. 冒泡排序
bool bubble_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 2. 插入排序
bool insert_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 3. 快速排序
bool quick_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 4. 堆排序
bool heap_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 5. 归并排序
bool merge_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 6. 选择排序
bool select_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 7. 希尔排序
bool shell_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return false;
}

// 8. 基数排序
bool radix_sort(void* base, size_t count, size_t obj_size)
{
    return false;
}

// 9. 桶排序
bool bucket_sort(void* base, size_t count, size_t obj_size)
{
    return false;
}

// 10. 计数排序
bool counting_sort(void* base, size_t count, size_t obj_size)
{
    return false;
}


int linear_search(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    if (key == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (cmp((const char *)base + i * obj_size, (const char *)key) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 2. 二分查找（默认左边界）
int binary_search(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{

}

// 3. 二分找右边界：右边界
int binary_search_right(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{

}
