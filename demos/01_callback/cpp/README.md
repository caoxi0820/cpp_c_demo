# C++ 回调函数 Demo

演示 C++ 中五种回调实现方式：

1. 函数指针 - 与 C 兼容
2. `std::function` - 通用可调用对象包装器
3. Lambda 表达式 - 无捕获 / 带捕获
4. 仿函数 (Functor) - 重载 `operator()` 的类
5. 模板回调 - 零开销抽象

代码中所有回调函数都用 `[CALLBACK]` 注释标记，方便快速定位。

## 编译

使用项目根目录 CMake（编译所有 demo）：

```bash
# 在项目根目录执行
cmake -B build -S .
cmake --build build
./build/demos/01_callback/cpp/callback_cpp
```

直接使用 g++：

```bash
g++ -std=c++17 -Wall -o callback_cpp main.cpp
./callback_cpp
```

Windows (MSVC)：

```bash
cl /W4 /std:c++17 /EHsc main.cpp /Fe:callback_cpp.exe
callback_cpp.exe
```
