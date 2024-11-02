#include <iostream>
#include "fileutils.h"

int main() {
    try {
        FileUtils* f = new FileUtils("Logger");
        std::cout << "File written status : "<< f->Writer("Task 2 : Using Instagram") << std::endl;
        std::cout << "File content is : \n" << f->Reader() <<std::endl;
        delete f;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}