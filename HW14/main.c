#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    char buffer[4096];
    char program[8192];
    fgets(buffer, sizeof(buffer), stdin);
    char* slash_n_pos = strchr(buffer, '\n');
    if (slash_n_pos) {
        *slash_n_pos = '\0';
    }
    if (0 == strnlen(buffer, sizeof(buffer))) {return 0;}
    int fd = open("tmp1235.c", O_TRUNC | O_CREAT | O_WRONLY, 0777);
    snprintf(program, sizeof(program), "#include <stdio.h>\nint main(){int reg = (%s); printf(\"%%d\", reg);return 0;}", buffer);
    if (fd == -1) {return 0;}
    for (size_t i = 0; i < strlen(program);) {
        ssize_t wrote = write(fd, program, strlen(program) - i);
        if (wrote < 0) {return 0;}
        i += wrote;
    }
    close(fd);
    int child = fork();
    if (child == 0) {
        execlp("gcc", "gcc", "./tmp1235.c", "-o", "program123", NULL);
        perror("exec");
        exit(1);
    }
    int status;
    waitpid(child, &status, 0);
    child = fork();
    if (child == 0) {
        execlp("./program123", "./program123", NULL);
        perror("exec");
        exit(1);
    }
    waitpid(child, &status, 0);
    unlink("./program123");
    unlink("./tmp1235.c");
    exit(1);
}