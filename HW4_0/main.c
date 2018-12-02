#include <stdio.h>
#include <stdint.h>
//#include "add.c"

extern int R;

extern void calculate();

int main() {
    calculate();
    printf("%d", R);
    return 0;
}
