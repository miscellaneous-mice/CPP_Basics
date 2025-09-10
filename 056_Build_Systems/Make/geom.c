#include "gd.h"

extern double pythagorean(double x, double y);

int main() {
    double x = get_double("Enter the value of x : ", -100, 100);
    double y = get_double("Enter the value of y : ", -100, 100);

    double d = pythagorean(x, y);

    printf("Distance is %lf meters \n", d);
    return 0;
}

/*
clang -E geom.c -o geom.i // Preprocessing only
clang -S geom.c // Compilation to assembly
clang -c geom.c // Compilation to object code
clang -save-temps geom.c gd.c -o main -lm // To save all the above files

clang geom.o gd.o -o main -lm // links all the functions together and run

Make changes only in this file and run "make", will just recompile geom.c
*/