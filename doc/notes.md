
# notes

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
