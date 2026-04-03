# C/C++ Demos

学习和调试用的 C/C++ 小型 demo 集合。

## 构建

```bash
cmake -B build -S .
cmake --build build
```

Windows (MSVC):
```bash
cmake -B build -S . -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## Demo 列表

| 目录 | 说明 |
|------|------|
| `demos/01_callback_c` | C 语言回调函数 |
| `demos/01_callback_cpp` | C++ 回调函数（函数指针、std::function、lambda、仿函数） |
