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

static inline void mem_swap(const void *obj1, void *obj2, size_t obj_size)
{
    size_t cnt = obj_size;
    for(size_t i = 0; i < cnt; ++i)
    {
        char tmp = ((char*)obj1)[i];
        ((char*)obj1)[i] = ((char*)obj2)[i];
        ((char*)obj2)[i] = tmp;
    }
}

static inline void obj_swap(const void *base, size_t index1, size_t index2, size_t obj_size)
{
    mem_swap((char*)base + index1 * obj_size, (char*)base + index2 * obj_size, obj_size);
}

static inline int compare_obj(const void *base, size_t index1, size_t index2, size_t obj_size, compare_fun_t cmp)
{
    return cmp((char*)base + index1 * obj_size, (char*)base + index2 * obj_size);
}

// 1. 冒泡排序
bool bubble_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    if (base == NULL || count <= 1)
    {
        return false;
    }

    size_t i = 0, j = 0;
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            if(compare_obj(base, j, j + 1, obj_size, cmp) > 0)
            {
                obj_swap(base, j, j + 1, obj_size);
            }
        }
    }
    return true;
}

// 2. 插入排序
bool insert_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    if (base == NULL || count <= 1)
    {
        return false;
    }

    size_t i = 0, j = 0;
    for (i = 1; i < count; i++)
    {
        for (j = i; j > 0; j--)
        {
            if(compare_obj(base, j-1, j, obj_size, cmp) > 0)
            {
                obj_swap(base, j-1, j, obj_size);
            }
            else
            {
                break;
            }
        }
    }
    return true;
}

// 3. 快速排序
bool quick_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp)
{
    return insert_sort(base, count, obj_size, cmp);
    // return false;
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
