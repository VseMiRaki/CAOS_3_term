#include <stdio.h>

extern double my_sin(double x);

int main() {
    double x;
    scanf("%lf", &x);
    x = my_sin(x);
    printf("%.20lf", x);
    return 0;

}
