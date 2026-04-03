/**
 * C++ 回调函数 Demo
 *
 * C++ 中实现回调有多种方式，灵活性远超 C 语言。
 * 本 demo 演示四种常见方式：
 *   1. 函数指针 —— 和 C 一样的方式
 *   2. std::function —— 通用可调用对象包装器
 *   3. Lambda 表达式 —— 最现代、最常用的方式
 *   4. 仿函数 (Functor) —— 重载 operator() 的类
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

/* ========== 方式 1：函数指针（与 C 兼容） ========== */

using EventCallback = void (*)(const std::string &);

void run_engine(EventCallback on_event)
{
    on_event("ENGINE_STARTED");
    on_event("ENGINE_STOPPED");
}

/* [CALLBACK] 函数指针回调 —— 传给 run_engine() */
void my_handler(const std::string &event)
{
    std::cout << "  -> [函数指针] 事件: " << event << "\n";
}

/* ========== 方式 2：std::function ========== */

using ProgressFn = std::function<void(int percent)>;

void download(const std::string &url, ProgressFn on_progress)
{
    std::cout << "[Download] " << url << "\n";
    for (int i = 25; i <= 100; i += 25) {
        on_progress(i);
    }
}

/* [CALLBACK] 普通函数也能传给 std::function */
void print_progress(int percent)
{
    std::cout << "  -> [std::function] 进度: " << percent << "%\n";
}

/* ========== 方式 3：Lambda 表达式 ========== */

void for_each_item(const std::vector<int> &items,
                   const std::function<void(int)> &callback)
{
    for (int item : items) {
        callback(item);
    }
}

/* ========== 方式 4：仿函数 (Functor) ========== */

/* [CALLBACK] 仿函数 —— 重载 operator() 使对象可被当作回调调用 */
struct Comparator {
    bool ascending;

    explicit Comparator(bool asc) : ascending(asc) {}

    bool operator()(int a, int b) const
    {
        return ascending ? (a < b) : (a > b);
    }
};

void print_vec(const std::string &label, const std::vector<int> &v)
{
    std::cout << "  " << label << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "]\n";
}

/* ========== 方式 5 (bonus)：模板回调 —— 零开销抽象 ========== */

template <typename Callback>
void repeat(int n, Callback cb)
{
    for (int i = 0; i < n; i++) {
        cb(i);
    }
}

/* ========== main ========== */

int main()
{
    std::cout << "===== 方式 1: 函数指针 =====\n";
    run_engine(my_handler);

    std::cout << "\n===== 方式 2: std::function =====\n";
    // 传普通函数
    download("https://example.com/a.zip", print_progress);
    // 也可以传 lambda
    download("https://example.com/b.zip", [](int p) {
        std::cout << "  -> [lambda via std::function] " << p << "%\n";
    });

    std::cout << "\n===== 方式 3: Lambda 表达式 =====\n";
    std::vector<int> items = {10, 20, 30, 40};

    // 无捕获 lambda
    std::cout << "  无捕获:\n";
    for_each_item(items, [](int x) {
        std::cout << "    item = " << x << "\n";
    });

    // 带捕获 lambda —— 累加求和
    int sum = 0;
    for_each_item(items, [&sum](int x) {
        sum += x;
    });
    std::cout << "  带捕获 lambda 求和: " << sum << "\n";

    std::cout << "\n===== 方式 4: 仿函数 (Functor) =====\n";
    std::vector<int> nums = {42, 7, 13, 99, 1, 55};
    print_vec("原始", nums);

    std::sort(nums.begin(), nums.end(), Comparator(true));
    print_vec("升序", nums);

    std::sort(nums.begin(), nums.end(), Comparator(false));
    print_vec("降序", nums);

    std::cout << "\n===== 方式 5: 模板回调 (零开销) =====\n";
    repeat(3, [](int i) {
        std::cout << "  -> 第 " << i << " 次调用\n";
    });

    return 0;
}
