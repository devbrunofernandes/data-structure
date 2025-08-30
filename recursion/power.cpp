#include <iostream>

int recursivePower(int m, int n)
{
    if (n > 0)
    {
        return recursivePower(m, n - 1) * m;
    }
    return 1;
} // time complexity: O(n) - space complexity: O(n)

int fasterRecursivePower(int m, int n)
{
    if (n == 0)
        return 1;

    if (n%2==0)
        return fasterRecursivePower(m * m, n / 2);
    else
        return m * fasterRecursivePower(m * m, (n - 1) / 2);
} // time complexity: O(n) - space complexity: O(n)

int iterativePower(int m, int n)
{
    int r = 1;
    while (n > 0)
    {
        r = r * m;
        n--;
    }
    return r;
} // time complexity: O(n) - space complexity: O(1)

int main()
{
    int m = 3, n = 8;
    printf("iterative: %d\n", iterativePower(m, n));
    printf("recursive: %d\n", recursivePower(m, n));
    printf("faster recursive: %d\n", fasterRecursivePower(m, n));

    return 0;
}