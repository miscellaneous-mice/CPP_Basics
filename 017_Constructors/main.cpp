/*
Constructor is used to initialize class objects
Constructor is by default initialized, it's called a default constructor
*/

#include <iostream>
#include <iomanip>

class Entity{
public:
    float garbage;
    float X, Y, Z;

    Entity(float x, float y){
        X = x;
        Y = y;
    }

    void Print(){
        std::cout<< X << ", " << Y <<std::endl;
    }

};

// This class only has static methods and objects
class Log{
private:
    Log() {}; // We hide the constructor by making it private. It is same as giving Log() = delete;
public:
    static void info(const char* message){
        std::cout<<message<<std::endl;
    }
};

void* get_addr_hex(void* addr){
    return addr; // 0x16fa96e6c : 61586270540
}

uintptr_t get_addr_decimal(void* addr){
    return reinterpret_cast<uintptr_t>(addr); // 0x16fa96e6c : 61586270540
}

int main(){
    Entity e(10.0f, 5.0f);
    Log::info(std::to_string(e.garbage).c_str());
    // Log l; // Throws error as we have initialized log to have no constructor i.e. can't construct any instances, as constructor is private
    e.Print();

    void* ptr = &e;

    std::cout<<get_addr_hex(ptr)<<std::endl;
    std::cout<<get_addr_decimal(ptr)<<std::endl;


    std::cout << "Hex address: 0x"
              << std::hex << std::uppercase // use hex format and uppercase A-F
              << std::setw(sizeof(uintptr_t) * 2) // pad to full width
              << std::setfill('0')              // pad with zeros
              << reinterpret_cast<uintptr_t>(ptr)
              << std::endl;

    // Print as decimal
    std::cout << "Decimal address: "
              << std::dec
              << reinterpret_cast<uintptr_t>(ptr)
              << std::endl;
    return 0;
}