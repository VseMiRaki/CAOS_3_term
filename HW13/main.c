#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main() {
    int counter = 0;
    int index = 0;
    pid_t pid;
    do {
        char str[4096];
        if (scanf("%s", str) == EOF) {
            if (index == 0 && strlen(str) == 0) {
                printf("%d", counter);
                return 0;
            }
            if (index == 1 && strlen(str) == 0) {
                return 0;
            }
            return 1;
        }
        counter = 1;
        pid = fork();
        if (pid == 0) {
            index = 1;
        }
    } while (0 == pid);

    int status;
    waitpid(pid, &status, 0);
    counter += status;
    if (index == 0) {
        printf("%d", WEXITSTATUS(counter));
        return 0;
    }
    return counter;
}