#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char     i8;
    int16_t  i16;
    int      i32;
} values_t;

extern int64_t
calculate(const values_t *values);

int main() {
	values_t *v = malloc(sizeof(values_t));
	scanf("%c%hd%d", &v->i8, &v->i16, &v->i32);
	printf("%lld", calculate(v));
	return 0;
}
