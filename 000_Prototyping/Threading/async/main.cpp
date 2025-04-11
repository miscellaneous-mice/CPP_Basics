#include <iostream>
#include <future>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <cmath>
#include <utility>
#include <tuple>
#include <array>

using namespace std::literals::chrono_literals;

std::atomic<bool> ready = false;
std::mutex mtx;
std::condition_variable cv;

template<typename T, std::size_t N, std::size_t... I>
auto array_to_tuple_impl(const std::array<T, N>& arr, std::index_sequence<I...>) {
    return std::make_tuple(arr[I]...);
}

template<std::size_t N>
constexpr auto arange() {
    std::array<int, N> arr;
    for(size_t i = 0; i < N; i++)
        arr[i] = i;
    return array_to_tuple_impl(arr, std::make_index_sequence<N>{});
}

template<int exponential, typename... Args>
typename std::common_type<std::decay_t<Args>...>::type exp_sum(Args&&... args) {
    using ResultType = typename std::common_type<std::decay_t<Args>...>::type;
    ResultType sum = 0;
    ((sum += std::pow(args, exponential)), ...);
    return sum;
}

template<int... exponentials, typename... Args>
std::vector<typename std::common_type<std::decay_t<Args>...>::type> ConditionalSum(Args&&... args) {
    using ResultType = typename std::common_type<std::decay_t<Args>...>::type;
    std::vector<ResultType> values(
        {
            exp_sum<exponentials>(std::forward<Args>(args)...)...
        }
    );
    return values;
}

template<int... exponentials, typename... Args>
std::vector<std::future<typename std::common_type<std::decay_t<Args>...>::type>> AsyncConditionalSum(Args&&... Arguments) {
    using ResultType = typename std::common_type<std::decay_t<Args>...>::type;
    std::vector<std::future<ResultType>> futures;

    // Lambda template that captures each exponential at compile-time
    auto launch = [&](auto Exp) {
        constexpr int exp = Exp;
        futures.push_back(std::async(std::launch::async, [&, exp] {
            std::unique_lock<std::mutex> lock(mtx);
            auto result = exp_sum<exp>(std::forward<Args>(Arguments)...);
            cv.wait(lock, [] { return ready.load(); });
            return result;
        }));
    };

    // Fold over parameter pack
    (launch(std::integral_constant<int, exponentials + 1>{}), ...);

    return futures;
}

template<typename... Args, std::size_t... Exps>
constexpr auto compute(std::index_sequence<Exps...>, Args&&... args) {
    return AsyncConditionalSum<Exps...>(std::forward<Args>(args)...);
}

int main() {
    constexpr size_t arg_range = 5;
    constexpr size_t exp_range = 3;
    // constexpr size_t range = 10000; // Uncomment if you want to crash your PC

    auto check_sum = [](std::vector<bool> vec) {
        int sum = 0;
        for(const bool& val : vec)
            sum += val;
        return sum;
    };

    auto futures = std::apply([] (auto&&... args) {
        return compute(std::make_index_sequence<exp_range>{}, std::forward<decltype(args)>(args)...);
    }, arange<arg_range>());

    std::vector<bool> processed(exp_range, false);
    auto start_time = std::chrono::high_resolution_clock::now();
    while (check_sum(processed) < exp_range) {
        cv.notify_all();
        std::cout<<"Processing..."<<std::endl; 
        for (size_t i = 0; i < futures.size(); ++i) {
            if (processed[i]) continue;
            auto status = futures[i].wait_for(std::chrono::milliseconds(10));
            if (status == std::future_status::ready) {
                std::cout << "Result: " << futures[i].get() << std::endl;
                processed[i] = true;
            }
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() >= 5)
            ready.store(true);
    }
    return 0;
}