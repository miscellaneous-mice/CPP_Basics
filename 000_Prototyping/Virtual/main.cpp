#include "utils.h"

int main() {
    Base* a = new A();
    Base* b = new B();
    Base* derived = new Derived();
    getInfo(a);
    getInfo(b);
    getInfo(derived);
    delete a;
    delete b;
    delete derived;
    return 0;
}
