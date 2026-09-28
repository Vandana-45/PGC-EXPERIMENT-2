# Parallel Computing Experiment — Pthreads and OpenMP

## Performance Analysis of Pthreads and OpenMP

This experiment demonstrates parallel programming concepts using **POSIX Threads (Pthreads)** and **OpenMP** in C. The programs cover thread creation, work sharing, race conditions, synchronization, barriers, and performance measurement.

The experiment is divided into three parts:

- **Part A — Pthreads**
- **Part B — OpenMP**
- **Part C — Performance Analysis**

---

## Table of Contents

1. [Objective](#1-objective)
2. [Software and Environment](#2-software-and-environment)
3. [Part A — Pthreads](#3-part-a--pthreads)
4. [Part B — OpenMP](#4-part-b--openmp)
5. [Part C — Performance Analysis](#5-part-c--performance-analysis)
6. [Performance Results](#6-performance-results)
7. [Observations](#7-observations)
8. [Conclusion](#8-conclusion)
9. [Repository Structure](#9-repository-structure)

---

## 1. Objective

The objectives of this experiment are:

- To create and execute threads using Pthreads.
- To divide computation among multiple Pthreads.
- To demonstrate a race condition.
- To solve a race condition using a mutex.
- To create parallel regions using OpenMP.
- To perform work sharing and reduction using OpenMP.
- To demonstrate race conditions in OpenMP.
- To synchronize OpenMP threads using `critical`.
- To coordinate threads using a barrier.
- To measure and compare parallel execution time.
- To calculate speedup and study the effect of increasing the number of threads.

---

## 2. Software and Environment

| Component | Details |
|---|---|
| Programming Language | C |
| Operating System | Ubuntu / Linux |
| Compiler | GCC |
| Pthreads | POSIX Threads (`pthread`) |
| OpenMP | GCC OpenMP (`-fopenmp`) |
| Working Directory | `~/parallel_lab` |

### Compilation

Pthreads programs are compiled using:

```bash
gcc program.c -o program -pthread
```

OpenMP programs are compiled using:

```bash
gcc program.c -o program -fopenmp
```

---

# 3. Part A — Pthreads

Part A contains the Pthreads programs used in the experiment.

## 3.1 `thread1.c` — Create One Thread

This program creates one thread using `pthread_create()`.

### Commands

```bash
gcc thread1.c -o thread1 -pthread
./thread1
```

### Output

```text
Hello from the thread!
Main thread finished.
```

### Concept Demonstrated

- Creating a thread
- Executing a thread function
- Waiting for a thread using `pthread_join()`

---

## 3.2 `thread2.c` — Create Multiple Threads

This program creates four Pthreads and passes a different thread ID to each thread.

### Commands

```bash
gcc thread2.c -o thread2 -pthread
./thread2
```

### Sample Output

```text
Hello from Thread 1
Hello from Thread 3
Hello from Thread 4
Hello from Thread 2
All threads have finished.
```

The order of thread output can vary because the operating system schedules the threads independently.

### Concept Demonstrated

- Creating multiple threads
- Passing arguments to threads
- Joining multiple threads
- Concurrent execution

---

## 3.3 `thread_sum.c` — Divide Work Among Threads

The program divides an array among four threads. Each thread calculates a partial sum and the main thread combines the partial sums.

### Commands

```bash
gcc thread_sum.c -o thread_sum -pthread
./thread_sum
```

### Output

```text
Thread 1 calculated sum = 30
Thread 2 calculated sum = 70
Thread 3 calculated sum = 110
Thread 4 calculated sum = 150
Total sum = 360
```

### Concept Demonstrated

- Dividing work among threads
- Partial computation
- Combining thread results
- Thread synchronization using `pthread_join()`

---

## 3.4 Additional Pthreads Programs

The experiment also includes the following Pthreads concepts:

### `race.c` — Race Condition

The shared counter is incremented by multiple threads without synchronization.

Observed output:

```text
Expected counter = 400000
Actual counter   = 212545
```

The actual value differs from the expected value because multiple threads access and update the same shared variable concurrently.

### `mutex.c` — Mutex Synchronization

The counter update is protected using:

```c
pthread_mutex_lock(&lock);
counter++;
pthread_mutex_unlock(&lock);
```

Observed output:

```text
Expected counter = 400000
Actual counter   = 400000
```

This demonstrates how a mutex protects a critical section.

### `pthread_perf.c` — Pthreads Performance

The program divides a large computation among different numbers of Pthreads and measures execution time.

Recorded results:

| Threads | Execution Time (seconds) |
|---:|---:|
| 1 | 2.084063 |
| 2 | 1.170643 |
| 4 | 0.806536 |
| 6 | 0.694168 |
| 16 | 0.470630 |

The calculated result was:

```text
Result = 499999999500.00
```

---

# 4. Part B — OpenMP

Part B demonstrates parallel programming using OpenMP directives.

## 4.1 `omp_sum.c` — Work Sharing and Reduction

The program uses:

```c
#pragma omp parallel for reduction(+:total_sum)
```

The array contains:

```text
10, 20, 30, 40, 50, 60, 70, 80
```

### Output

```text
Total sum = 360
```

The output also shows different OpenMP threads processing different array elements.

### Concept Demonstrated

- `parallel for`
- Work sharing
- Thread identification
- Reduction

---

## 4.2 `omp_race.c` — OpenMP Race Condition

The program increments a shared counter inside an OpenMP parallel region without synchronization.

Observed output:

```text
Expected counter = 400000
Actual counter   = 104876
```

This demonstrates the effect of a race condition when multiple OpenMP threads update the same variable.

---

## 4.3 `omp_critical.c` — Synchronization Using Critical

The counter update is protected using:

```c
#pragma omp critical
{
    counter++;
}
```

Observed output:

```text
Expected counter = 400000
Actual counter   = 400000
```

This demonstrates synchronization of a shared operation using the OpenMP `critical` directive.

---

## 4.4 `omp_barrier.c` — Thread Coordination

The program demonstrates the use of:

```c
#pragma omp barrier
```

### Output

```text
Thread 3 completed Stage 1
Thread 1 completed Stage 1
Thread 0 completed Stage 1
Thread 2 completed Stage 1
Thread 3 started Stage 2
Thread 1 started Stage 2
Thread 2 started Stage 2
Thread 0 started Stage 2
```

The barrier ensures that all threads complete Stage 1 before any thread proceeds to Stage 2.

---

## 4.5 `omp_perf.c` — OpenMP Performance

The program measures execution time using different numbers of OpenMP threads.

Recorded results:

| Threads | Execution Time (seconds) |
|---:|---:|
| 1 | 0.9493 |
| 2 | 0.4754 |
| 4 | 0.1869 |
| 8 | 0.1259 |

The computed sum was:

```text
124999999750000000
```

for the displayed runs.

---

# 5. Part C — Performance Analysis

Part C analyzes the performance of sequential/parallel execution and compares Pthreads with OpenMP.

## 5.1 Sequential Execution

A sequential implementation provides a baseline execution time.

**Note:** A separate sequential benchmark result was not included in the screenshots supplied for this experiment, so no sequential timing is claimed here.

---

## 5.2 Pthreads Execution

The Pthreads performance program was executed with different thread counts.

| Threads | Time (s) |
|---:|---:|
| 1 | 2.084063 |
| 2 | 1.170643 |
| 4 | 0.806536 |
| 6 | 0.694168 |
| 16 | 0.470630 |

The execution time decreased as the number of threads increased in the recorded runs.

---

## 5.3 OpenMP Execution

The OpenMP performance program was executed with 1, 2, 4, and 8 threads.

| Threads | Time (s) |
|---:|---:|
| 1 | 0.9493 |
| 2 | 0.4754 |
| 4 | 0.1869 |
| 8 | 0.1259 |

The recorded execution time decreased as the number of OpenMP threads increased.

---

## 5.4 Execution-Time Comparison

### Pthreads

The Pthreads run decreased from:

```text
2.084063 seconds (1 thread)
```

to:

```text
0.470630 seconds (16 threads)
```

### OpenMP

The OpenMP run decreased from:

```text
0.9493 seconds (1 thread)
```

to:

```text
0.1259 seconds (8 threads)
```

The measurements show that parallel execution reduced the measured execution time for the tested workload.

---

## 5.5 Speedup Calculation

Speedup is calculated as:

```text
Speedup = Time with 1 thread / Time with N threads
```

### Pthreads Speedup

| Threads | Time (s) | Speedup |
|---:|---:|---:|
| 1 | 2.084063 | 1.00× |
| 2 | 1.170643 | 1.78× |
| 4 | 0.806536 | 2.58× |
| 6 | 0.694168 | 3.00× |
| 16 | 0.470630 | 4.43× |

### OpenMP Speedup

| Threads | Time (s) | Speedup |
|---:|---:|---:|
| 1 | 0.9493 | 1.00× |
| 2 | 0.4754 | 2.00× |
| 4 | 0.1869 | 5.08× |
| 8 | 0.1259 | 7.54× |

These speedups use each implementation's **1-thread measurement as its own baseline**.

---

# 6. Performance Results

## Pthreads Performance

```text
1 thread  → 2.084063 s
2 threads → 1.170643 s
4 threads → 0.806536 s
6 threads → 0.694168 s
16 threads → 0.470630 s
```

## OpenMP Performance

```text
1 thread → 0.9493 s
2 threads → 0.4754 s
4 threads → 0.1869 s
8 threads → 0.1259 s
```

### Result Summary

| Implementation | Lowest Recorded Time | Thread Count |
|---|---:|---:|
| Pthreads | 0.470630 s | 16 |
| OpenMP | 0.1259 s | 8 |

These values are the recorded results from the submitted experiment screenshots.

---

# 7. Observations

1. Pthreads provides explicit control over thread creation and joining.
2. Multiple Pthreads can divide a computational task into independent portions.
3. A race condition can produce an incorrect shared-counter result when synchronization is absent.
4. A mutex protects a shared critical section and produces the expected counter value in the recorded test.
5. OpenMP simplifies parallel programming through compiler directives such as `parallel`, `parallel for`, `critical`, `barrier`, and `reduction`.
6. The OpenMP race-condition program produced an incorrect counter value without synchronization.
7. The OpenMP `critical` directive produced the expected counter value.
8. The barrier example demonstrates coordination between stages of parallel execution.
9. In the recorded performance tests, increasing the number of threads reduced execution time for both Pthreads and OpenMP.
10. The measurements are specific to the execution environment and workload used during this experiment.

---

# 8. Conclusion

This experiment demonstrated the basic concepts of parallel programming using **Pthreads** and **OpenMP**.

The Pthreads programs demonstrated thread creation, multiple-thread execution, work division, race conditions, mutex synchronization, and performance measurement.

The OpenMP programs demonstrated work sharing, reduction, race conditions, critical-section synchronization, barriers, and performance measurement.

The recorded performance measurements showed reduced execution time as the number of threads increased for the tested workloads. The experiment also demonstrated that synchronization mechanisms such as mutexes and OpenMP `critical` sections are required when multiple threads update shared data.

Overall, the experiment provides practical experience with thread creation, synchronization, parallel work distribution, and performance analysis in C.

---

# 9. Repository Structure

```text
parallel_lab/
│
├── README.md
│
├── Part-A-Pthreads/
│   ├── thread1.c
│   ├── thread2.c
│   ├── thread_sum.c
│   ├── race.c
│   ├── mutex.c
│   └── pthread_perf.c
│
├── Part-B-OpenMP/
│   ├── omp_sum.c
│   ├── omp_race.c
│   ├── omp_critical.c
│   ├── omp_barrier.c
│   └── omp_perf.c
│
├── Part-C-Performance/
│   ├── sequential/
│   ├── pthreads/
│   ├── openmp/
│   ├── comparison/
│   └── results/
│
└── screenshots/
    ├── Part-A-Pthreads/
    │   ├── thread1.png
    │   ├── thread2.png
    │   ├── thread_sum.png
    │   ├── race.png
    │   ├── mutex.png
    │   └── pthread_perf.png
    │
    ├── Part-B-OpenMP/
    │   ├── omp_sum.png
    │   ├── omp_race.png
    │   ├── omp_critical.png
    │   ├── omp_barrier.png
    │   └── omp_perf.png
    │
    └── Part-C-Performance/
        ├── pthread_performance.png
        ├── openmp_performance.png
        ├── execution_time_comparison.png
        ├── speedup.png
        └── performance_analysis.png
```

---

## Commands Used

### Pthreads

```bash
gcc thread1.c -o thread1 -pthread
./thread1

gcc thread2.c -o thread2 -pthread
./thread2

gcc thread_sum.c -o thread_sum -pthread
./thread_sum

gcc race.c -o race -pthread
./race

gcc mutex.c -o mutex -pthread
./mutex

gcc pthread_perf.c -o pthread_perf -pthread
./pthread_perf
```

### OpenMP

```bash
gcc omp_sum.c -o omp_sum -fopenmp
./omp_sum

gcc omp_race.c -o omp_race -fopenmp
./omp_race

gcc omp_critical.c -o omp_critical -fopenmp
./omp_critical

gcc omp_barrier.c -o omp_barrier -fopenmp
./omp_barrier

gcc omp_perf.c -o omp_perf -fopenmp
./omp_perf
```

---

## Final Result

The experiment successfully demonstrates:

- **Pthreads:** thread creation, work sharing, race conditions, mutex synchronization, and performance measurement.
- **OpenMP:** parallel regions, reduction, race conditions, critical sections, barriers, and performance measurement.
- **Performance Analysis:** execution-time measurements and speedup calculations for the recorded Pthreads and OpenMP runs.
