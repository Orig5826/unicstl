# unicstl

## 简介
基于C语言实现的通用C库，包含常用数据结构和算法。

**全称：** Universal C standard library

**作者：** 温建峰

**主页：** [博客](https://blog.wenjianfeng.top)

**邮箱：**[orig5826@163.com](mailto:orig5826@163.com)

**gitee：**[源码](https://gitee.com/apaki/unicstl)

**github：**[镜像](https://github.com/Orig5826/unicstl)


## 设计架构

```mermaid
classDiagram
direction TB

namespace basic {
    class ringbuf{
        不扩容或
        小数据扩容
    }
    class rawbuf
    class darray
    class linklist{
        <<单链表>>
    }
    class dlinklist{
        <<双向链表>>
    }
}

namespace embed {
    class estack
    class equeue
}

namespace iter {
    class iterator{
        + hasnext()
        + next() 
    }
}

namespace hal {
    class segarray{
        大数据
        优先扩容
    }
    class arraylist{
        切片
        负索引
    }
    class string
    class hashtable
}

namespace adapter {
    class deque
}

namespace top {
    class stack
    class queue
    class rbtree
    class map
    class unordered_map
}

%% hal层
segarray *-- ringbuf : 组合
segarray *-- rawbuf : 组合

arraylist *-- darray : 组合
string *-- arraylist : 组合
hashtable *-- darray : 组合


%% 适配器
deque *-- ringbuf : 组合
deque *-- segarray : 组合

%% 通用标准容器
stack *-- deque : 组合
queue *-- deque : 组合

%% 红黑树
rbtree ..> stack : 依赖
rbtree ..> queue : 依赖

%% 高级容器
map *-- rbtree : 组合
unordered_map *-- hashtable : 组合

%% 嵌入式专用容器
estack ..> ringbuf : 依赖
equeue ..> ringbuf : 依赖
```

## 数据结构

### 底层基础容器

|数据结构 |名称 |说明 |
|---|---|---|
| linklist   | 单链表 | 
| dlinklist   | 双向链表 |
| darray  | 动态数组 | 扩容
| ringbuf   | 环形缓存区 | 扩容/外部缓存 
| rawbuf | 原始缓冲区 | 动态分配固定容量/外部缓存
| segarray | 分段数组 | 扩容

### 中层容器
|数据结构 |名称 |说明 |
|---|---|---|
| segarray | 分段数组 | 扩容
| arraylist | 动态数组 | 扩容（负索引/切片）

**使用建议**
- ringbuf 小数据，少库容
- segarray 大数据，优先扩容

### 通用标准容器
> 基于底层封装

|数据结构 |名称 |说明 |
|---|---|---|
| deque  | 双端队列 | 扩容
| stack  | 栈 | 扩容
| queue  | 队列 | 扩容
| ustring | 字符串 | 扩容

### 嵌入式专用容器
> 适配嵌入式场景、外置内存、无动态堆分配

|数据结构 |名称 |说明 |
|---|---|---|
| estack | 栈 | 外部缓存
| equeue  | 队列 | 外部缓存


## 性能对比
|应用场合  |ringbuf  |segarray | 说明
|----------|---------|---------|--------------
|不扩容    |内存优势 | 内存浪费| 嵌入式无堆内存
|小对象扩容|尚可     | 优秀    | 开销低，后者无拷贝更丝滑
|大对象扩容|性能较差 | 极致优秀| 前者整体搬移，后者分段扩容


## 接口函数原型
```c
// -------------------- 初始化 --------------------
struct* new(size_t obj_size, size_t capacity);  // 创建
void free(struct**);                            // 释放

bool init(size_t obj_size, size_t capacity, void *mem_base);    // 静态初始化，支持传入外部缓存

// 外部实现
int compare(void* obj1, void* obj2);    // 比较函数，若调用了和比较有关的接口，需要在初始化后配置（树、图必须）

// -------------------- 核心功能 --------------------
// 核心操作
bool push(const void* obj);             // [栈、队列] 入栈/入队
bool push_front(const void* obj);       // [双端队列] 头部入队
bool push_back(const void* obj);        // [双端队列] 尾部入队
bool append(const void* obj);           // [动态数组] 追加元素 <push_back>

bool pop(void* obj);                    // [栈、队列，动态数组] 出栈/出队/移除元素
bool pop_front(void* obj);              // [双端队列] 头部出队
bool pop_back(void* obj);               // [双端队列] 尾部出队

bool peek(void* obj);                   // [栈]            查看栈顶元素
bool front(void* obj);                  // [队列、双端队列] 查看头部元素
bool back(void* obj);                   // [队列、双端队列] 查看尾部元素

// 基础操作
size_t size();                          // 获取大小
size_t capacity();                      // 获取容量
bool empty();                           // 判断是否空
bool full();                            // 判断是否满
void clear();                           // 清空

// 迭代器操作
iterator_t iter(...);                   // 返回迭代器
bool iter_hasnext();                    // 是否有下一个元素
const void* iter_next();                // 迭代器下一个元素 <只读访问>

// 索引操作
size_t index(void *obj);                // 获取元素索引, -1为不存在

bool insert(size_t index, const void* obj);     // 插入元素
bool remove(size_t index, const void *obj);     // 删除元素 < delete !!!废弃：防止项目用于C++，关键字冲突>
bool erase(size_t index, size_t count);         // 删除区间元素

// 随机访问
bool set(uint32_t index, const void* obj);      // 设置元素
bool get(uint32_t index, void* obj);            // 获取元素
const void* at(size_t index);                   // 获取元素指针

// 排序 & 搜索
bool sort();                                // 排序
bool search(const void* obj);               // 搜索元素 <返回索引，-1为不存在>

// 统计
uint32_t count(const void* obj);        // 统计元素的个数
bool contains(const void* obj);         // 判断元素是否存在 <返回bool>

// 树
bool insert(const void* obj);       // [树] 插入元素
bool delete(const void* obj);       // [树] 删除元素
bool add_(const void* obj);         // [图：顶点、边] 添加元素 <add不考虑位置关系>
bool del_(const void* obj);         // [图：顶点、边] 删除元素 
bool find_(const void* obj);        // [图：顶点、边] 查找元素
```

### 分支命名
| 分支    | 作用         | 示例
|-------- |------------ | ----
| master  | 稳定主分支  | master
| dev     | 开发主分支  | dev-stack
| test    | 功能测试    | test-tree
| release | 版本发布    | v1.2.5
| ---     | ---         | ---
| feature | 新增独立功能| feature-tree
| bugfix  | 问题修复    | bugfix-map
| refactor| 架构重构    | refactor-darray

**基础命名规则**
- 简易单层命名：**分支[`-`模块]**
    - 示例：`dev-stack`、`test-tree`、`refactor`
- 多层细分命名：**模块`/`分支[`-`功能]**
    - 示例：`stack/dev-push` `rbtree/test-insert` `v0.0.02/refactor`

## 修改日志

### Unicstl 0.0.10 (2026-5-11)
- new features
    - add darray/ringbuf/linlist/dlinklist
    - add estack/equeue for embedded
    - darray add function: search/sort
    - add algo: sort and search
    - add rawbuf/segarray
    
- refactor: 
    - deque base on ringbuf
    - stack base on deque 
    - queue base on deque

### Unicstl 0.0.02 (2025-05-06)
- new features
    - graph add function: add/del/find vertex/edge
    - graph add function: bfs/dfs
    - tree add new iterator and optimize code
    - deque add order select and delete some functions
    - iter change the name of container/index...
    - list optimize code and add slice function
    - unicstl add default function

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
