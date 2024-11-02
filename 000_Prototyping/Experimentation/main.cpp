#include "handler.h"

int main() {
    Accessor* accessor = new Accessor();
    Base* a = new A();
    Base* b = new B();
    Base* base = new Base();

    accessor->addElement(a);
    accessor->addElement(b);
    accessor->addElement(base);

    accessor->GetInfo(a);
    accessor->GetInfo(b);
    accessor->GetInfo(base);  

    accessor->GetMapInfo(cls_a);
    accessor->GetMapInfo(cls_b);
    accessor->GetMapInfo(cls_base);  
    // accessor->AllElements();
}