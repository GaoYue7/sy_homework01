# 嵌入式系统作业1

## 实验说明
本仓库用于完成嵌入式系统课程第一次Git作业，包含两个版本的HelloWorld程序。

---

## ex01/hello.c 版本迭代记录

### 版本1（第一次提交）
基础HelloWorld程序，仅实现控制台输出固定字符串。
```c
#include <stdio.h>
int main() {
    printf("Hello, World!\n");
    return 0;
}