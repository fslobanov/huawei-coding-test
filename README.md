# huawei-coding-test
Huawei Cloud Storage team employment test

## Text 1(15)

It's just a summation algorithm for big numbers - we sum this 2 numbers digit by digit from MSB to LSB.
If overflow occurs, then we store carry flag and add it as 1 to the next sum. If one number is longer than another,
we simply add its digits to summation buffer.

We only allocate two dynamic input buffers for input strings, and static buffer for output string. To omit output number reverse
after summation completion, we fill output buffer from right to left, and use view on it to print actual result string

## Text 2(58)


## Test 3(74)

This problem is much complexer than previous two. It's an exact cover problem, and solution for this
is Donald Knuth's algorithm named AlgorithmX https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
State-of-the-art implementation for this algorithm is Dancing Links algorithm, but for this 
task I decided to implement simplified AlgorithmX by my own, and not to use 3rdparty implementations(task does not forbid this).
My implementation is quite simple and solution matrix being built from bit vectors, so memory overhead per the biggest 
matrix would be: (30*30cells / 8bits) * 100pieces = 12Kb. Matrix being copied before each modification, so it allow
us not to use backtracking mechanism to restore original matrix state after recursion returns. Worst case is to have
100 matrix copies(we consider them as same size, but it's not actually true), when we delete only one row per algorithm call.
So total max memory overhead for this solution would be 12Kb * 100calls = 1.2Mb at each moment, so it fits into task memory
constraints

Even this implementation may be optimized, we can also use custom allocator for matrix and their rows
