#include "implementation.h"

std::string Entity_getName(EntityData* self){
    return self->m_Name;
}

void Entity_total(){
    std::cout<<"Population : " <<population<<std::endl;
}

void Entity_PrintType(EntityData* self){
    std::cout<<"Entity Class"<<std::endl;
}