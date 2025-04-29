# unicstl

## 简介
基于C语言实现的通用C库，包含常用数据结构和算法。

**全称：** Universal C standard library

**作者：** 温建峰

**主页：** [博客](https://blog.wenjianfeng.top)

**邮箱：**[orig5826@163.com](mailto:orig5826@163.com)

## 编译环境
- 编译器：gcc 13.2.0 
- 标准：--std=c99

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
| **graph**    | |**图** |
| graph_new   | 链表 |  |

## 接口函数原型
```c
// -------------------- 初始化 --------------------
struct* new(...);                   // 创建
void free(struct**);                // 释放

// 内部接口
// init 初始化  <构造函数>
// destory 销毁 <析构函数>

// 外部实现
int compare(void* obj1, void* obj2);// 比较函数，new后立刻配置（树、图必须）

// -------------------- 核心功能 --------------------
// 核心操作
bool push(const void* obj);         // [栈、队列] 入栈/入队
bool push_front(const void* obj);   // [双端队列] 头部入队
bool push_back(const void* obj);    // [双端队列] 尾部入队

bool pop(void* obj);                // [栈、队列] 出栈/出队
bool pop_front(void* obj);          // [双端队列] 头部出队
bool pop_back(void* obj);           // [双端队列] 尾部出队

bool peek(void* obj);               // [栈]            查看栈顶元素
bool front(void* obj);              // [队列、双端队列] 查看头部元素
bool back(void* obj);               // [队列、双端队列] 查看尾部元素

// bool insert(const void* obj);       // [树] 插入元素 <insert用于和位置相关操作>
// bool delete(const void* obj);       // [树] 删除元素

// bool add_(const void* obj);         // [图：顶点、边] 添加元素 <add不考虑位置关系>
// bool del_(const void* obj);         // [图：顶点、边] 删除元素 
// bool find_(const void* obj);        // [图：顶点、边] 查找元素

// 基础操作
uint32_t size();                    // 获取大小
bool empty();                       // 判断是否为空
bool full();                        // 判断是否为满
void clear();                       // 清空
uint32_t capacity();                // [动态数组] 获取容量

// 迭代器操作
iterator_t iter(...);               // 返回迭代器
bool iter_hasnext();                // 是否有下一个元素
void* iter_next();                  // 迭代器下一个元素

// -------------------- 扩展功能 --------------------
// 元素相关操作
bool append(const void* obj);        // 追加元素 <push_back> 一般用于list 
// bool remove(const void *obj);        // 删除元素 <暂不使用该命名>
bool find(const void* obj);          // 查找元素 <返回值，bool/uint32_t/void*待定？>
bool contains(const void* obj);      // 判断元素是否存在 <返回bool>
uint32_t count(const void* obj);     // 统计元素obj的个数

// 索引相关操作
uint32_t index(void *obj);                      // 获取元素索引
bool insert(uint32_t index, const void* obj);   // 插入元素 <非树>
bool delete(uint32_t index, void* obj);         // 删除元素
// bool erase(uint32_t index);                     // 删除元素<暂时不用该命名>
bool set(uint32_t index, const void* obj);      // 设置元素
bool get(uint32_t index, void* obj);            // 获取元素
```

## 特点
| 原理 | 优势 | 弊端 |
| --- | --- |--- |
| 链表 | 插入删除效率高 | 有额外指针开销 |
| 动态数组 | 随机访问效率高 | 扩容时数据搬移代价较大 |
| --- | --- | --- |
| 单链表 | 适用内存受限场景 | 逆向不便 |
| 双向链表 | 频繁双向遍历的场景（如光标移动） | 空间开销大 |


## 性能比较
| 数据结构 | < | 时 |间 | | 复 | 杂 |度 | > | <空间复杂度> |
|---|---|---|---|---|---|---|---|---|---|
|---|(|**平**|**均**|)  | (|**最**|**坏**| ) |**最坏**|
|---|访问|搜索|插入|删除|访问|搜索|插入|删除|---|
| 数组 | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| 栈 | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| 队列 | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| 单向链表 | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| 双向链表 | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| 跳表 | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n*log(n))$ |
| 哈希表 | $N/A$ | $O(1)$ | $O(1)$ | $O(1)$ | $N/A$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$
| 二叉搜索树 | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| AVL树  | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(n)$ |
| 红黑树 | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(n)$ |
| B树    | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(log(n))$ | $O(n)$ |

**【答疑】** 若链表的操作流程为，先查找元素再删除元素。那么时间复杂度确实是$O(n)$。但是链表的增删优势，在其他应用有体现。比如双向队列，插入和删除效率都为$O(1)$。

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

### Unicstl 0.0.02 (2025-04-24)
- new features
    - graph add function: add/del/find vertex/edge
    - graph add function: bfs/dfs
    - tree remove old iterator and add new iterator
    - deque add order select
- bugfixed: 
    - none
- others:
    - none


### Unicstl 0.0.01 (2025-04-24)
- new features
    - add stack
    - add queue
    - add deque
    - add list
    - add heap
    - add tree
    - add graph
    - add iterator
- bugfixed: 
    - none
- others:
    - none
