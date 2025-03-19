#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

static int num_threads = 5;
static std::mutex mtx;
static std::condition_variable cv;
static bool ready = false;

void print_id (int id) {
    std::unique_lock<std::mutex> lck(mtx);
    std::cout<<"Thread : "<<id<<" Waiting for Execution..."<<std::endl;
    // cv.wait(lck, [&id] {
    //     std::cout<<"Thread : "<<id<<" is sleeping"<<std::endl;
    //     return ready;
    // });
    while (!ready) {
        std::cout<<"Thread : "<<id<<" is sleeping"<<std::endl;
        cv.wait(lck);
    }
    std::cout << "thread " << id << '\n';
}

void go() {
    std::lock_guard<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main ()
{
    using namespace std::literals::chrono_literals;
    std::thread threads[num_threads];
    // spawn 10 threads:
    for (int i=0; i<num_threads; ++i) {
        threads[i] = std::thread(std::bind(&print_id,i));
    }

    std::cout << "5 threads ready to race...\n";
    std::this_thread::sleep_for(2s);
    go();

    for (auto& th : threads){
        std::cout<<"Closed thread"<<std::endl;
        th.join();
    }

    return 0;
}