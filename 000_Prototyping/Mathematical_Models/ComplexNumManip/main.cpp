#include <iostream>
#include <tuple>
#include <ranges>

template<typename T>
class ComplexNumber {
private:
    T r, i;
public:
    ComplexNumber() : r(0), i(0) {};

    constexpr ComplexNumber(T real) : r(real), i(0) {};

    constexpr ComplexNumber(T r, T i) : r(r), i(i) {};

    template<typename U>
    constexpr ComplexNumber(U r, U i) : r(static_cast<T>(r)), i(static_cast<T>(i)) {};

    template<typename U>
    constexpr ComplexNumber(const ComplexNumber<U>& cmpl_no): r(static_cast<T>(cmpl_no.r)), i(static_cast<T>(cmpl_no.i)) {};

    template<typename U>
    ComplexNumber operator+(U r) const {
        return ComplexNumber(this->r + static_cast<T>(r), this->i);
    }

    template<typename U>
    auto operator+(const ComplexNumber<U>& cmpl_no) const {
        using ResultType = typename std::common_type<T, U>::type;
        return ComplexNumber(
            static_cast<ResultType>(this->r) + static_cast<ResultType>(cmpl_no.r),
            static_cast<ResultType>(this->i) + static_cast<ResultType>(cmpl_no.i)
        );
    }
    T real() const {
        return r;
    }
    T imag() const {
        return i;
    }
};

template<typename T, typename U>
auto operator+(U real, const ComplexNumber<T>& cmpl_no) {
    using ResultType = typename std::common_type<T, U>::type;
    return ComplexNumber<ResultType>(
        static_cast<ResultType>(real) + static_cast<ResultType>(cmpl_no.real()),
        static_cast<ResultType>(cmpl_no.imag())
    );
}

namespace complex_literals {
    constexpr ComplexNumber<double> operator"" i(long double im) {
        return ComplexNumber<double>(0, im);
    }
    constexpr ComplexNumber<int> operator"" i(unsigned long long im) {
        return ComplexNumber<int>(0, static_cast<int>(im));
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const ComplexNumber<T>& complex_no){
    stream<<complex_no.real()<<" + "<<complex_no.imag()<<"i";
    return stream;
}


int main() {
    using namespace complex_literals;
    auto value = 1.0 + 3i;
    std::cout << value << std::endl;

    const auto zz = {0.0 + 1.0i, 2.0 + 3.1i, 4.0 + 5.7i};

    for (auto [no, re, im] : zz | std::views::transform([](auto z){ return std::make_tuple(z, z.real(), z.imag()); }))
        std::cout << no << " -> " << re << "::" <<im<<'\n';

    return 0;
}
