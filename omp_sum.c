#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    long long sum = 0;

    printf("=== OpenMP Parallel For Loop with Reduction ===\n\n");

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    long long expected = (long long)N * (N + 1) / 2;

    printf("Calculated Sum (1 to %d) = %lld\n", N, sum);
    printf("Expected Sum            = %lld\n", expected);

    return 0;
}
