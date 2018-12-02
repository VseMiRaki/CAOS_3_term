#include <stdio.h>

extern void summ(int N, const int *A, const int *B, int *R);

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    int B[N];
    int R[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    summ(N, A, B, R);
    for (int i = 0; i < N; i++) {
        printf("%d ", R[i]);
    }
    return 0;
}
