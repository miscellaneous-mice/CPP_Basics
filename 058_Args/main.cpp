#include <iostream>

void Counter() {
    static int counter = 0;
    counter++;
    std::cout<<"Called "<<counter<<" Times"<<std::endl;
}

int main(int argc, char **argv) {
    std::cout<<"Number of arguments passed : "<<argc<<std::endl;
    for (int i = 0; i < argc; i++) {
        Counter();
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