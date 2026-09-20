#include <omp.h>
#include <stdio.h>

int main(void) {

    #pragma omp parallel
    {
        int th = omp_get_thread_num();

        printf("Thread # %d\n", th);

        #pragma omp master
        {
            printf("Inside Master # %d\n", omp_get_thread_num());
            printf("Exiting Master\n");
        }

        printf("Hi again from thread # %d\n", th);
    }

    return 0;
}
