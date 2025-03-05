#include <thread>
#include <iostream>

using namespace std::literals::chrono_literals;
static bool cond = false;

void keepBusy() {
    std::cout<<"The thread id of the current process : "<<std::this_thread::get_id()<<std::endl;

    while (!cond) {
        std::cout<<"Working..."<<std::endl;
        std::this_thread::sleep_for(1s);
    }
}

void ProcessData() {
    std::cout<<"The thread id of the current process : "<<std::this_thread::get_id()<<std::endl;

    while (!cond) {
        std::cout<<"Processing..."<<std::endl;
        std::this_thread::sleep_for(0.5s);
    }
}

int main() {
    std::vector<std::thread> workers;
    workers.emplace_back(keepBusy);
    workers.emplace_back(ProcessData);
    std::this_thread::sleep_for(5s);
    cond = true;

    for(auto& worker: workers) {
        worker.join();
    }
    std::cout<<"Finished."<<std::endl;
}