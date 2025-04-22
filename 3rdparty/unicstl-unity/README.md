
# 问题和解决方案

## 1. 添加配置文件
在unity_internals.h文件中添加了宏定义，方便使用unity_config.h文件。
```c
#define UNITY_INCLUDE_CONFIG_H
```

## 2. 多文件打印测试文件路径不合理的问题
修改`RUN_TEST`宏，在测试文件路径前添加`__FILE__`。
借助`UnitySetTestFile`函数，打印的路径信息对多文件测试也有效。
