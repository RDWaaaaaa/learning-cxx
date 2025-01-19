#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]{0, 1}), cached(2) {}

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached) {
        // 将原对象的资源置为空
        other.cache = nullptr;
        other.cached = 0;
    }
    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止移动到自身
            // 释放当前对象的缓存
            delete[] cache;

            // 转移资源
            cache = other.cache;
            cached = other.cached;

            // 将原对象的资源置为空
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache; // 释放动态分配的数组
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        if (i >= cached) {
            // 计算需要的新缓存大小
            int new_cached = i + 1;

            // 分配新的缓存空间
            size_t *new_cache = new size_t[new_cached];

            // 复制旧缓存内容
            for (int j = 0; j < cached; ++j) {
                new_cache[j] = cache[j];
            }

            // 计算新的斐波那契数列值
            for (int j = cached; j < new_cached; ++j) {
                new_cache[j] = new_cache[j - 1] + new_cache[j - 2];
            }

            // 释放旧缓存
            delete[] cache;

            // 更新缓存指针和大小
            cache = new_cache;
            cached = new_cached;
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
