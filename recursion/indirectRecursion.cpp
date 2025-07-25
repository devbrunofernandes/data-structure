#include <iostream>

void funB(int n); // funB prototype to the compiler know at the first call of funB that it will exist in code.

// indirect recursion is a function that calls another function(s) and eventually call the first function again.
// this is a indirect recursive function
void funA(int n)
{
    if (n > 0)
    {
        printf("%d ", n);
        funB(n - 1); // calls another function
    }
}

void funB(int n)
{
    if (n > 1)
    {
        printf("%d ", n);
        funA(n / 2); // calls the first recursive function again
    }
}

int main()
{
    int x = 50000;
    funA(x);

    return 0;
}