# Comparison of Execution Times

### Comparative Execution Time

The table below summarizes the average execution times of 20 test runs for vector sizes $n = 2^{20}$, $2^{24}$, and $2^{28}$:

(You may view the raw [debug](ASSEMBLY/debug-test-results.txt) and [release](ASSEMBLY/release-test-results.txt) times)

| VECTOR SIZE (n) | ASSEMBLY DEBUG | C DEBUG | ASSEMBLY RELEASE | C RELEASE |
| --- | --- | --- | --- | --- |
| $2^{20}$ | 1.35ms | 3.15ms | 1.05ms | 0.95ms |
| $2^{24}$ | 16.17ms | 52.41ms | 19.75ms | 19.40ms |
| $2^{28}$ | 292.46ms | 852.87ms | 249.44ms | 252.52ms |

# Analysis

Based on what can be observed in the average execution times, we first noticed that the Debug build of Assembly is significantly faster than C's, with the tests using vector sizes of $2^{20}$ being ~2.33x faster, $2^{24}$ being ~3.24x faster, and $2^{28}$ being ~2.92x faster. In Debug build mode, the C compiler doesn't optimize speed and uses diagnostic checks to ensure traceability during development. It avoids reorganizing instructions so that each state could be inspected at that specific point, relying on stack memory, which slows execution; while Assembly utilizes CPU registers more than memory, reducing the need for memory accesses.

The execution times of C in Release build mode vary slightly to those of Assembly with a difference of a few milliseconds. Release mode utilizes optimizations and allows C to store and compute commonly used variables in registers, eliminating the need to frequently access the memory, explaining why execution times between C (in Release) and Assembly are very similar. 

Lastly, we compare the execution times of the C and Assembly kernels. In Assembly, the execution speed is consistent between Debug and Release, regardless of the build use. However, in C, the Debug execution time is approximately 3x slower than that of Release, making it less stable compared to that of Assembly. 

# Screenshots for Correctness Check

# Video
