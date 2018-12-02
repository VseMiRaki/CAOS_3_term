#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct Person {
    uint32_t  id;
    uint8_t   age;
    char      first_name[20];
    char      last_name[20];
} person_t;

extern void
sort_by_age(int N, person_t *persons);


int main() {
    person_t *v = (person_t*)malloc(3*sizeof(person_t));
    v[0].age = 4;
    v[0].id = 2;
    v[1].age = 2;
    v[1].id = 3;
    v[2].age = 3;
    v[2].id = 4;
    sort_by_age(3, v);
    return 0; 
}
