#include "random.h"

int main() {
    std::cout<<"Start Execution"<<std::endl;
    {
        std::cout<<"Uniform random generator: " << Uniform::Random::Generator()<<std::endl;
        std::cout<<"Normal random generator: " << Normal::Random::Generator()<<std::endl;
    }
    std::cout<<"End Execution"<<std::endl;
    return 0;
}