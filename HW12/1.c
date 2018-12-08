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


typedef struct
{
    int value;
    uint32_t next_pointer;
} Item;

int main(int argc, char *argv[]) {

    int exit_code = 0;

    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd <= -1) {
        return  1;
    }
    struct stat st;
    fstat(fd, &st);
    if (st.st_size == 0) {
        return 1;
    }
    char *contents = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    Item* item;

    item = (Item*) contents;

    printf("%d ", item->value);


    while (item->next_pointer != 0) {
        item = (Item*) (contents + item->next_pointer);
        printf("%d ", item->value);
    }
    munmap(contents, st.st_size);
    close(fd);
    return exit_code;
}