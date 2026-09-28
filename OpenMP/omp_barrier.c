#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    printf("=== OpenMP Barrier Demonstration ===\n\n");

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_id = omp_get_thread_num();

        printf("Thread %d: Before barrier\n", thread_id);

        #pragma omp barrier

        printf("Thread %d: After barrier\n", thread_id);
    }

    printf("\nAll threads completed.\n");

    return 0;
}
