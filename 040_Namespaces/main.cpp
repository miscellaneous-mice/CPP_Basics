#include <iostream>
#include <map>
#include <sstream>
#include <any>
#include <tuple>
#include <array>

#define str_concat(stream, a, b, oper) (stream<<a<<" "<<oper<<" "<<b<<" = ")

namespace data {
    void info() {
        std::cout<<"Data storage namespace"<<std::endl;
    }
    enum class operations {
        ADD=0, SUBTRACT, MULTIPLY, DIVIDE
    };
    template<typename T>
    struct Number {
        T n;
    };
    constexpr std::array<operations, 128> op_symbol() {
        std::array<operations, 128> op_sym = {};
        op_sym['+'] = operations::ADD;
        op_sym['-'] = operations::SUBTRACT;
        op_sym['*'] = operations::MULTIPLY;
        op_sym['/'] = operations::DIVIDE;
        return op_sym;
    }

    static std::stringstream op_desc;

    template<typename T>
    std::map<operations, std::function<std::tuple<std::string, float>(std::any, std::any)>> op_map = {
        {operations::ADD, [](std::any a, std::any b) -> std::tuple<std::string, float> {
            op_desc.str("");
            T a_val = std::any_cast<T>(a), b_val = std::any_cast<T>(b);
            str_concat(op_desc, a_val, b_val, "+");
            return std::make_tuple(op_desc.str(), static_cast<float>(a_val + b_val));
        }},
        {operations::SUBTRACT, [](std::any a, std::any b) -> std::tuple<std::string, float> {
            op_desc.str("");
            T a_val = std::any_cast<T>(a), b_val = std::any_cast<T>(b);
            str_concat(op_desc, a_val, b_val, "-");
            return std::make_tuple(op_desc.str(), static_cast<float>(std::any_cast<T>(a) - std::any_cast<T>(b)));
        }},
        {operations::MULTIPLY, [](std::any a, std::any b) -> std::tuple<std::string, float> {
            op_desc.str("");
            T a_val = std::any_cast<T>(a), b_val = std::any_cast<T>(b);
            str_concat(op_desc, a_val, b_val, "*");
            return std::make_tuple(op_desc.str(), static_cast<float>(std::any_cast<T>(a) * std::any_cast<T>(b)));
        }},
        {operations::DIVIDE, [](std::any a, std::any b) -> std::tuple<std::string, float> {
            op_desc.str("");
            T a_val = std::any_cast<T>(a), b_val = std::any_cast<T>(b);
            str_concat(op_desc, a_val, b_val, "/");
            if (b_val == 0) {
                throw std::invalid_argument("Division by zero");
            }
            return std::make_tuple(op_desc.str(), static_cast<float>(std::any_cast<T>(a) / b_val));
        }}
    };
}

namespace manipulate {
    void info() {
        std::cout<<"Data Manipulation namespace"<<std::endl;
    }
    using ops = typename data::operations;
    using data::op_symbol;

    constexpr std::array<ops, 128> op_sym = op_symbol();
    
    namespace functions {
        template<typename T, typename U>
        float operator+(const data::Number<T>& lhs, const data::Number<U>& rhs){
            using ResultType = typename std::common_type<T, U>::type;
            auto [how, value] = data::op_map<ResultType>[op_sym['+']](static_cast<ResultType>(lhs.n), static_cast<ResultType>(rhs.n));
            std::cout<<how;
            return value;
        }

        template<typename T, typename U>
        float operator-(const data::Number<T>& lhs, const data::Number<U>& rhs){
            using ResultType = typename std::common_type<T, U>::type;
            auto [how, value] = data::op_map<ResultType>[op_sym['-']](static_cast<ResultType>(lhs.n), static_cast<ResultType>(rhs.n));
            std::cout<<how;
            return value;
        }

        template<typename T, typename U>
        float operator*(const data::Number<T>& lhs, const data::Number<U>& rhs){
            using ResultType = typename std::common_type<T, U>::type;
            auto [how, value] = data::op_map<ResultType>[op_sym['*']](static_cast<ResultType>(lhs.n), static_cast<ResultType>(rhs.n));
            std::cout<<how;
            return value;
        }

        template<typename T, typename U>
        float operator/(const data::Number<T>& lhs, const data::Number<U>& rhs){
            using ResultType = typename std::common_type<T, U>::type;
            auto [how, value] = data::op_map<ResultType>[op_sym['/']](static_cast<ResultType>(lhs.n), static_cast<ResultType>(rhs.n));
            std::cout<<how;
            return value;
        }
    };
};



int main() {
    data::info();
    manipulate::info();

    data::Number<int> a = {10};
    data::Number<float> b = {6.384f};

    using namespace manipulate::functions;

    std::cout<<a + b<<std::endl;
    std::cout<<a - b<<std::endl;
    std::cout<<a * b<<std::endl;
    std::cout<<a / b<<std::endl;

}


/*
Namespaces are usually used to resolve the naming the conventions in c++/
Like having 2 versions of a same function with same function name inside different namespaces
*/