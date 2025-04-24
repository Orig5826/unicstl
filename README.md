# unicstl

## 简介
全称: Universal C standard library

基于C语言实现的通用C库。包含常用数据结构和算法

> 标准：--std=c99

[数据结构详细说明](https://blog.wenjianfeng.top)

## 数据结构
|数据结构 | 原理 |说明 |
|---|---|---|
| **stack**   | | **栈** |
| stack_new  | 链表 | |
| stack_new2 | 动态数组 | |
| **list**   | | **列表**
| list_new2  | 动态数组 | |
| **queue**   | | **队列**
| queue_new  | 单向链表 | |
| queue_new2 | 数组 | FIFO/空/满 |
| **deque**   | |**双端队列** |
| deque_new  | 双向循环链表 | |
| **tree**    | |**树** |
| tree_avl_new | 二叉搜索树 | AVL树 |
| tree_rb_new  | 二叉搜索树 | 红黑树 |
| **heap**    | |**堆** |
| heap_new2   | 数组 | 最大堆/最小堆 |

## 特点
| 原理 | 说明 |
| --- | --- |
| 链表 | 有额外指针开销 |
| 动态数组 | 扩容时数据搬移代价较大 |


## 性能比较
|项目| 数组| 链表|
|---|---|---|
|查找| $O(1)$ | $O(n)$ |
|插入| $O(n)$ | $O(1)$ |
|删除| $O(n)$ | $O(1)$ |

**【A1】** 若链表的操作流程为，先查找元素再删除元素。那么时间复杂度确实是$O(n)$。但是链表的增删优势，在其他应用有体现。比如双向队列，插入和删除效率都为$O(1)$。


## 规范
### 版本说明

| 命名 |版本说明 | 范围 | 更新说明 |
|:----: |:----:|:----:|:----:|
| `VERSION_MAJOR` | 主版本号 | 0 ~ 99 | 代码框架大改，完全不兼容旧版 |
| `VERSION_MINOR` | 次版本号 | 0 ~ 99 | 代码框架尽量兼容旧版，增信大功能、修复重大bug等 |
| `VERSION_MICRO` | 小版本号 | 0 ~ 99 | 代码框架兼容旧版，新增小功能、修复bug等 |

举例说明：
```c
// 若 major > 0 ，则代表正式发布版本
#define UNICSTL_VERSION_MAJOR    1
#define UNICSTL_VERSION_MINOR    2
#define UNICSTL_VERSION_MICRO    5
#define UNICSTL_VERSION          ((UNICSTL_VERSION_MAJOR << 16) | (UNICSTL_VERSION_MINOR << 8) | UNICSTL_VERSION_MICRO)
```

### 工程命名
`工程名(_功能)_v版本号_日期(_时间)(-其他信息)`
> 括号内表示可选项

| 其他信息后缀 | 说明 | 详细 
|:----:|:----:|----
| aX | alpha内测版 | 可能仅测试了新增功能，但没有测试新增功能对其他模块的影响
| bX | beta公测版 | 不仅测试了新增功能，也测试了其他模块，尽量保证新增的功能不影响原来的旧功能。
| ... |  | 或者添加其他有有效信息

举例说明：
```shell
unicstl_stack_v1.2.5_20240717-a0.zip

# 带a或者b后缀，表示当前版本发布前的测试版。如果发布后，则直接更新版本号了
```

## 修改日志

### Unicstl 0.0.01 (2025-04-24)
new features:
    - add stack
    - add queue
    - add deque
    - add list
    - add heap
    - add tree
    - add graph
bugfixed: 
    - none
others:
    - none
