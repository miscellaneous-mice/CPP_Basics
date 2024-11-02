#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    std::string input = "Name::Level::Date";
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::string target1 = "name";
    std::string target2 = "date";
    std::string target3 = "level";

    // Replace "name" with "LOGGER"
    std::cout<<input<<std::endl;
    size_t pos = input.find(target1);
    if (pos != std::string::npos) {
        input.replace(pos, target1.length(), "LOGGER");
    }

    // Replace "date" with "17-06-2024"
    pos = input.find(target2);
    if (pos != std::string::npos) {
        input.replace(pos, target2.length(), "17-06-2024");
    }

    // Replace "level" with "INFO"
    pos = input.find(target3);
    if (pos != std::string::npos) {
        input.replace(pos, target3.length(), "INFO");
    }

    std::cout << "Replaced string: " << input << std::endl;

    std::string str = "She sells sea Shells on the sea sHore. But the sea had not sea shells on it";
    std::vector<std::string> sub_str = {"on", "sea", "she"};
    std::cout<<"Finding all the occurences of the letter 'o' in : "<<str<<std::endl;

    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){
        return std::tolower(c);
    });

    std::vector<size_t> positions; // holds all the positions that sub occurs within str

    size_t loc = 0;
    std::string result = str;
    for (const std::string& sub : sub_str) {
        loc = str.find(sub, 0);
        while (loc != std::string::npos) {
            positions.push_back(loc);
            result.replace(loc, sub.length(), std::string(sub.length(), '*'));
            std::cout << "Found bad word occurrence: " << sub << " at position " << loc << std::endl;
            loc = str.find(sub, loc + sub.length());
        }
    }
    std::cout<<"The final string is : "<<result<<std::endl;
    return 0;
}
