#include <iostream>

using namespace std;

void recursive(int n) // recursive function.
{
    if (n > 0)
    { 
        // no operation before the function call.
        recursive(n - 1); // this is a head recursion because the recursive call is first statement of the function.
        printf("%d ", n);
    }
} // every processing in the function is executed in returning/descending phase.
// Time O(n) - Space O(n)

void iterative(int n) // iterative version of recursive function, using while loop.
{
    int i = 1; // in head recursive function you cannot directly convert the recursive to iterative version.
    while (i <= n)
    {
        printf("%d ", i);
        i++;
    }
} // iterative versions are more efficient in space complexity. Have no risk of stack memory overflow.
// Time O(n) - Space O(1)

int main()
{
    // recursive(100000);
    printf("\n");
    iterative(100000);

    return 0;
}