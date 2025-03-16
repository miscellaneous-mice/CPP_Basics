#include <iostream>
#include <any>

template<typename T, typename N>
auto sum2nums(T a, N b) {
    using resulttype = typename std::common_type<T, N>::type;
    auto result = static_cast<resulttype>(a) + static_cast<resulttype>(b);
    return result;
}

template <typename T>
void print (const T& arg) {
    std::cout<<arg<<std::endl;
}

template <typename T, typename... Types>
void print (const T& firstArg, const Types&... args) {
    std::cout << firstArg << ", ";
    print(args...);
}

template<typename... Args>
constexpr auto TotalSum(Args&&... args) {
    print(std::forward<Args>(args)...);
    using resulttype = std::common_type<std::decay_t<Args>...>::type;
    auto values = std::make_tuple(std::forward<Args>(args)...);
    resulttype result = 0;
    std::apply([&result](auto&&... args) mutable {
        ((result = result + static_cast<resulttype>(args)), ...);
    }, values);
    return result;
}

int main() {
    auto a = 1.54f;
    auto b = 3;
    using ReturnType = typename std::invoke_result_t<decltype(sum2nums<decltype(a), decltype(b)>), decltype(a), decltype(b)>;
    std::any value = sum2nums(1.54f, 3);
    std::cout<<std::any_cast<ReturnType>(value)<<std::endl;

    std::tuple args{1.54f, 3, 23L, 0.334};
    auto total_sum = std::apply([args](auto&&... values) {
        return TotalSum(std::forward<decltype(values)>(values)...);
    }, args);
    std::cout<<total_sum<<std::endl;
}