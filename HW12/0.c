#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 0;
    }
    char *file_name = argv[1];
    char *pattern = argv[2];
//    printf("%lu\n", strlen(pattern));
    if (strlen(pattern) == 0) {
        printf("\n");
        return 0;
    }
    int fd = open(file_name, O_RDONLY);
    if (fd <= 0) {
        return 0;
    }
    struct stat st;
    fstat(fd, &st);
    char *contents = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    size_t size = strlen(pattern);
    for (size_t i = 0; i < st.st_size; i++) {
        if (strncmp(contents + i, pattern, size) == 0) {
            printf("%lu ", i);
        }
    }

    munmap(contents, st.st_size);
    close(fd);
    printf("\n");
    return 0;
}