#include <stdio.h>
#include <stdlib.h>

// recursive fibonacci - this is bad recursion because calls itself multiple times for the same parameters.
int recursiveFibonacci(const int n) {
    if (n <= 1)
        return n;

    return recursiveFibonacci(n - 2) + recursiveFibonacci(n - 1);
} // time complexity: O(2**n)

int memoFibonacciHelper(int n, int memo[]) {
    if (n <= 1) return n;

    if (memo[n] != -1) return memo[n];

    memo[n] = memoFibonacciHelper(n - 1, memo) + memoFibonacciHelper(n - 2, memo);
    return memo[n];
}

// memoized recursive fibonacci. it's faster than normal recursion because avoid calling the same function with same parameters multiple times.
int memoFibonacci(const int n) {
    if (n <= 1) return n;

    int* memo = (int*) malloc(n * sizeof(int));

    for (int i = 1; i <= n; i++)
        memo[i] = -1;

    const int result = memoFibonacciHelper(n, memo);
    
    return result;
} // time complexity: O(n)

// iterative fibonacci
int iterativeFibonacci(int n) {
    int t0 = 0, t1 = 1, s = 0;
    if (n <= 1)
        return n;

    for (int i = 2; i <= n; i++)
    {
        s = t0 + t1;
        t0 = t1;
        t1 = s;
    }
    return s;
} // time complexity: O(n)

int main() {
    int x = 6;

    printf("recursive fibonacci: %d\n", recursiveFibonacci(x));
    printf("recursive memoized fibonacci: %d\n", memoFibonacci(x));
    printf("iterative fibonacci: %d\n", iterativeFibonacci(x));

    return 0;
}