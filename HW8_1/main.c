#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

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
        exit_code = 1;
        goto finally;
    }

    int in = open(argv[1], O_RDONLY);
    if (in <= -1) {
        exit_code = 1;
        goto finally;
    }
    ssize_t in_read;
    Item item;
    for (ssize_t Read = 0; Read < sizeof(Item);) {
        in_read = read(in, (char *)(&item) + Read, sizeof(Item) - Read);
        if (in_read <= 0) {
            exit_code = 1;
            goto finally;
        }
        Read += in_read;
    }
    printf("%d ", item.value);


    while (lseek(in, item.next_pointer, SEEK_SET) >= 0) {
        for (ssize_t Read = 0; Read < sizeof(Item);) {
            in_read = read(in, (char *)(&item) + Read, sizeof(Item) - Read);
            if (in_read <= 0) {
                exit_code = 1;
                goto finally;
            }
            Read += in_read;
        }
        printf("%d ", item.value);
        if (item.next_pointer == 0) {
            goto finally;
        }

    }
    finally:
    close(in);
    return exit_code;
}