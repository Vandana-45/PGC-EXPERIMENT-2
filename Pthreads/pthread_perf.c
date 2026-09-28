#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 50000000
#define NUM_THREADS 4

double *array;
double thread_partial_sums[NUM_THREADS];

typedef struct {
    int thread_id;
    size_t start_idx;
    size_t end_idx;
} ThreadData;

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

double sequential_sum() {
    double sum = 0.0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    return sum;
}

void* parallel_sum_worker(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double partial_sum = 0.0;

    for (size_t i = data->start_idx; i < data->end_idx; i++) {
        partial_sum += array[i];
    }

    thread_partial_sums[data->thread_id] = partial_sum;
    pthread_exit(NULL);
}

int main() {
    struct timespec start_time, end_time;

    array = (double*)malloc(ARRAY_SIZE * sizeof(double));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    printf("Initializing dataset (%d elements)...\n", ARRAY_SIZE);
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1.0;
    }

    printf("\n--- Starting Performance Benchmark ---\n");

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    double seq_result = sequential_sum();
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double seq_time = get_elapsed_time(start_time, end_time);

    printf("Sequential Execution Time : %.6f seconds | Sum = %.2f\n", seq_time, seq_result);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    size_t chunk_size = ARRAY_SIZE / NUM_THREADS;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start_idx = i * chunk_size;
        thread_data[i].end_idx = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;

        if (pthread_create(&threads[i], NULL, parallel_sum_worker, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            free(array);
            return 1;
        }
    }

    double par_result = 0.0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        par_result += thread_partial_sums[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double par_time = get_elapsed_time(start_time, end_time);

    printf("Parallel Execution Time (%d threads): %.6f seconds | Sum = %.2f\n", 
           NUM_THREADS, par_time, par_result);

    double speedup = seq_time / par_time;
    double efficiency = (speedup / NUM_THREADS) * 100.0;

    printf("\n--- Performance Results ---\n");
    printf("Speedup Ratio : %.2fx\n", speedup);
    printf("Efficiency    : %.2f%%\n", efficiency);

    free(array);
    return 0;
}
