#include <iostream>
#include <chrono>
#include <thread>

namespace time_literals {
    constexpr std::chrono::duration<double> operator"" ms(long double seconds) {
        return std::chrono::duration<double>(static_cast<double>(seconds) / 1000);
    }

    constexpr std::chrono::duration<double> operator"" s(long double seconds) {
        return std::chrono::duration<double>(static_cast<double>(seconds));
    }

    constexpr std::chrono::duration<double> operator"" min(long double seconds) {
        return std::chrono::duration<double>(static_cast<double>(seconds * 60));
    }

    constexpr std::chrono::duration<double> operator"" hr(long double seconds) {
        return std::chrono::duration<double>(static_cast<double>(seconds * 3600));
    }


    constexpr std::chrono::duration<int> operator"" ms(unsigned long long seconds) {
        return std::chrono::duration<int>(static_cast<int>(seconds) / 1000);
    }

    constexpr std::chrono::duration<int> operator"" s(unsigned long long seconds) {
        return std::chrono::duration<int>(static_cast<int>(seconds));
    }

    constexpr std::chrono::duration<int> operator"" min(unsigned long long seconds) {
        return std::chrono::duration<int>(static_cast<int>(seconds * 60));
    }

    constexpr std::chrono::duration<int> operator"" hr(unsigned long long seconds) {
        return std::chrono::duration<int>(static_cast<int>(seconds * 3600));
    }
}

template<typename T>
std::chrono::duration<T> operator*(T num, const std::chrono::duration<T>& val) {
    return std::chrono::duration<T>(num * val.count());
}

template<typename T>
std::chrono::duration<T> operator*(const std::chrono::duration<T>& val, T num) {
    return std::chrono::duration<T>(num * val.count());
}

int main(){
    using namespace time_literals;
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(1min);
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start);
    std::cout<<duration.count()<<std::endl;
}
