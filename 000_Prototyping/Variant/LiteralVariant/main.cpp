#include <iostream>
#include <variant>

struct Helper;

template<typename T>
class ComplexLiterals {
public:
    ComplexLiterals() : i(0), r(0) {};
    ComplexLiterals(T i) : i(i), r(0) {};
    ComplexLiterals(T r, T i) : i(i), r(r) {};
    
    ComplexLiterals operator+(int value) const {
        return ComplexLiterals(this->r + value,  this->i);
    }
    
    ComplexLiterals operator+(double value) const {
        return ComplexLiterals(this->r + value,  this->i);
    }
private:
    T r, i;
    friend struct Helper;
};

namespace complex_literals {
    ComplexLiterals<double> operator"" i(long double value) {
        return ComplexLiterals<double>(value);
    }
    
    ComplexLiterals<int> operator"" i(unsigned long long value) {
        return ComplexLiterals<int>(value);
    }
}


template<typename T>
auto operator+(std::variant<int, double> value, const ComplexLiterals<T>& cmpl_no) {
    return std::visit([cmpl_no](auto&& e) {
        auto result = cmpl_no + e;
        return result;
    }, value);
}

struct Helper {
private:
    Helper() = default;
public:
    template<typename T>
    static T real(const ComplexLiterals<T>& cmpl_no) {
        return cmpl_no.r;
    }
    template<typename T>
    static T img(const ComplexLiterals<T>& cmpl_no) {
        return cmpl_no.i;
    }
    template<typename T>
    static void Print(const ComplexLiterals<T>& cmpl_no) {
        std::cout<<cmpl_no.r<<" + "<<cmpl_no.i<<"i"<<std::endl;
    }
};

template<typename T, typename U>
auto operator+(const ComplexLiterals<T>& first, const ComplexLiterals<U>& second) {
    using ResultType = typename std::common_type<T, U>::type;
    auto real = Helper::real(first) + Helper::real(second);
    auto imag = Helper::img(first) + Helper::img(second);
    return ComplexLiterals<ResultType>(real, imag);
}


int main() {
    using namespace complex_literals;
    auto cmpl_no = 1 + 2i;
    auto cmpl_no2 = 2 + 4.5i;
    Helper::Print(cmpl_no);
    Helper::Print(cmpl_no2);
    Helper::Print(cmpl_no + cmpl_no2);
    return 0;
}