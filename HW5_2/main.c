#include <stdio.h>

extern void mergesort(int from, int to, const int *in, int *out);


int main() {
    int n;
    int from, to, mid;
    scanf("%d %d %d", &n, &from, &to);
    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
       // b[i] = a[i];
    }
    mergesort(from, to, a, b);

    //merge(a, from, mid, to);
    for (int i = 0; i < n; i++) {
       printf("%d ", b[i]);
    }
    return 0;
}

