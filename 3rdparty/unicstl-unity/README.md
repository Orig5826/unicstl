
# ����ͽ������

## 1. ���ļ���ӡ�����ļ�·�������������
�����궨�壬�ɷ���unity_config.h�У������ò����ļ�·����ʾΪ��ǰ�����ļ�����������test.c�ļ���
������Զ��ļ����ԣ����ٶ�λ����
```c
#define RUN_TEST_WITH_CURRENT_FILE      1
```

���⣬�޸������������������ļ�·��������
```c
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum, const char* FileName);

void UnityConcludeTest(const char *FileName);
```
