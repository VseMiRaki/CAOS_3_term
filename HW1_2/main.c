#include <stdio.h>


int second_byte(int byte) {
    if (((byte >> 7) & 1) && (byte >> 6) % 2 == 0) {
        return 1;
    }
    return 0;
}

int first_byte(int byte) {
    int bit1 = (byte >> 7) % 2, bit2 = (byte >> 6) % 2, bit3 = (byte >> 5) % 2, bit4 = (byte >> 4) % 2,
    bit5 = (byte >> 3) % 2, bit6 = (byte >> 2) % 2, bit7 = (byte >> 1) % 2;
    if (bit1 == 0) {
        return 1;
    }
    if (bit2 == 0) {
        return -1;
    }
    if (bit3 == 0) {
        return 2;
    }
    if (bit4 == 0) {
        return 3;
    }
    if (bit5 == 0) {
        return 4;
    }
    if (bit6 == 0) {
        return 5;
    }
    if (bit7 == 0) {
        return 6;
    }
    return -1;
}

int main() {
    int number_of_acii = 0, number_of_utf8 = 0;
    int byte;
    byte = getchar();
    while (byte != EOF) {
        int number_of_bytes = first_byte(byte);
        if (number_of_bytes == -1) {
            printf("%d %d", number_of_acii, number_of_utf8);
            return 1;
        }
        if (number_of_bytes == 1) {
            number_of_acii += 1;
        }
        else {
            for (int i = 1; i < number_of_bytes; i++) {
                byte = getchar();
                if (byte == EOF || !second_byte(byte)) {
                    printf("%d %d", number_of_acii, number_of_utf8);
                    return 1;
                }
            }
            number_of_utf8 += 1;
        }
        byte = getchar();
    }
    printf("%d %d", number_of_acii, number_of_utf8);
    return 0;
}