#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <map>

enum class TUnit {
    SECOND, MINUTE, HOUR
};

namespace literals {
    template<typename T, typename N>
    constexpr std::chrono::duration<double> time(T value, N multiplier) {
        return std::chrono::duration<double>(static_cast<double>(value) * multiplier);
    }

    template<TUnit Unit>
    constexpr std::chrono::duration<double> TMap(const std::variant<long double, unsigned long long>& seconds) {
        return std::visit([](auto&& value) {
            if constexpr (Unit == TUnit::SECOND) {
                return time(value, 1.0);
            } else if constexpr (Unit == TUnit::MINUTE) {
                return time(value, 60.0);
            } else if constexpr (Unit == TUnit::HOUR) {
                return time(value, 3600.0);
            }
        }, seconds);
    }

    class jthread {
    private:
        std::thread t;
    public:
        template<typename Callable, typename... Args>
        jthread(Callable&& func, Args&&... args) : 
            t(std::forward<Callable>(func), std::forward<Args>(args)...) {}
        
        ~jthread() {
            if (t.joinable()) {
                t.join();
            }
        }
        
        jthread(const jthread&) = delete;
        jthread& operator=(const jthread&) = delete;
        
        jthread(jthread&& other) noexcept : t(std::move(other.t)) {}
        jthread& operator=(jthread&& other) noexcept {
            if (t.joinable()) {
                t.join();
            }
            t = std::move(other.t);
            return *this;
        }
        
        std::thread& get() { return t; }
        const std::thread& get() const { return t; }
        
        bool joinable() const noexcept { return t.joinable(); }
        void join() { t.join(); }
        void detach() { t.detach(); }
    };
};



double gen_random() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(1.0, 10.0);
    return dis(gen);
}

int main() {
    using namespace literals;
    auto start = std::chrono::steady_clock::now();
    std::vector<jthread> jthreads;
    std::function<void(int, int)> mExec = [=](int x, int delay) {
        std::cout<<"[Sub] : " << std::this_thread::get_id() << " Started" << std::endl;
        std::this_thread::sleep_for(delay * TMap<TUnit::SECOND>(1.0));
        std::cout<<"Parameter Passed : "<<x<<std::endl;
        std::cout<<"[Sub] : " << std::this_thread::get_id() << " Finished" << std::endl;
    };
    for (int i = 0; i <= 10; ++i) {
        jthreads.emplace_back(mExec, i, gen_random());
    }

    std::cout<<"[Main] : Processing threads"<<std::endl;

    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start);
    std::cout<<"Execution completed : " << elapsed_time.count()<<std::endl;

}