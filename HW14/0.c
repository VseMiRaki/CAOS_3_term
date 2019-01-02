#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buffer[4096];
    char program[4096];
    fgets(buffer, sizeof(buffer), stdin);
    char* slash_n_pos = strchr(buffer, '\n');
    if (slash_n_pos) {
        *slash_n_pos = '\0';
    }
    if (0 == strnlen(buffer, sizeof(buffer))) {return 0;}
    snprintf(program, sizeof(program), "expr = %s; print(expr)", buffer);
    execlp("python3", "python3", "-c", program, NULL);
    perror("exec");
    exit(1);
}