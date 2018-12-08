#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int exit_code = 0;

    if (argc != 4) {
        return 1;
    }

    int size = atoi(argv[2]);
    int width = atoi(argv[3]);

    int fd = open(argv[1], O_TRUNC | O_RDWR | O_CREAT, 0666);
    if (fd <= -1) {
        return 1;
    }

    char *contents = mmap(NULL, size + size * size * width, PROT_WRITE, MAP_SHARED, fd, 0);

    ftruncate(fd, size + size * size * width);

    int t_edge = 0, l_edge = 0, r_edge = size - 1, b_edge = size - 1;

    char direction = 'r';

    int n = 1;
    int i = 0;
    int j = 0;
    while (n <= size*size) {
//        printf("%d %d\n", i, j);

        char str[width + 1];
        sprintf(str, "%*d", width, n);
        char *cage_place = contents + (i*(size*width + 1) + j*width);
        memcpy(cage_place, str, width);

        if (j == size - 1) {
            *(cage_place + width) = '\n';
        }


        if (direction == 'r' && j == r_edge) {
            direction = 'd';
            t_edge++;
//                r_edge--;
            i++;
        } else if (direction == 'd' && i == b_edge) {
            direction = 'l';
//                b_edge++;
            r_edge--;
            j--;
        } else if (direction == 'l' && j == l_edge) {
            direction = 'u';
//                l_edge++;
            b_edge--;
            i--;
        } else if (direction == 'u' && i == t_edge) {
            direction = 'r';
            l_edge++;
            j++;
        } else if (direction == 'r') {
            j++;
        } else if (direction == 'd') {
            i++;
        } else if (direction == 'l') {
            j--;
        } else if (direction == 'u') {
            i--;
        }
        n++;
    }


    finally:
    munmap(contents, size + size * size * width);
    close(fd);
    return exit_code;
}