#include <stdio.h>

// tree recursion is when a recursive function have more than one recursive call.
void recursive(int n) 
{
    if (n > 0) // the max stacked functions in stack memory will be equal n + 1, accordingly to this base case.
    {
        printf("%d ", n); // this line will be executed in calling phase.
        recursive(n - 1); // this is the first recursive call.
        recursive(n - 1); // this recursive call will happen after the return of the first call.
    }
}
// Time O(2**n) - Space O(n)

int main()
{
    recursive(5);
    printf("\n");

    return 0;
}