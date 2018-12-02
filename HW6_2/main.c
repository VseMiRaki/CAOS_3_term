#include <stdio.h>

extern float dot_product(int N, const float *A, const float *B);

int main() {
    int n;
    scanf("%d", &n);
    float A[n], B[n];
    for (int i = 0; i < n; i++) {
        scanf("%f", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%f", &B[i]);
    }
    printf("%f", dot_product(n, A, B));
    return 0;
}
