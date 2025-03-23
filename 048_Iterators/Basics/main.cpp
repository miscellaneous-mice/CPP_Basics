#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::vector<int> values {1, 2, 3, 4, 5};
    for (int i = 0; i < values.size(); i++){
        std::cout<<values[i]<<", ";
    }
    std::cout<<std::endl;

    for (auto& val : values) {
        std::cout<<val<<", ";
    }
    std::cout<<std::endl;

    for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        std::cout<<*it<<", ";
    }
    std::cout<<std::endl;

    std::unordered_map<std::string, uint32_t> langs;
    langs["C"] = 1972;
    langs["C++"] = 1985;
    langs["Java"] = 1995;
    langs["Python"] = 1991;
    langs["Ruby"] = 1995;
    langs["C#"] = 2000;
    langs["JavaScript"] = 1995;
    langs["Zig"] = 2016;
    langs["Rust"] = 2010;
    langs["Go"] = 2009;

    using LangIterator = typename decltype(langs)::const_iterator;
    for (LangIterator it = langs.begin(); it != langs.end(); it++){
        std::cout<<it->first<<" = "<<it->second<<", ";
    }
    std::cout<<std::endl;

    for (const auto& [lang, prog] : langs){
        std::cout<<lang<<" = "<<prog<<", ";
    }
    std::cout<<std::endl;



}