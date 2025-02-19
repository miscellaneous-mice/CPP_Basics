#include "entity.h"

// If the Struct/Class variables are static then only define outside the class/struct scope to be used by the instances of class/struct
int Entity::a;
int Entity::c;

void Entity::Print(){
    std::cout << a << ", "<< b <<  ", " << c << std::endl;
}

void Entity::add_to_a(int num){
    a = a + num;
}

// The Below method is a static method hence it can't access non static variables
void Entity::add_to_b(Entity& e, int num) {
    e.b = e.b + num;
}

// But static methods can access static variables
void Entity::add_to_c(int num){
    c = c + num;
}

/*
#########################################
How Classes work:
Class Dummy{
    int a, b; // Non static members
    static c; // Static member

    // Success
    int add(){  // A hidden class instance parameter is passed hence, looks something like this "int add(Dummy& d)""
        return a + c // Looks like this "return d.a + Dummy::c"
    }

    // Error
    static int static_add(){ // No Hidden parameters is passed hence, can't access the class entities
        return a + c // Looks something like this "return d.a + Dummy::c"
    }
}
#########################################
Behind the scenes:

class Dummy{
    int a, b;
    static c;
}

int Dummy::c; // Defined as a global variable hence all class instances have the same entity c;

int Dummy::add(Dummy& d){  // A hidden class instance is passed automatically to a normal class method, hence it can access class entities
    return d.a + c
}

static int static_add(){    // A hidden class instance isn't passed automatically to a static class method, hence it can't access class entities
    return d.a + c
}
*/