#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>

int main() {
    char file_name[PATH_MAX];
    struct stat st;
    char *nl;
    while (fgets(file_name, sizeof(file_name), stdin)) {
        nl = memchr(file_name, '\n', sizeof(file_name));
        if (nl) {
            *nl = '\0';
        }
        if (lstat(file_name, &st) != -1) {
            if (S_ISLNK(st.st_mode)) {
                char absolute_path[PATH_MAX];
                realpath(file_name, absolute_path);
//                if (real_path == NULL) {
//                    continue;
//                }
                printf("%s\n", absolute_path);
            } else if (S_ISREG(st.st_mode)) {
                char link_file_name[PATH_MAX];
                char * base_name = basename(file_name);
                strcpy(link_file_name, "link_to_");
                strcat(link_file_name, base_name);
                symlink(file_name, link_file_name);
            }
        }
    }

    return 0;
}