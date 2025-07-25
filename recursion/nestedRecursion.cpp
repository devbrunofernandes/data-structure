#include <iostream>

// nested recursion is when a recursive call have a recursive call as a parameter.
// this is a nested recursive function.
int fun(int n)
{
    if (n > 100)
    {
        return n - 10;
    }
    else
    {
        return fun(fun(n + 11)); // this is nested recursive call.
    }
}

int main()
{
    int x = 95;
    printf("%d\n", fun(x));

    return 0;
}