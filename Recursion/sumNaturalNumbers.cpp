#include <iostream>

// calculating sum of first n natural numbers using recursion.
int recursiveSum(int n)
{
    if (n > 0)
    {
        return recursiveSum(n - 1) + n;
    }
    return 0;
}

// calculating sum of first n natural numbers using math formula, this is the fastest way for computer and spend low memory.
int formulaSum(int n)
{
    return n * (n + 1) / 2;
}

// calculating sum of first n natural numbers using iterative function, this spend low memory but is as fast as recursive.
int iterativeSum(int n)
{
    int s = 0, i = 0;

    for (i = 1; i <= n; i++)
        s = s + i;

    return s;
}

int main()
{
    int x = 10;
    printf("recursion: %d\n", recursiveSum(x));
    printf("formula: %d\n", formulaSum(x));
    printf("iterative: %d\n", iterativeSum(x));

    return 0;
}