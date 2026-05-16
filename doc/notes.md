
# notes

## rawbuf
> 只对malloc封装，方便对特定目标进行index访问
- 特点：支持随机访问，不支持扩容

## segarray
`2026-05-16`

### 1. darray + darray
> 放弃，darray做map不好管理索引

### 2. ringbuf + darray
> 放弃，darray随机访问，只能访问有效区域

### 3. ringbuf + rawbuf
> 实现便捷，但扩容时，可能存在空闲内存问题

$$ objs:capacity = mapcap * segcap * objsize $$
$$ memory = mapcap * sizeof(pointer) + objs:capacity $$

最坏情况浪费内存：(mapcap - 1) * segcap * objsize

### 4. ringbuf + rawbuf + ringbuf(use stack: mapfree)
> 完美
**用栈作free比queue有优势，因为刚刚使用过的内存，缓存命中概率高。**

$$ objs:capacity = mapcap * segcap * objsize $$
$$ memory = 2 * mapcap * sizeof(pointer) + objs:capacity $$

最坏情况浪费内存：(segcap - 1) * objsize

### 5. based on scheme 4, limited to 512 bytes
> obj_size < 512 ? segsize=512 : segsize=1

## ringbuf

对于嵌入式场景下（没有malloc，也即不扩容的场景），需要用到的estack和equeue，只选择ringbuf即可。而不使用segarray。
```c
bool ringbuf_init(struct _ringbuf *self, size_t obj_size, size_t capacity, void *mem_base);|
```

### 不扩容场景
ringbuf比segarray更节省内存。ringbuf只多一个obj_size的空间。

$$
    membase:size = objsize * (capacity + 1)
$$

而segarray是不确定的，所以segarray就得按照可能的最大空间分配。比如方案4的情况下：
seghead默认是放中间的，方便不需要库容的时候，push_back和push_front一开始不用分配内存。
则为了保证push_back和push_front都能够用，至少需要三个空间。

$$
mem_base_size = obj_size * (capacity * 3) 
$$

当然了，若非要将segarray用于嵌入式场景。也可以将seghead初始放在首段开头，那么需要的总内存为：

$$
mem_base_size = obj_size * (capacity * 2) 
$$

**因此，若嵌入式不扩容场景下，ringbuf更节省内存。**
这可能也是Rust的底层VecDeque选择使用ringbuf的原因。

### 小文件库容

对于小文件，ringbuf库容全内存搬移，还尚可以接受。
segarray扩容，开新segment，然后指向新的segment，性能也不差。

### 大文件扩容
但对于大文件，ringbuf库容全内存搬移，代价太大。

而segarray库容，不会触发大量数据搬移，而是新建一个segment，然后指向新的segment。

**因此，对于大文件扩容场景下，segarray远胜于ringbuf**



## 经典问题

### 2026-05-15
1. ringbuffer，resize扩容，截断的处理代码简化了。

### 2026-05-14
> 这就是单元测试的魅力
1. darray模块，insert传参obj没有判断NULL，导致crash
2. darray模块，resize没有处理当realloc之后，size > capacity 的情况
