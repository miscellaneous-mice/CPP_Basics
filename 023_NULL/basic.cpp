#include "basic.h"

int Entity::population;

std::string Entity::getName() const {
    return m_Name;
}

void Entity::total(){
    std::cout<<"Population : "<<population<<std::endl;
}

void Entity::PrintType(){
    std::cout<<"Entity Class"<<std::endl;
}