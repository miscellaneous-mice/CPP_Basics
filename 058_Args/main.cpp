#include <iostream>

int main(int argc, char **argv) {
    std::cout<<"Number of arguments passed : "<<argc<<std::endl;
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
	return 0;
}

/*
mkdir build && cd build
cmake ../
make
./exec/exec hello world
*/