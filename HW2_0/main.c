#include <stdio.h>

int f(int A, int B, int C, int x);

int main() {
	int A, B, C, x;
	scanf("%d %d %d %d", &A,& B, &C, &x);
	x = f(A, B, C, x);
	printf("%d", x);
	return 0;
}
