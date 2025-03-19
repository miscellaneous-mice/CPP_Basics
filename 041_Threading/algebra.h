#pragma once
namespace formulas {
    [[nodiscard]] constexpr long long factorial(long long n) noexcept {
        if (n > 1) [[likely]]
            return n * factorial(n - 1);
        else [[unlikely]]
            return 1;
    }

    [[nodiscard]] constexpr double pow(long double x, long long n) {
        if (n <= 1) [[unlikely]] {
            return x;
        } else [[likely]] {
            return x * pow(x, n - 1);
        }
    }
}

namespace elements {
    [[nodiscard]] constexpr double nCr(int n, int r) {
        return (formulas::factorial(n)) / 
               (formulas::factorial(n - r) * formulas::factorial(r));
    }

    [[nodiscard]] constexpr double binomial(long double p, int n, int x) noexcept {
        return nCr(n, x) * formulas::pow(p, x) * formulas::pow((1 - p), (n - x));
    }
    [[nodiscard]] constexpr double cos(double x) noexcept {
        constexpr long long precision{16LL};
        double y{};
        for (auto n{0LL}; n < precision; n += 2LL) [[likely]]
            y += formulas::pow(x, n) / (n & 2LL ? - formulas::factorial(n) : formulas::factorial(n));
        return y;
    }
}
