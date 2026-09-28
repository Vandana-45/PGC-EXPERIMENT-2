#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    printf("--- OpenMP Basic Parallel Region Demo ---\n");

    omp_set_num_threads(4);

    int max_threads = omp_get_max_threads();
    printf("Configured Max Threads: %d\n\n", max_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        printf("Hello World from thread %d of %d\n", thread_id, total_threads);
    }

    printf("\nExecution back in master thread. Program finished.\n");
    return 0;
}
