#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>


char* my_strcpy(char *dest, char *src) {
    char buf[PATH_MAX];
    int i = 0;
    while (src[i] != '\0') {
        buf[i] = src[i];
        i++;
    }
    free(dest);
    buf[i] = '\0';
    dest = buf;
    return dest;
}

int my_strcmp(char* buf1, char* buf2) {
    int i = 0;
    while (1){
        if (buf1[i] == '\0' && buf2[i] == '\0') { return 0;}
        if (buf1[i] == '\0' || buf2[i] == '\0') { return 1;}
        if (buf1[i] != buf2[i]) {return 1;}
        i++;
    }
}


void normalize_path(char *path) {
    char *norm_path[PATH_MAX];
    int part_index = 0;

    char c;
    int i = 0;
    int index = 0;
    char cur_part[PATH_MAX];
    while (path[i] != '\0') {
        if (path[i] != '/' || i == 0) {
            cur_part[index] = path[i];
            index++;
            i++;
        } else {
            i++;
            cur_part[index] = '\0';
            index = 0;
            if (strcmp(cur_part, "..") == 0) {
                part_index--;
            } else if (strcmp(cur_part, ".") == 0 || strcmp(cur_part, "") == 0) {
            } else {
                char *part_path = malloc(sizeof(char) * PATH_MAX);
                part_path = my_strcpy(part_path, cur_part);
                norm_path[part_index] = part_path;
                part_index++;
            }
        }
    }
    cur_part[index] = '\0';
    if (strcmp(cur_part, "..") == 0) {
        part_index--;
    } else if (strcmp(cur_part, ".") == 0 || strcmp(cur_part, "") == 0) {
    } else {
        char *part_path = malloc(sizeof(char) * PATH_MAX);
        part_path = my_strcpy(part_path, cur_part);
        norm_path[part_index] = part_path;
        part_index++;
    }
    int flag = 0;
    if (path[i - 1] == '/') flag = 1;
    int j = 0;
    for (i = 0; i < part_index; i++) {
        index = 0;
        while (norm_path[i][index] != '\0') {
            path[j] = norm_path[i][index];
            j++;
            index++;
        }
        if (i != part_index - 1) {
            path[j] = '/';
            j++;
        }
    }
    if (flag == 1) {
        path[j] = '/';
        j++;
    }
    path[j] = '\0';
}


int main() {
    char buf[PATH_MAX];
    strcpy(buf, "abrakadabra///abc");
//    scanf("%s", buf);
    normalize_path(buf);
    printf("%s", buf);
    return 0;
}