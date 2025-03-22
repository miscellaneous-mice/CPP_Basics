#pragma once
#include <iostream>
#include <map>
#include <unordered_map>

struct City {
    std::string name;
    uint64_t population;
    double lat, lng;

    bool operator==(const City& other) const {
        return name == other.name &&
               population == other.population &&
               lat == other.lat &&
               lng == other.lng;
    }

    bool operator<(const City& other) const {
        int res = name.compare(other.name);
        return res < 0;
    }
};

std::ostream& operator<<(std::ostream& stream, const City& city) {
    std::cout<<"Population : "<<city.population << "\nCity : "<<city.name 
    << "\nLatitude, Longitude : " << "(" << city.lat << ", " <<city.lng << ")" << std::endl;
    return stream;
}