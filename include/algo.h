/**
 * @file algo.h
 * @author wenjf (Orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-14
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _ALGO_H_
#define _ALGO_H_

#include "unicstl_internal.h"

// --------------------------------------------------
// 排序算法
// void __cdecl qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__cdecl *_PtFuncCompare)(const void *,const void *));
// --------------------------------------------------
// 1. 冒泡排序
bool bubble_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 2. 插入排序
bool insert_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 3. 快速排序
bool quick_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 4. 堆排序
bool heap_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 5. 归并排序
bool merge_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 6. 选择排序
bool select_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 7. 希尔排序
bool shell_sort(void* base, size_t count, size_t obj_size, compare_fun_t cmp);

// 非比较类排序
// 8. 基数排序
bool radix_sort(void* base, size_t count, size_t obj_size);
// 9. 桶排序
bool bucket_sort(void* base, size_t count, size_t obj_size);
// 10. 计数排序
bool counting_sort(void* base, size_t count, size_t obj_size);

// --------------------------------------------------
// 查找算法
// void *__cdecl bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__cdecl *_PtFuncCompare)(const void *,const void *));
// --------------------------------------------------
// 1. 线性查找
int linear_search(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp);

// 2. 二分查找（默认左边界）
int binary_search(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp);
// 3. 二分查找（右边界）
int binary_search_right(const void* key, const void* base, size_t count, size_t obj_size, compare_fun_t cmp);


#ifdef UNICSTL_ALGO_ENABLE

#ifdef UNICSTL_ALGO_SORT
#define unicstl_sort(base, count, obj_size, cmp) \
    quick_sort(base, count, obj_size, cmp)
#endif // UNICSTL_ALGO_SORT

#ifdef UNICSTL_ALGO_BSEARCH
#define unicstl_search(base, count, obj_size, key, cmp) \
    binary_search(base, count, obj_size, key, cmp)
#endif // UNICSTL_ALGO_BSEARCH

#else

#endif // UNICSTL_ALGO_ENABLE

#endif // _ALGO_H_
