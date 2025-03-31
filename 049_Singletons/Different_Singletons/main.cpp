#include "random.h"

int main() {
    std::cout<<"Start Execution"<<std::endl;
    {
        Normal::Random::Init();
        std::cout<<"Uniform random generator: " << Uniform::Random::Generator()<<std::endl;
        std::cout<<"Normal random generator: " << Normal::Random::Generator()<<std::endl;
        Uniform::Random::Shutdown();
        Normal::Random::Shutdown();
    }
    std::cout<<"End Execution"<<std::endl;
    Uniform::Random::Shutdown();
    Normal::Random::Shutdown();

    std::cout<<"\nCorrect way of implementation"<<std::endl;
    Global::Random::Init();
    std::cout<<"Poisson random generator: " << Global::Random::Generator()<<std::endl;
    Global::Random::Shutdown();
    // Global::Random::Shutdown();
    return 0;
}