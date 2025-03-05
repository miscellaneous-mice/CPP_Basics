#include <iostream>
#include <iomanip>

namespace formulas {
    constexpr double factorial(int n) {
        if (n <= 1) [[unlikely]] {
            return n;
        } else [[likely]] {
            return n * factorial(n - 1);
        }
    }

    constexpr double pow(long double x, int n) {
        if (n <= 1) [[unlikely]] {
            return x;
        } else [[likely]] {
            return x * pow(x, n - 1);
        }
    }
}

namespace elements {
    constexpr double nCr(int n, int r) {
        return (formulas::factorial(n)) / 
               (formulas::factorial(n - r) * formulas::factorial(r));
    }

    constexpr double binomial(long double p, int n, int x) {
        return nCr(n, x) * formulas::pow(p, x) * formulas::pow((1 - p), (n - x));
    }
}

volatile double sink{};

template<typename Func, typename... Args>
void benchmark_impl(const std::string& name, Func&& func, Args&&... args) {
    for (int i = 0; i < 5; ++i) {
        sink = func(std::forward<Args>(args)...);
    }
    const int num_runs = 10'000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_runs; ++i) {
        sink = func(std::forward<Args>(args)...);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << std::fixed << std::setprecision(6)
                << "Benchmark: " << name 
                << "\nTotal Time: " << diff.count() << " sec"
                << std::endl;
}

int main() {
    benchmark_impl(
        "Binomial(1/6, 12, 7)", 
        elements::binomial, 
        1.0/6, 12, 7
    );

    benchmark_impl(
        "Binomial(1/6, 7, 2)", 
        elements::binomial, 
        4.0/6, 7, 7
    );

    return 0;
}