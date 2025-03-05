#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::literals::chrono_literals;

class Timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::duration<float> duration;
    Timer() : start(std::chrono::high_resolution_clock::now()) {};
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout<<"Time elapsed : "<<duration.count() * 1000 << "ms" <<std::endl;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::chrono::duration<T>& duration) {
    stream<<duration.count();
    return stream;
}

void Process(long long seconds) {
    Timer timer;
    std::this_thread::sleep_for(std::chrono::milliseconds(seconds));
}

int main(){
    auto begin = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<float> elapsed = end - begin;

    std::cout<<"Time Elapsed : "<< elapsed <<"s"<<std::endl;

    std::vector<std::thread> workers;
    workers.emplace_back(&Process, 500);
    workers.emplace_back(std::bind(&Process, 1000));

    for (auto& worker : workers) {
        worker.join();
    }

    // 20 second timer
    auto start_time = std::chrono::high_resolution_clock::now();
    while(true) {
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time) >= 5s){
            break;
        }
        std::cout<<"Processing...\n";
        std::this_thread::sleep_for(5ms);
    }
    auto end_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
    std::cout<<"Timer finished. Elapsed time : "<<end_time.count()<<std::endl;

    std::thread thread_timer(std::bind([](std::chrono::seconds secs){
        std::this_thread::sleep_for(secs);
        std::cout<<"Timer finished scheduled for : "<<secs.count()<<"s on thread : "<<std::this_thread::get_id()<<std::endl;
    }, 5s));
    std::cout<<"Processing other stuffs "<<std::endl;
    thread_timer.join();
}