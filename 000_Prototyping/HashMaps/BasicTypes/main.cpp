#include <any>
#include <map>
#include <string>
#include <iostream>


class HashMap {
public:
    std::map<std::string, std::any> Map;

    template<typename T>
    void add_element(const std::string& key, T value) {
        Map[key] = value;  // Store value as std::any
    }

    template<typename T>
    T get_element(const std::string& key) {
        try {
            return std::any_cast<T>(Map[key]);  // Retrieve the value and cast it
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Bad cast: " << e.what() << std::endl;
            throw e;
        }
    }
    
    void print_info() {
        for (const auto& pair : Map) {
            std::cout << "Key: " << pair.first << " -> ";

            const std::type_info& type = pair.second.type();  // Get type info of the value

            if (type == typeid(int)) {
                std::cout << "Value: " << std::any_cast<int>(pair.second) << ", Type: int" << std::endl;
            }
            else if (type == typeid(float)) {
                std::cout << "Value: " << std::any_cast<float>(pair.second) << ", Type: float" << std::endl;
            }
            else if (type == typeid(double)) {
                std::cout << "Value: " << std::any_cast<double>(pair.second) << ", Type: double" << std::endl;
            }
            else if (type == typeid(std::string)) {
                std::cout << "Value: " << std::any_cast<std::string>(pair.second) << ", Type: std::string" << std::endl;
            }
            else if (type == typeid(std::map<std::string, int>)){
                for (const auto& sub_pair: std::any_cast<std::map<std::string, int>>(pair.second)){
                    std::cout<<sub_pair.first<<" -> "<<sub_pair.second<<std::endl;
                }
            }
            else {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }
};

int main() {
    HashMap* MapV2 = new HashMap();

    std::map<std::string, int> MapV1;
    MapV1["x"] = 74;
    MapV1["y"] = 75;
    MapV1["z"] = 76;
    // Adding different types of elements to the map
    MapV2->add_element("int_key", 42);
    MapV2->add_element("float_key", 3.14f);
    MapV2->add_element("string_key", std::string("Hello"));
    MapV2->add_element("map_key", MapV1);

    // Retrieving and printing the elements
    try {
        int int_value = MapV2->get_element<int>("int_key");
        float float_value = MapV2->get_element<float>("float_key");
        std::string string_value = MapV2->get_element<std::string>("string_key");
        std::map<std::string, int> coor= MapV2->get_element<std::map<std::string, int>>("map_key");

        std::cout << "int_value: " << int_value << std::endl;
        std::cout << "float_value: " << float_value << std::endl;
        std::cout << "string_value: " << string_value << std::endl;
        for (const auto& pair : coor){
            std::cout<<pair.first<<" -> "<<pair.second<<std::endl;
        }
    } catch (const std::bad_any_cast& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    MapV2->print_info();
    return 0;
}
