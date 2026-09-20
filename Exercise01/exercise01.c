#include <omp.h>
#include <stdio.h>

int main(void) {

    #pragma omp parallel
    {
        int th = omp_get_thread_num();

        printf("Thread # %d reached the barrier\n", th);

        #pragma omp barrier

        printf("Outside Barrier # %d\n", th);
        printf("Hi again from thread # %d\n", th);
    }

    return 0;
}
