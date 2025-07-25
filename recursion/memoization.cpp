#include <stdio.h>
#include <stdlib.h>

// recursive fibonacci - this is execessive recursion because it call itself multiple times for the same parameters.
int recursiveFibonacci(int n)
{
    if (n <= 1)
        return n;

    return recursiveFibonacci(n - 2) + recursiveFibonacci(n - 1);
} // time complexity: O(2**n)

// initializing memory for array in memoized version of fibonacci.
int *initializeMemo(int n)
{
    int intSize = sizeof(int);
    int *memo = (int *)calloc((n + 1), intSize);

    for (int i = 0; i < (n + 1); i++)
    {
        memo[i] = -1;
    }

    return memo;
}

// memoized recursive fibonacci. its faster than normal recursion because it avoid calling the same function with same parameters multiple times.
int memoFibonacci(int n)
{
    static int originalN = n;
    static int *memo = initializeMemo(n); // memoization is use a variable for keeping track for calls result to avoid redundancy.

    if (n <= 1)
    {
        memo[n] = n;
        return n;
    }

    if (memo[n - 2] == -1) 
    {
        memo[n - 2] = memoFibonacci(n - 2);
    } 
    if (memo[n - 1] == -1)
    {
        memo[n - 1] = memoFibonacci(n - 1);
    }

    memo[n] = memo[n - 2] + memo[n - 1];
    int result = memo[n];

    if (originalN == n)
    {
        free(memo);
    }
    
    return result;
} // time complexity: O(n)

// iterative fibonacci
int iterativeFibonacci(int n)
{
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

int main()
{
    int x = 6;

    printf("recursive fibonacci: %d\n", recursiveFibonacci(x));
    printf("recursive memoized fibonacci: %d\n", memoFibonacci(x));
    printf("iterative fibonacci: %d\n", iterativeFibonacci(x));

    return 0;
}