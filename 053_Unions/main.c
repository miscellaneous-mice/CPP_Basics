#include <stdio.h>

typedef union {
    char ch_val[128];
    long long num_val;
} val_container;

int main() {
    val_container v = {0};
    v.num_val = 42;      // write to the long long
    printf("%lld\n", v.num_val);

    v.ch_val[0] = 'A'; // write to the first char
    printf("%c\n", v.ch_val[0]);

    // But now, v.num_val may no longer be meaningful
    printf("%lld (garbled)\n", v.num_val);
    return 0;
}