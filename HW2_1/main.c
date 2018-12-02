#include <stdio.h>
#include <stdlib.h>

int summ(int x0, int N, int *X);

int main() {
	int x0 = 0;
	int *X = (int*)malloc(4*sizeof(int));
	X[0] = 1;
	X[1] = 10;
	X[2] = 100;
	X[3] = 1000;
	printf("%d", summ(x0, 4, X));
	return 0;
}
