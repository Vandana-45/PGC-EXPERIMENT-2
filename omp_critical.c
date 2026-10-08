#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

int main() {
    int counter = 0;

    printf("=== OpenMP Critical Section ===\n\n");

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        for (int i = 0; i < ITERATIONS; i++) {
            #pragma omp critical
            {
                counter++;
            }
        }
    }

    printf("Final Counter Value = %d\n", counter);
    printf("Expected Value      = %d\n", NUM_THREADS * ITERATIONS);

    return 0;
}
