# SE3082 OpenMP Lab

## Exercise 1 - Barrier

The `#pragma omp barrier` directive creates a synchronization point.
Every thread must reach the barrier before any thread can continue to
the statements after it. Therefore, all threads execute the statements
before the barrier before any thread executes the statements after the
barrier. The order of the thread numbers may change between executions.

## Exercise 2 - Single

The `#pragma omp single` directive allows only one thread in the team
to execute the single region. The selected thread does not necessarily
have to be thread 0. The other threads skip the single region. By
default, an implicit barrier exists at the end of the single region.

## Exercise 3 - Master

The `#pragma omp master` directive allows only the master thread,
which is thread 0, to execute the master region. The other threads skip
this region. Unlike the single directive, master does not have an
implicit barrier at the end.

## Exercise 4 - Nested Loops

Without `collapse(2)`, OpenMP distributes only the five iterations of
the outer `r` loop among the available threads. A thread that receives
an `r` iteration executes all ten corresponding `k` iterations.

With `collapse(2)`, OpenMP combines the two nested loops into a single
iteration space containing 5 x 10 = 50 iterations. The 50 iterations
are distributed among the available threads, which can provide better
load balancing.

## Exercise 5 - Fibonacci Task Parallelization

The parallel region creates a team of OpenMP threads. The `single`
directive ensures that only one thread starts the initial Fibonacci
calculation. The `task` directives create separate tasks for
`fib(n - 1)` and `fib(n - 2)`. The `taskwait` directive waits until
both tasks are completed before adding their results.

## Exercise 6 - Array Multiplication with Strip Mining

Strip mining divides the array into fixed-size blocks called strips.
Each strip in this program contains 1024 elements. The outer strip
loop is distributed among OpenMP threads using static scheduling.
The `omp simd` directive allows the compiler to vectorize the
element-wise multiplication inside each strip. The strip size 1024
is a multiple of common SIMD vector widths.

The program was tested using 1, 2, 3, and 4 threads. The result was
verified by checking that every output element was equal to 6.0.
The actual execution times are recorded in
`Exercise06/timing_results.txt`.
