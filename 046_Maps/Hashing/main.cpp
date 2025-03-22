#include "../City.h"

namespace std {
    template <>
    struct hash<City> {
        size_t operator()(const City& key) const {
            return std::hash<std::string>()(key.name);
        }
    };
}


int main() {
    City dublin {"Dublin", 4587933, 34.34, 95.33};
    City japan {"Japan", 3248943, 54.34, 84.33};
    City hongkong {"HongKong", 32489433, 23.43, 16.32};

    std::cout<<"Unordered maps"<<std::endl;
    std::unordered_map<City, uint16_t> unorderedcities;
    unorderedcities[hongkong] = 1200;
    unorderedcities[hongkong] = 1940; // Update to the newest one
    unorderedcities[dublin] = 1984;
    unorderedcities[japan] = 1649;
    for (auto& [city, year] : unorderedcities) {
        std::cout<<city.name<<" : "<<year<<std::endl;
    }

    std::cout<<"\nOrdered maps"<<std::endl;
    std::map<City, uint16_t> orderedcities;
    orderedcities[dublin] = 1984;
    orderedcities[hongkong] = 1200;
    orderedcities[hongkong] = 1218; // Update to the newest one
    orderedcities[japan] = 1649;
    for (auto& [city, year] : orderedcities) {
        std::cout<<city.name<<" : "<<year<<std::endl;
    }

}