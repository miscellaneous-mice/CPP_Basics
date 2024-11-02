#include <iostream>
#include <string>

class Animal {
public:
    virtual void makeSound() const {
        std::cout << "Some generic animal sound\n";
    }
    
    virtual ~Animal() { // Virtual destructor
        std::cout << "Animal destroyed\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() const override { // Override keyword is optional but good practice
        std::cout << "Woof!\n";
    }
    
    ~Dog() {
        std::cout << "Dog destroyed\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow!\n";
    }
    
    ~Cat() {
        std::cout << "Cat destroyed\n";
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();
    
    animal1->makeSound(); // Outputs: Woof!
    animal2->makeSound(); // Outputs: Meow!
    
    delete animal1; // Outputs: Dog destroyed \n Animal destroyed
    delete animal2; // Outputs: Cat destroyed \n Animal destroyed
    
    return 0;
}


