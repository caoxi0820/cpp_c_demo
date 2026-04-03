/**
 * C 语言回调函数 Demo
 *
 * 回调函数的本质：把一个函数的指针作为参数传给另一个函数，
 * 让被调用方在合适的时机"回过头来调用"你提供的函数。
 *
 * 本 demo 演示三种典型场景：
 *   1. 基础回调 —— 事件通知
 *   2. 带用户数据的回调 —— 通过 void* 传递上下文
 *   3. 数组排序 —— qsort 就是标准库中最经典的回调用法
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========== 场景 1：基础回调 - 事件通知 ========== */

/* 定义回调函数类型：接收一个事件名称字符串 */
typedef void (*event_callback_t)(const char *event_name);

/* 模拟一个会触发事件的"引擎" */
void run_engine(event_callback_t on_event)
{
    printf("[Engine] 启动中...\n");
    on_event("ENGINE_STARTED");

    printf("[Engine] 处理数据...\n");
    on_event("DATA_PROCESSED");

    printf("[Engine] 关闭中...\n");
    on_event("ENGINE_STOPPED");
}

/* [CALLBACK] 用户提供的回调实现 —— 传给 run_engine() 作为回调 */
void my_event_handler(const char *event_name)
{
    printf("  -> [Handler] 收到事件: %s\n", event_name);
}

/* ========== 场景 2：带用户数据的回调 ========== */

typedef void (*progress_callback_t)(int percent, void *user_data);

void download_file(const char *url, progress_callback_t on_progress, void *user_data)
{
    printf("[Download] 开始下载: %s\n", url);
    for (int i = 25; i <= 100; i += 25) {
        on_progress(i, user_data);
    }
    printf("[Download] 完成!\n");
}

/* 用户数据结构 */
typedef struct {
    char task_name[64];
    int call_count;
} download_context_t;

/* [CALLBACK] 带用户数据的回调实现 —— 传给 download_file() 作为回调 */
void my_progress_handler(int percent, void *user_data)
{
    download_context_t *ctx = (download_context_t *)user_data;
    ctx->call_count++;
    printf("  -> [%s] 进度: %d%% (第 %d 次回调)\n",
           ctx->task_name, percent, ctx->call_count);
}

/* ========== 场景 3：qsort 回调 - 标准库经典用法 ========== */

/* 回调的返回值直接决定了调用方的行为。qsort 每次比较两个元素时都调用你的回调
 * 根据你返回的正/负/零来决定元素的排列顺序。换一个回调函数，排序结果就完全不同
 * 回调在这里不是"旁观者"，而是"决策者"。
 * 回调是双向的，调用方依赖你的返回值来做决策（int）
 * 这个思路在 C++ 里演变成了 std::sort + 仿函数/lambda
 * 在更高层的设计模式里就是策略模式（Strategy Pattern）
 */

/* [CALLBACK] 升序比较 —— 传给 qsort() 作为回调 */
int compare_int_asc(const void *a, const void *b)
{
    return (*(const int *)a) - (*(const int *)b);
}

/* [CALLBACK] 降序比较 —— 传给 qsort() 作为回调 */
int compare_int_desc(const void *a, const void *b)
{
    return (*(const int *)b) - (*(const int *)a);
}

void print_array(const char *label, const int *arr, int n)
{
    printf("  %s: [", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

/* ========== main ========== */

int main(void)
{
    printf("===== 场景 1: 基础回调 - 事件通知 =====\n");
    run_engine(my_event_handler);

    printf("\n===== 场景 2: 带用户数据的回调 =====\n");
    download_context_t ctx;
    strncpy(ctx.task_name, "文件A", sizeof(ctx.task_name) - 1);
    ctx.task_name[sizeof(ctx.task_name) - 1] = '\0';
    ctx.call_count = 0;
    download_file("https://example.com/file.zip", my_progress_handler, &ctx);

    printf("\n===== 场景 3: qsort 回调 =====\n");
    int nums[] = {42, 7, 13, 99, 1, 55};
    int n = sizeof(nums) / sizeof(nums[0]);

    print_array("原始", nums, n);

    qsort(nums, n, sizeof(int), compare_int_asc);
    print_array("升序", nums, n);

    qsort(nums, n, sizeof(int), compare_int_desc);
    print_array("降序", nums, n);

    return 0;
}
