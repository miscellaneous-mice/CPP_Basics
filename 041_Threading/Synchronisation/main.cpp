#include <iostream>
#include <chrono>
#include <future>
#include <mutex>
#include <type_traits>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "../algebra.h"

using namespace std::literals::chrono_literals;

static std::mutex gLock;
std::condition_variable cv;
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

std::tuple<std::string, bool> SearchStr(const std::string& File, const std::string& word) {
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
            if (line.compare(word) == 0)
                return std::make_tuple(word, true);
        }
        return std::make_tuple(word, false);
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return std::make_tuple(word, false);
    }
}

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
    auto future = Timer(10s, &elements::binomial, 1.0/6, 12, 7);
    while(true) {
        std::cout<<"Processing..."<<std::endl;
        std::this_thread::sleep_for(1ms);
        auto status = future.wait_for(1ms);
        if (status == std::future_status::ready) {
            break;
        }
    }
    std::cout<<future.get()<<std::endl;
    std::cout<<elements::binomial(1.0/6, 12, 7)<<std::endl;

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
}