#include <iostream>
#include <variant>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cmath>
#include <random>
#include <ranges>
#include <mutex>
#include "../algebra.h"


std::mutex gLock;

static unsigned long long num_execs;

class ContextManager {
public:
    ContextManager() = default;
    ~ContextManager() {
        for(auto& thread : threads) {
            if(thread.joinable())
                thread.join();
        }
    }

    template<typename Callable, typename... Args>
    void backgroundTasks(std::string name, Callable&& func, Args&&... args) {
        threads.emplace_back([&](){
            for (int i = 0; i < 5; ++i) {
                inc_exec();
                sink = func(std::forward<Args>(args)...);
            }
            sink = func(std::forward<Args>(args)...);
            const int num_runs = 1'000;

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < num_runs; ++i) {
                inc_exec();
                sink = func(std::forward<Args>(args)...);
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> diff = end - start;
            
            {
                std::lock_guard<std::mutex> lock(gLock);
                std::cout << std::fixed << std::setprecision(6)
                            << "Benchmark: "<< name
                            << "\nTotal Time: " << diff.count() << " sec"
                            << std::endl;
            }
        });
    }

    ContextManager(const ContextManager&) = delete;
    ContextManager& operator=(const ContextManager&) = delete;

    ContextManager(ContextManager&& other) noexcept : threads(std::move(other.threads)) {}
    ContextManager& operator=(ContextManager&& other) noexcept {
        for(auto& thread : threads) {
            if(thread.joinable())
                thread.join();
        }
        threads = std::move(other.threads);
        return *this;
    }
private:
    std::vector<std::thread> threads;
    volatile double sink{};
    std::function<void()> inc_exec = [=] {
        std::lock_guard<std::mutex> lock(gLock);
        num_execs++;
    };
};

int main() {
    {
        ContextManager c;
        c.backgroundTasks(
            "Binomial(1/6, 12, 7)",
            &elements::binomial,
            1.0/6, 12, 7
        );

        c.backgroundTasks(
            "cos(0.4)",
            &elements::cos,
            0.4
        );

        c.backgroundTasks(
            "Binomial(1/6, 12, 2)",
            &elements::binomial,
            1.0/6, 12, 2
        );

        c.backgroundTasks(
            "cos(-0.85)",
            &elements::cos,
            -0.85
        );

        c.backgroundTasks(
            "Binomial(0.5, 20, 10)",
            &elements::binomial,
            0.5, 20, 10
        );
    }

    std::cout<<"Number of executions : "<<num_execs<<std::endl;

    return 0;
}
