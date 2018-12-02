#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

extern int
check_int(uint32_t u32); /* retval: 0 - false, 1 - true */

int main() {
    for (uint32_t u32 = 0; u32 < 134217729; u32++) {
        float f = u32;
        uint32_t y = f;
        if (check_int(u32)) {
            assert(u32 == y);
        }
    }
    printf("12");
    return 0;
}
