
# performance

## 性能对比

### 测试环境

| 测试环境 | 详细信息 |
| --------| -----|
| CPU    | Intel(R) Pentium(R) G4560 @ 3.50GHz |
| 内存   | 16GB |
| OS     | win10 22H2 |
| gcc    | mingw (x86_64-posix-seh-rev0, Built by MinGW-Builds project) 13.2.0 |

### 测试结果

1. ringbuf和segarray的性能对比
```
T0: obj_size=256, capacity=1024, run_count=1024
T1: obj_size=256, capacity=8192, run_count=8192
T2: obj_size=4096, capacity=1024, run_count=1024
T3: obj_size=4096, capacity=8192, run_count=8192
T4: obj_size=256, capacity=1024, run_count=100000
T5: obj_size=256, capacity=8192, run_count=100000
T6: obj_size=4096, capacity=1024, run_count=100000
T7: obj_size=4096, capacity=8192, run_count=100000

       function                    T0 (us)   T1 (us)   T2 (us)   T3 (us)   T4 (us)   T5 (us)   T6 (us)   T7 (us)        
 --------------------            ---------  ---------  ---------  ---------  ---------  ---------  ---------  --------- 
perf_segarray_new()                  0.008     0.000     0.000     0.000     0.000     0.000     0.000     0.000        
perf_segarray_push_back()            0.215     0.316     0.658     1.038     0.182     0.158     0.795     0.978        
perf_segarray_pop_back()             0.058     0.060     0.231     0.497     0.054     0.056     0.328     0.327
perf_segarray_free()                 0.037     0.026     0.332     0.335     0.022     0.024     0.337     0.308
perf_segarray_new()                  0.001     0.000     0.001     0.000     0.000     0.000     0.000     0.000
perf_segarray_push_front()           0.180     0.148     1.569     1.952     0.172     0.147     1.685     1.942
perf_segarray_pop_front()            0.051     0.060     0.242     0.342     0.062     0.061     0.348     0.368
perf_segarray_free()                 0.034     0.023     0.325     0.342     0.026     0.021     0.369     0.306
perf_ringbuf_new()                   0.006     0.002     0.019     0.003     0.000     0.000     0.000     0.000
perf_ringbuf_push_back()             0.153     0.096     0.983     0.866     0.854     1.060    13.849    14.344
perf_ringbuf_pop_back()              0.030     0.037     0.273     0.275     0.049     0.054     0.344     0.317
perf_ringbuf_free()                  0.032     0.018     0.393     0.371     0.019     0.026     0.340     0.307
perf_ringbuf_new()                   0.006     0.001     0.022     0.003     0.000     0.000     0.000     0.000
perf_ringbuf_push_front()            0.138     0.135     2.114     1.941     0.990     1.252    14.603    13.887
perf_ringbuf_pop_front()             0.039     0.065     0.292     0.365     0.045     0.044     0.516     0.309
perf_ringbuf_free()                  0.000     0.024     0.407     0.408     0.025     0.023     0.605     0.301
```
