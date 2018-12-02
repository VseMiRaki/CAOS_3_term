#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

uint64_t bin_pow(int p) {
    uint64_t n = 1;
    return n << p;
}

uint64_t make_or(uint64_t a, uint64_t b) {
    return a | b;
}

uint64_t make_and(uint64_t a, uint64_t b) {
    return a & b;
}

uint64_t make_sym_dif(uint64_t a, uint64_t b) {
    return a ^ b;
}

uint64_t make_com(uint64_t a) {
    return ~a;
}

uint64_t char_to_set(int c) {
    if (c > 47 && c < 58) {
        return bin_pow(c - 48);
    }
    if (c > 64 && c < 91) {
        return bin_pow(c - 55);
    }
    if (c > 96 && c < 123) {
        return bin_pow(c - 61);
    }
    return 0;
}

void print(uint64_t current) {
    char c = '0';
    for (int i = 0; i < 10; i++) {
        if (current % 2 != 0) {
            printf("%c", c);
        }
        c++;
        current = current>>1;
    }
    c = 'A';
    for (int i = 0; i < 26; i++) {
        if (current % 2 != 0) {
            printf("%c", c);
        }
        c++;
        current = current>>1;

    }
    c = 'a';
    for (int i = 0; i < 26; i++) {
        if (current % 2 != 0) {
            printf("%c", c);
        }
        c++;
        current = current>>1;

    }
}

int main() {
    int c;
    uint64_t current = 0;
    uint64_t new = 0;
    c = getchar();
    while (c != EOF) {
        if (c == '|') {
            current = make_or(current, new);
            new = 0;
        }
        else if (c == '&') {
            current = make_and(current, new);
            new = 0;
        }
        else if (c == '^') {
            current = make_sym_dif(current, new);
            new = 0;
        }
        else if (c == '~') {
            current = make_com(current);
            new = 0;
        }
        else {
            new = make_or(new, char_to_set(c));
        }
        c = getchar();
    }
    //printf("%"PRId64, current);
    print(current);
    return 0;
}