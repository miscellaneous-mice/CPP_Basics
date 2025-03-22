#include <iostream>
#include <variant>
#include <string>

void binomial(double, int, int) {
    std::cout << "binomial(double, int, int)" << std::endl;
}

void binomial(double, int) {
    std::cout << "binomial(double, int)" << std::endl;
}

void foo(const std::string& message) {
    std::cout << "std::string -> " << message << std::endl;
}

void foo(const char* message) {
    std::cout << "const char* -> " << message << std::endl;
}

template<typename Callable>
void callFunction1(Callable&& func, std::variant<std::string, const char*> param) noexcept {
    std::visit([&func](auto&& arg) {
        func(std::forward<decltype(arg)>(arg));
    }, param);
}


template<typename Callable, typename T>
void callFunction2(Callable&& func, T param) noexcept {
    std::visit([&func](const auto&& arg) {
        func(std::forward<T>(arg));
    }, param);
}

template<typename Callable, typename... Args>
void pass_params(Callable&& func, Args&&... args) {
    
}

int main() {
    callFunction1(static_cast<void(*)(const std::string&)>(&foo), std::string("Value"));
    callFunction1(static_cast<void(*)(const char*)>(&foo), "Value");

    callFunction2(static_cast<void(*)(const std::string&)>(&foo), std::string("Value"));
    callFunction2(static_cast<void(*)(const char*)>(&foo), "Value");
}
