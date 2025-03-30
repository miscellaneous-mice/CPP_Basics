#include "../City.h"

namespace std {
    template<typename T>
    class enhanced_map : public std::unordered_map<T, City> {
    public:
        const City& at(const T& key) const {
            if (this->find(key) != this->end()) {
                return this->std::unordered_map<T, City>::at(key);
            } else {
                std::cerr << "No key found in the hashmap" << std::endl;
                throw std::out_of_range("Key not found");
            }
        }

        // Override erase() but call std::unordered_map<T, City>::erase()
        size_t erase(const T& key) {
            if (this->find(key) != this->end()) {
                return this->std::unordered_map<T, City>::erase(key);
            } else {
                std::cerr << "No key found in the hashmap" << std::endl;
                return 0;
            }
        }
    };
}

int main() {
    std::cout<<"\nBasic unordered map"<<std::endl;
    std::enhanced_map<std::string> CityMap;
    CityMap["Melbourne"] = City{"Melbourne", 100000, 9.65, 4.35};
    CityMap["London"] = City{"London", 100000, 9.65, 4.35};
    CityMap["NYC"] = City{"NYC", 100000, 9.65, 4.35};
    CityMap["Paris"] = City{"Paris", 100000, 9.65, 4.35};
    CityMap["Japan"] = City{"Japan", 100000, 9.65, 4.35};

    const auto& cities = CityMap;
    // std::cout<<cities["Melbourne"]<<std::endl; // This is because std::map/unordered_map has no version of const RetType operator[] version
    std::cout<<cities.at("Melbourne")<<std::endl;
    CityMap.erase("NYC");

    for (const auto& [_, data] : cities) {
        std::cout<<data<<std::endl;
    }

}