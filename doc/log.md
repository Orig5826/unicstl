
# 日志

### 2026-05-16

### 2026-05-15
1. ringbuffer，resize扩容，截断的处理代码简化了。

### 2026-05-14
1. darray模块，insert传参obj没有判断NULL，导致crash
2. darray模块，reseze没有处理当realloc之后，size > capacity 的情况
