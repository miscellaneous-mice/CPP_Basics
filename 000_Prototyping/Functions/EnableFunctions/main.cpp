#include <iostream>
#include <type_traits> // For std::enable_if

// Function only enabled for integers
template <typename T>
typename std::enable_if<std::is_integral<T>::value, int>::type print(T value) {
    std::cout << "Integer: ";
    return value;
}

// Function only enabled for floating-point numbers
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, float>::type print(T value) {
    std::cout << "Floating-point: ";
    return value;
}

// Function only enabled for floating-point numbers
template <typename E, typename... Args>
typename std::enable_if<std::is_same_v<E, typename std::common_type<Args...>::type>, void>::type type_check_print(Args&&... args) {
    ((std::cout<<args<<", "), ...);
    std::cout<<std::endl;
}

template <typename E, typename... Args>
typename std::enable_if<std::is_convertible_v<E, std::common_type_t<Args...>>, void>::type print_everytime(Args&&... args) {
    ((std::cout << args << ", "), ...);
    std::cout << std::endl;
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type Print_tuple(std::tuple<Tp...>& t) {
    std::cout<<std::endl;
} // Does nothing, hence breaks the recusion

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type Print_tuple(std::tuple<Tp...>& t) {
    std::cout << std::get<I>(t) << ", ";
    Print_tuple<I + 1, Tp...>(t);
}

template<typename T1, typename T2>
typename std::common_type<T1, T2>::type div(T1 a, T2 b) {
    return static_cast<typename std::common_type<T1, T2>::type>(b / a);
}

template<typename ExpectedReturnType = void, typename Callable, typename... Args>
typename std::enable_if<std::is_same_v<ExpectedReturnType, std::invoke_result_t<std::decay_t<Callable>, std::decay_t<Args>...>>, ExpectedReturnType>::type Execute(Callable&& callable, Args&&... args) {
    return std::forward<Callable>(callable)(std::forward<Args>(args)...);
}

int main() {
    std::cout<<"Basic Example : "<<std::endl;
    std::cout<<print(42)<<std::endl; // Calls the integer version
    std::cout<<print(3.14)<<std::endl; // Calls the floating-point version
    // print("hello"); // Compilation error (string is neither integer nor float)

    std::cout<<"\nCheck the Type before printing : "<<std::endl;
    type_check_print<float, float, int, int>(3.14, 2, 5);
    type_check_print<double, float, int, int, double>(3.14, 2, 5, 553);
    // type_check_print<int, float, int, int, double>(3.14, 2, 5, 553); // Error

    std::cout<<"\nPrint no matter the type : "<<std::endl;
    print_everytime<int, float, int, int>(3.14, 2, 5);
    print_everytime<float, float, int, int, double>(3.14, 2, 5, 553);

    std::cout<<"\nRecursive printing of tuple : "<<std::endl;
    auto tp = std::make_tuple(1.25f, 5.33, 43L, 3, "Hello");
    Print_tuple(tp);

    std::cout<<"\nExecuting the function and verify the type : "<<std::endl;
    std::cout<<Execute<float>(&div<float, int>, 5.04f, 44)<<std::endl;
    std::cout<<Execute<long>(&div<long, int>, 5L, 53)<<std::endl;
    // std::cout<<Execute<long>(&div<long, int>, 5L, 53)<<std::endl; // Error
}
