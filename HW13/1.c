#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argv, char *argc[]) {

    if (argv != 2) {
        return 0;
    }
    int N = atoi(argc[1]);

    if (N == 1) {
        printf("1\n");
        return 0;
    }
    if (N == 0) {
        return 0;
    }

    int counter = 1;
    pid_t pid;
    do {
        pid = fork();
        if (-1 != pid) {
            counter++;
        }
    } while (0 == pid && counter < N);

    if (pid > 0 && counter <= N) {
        int status;
        waitpid(pid, &status, 0);
        if (counter - 1 == 1) {
            printf("%d\n", N);
        } else {
            printf("%d ", N - counter + 2);
        }
    } else {
        printf("%d ", 1);
    }
    return 0;
}