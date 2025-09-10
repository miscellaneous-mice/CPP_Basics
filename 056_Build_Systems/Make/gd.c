#include "gd.h"

double pythagorean(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

double calc_tip(double price, double tip) {
    return price * tip/100;
}

double get_double(char* prompt, double min, double max) {
    double input;
    do {
        printf("%s", prompt);
        scanf("%lf", &input);
        if (input < min) printf("Must be greater than %lf", min);
        if (input > max) printf("Must be less than %lf", max);
    } while (input < min || input > max);
    return input;
}

/*
As you can see you just need to compile this once
clang -c gd.c // Compilation to object code

clang tip.o gd.o -o main // links all the functions together and run
clang geom.o gd.o -o main // links all the functions together and run
*/