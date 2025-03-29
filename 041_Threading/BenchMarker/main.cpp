#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <pthread.h>
#include <vector>
#include <map>
#include <iomanip>
#include <future>
#include <random>
#include <mach/mach.h>
#include "../algebra.h"


template<typename Callable, typename... Args>
auto SafeTask(Callable&& function, Args&&... args) {
    auto lambda = [func = std::move(function), args_tuple = std::make_tuple(std::move(args)...)]() {
        return std::apply(func, args_tuple);
    };
    return lambda;
}

class Benchmark {
public:
    Benchmark() = default;
    
    template<typename Callable, typename... Args>
    void add_benchmark(const std::string& bench_name, Callable&& function, Args&&... args) {
        futures.emplace_back(std::async(std::launch::async, [&]() -> std::pair<std::string, std::chrono::microseconds> {
            auto run_func = SafeTask(function, std::forward<decltype(args)>(args)...);
            {
                std::lock_guard<std::mutex> lck(mtx);
                std::cout << "Adding benchmark: " << bench_name << std::endl;
                pthread_setname_np(bench_name.c_str());
                bench_status[bench_name] = true;
                cv_ready.notify_one();
            }
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck, [this] { return ready_to_search.load(); });
            lck.unlock();
    
            for (int i = 0; i < 5; ++i) {
                sink = run_func();
            }
            
            using high_res_clk = typename std::chrono::high_resolution_clock;
            auto st = high_res_clk::now();
            for (int i = 0; i < bench_cycles; ++i) {
                sink = run_func();
            }
            auto diff = std::chrono::duration_cast<std::chrono::microseconds>(high_res_clk::now() - st);
            return std::make_pair(bench_name, diff);
        }));

        std::unique_lock<std::mutex> lck(mtx_ready);
        cv_ready.wait(lck, [this, bench_name] {
            return bench_status[bench_name];
        });

    }

    void benchmark_status() {
        processes.emplace_back([&] () {
            task_threads(mach_task_self(), &threads, &thread_count);
            std::cout << "[Report] Number of benchmarks still running: " << futures.size() << std::endl;

            for (int i = 1; i < thread_count; i++) {
                char thread_name[64];
                uint64_t tid;
                pthread_t pthread = pthread_from_mach_thread_np(threads[i]);
                pthread_getname_np(pthread, thread_name, sizeof(thread_name));
                pthread_threadid_np(pthread, &tid);
                if (bench_status.find(thread_name) == bench_status.end()) continue;
                std::cout << "[Report]   - Benchmark: " << thread_name << ", Running in thread id: " << tid << std::endl;
            }
        });
    }

    void run_benchmark() {
        ready_to_search.store(true);
        cv.notify_all();

        while (futures.size() > 0) {
            for (size_t i = 0; i < futures.size(); i++) {
                auto status = futures[i].wait_for(std::chrono::milliseconds(10));
                if (status == std::future_status::ready) {
                    const auto& [pname, tt] = futures[i].get();
                    std::cout << std::fixed << std::setprecision(6)
                                << "\nBenchmark: " << pname
                                << "\nTotal Time: " << tt.count() << " microsecs"
                                << "\nAverage Time: " << static_cast<double>(tt.count()) / bench_cycles
                                << " microsecs/iteration"
                                << std::endl;
                    futures.erase(futures.begin() + i);
                }
            }
        }
    }
    
    ~Benchmark() {
        this->run_benchmark();
        for (auto& process : processes) {
            if (process.joinable())
                process.join();
        }
    }
    
private:
    const int bench_cycles{1'00'000};
    volatile double sink{};
    std::atomic<bool> ready_to_search;

    std::vector<std::future<std::pair<std::string, std::chrono::microseconds>>> futures;
    std::vector<std::thread> processes;
    std::unordered_map<std::string, bool> bench_status;

    std::condition_variable cv;
    std::mutex mtx;

    std::condition_variable cv_ready;
    std::mutex mtx_ready;

    thread_act_array_t threads;
    mach_msg_type_number_t thread_count;
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

    b.benchmark_status();
    b.run_benchmark();
    b.benchmark_status();

    b.add_benchmark(
        "Cos : -0.25",
        &elements::cos,
        -0.25
    );
    b.benchmark_status();
    b.add_benchmark(
        "Binomial : 5/11, 12, 2",
        &elements::binomial,
        5.0/11, 12, 7
    );
    b.benchmark_status();
    b.run_benchmark();
}