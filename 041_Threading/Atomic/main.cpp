#include <iostream>
#include <thread>
#include <iomanip>
#include <cmath>
#include <random>
#include <mutex>
#include <chrono>
#include <ranges>
#include <map>
#include <condition_variable>
#include "../algebra.h"

class Benchmark {
public:
    Benchmark() = default;
    
    template<typename Callable, typename... Args>
    void add_benchmark(const std::string& name, Callable function, Args... args) {
        std::cout << "Adding benchmark: " << name << std::endl;
        ++active_threads;

        processes.emplace_back([this, name_copy = name, func = std::move(function), 
                                args_tuple = std::make_tuple(std::move(args)...)]() {
            {
                std::lock_guard<std::mutex> lock(gLock);
                logprocess[std::this_thread::get_id()] = name_copy;
            }
            cv.notify_all();
            
            auto run_func = [&]() {
                return std::apply(func, args_tuple);
            };
            
            // Warmup runs
            for (int i = 0; i < 5; ++i) {
                sink = run_func();
            }
            
            // Actual benchmark
            auto st = std::chrono::high_resolution_clock::now();
            const int num = 10'000;
            for (int i = 0; i < num; ++i) {
                sink = run_func();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - st);
            
            {
                std::lock_guard<std::mutex> lock(gLock);
                std::cout << std::fixed << std::setprecision(6)
                            << "Benchmark: " << name_copy
                            << "\nTotal Time: " << diff.count() << " microsecs"
                            << "\nAverage Time: " << static_cast<double>(diff.count()) / num << " microsecs/iteration"
                            << std::endl;
                logprocess.erase(std::this_thread::get_id());
            }
            
            --active_threads;
            cv.notify_all();
        });
    }
    
    void showProcesses() {
        std::unique_lock<std::mutex> lock(gLock);
        std::cout << "Number of processes currently active: " << active_threads << std::endl;
        
        if (active_threads == 0) {
            std::cout << "No active processes." << std::endl;
            return;
        }
        
        // Wait until at least one process has registered in the logprocess map
        cv.wait(lock, [this]() { return !logprocess.empty() || active_threads == 0; });
        
        for (const auto& [thread_id, process_name] : logprocess) {
            std::cout << "Process ID: " << thread_id << " Name: " << process_name << std::endl;
        }
    }
    
    ~Benchmark() {
        for (auto& process : processes) {
            if (process.joinable())
                process.join();
        }
    }
    
private:
    std::vector<std::thread> processes;
    std::map<std::thread::id, std::string> logprocess;
    std::mutex gLock;
    std::condition_variable cv;
    std::atomic<int> active_threads{0};
    volatile double sink{};
};

int main() {
    using namespace std::literals::chrono_literals;
    Benchmark b;
    b.add_benchmark(
        "Binomial : 1/6, 12, 7",
        &elements::binomial,
        1.0/6, 12, 7
    );

    b.add_benchmark(
        "Cos : 0.85",
        &elements::cos,
        0.85
    );

    b.add_benchmark(
        "Binomial : 0.46, 20, 2",
        &elements::binomial,
        0.46, 20, 2
    );

    b.add_benchmark(
        "Cos : -0.25",
        &elements::cos,
        -0.25
    );

    b.add_benchmark(
        "Binomial : 5/11, 12, 2",
        &elements::binomial,
        5.0/11, 12, 7
    );
    b.showProcesses();
}