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

Based on what can be observed in the average execution times, we first noticed that the Debug build of Assembly is significantly faster than C's. With the vector size of $2^{20}$ being ~2.33x faster, $2^{24}$ being ~3.24x faster, and $2^{28}$ being ~2.92x faster. In Debug build mode, the C compiler doesn't optimize speed and uses diagnostic checks to ensure traceability during development. It avoids reorganizing instructions so that each state could be inspected at that specific point, relying on stack memory, which slows execution; while Assembly directly accesses the registers, which minimizes its access time.

Second, the execution times of C in Release build mode are barely faster or almost the same (but slightly slower) as Assembly. Release mode utilizes optimizations, as C now uses registers directly, which does the same as Assembly, explaining why their execution times are very similar. 

Lastly are the execution times of each C and Assembly kernel. Assembly's execution speed fluctuates between Debug and Release, which means regardless of the build use, Assembly is much more stable compared to that of C, whose Debug execution time is approximately 3x slower than Release builds' execution.


# Screenshots for Correctness Check

# Video
