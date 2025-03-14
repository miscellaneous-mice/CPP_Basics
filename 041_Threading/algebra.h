namespace formulas {
    constexpr long long factorial(int n) {
        if (n <= 1) [[unlikely]] {
            return n;
        } else [[likely]] {
            return n * factorial(n - 1);
        }
    }

    constexpr double pow(long double x, int n) {
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
