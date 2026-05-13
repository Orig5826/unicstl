
# 笔记

## 单元测试找bug

`2026-05-14`
1. darray模块，insert传参obj没有判断NULL，导致crash
2. darray模块，reseze没有处理当realloc之后，size > capacity 的情况
