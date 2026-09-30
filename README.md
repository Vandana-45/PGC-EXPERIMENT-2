# Parallel Computing Experiment 2 — Pthreads and OpenMP

## Performance Analysis of Pthreads and OpenMP

This experiment demonstrates fundamental parallel programming concepts using **POSIX Threads (Pthreads)** and **OpenMP** in C.

The experiment covers:

* Thread creation
* Multiple-thread execution
* Work sharing
* Race conditions
* Synchronization using mutexes
* Synchronization using OpenMP `critical`
* Thread coordination using barriers
* Parallel reduction
* Performance measurement
* Execution-time comparison
* Speedup and efficiency analysis

The experiment is divided into three parts:

* **Part A — Pthreads**
* **Part B — OpenMP**
* **Part C — Performance Analysis**

---

## Table of Contents

1. [Objective](#1-objective)
2. [Software and Environment](#2-software-and-environment)
3. [Part A — Pthreads](#3-part-a--pthreads)
4. [Part B — OpenMP](#4-part-b--openmp)
5. [Part C — Performance Analysis](#5-part-c--performance-analysis)
6. [Observations](#6-observations)
7. [Conclusion](#7-conclusion)
8. [Repository Structure](#8-repository-structure)
9. [Compilation and Execution Commands](#9-compilation-and-execution-commands)

---

# 1. Objective

The objectives of this experiment are:

* To create and execute threads using Pthreads.
* To create multiple threads and distribute work among them.
* To demonstrate work division using Pthreads.
* To demonstrate a race condition.
* To solve a race condition using a mutex.
* To create parallel regions using OpenMP.
* To perform work sharing and reduction using OpenMP.
* To demonstrate race conditions in OpenMP.
* To synchronize OpenMP threads using `critical`.
* To coordinate threads using a barrier.
* To measure parallel execution time.
* To compare sequential, Pthreads, and OpenMP execution.
* To calculate speedup and efficiency.
* To study the effect of increasing the number of threads.

---

# 2. Software and Environment

| Component              | Details                   |
| ---------------------- | ------------------------- |
| Programming Language   | C                         |
| Operating System       | Ubuntu / Linux            |
| Compiler               | GCC                       |
| Thread Library         | POSIX Threads (`pthread`) |
| Parallel Framework     | OpenMP                    |
| Pthreads Compiler Flag | `-pthread`                |
| OpenMP Compiler Flag   | `-fopenmp`                |

### Pthreads Compilation

```bash
gcc program.c -o program -pthread
```

### OpenMP Compilation

```bash
gcc program.c -o program -fopenmp
```

---

# 3. Part A — Pthreads

Part A demonstrates parallel programming using **POSIX Threads (Pthreads)**.

## 3.1 `thread1.c` — Create One Thread

This program creates one thread using `pthread_create()` and waits for it using `pthread_join()`.

### Concepts Demonstrated

* Creating a thread
* Executing a thread routine
* Passing control to a thread
* Joining a thread

---

## 3.2 `thread2.c` — Create Multiple Threads

This program creates multiple Pthreads and passes a unique thread ID to each thread.

### Concepts Demonstrated

* Creating multiple threads
* Passing arguments to threads
* Concurrent execution
* Joining multiple threads

The order in which thread messages appear can vary because the operating system schedules the threads independently.

---

## 3.3 `thread_sum.c` — Divide Work Among Threads

This program divides an array into separate portions. Each thread calculates a partial sum, and the main thread combines the results.

### Concepts Demonstrated

* Dividing work among threads
* Partial computation
* Combining thread results
* Thread synchronization using `pthread_join()`

For the tested array, the total sum is:

```text
Total Sum = 5050
```

---

## 3.4 `race.c` — Demonstrate Race Condition

This program allows multiple threads to update a shared counter without synchronization.

The recorded test demonstrated that the actual counter value can differ from the expected value because multiple threads access the shared variable concurrently.

### Concept Demonstrated

**Race condition caused by unsynchronized access to shared data.**

---

## 3.5 `mutex.c` — Fix Race Condition Using Mutex

This program protects the shared counter using a Pthreads mutex.

The critical section uses:

```c
pthread_mutex_lock(&lock);
counter++;
pthread_mutex_unlock(&lock);
```

The synchronized program produces the expected counter value.

### Concept Demonstrated

**Mutex synchronization and protection of a critical section.**

---

## 3.6 `pthread_perf.c` — Measure Performance

This program performs a large computation using different numbers of Pthreads and measures execution time.

Recorded Pthreads results:

| Threads | Execution Time |
| ------: | -------------: |
|       1 |     2.084063 s |
|       2 |     1.170643 s |
|       4 |     0.806536 s |
|       6 |     0.694168 s |
|      16 |     0.470630 s |

The calculated result was:

```text
Result = 499999999500.00
```

The recorded execution time decreased as the number of threads increased.

---

# 4. Part B — OpenMP

Part B demonstrates parallel programming using **OpenMP directives**.

## 4.1 `omp1.c` — Parallel Region and Thread Identification

This program creates an OpenMP parallel region and displays the thread IDs.

### Concepts Demonstrated

* OpenMP parallel region
* Thread identification
* Multiple-thread execution

---

## 4.2 `omp_sum.c` — Work Sharing and Reduction

This program uses an OpenMP parallel loop with reduction.

```c
#pragma omp parallel for reduction(+:sum)
```

The program calculates the sum of the integers from 1 to 1,000,000.

The expected and calculated result is:

```text
Calculated Sum = 500000500000
Expected Sum   = 500000500000
```

### Concepts Demonstrated

* `parallel for`
* Work sharing
* Reduction
* Parallel summation

---

## 4.3 `omp_race.c` — Demonstrate Race Condition

The program increments a shared counter inside an OpenMP parallel region without synchronization.

Recorded output:

```text
Expected counter = 400000
Actual counter   = 104876
```

The difference demonstrates a race condition caused by multiple threads updating the same shared variable.

---

## 4.4 `omp_critical.c` — Synchronization Using Critical

The shared counter update is protected using:

```c
#pragma omp critical
{
    counter++;
}
```

Recorded output:

```text
Expected counter = 400000
Actual counter   = 400000
```

This demonstrates how an OpenMP `critical` section prevents conflicting simultaneous updates to the shared counter.

---

## 4.5 `omp_barrier.c` — Thread Coordination

This program demonstrates the OpenMP barrier:

```c
#pragma omp barrier
```

The barrier ensures that all threads complete Stage 1 before any thread proceeds to Stage 2.

### Concept Demonstrated

**Coordination of threads between different stages of parallel execution.**

---

## 4.6 `omp_perf.c` — Measure Performance

The OpenMP performance program measures execution time using different numbers of threads.

Recorded results:

| Threads | Execution Time |
| ------: | -------------: |
|       1 |       0.9493 s |
|       2 |       0.4754 s |
|       4 |       0.1869 s |
|       8 |       0.1259 s |

The computed sum for the displayed runs was:

```text
124999999750000000
```

The execution time decreased as the number of OpenMP threads increased in the recorded tests.

---

# 5. Part C — Performance Analysis

Part C analyzes sequential and parallel execution and studies the effect of increasing the number of threads.

## 5.1 Sequential Execution

The sequential program provides the baseline execution time used for performance comparison.

Recorded result:

```text
Result = 499999999500.00
Execution Time = 2.063916 seconds
```

---

## 5.2 Pthreads Execution

The Pthreads performance program was executed using different thread counts.

| Threads | Execution Time |
| ------: | -------------: |
|       1 |     2.084063 s |
|       2 |     1.170643 s |
|       4 |     0.806536 s |
|       6 |     0.694168 s |
|      16 |     0.470630 s |

The execution time decreased as the number of Pthreads increased.

---

## 5.3 OpenMP Execution

The OpenMP performance program was executed with different numbers of threads.

| Threads | Execution Time |
| ------: | -------------: |
|       1 |       0.9493 s |
|       2 |       0.4754 s |
|       4 |       0.1869 s |
|       8 |       0.1259 s |

The execution time decreased as the number of OpenMP threads increased.

---

## 5.4 Execution-Time Comparison

The recorded measurements show that increasing the number of threads reduced execution time for both Pthreads and OpenMP for the tested workloads.

### Pthreads

```text
1 thread  → 2.084063 s
2 threads → 1.170643 s
4 threads → 0.806536 s
6 threads → 0.694168 s
16 threads → 0.470630 s
```

### OpenMP

```text
1 thread → 0.9493 s
2 threads → 0.4754 s
4 threads → 0.1869 s
8 threads → 0.1259 s
```

---

## 5.5 Speedup Calculation

Speedup is calculated as:

```text
Speedup = Time with 1 thread / Time with N threads
```

### Pthreads Speedup

| Threads |       Time | Speedup |
| ------: | ---------: | ------: |
|       1 | 2.084063 s |   1.00× |
|       2 | 1.170643 s |   1.78× |
|       4 | 0.806536 s |   2.58× |
|       6 | 0.694168 s |   3.00× |
|      16 | 0.470630 s |   4.43× |

### OpenMP Speedup

| Threads |     Time | Speedup |
| ------: | -------: | ------: |
|       1 | 0.9493 s |   1.00× |
|       2 | 0.4754 s |   2.00× |
|       4 | 0.1869 s |   5.08× |
|       8 | 0.1259 s |   7.54× |

These calculations use each implementation's own 1-thread measurement as its baseline.

---

## 5.6 Efficiency Calculation

Parallel efficiency is calculated using:

```text
Efficiency = (Speedup / Number of Threads) × 100%
```

The efficiency indicates how effectively the available threads are being used.

Efficiency generally decreases as thread count increases because parallel overhead and other system limitations become more significant.

---

## 5.7 Graphical Analysis

The performance data can be represented using:

### Execution Time vs. Number of Threads

The execution-time data shows a downward trend as the number of threads increases for both Pthreads and OpenMP.

### Speedup vs. Number of Threads

The speedup increases as more threads are used, although speedup is not necessarily perfectly linear because of parallel overhead and hardware limitations.

---

## 5.8 Performance Interpretation

The measured results demonstrate that parallel execution can reduce execution time by distributing computational work among multiple threads.

### Pthreads

Pthreads provides explicit control over:

* Thread creation
* Thread arguments
* Thread joining
* Synchronization
* Work distribution

### OpenMP

OpenMP simplifies parallel programming through compiler directives such as:

* `parallel`
* `parallel for`
* `reduction`
* `critical`
* `barrier`

### Effect of Increasing Thread Count

Increasing the number of threads reduced execution time in the recorded tests. However, performance does not necessarily scale perfectly with the number of threads because of:

* Thread creation and scheduling overhead
* Synchronization overhead
* Memory bandwidth limitations
* Hardware limitations
* Non-parallel portions of the program

The measured values are specific to the system, compiler, workload, and execution environment used for the experiment.

---

# 6. Observations

1. Pthreads provides explicit control over thread creation and joining.
2. Multiple Pthreads can divide a computational task into independent portions.
3. Unsynchronized shared-data access can produce a race condition.
4. A mutex protects a shared critical section and produces the expected result.
5. OpenMP simplifies parallel programming through compiler directives.
6. OpenMP reduction can be used to safely combine partial results.
7. The OpenMP race-condition program demonstrates incorrect results without synchronization.
8. The OpenMP `critical` directive protects a shared operation.
9. The OpenMP barrier coordinates different stages of parallel execution.
10. Increasing the number of threads reduced execution time in the recorded performance tests.
11. Speedup is not necessarily linear because of parallel overhead and hardware limitations.
12. Performance measurements depend on the execution environment and workload.

---

# 7. Conclusion

This experiment demonstrated fundamental parallel programming concepts using **Pthreads** and **OpenMP**.

The Pthreads programs demonstrated thread creation, multiple-thread execution, work division, race conditions, mutex synchronization, and performance measurement.

The OpenMP programs demonstrated parallel regions, work sharing, reduction, race conditions, critical-section synchronization, barriers, and performance measurement.

The performance analysis showed that increasing the number of threads reduced execution time for the tested workloads. Speedup increased with additional threads, although the improvement was not perfectly linear because of synchronization, scheduling, memory, and hardware limitations.

Overall, this experiment provided practical experience with **thread creation, parallel work distribution, synchronization, race-condition handling, performance measurement, speedup, and efficiency analysis in C**.

---

# 8. Repository Structure

```text
experiment_2/
│
├── README.md
│
├── Pthreads/
│   ├── thread1.c
│   ├── thread2.c
│   ├── thread_sum.c
│   ├── race.c
│   ├── mutex.c
│   └── pthread_perf.c
│
├── OpenMP/
│   ├── omp1.c
│   ├── omp_sum.c
│   ├── omp_race.c
│   ├── omp_critical.c
│   ├── omp_barrier.c
│   └── omp_perf.c
│
└── Screenshots/
    ├── Part-A/
    ├── Part-B/
    └── Part-C/
```

---

# 9. Compilation and Execution Commands

## Pthreads

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

## OpenMP

```bash
gcc omp1.c -o omp1 -fopenmp
./omp1

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

* **Pthreads:** thread creation, multiple-thread execution, work sharing, race conditions, mutex synchronization, and performance measurement.
* **OpenMP:** parallel regions, work sharing, reduction, race conditions, critical sections, barriers, and performance measurement.
* **Performance Analysis:** execution-time measurements, speedup, efficiency, and comparison of parallel execution.
