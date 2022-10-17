# huawei-coding-test

Huawei Cloud Storage team employment test

## How to build

Both three tasks have tiny test coverage, so I used Google Test framework for this. GTest required to
be installed in your system, if you don't have it or not want to build tests, pass an '-Dhuawei_coding_test_BUILD_TESTS=OFF' 
option to CMake, by default tests are enabled

## Text 1(15)

It's just a summation algorithm for big numbers - we sum this 2 numbers digit by digit from MSB to LSB.
If overflow occurs, then we store carry flag and add it as 1 to the next sum. If one number is longer than another,
we simply add its digits to summation buffer. We only allocate two dynamic input buffers for input strings, and static buffer 
for output string. To omit output number reverse after summation completion, we fill output buffer from right to left, and 
use view on it to print actual result string

## Text 2(58)

The solution of this task is to iterate over numbers recursively with prefix summation. Numbers being sorted, iteration starts
from biggest to lowest, because it will allow to find GN faster. The pitfall of this task that cannot just subtract numbers from
upper bound to find proper sequence, consider:

3 55
40
5
7
00

Correct answer is 40+5+5+5, not 40+7+7, so we should really find the closest sum

## Test 3(74)

This problem is much complexer than previous two. It's an exact cover problem, and solution for this
is Donald Knuth's algorithm named AlgorithmX https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X.
State-of-the-art implementation for this algorithm is Dancing Links https://en.wikipedia.org/wiki/Dancing_Links,
but for this task I decided to implement simplified AlgorithmX by my own, and not to use 3rdparty
implementations(task does not forbid this explicitly). My implementation is quite simple and solution matrix being built from
bit vectors, so memory overhead per the biggest matrix would be: (30*30cells / 8bits) * 100pieces = 12Kb. Matrix being
copied before each modification, so it allow us not to use backtracking mechanism to restore original matrix state after
recursion returns. Worst case is to have 30 matrix copies - because we can only place 30 pieces without any intersection
on row or column, and would delete only one row per algorithm call. Note, that we consider them as same size, but it's
not actually true, anyway total max memory overhead for this solution would be 12Kb * 30calls = 0.5Mb, and it fits into 
task memory constraints

