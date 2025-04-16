#include <iostream>
#include <chrono>
#include <future>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <type_traits>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <mach/mach.h>
#include "../algebra.h"

using namespace std::literals::chrono_literals;

static std::mutex gLock;
std::condition_variable cv_gbl;
bool result;

template<typename Rep, typename Period, typename Callable, typename... Args>
std::future<std::invoke_result_t<std::decay_t<Callable>, std::decay_t<Args>...>>  Timer(std::chrono::duration<Rep, Period> duration, Callable&& callback, Args&&... args) 
{
    std::cout << "Timer Started" << std::endl;
    return std::async(std::launch::async, 
        [duration, func = std::forward<Callable>(callback), args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
            std::this_thread::sleep_for(duration);
            return std::apply(func, args);
        }
    );
}

[[nodiscard]] std::tuple<std::string, bool> SearchStr(const std::string& File, const std::string& word) {
    std::fstream MyFile;
    MyFile.open(File, std::ios::in);
    MyFile.clear();
    MyFile.seekg(0, std::ios::beg);
    try {
        if (!MyFile.is_open()) {
            std::cerr << "Error: Unable to open the file!" << std::endl;
            return std::make_tuple(word, false);
        }

        // Write to the file
        std::string line;
        while (std::getline(MyFile, line)) {
            if (line.compare(word) == 0){
                MyFile.close();
                return std::make_tuple(word, true);
            }
        }
        MyFile.close();
        return std::make_tuple(word, false);
    } catch (const std::exception& e) {
        MyFile.close();
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return std::make_tuple(word, false);
    }
}
    
class SearchWord {
public:
    explicit SearchWord(const std::string& File) : SearchFile(File), ready_to_search(false) {}

    void BeginSearch(std::fstream& MyFile, const std::string& word) {
        std::lock_guard<std::mutex> lck(mtx);
        pthread_setname_np(word.c_str());
        MyFile.open(SearchFile, std::ios::in);
        MyFile.clear();
        MyFile.seekg(0, std::ios::beg);
        word_status[word] = true;
        cv_ready.notify_one();
    }

    [[nodiscard]] std::pair<std::string, bool> SearchStr(std::fstream& File, const std::string& word) {
        std::pair<std::string, bool> result(word, false);
        try {
            if (File.is_open()) {
                std::string line;
                while (std::getline(File, line)) {
                    if (line == word) {
                        result.second = true;
                        break;
                    }
                }
            } else {
                std::cerr << "Error: File not open during search!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred while searching file: " << e.what() << std::endl;
        }
        return result;
    }

    std::pair<std::string, bool> MakeSearch(const std::string& word) {
        std::fstream file_to_search;
        BeginSearch(file_to_search, word);

        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [this] { return ready_to_search.load(); });
        lck.unlock();

        auto result = SearchStr(file_to_search, word);
        file_to_search.close();
        return result;
    }

    void AddSearch(const std::string& word) {
        futures.emplace_back(std::async(std::launch::async, [this, word]() {
            return this->MakeSearch(word);
        }));

        // Wait for the word search to start
        std::unique_lock<std::mutex> lck(mtx_ready);
        cv_ready.wait(lck, [this, word] {
            return word_status[word];
        });
    }

    void CheckStatus() {
        processes.emplace_back([&] () {
            task_threads(mach_task_self(), &threads, &thread_count);
            std::cout << "[Search] Number of searches still running: " << futures.size() << std::endl;

            for (int i = 1; i < thread_count; i++) {
                char thread_name[64];
                uint64_t tid;
                pthread_t pthread = pthread_from_mach_thread_np(threads[i]);
                pthread_getname_np(pthread, thread_name, sizeof(thread_name));
                pthread_threadid_np(pthread, &tid);
                if (word_status.find(thread_name) == word_status.end()) continue;
                std::cout << "[Search]   - Search for word: " << thread_name << " in thread id: " << tid << std::endl;
            }
        });
    }

    void RunSearch() {
        ready_to_search.store(true);
        cv.notify_all();

        std::pair<std::string, bool> results;
        while (futures.size() > 0) {
            for (size_t i = 0; i < futures.size(); i++) {
                auto status = futures[i].wait_for(std::chrono::milliseconds(10));
                if (status == std::future_status::ready) {
                    results = futures[i].get();
                    std::cout << "Word search complete...!!! : " << results.first
                                << " result : " << results.second << std::endl;
                    futures.erase(futures.begin() + i);
                }
            }
        }
    }

    ~SearchWord() {
        this->RunSearch();
        for (auto& process : processes) {
            if (process.joinable())
                process.join();
        }
    }

private:
    std::atomic<bool> ready_to_search;
    std::string SearchFile;
    std::unordered_map<std::string, bool> word_status;

    std::vector<std::future<std::pair<std::string, bool>>> futures;
    std::vector<std::thread> processes;

    std::condition_variable cv;
    std::mutex mtx;

    std::condition_variable cv_ready;
    std::mutex mtx_ready;

    thread_act_array_t threads;
    mach_msg_type_number_t thread_count;
};
    

template<typename... Tp>
std::ostream& operator<<(std::ostream& stream, const std::tuple<Tp...>& args) {
    stream << "(";
    std::apply([&stream](const auto&... elems) {
        ((stream << elems << ", "), ...);
    }, args);
    stream << ")"; // Removes last ", " and closes the tuple with ")"
    return stream;
}

int main() {
    auto future = Timer(3s, &elements::binomial, 1.0/6, 12, 7);
    while(true) {
        std::cout<<"Processing..."<<std::endl;
        std::this_thread::sleep_for(1ms);
        auto status = future.wait_for(1ms);
        if (status == std::future_status::ready) {
            break;
        }
    }
    std::cout<<"Async value : " << future.get()<< ", Original Value : " << elements::binomial(1.0/6, 12, 7) <<std::endl;

    std::string file = "words_alpha.txt";
    std::array<std::string, 5> words = {"sanity", "goatly", "megame", "scaredfrog", "goatee"};
    
    std::vector<std::future<std::tuple<std::string, bool>>> futures{};
    for (const auto& word : words) {
        futures.emplace_back(std::async(std::launch::async, [file, word]() {
            return SearchStr(file, word);
        }));
    }
    
    int ready = 0;
    size_t search_len = words.size();  // Use the array's size() method
    
    std::vector<bool> processed(search_len, false);  // Track which futures have been processed
    
    auto st = std::chrono::high_resolution_clock::now();
    while (ready < search_len) {
        for (size_t i = 0; i < futures.size(); i++) {
            if (processed[i]) continue;  // Skip already processed futures
            
            std::cout << "Searching..." << std::endl;
            auto status = futures[i].wait_for(std::chrono::milliseconds(1));  // Use proper namespace
            
            if (status == std::future_status::ready) {
                std::cout << "Text result : " << futures[i].get() << std::endl;
                processed[i] = true;  // Mark this future as processed
                ready += 1;
            }
        }
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - st);
    std::cout<<duration.count()<<" ms"<<std::endl;

    std::cout<<"\nUsing class to search words"<<std::endl;
    // std::unique_ptr<SearchWord> word_searcher = std::make_unique<SearchWord>(file);
    // word_searcher->AddSearch("sanity");
    // word_searcher->AddSearch("goatly");
    // word_searcher->AddSearch("megame");
    // word_searcher->CheckStatus();
    // word_searcher->RunSearch();

    // word_searcher->CheckStatus();
    // word_searcher->AddSearch("scaredfrog");
    // word_searcher->AddSearch("goatee");
    // word_searcher->CheckStatus();
    // word_searcher->RunSearch();
    // word_searcher->CheckStatus();

    SearchWord word_searcher = SearchWord(file);
    word_searcher.AddSearch("sanity");
    word_searcher.AddSearch("goatly");
    word_searcher.CheckStatus();
    word_searcher.RunSearch();
    
}