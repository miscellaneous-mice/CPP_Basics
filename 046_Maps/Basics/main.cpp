#include "../City.h"

int main() {
    std::cout<<"Testing the City struct"<<std::endl;
    City city1 = City {"Melbourne", 100000, 9.65, 4.35};
    std::cout<<city1.name<<", "<<city1.population<<std::endl;
    City city2{};
    std::cout<<city2.name<<", "<<city2.population<<", "<<city2.lat<<", "<<city2.lng<<std::endl;

    std::cout<<"\nBasic ordered map"<<std::endl;
    std::map<std::string, City> cities;
    cities["Melbourne"] = City{"Melbourne", 100000, 9.65, 4.35};
    cities["London"] = City{"London", 100000, 9.65, 4.35};
    cities["NYC"] = City{"NYC", 100000, 9.65, 4.35};
    cities["Paris"] = City{"Paris", 100000, 9.65, 4.35};
    cities["Japan"] = City{"Japan", 100000, 9.65, 4.35};

    for (auto& [key, value] : cities) {
        std::cout<<key<<" -> Population : "<<value.population<<std::endl;
    }
    
    std::cout<<"\nBasic unordered map"<<std::endl;
    std::unordered_map<std::string, City> un_cities;
    un_cities["Melbourne"] = City{"Melbourne", 100000, 9.65, 4.35};
    un_cities["London"] = City{"London", 100000, 9.65, 4.35};
    un_cities["NYC"] = City{"NYC", 100000, 9.65, 4.35};
    un_cities["Paris"] = City{"Paris", 100000, 9.65, 4.35};
    un_cities["Japan"] = City{"Japan", 100000, 9.65, 4.35};

    for (auto& [key, value] : un_cities) {
        std::cout<<key<<" -> Population : "<<value.population<<std::endl;
    }

    std::cout<<"\nIndexing new keys in map"<<std::endl;
    City& delhi = un_cities["Delhi"]; // Creates a new key in the, and here no copy is created
    delhi.name = "Delhi";
    delhi.population = 10000;
    std::cout<<delhi.name<<" -> Population : "<<un_cities["Delhi"].population<<std::endl;
    std::cout<<"Latitude : "<<un_cities["Delhi"].lat<<", Longitude : "<<delhi.lng<<std::endl;

    City delhi_cpy{"Delhi", 10000};
    un_cities["Delhi_cpy"] = delhi_cpy;
    delhi_cpy.population = 50000;
    std::cout<<delhi_cpy.name<<" -> Population : "<<delhi_cpy.population<<std::endl;
    std::cout<<un_cities["Delhi_cpy"].name<<" -> Population : "<<un_cities["Delhi_cpy"].population<<std::endl;
    return 0;
}

/*
std::map -> Indexes keys using tree data structure, hence the key is stored ordered fashion.
std::unordered -> Indexes keys using hash value, hence each key corresponds to a specific hash value.
*/