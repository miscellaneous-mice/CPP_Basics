#include "basic.h"
#include "implementation.h"
#include "data.h"

#define calc_offset(s, m) ((size_t)&(((s*)0)->m))

int main(){
    // Class implementation
    std::unique_ptr<Entity> e = nullptr;
    e->PrintType();
    e->total();
    // std::cout<<"Name : "<<e->getName()<<std::endl; // Gives error
    
    // C implementation
    EntityData* e_new = nullptr;
    Entity_PrintType(e_new);
    Entity_total();
    // std::cout<<"Name : "<<Entity_getName(e_new)<<std::endl; // Gives error

    // Getting when the size of class is
    Data* d = nullptr;
    uint64_t offset = offsetof(Data, a);
    std::cout<<"Offset of a is : "<<offset<<" bytes\n";

    offset = offsetof(Data, b);
    std::cout<<"Ofsset of b is : "<<offset<<" bytes\n";

    offset = offsetof(Data, c);
    std::cout<<"Ofsset of c is : "<<offset<<" bytes\n";

    offset = offsetof(Data, d);
    std::cout<<"Ofsset of d is : "<<offset<<" bytes\n";

    offset = offsetof(Data, e);
    std::cout<<"Ofsset of e is : "<<offset<<" bytes\n";

    std::cout<<"Ofsset of e is : "<<calc_offset(Data, f)<<" bytes\n";
    std::cout<<"Ofsset of e is : "<<calc_offset(Data, g)<<" bytes\n";

    std::cout<<"Nullptr : "<<((Data*)0)<<std::endl;
    std::cout<<"Address w.r.t the nullptr : "<<&((Data*)0)->g<<std::endl;
    std::cout<<"Calculating the size from address "<<((Data*)0)<<" to "<<&((Data*)0)->g<<" is : "<<((size_t)&((Data*)0)->g)<<" bytes"<<std::endl;
    delete d;
    delete e_new;
}
/*
(Data*)0 : nullptr of data type Data*
&((Data*)0)->m : Get the address of m w.r.t 0 hence giving the offset w.r.t zero
*/