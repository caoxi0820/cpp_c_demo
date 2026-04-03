# C 回调函数 Demo

演示 C 语言中回调函数的三种典型用法：

1. 基础回调 - 事件通知
2. 带 `void*` 用户数据的回调 - 传递上下文
3. `qsort` 回调 - 标准库经典用法

代码中所有回调函数都用 `[CALLBACK]` 注释标记，方便快速定位。

## 编译

使用项目根目录 CMake（编译所有 demo）：

```bash
# 在项目根目录执行
cmake -B build -S .
cmake --build build
./build/demos/01_callback/c/callback_c
```

直接使用 gcc：

```bash
gcc -std=c11 -Wall -o callback_c main.c
./callback_c
```

Windows (MSVC)：

```bash
cl /W4 main.c /Fe:callback_c.exe
callback_c.exe
```
