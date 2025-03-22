#include <functional>
#include <tuple>
#include <sstream>
#include <future>
#include <type_traits>
#include <iomanip>
#include "str.h"

namespace formulas {
    constexpr long long factorial(long long n) noexcept {
        if (n > 1) [[likely]]
            return n * factorial(n - 1);
        else [[unlikely]]
            return 1;
    }

    constexpr double pow(long double x, long long n) {
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

    constexpr double binomial(long double p, int n, int x) noexcept {
        return nCr(n, x) * formulas::pow(p, x) * formulas::pow((1 - p), (n - x));
    }
    constexpr double cos(double x) noexcept {
        constexpr long long precision{16LL};
        double y{};
        for (auto n{0LL}; n < precision; n += 2LL) [[likely]]
            y += formulas::pow(x, n) / (n & 2LL ? - formulas::factorial(n) : formulas::factorial(n));
        return y;
    }
}

template<typename Callable, typename... Args>
void Tasks(const std::string& name, Callable&& func, Args&&... args) noexcept {
    std::cout << name << std::endl;
    std::cout<< std::setprecision(53) <<"Result is : "<<func(std::forward<Args>(args)...)<<std::endl;;
}

template<typename Callable, typename... Args>
auto SafeTask(const std::string& name, Callable&& function, Args&&... args) {
    auto lambda = [name_copy = name, func = std::move(function), args_tuple = std::make_tuple(std::move(args)...)]() {
        std::apply([&](auto&&... unpacked_args) { 
            Tasks(name_copy, func, std::forward<decltype(unpacked_args)>(unpacked_args)...); 
        }, args_tuple);
    };
    return lambda;
}

template<typename Callable, typename... Args>
auto ExecFunc(const std::string& name, Callable&& callback, Args&&... args) 
{
    return std::apply([name, callable = std::forward<Callable>(callback)](auto&&... unpacked_args) { 
        Tasks(name, callable, std::forward<decltype(unpacked_args)>(unpacked_args)...); 
        return callable(std::forward<decltype(unpacked_args)>(unpacked_args)...);
    }, std::make_tuple(std::forward<Args>(args)...));
}

class BasicStr {
private:
    const char* value;
public:
    const char* operator+(const char* other) {
        size_t cls_len = strlen(value), new_len = cls_len + strlen(other);
        char* result_val;
        for (auto i{0}; i < new_len; i++) {
            result_val[i] = (i < cls_len) ? value[i] : other[cls_len - i];
        }
        return value;
    }
};

template<typename... Args>
auto sum(Args&&... args) {
    return (args + ...);
}

template<typename... Args>
void Print(Args&&... args) {
    // auto values = std::make_tuple(std::forward<Args>(args)...);
    auto values = std::make_tuple(std::forward<decltype(args)>(args)...);
    // auto values = std::make_tuple(std::move(args)...);

    std::apply([](auto&&... vals) {
        ((std::cout << vals << ", "), ...);
    }, values);
    std::cout << "\n";
}

template<typename... Args>
static double sq_sum(Args&&... args) {
    // auto values = std::make_tuple(std::forward<Args>(args)...);
    Print(std::forward<decltype(args)>(args)...);
    auto values = std::make_tuple(std::forward<decltype(args)>(args)...);
    // auto values = std::make_tuple(std::move(args)...);
    long double result = 0;
    std::apply([&result](auto&&... args) mutable {
        ((result = result + std::pow(args, 2)), ...);
    }, values);
    return result;
}

int main() {
    std::cout << "Generally used to have multiple parameters" << std::endl;
    try {
        Tasks("Binomial : 1/6, 12, 7", elements::binomial, 1.0/6, 12, 7);
        Tasks("Cos : 0.125", elements::cos, 0.125);
    } catch (...) {
        std::cout << "Chose the wrong function" << std::endl;
    }

    std::cout << "\nThese type of functions will be used in case of multithreading" << std::endl;
    try {
        SafeTask("Binomial : 1/6, 12, 7", elements::binomial, 1.0/6, 12, 7)();
        SafeTask("Cos : 0.125", elements::cos, 0.125)();
    } catch (...) {
        std::cout << "Chose the wrong function" << std::endl;
    }

    std::cout << "\nUsed in std::async functions" << std::endl;
    try {
        auto val1 = ExecFunc("Binomial : 1/6, 12, 7", elements::binomial, 1.0/6, 12, 7);
        auto val2 = ExecFunc("Cos : 0.125", elements::cos, 0.125);
    } catch (...) {
        std::cout << "Chose the wrong function" << std::endl;
    }

    std::cout << "\nSum of all the numbers : " << sum(1, 2, 3, 4, 5) << std::endl; 
    std::cout << "Sum of all the Strings : " << sum(
        String("Yoho"),
        "Toho",
        "kolo",
        String("Moho"),
        String("Fojo")
    ) << std::endl; 
    Print(1, " Gof", 6.54f, 'fjk3', 50'000LL);

    std::cout<<sq_sum(1, 2, 3, 4, 5)<<std::endl;;
}
