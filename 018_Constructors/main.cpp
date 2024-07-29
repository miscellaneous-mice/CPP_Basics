/*
Constructor is used to initialize class objects
Constructor is by default initialized, it's called a default constructor
*/

#include <iostream>

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

float* get_addr(float* addr){
    return addr;
}

int main(){
    Entity e(10.0f, 5.0f);
    Log::info(std::to_string(e.garbage).c_str());
    // Log l; // Throws error as we have initialized log to have no constructor i.e. can't construct any instances, as constructor is private
    e.Print();
    return 0;
}