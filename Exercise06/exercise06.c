#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 1024

int main(void) {
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed.\n");

        free(A);
        free(B);
        free(C);

        return 1;
    }

    for (int i = 0; i < N; i++) {
        A[i] = 2.0;
        B[i] = 3.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int strip = 0; strip < N; strip += STRIP_SIZE) {
        int end = strip + STRIP_SIZE;

        if (end > N) {
            end = N;
        }

        #pragma omp simd
        for (int i = strip; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double stop = omp_get_wtime();

    int correct = 1;

    for (int i = 0; i < N; i++) {
        if (C[i] != 6.0) {
            correct = 0;
            break;
        }
    }

    printf("Array size: %d\n", N);
    printf("Strip size: %d\n", STRIP_SIZE);
    printf("C[0] = %.2f\n", C[0]);
    printf("C[%d] = %.2f\n", N - 1, C[N - 1]);
    printf("Verification: %s\n", correct ? "PASSED" : "FAILED");
    printf("Execution time: %f seconds\n", stop - start);

    free(A);
    free(B);
    free(C);

    return 0;
}
