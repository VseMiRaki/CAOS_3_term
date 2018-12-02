#include <stdio.h>
#include <stdlib.h>

int N;
int *A;
int *B;
int *R;

extern void summ();
extern void everyday795(int X, int Y);

int main() {
    scanf("%d", &N);
    A = malloc(N * sizeof(int));
    B = malloc(N * sizeof(int));
    R = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", B + i);
    }
    summ();
    for (int i = 0; i < N; i++) {
        printf("%d ", *(R + i));
    }
    int x, y;
    scanf("%d %d", &x, &y);
    everyday795(x, y);
    return 0;
}
