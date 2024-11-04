/*
Pure Virtual Function/ Interfaces
    - Used to specify any function which is should be stricly implemented in it's subclass
    - The classes with pure virtual functions cannot be instanciated
    - The interfaces should be stricly inherited by the subclasses, or the subclasses of the subclass
*/

#include <iostream>
#include <string>

class Printable {
public:
    virtual void PrintEntityMessage(std::string message) = 0; // Assigning the function declaration will make it an pure virtual function/interface
};

class Entity : public Printable {
public:
    virtual void GetName() { std::cout<<"Entity Class"<<std::endl; }
    void PrintEntityMessage(std::string message) override {std::cout<<"Entity : "<<message<<std::endl; }
};

class Player : public Entity {
public:
    void GetName() override { std::cout<<"Player Class"<<std::endl; }
    void PrintEntityMessage(std::string message) override {std::cout<<"Player : "<<message<<std::endl; }
};

void GetInfo(Entity* obj) {
    obj->GetName();
}

void Print(Printable* obj, std::string message="Hello") {
    obj->PrintEntityMessage(message);
}

class Dummy : public Printable {
public:
    void GetName() { std::cout<<"Dummy Class"<<std::endl; }
    void PrintEntityMessage(std::string message) override {std::cout<<"Dummy : "<<message<<std::endl; }
};

int main(){
    // Printable* print = new Printable(); // The classes with interfaces cannot be instanciated
    Entity* e = new Entity();
    Player* p = new Player();
    Entity* pV = new Player();
    GetInfo(e);
    GetInfo(p);
    GetInfo(pV);

    Print(e, "Hello");
    Print(p, "Hello");
    Print(pV, "Hello");
    Print(new Dummy()); // Avoid this type of code due to memory leak

    delete e;
    delete p;
    delete pV;
    return 0;
}