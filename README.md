# unicstl

## 简介
全称: Universal C standard library

基于C语言实现的通用C库。包含常用数据结构和算法

> 标准：--std=c99

[数据结构详细说明](http://wenjianfeng.top)

## 数据结构
|数据结构 | 原理 |说明 |
|---|---|---|
| **stack**   | | **栈** |
| stack_new  | 链表 | |
| stack_new2 | 动态数组 | |
| **list**   | | **列表**
| list_init2  | 动态数组 | |
| **queue**   | | **队列**
| queue_init  | 单向链表 | |
| queue_init2 | 数组 | FIFO/空/满 |
| **deque**   | |**双端队列** |
| deque_init  | 双向循环链表 | |
| **tree**    | |**树** |
| tree_avl_init | 二叉搜索树 | AVL树 |
| tree_rb_init  | 二叉搜索树 | 红黑树 |
| **heap**    | |**堆** |
| heap_init2   | 数组 | 最大堆/最小堆 |


## 版本
| 版本 | 说明 |
|:----:|:----:|
| 0.xx.xx  | 测试版本 |
