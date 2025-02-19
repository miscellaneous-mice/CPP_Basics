#include <iostream>

class Entity {
public:
    char* buffer;
    
    Entity(int size) {
        buffer = new char[size];
        std::cout << "Initialized an instance in the memory" << std::endl;
    }

    void Set_Memory(int value, int size) {
        memset(buffer, value, size);
    }

    ~Entity() {
        delete[] buffer;
        std::cout << "The instance memory has been deallocated" << std::endl;
    }
};

void desc_mem() {
    Entity e(10);
    e.Set_Memory(1, 8);
}

int main() {
    desc_mem();
    return 0;
}
