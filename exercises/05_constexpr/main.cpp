#include "../exercise.h"
#include <unordered_map>
unsigned long long fibonacci(int i) {
    static std::unordered_map<int, unsigned long long> cache;
    if (cache.find(i) != cache.end()) {
        return cache[i];
    }
    unsigned long long result;
    switch (i) {
        case 0:
            result = 0;
            break;
        case 1:
            result = 1;
            break;
        default:
            result = fibonacci(i - 1) + fibonacci(i - 2);
            break;
    }
    cache[i] = result;
    return result;
}

int main(int argc, char **argv) {
    auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    auto ANS_N = 90;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
