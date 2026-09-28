#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 50000000

double *array;

double sequential_sum() {
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        sum += array[i];
    }

    return sum;
}

int main() {
    array = (double *)malloc(N * sizeof(double));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        array[i] = 1.0;
    }

    printf("=== OpenMP Performance Benchmark ===\n\n");

    double start = omp_get_wtime();
    double seq_sum = sequential_sum();
    double seq_time = omp_get_wtime() - start;

    printf("Sequential Time = %.6f seconds\n", seq_time);
    printf("Sequential Sum  = %.2f\n\n", seq_sum);

    double parallel_sum = 0.0;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:parallel_sum)
    for (int i = 0; i < N; i++) {
        parallel_sum += array[i];
    }

    double parallel_time = omp_get_wtime() - start;

    printf("OpenMP Time = %.6f seconds\n", parallel_time);
    printf("OpenMP Sum  = %.2f\n", parallel_sum);

    double speedup = seq_time / parallel_time;

    printf("\nSpeedup = %.2fx\n", speedup);

    free(array);

    return 0;
}
