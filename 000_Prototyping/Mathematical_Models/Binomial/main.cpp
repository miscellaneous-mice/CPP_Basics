#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <cmath>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>

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

// Thread-safe output
std::mutex cout_mutex;

class Benchmarker {
private:
    // Volatile to prevent compiler optimizations
    volatile double sink{};

    // Benchmark function with more detailed measurements
    template<typename Func, typename... Args>
    void benchmark_impl(const std::string& name, Func&& func, Args&&... args) {
        // Warmup runs
        for (int i = 0; i < 5; ++i) {
            sink = func(std::forward<Args>(args)...);
        }

        // Actual benchmark
        const int num_runs = 10'000;
        std::vector<double> run_times;
        run_times.reserve(num_runs);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_runs; ++i) {
            sink = func(std::forward<Args>(args)...);
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = end - start;
        
        // Thread-safe output
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << std::fixed << std::setprecision(6)
                      << "Benchmark: " << name 
                      << "\nTotal Time: " << diff.count() << " sec"
                      << std::endl;
        }
    }

public:
    template<typename Func, typename... Args>
    void run_benchmark(const std::string& name, Func&& func, Args&&... args) {
        benchmark_impl(name, std::forward<Func>(func), std::forward<Args>(args)...);
    }
};

int main() {
    Benchmarker benchmarker;
    std::vector<std::thread> threads;

    // Benchmark different parameters in parallel
    threads.emplace_back([&]{ 
        benchmarker.run_benchmark(
            "Binomial(1/6, 12, 7)", 
            elements::binomial, 
            1.0/6, 12, 7
        ); 
    });

    threads.emplace_back([&]{ 
        benchmarker.run_benchmark(
            "Binomial(1/6, 12, 8)", 
            elements::binomial, 
            1.0/6, 12, 8
        ); 
    });

    // Optional: benchmark more variations
    threads.emplace_back([&]{ 
        benchmarker.run_benchmark(
            "Binomial(0.5, 20, 10)", 
            elements::binomial, 
            0.5, 20, 10
        ); 
    });

    threads.emplace_back([&]{ 
        benchmarker.run_benchmark(
            "Binomial(0.5, 100, 90)", 
            elements::binomial, 
            0.5, 100, 90
        ); 
    });

    // Wait for all threads to complete
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}