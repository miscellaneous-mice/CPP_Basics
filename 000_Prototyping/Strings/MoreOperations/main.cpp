#include <iostream>
#include <map>
#include <cctype> 

int main(){
    std::string input = "HoySoy";
    for (auto& c : input) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    std::cout<<"Converted to upper case : "<<input<<std::endl;

    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::cout<<"Converted to lower case : "<<input<<std::endl;

    std::string str ("Test string");
    for ( std::string::iterator it=str.begin(); it!=str.end(); ++it)
        std::cout << *it <<std::endl;
    std::cout<<"Converted to lower case : "<<input<<std::endl;

    std::map<std::string, std::string> StrMap;
    StrMap["Name"] = "Lowy";
    StrMap["Age"] = "18";
    StrMap["Sex"] = "Male";

    for(const auto& pair : StrMap){
        std::cout<<"Key : "<<pair.first<<", Value : "<<pair.second<<std::endl;
    }
}
