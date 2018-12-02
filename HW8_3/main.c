#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdint.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;


int main(int argc, char **argv) {
    int exit_code = 0;
    HANDLE hFile;
    DWORD dwBytesRead = 0;

    hFile = CreateFile(argv[1],
                       GENERIC_READ,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);
    if (hFile == INVALID_HANDLE_VALUE) {
        exit_code = 1;
        goto finally;
    }
    LPVOID buf = malloc(sizeof(Item));
    printf("sdjhbcvs");
    if (FALSE == ReadFile(hFile, buf, sizeof(Item), &dwBytesRead, NULL) || dwBytesRead < sizeof(Item)) {
        exit_code = 0;
        goto finally;
    }
    Item * item = (Item*)buf;
    printf("%d ", item->value);
    LARGE_INTEGER next;
    next.QuadPart = item->next_pointer;

    while (INVALID_SET_FILE_POINTER != SetFilePointerEx(hFile, next, NULL, FILE_BEGIN)) {
        if (ReadFile(hFile, buf, sizeof(Item), &dwBytesRead, NULL) == FALSE || dwBytesRead < sizeof(Item)) {
            exit_code = 1;
            goto finally;
        }
        Item * item = (Item*)buf;
        printf("%d ", item->value);
        if (item->next_pointer == 0) {
            goto finally;
        }
        next.QuadPart = item->next_pointer;

    }
    finally:
    CloseHandle(hFile);
    return exit_code;
}