#include <condition_variable>
#include <string>
#include <pthread.h>
#include <thread>
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <mach/mach.h>

using namespace std::literals::chrono_literals;

long gen_random() noexcept
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0, 10.0);
    return static_cast<long>(dis(gen));
}

class Reporter {
public:
    Reporter() {
        task_threads(mach_task_self(), &threads, &thread_count);
        std::cout << "[Reporter] Reporter loaded. Found " << thread_count << " threads." << std::endl;
    }

    void report() {
        std::cout << "[Reporter] Reporting all threads:" << std::endl;
        for (int i = 0; i < thread_count; i++) {
            char thread_name[64];
            uint64_t tid;
            pthread_t pthread = pthread_from_mach_thread_np(threads[i]);
            pthread_getname_np(pthread, thread_name, sizeof(thread_name));
            pthread_threadid_np(pthread, &tid);
            std::cout << "[Reporter]   - thread " << i << " name: " 
                    << thread_name << " tid: " << tid << std::endl;
        }
    }

private:
    thread_act_array_t threads;
    mach_msg_type_number_t thread_count;
};

class Worker {
public:
    Worker(int16_t n) : num_workers(n), num_ready(0) { }

    void worker_thread(std::string thread_name) {

        // Thread preparation
        {
            std::lock_guard<std::mutex> lck(mtx);
            pthread_setname_np(thread_name.c_str());
            std::cout << "[Worker] Thread " << thread_name << " ready to run." << std::endl;
            num_ready++;
            cv_ready.notify_one();
        }

        // Suspend all threads until ready
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [this] {
            return num_ready == num_workers;
        });

        // Allow parallel execution of worker threads
        lck.unlock();

        // Execution of thread
        auto st = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(gen_random()));

        {
            std::lock_guard<std::mutex> lck(mtx);
            std::cout << "[Worker] Thread " << thread_name
            << " finished. Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - st).count() << std::endl;
        }
    }

    void create_workers() {
        std::string main_thread_name = "main";
        pthread_setname_np(main_thread_name.c_str());
        for (int i = 0; i < num_workers; i++) {
            std::string worker_name = "worker-" + std::to_string(i);
            m_threads.emplace_back(&Worker::worker_thread, this, worker_name);
        }

        // Wait for all threads to be loaded
        std::unique_lock<std::mutex> lck(mtx_ready);
        cv_ready.wait(lck, [this] {
            return num_ready == num_workers;
        });


    }

    void report() {
        std::unique_ptr<Reporter> reporter = std::make_unique<Reporter>();
        reporter->report();
    }

    void run() {
        // Notify all threads to start
        cv.notify_all();
        for (auto &t: m_threads) {
            t.join();
        }
    }

private:
    int16_t num_workers;
    int16_t num_ready;
    std::vector<std::thread> m_threads;

    std::condition_variable cv;
    std::mutex mtx;

    std::condition_variable cv_ready;
    std::mutex mtx_ready;
};

int main() {
    // Create threads
    std::unique_ptr<Worker> worker = std::make_unique<Worker>(5);
    worker->create_workers();

    // Do something before actual threads execution, after all threads are created and configured.
    worker->report();

    // Start all worker threads
    worker->run();
}