#include "handler.h"

int main() {
    std::unique_ptr<Accessor> accessor = std::make_unique<Accessor>();
    std::unique_ptr<Base> a = std::make_unique<A>();
    std::unique_ptr<Base> b = std::make_unique<B>();
    std::unique_ptr<Base> base = std::make_unique<Base>();

    accessor->addElement(std::move(a));
    accessor->addElement(std::move(b));
    accessor->addElement(std::move(base));

    accessor->GetMapInfo(cls_a);
    accessor->GetMapInfo(cls_b);
    accessor->GetMapInfo(cls_base);  
    accessor->AllElements();
}