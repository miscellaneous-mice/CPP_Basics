#include <iostream>
#include <chrono>
#include <future>
#include <mutex>
#include <type_traits>
#include "../algebra.h"

using namespace std::literals::chrono_literals;

static std::mutex gLock;
std::condition_variable cv;
bool result;

template<typename Rep, typename Period, typename Callable, typename... Args>
std::future<std::invoke_result_t<std::decay_t<Callable>, std::decay_t<Args>...>>  Timer(std::chrono::duration<Rep, Period> duration, Callable&& callback, Args&&... args) 
{
    std::cout << "Timer Started" << std::endl;
    return std::async(std::launch::async, 
        [duration, func = std::forward<Callable>(callback), args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
            std::this_thread::sleep_for(duration);
            return std::apply(func, args);
        }
    );
}

int main() {
    auto future = Timer(10s, &elements::binomial, 1.0/6, 12, 7);
    while(true) {
        std::cout<<"Processing..."<<std::endl;
        std::this_thread::sleep_for(1ms);
        auto status = future.wait_for(1ms);
        if (status == std::future_status::ready) {
            break;
        }
    }
    std::cout<<future.get()<<std::endl;
    std::cout<<elements::binomial(1.0/6, 12, 7)<<std::endl;
}