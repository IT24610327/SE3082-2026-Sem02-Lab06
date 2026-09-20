#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

long long fib(int n) {
    long long i;
    long long j;

    if (n < 2) {
        return n;
    }

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait

    return i + j;
}

int main(int argc, char *argv[]) {
    int n = 20;
    long long result;
    double start;
    double stop;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    stop = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Execution time = %f seconds\n", stop - start);

    return 0;
}
