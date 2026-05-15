
# notes

## rawbuf
> 只对malloc封装，方便对特定目标进行index访问
- 特点：支持随机访问，不支持扩容

## segarray
1. 扩容方案1
```
if map.full
    map.resize
else
    new seg
    map.push(seg)
    seg.set(obj)
```
