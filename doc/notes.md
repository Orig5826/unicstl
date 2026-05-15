
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
