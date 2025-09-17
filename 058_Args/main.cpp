#include <iostream>

void Counter(int arg1 = 0, [[maybe_unused]] int arg2 = 0) {
    (void) &arg1; // To remove compiler warning about not using arg1
    static int counter = 0; // initialization happens only once, next time entirely skips the line, you can debug and check
    counter++;
    std::cout<<"Called "<<counter<<" Times"<<std::endl;
}

int main(int argc, char **argv) {
    std::cout<<"Number of arguments passed : "<<argc<<std::endl;
    for (int i = 0; i < argc; i++) {
        Counter();
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    Counter();
    Counter();
	return 0;
}

/*
mkdir build && cd build
cmake ../
make
./exec/exec hello world
*/