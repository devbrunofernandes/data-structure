#include <stdio.h>

// calculating factorial of a number
// recursive function
int recursiveFactorial(int n) // risk of stack overflow
{
    if (n > 0)
    {
        return n * recursiveFactorial(n - 1);
    }
    return 1;
} // time complexity: O(n) - space complexity: O(n)

// iterative function
int iterativeFactorial(int n) // no risk of stack overflow
{
    int f = 1;

    for (int i = 1; i <= n; i++)
        f = f * i;

    return f;
} // time complexity: O(n) - space complexity: O(1)

int main()
{
    int x = 15;
    printf("iterative: %d\n", iterativeFactorial(x));
    printf("recursive: %d\n", recursiveFactorial(x));

    return 0;
}