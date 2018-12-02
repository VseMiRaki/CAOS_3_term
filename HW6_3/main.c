#include <stdio.h>
#include <stdlib.h>
#include <smmintrin.h>
#include <xmmintrin.h>

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);


    int new_n = n;
    int new_m = m;
    if (n % 4 != 0) {
        new_n = n + 4 - n % 4;
    }
    if (m % 4 != 0) {
        new_m = m + 4 - m % 4;
    }
    float * first_matrix = aligned_alloc(16, new_m * new_n * sizeof(float));
    float * second_matrix = aligned_alloc(16, new_m * new_n * sizeof(float));
    float * result_matrix = aligned_alloc(16, new_n* new_n * sizeof(float));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", first_matrix + (i * new_m + j));
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", second_matrix + (j * new_m + i));
        }
    }

    for (int i = n; i < new_n; i++) {
        for (int j = m; j < new_m; j++) {
            second_matrix[i * new_m + j] = 0;
        }
    }
    for (int i = m; i < new_m; i++) {
        for (int j = n; j < new_m; j++) {
            second_matrix[j * new_m + i] = 0;
        }
    }

    for (int i = 0; i < new_m * new_n; i++) {
        result_matrix[i] = 0;
    }
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            for (int k = 0; k < new_m; k += 4) {
                __m128 first = _mm_load_ps(first_matrix + (i * new_m + k));
                __m128 second = _mm_load_ps(second_matrix + (j * new_m + k));
                __m128 ans = _mm_dp_ps(first, second, 0xFF);
                float result;
                _mm_store_ss(&result, ans);
                result_matrix[i * new_m + j] += result;
            }
        }
    }

    free(first_matrix);
    free(second_matrix);
 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", result_matrix[i * new_n + j]);
        }
        printf("\n");
    }

    free(result_matrix);
    return 0;
}
