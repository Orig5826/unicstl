
# performance

## 性能对比

### 测试环境

| 测试环境 | 详细信息 |
| --------| -----|
| CPU    | Intel(R) Pentium(R) G4560 @ 3.50GHz |
| 内存   | 16GB |
| OS     | win10 22H2 |
| gcc    | mingw (x86_64-posix-seh-rev0, Built by MinGW-Builds project) 13.2.0 |


### 测试方案
```
T0: capacity = 1024, obj_size = 256
T1: capacity = 4096, obj_size = 256
T2: capacity = 8192, obj_size = 256
T3: capacity = 1024, obj_size = 4096
T4: capacity = 4096, obj_size = 4096
T5: capacity = 8192, obj_size = 4096
```

### 测试对比
> 这里是总时间，对比意义不大。而且目前都未使用扩容

1. 链表实现的栈和队列

```bash
       function                    T0 (ms)   T1 (ms)   T2 (ms)   T3 (ms)   T4 (ms)   T5 (ms)
 --------------------            ---------  ---------  ---------  ---------  ---------  ---------
perf_deque_new()                     0.013     0.011     0.008     0.008     0.013     0.014
perf_deque_push_back()               0.161     0.520     1.011     0.626     2.934     7.444
perf_deque_pop_back()                0.032     0.172     0.329     0.236     1.478     2.728
perf_deque_push_front()              0.038     0.162     0.369     0.175     1.019     2.050
perf_deque_pop_front()               0.037     0.146     0.305     0.220     2.061     2.628
perf_deque_free()                    0.001     0.092     0.187     0.357     1.287     2.694
perf_stack_new()                     0.002     0.001     0.002     0.001     0.001     0.001
perf_stack_push()                    0.271     1.003     1.941     1.967     8.882    16.369
perf_stack_pop()                     0.164     1.183     1.893     0.965     3.717     8.114
perf_stack_free()                    0.000     0.001     0.001     0.002     0.001     0.001
perf_queue_new()                     0.018     0.000     0.000     0.000     0.001     0.002
perf_queue_push()                    0.258     1.020     1.947     1.537     7.774    15.220
perf_queue_pop()                     0.162     0.613     1.050     0.811     3.590     7.070
perf_queue_free()                    0.000     0.000     0.000     0.001     0.001     0.001
```

2. 动态数组实现的栈和队列（这里还不涉及到扩容）

```bash
       function                    T0 (ms)   T1 (ms)   T2 (ms)   T3 (ms)   T4 (ms)   T5 (ms)      
 --------------------            ---------  ---------  ---------  ---------  ---------  --------- 
perf_deque_new()                     0.011     0.018     0.015     0.033     0.017     0.017      
perf_deque_push_back()               0.187     0.650     1.216     1.692     2.852     6.202      
perf_deque_pop_back()                0.052     0.219     0.468     0.685     1.332     2.295      
perf_deque_push_front()              0.058     0.262     0.536     0.290     1.155     1.845      
perf_deque_pop_front()               0.055     0.239     0.438     0.427     1.398     2.398      
perf_deque_free()                    0.002     0.151     0.286     0.361     2.695     3.049      
perf_stack_new()                     0.224     0.013     0.013     0.010     0.014     0.014      
perf_stack_push()                    0.036     0.388     0.745     0.801     2.890     6.183      
perf_stack_pop()                     0.035     0.244     0.318     0.236     1.109     3.167      
perf_stack_free()                    0.002     0.113     0.177     0.408     1.272     2.578      
perf_queue_new()                     0.010     0.012     0.007     0.008     0.012     0.014      
perf_queue_push()                    0.148     0.377     0.701     0.737     2.955     6.273      
perf_queue_pop()                     0.030     0.149     0.271     0.230     1.173     2.338      
perf_queue_free()                    0.001     0.094     0.154     0.350     1.273     2.556
```


