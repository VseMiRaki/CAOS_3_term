#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint16_t satsum(uint16_t x, uint16_t y) {
    uint16_t sum = x + y;
    if (sum < x) {
        return -1;
    }
    return sum;
}

//int main() {
//    uint16_t a, b;
//    scanf("%"SCNu16"%"SCNu16, &a, &b);
//    uint16_t sum = satsum(a, b);
//    printf("%"SCNu16, sum);
//    return 0;
//}