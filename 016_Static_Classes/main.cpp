/*
-   Static variable inside a class means that there will ever only be one instance of that variable for all the instances of that struct/Class

-   Hence if the static variable is changed in one instance, then the change of static variable will be reflected in all the instances of that struct/Class
*/

#include "entity.h"

int main(){
    Entity e1;
    Entity e2;

    e1.a = 5; // Same as defining Entity::a = 5
    e1.b = 15;
    e1.c = 25; // Same as defining Entity::c = 25
    e1.Print();

    e2.a = 10; // Same as redefining Entity::a = 10
    e2.b = 20;
    e2.c = 30; // Same as defining Entity::c = 30
    e2.Print();

    e1.add_to_a(10); // Same as Entity::a = Entity::a + 10 => 20
    Entity::add_to_b(e1, 10); // Same as e1.add_to_c(e1, 10) or e2.add_to_c(e1, 10)
    e1.add_to_c(10); // Same as Entity::a = Entity::c + 10 => 40
    e1.Print();

    e2.add_to_a(10); // Same as Entity::a = Entity::a + 10 => 30
    Entity::add_to_b(e2, 10); // Same as e1.add_to_c(e2, 10) or e2.add_to_c(e2, 10)
    e2.add_to_c(10); // Same as Entity::a = Entity::c + 10 => 50
    e2.Print();

    return 0;
}