#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>


size_t get_size(int dir_fd) {
    struct dirent *entry;
    DIR *dir = fdopendir(dir_fd);
    size_t ans = 0;
    struct stat st;
    while((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        fstatat(dir_fd, entry->d_name, &st, 0);
        int newFD;
        if (S_ISDIR(st.st_mode) && (newFD = open(entry->d_name, O_RDONLY | O_DIRECTORY) >= 0)) {
            ans += get_size(newFD);
            close(newFD);
        }
        else if (S_ISREG(st.st_mode)) {
            ans += st.st_size;
        }
    }
    return ans;
}

int main(int argc, char *argv[])
{
    int curDir = open(argv[1], O_RDONLY | O_DIRECTORY);
    printf("%u", get_size(curDir));
    close(curDir);
    return 0;
}