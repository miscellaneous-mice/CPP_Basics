#include <iostream>
#include <tuple>
#include <type_traits>
#include <iomanip>

template <typename T>
void print (const T& arg) {
    std::cout<<arg<<std::endl;
}

template <typename T, typename... Types>
void print (const T& firstArg, const Types&... args) {
    std::cout << firstArg << ", ";
    print(args...);
}

template<typename... Tp>
[[nodiscard]] constexpr std::tuple<std::decay_t<Tp>...> RetFunc(Tp&&... elements) {
    print(std::forward<Tp>(elements)...);
    return std::make_tuple(std::forward<Tp>(elements * elements)...);
}

template<typename... Tp>
[[nodiscard]] constexpr auto RetFuncPair(Tp&&... elements) {
    using CommonType = typename std::common_type<std::decay_t<Tp>...>::type;
    return std::array<std::pair<CommonType, CommonType>, sizeof...(Tp)>{ 
        std::pair(static_cast<CommonType>(elements), static_cast<CommonType>(elements * elements))...
    };
}

template<typename... Args>
typename std::common_type<std::decay_t<Args>...>::type sum(Args&&... args) {
    using ResultType = typename std::common_type<std::decay_t<Args>...>::type;
    ResultType sum = 0;
    ((sum += args), ...);
    return sum;
}

template<typename ExpectedReturnType = void, int exponential = 1, typename Callable, typename... Args>
typename std::enable_if<std::is_same_v<ExpectedReturnType, std::invoke_result_t<std::decay_t<Callable>, std::decay_t<Args>...>>, ExpectedReturnType>::type ExponentialSum(Callable&& callable, Args&&... args) {
    std::cout<<"Calling sum function with exponential : " <<exponential<<", Parameters : ";
    ((std::cout<< args << "->" << typeid(args).name() <<" "), ...);
    std::cout<<std::endl;
    return std::apply([function = std::forward<Callable>(callable)](auto&&... e) {
        return function(std::forward<decltype(e)>(e)...);
    }, std::make_tuple(std::pow(args, exponential)...));
}

template<typename ExpectedReturnType, int... Exponentials, typename... Args>
[[nodiscard]] constexpr auto CollectiveSum(Args&&... args) {
    using Callable = decltype(&sum<Args&&...>);
    auto function = std::forward<Callable>(&sum<Args&&...>);
    return std::make_tuple(
        ExponentialSum<ExpectedReturnType, Exponentials>((Callable&&)function, std::forward<Args>(args)...)...
    );
}


int main() {
    auto&& [a, b, c, d, e] = RetFunc(1, 2.74f, 3.33, 4L, 50034);
    std::cout<<a<<", "<<b<<", "<<c<<", "<<d<<", "<<e<<std::endl;

    auto&& result = RetFuncPair(1, 2.74f, 3.33, 4L, 50034);
    for(auto& [a, b]: result){
        std::cout<<std::setprecision(10)<<"("<<a << ", "<<b<<")"<<", ";
    }
    std::cout<<std::endl;

    // auto result_1 = ExponentialSum<double>(&sum<int, int, long, double, float>, 1, 2, 5L, 4.534, 3.54f);
    // auto result_2 = ExponentialSum<double, 2>(&sum<int, int, long, double, float>, 1, 2, 5L, 4.534, 3.54f);
    // auto result_3 = ExponentialSum<double, 3>(&sum<int, int, long, double, float>, 1, 2, 5L, 4.534, 3.54f);
    // std::cout<<result_1<<std::endl;
    // std::cout<<result_2<<std::endl;
    // std::cout<<result_3<<std::endl;

    auto [result_7, result_8, result_9, result_10] = CollectiveSum<double, 1, 2, 3, 4>(1, 2, 5L, 4.534, 3.54f);
    std::cout<<result_7<<std::endl;
    std::cout<<result_8<<std::endl;
    std::cout<<result_9<<std::endl;
    std::cout<<result_10<<std::endl;
    return 0;
}