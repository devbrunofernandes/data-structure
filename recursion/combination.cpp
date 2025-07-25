#include <stdio.h>

// factorial function
int fact(int n)
{
    int f = 1;

    for (int i = 1; i <= n; i++)
        f = f * i;

    return f;
}

// iterative combination calc function.
int iterativeC(int n, int r)
{
    int t1 = fact(n), t2 = fact(r), t3 = fact(n - r);

    return t1 / (t2 * t3);
} // time complexity: O(n)

// recursive combination calc function.
int recursiveC(int n, int r)
{
    if (r == 0 || n == r)
        return 1;

    return recursiveC(n-1, r-1) + recursiveC(n-1, r);
} // time complexity: O(n)

int main()
{
    int x = 5;

    printf("iterative combination: %d\n", iterativeC(x, 2));
    printf("recursive combination: %d\n", recursiveC(x, 2));
}