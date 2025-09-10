#include "stringstream.h"

int main() {
    std::cout<<"Move semantics"<<std::endl;
    auto iter_vals = [](std::unique_ptr<SStream>&& sstream) {
        std::cout<<"Moved the class instance"<<std::endl;
        SStreamAccessor::print_contents(*sstream);
    };
    
    {
        std::unique_ptr<SStream> strng_uniq_ptr = std::make_unique<SStream>("Move Smart Pointers");
        auto new_owner = std::move(strng_uniq_ptr);

        // for (auto s : *strng_uniq_ptr) {
        //     std::cout << s << ", ";
        // } std::cout<<std::endl;

        iter_vals(std::move(new_owner));
        // std::cout << *strng_uniq_ptr->begin() << std::endl; // Will cause issue
    }
}

/*
mdkir build && cd build
cmake ../
make
./exec/main
*/