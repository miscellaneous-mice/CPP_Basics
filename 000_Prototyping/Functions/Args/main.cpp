#include <functional>
#include <tuple>
#include <sstream>
#include "str.h"

void binomial(double, int, int) {
    std::cout << "binomial(double, int, int)" << std::endl;
}

void binomial(double, int) {
    std::cout << "binomial(double, int)" << std::endl;
}

template<typename Callable, typename... Args>
void Tasks(const std::string& name, Callable&& func, Args&&... args) noexcept {
    std::cout << name << std::endl;
    func(std::forward<Args>(args)...);
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
    auto values = std::make_tuple(std::forward<decltype(args)>(args)...);
    // auto values = std::make_tuple(std::move(args)...);

    return std::apply([](auto&&... vals) {
        Print(std::forward<decltype(vals)>(vals)...);
        return std::pow((vals + ...), 2);
    }, values);
}

int main() {
    std::cout << "Generally used to have multiple parameters" << std::endl;
    try {
        Tasks("test-1", static_cast<void(*)(double, int, int)>(binomial), 1.0/6, 12, 7);
        Tasks("test-2", static_cast<void(*)(double, int)>(binomial), 1.0/6, 12);
    } catch (...) {
        std::cout << "Chose the wrong function" << std::endl;
    }

    std::cout << "\nThese type of functions will be used in case of multithreading" << std::endl;
    try {
        SafeTask("test-1", static_cast<void(*)(double, int, int)>(binomial), 1.0/6, 12, 7)();
        SafeTask("test-2", static_cast<void(*)(double, int)>(binomial), 1.0/6, 12)();
    } catch (...) {
        std::cout << "Chose the wrong function" << std::endl;
    }

    std::cout << "Sum of all the numbers : " << sum(1, 2, 3, 4, 5) << std::endl; 
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
