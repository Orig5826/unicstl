
# 问题和解决方案

## 1. 多文件打印测试文件路径不合理的问题
新增宏定义，可放于unity_config.h中，用来让测试文件路径显示为当前测试文件，而不是主test.c文件。
方便针对多文件测试，快速定位错误。
```c
#define RUN_TEST_WITH_CURRENT_FILE      1
```

另外，修改了两个函数，新增文件路径参数。
```c
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum, const char* FileName);

void UnityConcludeTest(const char *FileName);
```
