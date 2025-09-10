#include "gd.h"

extern double calc_tip(double price, double tip);

int main() {
    double price = get_double("Enter price meal : ", 0, 1000);
    double tip = get_double("Enter tip amount (percentage) : ", 0, 100);

    double tipAmt = calc_tip(price, tip);
    double totalprice = price + tipAmt;
    printf("Tip amount %lf\n", tipAmt);
    printf("Total amount %lf", totalprice);
}

/*
clang -E tip.c -o tip.i // Preprocessing only
clang -S tip.c // Compilation to assembly
clang -c tip.c // Compilation to object code
clang -save-temps tip.c gd.c -o main // To save all the above files

clang tip.o gd.o -o main // links all the functions together and run

Make changes only in this file and run "make", will just recompile tip.c
*/