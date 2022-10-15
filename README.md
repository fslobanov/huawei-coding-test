# huawei-coding-test
Huawei Cloud Storage team employment test

## Text 1(15)

Topic description：
I have a very simple problem for you. Given two integers A and B, your job is to calculate the Sum of A + B.

### Requirement
time limitation：1000ms, memory limitation：100MB
Input
The first line of the input contains an integer T(1≤T≤20) which means the number of test cases.
Then T lines follow, each line consists of two positive integers, A and B. Notice that the integers are very large,that means you should not process them by using 32-bit integer.You may assume the length of each integer will not exceed 1000.

Output
For each test case, you should output two lines. The first line is "Case #:", # means the number of the test case. The second line is the an equation "A + B = Sum", Sum means the result of A + B.Note there are some spaces int the equation. Output a blank line between two test cases.

Example 1

Input
2
1 2
112233445566778899 998877665544332211

Output
Case 1:
1 + 2 = 3

Case 2:
112233445566778899 + 998877665544332211 = 1111111111111111110

Function
// we have defined the necessary header files here for this problem.
// If additional header files are needed in your program, please import here.
int main()
{  
// please define the C++ input here. For example: int a,b; cin>>a>>b;;  
// please finish the function body here.  
// please define the C++ output here. For example:cout<<____<<endl;
return 0;
}

## Text 2(58)

Saya likes math, because she thinks math can make her cleverer.
One day, Kudo invited a very simple game:
Given N integers, then the players choose no more than four integers from them (can be repeated) and add them together. Finally, the one whose sum is the largest wins the game. It seems very simple, but there is one more condition: the sum shouldn’t larger than a number M.
Saya is very interest in this game. She says that since the number of integers is finite, we can enumerate all the selecting and find the largest sum. Saya calls the largest sum Greatest Number (GN). After reflecting for a while, Saya declares that she found the GN and shows her answer.
Kudo wants to know whether Saya’s answer is the best, so she comes to you for help.
Can you help her to compute the GN?

### Requirement
time limitation：1000ms, memory limitation：100MB
Input
The input consists of several test cases.
The first line of input in each test case contains two integers N (0<N≤1000) and M(0<M≤ 1000000000), which represent the number of integers and the upper bound.
Each of the next N lines contains the integers. (Not larger than 1000000000)
The last case is followed by a line containing two zeros.

Output
For each case, print the case number (1, 2 …) and the GN.
Your output format should imitate the sample output. Print a blank line between each test case.

Example

Input
2 10
100
2
0 0

Output
Case 1: 8

Function
// we have defined the necessary header files here for this problem.
// If additional header files are needed in your program, please import here.

int main()
{  
// please define the C++ input here. For example: int a,b; cin>>a>>b;;  
// please finish the function body here.  
// please define the C++ output here. For example:cout<<____<<endl;
return 0;
}

## Test 3(74)

Your boss once had got many copies of a treasure map. Unfortunately, all the copies are now broken to many rectangular pieces, and what make it worse, he has lost some of the pieces. Luckily, it is possible to figure out the position of each piece in the original map. Now the boss asks you, the talent programmer, to make a complete treasure map with these pieces. You need to make only one complete map and it is not necessary to use all the pieces. But remember, pieces are not allowed to overlap with each other (See sample 2).

### Requirement
time limitation：3000ms, memory limitation：100MB

Input
The first line of the input contains an integer T (T <= 10), indicating the number of cases.

For each case, the first line contains three integers n m p (1 <= n, m <= 30, 1 <= p <= 100), the width and the height of the map, and the number of pieces. Then p lines follow, each consists of four integers x1 y1 x2 y2 (0 <= x1 < x2 <= n, 0 <= y1 < y2 <= m), where (x1, y1) is the coordinate of the lower-left corner of the rectangular piece, and (x2, y2) is the coordinate of the upper-right corner in the original map.

Cases are separated by one blank line.

Output
If you can make a complete map with these pieces, output the least number of pieces you need to achieve this. If it is impossible to make one complete map, just output -1.


Example

Input
3
5 5 1
0 0 5 5

5 5 2
0 0 3 5
2 0 5 5

30 30 5
0 0 30 10
0 10 30 20
0 20 30 30
0 0 15 30
15 0 30 30

Output

1
-1
2


Function
// we have defined the necessary header files here for this problem.
// If additional header files are needed in your program, please import here.

int main()
{  
// please define the C++ input here. For example: int a,b; cin>>a>>b;;  
// please finish the function body here.  
// please define the C++ output here. For example:cout<<____<<endl;
return 0;
}